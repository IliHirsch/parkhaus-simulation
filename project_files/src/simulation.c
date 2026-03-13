#include "simulation.h"
#include "io.h"
#include "parking.h"
#include "queue.h"
#include "rng.h"
#include "stats.h"

static void simulate_step(
    ParkingLot* p_parking,
    Queue* p_queue,
    const SimConfig* p_cfg,
    Stats* p_stats,
    int step,
    unsigned int* p_next_vehicle_id
)
{

    SimStatus status = SIM_OK;
    bool arrival_occurs = false;

    if (p_parking == NULL || p_queue == NULL || p_cfg == NULL || p_stats == NULL || p_next_vehicle_id == NULL){
        return;
    }

    stats_reset_step(p_stats);

    //Abfahrten
    parking_process_departures(p_parking, p_stats);

    //Ankunft
    arrival_occurs = rng_chance_percent(p_cfg->ankunft_wahrscheinlichkeit_prozent);

    /* Möglichkeit für Debugging

    if (arrival_occurs == true){
        status = parking_handle_arrival(p_parking, p_queue, p_cfg, p_stats, step, p_next_vehicle_id);
        if (status == SIM_KFZ_WARTEN){
        }
        else if (status == SIM_OK){
        }
        else{
        }
    }
    */

    // Warteschlange abarbeiten
    parking_process_queue(p_parking, p_queue, p_stats, step);

    //Statistiken aktualisieren, ausgeben, loggen
    stats_update_step(p_stats, p_parking, p_queue, step);
    stats_print_step(p_stats, step);
    io_log_step(p_stats, step);
}

void simulation_run(const SimConfig* p_cfg){

    ParkingLot parking;
    Queue queue;
    Stats stats;

    unsigned int next_vehicle_id = 1;
    bool log_ok = false;

    int step = 0;

    // Initialisierung
    rng_seed(p_cfg->seed);

    parking_init(&parking, p_cfg->anzahl_stellplaetze);
    queue_init(&queue);
    stats_init(&stats);

    log_ok = io_open_log("project_files/data/log.txt");

    if (log_ok == false){
        printf("Fehler: Log-Datei konnte nicht geöffnet werden\n");
    }

    // Simulation für die Zeitschritte
    for (step = 0; step < p_cfg->sim_dauer_zeitschritte; step++){
        simulate_step(&parking, &queue, p_cfg, &stats, step, &next_vehicle_id);
    }

    // Abschlussausgabe
    stats_print_final(&stats);
    io_log_final(&stats);

    // Cleanup
    io_close_log();
    queue_free(&queue);
    parking_free(&parking);
}
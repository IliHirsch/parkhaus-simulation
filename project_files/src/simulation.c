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
    /*
     * FUNCTION simulate_step(parking, queue, cfg, stats, step, next_vehicle_id)
     * INPUT  parking, queue, cfg, stats, step, next_vehicle_id
     * OUTPUT aktualisierte Zustände + Step-Statistiken
     *
     * // Step-Zähler zurücksetzen
     * CALL stats_reset_step(stats)
     *
     * // 1) Abfahrten
     * CALL parking_process_departures(parking, stats)
     *
     * // 2) Ankunft (max. 1 Fahrzeug pro Step)
     * IF CALL rng_chance_percent(cfg->ankunft_wahrscheinlichkeit_prozent) THEN
     *     status <- CALL parking_handle_arrival(parking, queue, cfg, stats, step, next_vehicle_id)
     *
     *     // Optional: Status dokumentieren
     *     IF status == SIM_KFZ_WARTEN THEN
     *         // Fahrzeug wurde in Warteschlange eingereiht
     *     ELSE IF status == SIM_OK THEN
     *         // Fahrzeug wurde direkt eingeparkt
     *     ELSE
     *         // Fehlerfall (sollte bei validierter cfg nicht passieren)
     *     END IF
     * END IF
     *
     * // 3) Warteschlange abarbeiten (solange Platz frei)
     * CALL parking_process_queue(parking, queue, stats, step)
     *
     * // 4) Statistiken aktualisieren + ausgeben + loggen
     * CALL stats_update_step(stats, parking, queue, step)
     * CALL stats_print_step(stats, step)
     * CALL io_log_step(stats, step)
     *
     * END FUNCTION
     */

    SimStatus status = SIM_OK;
    bool arrival_occurs = false;

    stats_reset_step(p_stats);

    parking_process_departures(p_parking, p_stats);

    arrival_occurs = rng_chance_percent(p_cfg->ankunft_wahrscheinlichkeit_prozent);

    if (arrival_occurs == true){
        status = parking_handle_arrival(
            p_parking,
            p_queue,
            p_cfg,
            p_stats,
            step,
            p_next_vehicle_id);

        if (status == SIM_KFZ_WARTEN){
            /* Vehicle placed in queue */
        }
        else if (status == SIM_OK){
            /* Vehicle parked immediately */
        }
        else{
            /* Error case (should not occur with valid config) */
        }
    }

    parking_process_queue(p_parking, p_queue, p_stats, step);
    stats_update_step(p_stats, p_parking, p_queue, step);
    stats_print_step(p_stats, step);
    io_log_step(p_stats, step);
}

void simulation_run(const SimConfig* p_cfg){
    /*
     * FUNCTION simulation_run(cfg)
     * INPUT  cfg
     * OUTPUT (Konsole + Log-Datei)
     *
     * DECLARE parking : ParkingLot
     * DECLARE queue   : Queue
     * DECLARE stats   : Stats
     * DECLARE next_vehicle_id : unsigned int
     * DECLARE ok : bool
     *
     * // Initialisierung
     * CALL rng_seed(cfg->seed)
     * CALL parking_init(&parking, cfg->anzahl_stellplaetze)
     * CALL queue_init(&queue)
     * CALL stats_init(&stats)
     *
     * ok <- CALL io_open_log("project_files/data/log.txt")
     * IF ok == false THEN
     *     OUTPUT "Fehler: Log-Datei konnte nicht geöffnet werden"
     *     // Simulation läuft trotzdem weiter (nur ohne Log-Datei)
     * END IF
     *
     * next_vehicle_id <- 1
     *
     * // Simulation über diskrete Zeitschritte
     * FOR step <- 0 TO (cfg->sim_dauer_zeitschritte - 1) DO
     *     CALL simulate_step(&parking, &queue, cfg, &stats, step, &next_vehicle_id)
     * END FOR
     *
     * // Abschlussausgabe
     * CALL stats_print_final(&stats)
     * CALL io_log_final(&stats)
     *
     * // Cleanup
     * CALL io_close_log()
     * CALL queue_free(&queue)
     * CALL parking_free(&parking)
     *
     * END FUNCTION
     */

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
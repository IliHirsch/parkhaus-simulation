#include <stdio.h>
#include <stdbool.h>

#include "../include/simulation.h"
#include "../include/io.h"
#include "../include/parking.h"
#include "../include/queue.h"
#include "../include/rng.h"
#include "../include/stats.h"

/**
 * @brief Simuliert genau einen Zeitschritt.
 *
 * Ablauf:
 * 1. Step-Statistiken zurücksetzen
 * 2. Abfahrten verarbeiten
 * 3. Warteschlange abarbeiten (wartende Fahrzeuge haben Vorrang)
 * 4. Ggf. neue Ankunft erzeugen
 * 5. Statistiken aktualisieren, ausgeben und loggen
 *
 * @param[in,out] p_parking Parkhauszustand.
 * @param[in,out] p_queue Warteschlange.
 * @param[in] p_cfg Simulationskonfiguration.
 * @param[in,out] p_stats Statistikstruktur.
 * @param[in] step Aktueller Zeitschritt.
 * @param[in,out] p_next_vehicle_id Nächste freie Fahrzeug-ID.
 */
static void simulate_step(
    ParkingLot* p_parking,
    Queue* p_queue,
    const SimConfig* p_cfg,
    Stats* p_stats,
    int step,
    unsigned int* p_next_vehicle_id
)
{
    if (p_parking == NULL ||
        p_queue == NULL ||
        p_cfg == NULL ||
        p_stats == NULL ||
        p_next_vehicle_id == NULL) {
        return;
    }

    stats_reset_step(p_stats);

    /* 1. Fahrzeuge fahren ggf. ab */
    parking_process_departures(p_parking, p_stats);

    /* 2. Warteschlange zuerst abarbeiten, damit FIFO fair bleibt */
    parking_process_queue(p_parking, p_queue, p_stats, step);

    /* 3. Mit gegebener Wahrscheinlichkeit kommt ein neues Fahrzeug an */
    if (rng_chance_percent(p_cfg->ankunft_wahrscheinlichkeit_prozent)) {
        SimStatus status = parking_handle_arrival(
            p_parking,
            p_queue,
            p_cfg,
            p_stats,
            step,
            p_next_vehicle_id
        );

        if (status == SIM_ERR_INPUT) {
            printf("Warnung: Fahrzeugankunft in Step %d konnte nicht verarbeitet werden.\n", step);
        }
    }

    /* 4. Statistiken aktualisieren und ausgeben */
    stats_update_step(p_stats, p_parking, p_queue, step);
    stats_print_step(p_stats, step);
    io_log_step(p_stats, step);
}

/**
 * @brief Führt die komplette Parkhaus-Simulation aus.
 *
 * Initialisiert alle benötigten Module, simuliert die konfigurierte Anzahl
 * an Zeitschritten und gibt am Ende die Gesamtstatistik aus.
 *
 * @param[in] p_cfg Simulationskonfiguration.
 */
void simulation_run(const SimConfig* p_cfg)
{
    if (p_cfg == NULL || !config_validate(p_cfg)) {
        printf("Fehler: Ungueltige Konfiguration.\n");
        return;
    }

    ParkingLot parking;
    Queue queue;
    Stats stats;

    unsigned int next_vehicle_id = 1U;
    bool log_ok;
    int step;

    /* Defensive Grundinitialisierung */
    parking.slots = NULL;
    parking.kapazitaet = 0U;
    parking.belegte_plaetze = 0U;

    queue.head = NULL;
    queue.tail = NULL;
    queue.size = 0U;

    stats_init(&stats);
    rng_seed(p_cfg->seed);

    if (!parking_init(&parking, p_cfg->anzahl_stellplaetze)) {
        printf("Fehler: Speicher fuer Parkplaetze konnte nicht allokiert werden.\n");
        return;
    }

    queue_init(&queue);

    log_ok = io_open_log("parkhaus_log.txt");
    if (!log_ok) {
        printf("Warnung: Log-Datei konnte nicht geoeffnet werden.\n");
    }

    for (step = 1; step <= p_cfg->sim_dauer_zeitschritte; step++) {
        simulate_step(&parking, &queue, p_cfg, &stats, step, &next_vehicle_id);
    }

    stats_print_final(&stats);
    io_log_final(&stats);

    io_close_log();
    queue_free(&queue);
    parking_free(&parking);
}
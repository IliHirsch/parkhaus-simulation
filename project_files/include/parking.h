#ifndef PARKING_H
#define PARKING_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"
#include "vehicle.h"
#include "queue.h"
#include "config.h"
#include "stats.h"

/* =========================
   Parkhaus-Verwaltung
   ========================= */

/**
 * @brief Initialisiert das Parkhaus.
 *
 * @param[out] p          Parkhaus-Struktur
 * @param[in]  kapazitaet Anzahl Stellplätze
 */
void parking_init(ParkingLot* p, size_t kapazitaet);
/*
 * PSEUDOCODE:
 * - p->kapazitaet = kapazitaet
 * - p->belegte_plaetze = 0
 * - allocate memory for slots
 * - for each slot:
 *     slot.belegt = false
 */

/**
 * @brief Gibt Speicher des Parkhauses frei.
 */
void parking_free(ParkingLot* p);
/*
 * PSEUDOCODE:
 * - free(p->slots)
 */

/**
 * @brief Sucht freien Stellplatz.
 *
 * @return Index oder -1 wenn keiner frei
 */
int parking_find_free_slot(const ParkingLot* p);
/*
 * PSEUDOCODE:
 * - for i in 0..kapazitaet-1:
 *     if slot[i] not belegt:
 *         return i
 * - return -1
 */

/**
 * @brief Behandelt neu ankommendes Fahrzeug.
 *
 * @return SIM_OK oder SIM_KFZ_WARTEN
 */
SimStatus parking_handle_arrival(
    ParkingLot* p,
    Queue* q,
    const SimConfig* cfg,
    Stats* stats,
    int current_time
);
/*
 * PSEUDOCODE:
 * - stats->neu_angekommen++
 * - vehicle initialisieren (id, restparkdauer, einfahrtzeit)
 * - slot = parking_find_free_slot()
 * - if slot == -1:
 *     queue_push(q, vehicle)
 *     return SIM_KFZ_WARTEN
 * - else:
 *     p->slots[slot] = vehicle
 *     p->slots[slot].belegt = true
 *     p->belegte_plaetze++
 *     return SIM_OK
 */

/**
 * @brief Reduziert Parkdauer und entfernt Fahrzeuge.
 */
void parking_process_departures(
    ParkingLot* p,
    Queue* q,
    Stats* stats
);
/*
 * PSEUDOCODE:
 * - for each slot:
 *     if belegt:
 *         restparkdauer--
 *         if restparkdauer == 0:
 *             freigeben
 *             belegte_plaetze--
 *             stats->verlassen++
 *             if queue not empty:
 *                 pop vehicle
 *                 auf slot setzen
 *                 belegte_plaetze++
 *                 stats->abgefertigte_wartende++
 */

#endif // PARKING_H
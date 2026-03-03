#ifndef PARKING_H
#define PARKING_H

#include <stddef.h>
#include "types.h"
#include "queue.h"
#include "config.h"
#include "stats.h"
#include "rng.h"

/**
 * @brief Initialisiert das Parkhaus (Slots allokieren und als frei markieren).
 *
 * @param[out] p Parkhausstruktur, die initialisiert wird.
 * @param[in] kapazitaet Anzahl Stellplätze.
 */
void parking_init(ParkingLot* p, size_t kapazitaet);

/**
 * @brief Gibt den Speicher der Slots frei und setzt das Parkhaus zurück.
 *
 * @param[in,out] p Parkhausstruktur.
 */
void parking_free(ParkingLot* p);

/**
 * @brief Sucht einen freien Stellplatz im Parkhaus.
 *
 * @param[in] p Parkhausstruktur.
 * @return Index eines freien Slots (0..kapazitaet-1) oder -1 wenn keiner frei ist.
 */
int parking_find_free_slot(const ParkingLot* p);

/**
 * @brief Behandelt die Ankunft eines Fahrzeugs (einparken oder in Warteschlange).
 *
 * Erzeugt ein neues Vehicle (ID, restparkdauer, einfahrtzeit) und aktualisiert Step- und Aggregat-Stats.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] q Warteschlange für wartende Fahrzeuge.
 * @param[in] cfg Simulationskonfiguration (u.a. max_parkdauer).
 * @param[in,out] stats Statistikstruktur.
 * @param[in] current_time Aktueller Zeitschritt (Ankunftszeit).
 * @param[in,out] next_vehicle_id Zeiger auf nächste freie Fahrzeug-ID (wird inkrementiert).
 * @return SIM_OK wenn direkt eingeparkt, SIM_KFZ_WARTEN wenn in Queue, SIM_ERR_INPUT bei Fehlern.
 */
SimStatus parking_handle_arrival(
    ParkingLot* p,
    Queue* q,
    const SimConfig* cfg,
    Stats* stats,
    int current_time,
    unsigned int* next_vehicle_id
);

/**
 * @brief Verarbeitet Abfahrten: Restparkdauer reduzieren und Fahrzeuge ggf. entfernen.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] stats Statistikstruktur (verlassen wird erhöht).
 */
void parking_process_departures(ParkingLot* p, Stats* stats);

/**
 * @brief Arbeitet die Warteschlange ab, solange Plätze frei sind.
 *
 * Fahrzeuge werden FIFO entnommen und eingeparkt. Wartezeit wird als current_time - einfahrtzeit erfasst.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] q Warteschlange.
 * @param[in,out] stats Statistikstruktur (abgefertigte_wartende, sum_wartezeit/count_wartezeit).
 * @param[in] current_time Aktueller Zeitschritt.
 */
void parking_process_queue(ParkingLot* p, Queue* q, Stats* stats, int current_time);

#endif /* PARKING_H */
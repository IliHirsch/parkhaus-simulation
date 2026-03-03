#ifndef PARKING_H
#define PARKING_H

#include <stdbool.h>
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
/*
 * FUNCTION parking_init(p, kapazitaet)
 * INPUT  p, kapazitaet
 * OUTPUT p initialisiert (Slots allokiert und auf frei gesetzt)
 *
 * p->kapazitaet <- kapazitaet
 * p->belegte_plaetze <- 0
 *
 * allocate p->slots
 *
 * FOR i <- 0 TO kapazitaet-1 DO
 *     p->slots[i].belegt <- false
 * END FOR
 *
 * END FUNCTION
 */

/**
 * @brief Gibt den Speicher der Slots frei und setzt das Parkhaus zurück.
 *
 * @param[in,out] p Parkhausstruktur.
 */
void parking_free(ParkingLot* p);
/*
 * FUNCTION parking_free(p)
 * free(p->slots)
 * p->slots <- NULL
 * p->kapazitaet <- 0
 * p->belegte_plaetze <- 0
 * END FUNCTION
 */

/**
 * @brief Sucht einen freien Stellplatz im Parkhaus.
 *
 * @param[in] p Parkhausstruktur.
 * @return Index eines freien Slots (0..kapazitaet-1) oder -1 wenn keiner frei ist.
 */
int parking_find_free_slot(const ParkingLot* p);
/*
 * FUNCTION parking_find_free_slot(p) RETURNS index
 * FOR i <- 0 TO p->kapazitaet-1 DO
 *     IF p->slots[i].belegt == false THEN RETURN i END IF
 * END FOR
 * RETURN -1
 * END FUNCTION
 */

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
/*
 * FUNCTION parking_handle_arrival(p, q, cfg, stats, current_time, next_vehicle_id) RETURNS status
 * stats->neu_angekommen <- stats->neu_angekommen + 1
 *
 * v.id <- *next_vehicle_id
 * *next_vehicle_id <- *next_vehicle_id + 1
 *
 * v.restparkdauer <- CALL rng_int(1, cfg->max_parkdauer)
 * v.einfahrtzeit <- current_time
 *
 * stats->sum_parkdauer <- stats->sum_parkdauer + v.restparkdauer
 * stats->count_parkdauer <- stats->count_parkdauer + 1
 *
 * slot <- CALL parking_find_free_slot(p)
 * IF slot == -1 THEN
 *     CALL queue_push(q, v)
 *     RETURN SIM_KFZ_WARTEN
 * ELSE
 *     p->slots[slot].fahrzeug <- v
 *     p->slots[slot].belegt <- true
 *     p->belegte_plaetze <- p->belegte_plaetze + 1
 *     RETURN SIM_OK
 * END IF
 *
 * END FUNCTION
 */

/**
 * @brief Verarbeitet Abfahrten: Restparkdauer reduzieren und Fahrzeuge ggf. entfernen.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] stats Statistikstruktur (verlassen wird erhöht).
 */
void parking_process_departures(ParkingLot* p, Stats* stats);
/*
 * FUNCTION parking_process_departures(p, stats)
 * FOR i <- 0 TO p->kapazitaet-1 DO
 *     IF p->slots[i].belegt THEN
 *         p->slots[i].fahrzeug.restparkdauer <- p->slots[i].fahrzeug.restparkdauer - 1
 *         IF p->slots[i].fahrzeug.restparkdauer <= 0 THEN
 *             p->slots[i].belegt <- false
 *             p->belegte_plaetze <- p->belegte_plaetze - 1
 *             stats->verlassen <- stats->verlassen + 1
 *         END IF
 *     END IF
 * END FOR
 * END FUNCTION
 */

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
/*
 * FUNCTION parking_process_queue(p, q, stats, current_time)
 * WHILE CALL queue_is_empty(q) == false DO
 *     slot <- CALL parking_find_free_slot(p)
 *     IF slot == -1 THEN BREAK END IF
 *
 *     ok <- CALL queue_pop(q, &v)
 *     IF ok == false THEN BREAK END IF
 *
 *     wartezeit <- current_time - v.einfahrtzeit
 *     stats->sum_wartezeit <- stats->sum_wartezeit + wartezeit
 *     stats->count_wartezeit <- stats->count_wartezeit + 1
 *
 *     p->slots[slot].fahrzeug <- v
 *     p->slots[slot].belegt <- true
 *     p->belegte_plaetze <- p->belegte_plaetze + 1
 *
 *     stats->abgefertigte_wartende <- stats->abgefertigte_wartende + 1
 * END WHILE
 *
 * END FUNCTION
 */

#endif // PARKING_H
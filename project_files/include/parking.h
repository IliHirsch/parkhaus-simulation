#ifndef PARKING_H
#define PARKING_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"
#include "queue.h"
#include "config.h"
#include "stats.h"
#include "rng.h"

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

void parking_free(ParkingLot* p);
/*
 * FUNCTION parking_free(p)
 * free(p->slots)
 * p->slots <- NULL
 * p->kapazitaet <- 0
 * p->belegte_plaetze <- 0
 * END FUNCTION
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
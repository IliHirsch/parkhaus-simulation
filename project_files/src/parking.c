#include "parking.h"
#include <stdlib.h>

/**
 * Initialisiert das Parkhaus.
 */
void parking_init(ParkingLot* p, size_t kapazitaet)
{
    if (p == NULL) {
        return;
    }

    p->kapazitaet = kapazitaet;
    p->belegte_plaetze = 0;

    p->slots = malloc(kapazitaet * sizeof(ParkingSlot));
    if (p->slots == NULL) {
        p->kapazitaet = 0;
        return;
    }

    for (size_t i = 0; i < kapazitaet; i++) {
        p->slots[i].belegt = false;
    }
}

/**
 * Gibt Speicher des Parkhauses frei.
 */
void parking_free(ParkingLot* p)
{
    if (p == NULL) {
        return;
    }

    free(p->slots);
    p->slots = NULL;
    p->kapazitaet = 0;
    p->belegte_plaetze = 0;
}

/**
 * Sucht freien Parkplatz.
 */
int parking_find_free_slot(const ParkingLot* p)
{
    if (p == NULL || p->slots == NULL) {
        return -1;
    }

    for (size_t i = 0; i < p->kapazitaet; i++) {
        if (!p->slots[i].belegt) {
            return (int)i;
        }
    }

    return -1;
}

/**
 * Verarbeitet Fahrzeugankunft.
 */
SimStatus parking_handle_arrival(
    ParkingLot* p,
    Queue* q,
    const SimConfig* cfg,
    Stats* stats,
    int current_time,
    unsigned int* next_vehicle_id
)
{
    if (p == NULL || q == NULL || cfg == NULL || stats == NULL || next_vehicle_id == NULL) {
        return SIM_ERR_INPUT;
    }

    stats->neu_angekommen++;

    Vehicle v;

    v.id = *next_vehicle_id;
    (*next_vehicle_id)++;

    v.restparkdauer = rng_int(1, cfg->max_parkdauer);
    v.einfahrtzeit = current_time;

    stats->sum_parkdauer += v.restparkdauer;
    stats->count_parkdauer++;

    int slot = parking_find_free_slot(p);

    if (slot == -1) {

        bool ok = queue_push(q, v);
        if (!ok) {
            return SIM_ERR_INPUT;
        }

        return SIM_KFZ_WARTEN;
    }

    p->slots[slot].fahrzeug = v;
    p->slots[slot].belegt = true;
    p->belegte_plaetze++;

    return SIM_OK;
}

/**
 * Bearbeitet Abfahrten.
 */
void parking_process_departures(ParkingLot* p, Stats* stats)
{
    if (p == NULL || stats == NULL) {
        return;
    }

    for (size_t i = 0; i < p->kapazitaet; i++) {

        if (p->slots[i].belegt) {

            p->slots[i].fahrzeug.restparkdauer--;

            if (p->slots[i].fahrzeug.restparkdauer <= 0) {

                p->slots[i].belegt = false;
                p->belegte_plaetze--;

                stats->verlassen++;
            }
        }
    }
}

/**
 * Arbeitet Warteschlange ab.
 */
void parking_process_queue(ParkingLot* p, Queue* q, Stats* stats, int current_time)
{
    if (p == NULL || q == NULL || stats == NULL) {
        return;
    }

    while (!queue_is_empty(q)) {

        int slot = parking_find_free_slot(p);
        if (slot == -1) {
            break;
        }

        Vehicle v;

        bool ok = queue_pop(q, &v);
        if (!ok) {
            break;
        }

        int wartezeit = current_time - v.einfahrtzeit;

        stats->sum_wartezeit += wartezeit;
        stats->count_wartezeit++;

        p->slots[slot].fahrzeug = v;
        p->slots[slot].belegt = true;
        p->belegte_plaetze++;

        stats->abgefertigte_wartende++;
    }
}
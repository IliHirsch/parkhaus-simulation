#include "../include/parking.h"
#include <stdlib.h>

/**
 * @brief Initialisiert das Parkhaus.
 *
 * Allokiert ein Array von Stellplätzen mit der angegebenen Kapazität,
 * markiert alle Plätze als frei und setzt die Verwaltungsdaten zurück.
 *
 * @param[out] p Parkhausstruktur, die initialisiert werden soll.
 * @param[in] kapazitaet Anzahl der Stellplätze.
 * @return true wenn das Parkhaus erfolgreich initialisiert wurde,
 *         sonst false.
 */
bool parking_init(ParkingLot* p, size_t kapazitaet)
{
    if (p == NULL || kapazitaet == 0U) {
        return false;
    }

    p->slots = NULL;
    p->kapazitaet = 0U;
    p->belegte_plaetze = 0U;

    p->slots = malloc(kapazitaet * sizeof(ParkingSlot));
    if (p->slots == NULL) {
        return false;
    }

    p->kapazitaet = kapazitaet;
    p->belegte_plaetze = 0U;

    for (size_t i = 0U; i < kapazitaet; i++) {
        p->slots[i].belegt = false;
    }

    return true;
}

/**
 * @brief Gibt den Speicher des Parkhauses frei.
 *
 * Gibt das Array der Stellplätze frei und setzt alle Verwaltungsfelder
 * der Parkhausstruktur auf definierte Ausgangswerte zurück.
 *
 * @param[in,out] p Parkhausstruktur.
 */
void parking_free(ParkingLot* p)
{
    if (p == NULL) {
        return;
    }

    free(p->slots);
    p->slots = NULL;
    p->kapazitaet = 0U;
    p->belegte_plaetze = 0U;
}

/**
 * @brief Sucht einen freien Stellplatz im Parkhaus.
 *
 * Durchläuft alle Stellplätze linear und liefert den Index des ersten
 * freien Platzes zurück.
 *
 * @param[in] p Parkhausstruktur.
 * @return Index eines freien Stellplatzes oder -1, wenn kein Platz frei ist
 *         oder die Eingabe ungültig ist.
 */
int parking_find_free_slot(const ParkingLot* p)
{
    if (p == NULL || p->slots == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < p->kapazitaet; i++) {
        if (!p->slots[i].belegt) {
            return (int)i;
        }
    }

    return -1;
}

/**
 * @brief Behandelt die Ankunft eines Fahrzeugs.
 *
 * Erzeugt ein neues Fahrzeug mit laufender ID, zufälliger Parkdauer und
 * aktueller Ankunftszeit. Wenn ein freier Stellplatz vorhanden ist,
 * wird das Fahrzeug direkt eingeparkt. Andernfalls wird es in die
 * Warteschlange eingefügt.
 *
 * Die Statistik für neue Fahrzeuge und geplante Parkdauer wird nur dann
 * erhöht, wenn das Fahrzeug erfolgreich eingeparkt oder erfolgreich in
 * die Warteschlange übernommen wurde.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] q Warteschlange für wartende Fahrzeuge.
 * @param[in] cfg Simulationskonfiguration.
 * @param[in,out] stats Statistikstruktur.
 * @param[in] current_time Aktueller Zeitschritt.
 * @param[in,out] next_vehicle_id Laufende Fahrzeug-ID.
 * @return SIM_OK bei direktem Einparken, SIM_KFZ_WARTEN bei erfolgreichem
 *         Einreihen in die Warteschlange, SIM_ERR_INPUT bei Fehlern.
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

    Vehicle v;
    int slot;

    v.id = *next_vehicle_id;
    v.restparkdauer = rng_int(1, cfg->max_parkdauer);
    v.ankunftszeit = current_time;

    slot = parking_find_free_slot(p);

    if (slot == -1) {
        bool ok = queue_push(q, v);
        if (!ok) {
            return SIM_ERR_INPUT;
        }

        (*next_vehicle_id)++;
        stats->neu_angekommen++;
        stats->sum_parkdauer += (size_t)v.restparkdauer;
        stats->count_parkdauer++;

        return SIM_KFZ_WARTEN;
    }

    p->slots[slot].fahrzeug = v;
    p->slots[slot].belegt = true;
    p->belegte_plaetze++;

    (*next_vehicle_id)++;
    stats->neu_angekommen++;
    stats->sum_parkdauer += (size_t)v.restparkdauer;
    stats->count_parkdauer++;

    return SIM_OK;
}

/**
 * @brief Verarbeitet Abfahrten im Parkhaus.
 *
 * Reduziert bei allen belegten Stellplätzen die Restparkdauer um einen
 * Zeitschritt. Fahrzeuge mit Restparkdauer <= 0 verlassen das Parkhaus
 * und der Stellplatz wird wieder freigegeben.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] stats Statistikstruktur; verlassen wird pro Abfahrt erhöht.
 */
void parking_process_departures(ParkingLot* p, Stats* stats)
{
    if (p == NULL || stats == NULL) {
        return;
    }

    for (size_t i = 0U; i < p->kapazitaet; i++) {
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
 * @brief Arbeitet die Warteschlange ab, solange freie Stellplätze vorhanden sind.
 *
 * Entnimmt Fahrzeuge in FIFO-Reihenfolge aus der Warteschlange und parkt
 * sie auf freien Stellplätzen ein. Für jedes erfolgreich eingeparkte
 * Fahrzeug wird die Wartezeit als Differenz aus aktuellem Zeitschritt
 * und ursprünglicher Ankunftszeit erfasst.
 *
 * @param[in,out] p Parkhausstruktur.
 * @param[in,out] q Warteschlange.
 * @param[in,out] stats Statistikstruktur.
 * @param[in] current_time Aktueller Zeitschritt.
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

        int wartezeit = current_time - v.ankunftszeit;

        stats->sum_wartezeit += (size_t)wartezeit;
        stats->count_wartezeit++;

        p->slots[slot].fahrzeug = v;
        p->slots[slot].belegt = true;
        p->belegte_plaetze++;

        stats->abgefertigte_wartende++;
    }
}
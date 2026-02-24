#ifndef STATS_H
#define STATS_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"

/* =========================
   Statistiken
   ========================= */

/**
 * @brief Initialisiert alle Statistikwerte.
 */
void stats_init(Stats* s);
/*
 * PSEUDOCODE:
 * - set all counters to 0
 */

/**
 * @brief Setzt zeitschrittbezogene Zähler zurück (falls ihr Step-Counter getrennt führt).
 */
void stats_reset_step(Stats* s);
/*
 * PSEUDOCODE:
 * - s->neu_angekommen = 0
 * - s->verlassen = 0
 * - s->abgefertigte_wartende = 0
 */

/**
 * @brief Aktualisiert Werte, die aus dem Systemzustand berechnet werden.
 *        (Belegung, Queue-Länge, Ø Restparkdauer, Belegungsänderung)
 */
void stats_update_step(
    Stats* s,
    const ParkingLot* p,
    const Queue* q,
    int step
);
/*
 * PSEUDOCODE:
 * - s->belegung = p->belegte_plaetze
 * - s->warteschlangenlaenge = queue_size(q)
 * - compute avg_restparkdauer:
 *     sum = 0; count = 0
 *     for each slot:
 *         if belegt: sum += restparkdauer; count++
 *     if count>0: avg = sum/(double)count else avg = -1
 * - compute belegungsaenderung:
 *     delta = belegung - belegung_prev
 *     belegung_prev = belegung
 */

/**
 * @brief Gibt Statistiken für einen Zeitschritt auf der Konsole aus.
 */
void stats_print_step(const Stats* s, int step);
/*
 * PSEUDOCODE:
 * - print formatted lines like in example output
 */

/**
 * @brief Berechnet und gibt Endstatistiken aus.
 */
void stats_print_final(const Stats* s);
/*
 * PSEUDOCODE:
 * - compute averages/max values accumulated over all steps
 * - print formatted summary
 */

#endif // STATS_H
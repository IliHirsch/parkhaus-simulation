#ifndef STATS_H
#define STATS_H

#include <stddef.h>
#include "types.h"
#include "queue.h"

/**
 * @brief Initialisiert alle Statistikfelder mit 0.
 *
 * @param[out] p_stats Stats-Struktur, die initialisiert werden soll.
 */
void stats_init(Stats* p_stats);

/**
 * @brief Setzt die Step-Zähler für den aktuellen Zeitschritt zurück.
 *
 * Reset betrifft nur Step-Werte (neu_angekommen, verlassen, abgefertigte_wartende).
 *
 * @param[in,out] p_stats Stats-Struktur.
 */
void stats_reset_step(Stats* p_stats);

/**
 * @brief Aktualisiert Momentanwerte und Aggregate nach einem Simulation-Step.
 *
 * Setzt belegung und warteschlangenlaenge anhand des aktuellen Zustands und führt Summen/Maxima fort.
 *
 * @param[in,out] s Stats-Struktur.
 * @param[in] p Aktueller Parkhauszustand.
 * @param[in] q Aktueller Queue-Zustand.
 * @param[in] step Aktueller Zeitschritt (für mögliche Erweiterungen/Debug).
 */
void stats_update_step(Stats* s, const ParkingLot* p, const Queue* q, int step);

/**
 * @brief Gibt eine Zeile Step-Statistik auf der Konsole aus.
 *
 * Mindestens: belegung, warteschlangenlaenge, neu_angekommen, verlassen, abgefertigte_wartende.
 *
 * @param[in] s Stats-Struktur (nach stats_update_step).
 * @param[in] step Aktueller Zeitschritt.
 */
void stats_print_step(const Stats* s, int step);

/**
 * @brief Gibt die Abschlussstatistiken der Simulation aus.
 *
 * Berechnet Durchschnittswerte/Maxima und ggf. Wartezeiten/Parkdauern.
 *
 * @param[in] s Stats-Struktur nach Ende der Simulation.
 */
void stats_print_final(const Stats* s);

#endif /* STATS_H */
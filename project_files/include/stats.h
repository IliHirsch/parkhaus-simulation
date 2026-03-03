#ifndef STATS_H
#define STATS_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"
#include "queue.h"

/* =========================
   Statistiken
   ========================= */

void stats_init(Stats* s);
/*
 * FUNCTION stats_init(s)
 * INPUT  s
 * OUTPUT alle Stats-Felder auf 0 gesetzt
 *
 * s->neu_angekommen <- 0
 * s->verlassen <- 0
 * s->abgefertigte_wartende <- 0
 *
 * s->belegung <- 0
 * s->warteschlangenlaenge <- 0
 *
 * s->step_count <- 0
 * s->sum_belegung <- 0
 * s->sum_warteschlange <- 0
 * s->max_warteschlange <- 0
 * s->vollauslastung_steps <- 0
 *
 * s->sum_restparkdauer <- 0
 * s->count_restparkdauer <- 0
 *
 * s->sum_wartezeit <- 0
 * s->count_wartezeit <- 0
 *
 * s->sum_parkdauer <- 0
 * s->count_parkdauer <- 0
 *
 * END FUNCTION
 */

void stats_reset_step(Stats* s);
/*
 * FUNCTION stats_reset_step(s)
 * INPUT  s
 * OUTPUT Step-Werte auf 0 gesetzt (pro Zeitschritt)
 *
 * s->neu_angekommen <- 0
 * s->verlassen <- 0
 * s->abgefertigte_wartende <- 0
 *
 * END FUNCTION
 */

void stats_update_step(Stats* s, const ParkingLot* p, const Queue* q, int step);
/*
 * FUNCTION stats_update_step(s, p, q, step)
 * INPUT  s, p, q, step
 * OUTPUT Momentanwerte gesetzt + Aggregate fortgeschrieben
 *
 * s->belegung <- p->belegte_plaetze
 * s->warteschlangenlaenge <- CALL queue_size(q)
 *
 * s->step_count <- s->step_count + 1
 * s->sum_belegung <- s->sum_belegung + s->belegung
 * s->sum_warteschlange <- s->sum_warteschlange + s->warteschlangenlaenge
 *
 * IF s->warteschlangenlaenge > s->max_warteschlange THEN
 *     s->max_warteschlange <- s->warteschlangenlaenge
 * END IF
 *
 * IF s->belegung == p->kapazitaet THEN
 *     s->vollauslastung_steps <- s->vollauslastung_steps + 1
 * END IF
 *
 * FOR i <- 0 TO (p->kapazitaet - 1) DO
 *     IF p->slots[i].belegt == true THEN
 *         s->sum_restparkdauer <- s->sum_restparkdauer + p->slots[i].fahrzeug.restparkdauer
 *         s->count_restparkdauer <- s->count_restparkdauer + 1
 *     END IF
 * END FOR
 *
 * END FUNCTION
 */

void stats_print_step(const Stats* s, int step);
/*
 * FUNCTION stats_print_step(s, step)
 * INPUT  s, step
 * OUTPUT Konsolen-Ausgabe für diesen Step (mind. 5 Werte)
 *
 * OUTPUT "Step " step ": "
 * OUTPUT "Belegung=" s->belegung ", Queue=" s->warteschlangenlaenge
 * OUTPUT ", Neu=" s->neu_angekommen ", Verlassen=" s->verlassen
 * OUTPUT ", Queue->Park=" s->abgefertigte_wartende
 *
 * IF s->count_restparkdauer > 0 THEN
 *     avg_rest <- s->sum_restparkdauer / s->count_restparkdauer
 *     OUTPUT ", AvgRest=" avg_rest
 * END IF
 *
 * OUTPUT newline
 *
 * END FUNCTION
 */

void stats_print_final(const Stats* s);
/*
 * FUNCTION stats_print_final(s)
 * INPUT  s
 * OUTPUT Abschlussausgabe (Durchschnitte/Maxima)
 *
 * OUTPUT "===== FINAL STATS ====="
 *
 * IF s->step_count == 0 THEN
 *     OUTPUT "Keine Schritte simuliert."
 *     RETURN
 * END IF
 *
 * avg_belegung <- s->sum_belegung / s->step_count
 * avg_queue <- s->sum_warteschlange / s->step_count
 * vollauslastung_prozent <- (s->vollauslastung_steps * 100) / s->step_count
 *
 * OUTPUT "Ø Belegung: " avg_belegung
 * OUTPUT "Ø Warteschlange: " avg_queue
 * OUTPUT "Max Warteschlange: " s->max_warteschlange
 * OUTPUT "Vollauslastung: " vollauslastung_prozent "% der Schritte"
 *
 * IF s->count_wartezeit > 0 THEN
 *     avg_wartezeit <- s->sum_wartezeit / s->count_wartezeit
 *     OUTPUT "Ø Wartezeit (Queue->Park): " avg_wartezeit
 * ELSE
 *     OUTPUT "Ø Wartezeit: 0 Samples"
 * END IF
 *
 * IF s->count_parkdauer > 0 THEN
 *     avg_parkdauer <- s->sum_parkdauer / s->count_parkdauer
 *     OUTPUT "Ø Parkdauer: " avg_parkdauer
 * ELSE
 *     OUTPUT "Ø Parkdauer: 0 Samples"
 * END IF
 *
 * END FUNCTION
 */

#endif // STATS_H
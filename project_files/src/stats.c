#include "stats.h"
#include <stdio.h>

void stats_init(Stats* s)
{
    /*
     * FUNCTION stats_init(s)
     * INPUT  s
     * OUTPUT alle Felder auf 0 gesetzt
     *
     * // Step-Werte
     * s->neu_angekommen <- 0
     * s->verlassen <- 0
     * s->abgefertigte_wartende <- 0
     *
     * // Momentanwerte
     * s->belegung <- 0
     * s->warteschlangenlaenge <- 0
     *
     * // Aggregate über alle Steps
     * s->step_count <- 0
     * s->sum_belegung <- 0
     * s->sum_warteschlange <- 0
     * s->max_warteschlange <- 0
     * s->vollauslastung_steps <- 0
     *
     * // Samples
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
}

void stats_reset_step(Stats* s)
{
    /*
     * FUNCTION stats_reset_step(s)
     * INPUT  s
     * OUTPUT Step-Zähler für diesen Zeitschritt zurückgesetzt
     *
     * s->neu_angekommen <- 0
     * s->verlassen <- 0
     * s->abgefertigte_wartende <- 0
     *
     * // belegung & warteschlangenlaenge werden später in stats_update_step gesetzt
     *
     * END FUNCTION
     */
}

void stats_update_step(Stats* s, const ParkingLot* p, const Queue* q, int step)
{
    /*
     * FUNCTION stats_update_step(s, p, q, step)
     * INPUT  s, p, q, step
     * OUTPUT Momentanwerte gesetzt + Aggregate aktualisiert
     *
     * DECLARE i : size_t
     *
     * // Momentanwerte nach dem Step
     * s->belegung <- p->belegte_plaetze
     * s->warteschlangenlaenge <- CALL queue_size(q)
     *
     * // Aggregate: Zeit fortschreiben
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
     * // Restparkdauer-Samples (über alle belegten Plätze)
     * FOR i <- 0 TO (p->kapazitaet - 1) DO
     *     IF p->slots[i].belegt == true THEN
     *         s->sum_restparkdauer <- s->sum_restparkdauer + p->slots[i].fahrzeug.restparkdauer
     *         s->count_restparkdauer <- s->count_restparkdauer + 1
     *     END IF
     * END FOR
     *
     * END FUNCTION
     */
}

void stats_print_step(const Stats* s, int step)
{
    /*
     * FUNCTION stats_print_step(s, step)
     * INPUT  s, step
     * OUTPUT Konsolen-Ausgabe für diesen Zeitschritt (mind. 5 Werte)
     *
     * DECLARE avg_rest : size_t
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
}

void stats_print_final(const Stats* s)
{
    /*
     * FUNCTION stats_print_final(s)
     * INPUT  s
     * OUTPUT Abschlussausgabe (Durchschnitte/Maxima)
     *
     * DECLARE avg_belegung : size_t
     * DECLARE avg_queue : size_t
     * DECLARE vollauslastung_prozent : size_t
     * DECLARE avg_warte : size_t
     * DECLARE avg_park : size_t
     * DECLARE avg_rest : size_t
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
     *     avg_warte <- s->sum_wartezeit / s->count_wartezeit
     *     OUTPUT "Ø Wartezeit (Queue->Park): " avg_warte
     * ELSE
     *     OUTPUT "Ø Wartezeit: 0 Samples"
     * END IF
     *
     * IF s->count_parkdauer > 0 THEN
     *     avg_park <- s->sum_parkdauer / s->count_parkdauer
     *     OUTPUT "Ø Parkdauer: " avg_park
     * ELSE
     *     OUTPUT "Ø Parkdauer: 0 Samples"
     * END IF
     *
     * IF s->count_restparkdauer > 0 THEN
     *     avg_rest <- s->sum_restparkdauer / s->count_restparkdauer
     *     OUTPUT "Ø Restparkdauer (Samples): " avg_rest
     * END IF
     *
     * END FUNCTION
     */
}
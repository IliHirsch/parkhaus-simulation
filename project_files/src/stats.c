#include "stats.h"
#include <stdio.h>

// Initialisiert alle Statistikfelder mit 0
void stats_init(Stats* p_stats)
{
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

    if (p_stats == NULL){
        return;
    }

    p_stats->neu_angekommen = 0;
    p_stats->verlassen = 0;
    p_stats->abgefertigte_wartende = 0;

    p_stats->belegung = 0;
    p_stats->warteschlangenlaenge = 0;

    p_stats->step_count = 0;
    p_stats->sum_belegung = 0;
    p_stats->sum_warteschlange = 0;
    p_stats->max_warteschlange = 0;
    p_stats->vollauslastung_steps = 0;

    p_stats->sum_restparkdauer = 0;
    p_stats->count_restparkdauer = 0;

    p_stats->sum_wartezeit = 0;
    p_stats->count_wartezeit = 0;

    p_stats->sum_parkdauer = 0;
    p_stats->count_parkdauer = 0;
}

// Setzt die Zähler für jeden Step auf 0
void stats_reset_step(Stats* p_stats)
{
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

    if (p_stats == NULL){
        return;
    }

    p_stats->neu_angekommen = 0;
    p_stats->verlassen = 0;
    p_stats->abgefertigte_wartende = 0;
}

// Aktualisiert die Statsitiken für jeden Step
void stats_update_step(Stats* p_stats, const ParkingLot* p_parking, const Queue* p_queue, int step)
{
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

    if ((p_stats == NULL) || (p_parking == NULL) || (p_queue == NULL)){
        return;
    }

    p_stats->belegung = p_parking->belegte_plaetze;
    p_stats->warteschlangenlaenge = queue_size(p_queue);

    p_stats->step_count = p_stats->step_count + 1;

    p_stats->sum_belegung = p_stats->sum_belegung + p_stats->belegung;

    p_stats->sum_warteschlange = p_stats->sum_warteschlange + p_stats->warteschlangenlaenge;

    if (p_stats->warteschlangenlaenge > p_stats->max_warteschlange){
        p_stats->max_warteschlange = p_stats->warteschlangenlaenge;
    }

    if (p_stats->belegung == p_parking->kapazitaet){
        p_stats->vollauslastung_steps = p_stats->vollauslastung_steps + 1;
    }

    for (size_t i = 0; i < p_parking->kapazitaet; i++){
        if (p_parking->slots[i].belegt == true){
            p_stats->sum_restparkdauer = p_stats->sum_restparkdauer + p_parking->slots[i].fahrzeug.restparkdauer;
            p_stats->count_restparkdauer = p_stats->count_restparkdauer + 1;
        }
    }
}

// Gibt die Statistiken für einen Step in der Konsole aus
void stats_print_step(const Stats* p_stats, int step)
{
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

    if (p_stats == NULL){
        return;
    }

    printf("Step %d: ", step);

    printf("Belegung=%zu, ", p_stats->belegung);
    printf("Queue=%zu, ", p_stats->warteschlangenlaenge);

    printf("Neu=%zu, ", p_stats->neu_angekommen);
    printf("Verlassen=%zu, ", p_stats->verlassen);

    printf("Queue->Park=%zu", p_stats->abgefertigte_wartende);

    if (p_stats->count_restparkdauer > 0){
        float avg_rest = (float)p_stats->sum_restparkdauer / (float)p_stats->count_restparkdauer;
        printf(", AvgRest=%.2f", avg_rest);
    }

    printf("\n");
}

// Gibt die Statistiken am Ende der Simulation in der Konsole aus
void stats_print_final(const Stats* p_stats)
{
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

    if (p_stats == NULL){
        return;
    }

    printf("\n===== FINAL STATS =====\n");

    if (p_stats->step_count == 0){
        printf("Keine Schritte simuliert.\n");
        return;
    }

    float avg_belegung = (float)p_stats->sum_belegung / (float)p_stats->step_count;
    float avg_queue = (float)p_stats->sum_warteschlange / (float)p_stats->step_count;
    float vollauslastung_prozent = ((float)p_stats->vollauslastung_steps * 100.0f) / (float)p_stats->step_count;

    printf("Ø Belegung: %.2f\n", avg_belegung);
    printf("Ø Warteschlange: %.2f\n", avg_queue);
    printf("Max Warteschlange: %zu\n", p_stats->max_warteschlange);
    printf("Vollauslastung: %.2f %% der Schritte\n", vollauslastung_prozent);

    if (p_stats->count_wartezeit > 0){
        float avg_wartezeit = (float)p_stats->sum_wartezeit / (float)p_stats->count_wartezeit;
        printf("Ø Wartezeit (Queue->Park): %.2f\n", avg_wartezeit);
    }
    else{
        printf("Ø Wartezeit: 0 Samples\n");
    }

    if (p_stats->count_parkdauer > 0){
        float avg_parkdauer = (float)p_stats->sum_parkdauer / (float)p_stats->count_parkdauer;
        printf("Ø Parkdauer: %.2f\n", avg_parkdauer);
    }
    else{
        printf("Ø Parkdauer: 0 Samples\n");
    }
}
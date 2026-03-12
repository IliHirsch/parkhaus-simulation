#include "stats.h"
#include <stdio.h>

// Initialisiert alle Statistikfelder mit 0
void stats_init(Stats* p_stats){

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
void stats_reset_step(Stats* p_stats){
    if (p_stats == NULL){
        return;
    }

    p_stats->neu_angekommen = 0;
    p_stats->verlassen = 0;
    p_stats->abgefertigte_wartende = 0;
}

// Aktualisiert die Statsitiken für jeden Step
void stats_update_step(Stats* p_stats, const ParkingLot* p_parking, const Queue* p_queue, int step){
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
void stats_print_step(const Stats* p_stats, int step){

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
void stats_print_final(const Stats* p_stats){
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
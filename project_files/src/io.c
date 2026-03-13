#include "io.h"
#include <stdio.h>
#include <stdbool.h>
#include "types.h"

static FILE* p_log_file = NULL;

bool io_open_log(const char* path){

    p_log_file = fopen(path, "w");

    if (p_log_file == NULL){
        return false;
    }

    fprintf(p_log_file, "=== Parkhaus-Simulation Log ===\n");
    fprintf(p_log_file, "Format: Step | neu | verlassen | queue->park | belegung | queue\n");

    return true;
}

void io_close_log(void){

    if (p_log_file != NULL){
        fclose(p_log_file);
        p_log_file = NULL;
    }
}

void io_log_step(const Stats* p_stats, int step){

    size_t avg_rest = 0;

    if (p_log_file == NULL){
        return;
    }

    if (p_stats == NULL){
        return;
    }

    fprintf(
        p_log_file,
        "Step %d | neu=%zu | verlassen=%zu | queue->park=%zu | belegung=%zu | queue=%zu\n",
        step,
        p_stats->neu_angekommen,
        p_stats->verlassen,
        p_stats->abgefertigte_wartende,
        p_stats->belegung,
        p_stats->warteschlangenlaenge
    );

    if (p_stats->count_restparkdauer > 0){
        avg_rest = p_stats->sum_restparkdauer / p_stats->count_restparkdauer;
        fprintf(p_log_file, "    AvgRest=%zu\n", avg_rest);
    }
}

void io_log_final(const Stats* p_stats){

    size_t avg_belegung = 0;
    size_t avg_queue = 0;
    size_t vollauslastung_prozent = 0;
    size_t avg_warte = 0;
    size_t avg_park = 0;
    size_t avg_rest = 0;

    if (p_log_file == NULL){
        return;
    }

    if (p_stats == NULL){
        return;
    }

    fprintf(p_log_file, "===== FINAL STATS =====\n");

    if (p_stats->step_count == 0){
        fprintf(p_log_file, "Keine Schritte simuliert.\n");
        return;
    }

    avg_belegung = p_stats->sum_belegung / p_stats->step_count;
    avg_queue = p_stats->sum_warteschlange / p_stats->step_count;

    vollauslastung_prozent = (p_stats->vollauslastung_steps * 100) / p_stats->step_count;

    fprintf(p_log_file, "Ø Belegung: %zu\n", avg_belegung);
    fprintf(p_log_file, "Ø Warteschlange: %zu\n", avg_queue);
    fprintf(p_log_file, "Max Warteschlange: %zu\n", p_stats->max_warteschlange);
    fprintf(p_log_file, "Vollauslastung: %zu%% der Schritte\n", vollauslastung_prozent);

    if (p_stats->count_wartezeit > 0){
        avg_warte = p_stats->sum_wartezeit / p_stats->count_wartezeit;
        fprintf(p_log_file, "Ø Wartezeit (Queue->Park): %zu\n", avg_warte);
    }
    else{
        fprintf(p_log_file, "Ø Wartezeit: 0 Samples\n");
    }

    if (p_stats->count_parkdauer > 0){
        avg_park = p_stats->sum_parkdauer / p_stats->count_parkdauer;
        fprintf(p_log_file, "Ø Parkdauer: %zu\n", avg_park);
    }
    else{
        fprintf(p_log_file, "Ø Parkdauer: 0 Samples\n");
    }

    if (p_stats->count_restparkdauer > 0){
        avg_rest = p_stats->sum_restparkdauer / p_stats->count_restparkdauer;
        fprintf(p_log_file, "Ø Restparkdauer (Samples): %zu\n", avg_rest);
    }
}
#include "../include/io.h"
#include <stdio.h>

static FILE* p_log_file = NULL;

/**
 * @brief Öffnet die Logdatei für die Simulation.
 *
 * @param[in] path Pfad zur Logdatei.
 * @return true wenn Datei erfolgreich geöffnet wurde, sonst false.
 */
bool io_open_log(const char* path)
{
    if (path == NULL) {
        return false;
    }

    p_log_file = fopen(path, "w");

    if (p_log_file == NULL) {
        return false;
    }

    fprintf(p_log_file, "=== Parkhaus-Simulation Log ===\n");
    fprintf(p_log_file, "Format: Step | neu | verlassen | queue->park | belegung | queue\n");

    return true;
}

/**
 * @brief Schließt die Logdatei.
 */
void io_close_log(void)
{
    if (p_log_file != NULL) {
        fclose(p_log_file);
        p_log_file = NULL;
    }
}

/**
 * @brief Loggt einen einzelnen Simulationsschritt.
 *
 * @param[in] p_stats Statistikdaten.
 * @param[in] step Aktueller Simulationsschritt.
 */
void io_log_step(const Stats* p_stats, int step)
{
    if (p_log_file == NULL || p_stats == NULL) {
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

    if (p_stats->count_restparkdauer > 0U) {
    float avg_rest =
        (float)p_stats->sum_restparkdauer / (float)p_stats->count_restparkdauer;

    fprintf(p_log_file, "    AvgRestGesamt=%.2f\n", avg_rest);
    } else {
        fprintf(p_log_file, "    AvgRestGesamt=0.00\n");
    }
}

/**
 * @brief Loggt die finale Statistik der Simulation.
 *
 * @param[in] p_stats Statistikdaten.
 */
void io_log_final(const Stats* p_stats)
{
    if (p_log_file == NULL || p_stats == NULL) {
        return;
    }

    fprintf(p_log_file, "===== FINAL STATS =====\n");

    if (p_stats->step_count == 0U) {
        fprintf(p_log_file, "Keine Schritte simuliert.\n");
        return;
    }

    float avg_belegung =
        (float)p_stats->sum_belegung / (float)p_stats->step_count;

    float avg_queue =
        (float)p_stats->sum_warteschlange / (float)p_stats->step_count;

    float vollauslastung_prozent =
        ((float)p_stats->vollauslastung_steps * 100.0f) / (float)p_stats->step_count;

    fprintf(p_log_file, "Ø Belegung: %.2f\n", avg_belegung);
    fprintf(p_log_file, "Ø Warteschlange: %.2f\n", avg_queue);
    fprintf(p_log_file, "Max Warteschlange: %zu\n", p_stats->max_warteschlange);
    fprintf(p_log_file, "Vollauslastung: %.2f %% der Schritte\n", vollauslastung_prozent);

    if (p_stats->count_wartezeit > 0U) {
        float avg_warte =
            (float)p_stats->sum_wartezeit / (float)p_stats->count_wartezeit;

        fprintf(p_log_file, "Ø Wartezeit (Queue->Park): %.2f\n", avg_warte);
    } else {
        fprintf(p_log_file, "Ø Wartezeit: 0 Samples\n");
    }

    if (p_stats->count_parkdauer > 0U) {
        float avg_park =
            (float)p_stats->sum_parkdauer / (float)p_stats->count_parkdauer;

        fprintf(p_log_file, "Ø Parkdauer: %.2f\n", avg_park);
    } else {
        fprintf(p_log_file, "Ø Parkdauer: 0 Samples\n");
    }

    if (p_stats->count_restparkdauer > 0U) {
        float avg_rest =
            (float)p_stats->sum_restparkdauer / (float)p_stats->count_restparkdauer;

        fprintf(p_log_file, "Ø Restparkdauer (Samples): %.2f\n", avg_rest);
    } else {
        fprintf(p_log_file, "Ø Restparkdauer: 0 Samples\n");
    }
}
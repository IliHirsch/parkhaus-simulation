#include "io.h"
#include <stdio.h>
#include <stdbool.h>

static FILE* p_log_file = NULL;

bool io_open_log(const char* path)
{
    /*
     * FUNCTION io_open_log(path) RETURNS ok
     * INPUT  path
     * OUTPUT Log-Datei geöffnet und intern gemerkt; true/false
     *
     * file <- CALL fopen(path, "w")
     * IF file == NULL THEN RETURN false END IF
     *
     * // intern: globales Handle setzen (z.B. g_log <- file)
     *
     * WRITE to log:
     *   "=== Parkhaus-Simulation Log ===\n"
     *   "Format: Step | neu | verlassen | queue->park | belegung | queue\n"
     *
     * RETURN true
     *
     * END FUNCTION
     */

    p_log_file = fopen(path, "w");

    if (p_log_file == NULL){
        return false;
    }

    fprintf(p_log_file, "=== Parkhaus-Simulation Log ===\n");
    fprintf(p_log_file, "Format: Step | neu | verlassen | queue->park | belegung | queue\n");

    return true;
}

void io_close_log(void)
{
    /*
     * FUNCTION io_close_log()
     * IF log-handle exists THEN
     *     CALL fclose(log-handle)
     *     set log-handle to NULL
     * END IF
     * END FUNCTION
     */
}

void io_log_step(const Stats* s, int step)
{
    /*
     * FUNCTION io_log_step(s, step)
     * IF log-handle is NULL THEN RETURN END IF
     *
     * WRITE to log:
     *   "Step %d | neu=%zu | verlassen=%zu | queue->park=%zu | belegung=%zu | queue=%zu\n",
     *   step, s->neu_angekommen, s->verlassen, s->abgefertigte_wartende, s->belegung, s->warteschlangenlaenge
     *
     * IF s->count_restparkdauer > 0 THEN
     *     avg_rest <- s->sum_restparkdauer / s->count_restparkdauer
     *     WRITE to log: "    AvgRest=%zu\n", avg_rest
     * END IF
     *
     * END FUNCTION
     */
}

void io_log_final(const Stats* s)
{
    /*
     * FUNCTION io_log_final(s)
     * IF log-handle is NULL THEN RETURN END IF
     *
     * WRITE to log: "===== FINAL STATS =====\n"
     *
     * IF s->step_count == 0 THEN
     *     WRITE to log: "Keine Schritte simuliert.\n"
     *     RETURN
     * END IF
     *
     * avg_belegung <- s->sum_belegung / s->step_count
     * avg_queue <- s->sum_warteschlange / s->step_count
     * vollauslastung_prozent <- (s->vollauslastung_steps * 100) / s->step_count
     *
     * WRITE to log: "Ø Belegung: %zu\n", avg_belegung
     * WRITE to log: "Ø Warteschlange: %zu\n", avg_queue
     * WRITE to log: "Max Warteschlange: %zu\n", s->max_warteschlange
     * WRITE to log: "Vollauslastung: %zu%% der Schritte\n", vollauslastung_prozent
     *
     * IF s->count_wartezeit > 0 THEN
     *     avg_warte <- s->sum_wartezeit / s->count_wartezeit
     *     WRITE to log: "Ø Wartezeit (Queue->Park): %zu\n", avg_warte
     * ELSE
     *     WRITE to log: "Ø Wartezeit: 0 Samples\n"
     * END IF
     *
     * IF s->count_parkdauer > 0 THEN
     *     avg_park <- s->sum_parkdauer / s->count_parkdauer
     *     WRITE to log: "Ø Parkdauer: %zu\n", avg_park
     * ELSE
     *     WRITE to log: "Ø Parkdauer: 0 Samples\n"
     * END IF
     *
     * IF s->count_restparkdauer > 0 THEN
     *     avg_rest <- s->sum_restparkdauer / s->count_restparkdauer
     *     WRITE to log: "Ø Restparkdauer (Samples): %zu\n", avg_rest
     * END IF
     *
     * END FUNCTION
     */
}
#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"

bool io_open_log(const char* path);
/*
 * FUNCTION io_open_log(path) RETURNS ok
 * INPUT  path
 * OUTPUT Log-Handle global gespeichert, true/false
 *
 * file <- CALL fopen(path, "w")
 * IF file == NULL THEN RETURN false END IF
 *
 * g_log <- file
 *
 * WRITE to g_log: "=== Parkhaus-Simulation Log ===\n"
 * WRITE to g_log: "Format: Step | neu | verlassen | queue->park | belegung | queue\n"
 *
 * RETURN true
 *
 * END FUNCTION
 */

void io_close_log(void);
/*
 * FUNCTION io_close_log()
 * IF g_log != NULL THEN
 *     CALL fclose(g_log)
 *     g_log <- NULL
 * END IF
 * END FUNCTION
 */

void io_log_step(const Stats* s, int step);
/*
 * FUNCTION io_log_step(s, step)
 * IF g_log == NULL THEN RETURN END IF
 *
 * WRITE to g_log:
 *   "Step %d | neu=%zu | verlassen=%zu | queue->park=%zu | belegung=%zu | queue=%zu\n",
 *   step, s->neu_angekommen, s->verlassen, s->abgefertigte_wartende, s->belegung, s->warteschlangenlaenge
 *
 * IF s->count_restparkdauer > 0 THEN
 *     avg_rest <- s->sum_restparkdauer / s->count_restparkdauer
 *     WRITE to g_log: "    AvgRest=%zu\n", avg_rest
 * END IF
 *
 * END FUNCTION
 */

void io_log_final(const Stats* s);
/*
 * FUNCTION io_log_final(s)
 * IF g_log == NULL THEN RETURN END IF
 *
 * WRITE to g_log: "===== FINAL STATS =====\n"
 *
 * IF s->step_count == 0 THEN
 *     WRITE to g_log: "Keine Schritte simuliert.\n"
 *     RETURN
 * END IF
 *
 * avg_belegung <- s->sum_belegung / s->step_count
 * avg_queue <- s->sum_warteschlange / s->step_count
 * vollauslastung_prozent <- (s->vollauslastung_steps * 100) / s->step_count
 *
 * WRITE to g_log: "Ø Belegung: %zu\n", avg_belegung
 * WRITE to g_log: "Ø Warteschlange: %zu\n", avg_queue
 * WRITE to g_log: "Max Warteschlange: %zu\n", s->max_warteschlange
 * WRITE to g_log: "Vollauslastung: %zu%% der Schritte\n", vollauslastung_prozent
 *
 * IF s->count_wartezeit > 0 THEN
 *     avg_warte <- s->sum_wartezeit / s->count_wartezeit
 *     WRITE to g_log: "Ø Wartezeit (Queue->Park): %zu\n", avg_warte
 * ELSE
 *     WRITE to g_log: "Ø Wartezeit: 0 Samples\n"
 * END IF
 *
 * IF s->count_parkdauer > 0 THEN
 *     avg_park <- s->sum_parkdauer / s->count_parkdauer
 *     WRITE to g_log: "Ø Parkdauer: %zu\n", avg_park
 * ELSE
 *     WRITE to g_log: "Ø Parkdauer: 0 Samples\n"
 * END IF
 *
 * IF s->count_restparkdauer > 0 THEN
 *     avg_rest <- s->sum_restparkdauer / s->count_restparkdauer
 *     WRITE to g_log: "Ø Restparkdauer (Samples): %zu\n", avg_rest
 * END IF
 *
 * END FUNCTION
 */

#endif // IO_H
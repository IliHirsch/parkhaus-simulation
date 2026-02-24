#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"
#include "stats.h"

/* =========================
   I/O (Konsole + Logfile)
   ========================= */

/**
 * @brief Öffnet die Log-Datei zum Schreiben (überschreibt vorhandene Datei).
 *
 * @param[in] path Pfad zur Datei (z.B. "project_files/data/log.txt").
 * @return true wenn erfolgreich, sonst false.
 */
bool io_open_log(const char* path);
/*
 * PSEUDOCODE:
 * - file = fopen(path, "w")
 * - if file == NULL: return false
 * - store file handle (global oder Kontext)
 * - return true
 */

/**
 * @brief Schließt die Log-Datei, falls geöffnet.
 */
void io_close_log(void);
/*
 * PSEUDOCODE:
 * - if file != NULL: fclose(file); file = NULL
 */

/**
 * @brief Schreibt Zeitschritt-Statistiken in die Log-Datei.
 *
 * @param[in] s Statistikdaten.
 * @param[in] step Zeitschritt.
 */
void io_log_step(const Stats* s, int step);
/*
 * PSEUDOCODE:
 * - if file == NULL: return
 * - fprintf in einem klaren, reproduzierbaren Format
 */

/**
 * @brief Schreibt Endstatistiken in die Log-Datei.
 *
 * @param[in] s Statistikdaten.
 */
void io_log_final(const Stats* s);
/*
 * PSEUDOCODE:
 * - if file == NULL: return
 * - fprintf final summary
 */

#endif // IO_H
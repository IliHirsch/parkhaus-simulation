#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include "types.h"

/**
 * @brief Öffnet eine Log-Datei zum Schreiben (überschreibt vorhandene Datei).
 *
 * @param[in] path Pfad zur Log-Datei.
 * @return true wenn Datei geöffnet werden konnte, sonst false.
 */
bool io_open_log(const char* path);

/**
 * @brief Schließt die Log-Datei, falls geöffnet.
 */
void io_close_log(void);

/**
 * @brief Schreibt die Step-Daten in die Log-Datei (falls geöffnet).
 *
 * @param[in] p_stats Aktueller Stats-Zustand (nach stats_update_step).
 * @param[in] step Aktueller Zeitschritt.
 */
void io_log_step(const Stats* p_stats, int step);

/**
 * @brief Schreibt die Abschlussstatistiken in die Log-Datei (falls geöffnet).
 *
 * @param[in] p_stats Finaler Stats-Zustand.
 */
void io_log_final(const Stats* p_stats);

#endif /* IO_H */
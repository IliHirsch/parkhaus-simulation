#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"

/* =========================
   Simulations-Konfiguration
   ========================= */

typedef struct {
    size_t anzahl_stellplaetze;
    int max_parkdauer;
    int sim_dauer_zeitschritte;
    int ankunft_wahrscheinlichkeit_prozent;
    unsigned int seed;
} SimConfig;

/**
 * @brief Liest alle Simulationsparameter über das Terminal ein.
 *
 * @param[out] cfg  Zielstruktur für die Parameter.
 * @return true wenn alle Eingaben erfolgreich gelesen wurden, sonst false.
 */
bool config_read_from_terminal(SimConfig* cfg);
/*
 * PSEUDOCODE:
 * - prompt & read: anzahl_stellplaetze
 * - prompt & read: max_parkdauer
 * - prompt & read: sim_dauer_zeitschritte
 * - prompt & read: ankunft_wahrscheinlichkeit_prozent
 * - prompt & read: seed
 * - if validate(cfg) == false: return false
 * - return true
 */

/**
 * @brief Validiert die Simulationsparameter.
 */
bool config_validate(const SimConfig* cfg);
/*
 * PSEUDOCODE:
 * - check: anzahl_stellplaetze > 0
 * - check: max_parkdauer > 0
 * - check: sim_dauer_zeitschritte > 0
 * - check: 0 <= ankunft_wahrscheinlichkeit_prozent <= 100
 * - return true/false
 */

#endif // CONFIG_H
#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Simulations-Konfiguration (Parameter aus Terminal).
 */
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
 * Erwartet Eingaben für Kapazität, max. Parkdauer, Simulationsdauer, Ankunftswahrscheinlichkeit und Seed.
 * Validiert am Ende die Werte mit config_validate().
 *
 * @param[out] cfg Zielstruktur für die eingelesenen Parameter.
 * @return true wenn alle Eingaben erfolgreich gelesen und validiert wurden, sonst false.
 */
bool config_read_from_terminal(SimConfig* cfg);

/**
 * @brief Validiert die Simulationsparameter.
 *
 * Prüft u.a. >0 Bedingungen und ob die Wahrscheinlichkeit in [0..100] liegt.
 *
 * @param[in] cfg Zeiger auf die zu prüfende Konfiguration.
 * @return true wenn gültig, sonst false.
 */
bool config_validate(const SimConfig* cfg);

#endif /* CONFIG_H */
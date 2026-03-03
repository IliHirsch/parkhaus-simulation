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
/*
 * FUNCTION config_read_from_terminal(cfg) RETURNS ok
 * INPUT  cfg (out)
 * OUTPUT cfg befüllt; true wenn Eingaben + Validierung ok, sonst false
 *
 * OUTPUT "Anzahl Stellplaetze: "
 * READ cfg->anzahl_stellplaetze
 *
 * OUTPUT "Max. Parkdauer (in Zeitschritten): "
 * READ cfg->max_parkdauer
 *
 * OUTPUT "Simulationsdauer (Anzahl Zeitschritte): "
 * READ cfg->sim_dauer_zeitschritte
 *
 * OUTPUT "Ankunftswahrscheinlichkeit pro Zeitschritt (0..100): "
 * READ cfg->ankunft_wahrscheinlichkeit_prozent
 *
 * OUTPUT "Seed (Zufallszahlengenerator): "
 * READ cfg->seed
 *
 * ok <- CALL config_validate(cfg)
 * IF ok == false THEN RETURN false END IF
 *
 * RETURN true
 *
 * END FUNCTION
 */

/**
 * @brief Validiert die Simulationsparameter.
 *
 * Prüft u.a. >0 Bedingungen und ob die Wahrscheinlichkeit in [0..100] liegt.
 *
 * @param[in] cfg Zeiger auf die zu prüfende Konfiguration.
 * @return true wenn gültig, sonst false.
 */
 bool config_validate(const SimConfig* cfg);
/*
 * FUNCTION config_validate(cfg) RETURNS ok
 * INPUT  cfg
 * OUTPUT true wenn gültig, sonst false
 *
 * IF cfg->anzahl_stellplaetze <= 0 THEN RETURN false END IF
 * IF cfg->max_parkdauer <= 0 THEN RETURN false END IF
 * IF cfg->sim_dauer_zeitschritte <= 0 THEN RETURN false END IF
 * IF cfg->ankunft_wahrscheinlichkeit_prozent < 0 THEN RETURN false END IF
 * IF cfg->ankunft_wahrscheinlichkeit_prozent > 100 THEN RETURN false END IF
 *
 * RETURN true
 *
 * END FUNCTION
 */

#endif // CONFIG_H
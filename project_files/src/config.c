#include "config.h"
#include <stdio.h>

/**
 * @brief Liest alle Simulationsparameter über das Terminal ein.
 *
 * Erwartet Eingaben für Kapazität, maximale Parkdauer,
 * Simulationsdauer, Ankunftswahrscheinlichkeit und Seed.
 * Danach werden die Werte mit config_validate() geprüft.
 *
 * @param[out] cfg Zielstruktur für die eingelesenen Parameter.
 * @return true wenn Eingaben und Validierung erfolgreich sind,
 *         sonst false.
 */

bool config_read_from_terminal(SimConfig* cfg)
{

    if (cfg == NULL)
    {
        return false;
    }

    printf("Anzahl Stellplaetze: ");
    if (scanf("%zu", &cfg->anzahl_stellplaetze) != 1)
    {
        return false;
    }

    printf("Max. Parkdauer (in Zeitschritten): ");
    if (scanf("%d", &cfg->max_parkdauer) != 1)
    {
        return false;
    }

    printf("Simulationsdauer (Anzahl Zeitschritte): ");
    if (scanf("%d", &cfg->sim_dauer_zeitschritte) != 1)
    {
        return false;
    }

    printf("Ankunftswahrscheinlichkeit pro Zeitschritt (0..100): ");
    if (scanf("%d", &cfg->ankunft_wahrscheinlichkeit_prozent) != 1)
    {
        return false;
    }

    printf("Seed (Zufallszahlengenerator): ");
    if (scanf("%u", &cfg->seed) != 1)
    {
        return false;
    }

    if (!config_validate(cfg))
    {
        return false;
    }

    return true;
}

/**
 * @brief Prüft die Gültigkeit der Simulationsparameter.
 *
 * @param[in] cfg Zeiger auf die Konfiguration.
 * @return true wenn alle Werte gültig sind, sonst false.
 */

bool config_validate(const SimConfig* cfg)
{
    if (cfg == NULL)
    {
        return false;
    }

    if (cfg->anzahl_stellplaetze == 0)
    {
        return false;
    }

    if (cfg->max_parkdauer <= 0)
    {
        return false;
    }

    if (cfg->sim_dauer_zeitschritte <= 0)
    {
        return false;
    }

    if (cfg->ankunft_wahrscheinlichkeit_prozent < 0 ||
        cfg->ankunft_wahrscheinlichkeit_prozent > 100)
    {
        return false;
    }

    return true;
}
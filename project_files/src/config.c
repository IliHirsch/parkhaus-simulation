#include "config.h"
#include <stdio.h>

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

bool config_validate(const SimConfig* cfg)
{
    /*
     * FUNCTION config_validate(cfg) RETURNS ok
     * INPUT  cfg
     * OUTPUT true wenn gültig, sonst false
     *
     * IF cfg->anzahl_stellplaetze <= 0 THEN RETURN false END IF
     * IF cfg->max_parkdauer <= 0 THEN RETURN false END IF
     * IF cfg->sim_dauer_zeitschritte <= 0 THEN RETURN false END IF
     *
     * IF cfg->ankunft_wahrscheinlichkeit_prozent < 0 THEN RETURN false END IF
     * IF cfg->ankunft_wahrscheinlichkeit_prozent > 100 THEN RETURN false END IF
     *
     * RETURN true
     *
     * END FUNCTION
     */
}
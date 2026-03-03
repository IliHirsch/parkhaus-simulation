#include "config.h"
#include <stdio.h>

bool config_read_from_terminal(SimConfig* cfg)
{
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
     * IF ok == false THEN
     *     RETURN false
     * END IF
     *
     * RETURN true
     *
     * END FUNCTION
     */
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
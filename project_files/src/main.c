#include <stdio.h>
#include <stdbool.h>

#include "config.h"
#include "simulation.h"

/**
 * @brief Startpunkt des Programms.
 *
 * Liest die Simulationskonfiguration vom Terminal ein, prüft die Eingaben
 * und startet bei erfolgreicher Konfiguration die Simulation.
 *
 * @return 0 bei erfolgreicher Ausführung, sonst 1.
 */
int main(void)
{
    SimConfig cfg;
    bool ok = config_read_from_terminal(&cfg);

    if (!ok) {
        printf("Ungueltige Eingabe.\n");
        return 1;
    }

    simulation_run(&cfg);

    return 0;
}
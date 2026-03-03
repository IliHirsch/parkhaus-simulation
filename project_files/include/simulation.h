#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include "parking.h"
#include "queue.h"
#include "stats.h"
#include "rng.h"
#include "io.h"

/**
 * @brief Führt die komplette Simulation über alle Zeitschritte aus.
 *
 * Initialisiert Module (RNG, ParkingLot, Queue, Stats, Log),
 * führt pro Step den Ablauf aus (Departures, Arrival, Queue, Stats, Log)
 * und gibt am Ende die finalen Statistiken aus.
 *
 * @param[in] cfg Simulationskonfiguration.
 */
void simulation_run(const SimConfig* cfg);

/*
 * FUNCTION simulation_run(cfg)
 * INPUT  cfg
 * OUTPUT (Konsole + Log-Datei)
 *
 * // Der konkrete Step-Ablauf ist in simulation.c in simulate_step beschrieben.
 * // (Damit es keine doppelte "Quelle" gibt, steht der Step-Reset dort.)
 *
 * END FUNCTION
 */

#endif // SIMULATION_H
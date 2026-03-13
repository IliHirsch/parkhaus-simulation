#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"

/**
 * @brief Führt die komplette Simulation über alle Zeitschritte aus.
 *
 * Initialisiert Module (RNG, ParkingLot, Queue, Stats, Log),
 * führt pro Step den Ablauf aus (Departures, Queue, Arrival, Stats, Log)
 * und gibt am Ende die finalen Statistiken aus.
 *
 * @param[in] p_cfg Simulationskonfiguration.
 */
void simulation_run(const SimConfig* p_cfg);

#endif /* SIMULATION_H */
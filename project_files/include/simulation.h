#ifndef SIMULATION_H
#define SIMULATION_H

#include "types.h"
#include "config.h"
#include "parking.h"
#include "queue.h"
#include "stats.h"
#include "rng.h"
#include "io.h"

/**
 * @brief Führt die komplette Simulation aus.
 *
 * @param[in] cfg Simulationskonfiguration.
 */
void simulation_run(const SimConfig* cfg);
/*
 * PSEUDOCODE:
 * - rng_seed(cfg->seed)
 * - parking_init(&parking, cfg->anzahl_stellplaetze)
 * - queue_init(&queue)
 * - stats_init(&stats)
 * - io_open_log("project_files/data/log.txt")
 *
 * - for step = 0 .. cfg->sim_dauer_zeitschritte-1:
 *     stats_reset_step(&stats)
 *     parking_process_departures(&parking, &queue, &stats)
 *
 *     if rng_chance_percent(cfg->ankunft_wahrscheinlichkeit_prozent):
 *         parking_handle_arrival(&parking, &queue, cfg, &stats, step)
 *
 *     stats_update_step(&stats, &parking, &queue, step)
 *     stats_print_step(&stats, step)
 *     io_log_step(&stats, step)
 *
 * - stats_print_final(&stats)
 * - io_log_final(&stats)
 * - io_close_log()
 * - queue_free(&queue)
 * - parking_free(&parking)
 */

#endif // SIMULATION_H
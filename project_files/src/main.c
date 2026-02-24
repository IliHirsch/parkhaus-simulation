#include "config.h"
#include "simulation.h"

/* main(...)
 * PSEUDOCODE:
 * - declare SimConfig cfg
 * - if config_read_from_terminal(&cfg) == false:
 *     print error message
 *     return 1
 * - simulation_run(&cfg)
 * - return 0
 */
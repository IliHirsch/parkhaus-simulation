#ifndef RNG_H
#define RNG_H

#include <stdbool.h>

/**
 * @brief Initialisiert den Zufallszahlengenerator.
 *
 * Bei gleichem Seed entsteht die gleiche Zufallsfolge (reproduzierbar).
 *
 * @param[in] seed Startwert für srand().
 */
void rng_seed(unsigned int seed);

/**
 * @brief Liefert eine Ganzzahl im inklusiven Bereich [min_incl .. max_incl].
 *
 * Wenn max_incl < min_incl, werden die Werte intern getauscht.
 *
 * @param[in] min_incl Untere Grenze (inkl.).
 * @param[in] max_incl Obere Grenze (inkl.).
 * @return Zufallszahl im Bereich [min_incl .. max_incl].
 */
int rng_int(int min_incl, int max_incl);

/**
 * @brief Liefert true mit Wahrscheinlichkeit percent%, sonst false.
 *
 * percent wird auf [0..100] begrenzt.
 *
 * @param[in] percent Wahrscheinlichkeit in Prozent.
 * @return true mit Wahrscheinlichkeit percent%, sonst false.
 */
bool rng_chance_percent(int percent);

#endif /* RNG_H */
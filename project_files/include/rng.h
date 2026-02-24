#ifndef RNG_H
#define RNG_H

#include <stdbool.h>
#include <stddef.h>

/* =========================
   Zufallsfunktionen
   ========================= */

/**
 * @brief Setzt den Zufalls-Seed.
 */
void rng_seed(unsigned int seed);
/*
 * PSEUDOCODE:
 * - srand(seed)
 */

/**
 * @brief Liefert Zufallszahl im Bereich [min_incl, max_incl].
 */
int rng_int(int min_incl, int max_incl);
/*
 * PSEUDOCODE:
 * - if max < min: swap
 * - r = rand()
 * - return min + (r % (max - min + 1))
 */

/**
 * @brief Entscheidet mit gegebener Prozentwahrscheinlichkeit.
 */
bool rng_chance_percent(int percent);
/*
 * PSEUDOCODE:
 * - clamp percent to [0..100]
 * - r = rng_int(0, 99)
 * - return (r < percent)
 */

#endif // RNG_H
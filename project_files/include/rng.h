#ifndef RNG_H
#define RNG_H

#include <stdbool.h>
#include <stdlib.h> /* srand(), rand() */

/**
 * @brief Initialisiert den Zufallszahlengenerator.
 *
 * Bei gleichem Seed entsteht die gleiche Zufallsfolge (reproduzierbar).
 *
 * @param[in] seed Startwert für srand().
 */
void rng_seed(unsigned int seed);
/*
 * FUNCTION rng_seed(seed)
 * INPUT  seed
 * OUTPUT Zufallszahlengenerator initialisiert
 *
 * CALL srand(seed)
 *
 * END FUNCTION
 */

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
/*
 * FUNCTION rng_int(min_incl, max_incl) RETURNS r
 * INPUT  min_incl, max_incl
 * OUTPUT r im Bereich [min_incl .. max_incl]
 *
 * IF max_incl < min_incl THEN
 *     tmp <- min_incl
 *     min_incl <- max_incl
 *     max_incl <- tmp
 * END IF
 *
 * range <- (max_incl - min_incl + 1)
 * raw <- rand()
 * r <- min_incl + (raw MOD range)
 *
 * RETURN r
 *
 * END FUNCTION
 */

/**
 * @brief Liefert true mit Wahrscheinlichkeit percent%, sonst false.
 *
 * percent wird auf [0..100] begrenzt.
 *
 * @param[in] percent Wahrscheinlichkeit in Prozent.
 * @return true mit Wahrscheinlichkeit percent%, sonst false.
 */
bool rng_chance_percent(int percent);
/*
 * FUNCTION rng_chance_percent(percent) RETURNS ok
 * INPUT  percent
 * OUTPUT true mit Wahrscheinlichkeit percent%, sonst false
 *
 * IF percent < 0 THEN
 *     percent <- 0
 * ELSE IF percent > 100 THEN
 *     percent <- 100
 * END IF
 *
 * r <- CALL rng_int(0, 99)
 *
 * IF r < percent THEN
 *     RETURN true
 * ELSE
 *     RETURN false
 * END IF
 *
 * END FUNCTION
 */

#endif // RNG_H
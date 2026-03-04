#include "rng.h"
#include <stdlib.h> /* srand, rand */

/**
 * @brief Initialisiert den Zufallszahlengenerator.
 *
 * Bei gleichem Seed entsteht die gleiche Zufallsfolge (reproduzierbar).
 *
 * @param[in] seed Startwert für srand().
 */
void rng_seed(unsigned int seed)
{
    srand(seed);
}

/**
 * @brief Liefert eine Ganzzahl im inklusiven Bereich [min_incl .. max_incl].
 *
 * Wenn max_incl < min_incl, werden die Werte intern getauscht.
 *
 * @param[in] min_incl Untere Grenze (inkl.).
 * @param[in] max_incl Obere Grenze (inkl.).
 * @return Zufallszahl im Bereich [min_incl .. max_incl].
 */
int rng_int(int min_incl, int max_incl)
{
    if (max_incl < min_incl) {
        int tmp = min_incl;
        min_incl = max_incl;
        max_incl = tmp;
    }

    if (min_incl == max_incl) {
        return min_incl;
    }

    /* inklusiver Bereich */
    int range = max_incl - min_incl + 1;

    /* defensiv: sollte bei euren Parametern nicht passieren */
    if (range <= 0) {
        return min_incl;
    }

    return min_incl + (rand() % range);
}

/**
 * @brief Liefert true mit Wahrscheinlichkeit percent%, sonst false.
 *
 * percent wird auf [0..100] begrenzt.
 *
 * @param[in] percent Wahrscheinlichkeit in Prozent.
 * @return true mit Wahrscheinlichkeit percent%, sonst false.
 */
bool rng_chance_percent(int percent)
{
    if (percent <= 0) {
        return false;
    }
    if (percent >= 100) {
        return true;
    }

    return (rng_int(0, 99) < percent);
}
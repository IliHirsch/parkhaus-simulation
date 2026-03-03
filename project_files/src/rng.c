#include "rng.h"
#include <stdlib.h> /* srand(), rand() */

void rng_seed(unsigned int seed)
{
    /*
     * FUNCTION rng_seed(seed)
     * INPUT  seed
     * OUTPUT Zufallszahlengenerator initialisiert
     *
     * CALL srand(seed)
     *
     * END FUNCTION
     */
}

int rng_int(int min_incl, int max_incl)
{
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
}

bool rng_chance_percent(int percent)
{
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
}
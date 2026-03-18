#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/rng.h"


/**
 * @brief Prüft, dass rng_int immer Werte innerhalb des Bereichs liefert.
 */
static void test_rng_int_returns_value_within_range(void)
{
    int i;
    int value;

    rng_seed(7U);

    for (i = 0; i < 100; i++) {
        value = rng_int(1, 5);
        assert(value >= 1);
        assert(value <= 5);
    }
}

/**
 * @brief Prüft, dass vertauschte Grenzen intern korrekt behandelt werden.
 */
static void test_rng_int_swaps_reversed_bounds_correctly(void)
{
    int i;
    int value;

    rng_seed(7U);

    for (i = 0; i < 100; i++) {
        value = rng_int(5, 1);
        assert(value >= 1);
        assert(value <= 5);
    }
}

/**
 * @brief Prüft, dass 0 Prozent immer false liefert.
 */
static void test_rng_chance_percent_zero_returns_false(void)
{
        int i;

    rng_seed(9U);

    for (i = 0; i < 100; i++) {
        assert(rng_chance_percent(0) == false);
    }
}

/**
 * @brief Prüft, dass 100 Prozent immer true liefert.
 */
static void test_rng_chance_percent_hundred_returns_true(void)
{
    int i;

    rng_seed(9U);

    for (i = 0; i < 100; i++) {
        assert(rng_chance_percent(100) == true);
    }
}

int main(void)
{
    test_rng_int_returns_value_within_range();
    test_rng_int_swaps_reversed_bounds_correctly();

    test_rng_chance_percent_zero_returns_false();
    test_rng_chance_percent_hundred_returns_true();

    printf("Alle RNG-Tests erfolgreich.\n");
    return 0;
}
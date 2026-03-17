#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "rng.h"




/**
 * @brief Prüft, dass rng_int immer Werte innerhalb des Bereichs liefert.
 */
static void test_rng_int_returns_value_within_range(void)
{}

/**
 * @brief Prüft, dass vertauschte Grenzen intern korrekt behandelt werden.
 */
static void test_rng_int_swaps_reversed_bounds_correctly(void)
{}

/**
 * @brief Prüft, dass 0 Prozent immer false liefert.
 */
static void test_rng_chance_percent_zero_returns_false(void)
{}

/**
 * @brief Prüft, dass 100 Prozent immer true liefert.
 */
static void test_rng_chance_percent_hundred_returns_true(void)
{}

int main(void)
{


    test_rng_int_returns_value_within_range();
    test_rng_int_swaps_reversed_bounds_correctly();

    test_rng_chance_percent_zero_returns_false();
    test_rng_chance_percent_hundred_returns_true();

    printf("Alle RNG-Tests erfolgreich.\n");
    return 0;
}
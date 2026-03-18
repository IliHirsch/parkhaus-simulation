#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stats.h"
#include "types.h"

/**
 * @brief Hilfsfunktion zum Erzeugen eines Test-Fahrzeugs.
 *
 * @param[in] id Fahrzeug-ID.
 * @param[in] restparkdauer Restparkdauer.
 * @param[in] ankunftszeit Ankunftszeit.
 * @return Erzeugtes Vehicle.
 */
static Vehicle make_vehicle(unsigned int id, int restparkdauer, int ankunftszeit)
{
    Vehicle v;
    v.id = id;
    v.restparkdauer = restparkdauer;
    v.ankunftszeit = ankunftszeit;
    return v;
}

/* =========================
   stats_init
   ========================= */

/**
 * @brief Prüft, dass stats_init alle Felder auf 0 setzt.
 */
static void test_stats_init_sets_all_fields_to_zero(void)
{
    Stats stats;

    stats_init(&stats);

    assert(stats.neu_angekommen == 0U);
    assert(stats.verlassen == 0U);
    assert(stats.abgefertigte_wartende == 0U);

    assert(stats.belegung == 0U);
    assert(stats.warteschlangenlaenge == 0U);

    assert(stats.step_count == 0U);
    assert(stats.sum_belegung == 0U);
    assert(stats.sum_warteschlange == 0U);
    assert(stats.max_warteschlange == 0U);
    assert(stats.vollauslastung_steps == 0U);

    assert(stats.sum_restparkdauer == 0U);
    assert(stats.count_restparkdauer == 0U);

    assert(stats.sum_wartezeit == 0U);
    assert(stats.count_wartezeit == 0U);

    assert(stats.sum_parkdauer == 0U);
    assert(stats.count_parkdauer == 0U);
}

/**
 * @brief Prüft, dass stats_init auch bereits gesetzte Werte zurücksetzt.
 */
static void test_stats_init_resets_previously_modified_values(void)
{
    Stats stats;

    stats.neu_angekommen = 5U;
    stats.verlassen = 2U;
    stats.abgefertigte_wartende = 3U;
    stats.belegung = 4U;
    stats.warteschlangenlaenge = 6U;
    stats.step_count = 7U;
    stats.sum_belegung = 8U;
    stats.sum_warteschlange = 9U;
    stats.max_warteschlange = 10U;
    stats.vollauslastung_steps = 11U;
    stats.sum_restparkdauer = 12U;
    stats.count_restparkdauer = 13U;
    stats.sum_wartezeit = 14U;
    stats.count_wartezeit = 15U;
    stats.sum_parkdauer = 16U;
    stats.count_parkdauer = 17U;

    stats_init(&stats);

    assert(stats.neu_angekommen == 0U);
    assert(stats.verlassen == 0U);
    assert(stats.abgefertigte_wartende == 0U);
    assert(stats.belegung == 0U);
    assert(stats.warteschlangenlaenge == 0U);
    assert(stats.step_count == 0U);
    assert(stats.sum_belegung == 0U);
    assert(stats.sum_warteschlange == 0U);
    assert(stats.max_warteschlange == 0U);
    assert(stats.vollauslastung_steps == 0U);
    assert(stats.sum_restparkdauer == 0U);
    assert(stats.count_restparkdauer == 0U);
    assert(stats.sum_wartezeit == 0U);
    assert(stats.count_wartezeit == 0U);
    assert(stats.sum_parkdauer == 0U);
    assert(stats.count_parkdauer == 0U);
}

/* =========================
   stats_reset_step
   ========================= */

/**
 * @brief Prüft, dass stats_reset_step nur die Step-Zähler zurücksetzt.
 */
static void test_stats_reset_step_resets_only_step_counters(void)
{
    Stats stats;

    stats_init(&stats);

    stats.neu_angekommen = 4U;
    stats.verlassen = 2U;
    stats.abgefertigte_wartende = 1U;

    stats.belegung = 3U;
    stats.warteschlangenlaenge = 5U;
    stats.step_count = 7U;
    stats.sum_belegung = 8U;

    stats_reset_step(&stats);

    assert(stats.neu_angekommen == 0U);
    assert(stats.verlassen == 0U);
    assert(stats.abgefertigte_wartende == 0U);

    assert(stats.belegung == 3U);
    assert(stats.warteschlangenlaenge == 5U);
    assert(stats.step_count == 7U);
    assert(stats.sum_belegung == 8U);
}

/**
 * @brief Prüft, dass stats_reset_step bei bereits 0 gesetzten Step-Zählern stabil bleibt.
 */
static void test_stats_reset_step_keeps_zero_step_counters_at_zero(void)
{
    Stats stats;

    stats_init(&stats);

    stats_reset_step(&stats);

    assert(stats.neu_angekommen == 0U);
    assert(stats.verlassen == 0U);
    assert(stats.abgefertigte_wartende == 0U);
}

/* =========================
   stats_update_step
   ========================= */

/**
 * @brief Prüft, dass stats_update_step Belegung, Queue-Länge und Summen korrekt aktualisiert.
 */
static void test_stats_update_step_updates_current_values_and_aggregates(void)
{
    Stats stats;
    ParkingLot parking;
    Queue queue;

    stats_init(&stats);
    queue_init(&queue);

    parking.kapazitaet = 3U;
    parking.belegte_plaetze = 2U;
    parking.slots = malloc(3U * sizeof(ParkingSlot));
    assert(parking.slots != NULL);

    parking.slots[0].belegt = true;
    parking.slots[0].fahrzeug = make_vehicle(1U, 3, 0);

    parking.slots[1].belegt = true;
    parking.slots[1].fahrzeug = make_vehicle(2U, 2, 1);

    parking.slots[2].belegt = false;

    assert(queue_push(&queue, make_vehicle(10U, 4, 2)) == true);
    assert(queue_push(&queue, make_vehicle(11U, 5, 3)) == true);

    stats_update_step(&stats, &parking, &queue, 1);

    assert(stats.belegung == 2U);
    assert(stats.warteschlangenlaenge == 2U);

    assert(stats.step_count == 1U);
    assert(stats.sum_belegung == 2U);
    assert(stats.sum_warteschlange == 2U);
    assert(stats.max_warteschlange == 2U);
    assert(stats.vollauslastung_steps == 0U);

    assert(stats.sum_restparkdauer == 5U);
    assert(stats.count_restparkdauer == 2U);

    queue_free(&queue);
    free(parking.slots);
}

/**
 * @brief Prüft, dass stats_update_step Vollauslastung und Maximum korrekt fortführt.
 */
static void test_stats_update_step_tracks_full_utilization_and_max_queue(void)
{
    Stats stats;
    ParkingLot parking;
    Queue queue;

    stats_init(&stats);
    queue_init(&queue);

    parking.kapazitaet = 2U;
    parking.belegte_plaetze = 2U;
    parking.slots = malloc(2U * sizeof(ParkingSlot));
    assert(parking.slots != NULL);

    parking.slots[0].belegt = true;
    parking.slots[0].fahrzeug = make_vehicle(1U, 4, 0);

    parking.slots[1].belegt = true;
    parking.slots[1].fahrzeug = make_vehicle(2U, 1, 1);

    assert(queue_push(&queue, make_vehicle(20U, 3, 2)) == true);

    stats_update_step(&stats, &parking, &queue, 1);

    assert(stats.belegung == 2U);
    assert(stats.warteschlangenlaenge == 1U);
    assert(stats.step_count == 1U);
    assert(stats.sum_belegung == 2U);
    assert(stats.sum_warteschlange == 1U);
    assert(stats.max_warteschlange == 1U);
    assert(stats.vollauslastung_steps == 1U);
    assert(stats.sum_restparkdauer == 5U);
    assert(stats.count_restparkdauer == 2U);

    queue_free(&queue);
    free(parking.slots);
}

/* =========================
   stats_print
   ========================= */


/**
 * @brief Prüft, dass stats_print_step mit gültigen Daten aufrufbar ist.
 */
static void test_stats_print_step_runs_with_valid_stats(void)
{
    Stats stats;

    stats_init(&stats);
    stats.belegung = 2U;
    stats.warteschlangenlaenge = 1U;
    stats.neu_angekommen = 1U;
    stats.verlassen = 0U;
    stats.abgefertigte_wartende = 1U;
    stats.sum_restparkdauer = 6U;
    stats.count_restparkdauer = 2U;

    stats_print_step(&stats, 1);

    assert(true);
}

/**
 * @brief Prüft, dass stats_print_final mit gültigen Daten aufrufbar ist.
 */
static void test_stats_print_final_runs_with_valid_stats(void)
{
    Stats stats;

    stats_init(&stats);
    stats.step_count = 2U;
    stats.sum_belegung = 3U;
    stats.sum_warteschlange = 1U;
    stats.max_warteschlange = 1U;
    stats.vollauslastung_steps = 1U;
    stats.sum_wartezeit = 4U;
    stats.count_wartezeit = 2U;
    stats.sum_parkdauer = 7U;
    stats.count_parkdauer = 2U;
    stats.sum_restparkdauer = 5U;
    stats.count_restparkdauer = 2U;

    stats_print_final(&stats);

    assert(true);
}

int main(void)
{
    test_stats_init_sets_all_fields_to_zero();
    test_stats_init_resets_previously_modified_values();

    test_stats_reset_step_resets_only_step_counters();
    test_stats_reset_step_keeps_zero_step_counters_at_zero();

    test_stats_update_step_updates_current_values_and_aggregates();
    test_stats_update_step_tracks_full_utilization_and_max_queue();

    test_stats_print_step_runs_with_valid_stats();
    test_stats_print_final_runs_with_valid_stats();

    printf("Alle Stats-Tests erfolgreich.\n");
    return 0;
}
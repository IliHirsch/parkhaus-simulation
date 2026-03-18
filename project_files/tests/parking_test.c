#include<assert.h>
#include<stdio.h>
#include<stdbool.h>

#include "../include/parking.h"
#include "../include/queue.h"
#include "../include/stats.h"
#include "../include/rng.h"
#include "../include/types.h"
#include "../include/config.h"

/**
 * @brief Erzeugt ein Test-Fahrzeug mit den übergebenen Werten.
 *
 * @param[in] id Fahrzeug-ID.
 * @param[in] restparkdauer Verbleibende Parkdauer.
 * @param[in] ankunftszeit Ankunftszeit des Fahrzeugs.
 * @return Initialisiertes Vehicle.
 */
static Vehicle make_vehicle(unsigned int id, int restparkdauer, int ankunftszeit)
{
    Vehicle v;
    v.id = id;
    v.restparkdauer = restparkdauer;
    v.ankunftszeit = ankunftszeit;
    return v;
}

/**
 * @brief Erzeugt eine gültige Test-Konfiguration.
 *
 * @param[in] kapazitaet Anzahl Stellplätze.
 * @param[in] max_parkdauer Maximale Parkdauer.
 * @return Initialisierte SimConfig.
 */
static SimConfig make_config(size_t kapazitaet, int max_parkdauer)
{
    SimConfig cfg;
    cfg.anzahl_stellplaetze = kapazitaet;
    cfg.max_parkdauer = max_parkdauer;
    cfg.sim_dauer_zeitschritte = 10;
    cfg.ankunft_wahrscheinlichkeit_prozent = 50;
    cfg.seed = 123U;
    return cfg;
}

/* =========================
   parking_init
   ========================= */

/**
 * @brief Prüft, dass parking_init ein leeres Parkhaus korrekt initialisiert.
 */
static void test_parking_init_creates_empty_parking_lot(void)
{
    ParkingLot parking;
    bool ok = parking_init(&parking, 3U);

    assert(ok == true);
    assert(parking.slots != NULL);
    assert(parking.kapazitaet == 3U);
    assert(parking.belegte_plaetze == 0U);

    for (size_t i = 0U; i < parking.kapazitaet; i++) {
        assert(parking.slots[i].belegt == false);
    }

    parking_free(&parking);
}

/**
 * @brief Prüft, dass parking_init bei Kapazität 0 false zurückgibt.
 */
static void test_parking_init_with_zero_capacity_returns_false(void)
{
    ParkingLot parking;
    bool ok = parking_init(&parking, 0U);

    assert(ok == false);
}

/* =========================
   parking_free
   ========================= */

/**
 * @brief Prüft, dass parking_free alle Felder des Parkhauses zurücksetzt.
 */
static void test_parking_free_resets_all_fields(void)
{
    ParkingLot parking;
    bool ok = parking_init(&parking, 2U);

    assert(ok == true);

    parking.slots[0].belegt = true;
    parking.belegte_plaetze = 1U;

    parking_free(&parking);

    assert(parking.slots == NULL);
    assert(parking.kapazitaet == 0U);
    assert(parking.belegte_plaetze == 0U);
}

/**
 * @brief Prüft, dass parking_free(NULL) keinen Absturz verursacht.
 */
static void test_parking_free_with_null_does_not_crash(void)
{
    parking_free(NULL);
    assert(true);
}

/* =========================
   parking_find_free_slot
   ========================= */

/**
 * @brief Prüft, dass parking_find_free_slot den ersten freien Index liefert.
 */
static void test_parking_find_free_slot_returns_first_free_index(void)
{
    ParkingLot parking;
    bool ok = parking_init(&parking, 3U);

    assert(ok == true);

    parking.slots[0].belegt = true;
    parking.slots[1].belegt = false;
    parking.slots[2].belegt = true;

    assert(parking_find_free_slot(&parking) == 1);

    parking_free(&parking);
}

/**
 * @brief Prüft, dass parking_find_free_slot bei vollem Parkhaus -1 liefert.
 */
static void test_parking_find_free_slot_returns_minus_one_when_full(void)
{
    ParkingLot parking;
    bool ok = parking_init(&parking, 2U);

    assert(ok == true);

    parking.slots[0].belegt = true;
    parking.slots[1].belegt = true;

    assert(parking_find_free_slot(&parking) == -1);

    parking_free(&parking);
}

/* =========================
   parking_handle_arrival
   ========================= */

/**
 * @brief Prüft, dass ein ankommendes Fahrzeug direkt eingeparkt wird,
 *        wenn ein freier Stellplatz vorhanden ist.
 */
static void test_parking_handle_arrival_parks_vehicle_when_slot_is_free(void)
{
     ParkingLot parking;
    Queue queue;
    Stats stats;
    SimConfig cfg = make_config(2U, 1);
    unsigned int next_vehicle_id = 1U;

    assert(parking_init(&parking, cfg.anzahl_stellplaetze) == true);
    queue_init(&queue);
    stats_init(&stats);
    rng_seed(1U);

    SimStatus status = parking_handle_arrival(
        &parking,
        &queue,
        &cfg,
        &stats,
        5,
        &next_vehicle_id
    );

    assert(status == SIM_OK);
    assert(parking.belegte_plaetze == 1U);
    assert(queue_size(&queue) == 0U);

    assert(parking.slots[0].belegt == true);
    assert(parking.slots[0].fahrzeug.id == 1U);
    assert(parking.slots[0].fahrzeug.restparkdauer == 1);
    assert(parking.slots[0].fahrzeug.ankunftszeit == 5);

    assert(next_vehicle_id == 2U);
    assert(stats.neu_angekommen == 1U);
    assert(stats.sum_parkdauer == 1U);
    assert(stats.count_parkdauer == 1U);

    queue_free(&queue);
    parking_free(&parking);
}

/**
 * @brief Prüft, dass ein ankommendes Fahrzeug in die Warteschlange kommt,
 *        wenn kein freier Stellplatz vorhanden ist.
 */
static void test_parking_handle_arrival_queues_vehicle_when_no_slot_is_free(void)
{
    ParkingLot parking;
    Queue queue;
    Stats stats;
    SimConfig cfg = make_config(1U, 1);
    unsigned int next_vehicle_id = 7U;

    assert(parking_init(&parking, cfg.anzahl_stellplaetze) == true);
    queue_init(&queue);
    stats_init(&stats);
    rng_seed(1U);

    parking.slots[0].belegt = true;
    parking.slots[0].fahrzeug = make_vehicle(99U, 2, 0);
    parking.belegte_plaetze = 1U;

    SimStatus status = parking_handle_arrival(
        &parking,
        &queue,
        &cfg,
        &stats,
        3,
        &next_vehicle_id
    );

    assert(status == SIM_KFZ_WARTEN);
    assert(parking.belegte_plaetze == 1U);
    assert(queue_size(&queue) == 1U);

    Vehicle out_vehicle;
    assert(queue_pop(&queue, &out_vehicle) == true);
    assert(out_vehicle.id == 7U);
    assert(out_vehicle.restparkdauer == 1);
    assert(out_vehicle.ankunftszeit == 3);

    assert(next_vehicle_id == 8U);
    assert(stats.neu_angekommen == 1U);
    assert(stats.sum_parkdauer == 1U);
    assert(stats.count_parkdauer == 1U);

    queue_free(&queue);
    parking_free(&parking);
}

/* =========================
   parking_process_departures
   ========================= */

/**
 * @brief Prüft, dass parking_process_departures die Restparkdauer
 *        belegter Fahrzeuge korrekt reduziert.
 */
static void test_parking_process_departures_decrements_restparkdauer(void)
{
    ParkingLot parking;
    Stats stats;

    assert(parking_init(&parking, 2U) == true);
    stats_init(&stats);

    parking.slots[0].belegt = true;
    parking.slots[0].fahrzeug = make_vehicle(1U, 3, 0);
    parking.belegte_plaetze = 1U;

    parking_process_departures(&parking, &stats);

    assert(parking.slots[0].belegt == true);
    assert(parking.slots[0].fahrzeug.restparkdauer == 2);
    assert(parking.belegte_plaetze == 1U);
    assert(stats.verlassen == 0U);

    parking_free(&parking);
}

/**
 * @brief Prüft, dass Fahrzeuge entfernt werden, wenn ihre Restparkdauer
 *        auf 0 oder kleiner fällt.
 */
static void test_parking_process_departures_removes_vehicle_when_restparkdauer_reaches_zero(void)
{
    ParkingLot parking;
    Stats stats;

    assert(parking_init(&parking, 2U) == true);
    stats_init(&stats);

    parking.slots[0].belegt = true;
    parking.slots[0].fahrzeug = make_vehicle(1U, 1, 0);
    parking.belegte_plaetze = 1U;

    parking_process_departures(&parking, &stats);

    assert(parking.slots[0].belegt == false);
    assert(parking.belegte_plaetze == 0U);
    assert(stats.verlassen == 1U);

    parking_free(&parking);
}

/* =========================
   parking_process_queue
   ========================= */

/**
 * @brief Prüft, dass ein wartendes Fahrzeug aus der Queue auf einen
 *        freien Stellplatz übernommen wird.
 */
static void test_parking_process_queue_moves_waiting_vehicle_into_free_slot(void)
{
    ParkingLot parking;
    Queue queue;
    Stats stats;

    assert(parking_init(&parking, 2U) == true);
    queue_init(&queue);
    stats_init(&stats);

    assert(queue_push(&queue, make_vehicle(10U, 4, 2)) == true);

    parking_process_queue(&parking, &queue, &stats, 5);

    assert(queue_size(&queue) == 0U);
    assert(parking.belegte_plaetze == 1U);
    assert(parking.slots[0].belegt == true);
    assert(parking.slots[0].fahrzeug.id == 10U);

    assert(stats.abgefertigte_wartende == 1U);
    assert(stats.sum_wartezeit == 3U);
    assert(stats.count_wartezeit == 1U);

    queue_free(&queue);
    parking_free(&parking);
}

/**
 * @brief Prüft, dass Fahrzeuge in der Queue bleiben, wenn kein freier
 *        Stellplatz vorhanden ist.
 */
static void test_parking_process_queue_keeps_vehicle_waiting_when_no_slot_is_free(void)
{
    ParkingLot parking;
    Queue queue;
    Stats stats;

    assert(parking_init(&parking, 1U) == true);
    queue_init(&queue);
    stats_init(&stats);

    parking.slots[0].belegt = true;
    parking.slots[0].fahrzeug = make_vehicle(99U, 2, 0);
    parking.belegte_plaetze = 1U;

    assert(queue_push(&queue, make_vehicle(10U, 4, 2)) == true);

    parking_process_queue(&parking, &queue, &stats, 5);

    assert(queue_size(&queue) == 1U);
    assert(parking.belegte_plaetze == 1U);
    assert(stats.abgefertigte_wartende == 0U);
    assert(stats.sum_wartezeit == 0U);
    assert(stats.count_wartezeit == 0U);

    queue_free(&queue);
    parking_free(&parking);
}


int main (){

    test_parking_init_creates_empty_parking_lot();
    test_parking_init_with_zero_capacity_returns_false();

    test_parking_free_resets_all_fields();
    test_parking_free_with_null_does_not_crash();

    test_parking_find_free_slot_returns_first_free_index();
    test_parking_find_free_slot_returns_minus_one_when_full();

    test_parking_handle_arrival_parks_vehicle_when_slot_is_free();
    test_parking_handle_arrival_queues_vehicle_when_no_slot_is_free();

    test_parking_process_departures_decrements_restparkdauer();
    test_parking_process_departures_removes_vehicle_when_restparkdauer_reaches_zero();

    test_parking_process_queue_moves_waiting_vehicle_into_free_slot();
    test_parking_process_queue_keeps_vehicle_waiting_when_no_slot_is_free();

    printf("Alle Parking-Tests erfolgreich.\n");
    return 0;
}

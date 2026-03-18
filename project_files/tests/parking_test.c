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
 * @brief Hilfsfunktion zum Erzeugen eines Fahrzeugs.
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
 * @brief Hilfsfunktion zum Erzeugen einer gültigen Test-Konfiguration.
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
static void test_parking_init_with_zero_capacity_returns_false(void)
{
    ParkingLot parking;
    bool ok = parking_init(&parking, 0U);

    assert(ok == false);
}




int main (){

    test_parking_init_creates_empty_parking_lot();
    test_parking_init_with_zero_capacity_returns_false();


    printf("Alle Parking-Tests erfolgreich.\n");
    return 0;
}

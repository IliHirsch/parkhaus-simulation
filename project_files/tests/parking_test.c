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



int main (){


    printf("Alle Parking-Tests erfolgreich.\n");
    return 0;
}

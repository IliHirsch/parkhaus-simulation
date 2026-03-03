#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stddef.h>

/* =========================
   Status Codes
   ========================= */

typedef enum {
    SIM_OK = 0,
    SIM_KFZ_WARTEN,
    SIM_ERR_INPUT
} SimStatus;

/* =========================
   Fahrzeug
   ========================= */

typedef struct {
    unsigned int id;
    int restparkdauer;   // geplante Parkdauer bei Erzeugung
    int einfahrtzeit;    // Zeitpunkt der ANKUNFT am Parkhaus (für Wartezeitmessung)
} Vehicle;

/* =========================
   Stellplatz
   ========================= */

typedef struct {
    bool belegt;
    Vehicle fahrzeug;
} ParkingSlot;

/* =========================
   Parkhaus
   ========================= */

typedef struct {
    ParkingSlot* slots;
    size_t kapazitaet;
    size_t belegte_plaetze;
} ParkingLot;

/* =========================
   Warteschlange
   ========================= */

typedef struct QueueNode {
    Vehicle fahrzeug;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* head;
    QueueNode* tail;
    size_t size;
} Queue;

/* =========================
   Statistik
   ========================= */

typedef struct {
    /* Step-Zähler (pro Zeitschritt) */
    size_t neu_angekommen;
    size_t verlassen;
    size_t abgefertigte_wartende;

    /* Momentanwerte (Zustand nach dem Step) */
    size_t belegung;
    size_t warteschlangenlaenge;

    /* Aggregate über alle Steps */
    size_t step_count;
    size_t sum_belegung;
    size_t sum_warteschlange;
    size_t max_warteschlange;
    size_t vollauslastung_steps;

    /* Restparkdauer-Samples (über alle parkenden Fahrzeuge über die Zeit) */
    size_t sum_restparkdauer;
    size_t count_restparkdauer;

    /* Wartezeit (nur wenn Fahrzeuge aus Queue wirklich einparken) */
    size_t sum_wartezeit;
    size_t count_wartezeit;

    /* Parkdauer (bei Ankunft erfasst, geplante Parkdauer) */
    size_t sum_parkdauer;
    size_t count_parkdauer;

} Stats;

#endif // TYPES_H
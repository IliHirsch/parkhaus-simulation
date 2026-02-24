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
    int restparkdauer;
    int einfahrtzeit;
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
   Statistik (Basiswerte)
   ========================= */

typedef struct {
    size_t neu_angekommen;
    size_t verlassen;
    size_t abgefertigte_wartende;
    size_t belegung;
    size_t warteschlangenlaenge;
} Stats;

#endif // TYPES_H
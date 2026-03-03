# Datentypen und Strukturen Übersicht

## SimStatus

```c
typedef enum {
    SIM_OK = 0,
    SIM_KFZ_WARTEN,
    SIM_ERR_INPUT
} SimStatus;
```

Statuscodes zur Rückmeldung von Funktionsaufrufen innerhalb der Simulation.

## SimConfig

```c
typedef struct {
    size_t anzahl_stellplaetze;
    int max_parkdauer;
    int sim_dauer_zeitschritte;
    int ankunft_wahrscheinlichkeit_prozent;
    unsigned int seed;
} SimConfig;
```

Enthält alle konfigurierbaren Simulationsparameter, die vor Start der Simulation festgelegt werden.

## Vehicle

```c
typedef struct {
    unsigned int id;
    int restparkdauer;
    int einfahrtzeit;
} Vehicle;
```

Repräsentiert ein Fahrzeug mit eindeutiger ID, verbleibender Parkdauer und Ankunftszeit.

## ParkingSlot

```c
typedef struct {
    bool belegt;
    Vehicle fahrzeug;
} ParkingSlot;
```

Modelliert einen einzelnen Stellplatz mit Belegungsstatus und zugehörigem Fahrzeug.

## ParkingLot

```c
typedef struct {
    ParkingSlot* slots;
    size_t kapazitaet;
    size_t belegte_plaetze;
} ParkingLot;
```

Beschreibt das gesamte Parkhaus mit dynamischem Array von Stellplätzen, Gesamtkapazität und aktueller Belegung.

## QueueNode

```c
typedef struct QueueNode {
    Vehicle fahrzeug;
    struct QueueNode* next;
} QueueNode;
```

Einzelnes Element der Warteschlange als verketteter Listen-Knoten.

## Queue

```c
typedef struct {
    QueueNode* head;
    QueueNode* tail;
    size_t size;
} Queue;
```

FIFO-Warteschlange für Fahrzeuge mit Zeigern auf erstes und letztes Element sowie aktueller Größe.

## Stats

```c
typedef struct {
    size_t neu_angekommen;
    size_t verlassen;
    size_t abgefertigte_wartende;

    size_t belegung;
    size_t warteschlangenlaenge;

    size_t step_count;
    size_t sum_belegung;
    size_t sum_warteschlange;
    size_t max_warteschlange;
    size_t vollauslastung_steps;

    size_t sum_restparkdauer;
    size_t count_restparkdauer;

    size_t sum_wartezeit;
    size_t count_wartezeit;

    size_t sum_parkdauer;
    size_t count_parkdauer;

} Stats;
```

Zentrale Statistikstruktur zur Erfassung von Step-Werten, Momentanzuständen und aggregierten Kennzahlen über die gesamte Simulation.

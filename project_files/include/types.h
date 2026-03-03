#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stddef.h>

/* =========================
   Status Codes
   ========================= */

/**
 * @brief Statuscodes für Simulation/Teilfunktionen.
 *
 * SIM_OK: Operation erfolgreich.
 * SIM_KFZ_WARTEN: Fahrzeug muss warten (in Queue).
 * SIM_ERR_INPUT: Ungültige Eingabe oder Konfiguration.
 */
typedef enum {
    SIM_OK = 0,
    SIM_KFZ_WARTEN,
    SIM_ERR_INPUT
} SimStatus;

/* =========================
   Fahrzeug
   ========================= */

/**
 * @brief Repräsentiert ein Fahrzeug in der Simulation.
 *
 * restparkdauer ist die verbleibende Zeit bis zur Abfahrt (wird pro Zeitschritt reduziert).
 * einfahrtzeit ist die Ankunftszeit am Parkhaus (für Wartezeitmessung).
 */
typedef struct {
    unsigned int id;   /**< Eindeutige Fahrzeug-ID (laufend vergeben). */
    int restparkdauer; /**< Verbleibende Parkdauer in Zeitschritten. */
    int einfahrtzeit;  /**< Zeitpunkt der Ankunft am Parkhaus (nicht Einparkzeit!). */
} Vehicle;

/* =========================
   Stellplatz
   ========================= */

/**
 * @brief Ein Stellplatz im Parkhaus.
 *
 * Wenn belegt==true, ist fahrzeug gültig.
 */
typedef struct {
    bool belegt;       /**< true, wenn der Stellplatz belegt ist. */
    Vehicle fahrzeug;  /**< Das Fahrzeug, das aktuell auf dem Stellplatz steht. */
} ParkingSlot;

/* =========================
   Parkhaus
   ========================= */

/**
 * @brief Parkhaus-Zustand: Slots, Kapazität und belegte Plätze.
 */
typedef struct {
    ParkingSlot* slots;      /**< Array von Stellplätzen (Länge: kapazitaet). */
    size_t kapazitaet;       /**< Anzahl Stellplätze insgesamt. */
    size_t belegte_plaetze;  /**< Anzahl aktuell belegter Stellplätze. */
} ParkingLot;

/* =========================
   Warteschlange
   ========================= */

/**
 * @brief Ein Knoten der Warteschlange (Linked List).
 */
typedef struct QueueNode {
    Vehicle fahrzeug;         /**< Fahrzeugdaten. */
    struct QueueNode* next;   /**< Nächster Knoten oder NULL. */
} QueueNode;

/**
 * @brief Warteschlange (FIFO) für wartende Fahrzeuge.
 */
typedef struct {
    QueueNode* head; /**< Zeiger auf erstes Element oder NULL. */
    QueueNode* tail; /**< Zeiger auf letztes Element oder NULL. */
    size_t size;     /**< Anzahl Elemente in der Queue. */
} Queue;

/* =========================
   Statistik
   ========================= */

/**
 * @brief Sammelstruktur für Step-Statistiken und Aggregationen über die Simulation.
 *
 * Step-Zähler werden pro Zeitschritt zurückgesetzt.
 * Aggregierte Werte laufen über alle Steps weiter.
 */
typedef struct {
    /* Step-Zähler (pro Zeitschritt) */
    size_t neu_angekommen;         /**< Anzahl neu angekommener Fahrzeuge in diesem Step. */
    size_t verlassen;              /**< Anzahl abgefahrener Fahrzeuge in diesem Step. */
    size_t abgefertigte_wartende;  /**< Anzahl Fahrzeuge, die aus der Queue eingeparkt wurden in diesem Step. */

    /* Momentanwerte (Zustand nach dem Step) */
    size_t belegung;               /**< Belegte Plätze nach diesem Step. */
    size_t warteschlangenlaenge;   /**< Queue-Länge nach diesem Step. */

    /* Aggregate über alle Steps */
    size_t step_count;             /**< Anzahl simulierte Steps. */
    size_t sum_belegung;           /**< Summe Belegung über alle Steps (für Durchschnitt). */
    size_t sum_warteschlange;      /**< Summe Queue-Länge über alle Steps (für Durchschnitt). */
    size_t max_warteschlange;      /**< Maximale Queue-Länge über alle Steps. */
    size_t vollauslastung_steps;   /**< Anzahl Steps mit belegung == kapazitaet. */

    /* Restparkdauer-Samples (über alle parkenden Fahrzeuge über die Zeit) */
    size_t sum_restparkdauer;      /**< Summe der Restparkdauern aller Samples. */
    size_t count_restparkdauer;    /**< Anzahl Restparkdauer-Samples. */

    /* Wartezeit (nur wenn Fahrzeuge aus Queue wirklich einparken) */
    size_t sum_wartezeit;          /**< Summe Wartezeiten für Queue->Park Samples. */
    size_t count_wartezeit;        /**< Anzahl Wartezeit-Samples. */

    /* Parkdauer (bei Ankunft erfasst, geplante Parkdauer) */
    size_t sum_parkdauer;          /**< Summe geplante Parkdauer aller erzeugten Fahrzeuge. */
    size_t count_parkdauer;        /**< Anzahl Parkdauer-Samples. */

} Stats;

#endif /* TYPES_H */
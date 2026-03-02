#ifndef QUEUE_H
#define QUEUE_H

#include "vehicle.h"

/**
 * @brief Knotenstruktur der Warteschlange.
 *
 * Enthält ein Fahrzeug und einen Zeiger
 * auf den nächsten Knoten.
 */

typedef struct queue_node
{
    vehicle_t vehicle;
    struct queue_node *p_next;
} queue_node_t;

/**
 * @brief Warteschlangenstruktur.
 *
 * Verwaltet Head- und Tail-Zeiger.
 */

typedef struct
{
    queue_node_t *p_head;
    queue_node_t *p_tail;
    int length;
} queue_t;

/**
 * @brief Initialisiert eine leere Warteschlange.
 *
 * @param[out] p_queue Zeiger auf Warteschlange
 */

void queue_init(queue_t *p_queue);

/**
 * @brief Fügt ein Fahrzeug am Ende hinzu.
 *
 * Dynamische Speicherallokation eines neuen Knotens.
 *
 * @param[in,out] p_queue Warteschlange
 * @param[in] vehicle Fahrzeug
 */

void queue_enqueue(queue_t *p_queue,
                   vehicle_t vehicle);

/**
 * @brief Entfernt das erste Fahrzeug.
 *
 * @param[in,out] p_queue Warteschlange
 * @param[out] p_vehicle Entferntes Fahrzeug
 * @return 1 bei Erfolg, 0 wenn leer
 */

int queue_dequeue(queue_t *p_queue,
                  vehicle_t *p_vehicle);

/**
 * @brief Prüft, ob die Warteschlange leer ist.
 *
 * @param[in] p_queue Warteschlange
 * @return 1 wenn leer, sonst 0
 */
int queue_is_empty(queue_t *p_queue);

#endif
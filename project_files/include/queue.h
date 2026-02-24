#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"
#include "vehicle.h"

/* =========================
   Queue (Warteschlange)
   Dynamisch (Linked List)
   ========================= */

/**
 * @brief Initialisiert eine leere Queue.
 *
 * @param[out] q Queue-Instanz.
 */
void queue_init(Queue* q);
/*
 * PSEUDOCODE:
 * - q->head = NULL
 * - q->tail = NULL
 * - q->size = 0
 */

/**
 * @brief Gibt den gesamten dynamischen Speicher der Queue frei.
 *
 * @param[in,out] q Queue-Instanz.
 */
void queue_free(Queue* q);
/*
 * PSEUDOCODE:
 * - while head != NULL:
 *     tmp = head
 *     head = head->next
 *     free(tmp)
 * - tail = NULL
 * - size = 0
 */

/**
 * @brief Fügt ein Fahrzeug hinten in die Queue ein.
 *
 * @param[in,out] q Queue-Instanz.
 * @param[in]     v Fahrzeug.
 * @return true wenn erfolgreich, sonst false (malloc fehlgeschlagen).
 */
bool queue_push(Queue* q, Vehicle v);
/*
 * PSEUDOCODE:
 * - node = malloc(sizeof(QueueNode))
 * - if node == NULL: return false
 * - node->fahrzeug = v; node->next = NULL
 * - if q empty: head=tail=node else: tail->next=node; tail=node
 * - size++
 * - return true
 */

/**
 * @brief Entfernt das vorderste Fahrzeug aus der Queue.
 *
 * @param[in,out] q Queue-Instanz.
 * @param[out]    out_v Ziel für das entfernte Fahrzeug.
 * @return true wenn ein Element entfernt wurde, sonst false (Queue leer).
 */
bool queue_pop(Queue* q, Vehicle* out_v);
/*
 * PSEUDOCODE:
 * - if empty: return false
 * - node = head
 * - *out_v = node->fahrzeug
 * - head = head->next
 * - if head == NULL: tail = NULL
 * - free(node)
 * - size--
 * - return true
 */

/**
 * @brief Liefert die aktuelle Anzahl wartender Fahrzeuge.
 */
size_t queue_size(const Queue* q);
/*
 * PSEUDOCODE:
 * - return q->size
 */

/**
 * @brief Prüft ob Queue leer ist.
 */
bool queue_is_empty(const Queue* q);
/*
 * PSEUDOCODE:
 * - return (q->size == 0)
 */

#endif // QUEUE_H
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "types.h"

/**
 * @brief Initialisiert eine Queue als leer.
 *
 * Setzt head/tail auf NULL und size auf 0.
 *
 * @param[out] q Queue, die initialisiert werden soll.
 */
void queue_init(Queue* q);
/*
 * FUNCTION queue_init(q)
 * INPUT  q
 * OUTPUT q initialisiert (leer)
 *
 * q->head <- NULL
 * q->tail <- NULL
 * q->size <- 0
 *
 * END FUNCTION
 */

/**
 * @brief Gibt alle Knoten der Queue frei und setzt sie zurück.
 *
 * Nach dem Aufruf ist die Queue leer (head/tail NULL, size 0).
 *
 * @param[in,out] q Queue, die freigegeben werden soll.
 */
void queue_free(Queue* q);
/*
 * FUNCTION queue_free(q)
 * INPUT  q
 * OUTPUT Speicher freigegeben, Queue leer
 *
 * WHILE q->head != NULL DO
 *     tmp <- q->head
 *     q->head <- q->head->next
 *     free(tmp)
 * END WHILE
 *
 * q->tail <- NULL
 * q->size <- 0
 *
 * END FUNCTION
 */

/**
 * @brief Fügt ein Fahrzeug hinten an die Queue an (FIFO).
 *
 * Allokiert intern einen neuen QueueNode.
 *
 * @param[in,out] q Queue, an die angehängt wird.
 * @param[in] v Fahrzeug, das eingereiht wird.
 * @return true wenn erfolgreich, false wenn Speicherallokation fehlschlägt.
 */
bool queue_push(Queue* q, Vehicle v);
/*
 * FUNCTION queue_push(q, v) RETURNS ok
 * INPUT  q, v
 * OUTPUT v am Ende eingefügt (FIFO)
 *
 * node <- malloc(sizeof(QueueNode))
 * IF node == NULL THEN
 *     RETURN false
 * END IF
 *
 * node->fahrzeug <- v
 * node->next <- NULL
 *
 * IF q->tail == NULL THEN
 *     q->head <- node
 *     q->tail <- node
 * ELSE
 *     q->tail->next <- node
 *     q->tail <- node
 * END IF
 *
 * q->size <- q->size + 1
 * RETURN true
 *
 * END FUNCTION
 */

/**
 * @brief Entfernt das vorderste Fahrzeug aus der Queue (FIFO).
 *
 * @param[in,out] q Queue, aus der entnommen wird.
 * @param[out] out_v Zielvariable für das entnommene Fahrzeug.
 * @return true wenn ein Element entnommen wurde, false wenn Queue leer ist.
 */
bool queue_pop(Queue* q, Vehicle* out_v);
/*
 * FUNCTION queue_pop(q, out_v) RETURNS ok
 * INPUT  q, out_v
 * OUTPUT v entfernt (FIFO) und in *out_v gespeichert
 *
 * IF q->head == NULL THEN
 *     RETURN false
 * END IF
 *
 * node <- q->head
 * *out_v <- node->fahrzeug
 * q->head <- node->next
 *
 * IF q->head == NULL THEN
 *     q->tail <- NULL
 * END IF
 *
 * free(node)
 * q->size <- q->size - 1
 * RETURN true
 *
 * END FUNCTION
 */

/**
 * @brief Liefert die aktuelle Anzahl Elemente in der Queue.
 *
 * @param[in] q Queue.
 * @return Anzahl Elemente.
 */
size_t queue_size(const Queue* q);
/*
 * FUNCTION queue_size(q) RETURNS n
 * RETURN q->size
 * END FUNCTION
 */

/**
 * @brief Prüft, ob die Queue leer ist.
 *
 * @param[in] q Queue.
 * @return true wenn leer, sonst false.
 */
bool queue_is_empty(const Queue* q);
/*
 * FUNCTION queue_is_empty(q) RETURNS empty
 * RETURN (q->size == 0)
 * END FUNCTION
 */

#endif // QUEUE_H
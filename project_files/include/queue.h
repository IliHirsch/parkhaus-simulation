#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "types.h"

/**
 * @brief Initialisiert eine Queue als leer.
 *
 * Setzt head/tail auf NULL und size auf 0.
 *
 * @param[out] q Queue, die initialisiert werden soll.
 */
void queue_init(Queue* q);

/**
 * @brief Gibt alle Knoten der Queue frei und setzt sie zurück.
 *
 * Nach dem Aufruf ist die Queue leer (head/tail NULL, size 0).
 *
 * @param[in,out] q Queue, die freigegeben werden soll.
 */
void queue_free(Queue* q);

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

/**
 * @brief Entfernt das vorderste Fahrzeug aus der Queue (FIFO).
 *
 * @param[in,out] q Queue, aus der entnommen wird.
 * @param[out] out_v Zielvariable für das entnommene Fahrzeug.
 * @return true wenn ein Element entnommen wurde, false wenn Queue leer ist.
 */
bool queue_pop(Queue* q, Vehicle* out_v);

/**
 * @brief Liefert die aktuelle Anzahl Elemente in der Queue.
 *
 * @param[in] q Queue.
 * @return Anzahl Elemente.
 */
size_t queue_size(const Queue* q);

/**
 * @brief Prüft, ob die Queue leer ist.
 *
 * @param[in] q Queue.
 * @return true wenn leer, sonst false.
 */
bool queue_is_empty(const Queue* q);

#endif /* QUEUE_H */
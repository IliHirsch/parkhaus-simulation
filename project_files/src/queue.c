#include "../include/queue.h"
#include <stdlib.h> /* malloc(), free() */

/**
 * @brief Initialisiert eine Queue als leer.
 *
 * Setzt head und tail auf NULL sowie size auf 0.
 *
 * @param[out] q Queue, die initialisiert werden soll.
 */
void queue_init(Queue* q)
{
    if (q == NULL) {
        return;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0U;
}

/**
 * @brief Gibt alle Knoten der Queue frei und setzt sie zurück.
 *
 * Nach dem Aufruf ist die Queue leer.
 *
 * @param[in,out] q Queue, die freigegeben werden soll.
 */
void queue_free(Queue* q)
{
    if (q == NULL) {
        return;
    }

    QueueNode* current = q->head;

    while (current != NULL) {
        QueueNode* next = current->next;
        free(current);
        current = next;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0U;
}

/**
 * @brief Fügt ein Fahrzeug hinten an die Queue an (FIFO).
 *
 * Allokiert intern einen neuen QueueNode.
 *
 * @param[in,out] q Queue, an die angehängt wird.
 * @param[in] v Fahrzeug, das eingereiht wird.
 * @return true wenn erfolgreich, false wenn Speicherallokation fehlschlägt
 *         oder q == NULL.
 */
bool queue_push(Queue* q, Vehicle v)
{
    if (q == NULL) {
        return false;
    }

    QueueNode* new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return false;
    }

    new_node->fahrzeug = v;
    new_node->next = NULL;

    if (q->tail == NULL) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }

    q->size++;
    return true;
}

/**
 * @brief Entfernt das vorderste Fahrzeug aus der Queue (FIFO).
 *
 * @param[in,out] q Queue, aus der entnommen wird.
 * @param[out] out_v Zielvariable für das entnommene Fahrzeug.
 * @return true wenn ein Element entnommen wurde, false wenn Queue leer ist
 *         oder q/out_v == NULL.
 */
bool queue_pop(Queue* q, Vehicle* out_v)
{
    if (q == NULL || out_v == NULL || q->head == NULL) {
        return false;
    }

    QueueNode* first_node = q->head;
    *out_v = first_node->fahrzeug;

    q->head = first_node->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(first_node);
    q->size--;

    return true;
}

/**
 * @brief Liefert die aktuelle Anzahl Elemente in der Queue.
 *
 * @param[in] q Queue.
 * @return Anzahl Elemente; bei q == NULL wird 0 zurückgegeben.
 */
size_t queue_size(const Queue* q)
{
    if (q == NULL) {
        return 0U;
    }

    return q->size;
}

/**
 * @brief Prüft, ob die Queue leer ist.
 *
 * @param[in] q Queue.
 * @return true wenn leer oder q == NULL, sonst false.
 */
bool queue_is_empty(const Queue* q)
{
    if (q == NULL) {
        return true;
    }

    return (q->size == 0U);
}
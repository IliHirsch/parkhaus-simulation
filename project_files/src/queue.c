#include "queue.h"
#include <stdlib.h>

void queue_init(Queue* q)
{
    /*
     * FUNCTION queue_init(q)
     * INPUT  q
     * OUTPUT q ist leere Warteschlange
     *
     * q->head <- NULL
     * q->tail <- NULL
     * q->size <- 0
     *
     * END FUNCTION
     */
}

void queue_free(Queue* q)
{
    /*
     * FUNCTION queue_free(q)
     * INPUT  q
     * OUTPUT Alle Knoten freigegeben, Queue leer
     *
     * DECLARE tmp : QueueNode*
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
}

bool queue_push(Queue* q, Vehicle v)
{
    /*
     * FUNCTION queue_push(q, v) RETURNS ok
     * INPUT  q, v
     * OUTPUT v am Ende der Queue eingefügt (FIFO)
     *
     * DECLARE node : QueueNode*
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
     *
     * RETURN true
     *
     * END FUNCTION
     */
}

bool queue_pop(Queue* q, Vehicle* out_v)
{
    /*
     * FUNCTION queue_pop(q, out_v) RETURNS ok
     * INPUT  q, out_v
     * OUTPUT Erstes Element entfernt (FIFO) und in *out_v gespeichert
     *
     * DECLARE node : QueueNode*
     *
     * IF q->head == NULL THEN
     *     RETURN false
     * END IF
     *
     * node <- q->head
     * *out_v <- node->fahrzeug
     *
     * q->head <- node->next
     *
     * IF q->head == NULL THEN
     *     q->tail <- NULL
     * END IF
     *
     * free(node)
     * q->size <- q->size - 1
     *
     * RETURN true
     *
     * END FUNCTION
     */
}

size_t queue_size(const Queue* q)
{
    /*
     * FUNCTION queue_size(q) RETURNS n
     * INPUT  q
     * OUTPUT Anzahl der Elemente in der Queue
     *
     * RETURN q->size
     *
     * END FUNCTION
     */
}

bool queue_is_empty(const Queue* q)
{
    /*
     * FUNCTION queue_is_empty(q) RETURNS empty
     * INPUT  q
     * OUTPUT true falls Queue leer, sonst false
     *
     * IF q->size == 0 THEN
     *     RETURN true
     * ELSE
     *     RETURN false
     * END IF
     *
     * END FUNCTION
     */
}
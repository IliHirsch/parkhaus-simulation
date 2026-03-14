#include<assert.h>
#include<stdio.h>
#include<stdbool.h>

#include"types.h"
#include"queue.h"

/**
 * @brief Hilfsfunktion zum Erzeugen eines Test-Fahrzeugs.
 *
 * @param[in] id Fahrzeug-ID.
 * @param[in] restparkdauer Restparkdauer.
 * @param[in] ankunftszeit Ankunftszeit.
 * @return Erzeugtes Vehicle.
 */
static Vehicle make_vehicle(unsigned int id, int restparkdauer, int ankunftszeit)
{
    Vehicle v;
    v.id = id;
    v.restparkdauer = restparkdauer;
    v.ankunftszeit = ankunftszeit;
    return v;
}

/* =========================
   queue_init
   ========================= */

/**
 * @brief Prüft, dass queue_init eine Queue korrekt leer initialisiert.
 */
static void test_queue_init_initializes_empty_queue(void)
{
    Queue q;

    queue_init(&q);

    assert(q.head == NULL);
    assert(q.tail == NULL);
    assert(q.size == 0U);
    assert(queue_is_empty(&q) == true);
}

/**
 * @brief Prüft, dass queue_init(NULL) keinen Absturz verursacht.
 */
static void test_queue_init_with_null_does_not_crash(void)
{
    queue_init(NULL);
    assert(true);
}
/* =========================
   queue_free
   ========================= */

/**
 * @brief Prüft, dass queue_free auf leerer Queue den Zustand korrekt belässt.
 */
static void test_queue_free_on_empty_queue_resets_state(void)
{
    Queue q;

    queue_init(&q);
    queue_free(&q);

    assert(q.head == NULL);
    assert(q.tail == NULL);
    assert(q.size == 0U);
    assert(queue_is_empty(&q) == true);
}

/**
 * @brief Prüft, dass queue_free alle Elemente einer befüllten Queue entfernt.
 */
static void test_queue_free_on_filled_queue_clears_all_nodes(void)
{
    Queue q;
    Vehicle v1 = make_vehicle(1U, 3, 0);
    Vehicle v2 = make_vehicle(2U, 4, 1);

    queue_init(&q);

    assert(queue_push(&q, v1) == true);
    assert(queue_push(&q, v2) == true);

    queue_free(&q);

    assert(q.head == NULL);
    assert(q.tail == NULL);
    assert(q.size == 0U);
    assert(queue_is_empty(&q) == true);
}

/* =========================
   queue_push
   ========================= */

/**
 * @brief Prüft, dass queue_push auf leerer Queue das erste Element korrekt einfügt.
 */
static void test_queue_push_on_empty_queue_inserts_first_element(void)
{
    Queue q;
    Vehicle v = make_vehicle(10U, 5, 2);

    queue_init(&q);

    assert(queue_push(&q, v) == true);
    assert(q.size == 1U);
    assert(q.head != NULL);
    assert(q.tail != NULL);
    assert(q.head == q.tail);

    assert(q.head->fahrzeug.id == 10U);
    assert(q.head->fahrzeug.restparkdauer == 5);
    assert(q.head->fahrzeug.ankunftszeit == 2);
}

/**
 * @brief Prüft, dass queue_push auf nicht-leerer Queue korrekt hinten anhängt.
 */
static void test_queue_push_on_non_empty_queue_appends_to_tail(void)
{
    Queue q;
    Vehicle v1 = make_vehicle(1U, 3, 0);
    Vehicle v2 = make_vehicle(2U, 7, 1);

    queue_init(&q);

    assert(queue_push(&q, v1) == true);
    assert(queue_push(&q, v2) == true);

    assert(q.size == 2U);
    assert(q.head != NULL);
    assert(q.tail != NULL);
    assert(q.head != q.tail);

    assert(q.head->fahrzeug.id == 1U);
    assert(q.tail->fahrzeug.id == 2U);
    assert(q.head->next == q.tail);
    assert(q.tail->next == NULL);
}

/* =========================
   queue_pop
   ========================= */

/**
 * @brief Prüft, dass queue_pop das erste Element im FIFO-Sinn entnimmt.
 */
static void test_queue_pop_returns_first_element_fifo(void)
{
    Queue q;
    Vehicle v1 = make_vehicle(1U, 3, 0);
    Vehicle v2 = make_vehicle(2U, 4, 1);
    Vehicle out;

    queue_init(&q);

    assert(queue_push(&q, v1) == true);
    assert(queue_push(&q, v2) == true);

    assert(queue_pop(&q, &out) == true);
    assert(out.id == 1U);
    assert(out.restparkdauer == 3);
    assert(out.ankunftszeit == 0);

    assert(q.size == 1U);
    assert(q.head != NULL);
    assert(q.tail != NULL);
    assert(q.head == q.tail);
    assert(q.head->fahrzeug.id == 2U);
}

/**
 * @brief Prüft, dass queue_pop auf leerer Queue false liefert.
 */
static void test_queue_pop_on_empty_queue_returns_false(void)
{
    Queue q;
    Vehicle out;

    queue_init(&q);

    assert(queue_pop(&q, &out) == false);
    assert(q.size == 0U);
    assert(q.head == NULL);
    assert(q.tail == NULL);
}

/**
 * @brief Prüft, dass queue_size bei leerer Queue 0 liefert.
 */
static void test_queue_size_of_empty_queue_is_zero(void)
{
    Queue q;

    queue_init(&q);

    assert(queue_size(&q) == 0U);
}

/**
 * @brief Prüft, dass queue_size Push- und Pop-Operationen korrekt verfolgt.
 */
static void test_queue_size_tracks_push_and_pop_operations(void)
{
    Queue q;
    Vehicle v1 = make_vehicle(1U, 3, 0);
    Vehicle v2 = make_vehicle(2U, 4, 1);
    Vehicle out;

    queue_init(&q);
    assert(queue_size(&q) == 0U);

    assert(queue_push(&q, v1) == true);
    assert(queue_size(&q) == 1U);

    assert(queue_push(&q, v2) == true);
    assert(queue_size(&q) == 2U);

    assert(queue_pop(&q, &out) == true);
    assert(queue_size(&q) == 1U);

    queue_free(&q);
}


/**
 * @brief Prüft, dass queue_is_empty bei leerer Queue true liefert.
 */
static void test_queue_is_empty_returns_true_for_empty_queue(void)
{
    Queue q;

    queue_init(&q);

    assert(queue_is_empty(&q) == true);
}

/**
 * @brief Prüft, dass queue_is_empty nach einem Push false liefert.
 */
static void test_queue_is_empty_returns_false_after_push(void)
{
    Queue q;
    Vehicle v = make_vehicle(5U, 2, 0);

    queue_init(&q);

    assert(queue_push(&q, v) == true);
    assert(queue_is_empty(&q) == false);

    queue_free(&q);
}

int main(void)
{
    test_queue_init_initializes_empty_queue();
    test_queue_init_with_null_does_not_crash();

    test_queue_free_on_empty_queue_resets_state();
    test_queue_free_on_filled_queue_clears_all_nodes();

    test_queue_push_on_empty_queue_inserts_first_element();
    test_queue_push_on_non_empty_queue_appends_to_tail();

    test_queue_pop_returns_first_element_fifo();
    test_queue_pop_on_empty_queue_returns_false();

    test_queue_size_of_empty_queue_is_zero();
    test_queue_size_tracks_push_and_pop_operations();

    test_queue_is_empty_returns_true_for_empty_queue();
    test_queue_is_empty_returns_false_after_push();

    printf("Alle Queue-Tests erfolgreich.\n");

    return 0;
}
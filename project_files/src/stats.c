#include "../include/stats.h"
#include <stdio.h>

/**
 * @brief Initialisiert alle Statistikfelder mit 0.
 *
 * @param[out] p_stats Statistikstruktur.
 */
void stats_init(Stats* p_stats)
{
    if (p_stats == NULL) {
        return;
    }

    p_stats->neu_angekommen = 0U;
    p_stats->verlassen = 0U;
    p_stats->abgefertigte_wartende = 0U;

    p_stats->belegung = 0U;
    p_stats->warteschlangenlaenge = 0U;

    p_stats->step_count = 0U;
    p_stats->sum_belegung = 0U;
    p_stats->sum_warteschlange = 0U;
    p_stats->max_warteschlange = 0U;
    p_stats->vollauslastung_steps = 0U;

    p_stats->sum_restparkdauer = 0U;
    p_stats->count_restparkdauer = 0U;

    p_stats->sum_wartezeit = 0U;
    p_stats->count_wartezeit = 0U;

    p_stats->sum_parkdauer = 0U;
    p_stats->count_parkdauer = 0U;
}

/**
 * @brief Setzt die Step-Zähler für einen neuen Simulationsschritt zurück.
 *
 * @param[in,out] p_stats Statistikstruktur.
 */
void stats_reset_step(Stats* p_stats)
{
    if (p_stats == NULL) {
        return;
    }

    p_stats->neu_angekommen = 0U;
    p_stats->verlassen = 0U;
    p_stats->abgefertigte_wartende = 0U;
}

/**
 * @brief Aktualisiert die Statistik nach einem Simulationsschritt.
 *
 * Hinweis:
 * sum_restparkdauer und count_restparkdauer werden hier bewusst als
 * Gesamtaggregat über alle bisher beobachteten Fahrzeuge geführt.
 *
 * @param[in,out] p_stats Statistikstruktur.
 * @param[in] p_parking Parkhauszustand.
 * @param[in] p_queue Warteschlange.
 * @param[in] step Aktueller Simulationsschritt (wird nicht benötigt).
 */
void stats_update_step(
    Stats* p_stats,
    const ParkingLot* p_parking,
    const Queue* p_queue,
    int step
)
{
    (void)step;

    if (p_stats == NULL || p_parking == NULL || p_queue == NULL) {
        return;
    }

    p_stats->belegung = p_parking->belegte_plaetze;
    p_stats->warteschlangenlaenge = queue_size(p_queue);

    p_stats->step_count++;
    p_stats->sum_belegung += p_stats->belegung;
    p_stats->sum_warteschlange += p_stats->warteschlangenlaenge;

    if (p_stats->warteschlangenlaenge > p_stats->max_warteschlange) {
        p_stats->max_warteschlange = p_stats->warteschlangenlaenge;
    }

    if (p_stats->belegung == p_parking->kapazitaet) {
        p_stats->vollauslastung_steps++;
    }

    for (size_t i = 0U; i < p_parking->kapazitaet; i++) {
        if (p_parking->slots[i].belegt) {
            p_stats->sum_restparkdauer += (size_t)p_parking->slots[i].fahrzeug.restparkdauer;
            p_stats->count_restparkdauer++;
        }
    }
}

/**
 * @brief Gibt die Statistik des aktuellen Simulationsschritts aus.
 *
 * Hinweis:
 * AvgRestGesamt ist mit der aktuellen Datenstruktur ein laufender Gesamtdurchschnitt
 * aller bisher gesammelten Restparkdauer-Samples und kein reiner Step-Wert.
 *
 * @param[in] p_stats Statistikstruktur.
 * @param[in] step Aktueller Simulationsschritt.
 */
void stats_print_step(const Stats* p_stats, int step)
{
    if (p_stats == NULL) {
        return;
    }

    printf("Step %d: ", step);
    printf("Belegung=%zu, ", p_stats->belegung);
    printf("Queue=%zu, ", p_stats->warteschlangenlaenge);
    printf("Neu=%zu, ", p_stats->neu_angekommen);
    printf("Verlassen=%zu, ", p_stats->verlassen);
    printf("Queue->Park=%zu", p_stats->abgefertigte_wartende);

    if (p_stats->count_restparkdauer > 0U) {
        float avg_rest =
            (float)p_stats->sum_restparkdauer / (float)p_stats->count_restparkdauer;
        printf(", AvgRestGesamt=%.2f", avg_rest);
    } else {
        printf(", AvgRestGesamt=0.00");
    }

    printf("\n");
}

/**
 * @brief Gibt die aggregierte Endstatistik auf der Konsole aus.
 *
 * @param[in] p_stats Statistikstruktur.
 */
void stats_print_final(const Stats* p_stats)
{
    if (p_stats == NULL) {
        return;
    }

    printf("\n===== FINAL STATS =====\n");

    if (p_stats->step_count == 0U) {
        printf("Keine Schritte simuliert.\n");
        return;
    }

    float avg_belegung =
        (float)p_stats->sum_belegung / (float)p_stats->step_count;
    float avg_queue =
        (float)p_stats->sum_warteschlange / (float)p_stats->step_count;
    float vollauslastung_prozent =
        ((float)p_stats->vollauslastung_steps * 100.0f) / (float)p_stats->step_count;

    printf("Ø Belegung: %.2f\n", avg_belegung);
    printf("Ø Warteschlange: %.2f\n", avg_queue);
    printf("Max Warteschlange: %zu\n", p_stats->max_warteschlange);
    printf("Vollauslastung: %.2f %% der Schritte\n", vollauslastung_prozent);

    if (p_stats->count_wartezeit > 0U) {
        float avg_wartezeit =
            (float)p_stats->sum_wartezeit / (float)p_stats->count_wartezeit;
        printf("Ø Wartezeit (Queue->Park): %.2f\n", avg_wartezeit);
    } else {
        printf("Ø Wartezeit: 0 Samples\n");
    }

    if (p_stats->count_parkdauer > 0U) {
        float avg_parkdauer =
            (float)p_stats->sum_parkdauer / (float)p_stats->count_parkdauer;
        printf("Ø Parkdauer: %.2f\n", avg_parkdauer);
    } else {
        printf("Ø Parkdauer: 0 Samples\n");
    }

    if (p_stats->count_restparkdauer > 0U) {
        float avg_restparkdauer =
            (float)p_stats->sum_restparkdauer / (float)p_stats->count_restparkdauer;
        printf("Ø Restparkdauer (Samples): %.2f\n", avg_restparkdauer);
    } else {
        printf("Ø Restparkdauer: 0 Samples\n");
    }
}
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

/**
 * @brief Liest eine Zeile von stdin in den übergebenen Puffer.
 *
 * Entfernt einen eventuell vorhandenen Zeilenumbruch am Ende.
 *
 * @param[out] buffer Zielpuffer.
 * @param[in] buffer_size Größe des Puffers.
 * @return true wenn erfolgreich gelesen wurde, sonst false.
 */
static bool read_line(char* buffer, size_t buffer_size)
{
    if (buffer == NULL || buffer_size == 0U) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    return true;
}

/**
 * @brief Liest einen int-Wert aus einer Eingabezeile.
 *
 * Akzeptiert nur vollständige gültige Ganzzahlen ohne Restzeichen.
 *
 * @param[in] prompt Ausgabetext für den Benutzer.
 * @param[out] out_value Zielvariable.
 * @return true wenn erfolgreich geparst, sonst false.
 */
static bool read_int_value(const char* prompt, int* out_value)
{
    char buffer[128];
    char* end_ptr = NULL;
    long value;

    if (prompt == NULL || out_value == NULL) {
        return false;
    }

    printf("%s", prompt);

    if (!read_line(buffer, sizeof(buffer))) {
        return false;
    }

    if (buffer[0] == '\0') {
        return false;
    }

    errno = 0;
    value = strtol(buffer, &end_ptr, 10);

    if (errno != 0 || end_ptr == buffer || *end_ptr != '\0') {
        return false;
    }

    if (value < INT_MIN || value > INT_MAX) {
        return false;
    }

    *out_value = (int)value;
    return true;
}

/**
 * @brief Liest einen unsigned int-Wert aus einer Eingabezeile.
 *
 * Akzeptiert nur vollständige gültige nichtnegative Ganzzahlen ohne Restzeichen.
 *
 * @param[in] prompt Ausgabetext für den Benutzer.
 * @param[out] out_value Zielvariable.
 * @return true wenn erfolgreich geparst, sonst false.
 */
static bool read_unsigned_int_value(const char* prompt, unsigned int* out_value)
{
    char buffer[128];
    char* end_ptr = NULL;
    unsigned long value;

    if (prompt == NULL || out_value == NULL) {
        return false;
    }

    printf("%s", prompt);

    if (!read_line(buffer, sizeof(buffer))) {
        return false;
    }

    if (buffer[0] == '\0') {
        return false;
    }

    errno = 0;
    value = strtoul(buffer, &end_ptr, 10);

    if (errno != 0 || end_ptr == buffer || *end_ptr != '\0') {
        return false;
    }

    if (value > UINT_MAX) {
        return false;
    }

    *out_value = (unsigned int)value;
    return true;
}

/**
 * @brief Liest einen size_t-Wert aus einer Eingabezeile.
 *
 * Akzeptiert nur vollständige gültige nichtnegative Ganzzahlen ohne Restzeichen.
 *
 * @param[in] prompt Ausgabetext für den Benutzer.
 * @param[out] out_value Zielvariable.
 * @return true wenn erfolgreich geparst, sonst false.
 */
static bool read_size_value(const char* prompt, size_t* out_value)
{
    char buffer[128];
    char* end_ptr = NULL;
    unsigned long long value;

    if (prompt == NULL || out_value == NULL) {
        return false;
    }

    printf("%s", prompt);

    if (!read_line(buffer, sizeof(buffer))) {
        return false;
    }

    if (buffer[0] == '\0') {
        return false;
    }

    errno = 0;
    value = strtoull(buffer, &end_ptr, 10);

    if (errno != 0 || end_ptr == buffer || *end_ptr != '\0') {
        return false;
    }

    if (value > SIZE_MAX) {
        return false;
    }

    *out_value = (size_t)value;
    return true;
}

/**
 * @brief Liest alle Simulationsparameter über das Terminal ein.
 *
 * Erwartet Eingaben für Kapazität, maximale Parkdauer,
 * Simulationsdauer, Ankunftswahrscheinlichkeit und Seed.
 * Danach werden die Werte mit config_validate() geprüft.
 *
 * @param[out] cfg Zielstruktur für die eingelesenen Parameter.
 * @return true wenn Eingaben und Validierung erfolgreich sind,
 *         sonst false.
 */
bool config_read_from_terminal(SimConfig* cfg)
{
    if (cfg == NULL) {
        return false;
    }

    if (!read_size_value("Anzahl Stellplaetze: ", &cfg->anzahl_stellplaetze)) {
        return false;
    }

    if (!read_int_value("Max. Parkdauer (in Zeitschritten): ", &cfg->max_parkdauer)) {
        return false;
    }

    if (!read_int_value("Simulationsdauer (Anzahl Zeitschritte): ", &cfg->sim_dauer_zeitschritte)) {
        return false;
    }

    if (!read_int_value("Ankunftswahrscheinlichkeit pro Zeitschritt (0..100): ",
                        &cfg->ankunft_wahrscheinlichkeit_prozent)) {
        return false;
    }

    if (!read_unsigned_int_value("Seed (Zufallszahlengenerator): ", &cfg->seed)) {
        return false;
    }

    return config_validate(cfg);
}

/**
 * @brief Prüft die Gültigkeit der Simulationsparameter.
 *
 * @param[in] cfg Zeiger auf die Konfiguration.
 * @return true wenn alle Werte gültig sind, sonst false.
 */
bool config_validate(const SimConfig* cfg)
{
    if (cfg == NULL) {
        return false;
    }

    if (cfg->anzahl_stellplaetze == 0U) {
        return false;
    }

    if (cfg->max_parkdauer <= 0) {
        return false;
    }

    if (cfg->sim_dauer_zeitschritte <= 0) {
        return false;
    }

    if (cfg->ankunft_wahrscheinlichkeit_prozent < 0 ||
        cfg->ankunft_wahrscheinlichkeit_prozent > 100) {
        return false;
    }

    return true;
}
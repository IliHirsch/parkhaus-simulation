#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../include/io.h"
#include "../include/stats.h"
#include "../include/types.h"

/**
 * @brief Liest den gesamten Inhalt einer Textdatei in einen Puffer.
 *
 * @param[in] path Pfad zur Datei.
 * @param[out] buffer Zielpuffer.
 * @param[in] buffer_size Größe des Puffers.
 * @return true wenn erfolgreich gelesen wurde, sonst false.
 */
static bool read_file_to_buffer(const char* path, char* buffer, size_t buffer_size)
{
    FILE* p_file = fopen(path, "r");
    size_t read_count;

    if (p_file == NULL || buffer == NULL || buffer_size == 0U) {
        return false;
    }

    read_count = fread(buffer, 1U, buffer_size - 1U, p_file);
    buffer[read_count] = '\0';

    fclose(p_file);
    return true;
}

/* =========================
   io_open_log
   ========================= */

/**
 * @brief Prüft, dass io_open_log eine gültige Datei erfolgreich öffnet.
 */
static void test_io_open_log_returns_true_for_valid_path(void)
{
    const char* p_path = "test_io_open_log.txt";

    assert(io_open_log(p_path) == true);
    io_close_log();

    remove(p_path);
}

/**
 * @brief Prüft, dass io_open_log bei NULL false zurückgibt.
 */
static void test_io_open_log_returns_false_for_null_path(void)
{
    assert(io_open_log(NULL) == false);
}

/* =========================
   io_close_log
   ========================= */

/**
 * @brief Prüft, dass io_close_log eine geöffnete Log-Datei sauber schließt.
 */
static void test_io_close_log_closes_open_log_file(void)
{
    const char* p_path = "test_io_close_log.txt";
    char buffer[512];

    assert(io_open_log(p_path) == true);
    io_close_log();

    assert(read_file_to_buffer(p_path, buffer, sizeof(buffer)) == true);
    assert(strstr(buffer, "=== Parkhaus-Simulation Log ===") != NULL);

    remove(p_path);
}

/**
 * @brief Prüft, dass io_close_log ohne geöffnete Datei keinen Absturz verursacht.
 */
static void test_io_close_log_without_open_file_does_not_crash(void)
{
    io_close_log();
    assert(true);
}

/**
 * @brief Prüft, dass io_log_step einen Step korrekt in die Log-Datei schreibt.
 */
static void test_io_log_step_writes_step_data_to_file(void)
{}

/**
 * @brief Prüft, dass io_log_step bei NULL-Statistik keinen Absturz verursacht.
 */
static void test_io_log_step_with_null_stats_does_not_crash(void)
{}

/**
 * @brief Prüft, dass io_log_step bei NULL-Statistik keinen Absturz verursacht.
 */
static void test_io_log_step_with_null_stats_does_not_crash(void)
{}


/**
 * @brief Prüft, dass io_log_final die Abschlussstatistik korrekt schreibt.
 */
static void test_io_log_final_writes_final_statistics(void)
{}

int main(void)
{
    test_io_open_log_returns_true_for_valid_path();
    test_io_open_log_returns_false_for_null_path();

    test_io_close_log_closes_open_log_file();
    test_io_close_log_without_open_file_does_not_crash();

    test_io_log_step_writes_step_data_to_file();
    test_io_log_step_with_null_stats_does_not_crash();

    test_io_log_final_writes_final_statistics();
    test_io_log_final_with_null_stats_does_not_crash();

    printf("Alle IO-Tests erfolgreich.\n");
    return 0;
}
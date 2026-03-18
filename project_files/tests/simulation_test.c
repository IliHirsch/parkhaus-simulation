#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../include/simulation.h"
#include "../include/config.h"

/**
 * @brief Prüft, ob eine Datei existiert.
 *
 * @param[in] path Pfad zur Datei.
 * @return true wenn die Datei geöffnet werden kann, sonst false.
 */
static bool file_exists(const char* path){
    FILE* p_file = fopen(path, "r");
    if (p_file == NULL){
        return false;
    }

    fclose(p_file);
    return true;
}

/**
 * @brief Liest den Inhalt einer Datei in einen Puffer.
 *
 * @param[in] path Pfad zur Datei.
 * @param[out] buffer Zielpuffer.
 * @param[in] buffer_size Größe des Puffers.
 * @return true wenn erfolgreich gelesen wurde, sonst false.
 */
static bool read_file_to_buffer(const char* path, char* buffer, size_t buffer_size){
    FILE* p_file = fopen(path, "r");
    size_t read_count;
    if (p_file == NULL || buffer == NULL || buffer_size == 0U){
        return false;
    }

    read_count = fread(buffer, 1U, buffer_size - 1U, p_file);
    buffer[read_count] = '\0';
    fclose(p_file);
    return true;
}

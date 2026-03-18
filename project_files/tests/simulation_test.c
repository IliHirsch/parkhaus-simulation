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
static bool file_exists(const char* path)
{
    FILE* p_file = fopen(path, "r");
    if (p_file == NULL) {
        return false;
    }

    fclose(p_file);
    return true;
}

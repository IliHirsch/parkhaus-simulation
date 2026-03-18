#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../include/config.h"

/**
 * @brief Schreibt Text in eine Datei.
 *
 * @param[in] path Pfad zur Datei.
 * @param[in] text Inhalt, der geschrieben werden soll.
 * @return true wenn erfolgreich geschrieben wurde, sonst false.
 */
static bool write_text_file(const char* path, const char* text){
    FILE* p_file = fopen(path, "w");
    if (p_file == NULL){
        return false;
    }

    if (fputs(text, p_file) == EOF){
        fclose(p_file);
        return false;
    }

    fclose(p_file);
    return true;
}
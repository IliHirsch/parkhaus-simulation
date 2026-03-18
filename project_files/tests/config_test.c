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

/**
 * @brief Leitet stdin auf eine Datei um.
 *
 * @param[in] path Pfad zur Eingabedatei.
 * @return true wenn stdin erfolgreich umgeleitet wurde, sonst false.
 */
static bool redirect_stdin_to_file(const char* path){
    FILE* p_file = freopen(path, "r", stdin);
    return (p_file != NULL);
}

/* =========================
   config_validate
   ========================= */

static void test_cfg_val_valid(void){
    SimConfig cfg;
    cfg.anzahl_stellplaetze = 10U;
    cfg.max_parkdauer = 5;
    cfg.sim_dauer_zeitschritte = 20;
    cfg.ankunft_wahrscheinlichkeit_prozent = 50;
    cfg.seed = 123U;

    assert(config_validate(&cfg) == true);
}

static void test_cfg_val_invalid_prob(void){
    SimConfig cfg;
    cfg.anzahl_stellplaetze = 10U;
    cfg.max_parkdauer = 5;
    cfg.sim_dauer_zeitschritte = 20;
    cfg.ankunft_wahrscheinlichkeit_prozent = 150;
    cfg.seed = 123U;

    assert(config_validate(&cfg) == false);
}

/* =========================
   config_read_from_terminal
   ========================= */

static void test_cfg_read_valid(void){
    const char* p_path = "test_config_valid_input.txt";
    SimConfig cfg;

    assert(write_text_file(p_path, "12\n7\n30\n40\n99\n") == true);
    assert(redirect_stdin_to_file(p_path) == true);

    assert(config_read_from_terminal(&cfg) == true);

    assert(cfg.anzahl_stellplaetze == 12U);
    assert(cfg.max_parkdauer == 7);
    assert(cfg.sim_dauer_zeitschritte == 30);
    assert(cfg.ankunft_wahrscheinlichkeit_prozent == 40);
    assert(cfg.seed == 99U);

    remove(p_path);
}
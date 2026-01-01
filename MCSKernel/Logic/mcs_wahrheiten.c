#include "mcs_wahrheiten.h"
#include <stdio.h>
#include <string.h>

void mcs_wahrheiten_process(const char *label, const char *value) {
    // –< Vergleich (Parallel-Prozess)
    if (strcmp(label, "Quit") == 0) {
        mcs_progress_operator(1, 100);
        printf(" [~QUIT_APPLICATION~]\n");
    } else if (strcmp(label, "About") == 0) {
        mcs_progress_operator(2, 70);
        printf(" [~SHOW_ABOUT_DIALOG~]\n");
    } else if (strcmp(label, "Einstellungen") == 0) {
        mcs_progress_operator(3, 50);
        printf(" [~OPEN_SETTINGS~]\n");
    } else if (strcmp(label, "Export") == 0) {
        mcs_progress_operator(4, 80);
        printf(" [~EXPORT_DATA~]\n");
    } else if (strcmp(label, "Import") == 0) {
        mcs_progress_operator(5, 100);
        printf(" [~IMPORT_DATA~]\n");
    } // –> Default
    else {
        mcs_progress_operator(5, 0);
        printf(" [UNBEKANNTER MENÜPUNKT]\n");
    }
}

void mcs_progress_operator(int level, int percent) {
    // Dynamischer Balken (# basierend auf Feed/AI)
    printf("--%*s: %*s %d%% GELADEN", level, "·····", percent / 4, "###############################", percent);
}

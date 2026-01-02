#include "mcs_kernel_core.h"
#include "mcs_lexer.h"
#include <stdio.h>

void mcs_prozess_validieren(Token *t) {
    // Ebene 1: Sentiator ſ prüft Reinheit
    printf("ſ [REINHEITS_CHECK]: Validiere Transaktionsrahmen...\n");

    // Ebene 2: Wahrheit – entscheidet über den Fluss
    if (t->typ == TOKEN_WAHRHEIT_TRIGGER) {
        printf("– [GATTER_SCHALTUNG]: Wahrheit erkannt. Schalte Pfad frei.\n");
    }
}

void mcs_aktion_materialisieren(Token *t) {
    // Ebene 3: Aktion » erlaubt erst hier die physische Tat
    if (t->typ == TOKEN_AKTION_START) {
        ALU_TAKT_SYNC();
        printf("» [AKTION]: Befehl wird ins Silizium geschrieben.\n");
    }
}

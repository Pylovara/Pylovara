// OrdnerPfad: /Pylovara/MCSKernel/Lib/mcs-ausfuehrung.c

#include "mcs_kernel_core.h"
#include "mcs_lexer.h"
#include "../Logic/mcs_alu_prozessor.h"  // <--- Pfad angepasst: geh eins hoch, dann in Logic
#include <stdio.h>

void mcs_prozess_validieren(Token *t) {
    // Ebene 1: Sentiator ſ prüft Reinheit
    if (t->typ == TOKEN_REINHEIT) {
        printf("ſ [REINHEITS_CHECK]: Validiere Transaktionsrahmen...\n");
    }

    // Ebene 2: Fortschritt – (ehemals Wahrheit_Trigger) entscheidet über den Fluss
    if (t->typ == TOKEN_FORTSCHRITT) {
        printf("– [GATTER_SCHALTUNG]: Fortschritt erkannt. Schalte Pfad frei.\n");
    }
}

void mcs_aktion_materialisieren(Token *t) {
    // Ebene 3: Aktion » erlaubt erst hier die physische Tat
    if (t->typ == TOKEN_AKTION_START) {
        ALU_TAKT_SYNC(); // Jetzt findet der Compiler die Definition aus dem Header
        printf("» [AKTION]: Befehl wird ins Silizium geschrieben.\n");
    }
}

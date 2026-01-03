// Logic/mcs_sentiatoren.c
#include "mcs_sentiator.h"
#include "mcs_register.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hilfsfunktion: Holt den aktuellen Status aus dem FEED-CACHE (Reg 0)
static int hole_aktuelle_wahrheit() {
    const char* wert = mcs_register_hole(0);
    if (!wert || strcmp(wert, "0") == 0 || strlen(wert) == 0) return 0;
    return 1; // Alles außer "0" oder leer gilt als WAHR
}

int mcs_sentiator_entscheide(int typ, const char* optionaler_wert) {
    int wahrheit = hole_aktuelle_wahrheit();

    switch(typ) {
        case 1: // ¶ SENTIATOR-KANN-IMPULS
            return wahrheit;

        case 2: // ¶¶ SENTIATOR-NICHT-IMPULS
            return !wahrheit;

        case 3: // ! SENTIATOR-MATCH-IMPULS
            // Prüft ob der Cache exakt dem optionalen Wert entspricht
            return (strcmp(mcs_register_hole(0), optionaler_wert) == 0);

        case 4: // ŧ SENTIATOR-BOXICHECK-IMPULS
            // Prüft auf VAKUUM (Leerer Boxi)
            return (strlen(mcs_register_hole(0)) == 0);

        case 5: // ſ SENTIATOR-REINHEIT-IMPULS
            // Wenn Datenmüll erkannt wird (hier simuliert)
            if (strstr(mcs_register_hole(0), "ERR")) return 1;
            return 0;

        default:
            return 0;
    }
    // OrdnerPfad: /Pylovara/MCSKernel/Logic/mcs_sentiator.c
    // Name: AIMS-Handshake-Validierung

    #include "mcs_register.h"

    // @kernel-nr: 03 | MCS-Typ: hnd- | Konsens-Typ
    // Funktion: Abgleich der Signaturen zur System-Integrität [cite: 211, 215]
    int ALU_AIMS_HANDSHAKE(long protein_signatur) {
        // Prüft, ob der Konsens (128-Bit Ebene simuliert) vorliegt [cite: 211]
        if (protein_signatur != 0) {
            printf("   [AIMS-HANDSHAKE]: Konsens validiert (þ10) [cite: 213, 251]\n");
            return 1; // Signalfluss erlaubt
        }
        printf("   [ALARM]: Konsens-Fehler! Gatter gesperrt. \n");
        return 0;
    }
    // Hier endet die Funktion ALU_AIMS_HANDSHAKE [cite: 58]




}

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
}

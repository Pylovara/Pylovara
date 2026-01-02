#include "mcs_sentiator.h"
#include "mcs_register.h"
#include "mcs_wahrheiten.h"
#include <stdio.h>

// Prüft die Reinheit basierend auf dem letzten ALU-Takt
int mcs_sentiator_entscheide(int typ) {
    int wahrheit = mcs_check_bedingung_aus_alu();

    if (typ == 1) { // ¶ (Kann/If)
        return wahrheit;
    } else {        // ¶¶ (Nicht/Else)
        return !wahrheit;
    }
}

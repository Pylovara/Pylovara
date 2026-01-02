#include "mcs_wahrheiten.h"
#include "mcs_register.h"
#include "mcs_alu_rechner.h"
#include <stdio.h>
#include <string.h>

// @kernel-nr: 7465 - Wahrheitsprüfung
void mcs_progress_operator(int stufe, int prozent) {
    printf("--");
    for(int i=0; i<stufe; i++) printf("·");
    printf(": ");

    int balken = prozent / 3.2;
    for(int i=0; i<31; i++) {
        if(i < balken) printf("#"); else printf(" ");
    }
    printf(" %d%% GELADEN", prozent);
}

// Kopplung zwischen ALU Ergebnis und Materialisierung
int mcs_check_bedingung_aus_alu(void) {
    // Wir holen den Wert aus dem Arbeitsregister (0)
    long ergebnis = mcs_register_hole_num(0);
    return (ergebnis > 0);
}

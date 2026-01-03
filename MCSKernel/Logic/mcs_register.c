// OrdnerPfad: /Pylovara/MCSKernel/Logic/mcs_register.c
// Name: Register-Protein-Bindung (Stabilisierte Version)
// Chat-Code: §7465

#include "mcs_register.h"
#include "mcs_alu_prozessor.h"
#include "mcs_kernel_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Das physische Register-Gatter
static long MCS_REGISTER_GATTER[17];

void ALU_REINIGEN_B64() {
    for (int i = 0; i <= 16; i++) MCS_REGISTER_GATTER[i] = 0;
    asm volatile ("mfence" ::: "memory");
}

void ALU_REGISTER_BINDEN(int reg_nr, long wert) {
    if (reg_nr >= 0 && reg_nr <= 16) {
        MCS_REGISTER_GATTER[reg_nr] = wert;
        printf("    [FEED-SYNC]: FF(%d) <- b64(%ld)\n", reg_nr, wert);
    }
}

long mcs_register_extrahiere_protein(int reg_nr) {
    return (reg_nr >= 0 && reg_nr <= 16) ? MCS_REGISTER_GATTER[reg_nr] : 0;
}

// --- Die stabilisierte Brücke mit Auto-Slot-Finder ---
void mcs_register_setze(int reg_nr, const char *wert_str) {
    if (wert_str == NULL) return;
    long wert = atol(wert_str);

    int ziel_reg = reg_nr;

    // Falls der Parser 0 liefert, suchen wir den ersten freien Slot von 1-16
    if (reg_nr == 0) {
        for (int i = 1; i <= 16; i++) {
            if (MCS_REGISTER_GATTER[i] == 0) {
                ziel_reg = i;
                break;
            }
        }
    }

    MCS_REGISTER_GATTER[ziel_reg] = wert;
    printf("    [TRANS-OK]: Protein %ld fest an FF(%d) gebunden.\n", wert, ziel_reg);
}

char * mcs_register_hole(int reg_nr) {
    static char puffer[32];
    snprintf(puffer, sizeof(puffer), "%ld", mcs_register_extrahiere_protein(reg_nr));
    return puffer;
}

long mcs_register_hole_num(int reg_nr) {
    return mcs_register_extrahiere_protein(reg_nr);
}

int ALU_AIMS_HANDSHAKE(long impuls) {
    return (impuls >= 0);
}

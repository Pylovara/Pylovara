// OrdnerPfad: /Pylovara/MCSKernel/Logic/mcs_register.c
// Name: Register-Protein-Bindung
// Chat-Code: §7465

#include "mcs_register.h"
#include "mcs_alu_prozessor.h"
#include "mcs_kernel_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// @kernel-nr: 990 | MCS-CMD-REGISTER
// Das physische Register-Gatter (Speicherzellen für 16 Feeds + System-FF 0)
static long MCS_REGISTER_GATTER[17];

/**
 * ALU_REINIGEN_B64
 * Leert alle Registerzellen und setzt Hardware-Barriere.
 */
void ALU_REINIGEN_B64() {
    for (int i = 0; i <= 16; i++) {
        MCS_REGISTER_GATTER[i] = 0;
    }
    asm volatile ("mfence" ::: "memory");
}

// --- Kern-Logik (ALU-Ebene arbeitet mit Long) ---

/**
 * ALU_REGISTER_BINDEN
 * Direkte Bindung eines Long-Wertes an ein Gatter.
 */
void ALU_REGISTER_BINDEN(int reg_nr, long wert) {
    if (reg_nr >= 0 && reg_nr <= 16) {
        MCS_REGISTER_GATTER[reg_nr] = wert;
        printf("    [FEED-SYNC]: FF(%d) <- b64(%ld)\n", reg_nr, wert);
    }
}

/**
 * mcs_register_extrahiere_protein
 * Holt den Long-Wert direkt aus der Hardware-Zelle.
 */
long mcs_register_extrahiere_protein(int reg_nr) {
    if (reg_nr >= 0 && reg_nr <= 16) {
        return MCS_REGISTER_GATTER[reg_nr];
    }
    return 0;
}

// --- Linker-Brücken (Kompabilität mit dem Kernel-Core) ---

/**
 * mcs_register_setze
 * Brücke: Wandelt Shell-Outputs (Strings) in ALU-Proteine (Long) um.
 * Korrigiert das FF(0) Adressierungsproblem.
 */
void mcs_register_setze(int reg_nr, const char *wert_str) {
    if (wert_str != NULL && reg_nr >= 0 && reg_nr <= 16) {
        long wert = atol(wert_str);

        // Direkte Gatter-Zuweisung
        MCS_REGISTER_GATTER[reg_nr] = wert;

        // Klare Diagnose für den Takt-Monitor
        printf("    [TRANS-OK]: Protein %ld fest an FF(%d) gebunden.\n", wert, reg_nr);
    }
}

/**
 * mcs_register_hole
 * Brücke: Gibt den Gatter-Inhalt als String an den Kernel zurück.
 */
char * mcs_register_hole(int reg_nr) {
    static char puffer[32];
    long wert = mcs_register_extrahiere_protein(reg_nr);
    snprintf(puffer, sizeof(puffer), "%ld", wert);
    return puffer;
}

/**
 * mcs_register_hole_num
 * Numerischer Direktzugriff für Wahrheits-Prüfungen.
 */
long mcs_register_hole_num(int reg_nr) {
    return mcs_register_extrahiere_protein(reg_nr);
}

/**
 * ALU_AIMS_HANDSHAKE
 * System-Integritätsprüfung (Requirement §7465).
 */
int ALU_AIMS_HANDSHAKE(long impuls) {
    // Validierung des Takt-Impulses
    if (impuls >= 0) {
        return 1;
    }
    return 0;
}

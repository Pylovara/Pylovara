#include "mcs_register.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Die physische Registerbank
MCSRegister reg_bank[MAX_REGISTERS];

// Master-Sicherheitsstufe (Default 1, Zimmermann = 10)
int mcs_aktuelle_sicherheitsstufe = 1;

void mcs_register_init(void) {
    for(int i = 0; i < MAX_REGISTERS; i++) {
        reg_bank[i].besetzt = 0;
        reg_bank[i].numerisch = 0;
        memset(reg_bank[i].wert, 0, 1024);
    }
    // Sicherheitsstufe auf Basis-Level setzen
    mcs_aktuelle_sicherheitsstufe = 1;
}

// @kernel-nr: 99 - Sicherheitsstufen-Validierung (þ)
int mcs_sicherheit_check(int erforderliche_stufe) {
    if (mcs_aktuelle_sicherheitsstufe >= erforderliche_stufe) {
        return 1;
    }
    printf("   [SICHERHEITS-ALARM]: Zugriff þ%d verweigert! Aktuell: þ%d\n",
           erforderliche_stufe, mcs_aktuelle_sicherheitsstufe);
    return 0;
}

void mcs_register_setze(int id, const char* wert) {
    if (id >= 0 && id < MAX_REGISTERS) {
        strncpy(reg_bank[id].wert, wert, 1023);
        reg_bank[id].besetzt = 1;
        reg_bank[id].numerisch = atol(wert);

        // Debug-Ausgabe im Pylovara-Stil
        printf("   [FEED-CACHE (%d) AKTUALISIERT]: %s\n", id, wert);
    }
}

char* mcs_register_hole(int id) {
    if (id >= 0 && id < MAX_REGISTERS && reg_bank[id].besetzt) {
        return reg_bank[id].wert;
    }
    return "";
}

long mcs_register_hole_num(int id) {
    if (id >= 0 && id < MAX_REGISTERS && reg_bank[id].besetzt) {
        return reg_bank[id].numerisch;
    }
    return 0;
}

// @kernel-nr: 99 - Spezial-Klasse: Regel der Reinheit (ſ)
void mcs_regel_der_reinheit(void) {
    printf("   [ſ] REGEL-DER-REINHEIT AKTIVIERT: Lösche Transaktions-Caches...\n");
    for(int i = 0; i < 10; i++) { // Löscht die ersten 10 Arbeitsregister
        reg_bank[i].besetzt = 0;
        memset(reg_bank[i].wert, 0, 1024);
    }
}

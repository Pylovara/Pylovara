#include "mcs_register.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

MCSRegister reg_bank[MAX_REGISTERS];

void mcs_register_init(void) {
    for(int i = 0; i < MAX_REGISTERS; i++) {
        reg_bank[i].besetzt = 0;
        reg_bank[i].numerisch = 0;
        memset(reg_bank[i].wert, 0, 1024);
    }
}

void mcs_register_setze(int id, const char* wert) {
    if (id >= 0 && id < MAX_REGISTERS) {
        strncpy(reg_bank[id].wert, wert, 1023);
        reg_bank[id].besetzt = 1;
        reg_bank[id].numerisch = atol(wert);
        printf("   [REGISTER (%d) GESPEICHERT]: %s\n", id, wert);
    }
}

// Diese Funktion heißt bei dir 'mcs_register_hole'
char* mcs_register_hole(int id) {
    if (id >= 0 && id < MAX_REGISTERS && reg_bank[id].besetzt) {
        return reg_bank[id].wert;
    }
    return "";
}

// Korrigierte numerische Abfrage
long mcs_register_hole_num(int id) {
    if (id >= 0 && id < MAX_REGISTERS && reg_bank[id].besetzt) {
        return reg_bank[id].numerisch;
    }
    return 0;
}

// mcs_register.c
#include "mcs_register.h"
#include <stdio.h>
#include <string.h>

void mcs_befehl_ausfuehren(const char* befehl) {
    if (strcmp(befehl, "~löschung~") == 0) {
        printf("Sentiator ſ: Starte atomare Bereinigung...\n");
        ALU_REINIGEN();
    } else if (strcmp(befehl, "~ausführung~") == 0) {
        printf("Aktion »: Prozess wird materialisiert.\n");
    }
}

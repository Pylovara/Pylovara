#include "mcs_lexer.h"
#include "mcs_kernel_core.h"
#include "mcs_wahrheiten.h"
#include "mcs_cmd_register.h"
#include <stdio.h>
#include <stdlib.h>

// Hilfsfunktion zum Laden der .mcs Datei in den Speicher
char* mcs_datei_laden(const char *dateiname) {
    FILE *f = fopen(dateiname, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    string[fsize] = 0;
    return string;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("PYLOVARA MCS KERNEL v4.6 - STATUS: BEREIT\n");
        return 1;
    }

    char *quellcode = mcs_datei_laden(argv[1]);
    if (!quellcode) {
        printf("❌ Fehler beim Laden von %s\n", argv[1]);
        return 1;
    }

    // Der Kernel regelt seinen Takt jetzt komplett selbst über mcs_kernel_takt
    mcs_kernel_takt(quellcode);

    free(quellcode);
    return 0;
}

//#include <gtk/gtk.h>  // Kommentiere aus
#include "mcs_wahrheiten.h"
#include "mcs_sentiator.h"
#include "mcs_cmd_register.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./mcs <mcs_file.mcs>\n");
        return 1;
    }

    mcs_transaktion_start();

    // Platzhalter für mcs_parse_and_execute(argv[1]);
    printf("MCS-Datei geladen: %s\n", argv[1]);
    mcs_wahrheiten_process("Quit", "test");  // Test-Aufruf

    mcs_regel_der_reinheit();
    return 0;
}

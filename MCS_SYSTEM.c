#include <stdio.h>

void MCS_SYSTEM(void) {
    unsigned char RUN_FLAG = 1;

    while (RUN_FLAG) {
        printf("> ");              
        char buffer[128];
        if (!fgets(buffer, sizeof(buffer), stdin)) break;

        if (buffer[0] == 'q') {
            RUN_FLAG = 0;       
        } else {
            printf("Befehl: %s", buffer);
        }
    }
}

int main(void) {
    MCS_SYSTEM();
    return 0;
}

BITS 64
DEFAULT REL

section .text
global efi_main
extern MCS_SYSTEM        ; Verweis auf die gemeinsame C-Funktion

efi_main:
    call MCS_SYSTEM      ; ENTRY
.hang:
    jmp .hang

#include "mcs_alu_rechner.h"
#include "mcs_register.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long mcs_alu_berechne(const char *ausdruck) {
    // 1. Spezialfall: Wahrheits-Keywords
    if (strcmp(ausdruck, "true") == 0 || strcmp(ausdruck, "valid") == 0) return 1;
    if (strcmp(ausdruck, "false") == 0 || strcmp(ausdruck, "error") == 0) return 0;

    // 2. String-Logik (für Validierung)
    if (strstr(ausdruck, " ! ")) {
        char links[64], rechts[64];
        if (sscanf(ausdruck, "%s ! %s", links, rechts) == 2) {
            const char* val_links = (links[0] == '(') ? mcs_register_hole(atoi(&links[1])) : links;
            // Entferne Anführungszeichen falls vorhanden
            if (rechts[0] == '"') {
                rechts[strlen(rechts)-1] = '\0';
                return (strcmp(val_links, &rechts[1]) != 0);
            }
            return (strcmp(val_links, rechts) != 0);
        }
    }

    // 3. Standard Mathematik (vorhandene Logik)
    char *ptr;
    long a = 0, b = 0;

    // Einfache Register-Ersetzung für (n)
    if (ausdruck[0] == '(') {
        a = atol(mcs_register_hole(atoi(&ausdruck[1])));
    } else {
        a = strtol(ausdruck, &ptr, 10);
    }

    if (strstr(ausdruck, " > ")) {
        ptr = strstr(ausdruck, " > ") + 3;
        if (ptr[0] == '(') b = atol(mcs_register_hole(atoi(&ptr[1])));
        else b = atol(ptr);
        return a > b;
    }

    if (strstr(ausdruck, " < ")) {
        ptr = strstr(ausdruck, " < ") + 3;
        if (ptr[0] == '(') b = atol(mcs_register_hole(atoi(&ptr[1])));
        else b = atol(ptr);
        return a < b;
    }

    // Unterstützung für Multiplikation/Division (dein 10*1024*1024)
    if (strstr(ausdruck, "*")) {
        ptr = strstr(ausdruck, "*") + 1;
        return a * atol(ptr);
    }

    return a;
}

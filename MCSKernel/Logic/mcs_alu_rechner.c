#include "mcs_alu_rechner.h"
#include "mcs_register.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Hilfsfunktion: Extrahiert nur Ziffern und wandelt in long um (Reinheitsgebot)
static long mcs_alu_get_val(const char *s) {
    if (!s) return 0;
    const char *raw_val = NULL;
    char clean_buffer[64];

    // 1. Register-Verweis auflösen
    if (s[0] == '(') {
        int reg_nr = atoi(s + 1);
        raw_val = mcs_register_hole(reg_nr);
    } else {
        raw_val = s;
    }

    if (!raw_val) return 0;

    // 2. REINHEIT: Nur Ziffern extrahieren (entfernt \n, Leerzeichen, Text)
    int j = 0;
    for (int i = 0; raw_val[i] != '\0' && j < 63; i++) {
        if (isdigit(raw_val[i])) {
            clean_buffer[j++] = raw_val[i];
        }
    }
    clean_buffer[j] = '\0';

    if (j == 0) return 0;
    return atol(clean_buffer);
}

long mcs_alu_berechne(const char *ausdruck) {
    if (!ausdruck) return 0;

    // 1. Wahrheiten-Check (Konstanten)
    if (strcmp(ausdruck, "true") == 0 || strcmp(ausdruck, "valid") == 0) return 1;
    if (strcmp(ausdruck, "false") == 0 || strcmp(ausdruck, "error") == 0) return 0;

    // 2. String-Vergleich (Ungleich-Operator '!')
    if (strstr(ausdruck, " ! ")) {
        char s1[64], op[8], s2[64];
        if (sscanf(ausdruck, "%63s %7s %63s", s1, op, s2) == 3) {
            const char* val1 = (s1[0] == '(') ? mcs_register_hole(atoi(&s1[1])) : s1;
            // Entferne Anführungszeichen falls vorhanden
            const char* compare_val = s2;
            if (s2[0] == '"') compare_val = s2 + 1;

            char clean_s2[64];
            strcpy(clean_s2, compare_val);
            if (clean_s2[strlen(clean_s2)-1] == '"') clean_s2[strlen(clean_s2)-1] = '\0';

            if (!val1) return 1; // Wenn Register leer, ist es ungleich dem String
            return (strcmp(val1, clean_s2) != 0);
        }
    }

    // 3. Komplexe Mathematik (Multiplikation mit Reinheits-Check)
    if (strchr(ausdruck, '*')) {
        long res = 1;
        char temp[256];
        strncpy(temp, ausdruck, 255);
        char *token = strtok(temp, "*");
        while (token) {
            // Nutze mcs_alu_get_val für jedes Teilstück!
            res *= mcs_alu_get_val(token);
            token = strtok(NULL, "*");
        }
        return res;
    }

    // 4. Numerische Vergleiche (z.B. (1) > (2) oder (2) < 30)
    char s1[64], op[8], s2[64];
    // Wir prüfen auf die Operatoren im String
    const char* ops[] = {">", "<", "==", "!="};
    for(int i=0; i<4; i++) {
        char* op_pos = strstr(ausdruck, ops[i]);
        if (op_pos) {
            // Teile den String manuell am Operator für höhere Robustheit
            char left[64] = {0}, right[64] = {0};
            int op_len = strlen(ops[i]);

            strncpy(left, ausdruck, op_pos - ausdruck);
            strcpy(right, op_pos + op_len);

            long v1 = mcs_alu_get_val(left);
            long v2 = mcs_alu_get_val(right);

            if (i == 0) return v1 > v2;
            if (i == 1) return v1 < v2;
            if (i == 2) return v1 == v2;
            if (i == 3) return v1 != v2;
        }
    }

    // Standardfall: Einzelwert (Zahl oder Register)
    return mcs_alu_get_val(ausdruck);
}

#include "mcs_alu_rechner.h"
#include "mcs_register.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long mcs_alu_berechne(const char* ausdruck) {
    long ergebnis = 0;
    char op = '+';
    const char* p = ausdruck;

    while (*p) {
        // Ignoriere Whitespace und Boxi-Klammern
        if (isspace(*p) || *p == '[' || *p == ']') { p++; continue; }

        // UTF-8 Handling für '×' (Multi-Byte)
        if ((unsigned char)*p == 0xC3 && (unsigned char)*(p+1) == 0x97) { p += 2; continue; }

        long wert = 0;
        if (*p == '(') { // Register (1)
            int id = atoi(p + 1);
            wert = mcs_register_hole_num(id);
            while (*p && *p != ')') p++;
            if (*p) p++;
        } else if (isdigit(*p)) {
            wert = strtol(p, (char**)&p, 10);
        }

        if (op == '+') ergebnis += wert;
        else if (op == '-') ergebnis -= wert;
        else if (op == '*') ergebnis *= wert;
        else if (op == '/') if (wert != 0) ergebnis /= wert;

        while (*p && isspace(*p)) p++;

        // MCS-Syntax Mapper: '·' zu '*'
        // Wenn ein Register (n) im Ausdruck vorkommt
        if (*p == '(') {
            char *endptr;
            int reg_id = (int)strtol(p + 1, &endptr, 10);
            wert = mcs_register_hole_num(reg_id); // Wert aus Register laden
            p = endptr;
            if (*p == ')') p++;
        }
    }
    return ergebnis;
}

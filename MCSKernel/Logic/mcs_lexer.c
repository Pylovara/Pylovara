#include "mcs_lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Hilfsfunktion zum Kopieren von Tokens
char* mcs_kopiere_zeichen(const char *start, int laenge) {
    char *puffer = malloc(laenge + 1);
    strncpy(puffer, start, laenge);
    puffer[laenge] = '\0';
    return puffer;
}

Token* mcs_lexer_erzeuge(const char *quellcode) {
    Token *tokens = malloc(1024 * sizeof(Token)); // Initialer Puffer
    int index = 0;
    const char *p = quellcode;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // 1. TRANSAKTIONSRAHMEN
        if (strncmp(p, "¢|", 2) == 0) {
            tokens[index].typ = TOKEN_TRANS_START;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        else if (strncmp(p, "|¢", 2) == 0) {
            tokens[index].typ = TOKEN_TRANS_END;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        // 2. WAHRHEITEN & OPTIONEN
        else if (strncmp(p, "–", 3) == 0) { // En-Dash (UTF-8)
            tokens[index].typ = TOKEN_WAHRHEIT_TRIGGER;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 3);
            p += 3;
        }
        else if (strncmp(p, "·", 2) == 0) { // Mittelpunkt
            tokens[index].typ = TOKEN_OPTION;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        // 3. AKTIONEN
        else if (strncmp(p, "»", 2) == 0) {
            tokens[index].typ = TOKEN_AKTION_START;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        else if (strncmp(p, "«", 2) == 0) {
            tokens[index].typ = TOKEN_AKTION_ENDE;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        // 4. BOXIS (ALU RECHNER)
        else if (strncmp(p, "[×", 3) == 0) {
            tokens[index].typ = TOKEN_BOXI_ALU_START;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 3);
            p += 3;
        }
        else if (strncmp(p, "×]", 3) == 0) {
            tokens[index].typ = TOKEN_BOXI_ALU_ENDE;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 3);
            p += 3;
        }
        // 5. SENTIATOREN
        else if (strncmp(p, "ſ", 2) == 0) {
            tokens[index].typ = TOKEN_SENTIATOR_REIN;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        else if (strncmp(p, "¶", 2) == 0) {
            if (strncmp(p+2, "¶", 2) == 0) {
                tokens[index].typ = TOKEN_SENTIATOR_NICHT;
                tokens[index++].wert = mcs_kopiere_zeichen(p, 4);
                p += 4;
            } else {
                tokens[index].typ = TOKEN_SENTIATOR_KANN;
                tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
                p += 2;
            }
        }
        // 6. FEEDS (1)
        else if (*p == '(') {
            const char *start = p;
            while (*p && *p != ')') p++;
            tokens[index].typ = TOKEN_FEED;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start + 1);
            if (*p) p++;
        }
        // 7. KOMMENTARE
        else if (*p == '#') {
            while (*p && *p != '\n') p++;
        }
        else {
            p++; // Unbekanntes überspringen
        }
    }
    tokens[index].typ = TOKEN_EOF;
    return tokens;
}

#include "mcs_lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static char* mcs_kopiere_zeichen(const char *start, int laenge) {
    char *neu = malloc(laenge + 1);
    if (neu) {
        memcpy(neu, start, laenge);
        neu[laenge] = '\0';
    }
    return neu;
}

Token* mcs_lexer_erzeuge(const char *quellcode) {
    Token *tokens = malloc(8192 * sizeof(Token));
    int index = 0;
    const char *p = quellcode;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // Regel der Reinheit (ſ) - UTF8: 0xC5 0xBF
        if ((unsigned char)p[0] == 0xC5 && (unsigned char)p[1] == 0xBF) {
            tokens[index].typ = TOKEN_REINHEIT;
            tokens[index++].wert = "ſ";
            p += 2; continue;
        }

        // Fortschritt (–) - UTF8: 0xE2 0x80 0x93
        if ((unsigned char)p[0] == 0xE2 && (unsigned char)p[1] == 0x80 && (unsigned char)p[2] == 0x93) {
            tokens[index].typ = TOKEN_FORTSCHRITT;
            tokens[index++].wert = "–";
            p += 3; continue;
        }

        // 1. KOMMENTARE
        if (*p == '#') {
            while (*p && *p != '\n') p++;
            continue;
        }

        // 2. TRANSAKTIONS-RAHMEN (¢! / !¢) - UTF8 sicher
        if ((unsigned char)p[0] == 0xC2 && (unsigned char)p[1] == 0xA2 && p[2] == '!') {
            tokens[index].typ = TOKEN_TRANS_START;
            tokens[index++].wert = "¢!";
            p += 3; continue;
        }
        if (p[0] == '!' && (unsigned char)p[1] == 0xC2 && (unsigned char)p[2] == 0xA2) {
            tokens[index].typ = TOKEN_TRANS_ENDE;
            tokens[index++].wert = "!¢";
            p += 3; continue;
        }

        // 3. BINDUNGS-IMPULS (Scharfschaltung -=)
        if (strncmp(p, "-=", 2) == 0) {
            tokens[index].typ = TOKEN_ASSIGN;
            tokens[index++].wert = "-=";
            p += 2; continue;
        }

        // 4. BOXI-KLASSEN (ALU, SHELL, CALLIS)
        if (strncmp(p, "»", 2) == 0) { tokens[index].typ = TOKEN_AKTION_START; tokens[index++].wert = "»"; p += 2; continue; }
        if (strncmp(p, "«", 2) == 0) { tokens[index].typ = TOKEN_AKTION_ENDE; tokens[index++].wert = "«"; p += 2; continue; }

        if (strncmp(p, "×", 2) == 0) {
            p += 2; const char *start = p;
            while (*p && strncmp(p, "×", 2) != 0) p++;
            tokens[index].typ = TOKEN_BOXI_ALU;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (strncmp(p, "×", 2) == 0) p += 2;
            continue;
        }

        if (*p == '\'') {
            p++; const char *start = p;
            while (*p && *p != '\'') p++;
            tokens[index].typ = TOKEN_BOXI_SHELL;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (*p == '\'') p++;
            continue;
        }

        // 5. REGISTER-IDENTIFIKATION [(n)]
        if (p[0] == '[' && p[1] == '(') {
            tokens[index].typ = TOKEN_REG_ID;
            const char *end = strchr(p, ')');
            if (end) {
                int len = end - (p + 2);
                tokens[index++].wert = mcs_kopiere_zeichen(p + 2, len);
                p = end + 2; // Überspringt )]
                continue;
            }
        }

        // Altes Register-Format (n) als Fallback
        if (*p == '(') {
            p++; const char *start = p;
            while (*p && *p != ')') p++;
            tokens[index].typ = TOKEN_REG_ID;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (*p == ')') p++;
            continue;
        }

        // 6. SENTIATOREN (¶ / ¶¶)
        if (strncmp(p, "¶", 2) == 0) {
            if (strncmp(p + 2, "¶", 2) == 0) {
                tokens[index].typ = TOKEN_SENTI_FALSE; tokens[index++].wert = "¶¶"; p += 4;
            } else {
                tokens[index].typ = TOKEN_SENTI_TRUE; tokens[index++].wert = "¶"; p += 2;
            }
            continue;
        }

        p++; // Fallback
    }

    tokens[index].typ = TOKEN_EOF;
    tokens[index].wert = NULL;
    return tokens;
}

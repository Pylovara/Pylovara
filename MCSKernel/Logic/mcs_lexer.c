#include "mcs_lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Hilfsfunktion: Kopiert einen Teilstring sicher in einen neuen Speicherbereich.
 */
static char* mcs_kopiere_zeichen(const char *start, int laenge) {
    char *neu = malloc(laenge + 1);
    if (neu) {
        memcpy(neu, start, laenge);
        neu[laenge] = '\0';
    }
    return neu;
}

/**
 * @kernel-nr: 07 & 09 | BOXI/S & SENTIATOREN
 * Zerlegt den MCS-Quellcode in logische Einheiten (Tokens).
 */
Token* mcs_lexer_erzeuge(const char *quellcode) {
    Token *tokens = malloc(8192 * sizeof(Token));
    int index = 0;
    const char *p = quellcode;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // --- 1. KOMMENTARE & BASIS ---
        if (*p == '#') {
            while (*p && *p != '\n') p++;
            continue;
        }

        // --- 2. PRIORITÄT: MULTI-ZEICHEN (Transaktionsrahmen & UTF-8) ---
        // --- TRANSAKTIONS-RAHMEN (¢! / !¢) ---
        if (strncmp(p, "¢!", 3) == 0 || (unsigned char)p[0] == 0xC2 && (unsigned char)p[1] == 0xA2 && p[2] == '!') {
            tokens[index].typ = TOKEN_TRANS_START;
            tokens[index++].wert = "¢!";
            p += 3; continue; // 3 Bytes springen! (C2 A2 21)
        }

        if (strncmp(p, "!¢", 3) == 0 || p[0] == '!' && (unsigned char)p[1] == 0xC2 && (unsigned char)p[2] == 0xA2) {
            tokens[index].typ = TOKEN_TRANS_ENDE;
            tokens[index++].wert = "!¢";
            p += 3; continue; // Wir müssen 3 Bytes springen! (21 C2 A2)
        }
        if (strncmp(p, "»", 2) == 0) { tokens[index].typ = TOKEN_AKTION_START; tokens[index++].wert = "»"; p += 2; continue; }
        if (strncmp(p, "«", 2) == 0) { tokens[index].typ = TOKEN_AKTION_ENDE; tokens[index++].wert = "«"; p += 2; continue; }

        // Sentiator: Kann/Nicht (¶ / ¶¶) - ¶¶ zuerst prüfen!
        if (strncmp(p, "¶", 2) == 0) {
            if (strncmp(p + 2, "¶", 2) == 0) {
                tokens[index].typ = TOKEN_SENTI_FALSE; tokens[index++].wert = "¶¶"; p += 4;
            } else {
                tokens[index].typ = TOKEN_SENTI_TRUE; tokens[index++].wert = "¶"; p += 2;
            }
            continue;
        }

        // --- 3. PRIORITÄT: EINZEL-ZEICHEN SENTIATOREN ---
        if (*p == '!') {
            tokens[index].typ = TOKEN_SENTI_MATCH;
            tokens[index++].wert = "!";
            p++; continue;
        }

        // --- 4. BOXI-KLASSEN ---
        if (strncmp(p, "×", 2) == 0) {
            p += 2; const char *start = p;
            while (*p && strncmp(p, "×", 2) != 0) p++;
            tokens[index].typ = TOKEN_BOXI_ALU;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (strncmp(p, "×", 2) == 0) p += 2;
            continue;
        }
        if (*p == '"') {
            p++; const char *start = p;
            while (*p && *p != '"') p++;
            tokens[index].typ = TOKEN_BOXI_CALLIS;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (*p == '"') p++;
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

        // --- 5. REGISTER & WEITERE ---
        if (*p == '(') {
            p++; const char *start = p;
            while (*p && *p != ')') p++;
            tokens[index].typ = TOKEN_REG_ID;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (*p == ')') p++;
            continue;
        }

        // Fortschritt (–) - UTF8: 0xE2 0x80 0x93 (3 Bytes!)
        if (strncmp(p, "–", 3) == 0) { tokens[index].typ = TOKEN_FORTSCHRITT; tokens[index++].wert = "–"; p += 3; continue; }

        if (*p == '[') { tokens[index].typ = TOKEN_BOXI_START; tokens[index++].wert = "["; p++; continue; }
        if (*p == ']') { tokens[index].typ = TOKEN_BOXI_ENDE; tokens[index++].wert = "]"; p++; continue; }

        p++; // Fallback
    }

    tokens[index].typ = TOKEN_EOF;
    tokens[index].wert = NULL;
    return tokens;
}

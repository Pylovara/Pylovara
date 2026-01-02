#include "mcs_lexer.h"
#include "mcs_kernel_core.h"
#include "mcs_wahrheiten.h"
#include "mcs_cmd_register.h"
#include "mcs_register.h"
#include "mcs_alu_rechner.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Hilfsfunktion zum Kopieren von Tokens
char* mcs_kopiere_zeichen(const char *start, int laenge) {
    char *puffer = malloc(laenge + 1);
    strncpy(puffer, start, laenge);
    puffer[laenge] = '\0';
    return puffer;
}

// @kernel-nr: 02 - Transaktionsrahmen & Byte-Kopplung
Token* mcs_lexer_erzeuge(const char *quellcode) {
    Token *tokens = malloc(2048 * sizeof(Token));
    int index = 0;
    const char *p = quellcode;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        if (strncmp(p, "¢!", 2) == 0 || strncmp(p, "¢|", 2) == 0) {
            tokens[index].typ = TOKEN_TRANS_START;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        else if (strncmp(p, "!¢", 2) == 0 || strncmp(p, "|¢", 2) == 0) {
            tokens[index].typ = TOKEN_TRANS_END;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 2);
            p += 2;
        }
        else if (strncmp(p, "«««", 6) == 0) {
            tokens[index].typ = TOKEN_ARGUMENT_KOMPLEX;
            tokens[index++].wert = mcs_kopiere_zeichen(p + 6, 2);
            p += 8;
        }
        else if (strncmp(p, "–", 3) == 0) {
            tokens[index].typ = TOKEN_WAHRHEIT_TRIGGER;
            tokens[index++].wert = "–";
            p += 3;
        }
        else if (strncmp(p, "·", 2) == 0) {
            tokens[index].typ = TOKEN_OPTION;
            tokens[index++].wert = "·";
            p += 2;
        }
        else if (strncmp(p, "»", 2) == 0) {
            tokens[index].typ = TOKEN_AKTION_START;
            tokens[index++].wert = "»";
            p += 2;
        }
        else if (strncmp(p, "[×", 3) == 0) {
            tokens[index].typ = TOKEN_BOXI_ALU_START;
            tokens[index++].wert = "[×";
            p += 3;
        }
        else if (strncmp(p, "×]", 3) == 0) {
            tokens[index].typ = TOKEN_BOXI_ALU_ENDE;
            tokens[index++].wert = "×]";
            p += 3;
        }
        else if (*p == '(') {
            const char *start = p;
            while (*p && *p != ')') p++;
            if (*p == ')') p++;
            // Falls ein String folgt: (1)"Wert"
            if (*p == '"') {
                p++;
                while (*p && *p != '"') p++;
                if (*p == '"') p++;
            }
            tokens[index].typ = TOKEN_FEED;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
        }
        else if (*p == '\'') {
            p++;
            const char *start = p;
            while (*p && *p != '\'') p++;
            tokens[index].typ = TOKEN_STRING;
            tokens[index++].wert = mcs_kopiere_zeichen(start, p - start);
            if (*p) p++;
        }
        else if (strncmp(p, "¶¶", 4) == 0) {
            tokens[index].typ = TOKEN_SENTIATOR_NICHT;
            tokens[index++].wert = "¶¶";
            p += 4;
        }
        else if (strncmp(p, "¶", 2) == 0) {
            tokens[index].typ = TOKEN_SENTIATOR_KANN;
            tokens[index++].wert = "¶";
            p += 2;
        }
        else if (*p == '#') {
            while (*p && *p != '\n') p++;
        }
        else {
            // Unbekannte Zeichen (Operatoren wie <, >, +, *) als TOKEN_STRING erfassen
            tokens[index].typ = TOKEN_STRING;
            tokens[index++].wert = mcs_kopiere_zeichen(p, 1);
            p++;
        }
    }
    tokens[index].typ = TOKEN_EOF;
    return tokens;
}

void mcs_kernel_takt(const char *quellcode) {
    Token *tokens = mcs_lexer_erzeuge(quellcode);
    int i = 0;
    mcs_register_init();

    while (tokens[i].typ != TOKEN_EOF) {
        switch (tokens[i].typ) {
            case TOKEN_TRANS_START:
                mcs_transaktion_start();
                break;
            case TOKEN_WAHRHEIT_TRIGGER: {
                int stufe = 1;
                while(tokens[i+1].typ == TOKEN_OPTION) { stufe++; i++; }
                mcs_progress_operator(stufe, 100);
                printf("\n");
                break;
            }
            case TOKEN_BOXI_ALU_START: {
                char finaler_ausdruck[512] = {0};
                i++;
                while (tokens[i].typ != TOKEN_BOXI_ALU_ENDE && tokens[i].typ != TOKEN_EOF) {
                    if (tokens[i].typ == TOKEN_FEED) {
                        int reg_id;
                        if (sscanf(tokens[i].wert, "(%d)", &reg_id) >= 1) {
                            long val = mcs_register_hole_num(reg_id);
                            char val_s[32];
                            sprintf(val_s, "%ld", val);
                            strcat(finaler_ausdruck, val_s);
                        }
                    } else {
                        strcat(finaler_ausdruck, tokens[i].wert);
                    }
                    strcat(finaler_ausdruck, " ");
                    i++;
                }
                long res = mcs_alu_berechne(finaler_ausdruck);
                char res_str[32];
                sprintf(res_str, "%ld", res);
                mcs_register_setze(0, res_str);
                printf("   [ALU-SYNC]: [%s] -> ERGEBNIS: %ld\n", finaler_ausdruck, res);
                break;
            }
            case TOKEN_AKTION_START:
                if (tokens[i+1].typ == TOKEN_STRING) {
                    printf("» [MATERIALISIERUNG]: %s\n", tokens[i+1].wert);
                    i++;
                }
                break;
            case TOKEN_FEED: {
                int reg_id;
                char reg_inhalt[1024];
                if (sscanf(tokens[i].wert, "(%d)\"%[^\"]\"", &reg_id, reg_inhalt) == 2) {
                    mcs_register_setze(reg_id, reg_inhalt);
                }
                break;
            }
            default: break;
        }
        i++;
    }
    free(tokens);
}

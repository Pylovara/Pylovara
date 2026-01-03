#include "mcs_kernel_core.h"
#include "mcs_lexer.h"
#include "mcs_alu_rechner.h"
#include "mcs_register.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Hilfsfunktion: Führt Shell aus und gibt den Output als String zurück
void mcs_shell_ausfuehren(const char *cmd, char *output_buffer) {
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        strcpy(output_buffer, "ERROR");
        return;
    }
    if (fgets(output_buffer, 256, fp) == NULL) {
        strcpy(output_buffer, "");
    } else {
        // Newline am Ende entfernen
        output_buffer[strcspn(output_buffer, "\r\n")] = 0;
    }
    pclose(fp);
}

void mcs_inject_vars(char *dest, const char *src) {
    strcpy(dest, "");
    char temp_src[512];
    strcpy(temp_src, src);
    char *start = temp_src;
    char *pos;
    while ((pos = strchr(start, '(')) != NULL) {
        if (isdigit(pos[1])) {
            *pos = '\0';
            strcat(dest, start);
            int reg_nr = atoi(pos + 1);
            const char* reg_val = mcs_register_hole(reg_nr);
            if (reg_val) strcat(dest, reg_val);
            start = strchr(pos + 1, ')') + 1;
        } else {
            strncat(dest, start, pos - start + 1);
            start = pos + 1;
        }
    }
    strcat(dest, start);
}

void mcs_kernel_takt(const char *quellcode) {
    Token *tokens = mcs_lexer_erzeuge(quellcode);
    int i = 0;
    int aktionsdraht_aktiv = 1;
    char injected_cmd[512];
    char shell_res[256];

    while (tokens[i].typ != TOKEN_EOF) {
        if (tokens[i].typ == TOKEN_TRANS_START) { printf("--- MCS KERNEL TAKT START ---\n"); aktionsdraht_aktiv = 1; i++; continue; }
        if (tokens[i].typ == TOKEN_TRANS_ENDE) { printf("--- MCS KERNEL TAKT ENDE ---\n"); i++; continue; }

        // Sentiator Logik: Reagiert auf Register 0 (das Ergebnis der letzten ALU/Wahrheits-Prüfung)
        if (tokens[i].typ == TOKEN_SENTI_TRUE) {
            const char* val = mcs_register_hole(0);
            aktionsdraht_aktiv = (val && strcmp(val, "0") != 0 && strlen(val) > 0 && strcmp(val, "FAIL") != 0);
            i++; continue;
        }
        if (tokens[i].typ == TOKEN_SENTI_FALSE) {
            const char* val = mcs_register_hole(0);
            aktionsdraht_aktiv = (val && (strcmp(val, "0") == 0 || strlen(val) == 0 || strcmp(val, "FAIL") == 0));
            i++; continue;
        }

        if (aktionsdraht_aktiv) {
            switch (tokens[i].typ) {
                case TOKEN_BOXI_SHELL:
                    mcs_inject_vars(injected_cmd, tokens[i].wert);
                    printf("[SHELL-EXEC]: %s\n", injected_cmd);
                    mcs_shell_ausfuehren(injected_cmd, shell_res);
                    if (strlen(shell_res) > 0) printf("%s\n", shell_res);
                    // AUTO-FEED: Schreibe Output immer in Register 0 für den nächsten Sentiator
                    mcs_register_setze(0, shell_res);
                break;
                case TOKEN_BOXI_ALU: {
                    long ergebnis = mcs_alu_berechne(tokens[i].wert);
                    char res_str[32];
                    snprintf(res_str, sizeof(res_str), "%ld", ergebnis);
                    mcs_register_setze(0, res_str);
                    printf("[ALU-TAKT]: %s = %ld\n", tokens[i].wert, ergebnis);
                    break;
                }
                case TOKEN_REG_ID:
                    if (tokens[i+1].typ == TOKEN_BOXI_CALLIS) {
                        // Wenn der Wert in der Box leer ist, nehmen wir das letzte Shell-Ergebnis
                        const char* val_to_store = (strlen(tokens[i+1].wert) > 0) ? tokens[i+1].wert : mcs_register_hole(0);
                        mcs_register_setze(atoi(tokens[i].wert), val_to_store);
                        printf("[FEED-SYNC]: FF(%s) <- %s\n", tokens[i].wert, val_to_store);
                    }
                    break;
                case TOKEN_AKTION_START: printf("» [START]\n"); break;
                case TOKEN_AKTION_ENDE:   printf("« [ENDE]\n"); break;
                default: break;
            }
        }
        if (tokens[i].typ == TOKEN_AKTION_ENDE) aktionsdraht_aktiv = 1;
        i++;
    }
    free(tokens);
}

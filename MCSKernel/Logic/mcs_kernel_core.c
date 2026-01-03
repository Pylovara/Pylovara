// OrdnerPfad: /Pylovara/MCSKernel/Logic/mcs_kernel_core.c
// Name: MCS-Zentral-Aktor-Logik

#include "mcs_kernel_core.h"
#include "mcs_lexer.h"
#include "mcs_alu_rechner.h"
#include "mcs_register.h"
#include "mcs_alu_prozessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Hilfsfunktion: Führt Shell aus (DNA-Akquirierung)
void mcs_shell_ausfuehren(const char *cmd, char *output_buffer) {
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        strcpy(output_buffer, "ERROR");
        return;
    }
    if (fgets(output_buffer, 256, fp) == NULL) {
        strcpy(output_buffer, "");
    } else {
        output_buffer[strcspn(output_buffer, "\r\n")] = 0;
    }
    pclose(fp);
}

// Variablen-Injektion für Proteine in Befehlen
void mcs_inject_vars(char *dest, const char *src) {
    strcpy(dest, "");
    char temp_src[512];
    strncpy(temp_src, src, 511);
    char *start = temp_src;
    char *pos;
    while ((pos = strchr(start, '(')) != NULL) {
        if (isdigit(pos[1])) {
            *pos = '\0';
            strcat(dest, start);
            int reg_nr = atoi(pos + 1);
            // Nutze die neue Extraktions-Funktion für den b64 Pfad
            long val = mcs_register_extrahiere_protein(reg_nr);
            char val_str[32];
            sprintf(val_str, "%ld", val);
            strcat(dest, val_str);
            char *end_paren = strchr(pos + 1, ')');
            start = end_paren ? end_paren + 1 : pos + 1;
        } else {
            strncat(dest, start, pos - start + 1);
            start = pos + 1;
        }
    }
    strcat(dest, start);
}

// @kernel-nr: 77 | Ausführungslogik (Zentraler Takt)
void mcs_kernel_takt(const char *quellcode) {
    Token *tokens = mcs_lexer_erzeuge(quellcode);
    int i = 0;
    int aktionsdraht_aktiv = 1;
    char injected_cmd[512];
    char shell_res[256];

    while (tokens[i].typ != TOKEN_EOF) {
        // Transaktionsrahmen-Steuerung [cite: 300, 311]
        if (tokens[i].typ == TOKEN_TRANS_START) {
            printf("--- MCS KERNEL TAKT START ---\n");
            aktionsdraht_aktiv = 1; i++; continue;
        }
        if (tokens[i].typ == TOKEN_TRANS_ENDE) {
            printf("--- MCS KERNEL TAKT ENDE ---\n"); i++; continue;
        }

        if (aktionsdraht_aktiv) {
            switch (tokens[i].typ) {
                case TOKEN_BOXI_SHELL: // »['...']«
                    mcs_inject_vars(injected_cmd, tokens[i].wert);
                    printf("[SHELL-EXEC]: %s\n", injected_cmd);
                    mcs_shell_ausfuehren(injected_cmd, shell_res);
                    if (strlen(shell_res) > 0) printf("%s\n", shell_res);
                    // Speicher im flüchtigen Register 0 (Cache)
                    mcs_register_setze(0, shell_res);
                break;

                case TOKEN_BOXI_ALU: { // »[×...×]«
                    long ergebnis = mcs_alu_berechne(tokens[i].wert);
                    char res_str[32];
                    sprintf(res_str, "%ld", ergebnis);
                    mcs_register_setze(0, res_str);
                    printf("[ALU-TAKT]: %s = %ld\n", tokens[i].wert, ergebnis);
                    break;
                }

                case TOKEN_ASSIGN: { // Der scharfe -= Impuls
                    // @kernel-nr: 11 | Feed-Akquirierung
                    const char* roh_wert = mcs_register_hole(0);
                    long b64_protein = atol(roh_wert);

                    // 2. AIMS-HANDSHAKE (Integritäts-Check b128) [cite: 213]
                    if (ALU_AIMS_HANDSHAKE(b64_protein)) {
                        // 3. SCHARFSCHALTUNG (ALU-BINDUNG)
                        // Nächstes Token muss die Register-ID sein
                        int ziel_reg = atoi(tokens[i+1].wert);
                        ALU_REGISTER_BINDEN(ziel_reg, b64_protein);
                        printf("   [TRANS-OK]: Protein gebunden an FF(%d)\n", ziel_reg);
                    } else {
                        ALU_PURGE_GATTER(NULL); // Regel der Reinheit [cite: 120, 259]
                    }
                    i++; // Register-Token überspringen
                    break;
                }

                case TOKEN_AKTION_START: printf("» [START]\n"); break;
                case TOKEN_AKTION_ENDE:   printf("« [ENDE]\n"); break;
                default: break;
            }
        }
        i++;
    }
    free(tokens);
}
// Hier endet die Funktion mcs_kernel_takt

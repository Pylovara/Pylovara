// =============================================================================
// src/mcs_17_parser.c
// Pylovara MCS Kernel – Modul 17: Ausführungs-Parser (Transaktionsrahmen)
// Stand: 10. Januar 2026 – SSoT 00.58 (Transaktionsrahmen aktiv)
// =============================================================================

#include "mcs_17_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Variablenspeicher – maximal 10 Feeds (FF 0–9)
static int feeds[10] = {0};
static int feed_count = 0;

// Letztes ALU-Ergebnis
static int last_alu_result = 0;

// Transaktionsrahmen-Status
static bool in_transaction = false;

// Debug-Flag (kann später ausgeschaltet werden)
static bool debug_mode = true;

// Hilfsfunktion: Ersetze °(n)° durch Feed-Wert (UTF-8 safe)
static void replace_feed_vars(char* line) {
    char buffer[512];
    const unsigned char* upos = (const unsigned char*)line;
    char* out = buffer;

    while (*upos) {
        if (*upos == 0xC2 && *(upos+1) == 0xB0) { // °
            upos += 2;
            if (*upos == '(') {
                upos++;
                int idx;
                const char* end = strchr((const char*)upos, ')');
                if (end && sscanf((const char*)upos, "%d", &idx) == 1 && idx < feed_count) {
                    out += sprintf(out, "%d", feeds[idx]);
                    upos = (const unsigned char*)end + 1;
                    if (*upos == 0xC2 && *(upos+1) == 0xB0) upos += 2;
                } else {
                    *out++ = 0xC2; *out++ = 0xB0;
                    *out++ = *upos++;
                }
            } else {
                *out++ = 0xC2; *out++ = 0xB0;
                *out++ = *upos++;
            }
        } else {
            *out++ = *upos++;
        }
    }
    *out = '\0';
    strcpy(line, buffer);
}

// ALU-Berechnung [×a op b×] oder [×°(i)° op °(j)°×]
static void execute_alu(const char* cmd) {
    int a, b;
    char op;
    int va, vb;

    // Direkte Zahlen
    if (sscanf(cmd, "[×%d %c %d×]", &a, &op, &b) == 3) {
        switch (op) {
            case '+': last_alu_result = a + b; break;
            case '-': last_alu_result = a - b; break;
            case '*': last_alu_result = a * b; break;
            case '/': last_alu_result = b != 0 ? a / b : 0; break;
            case '>': last_alu_result = a > b ? 1 : 0; break;
            default: last_alu_result = 0; break;
        }
        printf("[ALU] %d %c %d = %d\n", a, op, b, last_alu_result);
        return;
    }

    // Feed-Vergleich
    if (sscanf(cmd, "[×°(%d)° > °(%d)°×]", &va, &vb) == 2) {
        if (va < feed_count && vb < feed_count) {
            last_alu_result = feeds[va] > feeds[vb] ? 1 : 0;
            printf("[ALU] FF(%d)=%d > FF(%d)=%d → %d\n", va, feeds[va], vb, feeds[vb], last_alu_result);
        }
    }
}

// Speichere ALU-Ergebnis in Feed (Führender Feed)
static void store_in_feed(int idx) {
    if (idx < 10) {
        feeds[idx] = last_alu_result;
        printf("[FF] Feed %d = %d (Führender Feed)\n", idx, last_alu_result);
        if (idx >= feed_count) feed_count = idx + 1;
    }
}

int mcs_parser_execute_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("[PARSER] Datei '%s' nicht gefunden.\n", filename);
        return -1;
    }

    printf("[TRANS-RAHMEN] Parser gestartet – SSoT 00.58 (Transaktionsrahmen aktiv)\n");

    char line[512];
    bool in_transaction = false;  // Wichtig: false am Anfang!

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n\r")] = 0;

        if (strlen(line) == 0) continue;

        // Transaktionsrahmen – START (¢!)
        if (strstr(line, "¢!")) {
            in_transaction = true;
            printf("[TRANS] ANFANGSBEDIENUNG –¢! – Rahmen geöffnet\n");
            continue;
        }

        // Transaktionsrahmen – ENDE (!¢)
        if (strstr(line, "!¢")) {
            in_transaction = false;
            printf("[TRANS] ENDBEDIENUNG !¢ – Rahmen geschlossen\n");
            continue;
        }

        // **Streng**: Nur innerhalb des Rahmens wird etwas gemacht
        if (!in_transaction) continue;

        // Hier kommt die volle Ausführungslogik rein (Boxis, ALU, Feeds, Sentiatoren)
        // Für den Moment: nur Debug, damit wir sehen, dass der Rahmen hält
        printf("[DEBUG] Inhalt innerhalb Rahmen: %s\n", line);

        // Später hier: Boxis-Ausführung, ALU-Rechnung, Workspace-Speicherung usw.
    }

    fclose(file);
    return 0;
}

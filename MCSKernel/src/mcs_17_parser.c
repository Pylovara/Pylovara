// =============================================================================
// src/mcs_17_parser.c
// Pylovara MCS Kernel – Modul 17: Parser (Implementierung)
// Stand: 08. Januar 2026
// =============================================================================

#include "mcs_17_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Variablenspeicher – maximal 10 Variablen
static int variables[10] = {0};
static int var_count = 0;

// Hilfsfunktion: Ersetze °(n)° durch aktuellen Wert (UTF-8 safe)
static void replace_vars(char* line) {
    char buffer[512];
    char* pos = line;
    char* out = buffer;

    while (*pos) {
        if (*pos == 0xC2 && *(pos+1) == 0xB0) { // UTF-8 für °
            pos += 2;
            if (*pos == '(') {
                pos++;
                int idx;
                char* end = strchr(pos, ')');
                if (end && sscanf(pos, "%d", &idx) == 1 && idx < var_count) {
                    out += sprintf(out, "%d", variables[idx]);
                    pos = end + 1;
                    if (*pos == 0xC2 && *(pos+1) == 0xB0) pos += 2; // schließendes °
                } else {
                    *out++ = 0xC2;
                    *out++ = 0xB0;
                    *out++ = *pos++;
                }
            } else {
                *out++ = 0xC2;
                *out++ = 0xB0;
                *out++ = *pos++;
            }
        } else {
            *out++ = *pos++;
        }
    }
    *out = '\0';
    strcpy(line, buffer);
}

// Speichere Wert aus echo in nächste Variable
static void store_value_from_echo(const char* cmd) {
    int value;
    if (sscanf(cmd, "['echo %d']", &value) == 1) {
        if (var_count < 10) {
            variables[var_count] = value;
            printf("[VAR] v%d = %d\n", var_count, value);
            var_count++;
        }
    }
}

// Prüfe Vergleich und gib bool zurück
static bool evaluate_comparison(const char* cmd) {
    int v1, v2;
    if (sscanf(cmd, "[×°(%d)° > °(%d)°×]", &v1, &v2) == 2) {
        bool result = (v1 < var_count && v2 < var_count) ? (variables[v1] > variables[v2]) : false;
        printf("[VERGLEICH] v%d (%d) > v%d (%d) = %s\n", v1, variables[v1], v2, variables[v2], result ? "WAHR" : "FALSCH");
        return result;
    }
    return false;
}

int mcs_parser_execute_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("[PARSER] Datei '%s' nicht gefunden.\n", filename);
        return -1;
    }

    printf("[PARSER] Führe '%s' aus\n", filename);

    char line[512];
    int in_transaction = 0;
    bool condition_true = false;
    int condition_level = 0;
    var_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n\r")] = 0;

        if (strlen(line) == 0) continue;

        if (strstr(line, "¢!")) {
            in_transaction = 1;
            var_count = 0;
            printf("[TRANS] Start\n");
            continue;
        }
        if (strstr(line, "!¢")) {
            in_transaction = 0;
            printf("[TRANS] Ende\n");
            continue;
        }

        if (!in_transaction) continue;

        // Bedingung ¶
        if (strncmp(line, "¶", 3) == 0) { // UTF-8 ¶ ist 3 Bytes
            condition_level++;
            char* cmd = line + 3;
            while (isspace(*cmd)) cmd++;
            condition_true = evaluate_comparison(cmd);
            continue;
        }

        // Bedingung ¶¶ (else)
        if (strncmp(line, "¶¶", 6) == 0) { // UTF-8 ¶¶ sind 6 Bytes
            if (condition_level == 1 && !condition_true) {
                char* cmd = line + 6;
                while (isspace(*cmd)) cmd++;
                replace_vars(cmd);
                printf("%s\n", cmd);
            }
            condition_level--;
            continue;
        }

        // Befehl »
        if (strncmp(line, "»", 3) == 0) { // UTF-8 » ist 3 Bytes
            char* cmd = line + 3;
            while (isspace(*cmd)) cmd++;

            if (strstr(cmd, "['echo") != NULL) {
                store_value_from_echo(cmd);
                char content[256];
                if (sscanf(cmd, "['echo %255[^']]", content) == 1) {
                    replace_vars(content);
                    printf("%s\n", content);
                }
            }
        }
    }

    fclose(file);
    return 0;
}

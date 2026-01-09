// =============================================================================
// src/mcs_17_parser.c
// Pylovara MCS Kernel – Modul 17: Parser (Implementierung)
// Stand: 09. Januar 2026 – SSoT 00.58 konform
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

// Hilfsfunktion: Ersetze °(n)° durch aktuellen Wert (UTF-8 safe, keine Warnungen)
static void replace_vars(char* line) {
    char buffer[512];
    const unsigned char* upos = (const unsigned char*)line;
    char* out = buffer;

    while (*upos) {
        if (*upos == 0xC2 && *(upos+1) == 0xB0) { // UTF-8 für °
            upos += 2;
            if (*upos == '(') {
                upos++;
                int idx;
                const char* end = strchr((const char*)upos, ')');
                if (end && sscanf((const char*)upos, "%d", &idx) == 1 && idx < var_count) {
                    out += sprintf(out, "%d", variables[idx]);
                    upos = (const unsigned char*)end + 1;
                    if (*upos == 0xC2 && *(upos+1) == 0xB0) upos += 2;
                } else {
                    *out++ = 0xC2;
                    *out++ = 0xB0;
                    *out++ = *upos++;
                }
            } else {
                *out++ = 0xC2;
                *out++ = 0xB0;
                *out++ = *upos++;
            }
        } else {
            *out++ = *upos++;
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
        if (v1 < var_count && v2 < var_count) {
            bool result = variables[v1] > variables[v2];
            printf("[VERGLEICH] v%d (%d) > v%d (%d) = %s\n", v1, variables[v1], v2, variables[v2], result ? "WAHR" : "FALSCH");
            return result;
        }
    }
    return false;
}

int mcs_parser_execute_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("[PARSER] Datei '%s' nicht gefunden.\n", filename);
        return -1;
    }

    printf("[PARSER] Führe '%s' aus – SSoT 00.58 konform\n", filename);

    char line[512];
    int in_transaction = 0;
    bool condition_true = false;
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

        // Befehl »
        if (strncmp(line, "»", 3) == 0) {
            char* cmd = line + 3;
            while (*cmd == ' ') cmd++;

            if (strstr(cmd, "['echo") != NULL) {
                store_value_from_echo(cmd);
                char content[256];
                if (sscanf(cmd, "['echo %255[^']]", content) == 1) {
                    replace_vars(content);
                    printf("%s\n", content);
                }
            }
        }

        // Workspace-Zuweisungen
        if (strstr(line, "-·=") != NULL) {
            int idx;
            if (sscanf(line, "-·= [( %d )°°]", &idx) == 1) {
                printf("[WORKSPACE A] v%d reserviert\n", idx);
            }
        }
        if (strstr(line, "-··=") != NULL) {
            int idx;
            if (sscanf(line, "-··= [( %d )°°]", &idx) == 1) {
                printf("[WORKSPACE B] v%d reserviert\n", idx);
            }
        }
        if (strstr(line, "-···=") != NULL) {
            int idx;
            if (sscanf(line, "-···= [( %d )°°]", &idx) == 1) {
                printf("[WORKSPACE C] v%d reserviert\n", idx);
            }
        }

        // SENTIATOR-KANN-IMPULS (¶)
        if (strncmp(line, "    ¶", 6) == 0) {
            char* cmd = line + 6;
            while (*cmd == ' ') cmd++;
            condition_true = evaluate_comparison(cmd);
        }

        // Parallel-Transport bei WAHR
        if (strstr(line, "-····>") != NULL) {
            if (condition_true) {
                char* cmd = strstr(line, "»");
                if (cmd) {
                    cmd += 3;
                    while (*cmd == ' ') cmd++;
                    replace_vars(cmd);
                    printf("%s\n", cmd);
                }
            }
        }

        // Parallel-Transport bei FALSCH
        if (strstr(line, "-·····>") != NULL) {
            if (!condition_true) {
                char* cmd = strstr(line, "»");
                if (cmd) {
                    cmd += 3;
                    while (*cmd == ' ') cmd++;
                    replace_vars(cmd);
                    printf("%s\n", cmd);
                }
            }
        }
    }

    fclose(file);
    return 0;
}

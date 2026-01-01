#include "mcs_lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Token *mcs_lexer(const char *code) {
    Token *tokens = malloc(100 * sizeof(Token)); // Dynamisch erweitern
    int index = 0;
    const char *p = code;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        if (*p == '¢' && *(p+1) == '|') {
            tokens[index].type = TOKEN_TRANS_START;
            tokens[index++].value = strndup(p, 2);
            p += 2;
        } else if (*p == '|' && *(p+1) == '¢') {
            tokens[index].type = TOKEN_TRANS_END;
            tokens[index++].value = strndup(p, 2);
            p += 2;
        } else if (*p == '–') {
            tokens[index].type = TOKEN_WAHRHEIT_TRIGGER;
            tokens[index++].value = strndup(p, 1);
            p++;
            int dots = 0;
            while (*p == '·') { dots++; p++; }
            if (*p == ':') {
                tokens[index-1].type = TOKEN_PROGRESS; // Kombiniere
                p++;
            }
            if (dots == 1) tokens[index-1].type = TOKEN_OPTION_A;
            else if (dots == 2) tokens[index-1].type = TOKEN_OPTION_B;
            else if (dots == 3) tokens[index-1].type = TOKEN_OPTION_C;
            else if (dots == 4) tokens[index-1].type = TOKEN_OPTION_D;
            else if (dots == 5) tokens[index-1].type = TOKEN_OPTION_E;
        } else if (*p == '<') {
            tokens[index].type = TOKEN_PARALLEL_PROCESS;
            tokens[index++].value = strndup(p, 1);
            p++;
        } else if (*p == '>') {
            tokens[index].type = TOKEN_PARALLEL_TRANSPORT;
            tokens[index++].value = strndup(p, 1);
            p++;
        } else if (*p == '~') {
            const char *start = p;
            while (*p && *p != '~') p++;
            tokens[index].type = TOKEN_CMD_SPECIAL;
            tokens[index++].value = strndup(start, p - start + 1);
            p++;
        } else if (*p == '[' && *(p+1) == '×') {
            const char *start = p;
            while (*p && !(*p == '×' && *(p+1) == ']')) p++;
            tokens[index].type = TOKEN_BOXI;
            tokens[index++].value = strndup(start, p - start + 2);
            p += 2;
        } else if (*p == '(') {
            const char *start = p;
            while (*p && *p != ')') p++;
            tokens[index].type = TOKEN_FEED;
            tokens[index++].value = strndup(start, p - start + 1);
            p++;
        } else if (*p == '"') {
            const char *start = p;
            p++;
            while (*p && *p != '"') p++;
            tokens[index].type = TOKEN_STRING;
            tokens[index++].value = strndup(start, p - start + 1);
            p++;
        } else {
            p++; // Skip unknown
        }
    }
    tokens[index].type = TOKEN_EOF;
    tokens[index].value = NULL;
    return tokens;
}

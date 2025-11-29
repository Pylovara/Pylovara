// Lab/test_lexer.c — v2.9-konform, UTF-8-sicher, Feed-kompatibel
#include "../Logic/mcs_lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* token_name(mcs_token_type_t t) {
    switch (t) {
        case TOK_TRANS_START:       return "TOK_TRANS_START";
        case TOK_TRANS_END:         return "TOK_TRANS_END";
        case TOK_ACTION_START:      return "TOK_ACTION_START";
        case TOK_ACTION_END:        return "TOK_ACTION_END";
        case TOK_OP_MARK:           return "TOK_OP_MARK";
        case TOK_ARG_MINUS:         return "TOK_ARG_MINUS";
        case TOK_ARG_PLUS:          return "TOK_ARG_PLUS";
        case TOK_ARG_MUL:           return "TOK_ARG_MUL";
        case TOK_ARG_DIV:           return "TOK_ARG_DIV";
        case TOK_ARG_PERCENT:       return "TOK_ARG_PERCENT";
        case TOK_FEED_OPEN:         return "TOK_FEED_OPEN";
        case TOK_FEED_CLOSE:        return "TOK_FEED_CLOSE";
        case TOK_STR_SGL_QUOTE:     return "TOK_STR_SGL_QUOTE";
        case TOK_BLANKERNER_QUOTE:  return "TOK_BLANKERNER_QUOTE";
        case TOK_STR_DBL_QUOTE:     return "TOK_STR_DBL_QUOTE";
        case TOK_IF:                return "TOK_IF";
        case TOK_ELSE:              return "TOK_ELSE";
        case TOK_PARALLEL_RUN:      return "TOK_PARALLEL_RUN";
        case TOK_PARALLEL_TRANSPORT:return "TOK_PARALLEL_TRANSPORT";
        case TOK_ID:                return "TOK_ID";
        case TOK_NUMBER:            return "TOK_NUMBER";
        case TOK_COMMENT:           return "TOK_COMMENT";
        case TOK_UNKNOWN:           return "TOK_UNKNOWN";
        case TOK_EOF:               return "TOK_EOF";
        default:                    return "OTHER";
    }
}

int main() {
    // Lies test.mcs aus dem Lab-Verzeichnis
    const char* filename = "Lab/test.mcs";
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "[ERROR] Kann '%s' nicht öffnen.\n", filename);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buf = malloc(size + 1);
    if (!buf) {
        perror("malloc");
        fclose(f);
        return 1;
    }
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);

    // Drucke das *vollständige Token*, nicht nur das erste Byte
    char* full_text = malloc(tok.length + 1);
    memcpy(full_text, tok.literal, tok.length);
    full_text[tok.length] = '\0';
    printf("  [%s] '",
           token_name(tok.token_type));

    // Drucke Bytes lesbar (kein Absturz bei \0 im UTF-8)
    for (int i = 0; i < tok.length; i++) {
        unsigned char c = full_text[i];
        if (c >= 32 && c < 127) {
            putchar(c);
        } else {
            printf("\\x%02X", c);
        }
    }
    printf("' (line %d, col %d)\n", tok.line, tok.column);
    free(full_text);

    mcs_token_t tok;
    while ((tok = mcs_lexer_next(lex)).token_type != TOK_EOF) {
        // Extrahiere den Text (ohne Absturz bei ungültigen UTF-8)
        char* text = malloc(tok.length + 1);
        if (text) {
            memcpy(text, tok.literal, tok.length);
            text[tok.length] = '\0';
            for (int i = 0; i < tok.length; i++) {
                if ((unsigned char)text[i] < 32 || (unsigned char)text[i] > 126) {
                    sprintf(text + i, "\\x%02X", (unsigned char)text[i]);
                    break;
                }
            }
            printf("  [%s] '%s' (line %d, col %d)\n",
                   token_name(tok.token_type), text, tok.line, tok.column);
            free(text);
        }
    }

    mcs_lexer_free(lex);
    free(buf);
    printf("=== Lexing abgeschlossen ===\n");
    return 0;
}

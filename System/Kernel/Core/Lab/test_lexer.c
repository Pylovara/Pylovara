// Lab/test_lexer.c
#include "../Logic/mcs_token.h"
#include "../Logic/mcs_lexer.c"  // temporär — nur für Test
#include <stdio.h>

const char* token_name(mcs_token_type_t t) {
    switch (t) {
        case TOK_TRANS_START: return "TOK_TRANS_START";
        case TOK_TRANS_END: return "TOK_TRANS_END";
        case TOK_ACTION_START: return "TOK_ACTION_START";
        case TOK_ACTION_END: return "TOK_ACTION_END";
        case TOK_STR_SGL: return "TOK_STR_SGL";
        case TOK_STR_DBL: return "TOK_STR_DBL";
        case TOK_PROTEIN_OPEN: return "TOK_PROTEIN_OPEN";
        case TOK_PROTEIN_CLOSE: return "TOK_PROTEIN_CLOSE";
        case TOK_SEP: return "TOK_SEP";
        case TOK_EOF: return "TOK_EOF";
        default: return "UNKNOWN";
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.mcs>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) { perror("fopen"); return 1; }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);

    mcs_lexer_t* lex = mcs_lexer_new(buf);
    mcs_token_t tok;

    printf("Tokens in %s:\n", argv[1]);
    while ((tok = mcs_lexer_next(lex)).type != TOK_EOF) {
        if (tok.type == TOK_INVALID) {
            printf("  [INVALID] line %d\n", tok.line);
            break;
        }
        char* text = strndup(tok.start, tok.length);
        printf("  [%s] '%s' (line %d, col %d)\n",
               token_name(tok.type), text, tok.line, tok.column);
        free(text);
    }

    mcs_lexer_free(lex);
    free(buf);
    return 0;
}

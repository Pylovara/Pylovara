// Lib/mcs_argument.c
#include <stdlib.h>
#include <string.h>
#include "mcs_argument.h"
#include "mcs_token.h"

int mcs_parse_argument(mcs_lexer_t* lex, mcs_argument_t* out) {
    if (!lex || !out) return 0;
    *out = (mcs_argument_t){ARG_NONE, 0};

    mcs_token_t tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_OP_MARK) return 0;  // «««

    // Jetzt: nächstes Token bestimmt Typ
    tok = mcs_lexer_next(lex);
    switch (tok.token_type) {
        case TOK_ARG_MINUS:   out->type = ARG_MINUS;   break;
        case TOK_ARG_PLUS:    out->type = ARG_PLUS;    break;
        case TOK_ARG_MUL:     out->type = ARG_MUL;     break;
        case TOK_ARG_DIV:     out->type = ARG_DIV;     break;
        case TOK_ARG_PERCENT: out->type = ARG_PERCENT; break;
        case TOK_ID:
            if (tok.length >= 2) {
                const char* s = tok.literal;
                if (s[0] == 't') { out->type = ARG_TIME;   out->value = atoi(s+1); }
                if (s[0] == 'r') { out->type = ARG_REBOOT; out->value = atoi(s+1); }
                if (s[0] == '%') { out->type = ARG_PERCENT; out->value = atoi(s+1); }
            }
            break;
        default: return 0;
    }
    return 1;
}

// /Lab/test_action.c
#include "../Logic/mcs_token.h"
#include "../Logic/mcs_lexer.c"  // Ja — .c inkludieren für Test (nur hier!)
#include <stdio.h>

typedef struct { char* cmd; char* print; } action_t;

int parse_action(mcs_lexer_t* lex, action_t* out) {
    if (mcs_lexer_next(lex).type != TOK_ACTION_START) return -1;
    if (mcs_lexer_next(lex).type != TOK_PROTEIN_OPEN) return -1;

    mcs_token_t tok = mcs_lexer_next(lex);
    if (tok.type != TOK_STR_SGL) return -1;
    out->cmd = strndup(tok.start + 1, tok.length - 2);

    if (mcs_lexer_next(lex).type != TOK_SEP) return -1;

    tok = mcs_lexer_next(lex);
    if (tok.type != TOK_STR_DBL) return -1;
    out->print = strndup(tok.start + 1, tok.length - 2);

    if (mcs_lexer_next(lex).type != TOK_PROTEIN_CLOSE) return -1;
    if (mcs_lexer_next(lex).type != TOK_ACTION_END) return -1;
    return 0;
}

int main() {
    const char* code = "»['echo'|\"Hallo\"]«";
    mcs_lexer_t* lex = mcs_lexer_new(code);
    action_t act = {0};

    if (parse_action(lex, &act) == 0) {
        printf("✅ Aktion: cmd='%s', print='%s'\n", act.cmd, act.print);
    } else {
        printf("❌ Parse-Fehler\n");
    }

    free(act.cmd); free(act.print);
    mcs_lexer_free(lex);
    return 0;
}

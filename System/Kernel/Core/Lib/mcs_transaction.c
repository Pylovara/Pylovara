// Lib/mcs_transaction.c — Basis-Transaktionsparser für MCS v2.9
#include <stdlib.h>
#include "mcs_transaction.h"

int mcs_parse_transaction(mcs_lexer_t* lex, mcs_transaction_t* out) {
    if (!lex || !out) return 0;

    mcs_token_t tok = mcs_lexer_next(lex);

    // ¢!
    if (tok.token_type != TOK_TRANS_START) return 0;
    out->trans_start = tok;

    // Skip content until !¢ (für Minimal-Test: nur bis Ende suchen)
    while (1) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_EOF) return 0;
        if (tok.token_type == TOK_TRANS_END) {
            out->trans_end = tok;
            out->is_valid = 1;
            return 1;
        }
        // Sonst: ignorieren (später: Inhalts-Parser hier einbauen)
    }
}

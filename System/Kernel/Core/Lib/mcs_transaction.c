#include "mcs_transaction.h"
#include <stdio.h>

bool mcs_parse_transaction(mcs_lexer_t* lex, mcs_transaction_t* out) {
    mcs_token_t tok = mcs_lexer_next(lex);

    // 1. Prüfe Transaktions-Start
    if (tok.token_type != TOK_TRANS_START) {
        fprintf(stderr, "[TRANS] Fehler: Erwartet ¢! bei Zeile %d\n", tok.line);
        return false;
    }
    out->start = tok;

    // 2. Lies beliebige Inhalte (Aktionen, Warp, etc.) — bis Transaktions-Ende
    while (1) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_TRANS_END) {
            out->end = tok;
            out->is_valid = true;
            return true;
        }
        if (tok.token_type == TOK_EOF) {
            fprintf(stderr, "[TRANS] Fehler: Unvollständige Transaktion — !¢ fehlt\n");
            return false;
        }
        // Sonst: Token ignorieren (wird später vom Parser verarbeitet)
    }
}

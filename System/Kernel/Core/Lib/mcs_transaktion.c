// Lib/mcs_transaktion.c — v3.0 MVP: bedingte Transaktionen
// Lib/mcs_transaktion.c — v3.0 MVP: bedingte Transaktionen, *ohne* direkten Lexer-Zugriff
#include <stdlib.h>
#include <string.h>
#include "mcs_transaktion.h"
#include "mcs_wahrheiten.h"   // ← ohne -en! <-- sagst du , müssen wir aber , die datei heißt mcs_warheiten.h im ordner

mcs_transaktion_t* mcs_parse_transaktion(const char* input) {
    if (!input) return NULL;

    mcs_lexer_t* lex = mcs_lexer_new(input);
    if (!lex) return NULL;

    mcs_transaktion_t* t = calloc(1, sizeof(mcs_transaktion_t));
    if (!t) {
        mcs_lexer_free(lex);
        return NULL;
    }

    mcs_token_t tok = mcs_lexer_next(lex);

    // 🔹 Fall 1: Bedingte Transaktion (z.B. ° ['$terminal'])
    if (mcs_token_is_wahrheit(tok.token_type)) {
        t->wahrheit = mcs_token_to_wahrheit(tok.token_type);
        // MVP: Bedingung nur merken — Auswertung im Runner
        // Für MVP: überspringe Bedingung und suche ¢!
        tok = mcs_lexer_next(lex);
    }

    // 🔹 ¢!
    if (tok.token_type != TOK_TRANS_START) {
        mcs_lexer_free(lex);
        free(t);
        return NULL;
    }
    t->trans_start = tok;

    // 🔹 Parse Proteine bis !¢ — einfache Token-Abarbeitung
    while (1) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_TRANS_END) {
            t->trans_end = tok;
            t->is_valid = 1;
            break;
        }
        // MVP: Nur zählen — echtes Parsing später
        if (tok.token_type == TOK_ACTION_START) {
            t->protein_count++;
        }
    }

    mcs_lexer_free(lex);
    return t;
}

void mcs_free_transaktion(mcs_transaktion_t* t) {
    if (!t) return;
    free(t->proteine);
    free(t);
}

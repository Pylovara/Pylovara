// Lib/mcs_transaktion.c — erweitert um Operator-Unterstützung (kernel 09)
#include <stdlib.h>
#include <string.h>
#include "mcs_transaktion.h"
#include "mcs_wahrheiten.h"

#include "mcs_operatoren.h"   // erst hier — wo die vollständige Def. nötig ist

// 🔹 Forward-Deklaration
static mcs_protein_t* mcs_parse_next_protein(mcs_lexer_t* lex);

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

    // 🔹 Phase 1: Transaktions-Bedingung (z. B. ° ['$terminal'])
    if (mcs_token_is_wahrheit(tok.token_type)) {
        t->wahrheit = mcs_token_to_wahrheit(tok.token_type);
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_ACTION_START) {
            t->condition = mcs_parse_next_protein(lex);
        }
    }

    // 🔹 ¢!
    if (tok.token_type != TOK_TRANS_START) {
        mcs_lexer_free(lex);
        mcs_free_transaktion(t);
        return NULL;
    }
    t->trans_start = tok;

    // 🔹 Phase 2: Proteine & Operatoren parsen
    while (1) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_TRANS_END) {
            t->trans_end = tok;
            t->is_valid = 1;
            break;
        }

        // 🔹 Operator-Erkennung (kernel 09)
        if (tok.token_type == TOK_WHEN_NOT ||
            tok.token_type == TOK_WHEN_LT ||
            tok.token_type == TOK_WHEN_GT ||
            tok.token_type == TOK_TRANS_ERROR ||
            tok.token_type == TOK_DATA_RESIDUE) {

            mcs_operator_t* op = mcs_operator_new();
        switch (tok.token_type) {
            case TOK_WHEN_NOT:     mcs_operator_set_type(op, MCS_OP_WHEN_NOT); break;
            case TOK_WHEN_LT:      mcs_operator_set_type(op, MCS_OP_WHEN_LT);  break;
            case TOK_WHEN_GT:      mcs_operator_set_type(op, MCS_OP_WHEN_GT);  break;
            case TOK_TRANS_ERROR:  mcs_operator_set_type(op, MCS_OP_TRANS_ERROR); break;
            case TOK_DATA_RESIDUE: mcs_operator_set_type(op, MCS_OP_DATA_RESIDUE); break;
            default: mcs_operator_free(op); continue;
        }

        mcs_token_t next = mcs_lexer_next(lex);

        if (op->type == MCS_OP_WHEN_NOT && next.token_type == TOK_ACTION_START) {
            mcs_protein_t* cond = mcs_parse_next_protein(lex);
            mcs_operator_bind_condition(op, cond);
            // Zweige: ¶ / ¶¶
            // - mcs_token_t branch = mcs_lexer_peek(lex); // ❌ Fehlt noch! // Peek, nicht Next! Kommt noch
            //if (branch.token_type == TOK_IF) {
            //    mcs_lexer_next(lex); // konsumiere ¶
            //    op->then_branch = mcs_parse_next_protein(lex);
            //}
            //branch = mcs_lexer_peek(lex);
            //if (branch.token_type == TOK_ELSE) {
            //    mcs_lexer_next(lex); // konsumiere ¶¶
            //    op->else_branch = mcs_parse_next_protein(lex);
            // klammer entfernt für sauberes auskommentiern für später
            // Zweige: vorerst leer — später mit Peek vervollständigen
            op->then_branch = NULL;
            op->else_branch = NULL;
        }
        else if ((op->type == MCS_OP_WHEN_LT || op->type == MCS_OP_WHEN_GT)
            && next.token_type == TOK_FEED_OPEN) {
            int id1 = extract_number(mcs_lexer_next(lex));
        mcs_lexer_next(lex); // )
        mcs_lexer_next(lex); // (
            int id2 = extract_number(mcs_lexer_next(lex));
            mcs_lexer_next(lex); // )
            mcs_operator_bind_comparison(op, id1, id2);
            // Zweige
            //mcs_token_t branch = mcs_lexer_peek(lex);
            //if (branch.token_type == TOK_IF) {
            //    mcs_lexer_next(lex);
            //    op->then_branch = mcs_parse_next_protein(lex);
            // klammer fehlt fürs auskommentieren
            //branch = mcs_lexer_peek(lex);
            //if (branch.token_type == TOK_ELSE) {
            //    mcs_lexer_next(lex);
            //    op->else_branch = mcs_parse_next_protein(lex);
            // klammer fehlt fürs auskommentieren
            }
            else if (op->type == MCS_OP_DATA_RESIDUE && next.token_type == TOK_FEED_OPEN) {
                int id = extract_number(mcs_lexer_next(lex));
                mcs_lexer_next(lex); // )
                mcs_operator_bind_residue(op, id);
            }
            else if (op->type == MCS_OP_TRANS_ERROR && next.token_type == TOK_ACTION_START) {
                t->error_handler = mcs_parse_next_protein(lex);
                mcs_operator_free(op);
                continue;
            }

            // Speichern
            t->operators = realloc(t->operators, (t->operator_count + 1) * sizeof(mcs_operator_t*));
            t->operators[t->operator_count++] = op;
            continue;
            }

            // 🔹 Normales Protein
            if (tok.token_type == TOK_ACTION_START) {
                mcs_protein_t* p = mcs_parse_next_protein(lex);
                if (p) {
                    t->proteine = realloc(t->proteine, (t->protein_count + 1) * sizeof(mcs_protein_t*));
                    t->proteine[t->protein_count++] = p;
                }
            }
    }

    mcs_lexer_free(lex);
    return t;
}

void mcs_free_transaktion(mcs_transaktion_t* t) {
    if (!t) return;
    mcs_free_protein(t->condition);
    for (int i = 0; i < t->protein_count; i++) {
        mcs_free_protein(t->proteine[i]);
    }
    free(t->proteine);
    for (int i = 0; i < t->operator_count; i++) {
        mcs_operator_free(t->operators[i]);
    }
    mcs_free_protein(t->error_handler);
    free(t->operators);
    free(t);
}

// 🔹 Hilfsfunktion (vereinfacht — nutzt dein bestehendes mcs_parse_action)
static mcs_protein_t* mcs_parse_next_protein(mcs_lexer_t* lex) {
    // Rücksetzen des Lexers ist komplex → für MVP: leeres Protein
    mcs_protein_t* p = calloc(1, sizeof(mcs_protein_t));
    // In Zukunft: hier dein mcs_parse_action_from_lexer einbauen
    return p;
}

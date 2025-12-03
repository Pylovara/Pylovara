// Lib/mcs_action.c — v2.9-konform, Argumente per kernel 15
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mcs_action.h"

// Hilfsfunktionen (nun *definiert*, nicht nur deklariert)
static inline char* token_to_string(mcs_token_t tok) {
    return tok.length > 0 ? strndup(tok.literal, tok.length) : NULL;
}

static inline int extract_feed_id(mcs_token_t tok) {
    if (tok.token_type == TOK_NUMBER && tok.length > 0) {
        return atoi(tok.literal);
    }
    return 0;
}

mcs_action_t* mcs_parse_action(const char* input) {
    if (!input) return NULL;

    mcs_lexer_t* lex = mcs_lexer_new(input);
    if (!lex) return NULL;

    mcs_action_t* a = calloc(1, sizeof(mcs_action_t));
    if (!a) goto fail;

    mcs_token_t tok;

    // »
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_ACTION_START) goto fail;

    // [
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_PROTEIN_OPEN) goto fail;

    // 'cmd'
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_STR_SGL_QUOTE) goto fail;
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_ID) goto fail;
    a->cmd = token_to_string(tok);

    // |
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_SEP) goto fail;

    // Optionales Feed-Prefix: (1)
    tok = mcs_lexer_next(lex);
    if (tok.token_type == TOK_FEED_OPEN) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_NUMBER) {
            a->feed.id = extract_feed_id(tok);
            a->feed.is_set = 1;
        }
        tok = mcs_lexer_next(lex); // TOK_FEED_CLOSE
    }

    // Argument 1: entweder 'text' oder ¨text¨
    if (tok.token_type == TOK_STR_SGL_QUOTE || tok.token_type == TOK_STR_DBL_QUOTE) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_ID || tok.token_type == TOK_NUMBER) {
            a->arg1 = token_to_string(tok);
        }
    } else if (tok.token_type == TOK_BLANKERNER_QUOTE) {
        tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_ID || tok.token_type == TOK_NUMBER || tok.token_type == TOK_LITERAL) {
            a->blankernenner = token_to_string(tok);
        }
    } else {
        goto fail;
    }

    // ]«
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_PROTEIN_CLOSE) goto fail;
    tok = mcs_lexer_next(lex);
    if (tok.token_type != TOK_ACTION_END) goto fail;

    // ✅ Argumente: nach ]« kommt ggf. TOK_OP_MARK («««)
    tok = mcs_lexer_next(lex);
    if (tok.token_type == TOK_OP_MARK) {        // ««« — 6 Bytes
        tok = mcs_lexer_next(lex);
        // Jetzt: Argument-Token (z. B. -, +, ·, :, %, oder ID wie "t1")
        if (tok.token_type == TOK_ARG_MINUS) {
            a->arg.type = ARG_MINUS;
        } else if (tok.token_type == TOK_ARG_PLUS) {
            a->arg.type = ARG_PLUS;
        } else if (tok.token_type == TOK_ARG_MUL) {
            a->arg.type = ARG_MUL;
        } else if (tok.token_type == TOK_ARG_DIV) {
            a->arg.type = ARG_DIV;
        } else if (tok.token_type == TOK_ARG_PERCENT) {
            a->arg.type = ARG_PERCENT;
            // Optional: Wert parsen, z. B. ««%50
            tok = mcs_lexer_next(lex);
            if (tok.token_type == TOK_NUMBER) {
                a->arg.value = extract_feed_id(tok);
            }
        } else if (tok.token_type == TOK_ID && tok.length >= 2) {
            // z. B. "t1", "r3", "%50"
            const char* s = tok.literal;
            if (s[0] == 't') {
                a->arg.type = ARG_TIME;
                a->arg.value = atoi(s + 1);
            } else if (s[0] == 'r') {
                a->arg.type = ARG_REBOOT;
                a->arg.value = atoi(s + 1);
            } else if (s[0] == '%') {
                a->arg.type = ARG_PERCENT;
                a->arg.value = atoi(s + 1);
            }
        }
    }

    mcs_lexer_free(lex);
    return a;

    fail:
    mcs_lexer_free(lex);
    if (a) {
        free(a->cmd);
        free(a->arg1);
        free(a->blankernenner);
        free(a);
    }
    return NULL;
}

void mcs_free_action(mcs_action_t* a) {
    if (!a) return;
    free(a->cmd);
    free(a->arg1);
    free(a->blankernenner);
    free(a);
}

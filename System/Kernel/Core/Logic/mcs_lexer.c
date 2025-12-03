// mcs_lexer.c — v2.9-konform, UTF-8-sicher, GCC-ready
// Autor: Thomas Zimmermann / Qwen — basierend auf kernel 02–15, MCS 2.9

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mcs_token.h"

// 🔹 MUST be first: define the opaque struct
struct mcs_lexer {
    const char* input;
    const char* pos;
    int line, column;
};

// 🔹 Token table (sorted by length, longest first)
typedef struct {
    const char* symbol;
    int length;
    mcs_token_type_t type;
} LexerEntry;

static const LexerEntry TOKEN_TABLE[] = {
    // 6 Bytes — Argument-Start-Signal (gemäß @kernel 15)
    {"\xC2\xAB\xC2\xAB\xC2\xAB", 6, TOK_OP_MARK},   // ««« → 3 × 0xC2 0xAB = 6 Bytes

    // 5 Bytes — Argument-Operatoren (6 - 1 = 5: 2+2 Bytes «« + 1 Byte Operator)
    {"\xC2\xAB\xC2\xAB-", 5, TOK_ARG_MINUS},        // ««-
    {"\xC2\xAB\xC2\xAB+", 5, TOK_ARG_PLUS},         // ««+
    {"\xC2\xAB\xC2\xAB·", 5, TOK_ARG_MUL},          // ««·
    {"\xC2\xAB\xC2\xAB:", 5, TOK_ARG_DIV},          // ««:
    {"\xC2\xAB\xC2\xAB%", 5, TOK_ARG_PERCENT},      // ««%

    // 4 Bytes
    {"\xC2\xB6\xC2\xB6", 4, TOK_ELSE},              // ¶¶

    // 3 Bytes
    {"\xC2\xB6=", 3, TOK_PARALLEL_RUN},             // ¶=
    {"\xC2\xA2!", 3, TOK_TRANS_START},              // ¢!
    {"!\xC2\xA2", 3, TOK_TRANS_END},                // !¢
    {"\xE2\x80\xA6", 3, TOK_ON_ERROR},              // … (U+2026)
    {"\xE2\x80\x99", 3, TOK_STR_TICK_QUOTE},        // ’ (U+2019)
    {"\xE2\x8A\x95", 3, TOK_SYNC_TIMER},            // ⊕ (U+2295)

    // 2 Bytes
    {";;", 2, TOK_PARALLEL_TRANSPORT},              // ;;
    {"\xC2\xBB", 2, TOK_ACTION_START},              // »
    {"\xC2\xAB", 2, TOK_ACTION_END},                // «
    {"\xC5\xBF", 2, TOK_DATA_RESIDUE},              // ſ (U+017F)
    {"\xC2\xA8", 2, TOK_BLANKERNER_QUOTE},          // ¨ (U+00A8)
    {"\xC2\xB6", 2, TOK_IF},                        // ¶ (U+00B6)
    {"\xC2\xB0", 2, TOK_WHEN_NOT},                  // ° (U+00B0)
    {"\xC2\xA7", 2, TOK_TARGET_REF_PREFIX},         // § (U+00A7)
    {"\xC3\xB8", 2, TOK_WARP},                      // ø (U+00F8)
    {"\xC3\xBE", 2, TOK_THETA_ID_PREFIX},           // þ (U+00FE)

    // 1 Byte
    {"[", 1, TOK_PROTEIN_OPEN},
    {"]", 1, TOK_PROTEIN_CLOSE},
    {"{", 1, TOK_PROTON_OPEN},
    {"}", 1, TOK_PROTON_CLOSE},
    {"|", 1, TOK_SEP},
    {"\"", 1, TOK_STR_DBL_QUOTE},
    {"'", 1, TOK_STR_SGL_QUOTE},
    {">", 1, TOK_WHEN_GT},
    {"<", 1, TOK_WHEN_LT},
    {"!", 1, TOK_MUST},
    {"(", 1, TOK_FEED_OPEN},
    {")", 1, TOK_FEED_CLOSE},
    {"$", 1, TOK_DIRIGENT_PREFIX},
    {"^", 1, TOK_TRANS_ERROR},
    {"#", 1, TOK_COMMENT}
};
#define TOKEN_TABLE_SIZE (sizeof(TOKEN_TABLE) / sizeof(LexerEntry))

// ────────────────────────────────────────────────────────────────
// Helper functions
// ────────────────────────────────────────────────────────────────

static void advance(mcs_lexer_t* lex, int n) {
    for (int i = 0; i < n; i++) {
        if (*lex->pos == '\n') {
            lex->line++; lex->column = 1;
        } else {
            lex->column++;
        }
        lex->pos++;
    }
}

static void skip_whitespace(mcs_lexer_t* lex) {
    while (*lex->pos && isspace((unsigned char)*lex->pos)) {
        advance(lex, 1);
    }
}

// ────────────────────────────────────────────────────────────────
// Public API
// ────────────────────────────────────────────────────────────────

mcs_lexer_t* mcs_lexer_new(const char* input) {
    mcs_lexer_t* lex = malloc(sizeof(mcs_lexer_t));
    if (!lex) return NULL;
    lex->input = input;
    lex->pos = input;
    lex->line = 1;
    lex->column = 1;
    return lex;
}

void mcs_lexer_free(mcs_lexer_t* lex) {
    free(lex);
}

mcs_token_t mcs_lexer_next(mcs_lexer_t* lex) {
    mcs_token_t tok;
    skip_whitespace(lex);

    tok.line = lex->line;
    tok.column = lex->column;
    tok.literal = lex->pos;

    if (*lex->pos == '\0') {
        tok.token_type = TOK_EOF;
        tok.length = 0;
        return tok;
    }

    // 🔥 Maximum-Munch: longest match first
    for (size_t i = 0; i < TOKEN_TABLE_SIZE; i++) {
        const LexerEntry* e = &TOKEN_TABLE[i];
        if (memcmp(lex->pos, e->symbol, e->length) == 0) {
            tok.token_type = e->type;
            tok.length = e->length;

            if (tok.token_type == TOK_COMMENT) {
                while (*lex->pos && *lex->pos != '\n') lex->pos++;
                return mcs_lexer_next(lex);
            }

            advance(lex, tok.length);
            return tok;
        }
    }

    // Fallback: ID (alphanum, _-.)
    if (isalpha((unsigned char)*lex->pos) || *lex->pos == '_') {
        tok.token_type = TOK_ID;
        const char* start = lex->pos;
        while (isalnum((unsigned char)*lex->pos) ||
            *lex->pos == '_' || *lex->pos == '-' || *lex->pos == '.') {
            lex->pos++;
            }
            tok.length = (int)(lex->pos - start);
        return tok;
    }

    // Fallback: NUMBER
    if (isdigit((unsigned char)*lex->pos)) {
        tok.token_type = TOK_NUMBER;
        const char* start = lex->pos;
        while (isdigit((unsigned char)*lex->pos)) lex->pos++;
        tok.length = (int)(lex->pos - start);
        return tok;
    }

    // Fallback: single char
    tok.token_type = TOK_LITERAL;
    tok.length = 1;
    advance(lex, 1);
    return tok;
}

#include "mcs_token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// UTF-8-Hilfsfunktion — bleibt so
// 1. Strukturdefinition — MUSS vor allen Funktionen kommen, die `lex->pos` nutzen
struct mcs_lexer {
    const char* input;
    const char* pos;
    int line, column;
};

// 2. Jetzt dürfen Funktionen `lex->pos` verwenden
static int utf8_match(mcs_lexer_t* lex, const char* pattern) {
    const char* p = lex->pos;      // ← Jetzt bekannt!
    const char* pat = pattern;
    while (*pat && *p == *pat) {
        p++; pat++;
    }
    return *pat == '\0';
}

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

static void advance(mcs_lexer_t* lex, int n) {
    for (int i = 0; i < n; i++) {
        if (*lex->pos == '\n') {
            lex->line++;
            lex->column = 1;
        } else {
            lex->column++;
        }
        lex->pos++;
    }
}

static void skip_whitespace(mcs_lexer_t* lex) {
    while (*lex->pos == ' ' || *lex->pos == '\t') {
        advance(lex, 1);
    }
}

// 🔥 NEU: Alles ab hier auf utf8_match() — KEINE char-Literals mehr!
mcs_token_t mcs_lexer_next(mcs_lexer_t* lex) {
    skip_whitespace(lex);
    mcs_token_t tok = {TOK_INVALID, lex->pos, 0, lex->line, lex->column};

    if (*lex->pos == '\0') {
        tok.type = TOK_EOF;
        return tok;
    }

    // 🔹 Transaktion: ¢! = \xC2\xA2! , !¢ = !\xC2\xA2
    if (utf8_match(lex, "\xC2\xA2!")) {  // ¢!
        tok.type = TOK_TRANS_START;
        tok.length = 3;
        advance(lex, 3);
        return tok;
    }
    if (utf8_match(lex, "!\xC2\xA2")) {  // !¢
        tok.type = TOK_TRANS_END;
        tok.length = 3;
        advance(lex, 3);
        return tok;
    }

    // 🔹 Aktion: » = \xC2\xBB , « = \xC2\xAB
    if (utf8_match(lex, "\xC2\xBB")) {  // »
        tok.type = TOK_ACTION_START;
        tok.length = 2;
        advance(lex, 2);
        return tok;
    }
    if (utf8_match(lex, "\xC2\xAB")) {  // «
        // Prüfe auf ««« = \xC2\xAB\xC2\xAB\xC2\xAB
        if (utf8_match(lex, "\xC2\xAB\xC2\xAB\xC2\xAB")) {
            tok.type = TOK_OP_MARK;
            tok.length = 6;
            advance(lex, 6);
            return tok;
        }
        // Zwei « = \xC2\xAB\xC2\xAB → Fehler
        if (utf8_match(lex, "\xC2\xAB\xC2\xAB")) {
            fprintf(stderr, "[LEXER] E_SYNTAX_OP_INCOMPLETE: Expected third « at line %d, col %d\n", lex->line, lex->column);
            tok.type = TOK_INVALID;
            tok.length = 4;
            advance(lex, 4);
            return tok;
        }
        // Ein «
        tok.type = TOK_ACTION_END;
        tok.length = 2;
        advance(lex, 2);
        return tok;
    }

    // 🔹 Einzelzeichen (ASCII — sicher)
    switch (*lex->pos) {
        case '[': tok.type = TOK_PROTEIN_OPEN; tok.length = 1; advance(lex, 1); return tok;
        case ']': tok.type = TOK_PROTEIN_CLOSE; tok.length = 1; advance(lex, 1); return tok;
        case '{': tok.type = TOK_PROTON_OPEN; tok.length = 1; advance(lex, 1); return tok;
        case '}': tok.type = TOK_PROTON_CLOSE; tok.length = 1; advance(lex, 1); return tok;
        case '|': tok.type = TOK_SEP; tok.length = 1; advance(lex, 1); return tok;
        case '>': tok.type = TOK_WHEN_LT; tok.length = 1; advance(lex, 1); return tok;
        case '<': tok.type = TOK_WHEN_GT; tok.length = 1; advance(lex, 1); return tok;
        case '!': {
            // Achtung: '!¢' wurde schon oben gefangen — hier ist nur '!'-allein
            if (utf8_match(lex, "!\xC2\xA2")) {
                // Sollte nicht hier landen — aber sicher ist sicher
                tok.type = TOK_TRANS_END;
                tok.length = 3;
                advance(lex, 3);
            } else {
                tok.type = TOK_MUST;
                tok.length = 1;
                advance(lex, 1);
            }
            return tok;
        }
        case ';':
            if (*(lex->pos + 1) == ';') {
                tok.type = TOK_PAR_TRANSPORT;
                tok.length = 2;
                advance(lex, 2);
                return tok;
            }
            break;
        case '"': {
            tok.type = TOK_STR_DBL;
            const char* start = lex->pos;
            advance(lex, 1);
            while (*lex->pos && *lex->pos != '"') {
                if (*lex->pos == '\\' && *(lex->pos+1)) advance(lex, 1);
                advance(lex, 1);
            }
            if (*lex->pos == '"') advance(lex, 1);
            tok.length = (int)(lex->pos - start);
            return tok;
        }
        case '\'': {
            tok.type = TOK_STR_SGL;
            const char* start = lex->pos;
            advance(lex, 1);
            while (*lex->pos && *lex->pos != '\'') advance(lex, 1);
            if (*lex->pos == '\'') advance(lex, 1);
            tok.length = (int)(lex->pos - start);
            return tok;
        }
    }

    // 🔹 Unicode-Symbole (rein per utf8_match)
    if (utf8_match(lex, "\xC3\xB8")) {  // ø
        tok.type = TOK_WARP_START;
        tok.length = 2;
        advance(lex, 2);
        return tok;
    }
    if (utf8_match(lex, "\xC2\xB0")) {  // °
        tok.type = TOK_WHEN_NOT;
        tok.length = 2;
        advance(lex, 2);
        return tok;
    }
    if (utf8_match(lex, "\xE2\x80\xA6")) {  // …
        tok.type = TOK_ON_ERROR;
        tok.length = 3;
        advance(lex, 3);
        return tok;
    }
    if (utf8_match(lex, "\xC3\xBE")) {  // þ
        tok.type = TOK_THETA_ID;
        const char* start = lex->pos;
        advance(lex, 2);
        int len = 0;
        while (len < 64 && (
            (*lex->pos >= 'a' && *lex->pos <= 'z') ||
            (*lex->pos >= 'A' && *lex->pos <= 'Z') ||
            (*lex->pos >= '0' && *lex->pos <= '9') ||
            *lex->pos == '_' || *lex->pos == '.' || *lex->pos == '-'
        )) {
            advance(lex, 1);
            len++;
        }
        tok.length = (int)(lex->pos - start);
        return tok;
    }
    if (utf8_match(lex, "\xC2\xB6")) {  // ¶
        if (utf8_match(lex, "\xC2\xB6\xC2\xB6")) {  // ¶¶
            tok.type = TOK_ELSE;
            tok.length = 4;
            advance(lex, 4);
            return tok;
        }
        if (utf8_match(lex, "\xC2\xB6=")) {  // ¶=
            tok.type = TOK_PARALLEL;
            tok.length = 3;
            advance(lex, 3);
            return tok;
        }
        tok.type = TOK_IF;
        tok.length = 2;
        advance(lex, 2);
        return tok;
    }
    // Unicode ’ (U+2019 = \xE2\x80\x99)
    if (utf8_match(lex, "\xE2\x80\x99")) {
        tok.type = TOK_STR_TICK;
        const char* start = lex->pos;
        advance(lex, 3);
        while (*lex->pos) {
            if (utf8_match(lex, "\xE2\x80\x99")) {
                advance(lex, 3);
                break;
            }
            advance(lex, 1);
        }
        tok.length = (int)(lex->pos - start);
        return tok;
    }
    // Unicode ¨ (U+00A8 = \xC2\xA8)
    if (utf8_match(lex, "\xC2\xA8")) {
        tok.type = TOK_BLANKERNER;
        const char* start = lex->pos;
        advance(lex, 2);
        while (*lex->pos) {
            if (utf8_match(lex, "\xC2\xA8")) {
                advance(lex, 2);
                break;
            }
            advance(lex, 1);
        }
        tok.length = (int)(lex->pos - start);
        return tok;
    }

    // Unbekanntes Zeichen
    fprintf(stderr, "[LEXER] Unknown byte 0x%02X at line %d, col %d\n", (unsigned char)*lex->pos, lex->line, lex->column);
    tok.length = 1;
    advance(lex, 1);
    return tok;
}

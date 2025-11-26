#ifndef MCS_TOKEN_H
#define MCS_TOKEN_H

// Token-Typen — strikt nach MCS Kernel Spec v2.7 (kernel lex, 02, 06, 07, 08, 09, 13, 14, 15)
typedef enum {
    TOK_INVALID = 0,

    // Transaktion (02)
    TOK_TRANS_START,   // ¢! (zwei Zeichen, atomar)
    TOK_TRANS_END,     // !¢ (zwei Zeichen, atomar)

    // Aktion (06)
    TOK_ACTION_START,  // »
    TOK_ACTION_END,    // « (ein Zeichen — nie allein bei Operatoren)

    // Argument/Operator-Marker (15)
    TOK_OP_MARK,       // ««« (drei Zeichen — erst dann gültig)

    // Protein & Proton (03, 04)
    TOK_PROTEIN_OPEN,  // [
    TOK_PROTEIN_CLOSE, // ]
    TOK_PROTON_OPEN,   // {
    TOK_PROTON_CLOSE,  // }

    // Trennbefehl (05)
    TOK_SEP,           // | (nur innerhalb []/{} erlaubt)

    // Warp (13)
    TOK_WARP_START,    // ø
    TOK_WARP_END,      // ø (gleiches Zeichen — Kontext: nach øLang|)

    // þ-Identifikation (14)
    TOK_THETA_ID,      // þ[alnum_.-]{1,64} — z. B. þdev, þ1623512

    // Eingaben (07)
    TOK_STR_DBL,       // "..." — Print
    TOK_STR_SGL,       // '...' — System-CMD (ASCII 0x27)
    TOK_STR_TICK,      // ’...’ — MCS-CMD (Unicode U+2019)
    TOK_BLANKERNER,    // ¨...¨ — Blankernenner (Unicode U+00A8)

    // Wahrheiten (08)
    TOK_IF,            // ¶
    TOK_ELSE,          // ¶¶
    TOK_PARALLEL,      // ¶=
    TOK_PAR_TRANSPORT, // ;;

    // Operatoren (09)
    TOK_WHEN_NOT,      // °
    TOK_WHEN_LT,       // >
    TOK_WHEN_GT,       // <
    TOK_MUST,          // !
    TOK_ON_ERROR,      // …

    TOK_EOF
} mcs_token_type_t;

// Token-Struktur: Position + Inhalt (keine Interpretation!)
typedef struct {
    mcs_token_type_t type;
    const char* start;  // Zeiger auf Input-String
    int length;         // Länge des Tokens (z. B. 2 für ¢!, 3 für «««)
    int line, column;   // Für Fehlermeldungen
} mcs_token_t;

// Lexer-API — nur Deklaration (Implementierung in mcs_lexer.c)
typedef struct mcs_lexer mcs_lexer_t;

mcs_lexer_t* mcs_lexer_new(const char* input);
void         mcs_lexer_free(mcs_lexer_t* lex);
mcs_token_t  mcs_lexer_next(mcs_lexer_t* lex);
int          mcs_lexer_peek_char(mcs_lexer_t* lex, int offset);

#endif

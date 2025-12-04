// include/mcs_argument.h — @kernel 15 konform
#ifndef MCS_ARGUMENT_H
#define MCS_ARGUMENT_H

#include "mcs_token.h"   // ← diese Zeile fehlt!

// Gemäß MCS2.9.txt: «««t1, «««%50, «««r3
typedef enum {
    ARG_NONE = 0,
    ARG_MINUS,   // «««-   (6 Bytes: \xC2\xAB×3 + \x2D)
    ARG_PLUS,    // «««+
    ARG_MUL,     // «««·
    ARG_DIV,     // «««:
    ARG_PERCENT, // «««%   → optional mit Zahl: «««%50
    ARG_TIME,    // «««tN  → t + Zahl
    ARG_REBOOT   // «««rN  → r + Zahl
} mcs_arg_type_t;

typedef struct {
    mcs_arg_type_t type;
    int value;   // N bei tN/rN, %N; 0 bei reinen Operatoren
} mcs_argument_t;

// Parser-Hilfe — für mcs_action.c
int mcs_parse_argument(mcs_lexer_t* lex, mcs_argument_t* out);

#endif

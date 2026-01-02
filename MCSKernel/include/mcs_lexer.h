#ifndef MCS_LEXER_H
#define MCS_LEXER_H

#include <stdio.h>

typedef enum {
    TOKEN_TRANS_START,
    TOKEN_TRANS_END,
    TOKEN_WAHRHEIT_TRIGGER,
    TOKEN_OPTION,
    TOKEN_AKTION_START,
    TOKEN_AKTION_ENDE,
    TOKEN_BOXI_ALU_START,
    TOKEN_BOXI_ALU_ENDE,
    TOKEN_BOXI_ALU_INHALT,
    TOKEN_SENTIATOR_REIN,
    TOKEN_SENTIATOR_KANN,
    TOKEN_SENTIATOR_NICHT,
    TOKEN_FEED,
    TOKEN_STRING,
    TOKEN_ARGUMENT_KOMPLEX,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType typ;
    char *wert;
} Token;

// --- DIESE PROTOTYPEN SIND ESSENZIELL FÜR MAIN.C ---
Token* mcs_lexer_erzeuge(const char *quellcode);
void mcs_kernel_takt(const char *quellcode);

#endif

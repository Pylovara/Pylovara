#ifndef MCS_LEXER_H
#define MCS_LEXER_H

#include <stdio.h>

typedef enum {
    TOKEN_TRANS_START,      // ¢|
    TOKEN_TRANS_END,        // |¢
    TOKEN_WAHRHEIT_TRIGGER, // –
    TOKEN_OPTION,           // ·
    TOKEN_AKTION_START,     // »
    TOKEN_AKTION_ENDE,      // «
    TOKEN_BOXI_ALU_START,   // [×
    TOKEN_BOXI_ALU_ENDE,    // ×]
    TOKEN_SENTIATOR_KANN,   // ¶
    TOKEN_SENTIATOR_NICHT,  // ¶¶
    TOKEN_SENTIATOR_REIN,   // ſ
    TOKEN_FEED,             // (1)
    TOKEN_STRING,           // ' ' oder " "
    TOKEN_KOMMENTAR,        // #
    TOKEN_EOF
} TokenTyp;

typedef struct {
    TokenTyp typ;
    char *wert;
} Token;

// Prototyp der Hauptfunktion
Token* mcs_lexer_erzeuge(const char *quellcode);

#endif

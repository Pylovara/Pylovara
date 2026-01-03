#ifndef MCS_LEXER_H
#define MCS_LEXER_H
// OrdnerPfad: /Pylovara/MCSKernel/Logic/mcs_lexer.h

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_TRANS_START,  // ¢!
    TOKEN_TRANS_ENDE,   // !¢
    TOKEN_ASSIGN,       // -= (Scharfschaltung)
    TOKEN_REG_ID,       // [(n)]
    TOKEN_BOXI_ALU,     // ×...×
    TOKEN_BOXI_SHELL,   // '...'
    TOKEN_BOXI_CALLIS,  // "..."
    TOKEN_AKTION_START, // »
    TOKEN_AKTION_ENDE,  // «
    TOKEN_SENTI_TRUE,   // ¶
    TOKEN_SENTI_FALSE,  // ¶¶
    TOKEN_REINHEIT,     // ſ  (Regel der Reinheit)
    TOKEN_FORTSCHRITT,  // –  (Gatter-Schaltung / Fortschritt)
    TOKEN_BOXI_START,   // [
    TOKEN_BOXI_ENDE,    // ]
    TOKEN_SENTI_MATCH   // !
} TokenType;

typedef struct {
    TokenType typ;
    char *wert;
    int register_nr; // Optional für b64 Direktzugriff
} Token;

Token* mcs_lexer_erzeuge(const char *quellcode);

#endif

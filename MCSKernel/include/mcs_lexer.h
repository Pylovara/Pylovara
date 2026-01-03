#ifndef MCS_LEXER_H
#define MCS_LEXER_H

typedef enum {
    TOKEN_TRANS_START,   // ¢!
    TOKEN_TRANS_ENDE,    // !¢
    TOKEN_BOXI_ALU,      // ×...×
    TOKEN_BOXI_CALLIS,   // "..."
    TOKEN_BOXI_SHELL,    // '...'
    TOKEN_BOXI_MCS_CMD,  // ~...~
    TOKEN_BOXI_CALL_CONTROL, // ,...,
    TOKEN_AKTION_START,  // »
    TOKEN_AKTION_ENDE,    // «
    TOKEN_SENTI_TRUE,    // ¶
    TOKEN_SENTI_FALSE,   // ¶¶
    TOKEN_SENTI_VAKUUM,  // ŧ
    TOKEN_SENTI_MATCH,   // !
    TOKEN_SENTI_NEGATION, // °
    TOKEN_SENTI_MEHRWERT, // >>
    TOKEN_SENTI_MINDERWERT, // <<
    TOKEN_REINHEIT,      // ſ
    TOKEN_FORTSCHRITT,   // –
    TOKEN_REG_ID,        // (n)
    TOKEN_BOXI_START,    // [
    TOKEN_BOXI_ENDE,      // ]
    TOKEN_EOF            // Ende der Datei
} TokenType;

typedef struct {
    TokenType typ;
    char *wert;
} Token;

Token* mcs_lexer_erzeuge(const char *quellcode);

#endif

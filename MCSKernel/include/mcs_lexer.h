#ifndef MCS_LEXER_H
#define MCS_LEXER_H

typedef enum {
    TOKEN_TRANS_START, // ¢|
    TOKEN_TRANS_END,   // |¢
    TOKEN_WAHRHEIT_TRIGGER, // –
    TOKEN_OPTION_A, // ·
    TOKEN_OPTION_B, // ··
    TOKEN_OPTION_C, // ···
    TOKEN_OPTION_D, // ····
    TOKEN_OPTION_E, // ·····
    TOKEN_PROGRESS, // :
    TOKEN_PARALLEL_PROCESS, // <
    TOKEN_PARALLEL_TRANSPORT, // >
    TOKEN_CMD_SPECIAL, // ~cmd~
    TOKEN_BOXI, // [×...×]
    TOKEN_FEED, // (1)"value"
    TOKEN_STRING, // "text"
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *mcs_lexer(const char *code);

#endif

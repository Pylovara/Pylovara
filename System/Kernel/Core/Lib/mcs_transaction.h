#ifndef MCS_TRANSACTION_H
#define MCS_TRANSACTION_H

#include "../Logic/mcs_token.h"
#include <stdbool.h>

typedef struct {
    mcs_token_t start;   // TOK_TRANS_START
    mcs_token_t end;     // TOK_TRANS_END
    bool is_valid;       // true, wenn Rahmen korrekt
} mcs_transaction_t;

// Öffentliche API
bool mcs_parse_transaction(mcs_lexer_t* lex, mcs_transaction_t* out);

#endif // MCS_TRANSACTION_H

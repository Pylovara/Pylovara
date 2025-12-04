// include/mcs_transaktion.h — v2.9 Transaktions-API
#ifndef MCS_TRANS_H
#define MCS_TRANS_H

#include "mcs_token.h"

typedef struct {
    mcs_token_t trans_start;   // ¢! Token
    mcs_token_t trans_end;     // !¢ Token
    int is_valid;
} mcs_transaction_t;

// Public API
int mcs_parse_transaction(mcs_lexer_t* lex, mcs_transaction_t* out);

#endif

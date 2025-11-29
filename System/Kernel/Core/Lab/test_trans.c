#include "../Lib/mcs_transaction.h"
#include "../Logic/mcs_token.h"
#include <stdio.h>

int main() {
    const char* code = "¢!\n»['echo'|\"Hallo\"]«\n!¢";
    mcs_lexer_t* lex = mcs_lexer_new(code);
    mcs_transaction_t trans;

    if (mcs_parse_transaction(lex, &trans) && trans.is_valid) {
        printf("✅ Transaktion gültig: %.*s … %.*s\n",
               trans.start.length, trans.start.literal,
               trans.end.length, trans.end.literal);
    } else {
        printf("❌ Transaktion ungültig\n");
    }

    mcs_lexer_free(lex);
    return 0;
}

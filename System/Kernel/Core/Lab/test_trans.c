// Lab/test_trans.c
#include <stdio.h>
#include "mcs_token.h"
#include "mcs_transaction.h"

int main() {
    const char* input = "»['echo'|\"Hallo\"]«";
    mcs_lexer_t* lex = mcs_lexer_new(input);
    mcs_transaction_t trans = {0};

    if (mcs_parse_transaction(lex, &trans) && trans.is_valid) {
        printf("✅ Transaktion erkannt:\n"
        "   Start: %.*s (Zeile %d)\n"
        "   Ende:  %.*s (Zeile %d)\n",
               trans.trans_start.length, trans.trans_start.literal, trans.trans_start.line,
               trans.trans_end.length,   trans.trans_end.literal,   trans.trans_end.line);
    } else {
        printf("❌ Keine gültige Transaktion gefunden.\n");
    }

    mcs_lexer_free(lex);
    return 0;
}

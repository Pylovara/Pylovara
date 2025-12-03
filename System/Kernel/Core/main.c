// main.c — Minimaler MCS Kernel-Runner (v2.9)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcs_token.h"
#include "mcs_transaction.h"

int main(int argc, char** argv) {
    printf("ᴾʸˡᵒᵛᵃʳᵃ Kernel v2.9 | MCS Core Online\n");
    printf("» ready. type MCS code or 'exit' to quit.\n");

    char line[1024];
    while (1) {
        printf("mcs> ");
        if (!fgets(line, sizeof(line), stdin)) break;

        // Entferne Zeilenumbruch
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, "exit") == 0) break;

        if (strlen(line) == 0) continue;

        mcs_lexer_t* lex = mcs_lexer_new(line);
        if (!lex) {
            printf("🔥 Lexer init failed.\n");
            continue;
        }

        mcs_token_t tok = mcs_lexer_next(lex);
        if (tok.token_type == TOK_TRANS_START) {
            mcs_transaction_t trans = {0};
            if (mcs_parse_transaction(lex, &trans) && trans.is_valid) {
                printf("✅ Transaktion: %.*s ... %.*s\n",
                       trans.trans_start.length, trans.trans_start.literal,
                       trans.trans_end.length, trans.trans_end.literal);
            } else {
                printf("❌ Ungültige Transaktion.\n");
            }
        } else if (tok.token_type == TOK_ACTION_START) {
            printf("⚙️ Aktion erkannt — Parser erweitern?\n");
        } else {
            printf("🔍 Token: %d (%.*s)\n", tok.token_type, tok.length, tok.literal);
        }

        mcs_lexer_free(lex);
    }

    printf("👋 Kernel shutdown.\n");
    return 0;
}

// Lab/test_action.c — MCS v2.9 Action-Test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcs_action.h"

int main() {
    // ✅ Korrekter Input (1x » am Anfang, 1x « nach Protein, dann «««t1)
    const char input_bytes[] = {
        0xC2, 0xBB,                    // »
        0x5B,                          // [
        0x27, 0x70, 0x67, 0x72, 0x65, 0x70, 0x27,  // 'pgrep'
        0x7C,                          // |
        0xC2, 0xA8, 0x66, 0x69, 0x72, 0x65, 0x66, 0x6F, 0x78, 0xC2, 0xA8,  // ¨firefox¨
        0x7C,                          // |
        0x28, 0x31, 0x29,              // (1)
        0xC2, 0xA8, 0x24, 0x70, 0x67, 0x72, 0x65, 0x70, 0x20, 0x66, 0x69, 0x72, 0x65, 0x66, 0x6F, 0x78, 0xC2, 0xA8,  // ¨$pgrep firefox¨
        0x5D,                          // ]
        0xC2, 0xAB,                    // «
        0xC2, 0xAB, 0xC2, 0xAB,        // «««
        0x74, 0x31,                    // t1
        0x00                           // \0
    };
    const char* input = (const char*)input_bytes;
    mcs_action_t* a = mcs_parse_action(input);
    if (!a) {
        printf("❌ Parse error in »%s«\n", input);
        return 1;
    }

    printf("✅ Action parsed:\n");
    printf("   cmd            = %s\n", a->cmd ? a->cmd : "(null)");
    printf("   arg1           = %s\n", a->arg1 ? a->arg1 : "(null)");
    printf("   feed.id        = %d\n", a->feed.id);
    printf("   blankernenner  = %s\n", a->blankernenner ? a->blankernenner : "(null)");
    printf("   arg.type       = %d (%s)\n", a->arg.type,
           (a->arg.type == ARG_TIME) ? "TIME" :
           (a->arg.type == ARG_REBOOT) ? "REBOOT" :
           (a->arg.type == ARG_PERCENT) ? "PERCENT" :
           (a->arg.type == ARG_MINUS) ? "MINUS" : "OTHER");
    printf("   arg.value      = %d\n", a->arg.value);

    if (a->feed.id > 0 && a->blankernenner) {
        printf("→ Feed #%d mit Blankernenner: %s\n", a->feed.id, a->blankernenner);
    }

    mcs_free_action(a);
    return 0;
}

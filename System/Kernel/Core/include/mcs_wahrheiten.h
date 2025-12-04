// include/mcs_wahrheiten.h — @kernel 08 konform
// include/mcs_wahrheiten.h — @kernel 08 konform, ZYKELFREI
#ifndef MCS_WAHRHEITEN_H
#define MCS_WAHRHEITEN_H

#include "mcs_token.h"   // ← nur das, was *wirklich* gebraucht wird

// Nur Token-basierte Typen — keine Strukturen!
typedef enum {
    WAHR_NONE = 0,
    WAHR_IF,          // ¶
    WAHR_ELSE,        // ¶¶
    WAHR_PARALLEL_RUN, // ¶=
    WAHR_PARALLEL_TRANSPORT, // ;;
    WAHR_WHEN_NOT,    // °
    WAHR_WHEN_GT,     // >
    WAHR_WHEN_LT,     // <
    WAHR_MUST,        // !
    WAHR_ON_ERROR,    // …
    WAHR_TRANS_ERROR, // ^
    WAHR_DATA_RESIDUE // ſ
} mcs_wahrheit_t;

// Nur Funktionen, die *Tokens* prüfen — keine Strukturen!
int mcs_is_wahrheit(mcs_token_type_t tt);
mcs_wahrheit_t mcs_token_to_wahrheit(mcs_token_type_t tt);

#endif

// include/mcs_action.h — MCS Action API v2.9
#ifndef MCS_ACTION_H
#define MCS_ACTION_H

#include "mcs_token.h"   // muss zuerst kommen — enthält mcs_token_type_t
#include "mcs_feed.h"    // danach — benötigt mcs_feed_t

// Argument-Typen (gemäß @kernel 15)
typedef enum {
    ARG_NONE = 0,
    ARG_MINUS,
    ARG_PLUS,
    ARG_MUL,
    ARG_DIV,
    ARG_PERCENT,
    ARG_TIME,
    ARG_REBOOT
} mcs_arg_type_t;

typedef struct {
    mcs_arg_type_t type;
    int value;
} mcs_argument_t;

// Action-Struktur (gemäß @kernel 06 + 10)
typedef struct {
    char* cmd;
    char* arg1;
    mcs_feed_t feed;         // { id, value, is_set }
    char* blankernenner;
    mcs_argument_t arg;      // { type, value }
} mcs_action_t;


// Public API
mcs_action_t* mcs_parse_action(const char* input);
void          mcs_free_action(mcs_action_t* a);

// Inline-Hilfen (nur Deklarationen — Definitionen optional in .c)
static inline char* token_to_string(mcs_token_t tok);
static inline int extract_feed_id(mcs_token_t tok);

#endif // MCS_ACTION_Hf

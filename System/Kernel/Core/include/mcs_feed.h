// include/mcs_feed.h — MCS Feed Registry (v2.9)
#ifndef MCS_FEED_H
#define MCS_FEED_H

#include <stddef.h>

#define MCS_FEED_MAX 256

typedef struct {
    int id;
    char* value;     // ← das ist der *evaluierte* Wert, nicht der Ausdruck
    int is_set;
} mcs_feed_t;

// Public API
int  mcs_feed_set(int id, const char* value);
const char* mcs_feed_get(int id);
void mcs_feed_clear(int id);
void mcs_feed_reset_all(void);

#endif // MCS_FEED_H

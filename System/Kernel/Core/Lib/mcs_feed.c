// Lib/mcs_feed.c
#include <stdlib.h>
#include <string.h>
#include "mcs_feed.h"

static mcs_feed_t feed_table[MCS_FEED_MAX] = {{0}};

int mcs_feed_set(int id, const char* value) {
    if (id < 0 || id >= MCS_FEED_MAX) return -1;
    mcs_feed_t* f = &feed_table[id];

    // Alten Wert freigeben
    free(f->value);
    f->value = value ? strdup(value) : NULL;
    f->id = id;
    f->is_set = (value != NULL);
    return 0;
}

const char* mcs_feed_get(int id) {
    if (id < 0 || id >= MCS_FEED_MAX) return NULL;
    mcs_feed_t* f = &feed_table[id];
    return f->is_set ? f->value : NULL;
}

void mcs_feed_clear(int id) {
    if (id < 0 || id >= MCS_FEED_MAX) return;
    free(feed_table[id].value);
    feed_table[id].value = NULL;
    feed_table[id].is_set = 0;
}

void mcs_feed_reset_all(void) {
    for (int i = 0; i < MCS_FEED_MAX; i++) {
        mcs_feed_clear(i);
    }
}

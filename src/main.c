#include <assert.h>
#include <stdio.h>

#include "kv.h"

void main() {
    kv_t *db = kv_init(16);
    assert(db != NULL);
    assert(db->capacity == 16);
    assert(db->count == 0);
    kv_free(db);
}

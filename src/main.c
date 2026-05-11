#include <assert.h>
#include <stdio.h>

#include "kv.h"

#define DB_SIZE 5

int main() {
    kv_t *db = kv_init(16);

    kv_put(db, "name", "alice");
    kv_put(db, "city", "berlin");
    kv_put(db, "city", "vienna");
    kv_put(db, "lang", "c");

    kv_delete(db, "city");

    kv_free(db);
    return 0;
}

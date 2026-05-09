#include <assert.h>
#include <stdio.h>

#include "kv.h"

#define DB_SIZE 5

int main() {
    kv_t *db = kv_init(DB_SIZE);
    assert(db != NULL);
    assert(db->capacity == DB_SIZE);
    assert(db->count == 0);

    char *result = kv_get(db, "foo");
    if (result) {
        printf("Found foo: %s\n", result);
    } else {
        printf("foo not found\n");
    }

    kv_put(db, "hallo", "welt");
    kv_put(db, "bli", "blu");
    kv_put(db, "foo", "bar");
    kv_put(db, "new", "value");
    kv_put(db, "last", "one");
    kv_print_db(db);

    result = kv_get(db, "foo");
    if (result) {
        printf("Found foo: %s\n", result);
    } else {
        printf("foo not found\n");
    }

    kv_put(db, "foo", "haaaallllooooo");
    kv_print_db(db);

    result = kv_get(db, "foo");
    if (result) {
        printf("Found foo: %s\n", result);
    } else {
        printf("foo not found\n");
    }

    kv_delete(db, "bli");
    kv_delete(db, "new");
    kv_delete(db, "last");
    kv_delete(db, "hallo");
    kv_delete(db, "nope");
    kv_delete(db, "foo");
    kv_print_db(db);

    result = kv_get(db, "foo");
    if (result) {
        printf("Found foo: %s\n", result);
    } else {
        printf("foo not found\n");
    }

    kv_free(db);

    return 0;
}

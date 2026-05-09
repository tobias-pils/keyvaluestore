#include <assert.h>
#include <stdio.h>

#include "kv.h"

#define DB_SIZE 5

int main() {
    kv_t *db = kv_init(DB_SIZE);
    assert(db != NULL);
    assert(db->capacity == DB_SIZE);
    assert(db->count == 0);

    kv_put(db, "hallo", "welt");
    kv_put(db, "bli", "blu");
    kv_put(db, "foo", "bar");
    kv_put(db, "new", "value");
    kv_put(db, "last", "one");
    kv_print_db(db);

    kv_delete(db, "bli");
    kv_delete(db, "new");
    kv_delete(db, "last");
    kv_delete(db, "hallo");
    kv_delete(db, "nope");
    kv_delete(db, "foo");
    kv_print_db(db);

    kv_put(db, "test1", "123");
    kv_print_db(db);
    kv_put(db, "test1", "987");
    kv_print_db(db);
    kv_put(db, "test2", "123");
    kv_put(db, "test3", "123");
    kv_put(db, "test4", "123");
    kv_put(db, "test5", "123");
    kv_print_db(db);

    kv_free(db);

    return 0;
}

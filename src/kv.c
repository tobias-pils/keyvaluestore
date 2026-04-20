#include <stdlib.h>
#include <stdio.h>

#include "kv.h"

kv_t *kv_init (size_t capacity) {
    if (capacity < 1) return NULL;

    kv_entry *entries = calloc(sizeof(kv_entry), capacity);
    if (entries == NULL) {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    kv_t *db = malloc(sizeof(kv_t));
    if (db == NULL) {
        free(entries);
        printf("Failed to allocate memory\n");
        return NULL;
    }

    db->capacity = capacity;
    db->count = 0;
    db->entries = entries;

    return db;
}

void kv_free(kv_t *db) {
    free(db->entries);
    free(db);
}

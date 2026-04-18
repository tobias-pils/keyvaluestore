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

    kv_t *table = malloc(sizeof(kv_t));
    if (table == NULL) {
        free(entries);
        printf("Failed to allocate memory\n");
        return NULL;
    }

    table->capacity = capacity;
    table->count = 0;
    table->entries = entries;

    return table;
}

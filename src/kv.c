#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kv.h"

#define TOMBSTONE 0x1

void kv_print_db(kv_t *db) {
    printf("Count: %ld/%ld\n", db->count, db->capacity);
    for (size_t i = 0; i < db->capacity; i++) {
        if (db->entries[i].key) {
            if (db->entries[i].key == (void *)TOMBSTONE) {
                printf("[%ld] x\n", i);
            } else {
                printf("[%ld] %s: %s\n",
                        i,
                        db->entries[i].key,
                        db->entries[i].value);
            }
        }
    }
    printf("\n");
}

kv_t *kv_init (size_t capacity) {
    if (capacity < 1) return NULL;

    kv_entry_t *entries = calloc(sizeof(kv_entry_t), capacity);
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
    if (!db) return;

    for (size_t i = 0; i < db->capacity; i++) {
        kv_entry_t *entry = &db->entries[i];
        if (entry->key && entry->key != (void *)TOMBSTONE) {
            free(entry->key);
            free(entry->value);
        }
    }

    free(db->entries);
    free(db);
}

size_t hash(char *val, int capacity) {
    size_t hash = 0x0000111122223333;

    while(*val) {
        hash ^= *val;
        hash = hash << 8;
        hash += *val;

        val++;
    }

    return hash % capacity;
}

int kv_put(kv_t *db, char *key, char *value) {
    if (!db || !key || !value) return -1;

    size_t idx = hash(key, db->capacity);
    bool tombstone_hit = false;
    size_t tombstone_idx = 0;

    for (size_t i = 0; i < db->capacity; i++) {
        size_t real_idx = (idx + i) % db->capacity;

        kv_entry_t *entry = &db->entries[real_idx];

        if (!entry->key) {
            if (tombstone_hit) break;

            char *newkey = strdup(key);
            char *newvalue = strdup(value);
            if (!newkey || !newvalue) {
                free(newkey);
                free(newvalue);
                return -1;
            }
            entry->key = newkey;
            entry->value = newvalue;
            db->count++;
            return 0;
        }

        if (entry->key == (void *)TOMBSTONE) {
            if (!tombstone_hit) {
                tombstone_hit = true;
                tombstone_idx = real_idx;
            }
            continue;
        }

        if (!strcmp(entry->key, key)) {
            char *newvalue = strdup(value);
            if (!newvalue) return -1;
            free(entry->value);
            entry->value = newvalue;
            return 0;
        }
    }

    if (tombstone_hit) {
        kv_entry_t *entry = &db->entries[tombstone_idx];
        char *newkey = strdup(key);
        char *newvalue = strdup(value);
        if (!newkey || !newvalue) {
            free(newkey);
            free(newvalue);
            return -1;
        }
        entry->key = newkey;
        entry->value = newvalue;
        db->count++;
        return 0;
    }


    // the db is occupied
    return -2;
}

int kv_delete(kv_t *db, char *key) {
    if (!db || !key) return -1;

    size_t idx = hash(key, db->capacity);

    for (size_t i = 0; i < db->capacity; i++) {
        size_t real_idx = (idx + i) % db->capacity;

        kv_entry_t *entry = &db->entries[real_idx];

        if (!entry->key) return -1;

        if (entry->key == (void *)TOMBSTONE) continue;

        if (!strcmp(entry->key, key)) {
            free(entry->key);
            free(entry->value);
            entry->key = (void *)TOMBSTONE;
            entry->value = NULL;
            db->count--;
            return 0;
        }
    }
    
    return -1;
}

char *kv_get(kv_t *db, char *key) {
    if (!db || !key) return NULL;

    size_t idx = hash(key, db->capacity);

    for (size_t i = 0; i < db->capacity; i++) {
        size_t real_idx = (idx + i) % db->capacity;

        kv_entry_t *entry = &db->entries[real_idx];

        if (!entry->key) return NULL;

        if (entry->key == (void *)TOMBSTONE) continue;

        if (!strcmp(entry->key, key)) {
            return entry->value;
        }
    }
    
    return NULL;
}

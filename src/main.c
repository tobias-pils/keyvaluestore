#include <stdio.h>

#include "kv.h"

void main() {
    kv_t *table = kv_init(3);
    printf("%p\n", table);
    printf("%ld\n", table->capacity);
    printf("%ld\n", table->count);
}

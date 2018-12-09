#include "array.h"

void generic_array_free(struct generic_array *a) {
    free(a->data);
    a->data = NULL;
    a->size = 0;
    a->length = 0;
}

void generic_array_ensure_size(struct generic_array *a, size_t element_size, int requested_size) {
    if (a->size >= requested_size) return;
    int new_size = (a->size < 8 ? 8 : a->size);
    while (new_size < requested_size) {
        new_size *= 2;
    }
    void *new_data = realloc(a->data, new_size * element_size);
    a->data = new_data;
    a->size = new_size;
}

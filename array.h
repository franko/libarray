#pragma once
#include <stdlib.h>

struct generic_array {
    void *data;
    int size;
    int length;
};

extern void generic_array_free(struct generic_array *a);

extern void generic_array_ensure_size(struct generic_array *a, size_t element_size, int requested_size);

#define declare_array(type) \
    struct array_ ## type ## _struct { type* data; size_t size; int length; }; \
    typedef struct array_ ## type ## _struct array_ ## type[1]; \
    extern void array_ ## type ## _free(array_ ## type a); \
    extern void array_ ## type ## _push(array_ ## type a, type v)

#define declare_array_inline(type) \
    struct array_ ## type ## _struct { type* data; size_t size; int length; }; \
    typedef struct array_ ## type ## _struct array_ ## type[1]; \
    static void array_ ## type ## _free(array_ ## type a) { \
        generic_array_free((struct generic_array *)a); \
    } \
    static void array_ ## type ## _push(array_ ## type a, type v) { \
        generic_array_ensure_size((struct generic_array *)a, sizeof(type), a->length + 1); \
        a->data[a->length] = v; \
        a->length ++; \
    }

#define implement_array(type) \
    void array_ ## type ## _free(array_ ## type a) { \
        generic_array_free((struct generic_array *)a); \
    } \
    void array_ ## type ## _push(array_ ## type a, type v) { \
        generic_array_ensure_size((struct generic_array *)a, sizeof(type), a->length + 1); \
        a->data[a->length] = v; \
        a->length ++; \
    }

#define array(type) array_ ## type
#define array_free(type) array_ ## type ## _free
#define array_push(type) array_ ## type ## _push

#define array_init() {{NULL, 0, 0 }}

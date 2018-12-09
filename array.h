#pragma once
#include <stdlib.h>

struct generic_array {
    void *data;
    int size;
    int length;
};

#define array_method(type, name) array_ ## type ## _ ## name
#define array_type_decl(type) \
    struct array_ ## type { type* data; size_t size; int length; }; \
    typedef struct array_ ## type array_ ## type[1]

extern void generic_array_free(struct generic_array *a);
extern void generic_array_ensure_size(struct generic_array *a, size_t element_size, int requested_size);

#define declare_array(type) \
    array_type_decl(type); \
    extern void array_method(type, free)(array_ ## type a); \
    extern void array_method(type, push)(array_ ## type a, type v)

#define declare_array_inline(type) \
    array_type_decl(type); \
    static void array_method(type, free)(array_ ## type a) { \
        generic_array_free((struct generic_array *)a); \
    } \
    static void array_method(type, push)(array_ ## type a, type v) { \
        generic_array_ensure_size((struct generic_array *)a, sizeof(type), a->length + 1); \
        a->data[a->length] = v; \
        a->length ++; \
    }

#define implement_array(type) \
    void array_method(type, free)(array_ ## type a) { \
        generic_array_free((struct generic_array *)a); \
    } \
    void array_method(type, push)(array_ ## type a, type v) { \
        generic_array_ensure_size((struct generic_array *)a, sizeof(type), a->length + 1); \
        a->data[a->length] = v; \
        a->length ++; \
    }

#define array(type) array_ ## type
#define array_free(type) array_method(type, free)
#define array_push(type) array_method(type, push)

#define array_init() {{NULL, 0, 0 }}

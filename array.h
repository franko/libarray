#pragma once
#include <stdlib.h>

struct generic_array {
    void *data;
    int size;
    int length;
};

#define array(type) array_ ## type
#define array_type_decl(type) \
    struct array(type) { type* data; size_t size; int length; }; \
    typedef struct array(type) array(type)[1]
#define array_method(type, name) array_ ## type ## _ ## name

#define array_function_free(type) \
    void array_method(type, free)(array(type) a) { \
        generic_array_free((struct generic_array *)a); \
    }

#define array_function_push(type) \
    void array_method(type, push)(array(type) a, type v) { \
        generic_array_ensure_size((struct generic_array *)a, sizeof(type), a->length + 1); \
        a->data[a->length] = v; \
        a->length ++; \
    }

#define array_function_get(type) \
    type array_method(type, get)(array(type) a, int i) { \
        return a->data[i]; \
    }

#define array_function_set(type) \
    void array_method(type, set)(array(type) a, int i, type value) { \
        a->data[i] = value; \
    }

extern void generic_array_free(struct generic_array *a);
extern void generic_array_ensure_size(struct generic_array *a, size_t element_size, int requested_size);

#define declare_array(type) \
    array_type_decl(type); \
    extern void array_method(type, free)(array(type) a); \
    extern void array_method(type, push)(array(type) a, type v); \
    static array_function_get(type) \
    static array_function_set(type)

#define declare_array_inline(type) \
    array_type_decl(type); \
    static array_function_free(type) \
    static array_function_push(type) \
    static array_function_get(type) \
    static array_function_set(type)

#define implement_array(type) \
    array_function_free(type) \
    array_function_push(type)

#define array_free(type) array_method(type, free)
#define array_push(type) array_method(type, push)
#define array_get(type) array_method(type, get)
#define array_set(type) array_method(type, set)
#define element(a, i) (a)->data[i]

#define array_init() {{NULL, 0, 0 }}

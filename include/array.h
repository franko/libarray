#pragma once
#include <stdlib.h>

struct generic_array {
    void *data;
    int size;
    int length;
};

#define array(type) array_ ## type
#define array_ptr(type) struct array(type) *

/* The macro below should be used when the argument should to be evaluated
   before the macro body evaluation. The reason is that the string concatenation
   of "array" would otherwise prevent the evaluation of the argument.

   See "Macros that call other macros that stringize or concatenate" in:
   https://gcc.gnu.org/onlinedocs/cpp/Argument-Prescan.html */
#define ARRAY_X(type) array(type)

#define array_type_decl(type) \
    struct array(type) { type* data; int size; int length; }; \
    typedef struct array(type) array(type)[1]
#define array_method(type, name) array_ ## type ## _ ## name

/* See comment above for ARRAY_X,
   "Macros that call other macros that stringize or concatenate". */
#define ARRAY_METHOD_X(type, name) array_method(type, name)

#define ARRAY_INIT_MINSIZE 8

#define ARRAY_NEW_IMPL(type) \
    array_ptr(type) array_method(type, new)() { \
        array_ptr(type) a = malloc(sizeof(struct array(type))); \
        if (a == NULL) { return NULL; } \
        *a = (struct array(type)) {NULL, 0, 0}; \
        return a; \
    }

#define ARRAY_DELETE_IMPL(type) \
    void array_method(type, delete)(array_ptr(type) a) { \
        generic_array_free((struct generic_array *)a); \
        free(a); \
    }

#define ARRAY_FREE_IMPL(type) \
    void array_method(type, free)(array(type) a) { \
        generic_array_free((struct generic_array *)a); \
    }

#define ARRAY_PUSH_IMPL(type) \
    int array_method(type, push)(array(type) a, type v) { \
        if (generic_array_ensure_size((struct generic_array *)a, sizeof(type), a->length + 1)) { \
            return 1; \
        } \
        a->data[a->length] = v; \
        a->length ++; \
        return 0; \
    }

#define ARRAY_GET_IMPL(type) \
    type array_method(type, get)(array(type) a, int i) { \
        return a->data[i]; \
    }

#define ARRAY_SET_IMPL(type) \
    void array_method(type, set)(array(type) a, int i, type value) { \
        a->data[i] = value; \
    }

extern void generic_array_free(struct generic_array *a);
extern int generic_array_ensure_size(struct generic_array *a, int element_size, int requested_size);

#define declare_array(type) \
    array_type_decl(type); \
    extern void array_method(type, free)(array(type) a); \
    extern int array_method(type, push)(array(type) a, type v); \
    static inline ARRAY_GET_IMPL(type) \
    static inline ARRAY_SET_IMPL(type) \
    static inline ARRAY_NEW_IMPL(type) \
    static inline ARRAY_DELETE_IMPL(type)

#define declare_array_inline(type) \
    array_type_decl(type); \
    static inline ARRAY_FREE_IMPL(type) \
    static inline ARRAY_PUSH_IMPL(type) \
    static inline ARRAY_GET_IMPL(type) \
    static inline ARRAY_SET_IMPL(type) \
    static inline ARRAY_NEW_IMPL(type) \
    static inline ARRAY_DELETE_IMPL(type)

#define implement_array(type) \
    ARRAY_FREE_IMPL(type) \
    ARRAY_PUSH_IMPL(type)

#define array_new(type) array_method(type, new)
#define array_free(type) array_method(type, free)
#define array_delete(type) array_method(type, delete)
#define array_push(type) array_method(type, push)
#define array_get(type) array_method(type, get)
#define array_set(type) array_method(type, set)
#define element(a, i) ((a)->data[i])

#define array_init() {{NULL, 0, 0 }}

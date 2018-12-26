#pragma once
#include "array.h"

#define ARRAY_SEARCH_METHOD(type, method_name, predicate) array_method(type ## _ ## predicate, method_name)

#define ARRAY_SEARCH_FROM_IMPL(type, predicate) \
    int ARRAY_SEARCH_METHOD(type, search_from, predicate)(array(type) a, int index) { \
        for (int i = index; i < a->length; i++) { \
            if (predicate(element(a, i))) { \
                return i; \
            } \
        } \
        return -1; \
    }

#define ARRAY_SEARCH_IMPL(type, predicate) \
    int ARRAY_SEARCH_METHOD(type, search, predicate)(array(type) a) { \
        return ARRAY_SEARCH_METHOD(type, search_from, predicate)(a, 0); \
    }

#define declare_array_search_inline(type, predicate) \
    static inline ARRAY_SEARCH_FROM_IMPL(type, predicate) \
    static inline ARRAY_SEARCH_IMPL(type, predicate)

#define array_search_from(type, predicate) ARRAY_SEARCH_METHOD(type, search_from, predicate)
#define array_search(type, predicate) ARRAY_SEARCH_METHOD(type, search, predicate)

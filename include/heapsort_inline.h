/* Provides heapsort functions:

   - array_heapsort(type, compare), sort the whole array
   - array_heapsort_range(type, compare), sort the array in a given range of indexes.

   parametred by the type of array values and the name of a compare function.

   Should be used by declaring in the source code:

   declare_array_heapsort_inline(type, compare);

   Code adapted from:

   https://github.com/ladc/lgsl/blob/master/lgsl/sort.lua

   adapted, in turn, from GNU libstdc++'s source code. */

#pragma once
#include "array.h"

#define HEAPSORT_METHOD(type, method_name, compare) array_method(type ## _ ## compare, method_name)

#define HEAPSORT_PUSH_HEAP(type, compare) \
void HEAPSORT_METHOD(type, push_heap, compare)(array(type) list, int first, int hole, int top, type value) { \
    int parent = (hole - 1) / 2; \
    while (hole > top && compare(element(list, first + parent), value)) { \
        element(list, first + hole) = element(list, first + parent); \
        hole = parent; \
        parent = (hole - 1) / 2; \
    } \
    element(list, first + hole) = value; \
}

#define HEAPSORT_ADJUST_HEAP(type, compare) \
void HEAPSORT_METHOD(type, adjust_heap, compare)(array(type) list, int first, int hole, int len, type value) { \
    int top = hole; \
    int second = hole; \
    while (second < (len - 1) / 2) { \
        second = 2 * (second + 1); \
        if (compare(element(list, first + second), element(list, first + (second - 1)))) { \
            second = second - 1; \
        } \
        element(list, first + hole) = element(list, first + second); \
        hole = second; \
    } \
    if ((len & 1) == 0 && second == (len - 2) / 2) { \
        second = 2 * (second + 1); \
        element(list, first + hole) = element(list, first + (second - 1)); \
        hole = second - 1; \
    } \
    HEAPSORT_METHOD(type, push_heap, compare)(list, first, hole, top, value); \
}

#define HEAPSORT_POP_HEAP(type, compare) \
void HEAPSORT_METHOD(type, pop_heap, compare)(array(type) list, int first, int last, int result) { \
    type value = element(list, result); \
    element(list, result) = element(list, first); \
    HEAPSORT_METHOD(type, adjust_heap, compare)(list, first, 0, last - first, value); \
}

#define HEAPSORT_MAKE_HEAP(type, compare) \
void HEAPSORT_METHOD(type, make_heap, compare)(array(type) list, int first, int last) { \
    if (last - first < 2) { \
        return; \
    } \
    int len = last - first; \
    int parent = (len - 2) / 2; \
    while (1) { \
        type value = element(list, first + parent); \
        HEAPSORT_METHOD(type, adjust_heap, compare)(list, first, parent, len, value); \
        if (parent == 0) { \
            return; \
        } \
        parent = parent - 1; \
    } \
}

#define HEAPSORT_HEAP_SELECT(type, compare) \
void HEAPSORT_METHOD(type, heap_select, compare)(array(type) list, int first, int middle, int last) { \
    HEAPSORT_METHOD(type, make_heap, compare)(list, first, middle); \
    for (int i = middle; i < last; i++) { \
        if (compare(element(list, i), element(list, first))) { \
            HEAPSORT_METHOD(type, pop_heap, compare)(list, first, middle, i); \
        } \
    } \
}

#define HEAPSORT_SORT_HEAP(type, compare) \
void HEAPSORT_METHOD(type, sort_heap, compare)(array(type) list, int first, int last) { \
    while (last - first > 1) { \
        last = last - 1; \
        HEAPSORT_METHOD(type, pop_heap, compare)(list, first, last, last); \
    } \
}

#define HEAPSORT_HEAPSORT_RANGE(type, compare) \
void HEAPSORT_METHOD(type, heapsort_range, compare)(array(type) list, int i0, int i1) { \
    HEAPSORT_METHOD(type, heap_select, compare)(list, i0, i1 + 1, i1 + 1); \
    HEAPSORT_METHOD(type, sort_heap, compare)(list, i0, i1 + 1); \
}

#define HEAPSORT_HEAPSORT(type, compare) \
void HEAPSORT_METHOD(type, heapsort, compare)(array(type) list) { \
    HEAPSORT_METHOD(type, heapsort_range, compare)(list, 0, list->length); \
}

#define declare_array_heapsort_inline(type, compare) \
    static HEAPSORT_PUSH_HEAP(type, compare) \
    static HEAPSORT_ADJUST_HEAP(type, compare) \
    static HEAPSORT_POP_HEAP(type, compare) \
    static HEAPSORT_MAKE_HEAP(type, compare) \
    static HEAPSORT_HEAP_SELECT(type, compare) \
    static HEAPSORT_SORT_HEAP(type, compare) \
    static HEAPSORT_HEAPSORT_RANGE(type, compare) \
    static HEAPSORT_HEAPSORT(type, compare)

#define array_heapsort_range(type, compare) HEAPSORT_METHOD(type, heapsort_range, compare)
#define array_heapsort(type, compare) HEAPSORT_METHOD(type, heapsort, compare)

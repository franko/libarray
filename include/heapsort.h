/* This header file is meant to be included, possibly multiple times, each time
   by defining the macro variables: HEAPSORT_VALUE_TYPE, and HEAPSORT_LESS_THAN
   which represent, respectively, the value type of the array and the compare function.

   By including this header the following functions are provided:

   - array_heapsort(type), sort the whole array
   - array_heapsort_range(type), sort the array in a given range of indexes.

   Code adapted from:

   https://github.com/ladc/lgsl/blob/master/lgsl/sort.lua

   adapted, in turn, from GNU libstdc++'s source code. */

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, push_heap)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int first, int hole, int top, HEAPSORT_VALUE_TYPE value) {
    int parent = (hole - 1) / 2;
    while (hole > top && HEAPSORT_LESS_THAN(element(list, first + parent), value)) {
        element(list, first + hole) = element(list, first + parent);
        hole = parent;
        parent = (hole - 1) / 2;
    }
    element(list, first + hole) = value;
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, adjust_heap)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int first, int hole, int len, HEAPSORT_VALUE_TYPE value) {
    int top = hole;
    int second = hole;
    while (second < (len - 1) / 2) {
        second = 2 * (second + 1);
        if (HEAPSORT_LESS_THAN(element(list, first + second), element(list, first + (second - 1)))) {
            second = second - 1;
        }
        element(list, first + hole) = element(list, first + second);
        hole = second;
    }
    if ((len & 1) == 0 && second == (len - 2) / 2) {
        second = 2 * (second + 1);
        element(list, first + hole) = element(list, first + (second - 1));
        hole = second - 1;
    }
    ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, push_heap)(list, first, hole, top, value);
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, pop_heap)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int first, int last, int result) {
    HEAPSORT_VALUE_TYPE value = element(list, result);
    element(list, result) = element(list, first);
    ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, adjust_heap)(list, first, 0, last - first, value);
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, make_heap)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int first, int last) {
    if (last - first < 2) {
        return;
    }
    int len = last - first;
    int parent = (len - 2) / 2;
    while (1) {
        HEAPSORT_VALUE_TYPE value = element(list, first + parent);
        ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, adjust_heap)(list, first, parent, len, value);
        if (parent == 0) {
            return;
        }
        parent = parent - 1;
    }
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, heap_select)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int first, int middle, int last) {
    ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, make_heap)(list, first, middle);
    for (int i = middle; i < last; i++) {
        if HEAPSORT_LESS_THAN(element(list, i), element(list, first)) {
            ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, pop_heap)(list, first, middle, i);
        }
    }
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, sort_heap)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int first, int last) {
    while (last - first > 1) {
        last = last - 1;
        ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, pop_heap)(list, first, last, last);
    }
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, heapsort_range)(ARRAY_X(HEAPSORT_VALUE_TYPE) list, int i0, int i1) {
    ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, heap_select)(list, i0, i1 + 1, i1 + 1);
    ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, sort_heap)(list, i0, i1 + 1);
}

static void ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, heapsort)(ARRAY_X(HEAPSORT_VALUE_TYPE) list) {
    ARRAY_METHOD_X(HEAPSORT_VALUE_TYPE, heapsort_range)(list, 0, list->length);
}

#define array_heapsort_range(type) array_method(type, heapsort_range)
#define array_heapsort(type) array_method(type, heapsort)

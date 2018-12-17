#pragma once
#include "array.h"

declare_array_inline(float);

/* The code above should be type generic for the value_x and array_x.
   In addition the compare_x could be provided as a macro.
   In the implementation below value_x, array_x and compare_x are fixed
   for testing the code. */

typedef float value_x;
typedef struct array(float) *array_x;

#define compare_x(a, b) ((a) < (b))

static inline int div2(int x) {
    return x / 2;
}

static void push_heap(array_x list, int first, int hole, int top, value_x value) {
    int parent = div2(hole - 1);
    while (hole > top && compare_x(element(list, first + parent), value)) {
        element(list, first + hole) = element(list, first + parent);
        hole = parent;
        parent = div2(hole - 1);
    }
    element(list, first + hole) = value;
}

static void adjust_heap(array_x list, int first, int hole, int len, value_x value) {
    int top = hole;
    int second = hole;
    while (second < div2(len - 1)) {
        second = 2 * (second + 1);
        if (compare_x(element(list, first + second), element(list, first + (second - 1)))) {
            second = second - 1;
        }
        element(list, first + hole) = element(list, first + second);
        hole = second;
    }
    if ((len & 1) == 0 && second == div2(len - 2)) {
        second = 2 * (second + 1);
        element(list, first + hole) = element(list, first + (second - 1));
        hole = second - 1;
    }
    push_heap(list, first, hole, top, value);
}

void pop_heap(array_x list, int first, int last, int result) {
    value_x value = element(list, result);
    element(list, result) = element(list, first);
    adjust_heap(list, first, 0, last - first, value);
}

void make_heap(array_x list, int first, int last) {
    if (last - first < 2) {
        return;
    }
    int len = last - first;
    int parent = div2(len - 2);
    while (1) {
        value_x value = element(list, first + parent);
        adjust_heap(list, first, parent, len, value);
        if (parent == 0) {
            return;
        }
        parent = parent - 1;
    }
}

static void heap_select(array_x list, int first, int middle, int last) {
    make_heap(list, first, middle);
    for (int i = middle; i < last; i++) {
        if compare_x(element(list, i), element(list, first)) {
            pop_heap(list, first, middle, i);
        }
    }
}

static void sort_heap(array_x list, int first, int last) {
    while (last - first > 1) {
        last = last - 1;
        pop_heap(list, first, last, last);
    }
}

void heapsort(array_x list, int i0, int i1) {
    heap_select(list, i0, i1 + 1, i1 + 1);
    sort_heap(list, i0, i1 + 1);
}

#if 0
/* Taken from:

  https://github.com/ladc/lgsl/blob/master/lgsl/sort.lua

  It is a lua code adapted from GNU libstdc++ source. */

local function heapsort(list, i0, i1, f)
    f = f or less_than

    local function push_heap(first, hole, top, value)
        local parent = div2(hole - 1)
        while hole > top and f(list[first + parent], value) do
            list[first + hole] = list[first + parent]
            hole = parent
            parent = div2(hole - 1)
        end
        list[first + hole] = value
    end

    local function adjust_heap(first, hole, len, value)
        local top = hole
        local second = hole
        while second < div2(len - 1) do
            second = 2 * (second + 1)
            if f(list[first + second], list[first + (second - 1)]) then
                second = second - 1
            end
            list[first + hole] = list[first + second]
            hole = second
        end
        if band(len, 1) == 0 and second == div2(len - 2) then
            second = 2 * (second + 1)
            list[first + hole] = list[first + (second - 1)]
            hole = second - 1
        end
        push_heap(first, hole, top, value)
    end

    local function pop_heap(first, last, result)
        local value = list[result]
        list[result] = list[first]
        adjust_heap(first, 0, last - first, value)
    end

    local function make_heap(first, last)
        if last - first < 2 then return end
        local len = last - first
        local parent = div2(len - 2)
        while true do
            local value = list[first + parent]
            adjust_heap(first, parent, len, value)
            if parent == 0 then
                return
            end
            parent = parent - 1
        end
    end

    local function heap_select(first, middle, last)
        make_heap(first, middle)
        for i = middle, last - 1 do
            if f(list[i], list[first]) then
                pop_heap(first, middle, i)
            end
        end
    end

    local function sort_heap(first, last)
        while last - first > 1 do
            last = last - 1
            pop_heap(first, last, last)
        end
    end

    heap_select(i0, i1 + 1, i1 + 1)
    sort_heap(i0, i1 + 1)
end
#endif

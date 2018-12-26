#include <stdio.h>
#include <math.h>

#include "array.h"
#include "array/search.h"

static inline int my_test(float v) { return (v > 50.0); }

declare_array_inline(float);
declare_array_search_inline(float, my_test);

int main() {
    array(float) myarray = array_init();

    const int nmax = 3000;
    for (int i = 0; i < nmax; i++) {
        array_push(float)(myarray, sqrt((float) i));
    }

    int index = array_search(float, my_test)(myarray);

    if (index < 0) {
        printf("search failed");
        return 1;
    }

    for (int i = 0; i < index; i++) {
        if (my_test(element(myarray, i))) {
            printf("found unexpected match at index: %d value: %g\n", i, element(myarray, i));
            return 1;
        }
    }

    if (!my_test(element(myarray, index))) {
        printf("found elemet does not match at index: %d value: %g\n", index, element(myarray, index));
        return 1;
    }

    printf("found value %g at index: %d\n", element(myarray, index), index);
    array_free(float)(myarray);
    return 0;
}

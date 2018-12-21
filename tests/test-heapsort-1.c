#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "array.h"

declare_array_inline(float);

#define HEAPSORT_VALUE_TYPE float
#define HEAPSORT_LESS_THAN(a, b) ((a) < (b))
#include "heapsort.h"
#undef HEAPSORT_VALUE_TYPE
#undef HEAPSORT_LESS_THAN

int main() {
    array(float) list = array_init();
    for (int i = 0; i < 100; i++) {
        int rint = rand();
        array_push(float)(list, sqrt((float) rint));
    }

    array_heapsort(float)(list);

    float previous = -1.0;
    for (int i = 0; i < 100; i++) {
        const float current = element(list, i);
        if (current < previous) {
            printf("found inversion: array[%d] = %g, array[%d] = %g\n", i - 1, previous, i, current);
            return 1;
        }
        printf("%d: %g\n", i, current);
        previous = current;
    }
    return 0;
}

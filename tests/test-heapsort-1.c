#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "array/heapsort.h"

static inline int my_compare(float a, float b) { return a < b; }

declare_array_inline(float);
declare_array_heapsort_inline(float, my_compare);

int main() {
    array(float) list = array_init();
    for (int i = 0; i < 100; i++) {
        int rint = rand();
        array_push(float)(list, sqrt((float) rint));
    }

    array_heapsort(float, my_compare)(list);

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

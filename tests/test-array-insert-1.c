#include <stdio.h>
#include <math.h>

#include "array.h"

declare_array_inline(float);

int main() {
    array(float) radix = array_init();

    const int nmax = 256;
    for (int i = 0; i < nmax; i++) {
        array_push(float)(radix, sqrt((float) i));
    }    

    const int ninsert = 24;
    for (int i = 0; i < ninsert; i++) {
        const int insert_index = rand() % (nmax + i);
        array_insert(float)(radix, insert_index, -1.0);
    }

    const int expected_length = nmax + ninsert;
    if (radix->length != expected_length) {
        printf("unexpected array's length: %d instead of %d\n", radix->length, expected_length);
        return 1;
    }

    int spurious = 0;
    for (int i = 0; i < radix->length; i++) {
        const float expected_value = sqrt((float) (i - spurious));
        const float actual_value = element(radix, i);
        if (actual_value < 0.0) {
            spurious ++;
        } else if (actual_value != expected_value) {
            printf("unexpected value at index: %d expect %g got: %g\n", i, expected_value, actual_value);
            return 1;
        }
        printf("%d: %g\n", i, element(radix, i));
    }

    array_free(float)(radix);
    return 0;
}

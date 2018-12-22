#include <stdio.h>

#include "array.h"

declare_array_inline(int);

int main() {
    array(int) myarray = array_init();

    const int nmax = 100;
    for (int i = 0; i < nmax; i++) {
        array_push(int)(myarray, i * i);
    }    

    if (myarray->length != nmax) {
        printf("unexpected array's length: %d instead of %d\n", myarray->length, nmax);
        return 1;
    }

    for (int i = 0; i < myarray->length; i++) {
        if (element(myarray, i) != i * i) {
            printf("unexpected value at index %d, got %d instead of %d\n", i, element(myarray, 1), i * i);
            return 1;
        }
        printf("%i\n", element(myarray, i));
    }

    array_free(int)(myarray);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>

#include "array.h"

declare_array_inline(int);

int main() {
    array(int) myarray = array_init();

    const int nmax = 2048 * 8;
    for (int i = 0; i < nmax; i++) {
        array_push(int)(myarray, i * i);
    }    

    for (int i = 0; i < nmax; i++) {
        const int remove_index = rand() % (nmax - i);
        array_remove(int)(myarray, remove_index);
    }

    if (myarray->length != 0) {
        printf("unexpected array's length: %d instead of empty array\n", myarray->length);
        return 1;
    }

    array_free(int)(myarray);
    return 0;
}

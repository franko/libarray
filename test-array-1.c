#include <stdio.h>

#include "array.h"

declare_array_inline(int);

int main() {
    array(int) myarray = array_init();

    for (int i = 0; i < 100; i++) {
        array_push(int)(myarray, i * i);
    }    

    for (int i = 0; i < myarray->length; i++) {
        printf("%i\n", array_get(int)(myarray, i));
    }

    array_free(int)(myarray);
    return 0;
}

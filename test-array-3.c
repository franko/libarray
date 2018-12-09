#include <math.h>
#include <stdio.h>

#include "array.h"

typedef struct {
    int n, square;
    double root;
} foo;

declare_array_inline(foo);

int main() {
    array(foo) myarray = array_init();

    for (int i = 0; i < 100; i++) {
        array_push(foo)(myarray, (foo) {i, i * i, sqrt(i)});
    }    

    for (int i = 0; i < myarray->length; i++) {
        printf("%i %g\n", myarray->data[i].square, myarray->data[i].root);
    }

    array_free(foo)(myarray);
    return 0;
}

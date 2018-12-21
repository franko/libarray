#include <math.h>
#include <stdio.h>

#include "array.h"

typedef struct foo foo;

struct foo {
    int n, square;
    double root;
};

declare_array_inline(foo);

int main() {
    array(foo) myarray = array_init();

    for (int i = 0; i < 100; i++) {
        if (array_push(foo)(myarray, (foo) {i, i * i, sqrt(i)})) {
            fprintf(stderr, "Cannot allocate memory, exiting.\n");
            array_free(foo)(myarray);
            return 1;
        }
    }    

    for (int i = 0; i < myarray->length; i++) {
        foo e = array_get(foo)(myarray, i);
        printf("%d %g\n", e.square, e.root);
    }

    array_free(foo)(myarray);
    return 0;
}

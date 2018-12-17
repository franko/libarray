#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "heapsort.h"

int main() {
    array(float) list = array_init();
    for (int i = 0; i < 100; i++) {
        int rint = rand();
        array_push(float)(list, sqrt((float) rint));
    }
    heapsort(list, 0, 99);
    for (int i = 0; i < 100; i++) {
        printf("%d: %g\n", i, element(list, i));
    }
    return 0;
}

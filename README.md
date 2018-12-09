# Libarray

Very simple C library for generic dynamic arrays. It works in a similar way to C++ templates but using macros.
It works only for plain old data that do not need memory allocation or a destructor.

Please note that the library is just in early development and many functions are missing.

## Motivation

In C is a common pattern to use arrays that dinamically grows as needed when more elements are added.

The library avoid writing always the same code over and over again and it provides a type-safe implementation.

Here an example:

```c
#include <stdio.h>
#include "array.h"

/* Declare an array of int. Using the inline we don't need to provide an implementation
   in a separate file. */
declare_array_inline(int);

int main() {
    /* The type array(int) identifies the array of int. */
    array(int) myarray = array_init();

    /* All the method will use the sintax: array_<method_name>(int)(...). For example array_push(int) is
       used to append elements into the array. */

   for (int i = 0; i < 100; i++) {
        array_push(int)(myarray, i * i);
    }    

   /* Elements can be read by using either the 'element' macro or with the 'array_get(int)' function. */

    for (int i = 0; i < myarray->length; i++) {
        printf("%i\n", element(myarray, i));
    }

    array_free(int)(myarray);
    return 0;
}
```

## How to use

Just add 'array.h' and 'array.c' into your project, that's all.

Libarray is currently provided with a Meson build file and a few simple tests but these are not needed to use the library.

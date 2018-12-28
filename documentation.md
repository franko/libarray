# libarray documentation

Libarray is a very simple library based on C macros to implement generic array containers like std::vector in C++.

It works by using macro to create array types and function that specialize of the type of the elements that the array contains.

## Usage

First the `array.h` header should be included.

To actually use the array there are two approach. The first is to declare the array struct and functions and implement the functions separately. 

```c
declare_array(type);
```
Declare an array of `type` and the related functions.

```c
implement_array(type);
```
Implement tha functions related to the `array(type)`.

The second approach is to declare everything inline using the macro:

```c
declare_array_inline(type);
```
Declare inline an array of `type` and all the related functions.

***


### Array type
```c
array(type)
```

the type of an array containing values of the given type. Equivalent to:

```c
typedef struct {
    type *data;
    int length;
    int size;
} array(type)[1];
```

It is declared as an array of unit size so that it can be used like a pointer. If the array struct must be allocated on the heap the type `array_ptr(type)` can be used instead of `array(type)`.

The `type` should be a C type designed by a single identifier and should be assignable. Currently `type` cannot be an explicit struct type like `struct foo` but a typedef can be used like `typedef struct foo foo` and use the `foo` type.

#### Typical usage

Declare an array of `float` with automatic allocation:

```c
/* Declare and initialize an array of float values. */
array(float) a = array_init();

/* Use the array to append a value. */
array_push(float)(a, 2.5);

/* Free the memory used by the array when it goes out of scope. */
array_free(float)(a);
```

***

### Pointer array type
```c
array_ptr(type)
```

Like `array(type)` but as a pointer. Equivalent to:

```c
typedef struct {
    type *data;
    int length;
    int size;
} *array_ptr(type);
```

#### Typical usage

Declare an array of `float` with dynamic allocation:

```c
/* Declare and initialize an array of float values. */
array_ptr(float) a = array_new(float)();

/* Use the array to append a value. */
array_push(float)(a, 2.5);

/* Free the memory used by the array when it goes out of scope. */
array_delete(float)(a);
```

It should be noted that arrays created with `array_new` should be freed with the `array_delete` function.

***

## Array methods

The array methods are named like `array_<method>(type)` where `type` corresponds to the type of its values. The array methods always get the array as a first argument.


***
### Get an element
```c
array_get(type)(array(type) a, int index)
```

Returns the array's element at the given `index`. The index should be in a valid range between `0` and `length - 1`.

The macro `element(a, i)` can be used instead. The macro `element` refer directly to the element in the array data field and can be used as a LHS for assignments.

### Example of direct assignment

```c
array(float) a = array_init();

/* Insert some elements into the array */

/* Directly assign a value to the first element. */
element(a, 0) = 1.0;

/* Obtain a pointer by taking the adress of `element()` */
float *ptr = &element(a, 0);
```

***
### Set an element
```c
array_set(type)(array(type) a, int index, type value)
```

Sets the array's value in position `index` to the given `value`. The index should be in a valid range between `0` and `length - 1`.

The macro `element()` can be used instead.

***
### Push an element
```c
array_push(type)(array(type) a, type value)
```

Append the given `value` at the end of the array.

***
### Insert an element

```c
array_insert(type)(array(type) a, int index, type value)
```

Insert the given `value` in the position given by `index`. The `index` should be between `0` and `length`. If the index is equal to `length` the element is added at the end of the array.

***
### Remove an element
```c
array_remove(type)(array(type) a, int index)
```

Remove the value at the given `index`.

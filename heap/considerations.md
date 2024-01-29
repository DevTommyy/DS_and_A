I think there would be 2 approaches:

- The first being with an array:

```c
    #define SIZE 1024
    struct Heap {
      int elements[SIZE];
      size_t current;
    } typedef Heap;
```

- the second being a pointer to an array like with
  strings `char*`:

```c
    struct Heap {
      int* elements;
      size_t current;
      size_t capacity;
    } typedef Heap
```

## About Heap Implementation Approaches

There are two primary approaches for implementing a heap data structure:

- Array Approach
- Pointer to Array Approach

### Array Approach:

`PROS`:

- Provides contiguous memory allocation, beneficial for cache locality and linear traversal.
- Accessing elements is straightforward using array indexing.

`CONS`:

- Fixed Size: Imposes a limitation on the maximum number of elements the heap can hold. Reallocation is necessary if the limit is exceeded, which can be expensive.
- Memory Wastage: Allocated size may be larger than required, leading to memory wastage.

### Pointer to Array Approach:

`PROS`:

- Dynamically resize the array as needed, avoiding the fixed-size limitation.
- Memory is allocated dynamically, using only as much memory as needed.

`CONS`:

- Accessing elements requires dereferencing the pointer, adding a level of indirection.
- Memory allocation and deallocation may lead to fragmentation over time, potentially impacting performance.

### Considerations for choosing between the two:

- For a relatively small and fixed heap size, the array approach might be simpler and more efficient due to its contiguous memory and straightforward indexing.
- For a heap size expected to vary or potentially grow large, the pointer to array approach would offer more flexibility and efficient memory usage.

# In This Case

I will be using the array approach cause the pointer approach
would cause too much overhead

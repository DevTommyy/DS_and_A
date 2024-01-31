#ifndef MINHEAP_H
#define MINHEAP_H

#include <stddef.h> // Include for size_t


#define SIZE 1024

/// An `Heap` data structure
///
/// # Fields
///
/// - `elements` an int array of `SIZE` length that contains the elements
/// of the heap. NOTE: uninitialized values are represented as `0`
/// - `current` a `size_t` representing the index of the next free space
/// in the heap
struct Heap {
    int elements[SIZE];
    size_t current;
} typedef Heap;

void min_heapify(Heap* heap);

void heap_add(Heap* heap, int val);
bool heap_delete(Heap* heap, int val);

int heap_index_of(Heap* heap, int val);
bool heap_contains(Heap* heap, int val);
void heap_swap(Heap* heap, int first_idx, int second_idx);

void heap_print(Heap* heap);
#endif /* MINHEAP_H */

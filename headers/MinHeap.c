#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 1024

/*
 * To get the indexes the formula is:
 * - parent index = (index − 1)/2
 * - left child = 2 ∗ index + 1
 * - right child = 2 ∗ index + 2 
 */

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

/// "Normalizes" an `Heap` into it's specified type of heap
/// checking if each elemet respects its properties
void min_heapify(Heap* heap) {
    int idx = heap->current - 1;
    // (idx -1) / 2] is the parent idx
    while (idx > 0 && heap->elements[idx] < heap->elements[(idx - 1) / 2]) {
        heap_swap(heap, idx, (idx -1) / 2);
        idx = (idx -1) / 2;
    }
}

/// Inserts a new element inside the heap
///
/// # Warnings
/// 
/// This function can potentially fail in the case
/// a value is inserted when the heap is full
void heap_add(Heap* heap, int val) {
    if (heap->current + 1 == SIZE) {
        printf( 
            "Couldn' add anymore elemets, the length \
             of the heap exceeds the maximum size %d",
            SIZE
         );
         return;
    } else {
        heap->elements[heap->current] = val;
        heap->current++;
        min_heapify(heap);
    }
}

/* 
 * So the algorithm works like this, we check for the index of the val
 * if the index isn't found return early, else save the index of the left
 * and right child. Then swap the value of the element to remove with the last
 * element on the heap, null the previously last element and check if any of the
 * new children break the heap rule, IF THEY DO then swap the parent with the
 * smallest of them
 */
/// Deletes an element from the heap and re normalizes it 
/// if any element break its properties
///
/// # Params
/// 
/// - `heap` the `Heap*` we are referring to
/// - `val` an `int` representing the value we are deleting
///
/// # Returns
///
/// A `bool` flag stating if the value was found or not
bool heap_delete(Heap* heap, int val) { 
    int idx = heap_index_of(heap, val);
    if (idx < 0) {
        return false;
    }
    // remove it
    heap->current--;
    heap->elements[idx] = heap->elements[heap->current];

    // reset or free it
    heap->elements[heap->current] = 0;

    // save its children indexes
    size_t left = (2 * idx) + 1;
    size_t right = (2 * idx) + 2;
    
    while  (left < heap->current && right < heap->current &&
        ((heap->elements[idx] > heap->elements[left]) ||
        (heap->elements[idx] > heap->elements[right]))
    ){
        if (heap->elements[left] < heap->elements[right]) { // the left one is the smallest
            heap_swap(heap, left, idx);
            idx = left;
            left = (2 * idx) + 1;
            right = (2 * idx) + 2;
        } else { // the right one is the smallest
            heap_swap(heap, right, idx);
            idx = right;
            left = (2 * idx) + 1;
            right = (2 * idx) + 2;
        }
    }
    return true;
}

/// Returns an index of a given value in the heap
/// 
/// # Params
/// 
/// - `heap` the `Heap*` we are referring to
/// - `val` an `int` representing the value of which we are trying to 
/// find the index 
/// 
/// # Returns
/// 
/// An `int` representing the index of the value if it was found, if  
/// the value is not found the fucnction returns `-1`
int heap_index_of(Heap* heap, int val) {
    for (size_t i = 0; i < heap->current; i++) {
        if (heap->elements[i] == val) {
            return i;
        }
    }
    return -1;
    
}

/*
 * The following algorithm is specifically designed for a min-heap.
 * To tailor the algorithm for a max-heap the two comparison operations in 
 * the else if condition within the inner while loop should be flipped. 
 */
/// Checks for a value in the heap
/// 
/// # Params
/// 
/// - `heap` the `Heap*` we are referring to
/// - `val` an `int` representing the value we are checking for
/// 
/// # Returns
/// 
/// A `bool` flag stating if the value was found or not
bool heap_contains(Heap* heap, int val) {
    // initialize the various indexes and the number of nodes
    size_t start_node = 0;
    size_t end_node = 0;
    int nodes = 1;
    int count = 0;

    // all of this part is just index arithmetic
    // it might look difficult but it's not too hard
    // to understand
    while (start_node < heap->current) {
        start_node = nodes - 1;
        end_node = start_node + nodes;
        count = 0;
        while (start_node < heap->current && start_node < end_node) {
            // basically if the element at the current index
            // is not the one searched and for each node in this
            // level is bigger than the parent and less than the child
            // the element can't be in the heap
            if (val == heap->elements[start_node]) {
                return true;
            } else if (val > heap->elements[(start_node - 1) / 2] 
                    && val < heap->elements[start_node]) {
                count++;
            }
            start_node++;
        }
        if (count == nodes) {
            return false;
        }
        nodes *= 2;
    }
    return false;
}

/// Swaps a child and its parent on the heap given their indexes
///
/// # Params
/// 
/// - `heap` the `Heap*` we are referring to
/// - `child_idx` the index of the child to swap
/// - `parent_idx` the index of the parent to swap
void heap_swap(Heap* heap, int child_idx, int parent_idx) {
    int tmp = heap->elements[child_idx];
    heap->elements[child_idx] = heap->elements[parent_idx];
    heap->elements[parent_idx] = tmp;
}

/// Prints the whole heap in an array like manner
void heap_print(Heap* heap) {
    printf("[ ");
    for (size_t i = 0; i < heap->current; i++) { 
        // i'm printing while it is not 0 but uninitialized values could 
        // be random numbers too
        printf("%d ", heap->elements[i]);
    }
    printf("]\n");
}
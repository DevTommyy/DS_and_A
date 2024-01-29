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

void add(Heap* heap, int val);
void min_heapify(Heap* heap);
void swap(Heap* heap, int first_idx, int second_idx);
void print(Heap* heap);
int index_of(Heap* heap, int val);
bool delete(Heap* heap, int val);
bool contains(Heap* heap, int val);

void add(Heap* heap, int val) {
    if (heap->current + 1 == SIZE) {
        printf( 
            "Couldn't add anymore elemets, the length \
             of the heap exceeds the maximum size %d",
            SIZE
         );
         return;
    } else {
        heap->elements[heap->current] = val; // [x] could change this to `heap.current - 1`
        heap->current++;
        min_heapify(heap);
    }
}

void min_heapify(Heap* heap) {
    int idx = heap->current - 1;
    // (idx -1) / 2] is the parent idx
    while (idx > 0 && heap->elements[idx] < heap->elements[(idx -1) / 2]) { // to max_heapify() just swap the `<` for a `>`
        swap(heap, idx, (idx -1) / 2);
        idx = (idx -1) / 2;
    }
}

void swap(Heap* heap, int child_idx, int parent_idx) {
    int tmp = heap->elements[child_idx];
    heap->elements[child_idx] = heap->elements[parent_idx];
    heap->elements[parent_idx] = tmp;
}

void print(Heap* heap) {
    printf("[ ");
    for (size_t i = 0; i < sizeof(heap->elements) && heap->elements[i] != 0; i++) { 
        // i'm printing while it is not 0 but uninitialized values could 
        // be random numbers too
        printf("%d ", heap->elements[i]);
    }
    printf("]\n");
}

int index_of(Heap* heap, int val) {
    for (size_t i = 0; i < sizeof(heap->elements); i++) {
        if (heap->elements[i] == val) {
            return i;
        }
    }
    return -1;
    
}

/* 
 * So the algorithm works like this, we check for the index of the val
 * if the index isn't found return early, else save the index of the left
 * and right child. Then swap the value of the element to remove with the last
 * element on the heap, null the previously last element and check if any of the
 * new children break the heap rule, IF THEY DO then swap the parent with the
 * smallest of them
 */

bool delete(Heap* heap, int val) { 
    int idx = index_of(heap, val);
    if (idx < 0) {
        return false;
    }
    // remove it
    heap->current--;
    heap->elements[idx] = heap->elements[heap->current];

    // reset or free it
    heap->elements[heap->current] = 0;

    // save its children indexes
    int left = (2 * idx) + 1;
    int right = (2 * idx) + 2;
    
    while (left < heap->current && 
        (heap->elements[idx] > heap->elements[left]) ||
        (heap->elements[idx] > heap->elements[right])
    ) {
        if (heap->elements[left] < heap->elements[right]) {// the left one is the smallest
            swap(heap, left, idx);
            idx = left;
        } else { // the right one is the smallest
            swap(heap, right, idx);
            idx = right;
        }
    }
    return true;
}

bool contains(Heap* heap, int val) {
    // TODO implement an optimised version of contains
    return;
}

int main(int argc, char const *argv[]){
    Heap* heap = malloc(sizeof(Heap));
    add(heap, 3);
    add(heap, 9);
    add(heap, 12);
    add(heap, 7);
    add(heap, 1); 

    print(heap); 

    delete(heap, 1);
    
    print(heap);
}

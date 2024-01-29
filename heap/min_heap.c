#include<stdio.h>
#include<stdlib.h>

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
    while (idx > 0 && heap->elements[idx] < heap->elements[(idx -1) / 2]) {
        swap(heap, idx, (idx -1) / 2);
        idx = (idx -1) / 2;
    }
}

void swap(Heap* heap, int child_idx, int parent_idx) {
    // TODO implement
    return;
}

int main(int argc, char const *argv[]){
    return 0;
}

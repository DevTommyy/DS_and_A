#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 1024

struct PriorityQueue {
    int elements[SIZE];
    size_t current;
    // the head and the tail of this priority queue
    // are index `0` and index `current`
} typedef PriorityQueue;

void max_heapify(PriorityQueue* queue);
void swap(PriorityQueue* queue, int child_idx, int parent_idx);

void enqueue(PriorityQueue* queue);
int dequeue(PriorityQueue* queue);

int peek(PriorityQueue* queue);

void print(PriorityQueue* queue);

// Reorder the `PriorityQueue` in a increasing manner.
/// This takes `O(log n)` time
void max_heapify(PriorityQueue* queue) {
    int idx = queue->current - 1;
    // (idx -1) / 2] is the parent idx
    while (idx > 0 && queue->elements[idx] > queue->elements[(idx - 1) / 2]) {
        swap(queue, idx, (idx -1) / 2);
        idx = (idx -1) / 2;
    }
}

/// Swaps a child and its parent on the priority queue given their indexes.
/// This takes `O(1)` time
///
/// # Params
/// 
/// - `heap` the `PriorityQueue*` we are referring to
/// - `child_idx` the index of the child to swap
/// - `parent_idx` the index of the parent to swap
void swap(PriorityQueue* queue, int child_idx, int parent_idx) {
    int tmp = queue->elements[child_idx];
    queue->elements[child_idx] = queue->elements[parent_idx];
    queue->elements[parent_idx] = tmp;
}

void enqueue(PriorityQueue* queue) {
    // TODO
}

int dequeue(PriorityQueue* queue) {
    // TODO
}

int peek(PriorityQueue* queue) {
    // TODO
}

void print(PriorityQueue* queue) {
    printf("[ ");
    for (size_t i = 0; i < queue->current; i++) { 
        printf("%d ", queue->elements[i]);
    }
    printf("]\n");
}

int main(int argc, char const *argv[]) {
    return 0;
}

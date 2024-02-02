#ifndef DEQUE_H
#define DEQUE_H

/// The element in the deque
/// 
/// # Fields
///
/// - `val` an `int` representing the val contained
/// - `next` a pointer to the next element
/// - `prev` a pointer to the previous element
struct QueNode {
    int val;
    struct QueNode* next;
    struct QueNode* prev;
} typedef QueNode;

/// A `Deque` data structure
///
/// # Fields
///
/// - `head` a pointer to the first element
/// - `tail` a pointer to the last element
struct Deque {
    QueNode* head;
    QueNode* tail;
} typedef Deque;

void enqueue_back(Deque* queue, int val);
void enqueue_front(Deque* queue, int val);

int dequeue_front(Deque* queue); 
int dequeue_back(Deque* queue); 

bool deque_contains(Deque* queue, int val);

void deque_print(Deque* queue);
void deque_freeAll(Deque* queue);

#endif /* DEQUE_H */

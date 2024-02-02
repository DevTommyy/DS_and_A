#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct QueNode {
    int val;
    struct QueNode* next;
    struct QueNode* prev;
} typedef QueNode;

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

/// Pushes `val` to the back of the queue.
/// This is an `O(1)` operation
void enqueue_back(Deque* queue, int val) {
    QueNode* node = malloc(sizeof(QueNode));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        node->prev = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }
}

/// Pushes `val` to the front of the queue.
/// This is an `O(1)` operation
void enqueue_front(Deque* queue, int val) {
    QueNode* node = malloc(sizeof(QueNode));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        node->next = queue->head;
        queue->head->prev = node;
        queue->head = node;
    }
}

/// Remove the first element of the queue and return it's value.
/// This is an `O(1)` operation
/// 
/// # Returns 
///
/// `0` if the queue is already empty
/// `val` which is an int representing the value of the node popped
int dequeue_front(Deque* queue) {
    if (queue->head == NULL) {
        return 0;
    } else  {
        // cases are:
        // - removing the only node
        // - removing the first node
        int val = queue->head->val;

        if (queue->head == queue->tail) {
            // only node present
            queue->head = NULL;
            queue->tail = NULL;
        } else {
            // other nodes present, moving the head to the next node
            queue->head = queue->head->next;
            free(queue->head->prev);
            queue->head->prev = NULL;
        }
        return val;
    }
}

/// Remove the last element of the queue and return it's value.
/// This is an `O(1)` operation
/// 
/// # Returns 
///
/// `0` if the queue is already empty
/// `val` which is an int representing the value of the node popped
int dequeue_back(Deque* queue) {
    if (queue->head == NULL) {
        return 0;
    } else {
        // cases are:
        // - removing the only node
        // - removing the last node
        int val = queue->tail->val;

        if (queue->head == queue->tail) {
            // only node present
            queue->head = NULL;
            queue->tail = NULL;
        } else {
            // other nodes present, moving the tail to the previous node
            queue->tail = queue->tail->prev;
            free(queue->tail->next);
            queue->tail->next = NULL;
        }
        return val;
    }
}

/// Checks if the queue deque_contains a certain value
/// This is an `O(n)` operation
///
/// # Params
/// 
/// `queue` a `Deque` pointer of the queue to check
/// `val` an `int` representing the value to check
/// 
/// # Returns
/// `1` if the value is found
/// `0` if the queue is empty or the value is not found
bool deque_contains(Deque* queue, int val) {
    if (queue->head == NULL) {
        return false;
    }
    QueNode* cursor = queue->head;
    while (cursor != NULL) {
        if (cursor->val == val) {
            return true;
        } else {
            cursor = cursor->next;
        }
    }
    return false;
}

/// Prints the deque in `O(n)` time
void deque_print(Deque* queue) {
    // this way i create a pointer that is pointing to the same value as head
    QueNode* cursor = queue->head; 
    int idx = 0;
    while (cursor != NULL) {
        printf("queue[%d] = %d\n", idx, cursor->val);
        cursor = cursor->next;
        idx++;
    }
}

/// frees all the memory allocated by the queue
void deque_freeAll(Deque* queue) {
    QueNode* current = queue->head;
    while (current != NULL) {
        QueNode* next = current->next;
        free(current);
        current = next;
    }
}
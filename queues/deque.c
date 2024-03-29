#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
    struct Node* prev;
} typedef Node;

struct Deque {
    Node* head;
    Node* tail;
} typedef Deque;

typedef enum {true = 1, false = 0} bool;

void enqueue_back(Deque* queue, int val);
void enqueue_front(Deque* queue, int val);

int dequeue_front(Deque* queue); 
int dequeue_back(Deque* queue); 

int peek_front(Deque* queue);
int peek_back(Deque* queue);

bool contains(Deque* queue, int val);

void print(Deque* queue);
void freeAll(Deque* queue);

// this is infallible, if not for the malloc
// only if the sysem fails to allocate the memory
// this function fails
/// pushes `val` to the back of the queue
void enqueue_back(Deque* queue, int val) {
    Node* node = malloc(sizeof(Node));
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

/// pushes `val` to the front of the queue
void enqueue_front(Deque* queue, int val) {
    Node* node = malloc(sizeof(Node));
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

/// Peeks the first element of the queue and return it's value.
/// This is an `O(1)` operation
/// 
/// # Returns 
///
/// `0` if the queue is already empty
/// `val` which is an int representing the value of the node popped
int peek_front(Deque* queue) {
    if (queue->head == NULL) {
        return 0;
    } else  {
        return queue->head->val;
    }
}

/// Peeks the last element of the queue and return it's value.
/// This is an `O(1)` operation
/// 
/// # Returns 
///
/// `0` if the queue is already empty
/// `val` which is an int representing the value of the node popped
int peek_back(Deque* queue) {
    if (queue->head == NULL) {
        return 0;
    } else { 
        return queue->tail->val;
    }
}


/// checks if the queue contains a certain value
///
/// # Params
/// 
/// `queue` a `Deque` pointer of the queue to check
/// `val` an `int` representing the value to check
/// 
/// # Returns
/// `1` if the value is found
/// `0` if the queue is empty or the value is not found
bool contains(Deque* queue, int val) {
    if (queue->head == NULL) {
        return false;
    }
    Node* cursor = queue->head;
    while (cursor != NULL) {
        if (cursor->val == val) {
            return true;
        } else {
            cursor = cursor->next;
        }
    }
    return false;
}

/// pretty prints the queue
void print(Deque* queue) {
    // this way i create a pointer that is pointing to the same value as head
    Node* cursor = queue->head; 
    int idx = 0;
    while (cursor != NULL) {
        printf("queue[%d] = %d\n", idx, cursor->val);
        cursor = cursor->next;
        idx++;
    }
}

/// frees all the memory allocated by the queue
void freeAll(Deque* queue) {
    Node* current = queue->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

// some random testing generated by chatGPT
int main() {
    Deque *queue = (Deque *)malloc(sizeof(Deque)); // Allocate memory for the Deque struct
    queue->head = NULL;
    queue->tail = NULL;

    // Testing enqueue_back
    printf("Enqueuing elements to the back...\n");
    enqueue_back(queue, 10);
    enqueue_back(queue, 20);
    enqueue_back(queue, 30);
    print(queue); // Printing the queue

    // Testing enqueue_front
    printf("\nEnqueuing elements to the front...\n");
    enqueue_front(queue, 5);
    enqueue_front(queue, 2);
    print(queue); // Printing the queue

    // Testing dequeue_front
    printf("\nDequeuing from the front...\n");
    int dequeued = dequeue_front(queue);
    if (dequeued != 0) {
        printf("Dequeued value from the front: %d\n", dequeued);
    }
    print(queue); // Printing the queue

    // Testing dequeue_back
    printf("\nDequeuing from the back...\n");
    dequeued = dequeue_back(queue);
    if (dequeued != 0) {
        printf("Dequeued value from the back: %d\n", dequeued);
    }
    print(queue); // Printing the queue

    // Testing contains
    printf("\nChecking if the queue contains 30...\n");
    if (contains(queue, 30)) {
        printf("Value 30 is found in the queue.\n");
    } else {
        printf("Value 30 is not found in the queue.\n");
    }

    // Freeing allocated memory
    freeAll(queue);
    free(queue); // Free the memory allocated for the Deque struct

    return 0;
}
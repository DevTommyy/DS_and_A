#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Define the Node structure
struct ListNode {
    int val;
    struct ListNode* next;
    struct ListNode* prev;
} typedef Node;

// Define the LinkedList structure
struct LinkedList {
    Node* head;
    Node* tail;
}typedef LinkedList;

// Define boolean type

// Function prototypes
int list_len(LinkedList* list);
bool list_is_empty(LinkedList* list);

void list_push_back(LinkedList* list, int val);
void list_push_front(LinkedList* list, int val);

int list_pop_front(LinkedList* list);
int list_pop_back(LinkedList* list);

bool list_delete(LinkedList* list, int val);

bool list_contains(LinkedList* list, int val);
LinkedList* list_rev(LinkedList list);

void list_pprint(LinkedList* list);
void list_freeAll(LinkedList* list);

#endif /* LINKEDLIST_H */

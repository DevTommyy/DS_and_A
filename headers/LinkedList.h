#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/// The element in the list
/// 
/// # Fields
///
/// - `val` an `int` representing the val contained
/// - `next` a pointer to the next element
/// - `prev` a pointer to the previous element
struct ListNode {
    int val;
    struct ListNode* next;
    struct ListNode* prev;
} typedef ListNode;

/// A `Linked List` data structure
///
/// # Fields
///
/// - `head` a pointer to the first node
/// - `tail` a pointer to the last node
struct LinkedList {
    ListNode* head;
    ListNode* tail;
}typedef LinkedList;

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

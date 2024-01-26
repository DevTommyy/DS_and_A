#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode* next;
    struct ListNode* prev;
} typedef ListNode;

struct LinkedList {
    ListNode* head;
    ListNode* tail;
} typedef LinkedList;

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

/// returns the length of a list
int list_len(LinkedList* list) {
    if (list->head == NULL) {
            return 0;
    }
    int len = 0;
    ListNode* cursor = list->head;
    while (cursor != NULL) {
        len++;
    }
    return len;
}

/// returns `true` if a list is empty otherwise `false`
bool list_is_empty(LinkedList* list) {
    if (list->head == NULL) {
                return true;
    } else {
        return false;
    }
}

// this is infallible, if not for the malloc
// only if the sysem fails to allocate the memory
// this function fails
/// pushes `val` to the end of the list
void list_push_back(LinkedList* list, int val) {
    ListNode* node = malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}

/// pushes `val` to the start of the list
void list_push_front(LinkedList* list, int val) {
    ListNode* node = malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

/// remove the first element of the list and return it's value
/// 
/// # Returns 
/// `-1` if the list is already empty
/// `val` which is an int representing the value of the node popped
int list_pop_front(LinkedList* list) {
    if (list_is_empty(list)) {
        return -1;
    } else  {
        // cases are:
        // - removing the only node
        // - removing the first node
        int val = list->head->val;

        if (list_len(list) == 1) {
            // only node present
            list->head = NULL;
            list->tail = NULL;
        } else {
            // other nodes present, moving the head to the next node
            list->head = list->head->next;
            free(list->head->prev);
            list->head->prev = NULL;
        }
        return val;
    }
}

/// remove the last element of the list and return it's value
/// 
/// # Returns 
/// `-1` if the list is already empty
/// `val` which is an int representing the value of the node popped
int list_pop_back(LinkedList* list) {
    if (list_is_empty(list)) {
        return -1;
    } else {
        // cases are:
        // - removing the only node
        // - removing the last node
        int val = list->tail->val;

        if (list_len(list) == 1) {
            // only node present
            list->head = NULL;
            list->tail = NULL;
        } else {
            // other nodes present, moving the tail to the previous node
            list->tail = list->tail->prev;
            free(list->tail->next);
            list->tail->next = NULL;
        }
        return val;
    }
}

/// checks if the list contains a certain value
///
/// # Params
/// 
/// `list` a `LinkedList` pointer of the list to check
/// `val` an `int` representing the value to check
/// 
/// # Returns
/// `1` if the value is found
/// `0` if the list is empty or the value is not found
bool list_contains(LinkedList* list, int val) {
    if (list->head == NULL) {
        return false;
    }
    ListNode* cursor = list->head;
    while (cursor != NULL) {
        if (cursor->val == val) {
            return true;
        } else {
            cursor = cursor->next;
        }
    }
    return false;
}

/// # Cases
/// - the list is empty
/// - the node is the only one in the list
/// - the node is the head
/// - the node is the tail
/// - the node is in between
/// - the node isn't there

/// deletes the node with the value provided
/// 
/// # Params
/// 
/// `list` a `LinkedList` pointer of the list to check
/// `val` an `int` representing the value to delete
bool list_delete(LinkedList* list, int val) {
    if (list->head == NULL) {
        // list is empty
        return false;
    } else {
        if (list->head->val == val) { // the value is found immediately, so it's the head
            if (list->head == list->tail) {
                // the head and the tail are the same
                list->head = NULL;
                list->tail = NULL;
            } else {
                // deleting the head
                list->head = list->head->next;
                list->head->prev = NULL;
            }
            return true;
        }
        ListNode* cursor = list->head;
        // searching for the node to delete
        while(cursor != NULL && cursor->val != val) {
            cursor = cursor->next;
        } 
        // if was found
        if (cursor != NULL) {
            // we are removing the tail
            if (cursor == list->tail) {
                list->tail = list->tail->prev;
                list->tail->next = NULL;
            } else {
                // we are removing in between
                cursor->prev->next = cursor->next;
                cursor->next->prev = cursor->prev;
                /*  
                 * idk why there is no dereferncing
                 * maybe cause cursor is a pointer  to a pointer
                 * but cursor->prev is the actual pointer so by modifying
                 * it i'm modifying the actual list
                */
            }
            free(cursor); 
            return true;
        } else {
            // it wasn't found
            return false;
        }
    }
}

/// Consumes a `LinkedList` and reverses it
LinkedList* list_rev(LinkedList list) {
    LinkedList* reversed = malloc(sizeof(LinkedList));
    reversed->head = NULL;
    reversed->tail = NULL;
    while (list.head != NULL) {
        push_front(reversed, list.head->val);
        list.head = list.head->next;
    }
    freeAll(&list);
    return reversed;
}

/// pretty prints the list
void list_pprint(LinkedList* list) {
    // this way i create a pointer that is pointing to the same value as head
    ListNode* cursor = list->head; 
    int idx = 0;
    while (cursor != NULL) {
        printf("list[%d] = %d\n", idx, cursor->val);
        cursor = cursor->next;
        idx++;
    }
}

/// frees all the memory allocated by the list
void list_freeAll(LinkedList* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
}
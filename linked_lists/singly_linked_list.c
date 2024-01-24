#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
} typedef Node;

struct LinkedList {
    Node* head;
    Node* tail;
} typedef LinkedList;

typedef enum {true = 1, false = 0} bool;

/// this is infallible, if not for the malloc
/// only if the sysem fails to allocate the memory
/// this function fails
void push(LinkedList* list, int val) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
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
bool contains(LinkedList* list, int val) {
    if (list->head == NULL) {
        return false;
    }
    Node* cursor = list->head;
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
/// 
/// 
/// 
/// 
/// 
/// 
bool delete(LinkedList* list, int val) {
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
            }
            return true;
        }
        Node* cursor = list->head;
        // searching for the node before the one to delete
        while(cursor->next != NULL && cursor->next->val != val) {
            cursor = cursor->next;
        } 
        // if was found
        if (cursor->next != NULL) {
            // we are removing the tail
            if (cursor->next == list->tail) {
                list->tail = cursor;
            } else {
                // we are removing in between
                *cursor->next = *cursor->next->next;
                // dereferencing cause cursor is a pointer to a pointer
            }
            return true;
        } else {
            // it wasn't found
            return false;
        }
    }
}

/// pretty prints the list
void pprintList(LinkedList* list) {
    // this way i create a pointer that is pointing to the same value as head
    Node* cursor = list->head; 
    int idx = 0;
    while (cursor != NULL) {
        printf("list[%d] = %d\n", idx, cursor->val);
        cursor = cursor->next;
        idx++;
    }
}

/// frees all the memory allocated by the list
void freeAll(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

// some random testing generated by chatGPT
int main(int argc, char const *argv[]) {

    LinkedList* list = malloc(sizeof(LinkedList)); 
    list->head = NULL;
    list->tail = NULL;
    
   // Push some elements into the list
    push(list, 10);
    push(list, 20);
    push(list, 30);
    push(list, 40);

    // Print the initial list
    printf("Initial List:\n");
    pprintList(list);

    // Test the contains function
    int searchValue = 20;
    if (contains(list, searchValue)) {
        printf("List contains %d.\n", searchValue);
    } else {
        printf("List does not contain %d.\n", searchValue);
    }

    // Test the delete function
    int deleteValue = 30;
    if (delete(list, deleteValue)) {
        printf("Deleted %d from the list.\n", deleteValue);
    } else {
        printf("%d not found in the list.\n", deleteValue);
    }

    // Print the modified list
    printf("Modified List:\n");
    pprintList(list);

    // Free all the allocated memory
    freeAll(list);

    return 0;
}

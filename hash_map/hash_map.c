/*
 * Things to remember when implementing it:
 * - use an array of pointer to linked lists as base
 * - resize when a certain threshold is exceeded (75%)
 * - when resizing instanciate an array twice the size of the previous
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../headers/LinkedList.h"

#define INITIAL_SIZE 1024

// for the sake of simpliciry this HashMap is <int, int>
// (since my implementation of linked list is with int as a value)

struct Node {
    int key;
    LinkedList bucket; // this represents the value
} typedef Node;

struct HashMap {
    Node* elements;
} typedef HashMap;

int main() {
    // Allocate memory for the HashMap
    HashMap* map = malloc(sizeof(HashMap));
    map->elements = malloc(sizeof(Node) * INITIAL_SIZE);

    // Initialize elements of the HashMap
    for (int i = 0; i < INITIAL_SIZE; ++i) {
        map->elements[i].key = i; // Assigning keys for demonstration
        // Initialize the buckets
        map->elements[i].bucket.head = NULL;
        map->elements[i].bucket.tail = NULL;

        // Add some values to the buckets (for demonstration)
        list_push_back(&(map->elements[i].bucket), i * 10);
        list_push_back(&(map->elements[i].bucket), i * 20);
    }

    // Print the HashMap
    for (int i = 0; i < INITIAL_SIZE; ++i) {
        printf("Key: %d\n", map->elements[i].key);
        printf("Values in the bucket:\n");
        list_pprint(&(map->elements[i].bucket));
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < INITIAL_SIZE; ++i) {
        list_freeAll(&(map->elements[i].bucket));
    }
    free(map->elements);
    free(map);

    return 0;
}
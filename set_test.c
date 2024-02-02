#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define SIZE 1024
#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

uint32_t fnv1a_hash(const void *data, size_t size) {
    const unsigned char *bytes = (const unsigned char *)data;
    uint32_t hash = FNV_OFFSET_32;
    for (size_t i = 0; i < size; ++i) {
        hash ^= bytes[i];
        hash *= FNV_PRIME_32;
    }
    return hash;
}

// Structure to represent a node in the chain
struct Node {
    int value;
    struct Node *next;
} typedef Node;

// Structure to represent a set with chaining collision resolution
struct Set {
    Node **buckets;
    int size;
} typedef Set;

// Function to initialize the set
Set* initializeSet(int size) {
    Set *set = malloc(sizeof(Set));
    set->buckets = malloc(size * sizeof(Node *));
    set->size = size;

    // Initialize buckets
    for (int i = 0; i < size; i++) {
        set->buckets[i] = NULL;
    }

    return set;
}

// Function to print the elements of the set with buckets
void print(Set* set) {
    for(int i = 0; i < set->size; i++) {
        printf("Bucket %d: [ ", i);
        Node *current = set->buckets[i];
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("]\n");
    }
}

int main() {
    // Initialize the set
    Set* set = initializeSet(SIZE);
    srand(time(NULL));

    // Generate random numbers and insert into the set with chaining
    for (int i = 0; i < SIZE; i++) {
        int randomNumber = rand(); // Generate a random number
        uint32_t hashedValue = fnv1a_hash(&randomNumber, sizeof(randomNumber));
        int hashedIndex = hashedValue % SIZE; // Compute the hashed index

        // Create a new node
        Node *newNode = malloc(sizeof(Node));
        newNode->value = randomNumber;
        newNode->next = NULL;

        // Insert the node into the bucket using chaining
        if (set->buckets[hashedIndex] == NULL) {
            set->buckets[hashedIndex] = newNode;
        } else {
            // Collision resolution: Chaining
            Node *current = set->buckets[hashedIndex];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Print the set for visualization
    print(set);

    // Free allocated memory
    for (int i = 0; i < SIZE; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(set->buckets);
    free(set);

    return 0;
}

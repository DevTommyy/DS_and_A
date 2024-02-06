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

// -- Utility
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

#define INITIAL_SIZE 1024
// for the sake of simplicity this HashMap is <int, int>
// (since my implementation of linked list is with int as a value)

struct Node {
    int key;
    LinkedList bucket; // this represents the value
} typedef Node;

// the capacity will be doubled every time the 75% threshold is passed
struct HashMap {
    Node* entries;
    int len;
    int capacity;
} typedef HashMap;

HashMap create(int capacity);

HashMap* rehash(HashMap* old_map);
bool needs_rehashing(HashMap* map);

bool insert(HashMap* map, int key, int val);
LinkedList remove_key(HashMap* map, int key); // removes a key and returns its value

bool contains_key(HashMap* map, int key);
bool is_empty(HashMap* map);

void pprint(HashMap* map);
void freeAll(HashMap map);

/// Instanciate a new `HashMap` with a given capacity.
/// This takes `O(n)` time where `n` is the map `capacity`.
///
/// # Params
/// 
/// `capacity` an `int` representing the map initial capacity
///
/// # Returns
///
/// A new `HashMap` instance with all initialized
/// NOTE: the keys are initialized to a dummy value, which is -1
/// and all the `LinkedList` buckets have their `head` and 
/// `tail` set to `NULL`
HashMap create(int capacity) {
    HashMap map;
    map.capacity = capacity;
    map.len = 0;
    map.entries = (Node *)malloc(capacity * sizeof(Node));

    // Initialize each element in the array
    for (int i = 0; i < capacity; ++i) {
        map.entries[i].key = -1; // Initialize the key to an invalid value
        map.entries[i].bucket.head = NULL; // Initialize the linked list head to NULL
        map.entries[i].bucket.tail = NULL; // Initialize the linked list tail to NULL
    }

    return map;
}

#define SCALING_FACTOR 2
/// Rehashes the elements of a `HashMap` into a new map with double the capacity.
///
/// # Note
///
/// Rehashing involves iterating over all the elements in the original map and 
/// inserting them into the new map. In the worst-case scenario, where many elements 
/// cause long linked lists in buckets due to collisions, the time complexity of rehashing 
/// could approach O(n^2), where n is the number of elements in the original map.
///
/// # Params
///
/// `old_map` a pointer to the original `HashMap` to be rehashed.
///
/// # Returns
///
/// A pointer to the new `HashMap` instance with resized capacity and rehashed elements.
/// The old `HashMap` is deallocated and its memory freed.
HashMap* rehash(HashMap* old_map) {
    // Create a new HashMap instance with double the capacity
    HashMap* new_map = (HashMap *)malloc(sizeof(HashMap));
    new_map->capacity = SCALING_FACTOR * old_map->capacity;
    new_map->len = 0;
    new_map->entries = (Node *)malloc(new_map->capacity * sizeof(Node));

    // Initialize each element in the array
    for (int i = 0; i < new_map->capacity; ++i) {
        new_map->entries[i].key = -1; // Initialize the key to an invalid value
        new_map->entries[i].bucket.head = NULL; // Initialize the linked list head to NULL
        new_map->entries[i].bucket.tail = NULL; // Initialize the linked list tail to NULL
    }

    // Rehash all elements from the old map into the new map
    for (int i = 0; i < old_map->capacity; ++i) {
        if (old_map->entries[i].key != -1) {
            int key = old_map->entries[i].key;
            LinkedList values = old_map->entries[i].bucket;
            for (ListNode *current = values.head; current != NULL; current = current->next) {
                insert(new_map, key, current->val);
            }
        }
    }

    // Free the memory occupied by the old map entries
    freeAll(*old_map);
    free(old_map);

    // Return a pointer to the new map
    return new_map;
}

/// Checks if the map needs rehashing
///
/// # Params
///
/// `map` a pointer to the `HashMap` to be checked.
///
/// # Returns
///
/// `true` if the `HashMap` needs a rehash, `false` otherwise.
bool needs_rehashing(HashMap* map) {
    return (float)map->len >= 0.75 * (float)map->capacity;
}

/// Inserts a key-value pair into the `HashMap`.
/// This operation takes `O(1)` time on average, worst case `O(n)`.
///
/// - If the key already exists in the `HashMap` and matches the one being inserted, 
/// the function returns `false` and does not perform any modifications.
/// - If a collision occurs and the key differs from the existing one at the same index,
/// the function adds the value to the linked list associated with the key's index.
/// - If there is no collision and the key is inserted successfully, the function returns `true`.
///
/// # Note
///
/// This function may trigger rehashing if the number of elements in the `HashMap`
/// exceeds a certain threshold, that operation takes `O(n^2)`.
///
/// # Params
/// 
/// `map` a pointer to the `HashMap` into which the key-value pair will be inserted.
/// `key` an `int` representing the key to be inserted.
/// `val` an `int` representing the value to be associated with the key.
///
/// # Returns
///
/// `true` if the key-value pair is inserted successfully, `false` otherwise.
bool insert(HashMap* map, int key, int val) {

    if(needs_rehashing(map)) {
        map = rehash(map);
    }

    uint32_t hashedKey = fnv1a_hash(&key, sizeof(key));
    int entry = hashedKey % map->capacity;

    // if the key exists and is the same as the one which is being inserted return
    if(contains_key(map, key)) {
        printf("Key already present\n");
        return false;
    }

    // collision
    if(map->entries[entry].key != -1) {
        list_push_back(&(map->entries[entry].bucket), val);
    } else {
        // no collision
        map->entries[entry].key = key;
        list_push_back(&(map->entries[entry].bucket), val);
    }
    map->len++;
    return true;
}

/// Removes a key from the `HashMap` and returns its associated values in a `LinkedList`.
/// This operation takes `O(1)` time on average
///
/// # Params
/// 
/// `map` a pointer to the `HashMap` from which the key needs to be removed.
/// `key` an `int` representing the key to be removed from the `HashMap`.
///
/// # Returns
///
/// If the key exists in the `HashMap`, returns a `LinkedList` containing its associated values.
/// If the key does not exist, returns an empty `LinkedList`.
LinkedList remove_key(HashMap* map, int key) {
    uint32_t hashedKey = fnv1a_hash(&key, sizeof(key));
    int entry = hashedKey % map->capacity;

    if (map->entries[entry].key == key) {
        LinkedList found = map->entries[entry].bucket;
        // Reset the node to default
        map->entries[entry].key = -1;
        map->entries[entry].bucket.head = NULL;
        map->entries[entry].bucket.tail = NULL;

        map->len--;
        return found;
    } else {
        printf("Key does not exist\n");
        // Return an empty linked list
        // WARNING accessing fields of this list
        // results in undefined behavior
        LinkedList empty;
        empty.head = NULL;
        empty.tail = NULL;
        return empty;
    }
}

/// Checks if a key exists in the `HashMap`.
/// This operation takes `O(1)` time
///
/// # Params
/// 
/// `map` a pointer to the `HashMap` to be checked for the existence of the key.
/// `key` an `int` representing the key to be searched for in the `HashMap`.
///
/// # Returns
///
/// `true` if the key exists in the `HashMap`, `false` otherwise.
bool contains_key(HashMap* map, int key) {
    uint32_t hashedKey = fnv1a_hash(&key, sizeof(key));
    int entry = hashedKey % map->capacity;

    // if the key exists and is the same as the one which we're testing for return
    if(map->entries[entry].key != -1 && map->entries[entry].key == key) {
        return true;
    } else {
        return false;
    }
}


/// Checks if an `HashMap` is empty.
/// This operation takes `O(1)` time
///
/// # Params
/// 
/// `map` a pointer to the `HashMap` to be checked.
///
/// # Returns
///
/// `true` if the `HashMap` is empty, `false` otherwise.
bool is_empty(HashMap* map) {
    return map->len == 0;
}

/// Pretty prints the `HashMap` in `O(n)` time
void pprint(HashMap* map) {
    for (int i = 0; i < map->capacity; ++i) {
        if (map->entries[i].key != -1) {
            printf("Key: %d\n", map->entries[i].key);
            printf("Values in the bucket:\n");
            list_pprint(&(map->entries[i].bucket));
            printf("\n");
        }
    }
}

/// Free all the allocated memory from the `HashMap`.
/// This takes `O(1)` time
void freeAll(HashMap map) {
    for (int i = 0; i < map.capacity; ++i) {
        list_freeAll(&(map.entries[i].bucket));
    }
    free(map.entries);
}

// some random testing generated by chatGPT
int main() {
    // Test HashMap
    HashMap map = create(INITIAL_SIZE);

    // Insert some elements
    insert(&map, 1, 10);
    insert(&map, 2, 20);
    insert(&map, 3, 30);
    insert(&map, 4, 40);

    printf("HashMap after initial insertions:\n");
    pprint(&map);

    // Insert elements to trigger resizing
    insert(&map, 5, 50);
    insert(&map, 6, 60);
    insert(&map, 7, 70);
    insert(&map, 8, 80);

    printf("HashMap after resizing:\n");
    pprint(&map);

    // Remove an element
    LinkedList removed_values = remove_key(&map, 2);
    printf("HashMap after removing key 2:\n");
    pprint(&map);
    printf("Values removed for key 2:\n");
    list_pprint(&removed_values);

    // Check if key exists
    printf("Does key 3 exist? %s\n", contains_key(&map, 3) ? "Yes" : "No");
    printf("Does key 2 exist? %s\n", contains_key(&map, 2) ? "Yes" : "No");

    // Free the HashMap
    freeAll(map);

    return 0;
}
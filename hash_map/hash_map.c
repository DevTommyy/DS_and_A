#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// this is not the most well done map, if a collision occurs the key which hash collided
// will just be thrown away

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

struct MapNode {
    int key;
    LinkedList bucket; // this represents the value
} typedef MapNode;

// the capacity will be doubled every time the 75% threshold is passed
struct HashMap {
    MapNode* entries;
    int len;
    int capacity;
} typedef HashMap;

HashMap create(int capacity);

void rehash(HashMap* old_map);
bool needs_rehashing(HashMap* map);

bool insert(HashMap* map, int key, int val);
LinkedList remove_key(HashMap* map, int key); // removes a key and returns its value
LinkedList get_key(HashMap* map, int key);

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
    map.entries = (MapNode *)malloc(capacity * sizeof(MapNode));

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
/// cause long `LinkedList` in buckets due to collisions, the time complexity of rehashing 
/// could approach `O(m^2 * n * o)`, where `m` is the size of the old map, `n` is the size of the new map, 
/// and `o` is the size of the bucket.
///
/// This function deallocates the memory occupied by the old map entries and updates the 
/// old map with the new capacity and entries.
///
/// # Params
///
/// - `old_map` the old `HashMap` to rehash
void rehash(HashMap* old_map) {
    // Create a new array of Nodes with double the capacity
    int new_capacity = SCALING_FACTOR * old_map->capacity;
    MapNode* new_entries = (MapNode *)malloc(new_capacity * sizeof(MapNode));

    // Initialize each element in the new array
    for (int i = 0; i < new_capacity; ++i) {
        new_entries[i].key = -1;
        new_entries[i].bucket.head = NULL;
        new_entries[i].bucket.tail = NULL;
    }

    // Rehash all elements from the old map into the new map
    for (int i = 0; i < old_map->capacity; ++i) {
        if (old_map->entries[i].key != -1) {
            int key = old_map->entries[i].key;
            LinkedList values = old_map->entries[i].bucket;
            for (ListNode *current = values.head; current != NULL; current = current->next) {
                int entry = fnv1a_hash(&key, sizeof(key)) % new_capacity;
                // Collision resolution could be optimized here
                list_push_back(&(new_entries[entry].bucket), current->val);
                new_entries[entry].key = key;
                old_map->len--; // Decrement len for each moved element
            }
        }
    }

    // Free the memory occupied by the old map entries
    for (int i = 0; i < old_map->capacity; ++i) {
        list_freeAll(&(old_map->entries[i].bucket));
    }
    free(old_map->entries);

    // Update the old map with the new capacity and entries
    old_map->capacity = new_capacity;
    old_map->entries = new_entries;
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
        rehash(map);
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

/// Retrieves the values associated with a given key in the HashMap.
///
/// This operation takes O(1) time on average.
///
/// # Params
///
/// - `map` a pointer to the `HashMap` from which the key's values need to be retrieved.
/// - `key` an `int` representing the key to be retrieved from the `HashMap`
///
/// # Returns
///
/// If the key exists in the HashMap, returns a LinkedList containing its associated values.
/// If the key does not exist, returns an empty LinkedList.
LinkedList get_key(HashMap* map, int key) {
    uint32_t hashedKey = fnv1a_hash(&key, sizeof(key));
    int entry = hashedKey % map->capacity;

    if (map->entries[entry].key == key) {
        return map->entries[entry].bucket;
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
    // Instantiate a new HashMap with initial capacity
    HashMap map = create(INITIAL_SIZE);

    // Insert some key-value pairs
    insert(&map, 1, 10);
    insert(&map, 2, 20);
    insert(&map, 3, 30);
    insert(&map, 4, 40);
    insert(&map, 5, 50);

    // Get key and print its associated values
    LinkedList values = get_key(&map, 3);
    printf("Values associated with key 3:\n");
    list_pprint(&values);

    // Check if a key exists
    int key_to_check = 2;
    if (contains_key(&map, key_to_check)) {
        printf("Key %d exists in the map.\n", key_to_check);
    } else {
        printf("Key %d does not exist in the map.\n", key_to_check);
    }

    // Print the HashMap
    printf("HashMap contents:\n");
    pprint(&map);

    // Free allocated memory
    freeAll(map);

    return 0;
}
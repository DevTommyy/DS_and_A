#ifndef HASHMAP_H
#define HASHMAP_H

#include "../headers/LinkedList.h"

/// The element in the hash map
/// 
/// # Fields
///
/// - `key` an `int` representing the key to access the value
/// - `bucket` a `LinkedList` representing the values associated with that key
struct MapNode {
    int key;
    LinkedList bucket; // this represents the value
} typedef MapNode;

/// An `HashMap` data structure of the type `<int, int>`
///
/// # Fields
///
/// - `entries` a pointer to an array of `MapNode` which
/// are the elements in the hashmap
/// - `len` an `int` representing the current length of the map
/// - `capacity` an `int` representing the total capacity of the map
///
/// # Note
///
/// When the map length passes the 75% threshold of the capacity
/// it gets reallocated.
struct HashMap {
    MapNode* entries;
    int len;
    int capacity;
} typedef HashMap;

HashMap map_create(int capacity);

void map_rehash(HashMap* old_map);
bool map_needs_rehashing(HashMap* map);

bool map_insert(HashMap* map, int key, int val);
LinkedList map_remove_key(HashMap* map, int key); // removes a key and returns its value
LinkedList map_get_key(HashMap* map, int key);

bool map_contains_key(HashMap* map, int key);
bool map_is_empty(HashMap* map);

void map_pprint(HashMap* map);
void map_freeAll(HashMap map);

#endif /* HASHMAP_H */
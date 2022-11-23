#pragma once

typedef int Error;
typedef char *Value;

typedef struct HashTable HashTable;

HashTable *createHashTable();

// Adds a value to the hash table
Error insert(HashTable *table, Value value);

// Outputs a hash table
void printHashTable(HashTable *table);

// Frees up all the memory allocated for the hash table
void freeHashTable(HashTable *table);

int maximumLength(HashTable *table);

float averageLength(HashTable *table);

// the number of elements in the hash table
int numberOfElements(HashTable *table);

// the number of segments in the hash table
int numbeOfSegments(HashTable *table);

// Error codes:
//  -1: List not created
//  -2: Memory allocation error
//  -3: HashTable not created
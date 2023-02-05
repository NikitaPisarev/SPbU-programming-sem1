#pragma once

typedef int Error;
typedef int Value;

typedef struct Set Set;

// Creating a empty set
Set *setCreate();

// If the set is created, adds the value to the set
Error addElement(Set *set, Value value);

// Union of sets "firstSet" and "secondFirst"
Error setUnion(Set *firstSet, Set *secondSet, Set *unionSet);

// If a set is created, outputs it
Error printSet(Set *set);

// Frees up all the memory allocated for the set
void freeSet(Set *set);

// Error codes:
//  -1: Set not created
//  -2: Memory allocation error
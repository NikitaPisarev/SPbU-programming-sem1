#include <stdlib.h>
#include "hashTable.h"
#include "list.h"

#define CAPACITY 31

typedef struct HashTable
{
    List *values[CAPACITY];
    int count;
    int size;
} HashTable;

HashTable *createHashTable()
{
    HashTable *newHashTable = calloc(1, sizeof(HashTable));
    if (newHashTable == NULL)
    {
        return NULL;
    }
    newHashTable->count = 0;
    newHashTable->size = CAPACITY;
    return newHashTable;
}

int hash(Value value)
{
    unsigned int result = 0;
    for (int i = 0; value[i] != '\0'; ++i)
    {
        result = result * 13 + value[i];
    }
    return result % CAPACITY;
}

Error insert(HashTable *table, Value value)
{
    if (table == NULL)
    {
        return -3;
    }

    List **list = &table->values[hash(value)];
    List *node = findNode(list, value);

    if (node == NULL)
    {
        int errorCode = 0;
        if ((errorCode = addNode(list, value)) != 0)
        {
            return errorCode;
        }
        ++table->count;
        return 0;
    }
    else
    {
        ++node->amount;
        return 0;
    }
}

int maximumLength(HashTable *table)
{
    if (table == NULL)
    {
        return -3;
    }

    int maximum = 0;
    int currentLength = 0;
    for (int i = 0; i < table->size; ++i)
    {
        currentLength = lengthList(&table->values[i]);
        if (currentLength > maximum)
        {
            maximum = currentLength;
        }
    }
    return maximum;
}

float averageLength(HashTable *table)
{
    if (table == NULL)
    {
        return -3;
    }

    int sumsLength = 0;
    int notEmpty = 0;
    int currentLength = 0;
    for (int i = 0; i < table->size; ++i)
    {
        currentLength = lengthList(&table->values[i]);
        if (currentLength != 0)
        {
            sumsLength += currentLength;
            ++notEmpty;
        }
    }
    if (notEmpty != 0)
    {
        return (float)sumsLength / notEmpty;
    }
    else
    {
        return 0;
    }
}

int numberOfElements(HashTable *table)
{
    if (table == NULL)
    {
        return -3;
    }
    return table->count;
}

int numbeOfSegments(HashTable *table)
{
    if (table == NULL)
    {
        return -3;
    }
    return table->size;
}

void printHashTable(HashTable *table)
{
    if (table == NULL)
    {
        return;
    }

    for (int i = 0; i < table->size; ++i)
    {
        printList(table->values[i]);
    }
}

void freeHashTable(HashTable *table)
{
    if (table == NULL)
    {
        return;
    }

    for (int i = 0; i < table->size; ++i)
    {
        freeList(table->values[i]);
    }
    free(table);
}
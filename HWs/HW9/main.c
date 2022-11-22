#include <stdio.h>
#include "hashTable.h"

#define maximumSize 256

int main()
{
    FILE *file = fopen("../HWs/HW9/data.txt", "r");
    if (file == NULL)
    {
        printf("File opening error.\n");
        return 0;
    }
    HashTable *table = createHashTable();
    if (table == NULL)
    {
        printf("Table creation error.\n");
        return 0;
    }

    char buffer[maximumSize] = {0};
    int errorCode = 0;
    while (fscanf(file, "%s", buffer) == 1)
    {
        if ((errorCode = insert(table, buffer)) != 0)
        {
            printf("The Insert function finished with error %d.\n", errorCode);
            return 0;
        }
    }
    fclose(file);

    printf("Word frequencies in your file:\n");
    printHashTable(table);
    printf("Fill factor %f", (float)numberOfElements(table) / numbeOfSegments(table));
    freeHashTable(table);
    return 0;
}
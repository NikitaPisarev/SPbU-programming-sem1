#include <stdio.h>
#include "list.h"
#include "hashTable.h"

int main()
{
    List *list = listCreate();
    addElement(list, "Bba");
    addElement(list, "Alla");
    deleteElement(list, "Bba");
    printList(list);
    freeList(list);
    return 0;
}
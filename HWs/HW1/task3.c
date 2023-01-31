#include <stdio.h>
#include <stdbool.h>

#define arraySize 100

void reverse(int array[], int length)
{
    for (int i = 0; i < length / 2; ++i)
    {
        int clipboard = 0;

        clipboard = array[i];
        array[i] = array[length - (i + 1)];
        array[length - (i + 1)] = clipboard;
    }
}

void printArray(int array[], int length, int key)
{
    printf("[ ");
    for (int k = 0; k < length; ++k)
    {
        printf("%d ", array[k]);
        if (k == key - 1)
        {
            printf("| ");
        }
    }
    printf("]\n");
}

int main()
{
    int lengthN = 0;
    int lengthM = 0;
    int array[arraySize] = { 0 };
    int scanRes = 0;
    bool flagInput = true;

    do
    {
        flagInput = true;

        printf("Enter length \"N\" then length \"M\": ");
        scanRes = scanf("%d%d", &lengthN, &lengthM);

        if (!scanRes || lengthM <= 0 || lengthN <= 0 || lengthN + lengthM > arraySize)
        {
            printf("Invalid values (length N and length M must be positive and in total no more than %d). Try again!\n", arraySize);
            scanf("%*[^\n]");
            flagInput = false;
        }
    } while (!flagInput);

    printf("Enter an array, exactly %d element(s):\n", lengthM + lengthN);
    for (int i = 0; i < lengthM + lengthN; ++i)
    {
        scanf("%d", &array[i]);
    }

    printf("\nThe array was like this:\n");
    printArray(array, lengthM + lengthN, lengthM);

    reverse(array, lengthM);
    reverse(array, lengthM + lengthN);
    reverse(array, lengthN);

    printf("\nThe array become like this:\n");
    printArray(array, lengthM + lengthN, lengthN);

    return 0;
}
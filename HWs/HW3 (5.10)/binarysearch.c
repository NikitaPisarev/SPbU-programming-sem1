#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define arraySize 999

void arrayRandom(int array[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        array[i] = rand();
    }

}

bool binarySearch(int array[], int length, int key);

void main()
{
    int lengthN = 0;
    int lengthK = 0;
    int scan_resN = 0;
    int scan_resK = 0;
    bool flagInput = true;

    do
    {
        printf("Enter \"N\" and \"K\": ");
        scan_resN = scanf("%d", &lengthN);
        scan_resK= scanf("%d", &lengthK);

        flagInput = true;

        if (!scan_resN || !scan_resK || lengthK <= 0 || lengthN <= 0)
        {
            printf("Incorrect input (\"N\" and \"K\" are positive and less than %d). Try again!\n", arraySize);
            scanf_s("%*[^\n]");

            flagInput = false;
        }
    } while (!scan_resN || !scan_resK);

    int arrayN[arraySize] = { 0 };
    int arrayK[arraySize] = { 0 };

    arrayRandom(arrayK, lengthK);
    arrayRandom(arrayN, lengthN);

    printf("The array \"N\" looks like this:\n[ ");
    for (int i = 0; i < lengthN; ++i)
    {
        printf("%d ", arrayN[i]);
    }
    printf("]");
    /*
    for (int i = 0; i < lengthK; ++i)
    {
        if (binarySearch(arrayN, lengthN, arrayK[i]))
        {
            printf("%d is present in the array.\n", arrayK[i]);
        }
        else
        {
            printf("%d is missing in the array.\n", arrayK[i]);
        }
    }
    */
}
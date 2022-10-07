#include <stdio.h>
#include <stdbool.h>

#define arraySize 100

void reverse(int array[], int length)
{
    for (int i = 0; i < (length / 2); ++i)
    {
        int clipboard = 0;

        clipboard = array[i];
        array[i] = array[length - (i + 1)];
        array[length - (i + 1)] = clipboard;
    }

}
void task3(void)
{
    int lengthN = 0;
    int lengthM = 0;
    int arrayInverse[arraySize] = { 0 };
    int scanf_res = 0;
    bool flagInput = true;

    do
    {
        flagInput = true;

        printf("\nEnter length \"N\" then length \"M\": ");
        scanf_res = scanf_s("%d%d", &lengthN, &lengthM);

        if (!scanf_res || lengthM <= 0 || lengthN <= 0)
        {
            printf("Invalid values (length N and length M must be positive). Try again!");
            scanf_s("%*[^\n]");
            flagInput = false;
        }
    } while (!scanf_res || !flagInput);

    printf("Enter an array, exactly %d element(s):\n", lengthM + lengthN);
    for (int i = 0; i < (lengthM + lengthN); ++i)
    {
        scanf_s("%d", &arrayInverse[i]);
    }
   

    printf("\nThe array was like this:\n[ ");
    for (int k = 0; k < (lengthN + lengthM); ++k)
    {
        printf("%d ", arrayInverse[k]);
        if (k == (lengthM - 1))
        {
            printf("| ");
        }
    }
    printf("]\n");

    reverse(arrayInverse, lengthM); //Переворачиваем первую часть
    reverse(arrayInverse, lengthM + lengthN); //Переворачиваем полностью
    reverse(arrayInverse, lengthN); //Переворачиваем бывшую вторую часть(ныне первую)
  
    printf("\nThe array become like this:\n[ ");
    for (int k = 0; k < (lengthN + lengthM); ++k)
    {
        printf("%d ", arrayInverse[k]);
        if (k == (lengthN - 1))
        {
            printf("| ");
        }
    }
    printf("]\n\n");
}
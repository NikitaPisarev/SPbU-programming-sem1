#include <stdio.h>
#include <stdbool.h>

#define lengthString 100

const char* checkBalanced(char string[])
{
    int counterBalanceLine = 0;
    bool flagBracket = false;

    if (string[0] == '\0')
    {
        return "This is not a sequence.";
    }

    for (int i = 0; i < lengthString; ++i)
    {
        if (string[i] == '\0' || counterBalanceLine < 0)
        {
            break;
        }

        if (string[i] == '(')
        {
            ++counterBalanceLine;
            flagBracket = true; 
        }
        else if (string[i] == ')')
        {
            --counterBalanceLine;
        }
    }

    if (counterBalanceLine == 0 && flagBracket) //Условие на то, что хотя бы одна скобка появилась
    {
        return "Good sequence!";
    }
    else
    {
        return "Bad sequence!";
    }
}

void task5(void)
{
    char stringBracket[lengthString] = { '\0' };

    printf("\nEnter bracket sequence (not more than %d): \n", lengthString);

    scanf_s("%s", &stringBracket, lengthString);

    printf("%s\n\n", checkBalanced(stringBracket));
}
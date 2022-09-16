#include <stdio.h>
#include <string.h>

#define lengthString 100

void task6(void)
{
    int counterEntry = 0;
    char string[lengthString] = { '\0' };
    char subString[lengthString] = { '\0' };
    
    printf("\nEnter a string(S1) then a substring(S2), with 1 <= S1 <= S2 <= 100:\n");

    scanf_s("%s", &string, lengthString);
    scanf_s("%s", &subString, lengthString);
    
    int lengthStr = strlen(string);
    int lengthSubStr = strlen(subString);
    
    for (int i = 0; i < lengthStr; ++i)
    {
        if (subString[0] == string[i])
        {
            for (int j = 0; j < lengthSubStr; ++j)
            {
                if (subString[j] != string[j + i])
                {
                    break;
                }

                if (j == (lengthSubStr - 1))
                {
                    ++counterEntry;
                }
            }

        }
    }

    printf("Amount of occurrence of S2 in S1: %d\n\n", counterEntry);
}
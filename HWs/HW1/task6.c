#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define lengthString 100

void task6(void)
{
    int counterEntry = 0;
    char string[lengthString] = { '\0' };
    char subString[lengthString] = { '\0' };
    
    printf("\nEnter a string(S1) and substring(S2) separated by a space, with 1 <= S1 <= S2 <= %d:\n", lengthString);

    scanf_s("%s", &string, lengthString);
    scanf_s("%s", &subString, lengthString);
    
    const int lengthSubStr = strlen(subString);
    const int lengthStr = strlen(string) - lengthSubStr + 1;
    bool flagStr = true;
    
    for (int i = 0; i < lengthStr; ++i)
    {
        for (int j = 0; j < lengthSubStr; ++j)
        {
            if (subString[j] != string[i + j])
            {
                flagStr = false;
                break;
            }
        }

        if (flagStr)
        {
            ++counterEntry;
        }
        
        flagStr = true;
    }

    printf("Amount of occurrence of \"%s\" in \"%s\": %d\n\n", subString, string, counterEntry);
}
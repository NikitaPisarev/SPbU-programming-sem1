#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define lengthString 100

int main()
{
    int counterEntry = 0;
    char string[lengthString] = { '\0' };
    char subString[lengthString] = { '\0' };
    
    printf("Enter a string(S1) and substring(S2) separated by a space, with 1 <= S1 <= S2 <= %d:\n", lengthString);

    scanf("%s", string);
    scanf("%s", subString);
    
    const int lengthSubString = strlen(subString);
    const int border = strlen(string) - lengthSubString + 1;
    bool isEntry = true;
    
    for (int i = 0; i < border; ++i)
    {
        for (int j = 0; j < lengthSubString; ++j)
        {
            if (subString[j] != string[i + j])
            {
                isEntry = false;
                break;
            }
        }

        if (isEntry)
        {
            ++counterEntry;
        }
        isEntry = true;
    }

    printf("Amount of occurrence of \"%s\" in \"%s\": %d\n", subString, string, counterEntry);
    return 0;
}
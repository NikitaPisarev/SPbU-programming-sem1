#include <stdio.h>
#include <stdbool.h>

#define maximumSize 256

bool isCorrectString(char *string)
{
    int state = 0;
    char currentCharacter = -1;
    int counter = 0;
    bool isContinue = true;
    while (isContinue && currentCharacter != '\0')
    {
        currentCharacter = string[counter++];
        switch (state)
        {
        case 0:
            if ((currentCharacter >= 'A' && currentCharacter <= 'Z') || (currentCharacter >= 'a' && currentCharacter <= 'z'))
            {
                state = 1;
                break;
            }
            return false;
        case 1:
            if ((currentCharacter >= 'A' && currentCharacter <= 'Z') || (currentCharacter >= 'a' && currentCharacter <= 'z') ||
                (currentCharacter >= '0' && currentCharacter <= '9') || (currentCharacter == '_'))
            {
                break;
            }
            isContinue = false;
            break;
        }
    }
    return currentCharacter == '\0';
}

bool tests()
{
    char testString1[] = "My_var001";
    char testString2[] = "A";
    char testString3[] = "_Afewew";
    char testString4[] = "M_>_";

    return isCorrectString(testString1) &&
           isCorrectString(testString2) &&
           !isCorrectString(testString3) &&
           !isCorrectString(testString4);
}

int main()
{
    if (!tests())
    {
        printf("Tests failed!\n");
        return -1;
    }
    char string[maximumSize] = {0};
    printf("Enter the string you want to test for the regular expression [A-Za-z] ([A-Za-z] | [0-9] | _ )*\n");
    printf("(but not more than %d characters):\n", maximumSize - 1);
    scanf("%s", string);

    if (isCorrectString(string))
    {
        printf("\"%s\" matches the regular expression!\n", string);
    }
    else
    {
        printf("\"%s\" does not match the regular expression :(\n", string);
    }

    return 0;
}
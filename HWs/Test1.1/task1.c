#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

bool isPalindrome(char string[], int lengthString)
{
    bool flagPalindrome = true;

    for (int i = 0; i < (lengthString / 2); ++i) 
    {
        if (string[i] != string[lengthString - (i + 1)])
        {
            flagPalindrome = false;
            break;
        }
    }  

    return flagPalindrome;
}

int testPalindrome()
{
    int errorCode = 1;

    char stringTest1[] = "aaabbbaaa";
    if (!isPalindrome(stringTest1, 9))
    {
        errorCode = -1;
    }

    char stringTest2[] = "1221";
    if (!isPalindrome(stringTest2, 4))
    {
        errorCode = -2;
    }

    char stringTest3[] = "2022";
    if (isPalindrome(stringTest3, 4))
    {
        errorCode = -3;
    }
    
    char stringTest4[] = "\0";
    if (!isPalindrome(stringTest4, 1))
    {
        errorCode = -4;
    }

    return errorCode;
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    int errorCode = 1;
    if (!(errorCode = testPalindrome()))
    {
        printf("Ошибка в функции isPalindrome. Код ошибки %d.\n", errorCode);
        return 0;
    }

    char *string = (char *) malloc(sizeof(char));
    char currentCharacter = 0;
    int lengthString = 0;

    printf("Привет, введи строку:\n");

    while ((currentCharacter = getchar()) != '\n') // Считываем строку посимвольно
    {
        string[lengthString] = currentCharacter; // Записываем текущий символ
        ++lengthString;
        string = (char *) realloc(string, (lengthString + 1)*sizeof(char)); // Добавляем память для следующего символа (или для \0)
    }

    string[lengthString] = '\0';

    if (isPalindrome(string, lengthString))
    {
        printf("Это палиндром!\n");
    }
    else
    {
        printf("Это не палиндром.\n");
    }

    free(string);
    return 0;
}
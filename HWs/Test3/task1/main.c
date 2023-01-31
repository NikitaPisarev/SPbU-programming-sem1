#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define binarySize 256

int roundUp(int firstNumber, int secondNumber)
{
    int value = firstNumber / secondNumber;
    return value * secondNumber == firstNumber ? value : value + 1;
}

bool isCorrectBinaryNumber(char *number)
{
    int stringLength = strlen(number);
    for (int i = 0; i < stringLength; ++i)
    {
        if (number[i] != '0' && number[i] != '1')
        {
            return false;
        }
    }
    return true;
}

char triadTransformation(int number[])
{
    int power = 1;
    int result = 0;
    for (int i = 0; i < 3; ++i)
    {
        result += power * number[i];
        power <<= 1;
    }

    return result + '0';
}

char *binaryToOctal(char *binaryNumber)
{
    int binaryNumberLength = strlen(binaryNumber) - 1;
    int lengthOctalNumber = roundUp(binaryNumberLength + 1, 3);
    char *octalNumber = calloc(lengthOctalNumber + 1, sizeof(char));
    if (octalNumber == NULL)
    {
        return NULL;
    }
    octalNumber[lengthOctalNumber--] = '\0';
    int counter = 0;
    int triad[3] = {0};
    for (int i = binaryNumberLength; i >= 0; --i)
    {
        if (binaryNumber[i] == '1')
        {
            triad[counter] = 1;
        }
        else
        {
            triad[counter] = 0;
        }
        ++counter;
        if (counter == 3)
        {
            octalNumber[lengthOctalNumber] = triadTransformation(triad);
            --lengthOctalNumber;
            counter = 0;
            for (int j = 0; j < 3; ++j)
            {
                triad[j] = 0;
            }
        }
    }
    if (counter > 0)
    {
        octalNumber[lengthOctalNumber] = triadTransformation(triad);
    }
    return octalNumber;
}

bool tests()
{
    char *resultOne = binaryToOctal("10101");
    char *resultTwo = binaryToOctal("111");
    if (resultOne == NULL || resultTwo == NULL || strcmp(resultOne, "25") != 0 || strcmp(resultTwo, "7") != 0)
    {
        free(resultOne);
        free(resultTwo);
        return false;
    }
    free(resultOne);
    free(resultTwo);
    return true;
}

int main()
{
    if (!tests())
    {
        printf("Tests failed.\n");
        return -1;
    }
    char binaryNumber[binarySize] = {0};
    printf("Hi, please enter a binary number(no longer than %d):\n", binarySize - 1);
    scanf("%s", binaryNumber);
    if (!isCorrectBinaryNumber(binaryNumber))
    {
        printf("This is not a binary number.\n");
        return -1;
    }
    char *octalNumber = binaryToOctal(binaryNumber);
    printf("Your number in octal notation: ");
    bool isExtraZero = true;
    for (int i = 0; octalNumber[i] != '\0'; ++i)
    {
        if (octalNumber[i] == '0' && isExtraZero)
        {
            continue;
        }
        isExtraZero = false;
        printf("%c", octalNumber[i]);
    }
    printf("\n");
    free(octalNumber);
    return 0;
}
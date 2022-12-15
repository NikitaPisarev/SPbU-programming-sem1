#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define lengthBinaryNumber sizeof(int) * 8

void printArray(unsigned char array[], char length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("%d", array[i]);
    }
}

void binaryRepresentation(unsigned char array[], int number)
{
    int bit = 1;

    for (int i = lengthBinaryNumber - 1; i >= 0; --i)
    {
        array[i] = (number & bit) ? 1 : 0;
        bit = bit << 1;
    }
}

void addBinaryNumbers(unsigned char firstNumber[], unsigned char secondNimber[], unsigned char answer[])
{
    int temp = 0;
    int remainder = 0;

    for (int i = lengthBinaryNumber - 1; i >= 0; --i)
    {
        temp = firstNumber[i] + secondNimber[i] + remainder;
        answer[i] = temp % 2;
        remainder = temp / 2;
    }
}

int conversionFromBinaryDecimal(unsigned char array[], char length)
{
    int decimalResult = 0;
    int power = 1;

    for (int i = length - 1; i >= 0; --i)
    {
        decimalResult += array[i] * power;
        power <<= 1;
    }

    return decimalResult;
}

bool testBinaryRepresentation()
{
    int number = 12;
    unsigned char binaryNumber[lengthBinaryNumber] = {0};
    unsigned char correctBinaryNumber[lengthBinaryNumber] = {0};
    correctBinaryNumber[lengthBinaryNumber - 3] = 1; // 000100 = 4
    correctBinaryNumber[lengthBinaryNumber - 4] = 1; // 001000 = 8

    binaryRepresentation(binaryNumber, number);

    for (int i; i < lengthBinaryNumber; ++i)
    {
        if (binaryNumber[i] != correctBinaryNumber[i])
        {
            return false;
        }
    }

    return true;
}

bool testAddBinaryNumbers()
{
    unsigned char binaryNumber1[lengthBinaryNumber] = {0};
    unsigned char binaryNumber2[lengthBinaryNumber] = {0};

    binaryNumber1[lengthBinaryNumber - 3] = 1; // 000100 = 4
    binaryNumber2[lengthBinaryNumber - 3] = 1; // 000100 = 4

    unsigned char result[lengthBinaryNumber] = {0};
    unsigned char correctResult[lengthBinaryNumber] = {0};
    correctResult[lengthBinaryNumber - 4] = 1; // 001000 = 8

    addBinaryNumbers(binaryNumber1, binaryNumber2, result);

    for (int i = 0; i < lengthBinaryNumber; ++i)
    {
        if (result[i] != correctResult[i])
        {
            return false;
        }
    }

    return true;
}

bool testConversionFromBinaryDecimal()
{
    unsigned char binaryNumber[lengthBinaryNumber] = {0};
    binaryNumber[lengthBinaryNumber - 3] = 1; // 000100 = 4
    binaryNumber[lengthBinaryNumber - 4] = 1; // 001000 = 8

    return conversionFromBinaryDecimal(binaryNumber, lengthBinaryNumber) == 12;
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    if (!testBinaryRepresentation())
    {
        printf("Ошибка работы функции BinaryRepresentation.\n");
        return -1;
    }

    if (!testAddBinaryNumbers())
    {
        printf("Ошибка работы функции AddBinaryNumbers.\n");
        return -2;
    }

    if (!testConversionFromBinaryDecimal())
    {
        printf("Ошибка работы функции ConversionFromBinaryDecimal.\n");
        return -3;
    }

    int firstNumber = 0;
    int secondNumber = 0;
    int scanResFirstNumber = 0;
    int scanResSecondNumber = 0;

    printf("Привет, введи два числа: ");
    do
    {
        scanResFirstNumber = scanf("%d", &firstNumber);
        scanResSecondNumber = scanf("%d", &secondNumber);

        if (!scanResFirstNumber || !scanResSecondNumber)
        {
            printf("Ошибка ввода. Вводить можно только целые числа. Попробуй еще раз!\n");
            scanf("%*[^\n]");
        }

    } while (!scanResFirstNumber || !scanResSecondNumber);

    unsigned char binaryFirstNumber[lengthBinaryNumber] = {0};
    unsigned char binarySecondNumber[lengthBinaryNumber] = {0};
    binaryRepresentation(binaryFirstNumber, firstNumber);
    binaryRepresentation(binarySecondNumber, secondNumber);

    printf("\n ");
    printArray(binaryFirstNumber, lengthBinaryNumber);
    printf(" (%d)\n+\n ", firstNumber);
    printArray(binarySecondNumber, lengthBinaryNumber);
    printf(" (%d) \n --------------------------------\n ", secondNumber);

    unsigned char binarySum[lengthBinaryNumber] = {0};
    addBinaryNumbers(binaryFirstNumber, binarySecondNumber, binarySum);

    int decimalSum = conversionFromBinaryDecimal(binarySum, lengthBinaryNumber);

    printArray(binarySum, lengthBinaryNumber);
    printf(" (%d)", decimalSum);
    printf("\n\nСумма %d и %d равна %d.\n", firstNumber, secondNumber, decimalSum);

    return 0;
}
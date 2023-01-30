#include <stdio.h>
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
        power *= 2;
    }

    return decimalResult;
 } 

void main()
{
    setlocale(LC_ALL, "RU-ru");

    int firstNumber = 0;
    int secondNumber = 0;
    int scan_resFirstNumber = 0;
    int scan_resSecondNumber = 0;

    printf("Привет, введи два числа: ");
    do
    {
        scan_resFirstNumber = scanf("%d", &firstNumber);
        scan_resSecondNumber = scanf("%d", &secondNumber);

        if (!scan_resFirstNumber || !scan_resSecondNumber)
        {
            printf("Ошибка ввода. Вводить можно только целые числа. Попробуй еще раз!\n");
            scanf("%*[^\n]");
        }

    } while (!scan_resFirstNumber || !scan_resSecondNumber);

    unsigned char binaryFirstNumber[lengthBinaryNumber] = { 0 };
    unsigned char binarySecondNumber[lengthBinaryNumber] = { 0 };
    binaryRepresentation(binaryFirstNumber, firstNumber);
    binaryRepresentation(binarySecondNumber, secondNumber);

    printf("\n ");
    printArray(binaryFirstNumber, lengthBinaryNumber);
    printf(" (%d)\n+\n ", firstNumber);
    printArray(binarySecondNumber, lengthBinaryNumber);
    printf(" (%d) \n --------------------------------\n ", secondNumber);

    unsigned char binarySum[lengthBinaryNumber] = { 0 };
    addBinaryNumbers(binaryFirstNumber, binarySecondNumber, binarySum);

    int decimalSum = conversionFromBinaryDecimal(binarySum, lengthBinaryNumber);

    printArray(binarySum, lengthBinaryNumber);
    printf(" (%d)", decimalSum);
    
    printf("\n\nСумма %d и %d равна %d.\n", firstNumber, secondNumber, decimalSum);
}
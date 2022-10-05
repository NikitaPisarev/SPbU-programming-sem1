#include <stdio.h>
#include <locale.h>

#define lengthBinaryNumber sizeof(int) * 8

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

 int conversionFromBinaryDecimal(unsigned char array[])
 {
    int decimalResult = 0;
    int power = 1;

    for (int i = lengthBinaryNumber - 1; i >= 0; --i)
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

    printf("Привет, введи два числа: ");
    scanf("%d", &firstNumber);
    scanf("%d", &secondNumber);

    unsigned char binaryFirstNumber[lengthBinaryNumber] = { 0 };
    unsigned char binarySecondNumber[lengthBinaryNumber] = { 0 };
    binaryRepresentation(binaryFirstNumber, firstNumber);
    binaryRepresentation(binarySecondNumber, secondNumber);


    printf("\n ");
    for (int i = 0; i < lengthBinaryNumber; ++i)
    {
        printf("%d", binaryFirstNumber[i]);
    }
    printf("\n+\n ");
    for (int i = 0; i < lengthBinaryNumber; ++i)
    {
        printf("%d", binarySecondNumber[i]);
    }
    printf("\n --------------------------------\n ");

    unsigned char sumTwoNumbers[lengthBinaryNumber] = { 0 };
    addBinaryNumbers(binaryFirstNumber, binarySecondNumber, sumTwoNumbers);

    for (int i = 0; i < lengthBinaryNumber; ++i)
    {
        printf("%d", sumTwoNumbers[i]);
    }   
    
    printf("\n\nСумма %d и %d равна %d\n", firstNumber, secondNumber, conversionFromBinaryDecimal(sumTwoNumbers));
}
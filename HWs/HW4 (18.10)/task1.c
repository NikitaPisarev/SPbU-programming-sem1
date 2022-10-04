#include <stdio.h>
#include <locale.h>

void main()
{
    setlocale(LC_ALL, "");

    unsigned char firstNumber = 0;
    unsigned char secondNumber = 0;

    printf("Привет, введи два числа: ");
    scanf("%d", &firstNumber);
    scanf("%d", &secondNumber);

    firstNumber = firstNumber & ~(1 << 3);
    printf("Ответ: %d", firstNumber );
}
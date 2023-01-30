#include <stdio.h>

#define digit 10


int main()
{
    int countSums[28] = { 0 };
    int countLuckyTickets = 0;

    for (int firstNumber = 0; firstNumber < digit; ++firstNumber)
    {
        for (int secondNumber = 0; secondNumber < digit; ++secondNumber)
        {
            for (int thirdNumber = 0; thirdNumber < digit; ++thirdNumber)
            {
                ++countSums[firstNumber + secondNumber + thirdNumber];
            }
        }
    }

    for (int i = 0; i < 28; ++i)
    {
        countLuckyTickets += countSums[i] * countSums[i];
    }

    printf("Amount of lucky tickets: %d\n", countLuckyTickets);

    return 0;
}

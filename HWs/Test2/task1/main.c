#include <stdio.h>
#include <stdbool.h>

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

int main()
{
    FILE *file = fopen("data.txt", "r");
    if (file == NULL)
    {
        printf("File opening error.\n");
        return 0;
    }

    bool point = false;
    int day = 0;
    int month = 0;
    int year = 0;
    int date = 0;
    int maxDate = 0;

    char currentСharacter = 0;
    char prevCharacter = 0;
    char prevPrevCharacter = 0;
    char prevPrevPrevCharacter = 0; // :)
    while (!feof(file))
    {
        prevPrevPrevCharacter = prevPrevCharacter;
        prevPrevCharacter = prevCharacter;
        prevCharacter = currentСharacter;
        currentСharacter = fgetc(file);

        if (currentСharacter == '.')
        {
            if (!point && isDigit(prevCharacter) && isDigit(prevPrevCharacter))
            {
                day = (prevCharacter) + (prevPrevCharacter)*10;
                point = true;
            }

            if (point)
            {
                if (prevPrevPrevCharacter != '.' || !isDigit(prevCharacter) || !isDigit(prevPrevCharacter))
                {
                    point = false;
                }
                else
                {
                    month = (prevCharacter) + (prevPrevCharacter)*10;
                    for (int i = 0; i < 4; ++i)
                    {
                        currentСharacter = fgetc(file);
                        year = year * 10 + (currentСharacter);
                        if (!feof(file))
                        {
                            break;
                        }
                    }
                    date = day + month * 100 + year * 10000;
                    year = 0;
                    if (date > maxDate)
                    {
                        printf("%d %d %d ", day, month, date);
                        maxDate = date;
                    }
                    point = false;
                }
            }
        }
    }
    printf("Maximum date: %d", maxDate);

    fclose(file);
    return 0;
}
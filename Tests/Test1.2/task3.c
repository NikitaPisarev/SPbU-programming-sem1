#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "RU-ru");

    FILE *file = fopen("data.txt", "r");
    if (file == NULL || feof(file))
    {
        printf("Ошибка открытия файла (или файл пуст).\n");
        return 0;
    }

    unsigned char currentCharacterCode = fgetc(file);
    unsigned char previousCharacterCode = -1;
    unsigned char matchCounter = 1;
    while (!feof(file))
    {
        previousCharacterCode = currentCharacterCode;
        currentCharacterCode = fgetc(file);

        if (previousCharacterCode == currentCharacterCode)
        {
            ++matchCounter;
        }
        else
        {
            if (matchCounter == 1)
            {
                printf("%c", previousCharacterCode);
            }
            else
            {
                printf("%d%c", matchCounter, previousCharacterCode);
            }
            matchCounter = 1;
        }
    }

    fclose(file);
    return 0;
}
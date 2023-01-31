#include <stdio.h>
#include <locale.h>

#define sizeOfCodes 255

int main()
{
    setlocale(LC_ALL, "RU-ru");

    FILE *file = fopen("text.txt", "r");

    if (file == NULL)
    {
        printf("Ошибка работы с файлом.\n");
        return 0;
    }

    int frequencyDictionary[sizeOfCodes] = { 0 };

    while(!feof(file))
    {
        ++frequencyDictionary[fgetc(file)];
    }

    printf("В твоем файле:\n\n");

    for (int i = 0; i < sizeOfCodes; ++i)
    {
        if (frequencyDictionary[i])
        {
            if (((char) i) == '\n')
            {
                printf("Переносов строки: %d.\n",frequencyDictionary[i]);
            }
            else
            {
                printf("Символ \"%c\" встречается %d раз(а).\n", i, frequencyDictionary[i]);
            }
        }
    }
    
    printf("\nУдачи!\n");

    fclose(file); 

    return 0;
}
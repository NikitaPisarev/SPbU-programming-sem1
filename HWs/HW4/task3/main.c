#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#define maximumSize 255
#define recordSize 100

int printList(FILE *file, unsigned char amountRecord)
{
    if (amountRecord == 0)
    {
        printf("\nCправочник пуст.\n\n");
        return 1;
    }

    printf("\nСправочник:\n");

    char record[maximumSize] = { 0 };

    for (int i = 0; i < amountRecord; ++i)
    {
        fgets(record, maximumSize, file);
        printf("%d. %s", i + 1, record);
    }
    fseek(file, 0 , SEEK_SET);
    printf("\n");

    return 0;
}

void printActions(void)
{
    printf(" ------------------------------------\n");
    printf(" 0 — Выход\n");
    printf(" 1 — Добавить запись (имя и телефон)\n");
    printf(" 2 — Распечатать все имеющиеся записи\n");
    printf(" 3 — Найти телефон по имени\n");
    printf(" 4 — Найти имя по телефону\n");
    printf(" 5 — Сохранить текущие данные в файл\n");
    printf(" 6 - Посмотреть список команд\n");
    printf(" ------------------------------------\n");
}

unsigned char amountRecord(FILE *file)
{
    char amount = 0;
    char temp[maximumSize] = { 0 };

    while (!feof(file))
    {
        if (fgets(temp, maximumSize, file) != NULL)
        {
            ++amount;
        }
    }
    fseek(file, 0, SEEK_SET);

    return amount;
}

char *addRecord(char current)
{
    char *buffer = calloc(maximumSize ,sizeof(char));
    printf("\nВведи телефон и номер (Например: +79123456789 Александр Сергеевич):\n");
    getchar();
    fgets(buffer, recordSize, stdin);

    printf("Запись успешна добавлена.\n\n");

    return buffer;
}

int saveData(FILE *file, char *data[], char lengthData)
{
    if (lengthData == 0)
    {
        printf("\nИзменения отсутствуют.\n\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);

    for (int i = 0; i < lengthData; ++i)
    {
        fputs(data[i], file);
        data[i] = 0;
    }

    fseek(file, 0, SEEK_SET);

    printf("\nИзменения успешно сохранены!\n\n");

    return 0;
}

void nameByPhone(FILE *file, char number[])
{
    bool flagNumber = false;
    char currentNumber[maximumSize] = { 0 };
    char currentName[maximumSize] = { 0 };


    while (!feof(file))
    {
        fscanf(file, "%s", &currentNumber);
        if (fgets(currentName, maximumSize, file) != NULL)
        {
            if (!strcmp(currentNumber, number))
            {
                printf("\nНомер %s принадлежит%s\n", currentNumber, currentName);
                flagNumber = true;
            }        
        }      
    }

    fseek(file, 0, SEEK_SET);

    if (!flagNumber)
    {
        printf("\nТакого номера нет в справочнике.\n\n");
    }
}

void phoneByName(FILE *file, char name[])
{
    bool flagName= false;
    char currentNumber[maximumSize] = { 0 };
    char currentName[maximumSize] = { 0 };


    while (!feof(file))
    {
        fscanf(file, "%s", &currentNumber);
        if (fgets(currentName, maximumSize, file) != NULL)
        {
            if (!strncmp(currentName, name, strlen(name)))
            {
                printf("\nУ абонента%s номер %s\n\n", name, currentNumber);
                flagName = true;
            }     
        }   
    }

    fseek(file, 0, SEEK_SET);

    if (!flagName)
    {
        printf("\nТакого имени нет в справочнике.\n\n");
    }
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    FILE *file = fopen("database.txt", "a+");

    if (file == NULL)
    {
        printf("Ошибка работы с файлом.\n");
        return 0;
    }

    char *data[recordSize] = { 0 };
    char current = 0;

    printf("Привет, это телефонный справочник!\nВот что я умею:\n");
    printActions();

    int action = -1;

    while (action != 0)
    {
        printf("Введи номер команды: ");
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            printf("Удачи!\n");
            break;
        
        case 1:
            data[current] = addRecord(current);
            ++current;
            break;
        
        case 2:
            unsigned char amount = amountRecord(file);
            printList(file, amount);
            break;
        
        case 3:
            char name[maximumSize] = { 0 };

            printf("Введите имя абонента, по которому хотите найти телефон: ");
            scanf("%s", &name);

            char tempName[] = " ";
            strcat(tempName, name); // ...................
            strcpy(name, tempName);

            phoneByName(file, name);
            break;

        case 4:
            char number[maximumSize] = { 0 };

            printf("Введите телефон, по которому хотите найти абонента: ");
            scanf("%s", &number);

            if (number[0] != '+')
            {
                char tempNumber[] = "+";

                strcat(tempNumber, number);
                strcpy(number, tempNumber);
            }

            nameByPhone(file, number);
            break;
        
        case 5:
            saveData(file, data, current);
            current = 0;
            break;

        case 6:
            printActions();
            break;

        default:
            printf("Такой команды нет :(\n");
            break;
        }
    }

    fclose(file);

    return 0;
}
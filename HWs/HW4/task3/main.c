#include <stdio.h>
#include <locale.h>

#define maximumSize 256

int printList(FILE *file, char amountRecord)
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
    printf("\n\n");

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

int main()
{
    setlocale(LC_ALL, "RU-ru");

    FILE *file = fopen("database.txt", "a+");

    if (file == NULL)
    {
        printf("Ошибка работы с файлом.\n");
        return 0;
    }

    char amountRecord = 0;
    char temp[maximumSize] = { 0 };

    while (!feof(file))
    {
        if (fgets(temp, maximumSize, file) != NULL)
        {
            ++amountRecord;
        }
    }
    fseek(file, 0, SEEK_SET);

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
        
        case 2:
            printList(file, amountRecord);
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
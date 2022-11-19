#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define maximumSize 255
#define entrySize 100

int printList(FILE *file, unsigned char amountEntry)
{
    if (amountEntry == 0)
    {
        printf("\nPhone book is empty.\n\n");
        return 1;
    }

    printf("\nPhone book:\n");
    char entry[maximumSize] = {0};
    for (int i = 0; i < amountEntry; ++i)
    {
        fgets(entry, maximumSize, file);
        printf("%d. %s", i + 1, entry);
    }
    fseek(file, 0, SEEK_SET);
    printf("\n");

    return 0;
}

void printActions(void)
{
    printf(" ------------------------------------\n");
    printf(" 0 — Exit\n");
    printf(" 1 — Add an entry (name and phone number)\n");
    printf(" 2 — Print all available entries\n");
    printf(" 3 — Find a phone by namen\n");
    printf(" 4 — Find a name by phone\n");
    printf(" 5 — Save current data to a file\n");
    printf(" 6 - View the list of commands\n");
    printf(" ------------------------------------\n");
}

unsigned char amountEntries(FILE *file)
{
    char amount = 0;
    char temp[maximumSize] = {0};

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

char *addEntry(char current)
{
    char *buffer = calloc(maximumSize, sizeof(char));
    printf("\nEnter the phone and number (For example: +79123456789 Alex):\n");
    getchar();
    fgets(buffer, entrySize, stdin);
    printf("Entry successfully added.\n\n");

    return buffer;
}

int saveData(FILE *file, char *data[], char lengthData)
{
    if (lengthData == 0)
    {
        printf("\nNo changes.\n\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    for (int i = 0; i < lengthData; ++i)
    {
        fputs(data[i], file);
        data[i] = 0;
    }
    fseek(file, 0, SEEK_SET);
    printf("\nChanges saved successfully!\n\n");

    return 0;
}

void nameByPhone(FILE *file, char number[])
{
    bool isFound = false;
    char currentNumber[maximumSize] = {0};
    char currentName[maximumSize] = {0};

    while (!feof(file) && !isFound)
    {
        fscanf(file, "%s", currentNumber);
        fscanf(file, "%s", currentName);
        if (!strcmp(currentNumber, number))
        {
            printf("\nNumber %s belongs to %s\n", currentNumber, currentName);
            isFound = true;
        }
    }
    fseek(file, 0, SEEK_SET);
    if (!isFound)
    {
        printf("\nThere is no such number in phone book.\n\n");
    }
}

void phoneByName(FILE *file, char name[])
{
    bool isFound = false;
    char currentNumber[maximumSize] = {0};
    char currentName[maximumSize] = {0};

    while (!feof(file) && !isFound)
    {
        fscanf(file, "%s", currentNumber);
        fscanf(file, "%s", currentName);
        if (!strcmp(currentName, name))
        {
            printf("\nSubscriber has %s number %s\n\n", name, currentNumber);
            isFound = true;
        }
    }
    fseek(file, 0, SEEK_SET);
    if (!isFound)
    {
        printf("\nThere is no such name in the phone book.\n\n");
    }
}

int main()
{
    FILE *file = fopen("database.txt", "a+");
    if (file == NULL)
    {
        printf("Error working with the file.\n");
        return 0;
    }

    char *data[entrySize] = {0};
    char current = 0;

    printf("Hi, this is a Phone Book!\nThat's what I can do:\n");
    printActions();

    int action = -1;
    bool isContinue = true;

    while (isContinue)
    {
        printf("Enter the command number: ");
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            printf("Good luck!\n");
            isContinue = false;
            break;

        case 1:
            data[current] = addEntry(current);
            ++current;
            break;

        case 2:
            unsigned char amount = amountEntries(file);
            printList(file, amount);
            break;

        case 3:
            char name[maximumSize] = {0};

            printf("Enter the name of the subscriber whose number to show: ");
            scanf("%s", name);
            phoneByName(file, name);
            break;

        case 4:
            char number[maximumSize] = {0};

            printf("Enter the phone whose name of the subscriber to show(For example: +102): ");
            scanf("%s", number);

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
            printf("There is no such command :(\n");
            break;
        }
    }

    fclose(file);
    return 0;
}
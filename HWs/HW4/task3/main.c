#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define maximumSize 256
#define entrySize 100

typedef struct
{
    char name[maximumSize];
    char phone[maximumSize];
} Person;

int printList(Person data[], unsigned char amountEntry)
{
    if (amountEntry == 0)
    {
        printf("\nPhone book is empty.\n\n");
        return 1;
    }

    printf("\nPhone book:\n");
    for (int i = 0; i < amountEntry; ++i)
    {
        printf("%d. %s   %s", i + 1, data[i].name, data[i].phone);
    }
    printf("\n");

    return 0;
}

void printActions()
{
    printf(" ------------------------------------\n");
    printf(" 0 — Exit\n");
    printf(" 1 — Add an entry (name and phone number)\n");
    printf(" 2 — Print all available entries\n");
    printf(" 3 — Find a phone by name\n");
    printf(" 4 — Find a name by phone\n");
    printf(" 5 — Save current data to a file\n");
    printf(" 6 - View the list of commands\n");
    printf(" ------------------------------------\n");
}

int saveData(char fileName[], Person data[], char lengthData)
{
    if (lengthData == 0)
    {
        return 1;
    }

    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        return 2;
    }

    for (int i = 0; i < lengthData - 1; ++i)
    {
        fputs(data[i].name, file);
        fputs(data[i].phone, file);
    }
    fputs(data[lengthData - 1].name, file);
    char buffer[maximumSize] = {0};
    strcpy(buffer, data[lengthData - 1].phone);
    buffer[strlen(buffer) - 1] = '\0';
    fputs(buffer, file);

    fclose(file);
    return 0;
}

void nameByPhone(Person data[], unsigned char amountEntry, char number[])
{
    bool isFound = false;
    int lengthNumber = strlen(number);

    for (int i = 0; i < amountEntry; ++i)
    {
        if (!strncmp(data[i].phone, number, lengthNumber))
        {
            printf("\nThis number belongs to %s\n", data[i].name);
            isFound = true;
            break;
        }
    }

    if (!isFound)
    {
        printf("\nThere is no such number in phone book.\n\n");
    }
}

void phoneByName(Person data[], unsigned char amountEntry, char name[])
{
    bool isFound = false;
    int lengthName = strlen(name);

    for (int i = 0; i < amountEntry; ++i)
    {
        if (!strncmp(data[i].name, name, lengthName))
        {
            printf("\nThis subscriber has number %s\n", data[i].phone);
            isFound = true;
            break;
        }
    }
    if (!isFound)
    {
        printf("\nThere is no such name in the phone book.\n\n");
    }
}

int main()
{
    char fileName[maximumSize] = "database.txt";
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error working with the file.\n");
        return -1;
    }

    Person data[entrySize] = {0};
    unsigned char current = 0;

    while (!feof(file))
    {
        fgets(data[current].name, maximumSize, file);
        fgets(data[current].phone, maximumSize, file);
        ++current;
    }
    strcat(data[current - 1].phone, "\n");
    fclose(file);

    printf("Hi, this is a Phone Book!\nThat's what I can do:\n");
    printActions();

    int action = -1;
    int result = 0;
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
            printf("\nEnter the name:\n");
            getchar();
            fgets(data[current].name, maximumSize, stdin);
            printf("\nEnter the phone:\n");
            fgets(data[current].phone, maximumSize, stdin);

            ++current;
            printf("Entry successfully added.\n\n");
            break;

        case 2:
            printList(data, current);
            break;

        case 3:
            char name[maximumSize] = {0};

            printf("Enter the name of the subscriber whose number to show: ");
            getchar();
            fgets(name, maximumSize, stdin);
            phoneByName(data, current, name);
            break;

        case 4:
            char number[maximumSize] = {0};

            printf("Enter the phone whose name of the subscriber to show(For example: +102): ");
            getchar();
            fgets(number, maximumSize, stdin);

            if (number[0] != '+')
            {
                char tempNumber[] = "+";
                strcat(tempNumber, number);
                strcpy(number, tempNumber);
            }

            nameByPhone(data, current, number);
            break;

        case 5:
            result = saveData(fileName, data, current);
            if (result == 1)
            {
                printf("\nNo changes.\n\n");
            }
            else if (result == 2)
            {
                printf("File opening error.\n");
            }
            else
            {
                printf("\nChanges saved successfully!\n\n");
            }
            break;

        case 6:
            printActions();
            break;

        default:
            printf("There is no such command :(\n");
            break;
        }
    }

    return 0;
}
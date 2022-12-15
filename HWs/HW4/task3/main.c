#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define maximumSize 256
#define entrySize 100

typedef struct
{
    char *name;
    char *phone;
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
        printf("%d. %s %s", i + 1, data[i].name, data[i].phone);
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
    char *buffer = (char *)malloc(maximumSize * sizeof(char));
    if (buffer == NULL)
    {
        return NULL;
    }

    getchar();
    fgets(buffer, entrySize, stdin);
    return buffer;
}

int saveData(FILE *file, char *data[], char lengthData)
{
    if (lengthData == 0)
    {
        return 1;
    }
    for (int i = 0; i < lengthData; ++i)
    {
        fputs(data[i], file);
        data[i] = 0;
    }
    fseek(file, 0, SEEK_SET);

    return 0;
}

void nameByPhone(Person data[], unsigned char amountEntry, char number[])
{
    bool isFound = false;

    for (int i = 0; i < amountEntry; ++i)
    {
        if (!strcmp(data[i].phone, number))
        {
            printf("\nNumber %s belongs to %s\n\n", data[i].phone, data[i].name);
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

    for (int i = 0; i < amountEntry; ++i)
    {
        if (!strcmp(data[i].name, name))
        {
            printf("\nSubscriber has %s number %s\n\n", data[i].name, data[i].phone);
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
    FILE *file = fopen("database.txt", "a+");
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
            data[current].name = addEntry(current);
            if (data[current].name == NULL)
            {
                printf("Memory allocation error.\n");
                isContinue = false;
                break;
            }
            printf("\nEnter the phone:\n");
            data[current].phone = addEntry(current);
            if (data[current].phone == NULL)
            {
                printf("Memory allocation error.\n");
                isContinue = false;
                break;
            }
            ++current;
            printf("Entry successfully added.\n\n");
            break;

        case 2:
            printList(data, current);
            break;

        case 3:
            char name[maximumSize] = {0};

            printf("Enter the name of the subscriber whose number to show: ");
            scanf("%s", name);
            phoneByName(data, current, name);
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

            nameByPhone(data, current, number);
            break;

            // case 5:
            //     result = saveData(file, data, current);
            //     if (result == 1)
            //     {
            //         printf("\nNo changes.\n\n");
            //     }
            //     else
            //     {
            //         printf("\nChanges saved successfully!\n\n");
            //     }
            //     current = 0;
            //     break;

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
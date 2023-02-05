#include <stdio.h>

int main()
{
    FILE *file = fopen("order.txt", "r");
    if (file == NULL)
    {
        printf("File opening error.\n");
        return 0;
    }

    char currentCharacter = 0;
    int totalSum = 0;
    int amountOfGoods = 0;
    int price = 0;
    int scanRes = 0;

    while (!feof(file))
    {
        while (currentCharacter != '\t' && !feof(file))
        {
            currentCharacter = fgetc(file);
            if (currentCharacter == '\n')
            {
                printf("Incorrect file structure.\n");
                fclose(file);
                return 0;
            }
        }
        if (feof(file))
        {
            break;
        }

        scanRes = fscanf(file, "%d", &amountOfGoods);
        if (scanRes == 0 || amountOfGoods <= 0)
        {
            printf("Incorrect file structure.\n");
            fclose(file);
            return 0;
        }

        scanRes = fscanf(file, "%d", &price);
        if (scanRes == 0 || price <= 0)
        {
            printf("Incorrect file structure.\n");
            fclose(file);
            return 0;
        }
        if ((currentCharacter = fgetc(file)) != '\n' && currentCharacter != EOF)
        {
            printf("Incorrect file structure.\n");
            fclose(file);
            return 0;
        }

        totalSum += amountOfGoods * price;
    }

    if (totalSum <= 0) // If the total is 0, then the file is either empty or does not contain \t
    {
        printf("Incorrect file structure.\n");
    }
    else
    {
        printf("Total order value: %d\n", totalSum);
    }
    fclose(file);
    return 0;
}
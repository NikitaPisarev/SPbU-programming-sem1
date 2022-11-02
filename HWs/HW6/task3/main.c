#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    FILE *file = fopen("data.txt", "r");
    if (file == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    char temp[256] = { 0 };
    while (!feof(file))
    {
        fscanf(file, "%s", temp);
        printf("%s", temp);
    }
    fclose(file);
    return 0;
}
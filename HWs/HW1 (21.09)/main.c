#include <stdio.h>
#include <stdbool.h>
    
void main()
{
    bool flagStop = false;

    while (!flagStop)
    {
        int numberTask = 0;
        int scan_res = 0;

        do
        {
            printf("Enter task number (from 1 to 8, 0 - exit): ");
            scan_res = scanf_s("%d", &numberTask);

            if (!scan_res)
            {
                printf("Incorrect input. Try again! \n");
                scanf_s("%*[^\n]");
            }
        } while (!scan_res);

        switch (numberTask)
        {
            case 0:
                flagStop = true;
                printf("Thanks!");
                break;

            case 1:
                task1();
                break;

            case 2:
                task2();
                break;

            case 3:
                task3();
                break;

            case 4:
                task4();
                break;

            case 5:
                task5();
                break;
  
            case 6:
                task6();
                break;

            case 7:
                task7();
                break;

            case 8:
                task8();
                break;

            default:
                printf("\nNumber not found\n\n");
        }
    }
}
#include "bubble.h"

#include <stdio.h>

int main()
{
    int choice;

    do
    {
        printf("\n=====================================\n");
        printf("   Bubble Sort Performance Analysis\n");
        printf("=====================================\n");
        printf("1. Generate Comparison Graph\n");
        printf("2. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                generateComparisonData();
                plotGraph();
                break;

            case 2:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 2);

    return 0;
}
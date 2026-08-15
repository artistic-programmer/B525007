#include <stdio.h>
#include "defective_coin.h"

int main()
{
    int choice;

    while (1)
    {
        printf("\n=====================================\n");
        printf("       Defective Coin Problem\n");
        printf("=====================================\n");
        printf("1. Generate Analysis Graph\n");
        printf("2. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            generateComparisonData();
            plotGraph();
        }
        else if (choice == 2)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include "utils.h"

int main()
{
    int choice;

    while (1)
    {
        clearScreen();

        printHeader();
        printGrowthTable();
        printMenu();

        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        if (choice == 14)
        {
            printf("\nThank You!\n");
            break;
        }

        switch (choice)
        {
            case 0:

                printf("\nGenerating combined graph...\n");

                generateCombinedData();
                plotCombinedGraph();

                break;

            case 13:

                printAbout();

                break;

            default:

                if (choice >= 1 && choice <= FUNCTION_COUNT)
                {
                    printf("\nGenerating graph for %s...\n",
                           functions[choice - 1].name);

                    generateSingleData(choice - 1);
                    plotSingleGraph();
                }
                else
                {
                    printf("\nInvalid Choice!\n");
                }
        }

        printf("\nPress Enter to continue...");
        getchar();      // consume newline left by scanf
        getchar();      // wait for Enter
    }

    return 0;
}
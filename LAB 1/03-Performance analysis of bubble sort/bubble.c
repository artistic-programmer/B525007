#include "bubble.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateRandomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
}

//-------------------------------------------------------------

long long traditionalBubbleSort(int arr[], int n)
{
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

//-------------------------------------------------------------

long long optimizedBubbleSort(int arr[], int n)
{
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }

    return comparisons;
}

//-------------------------------------------------------------

void generateComparisonData()
{
    FILE *fp = fopen("output/comparison.dat", "w");

    if (fp == NULL)
    {
        printf("Cannot create output file.\n");
        return;
    }

    srand((unsigned)time(NULL));

    fprintf(fp, "#Size Optimized Traditional\n");

    for (int n = START_SIZE; n <= END_SIZE; n += STEP_SIZE)
    {
        int original[n];
        int arr1[n];
        int arr2[n];

        generateRandomArray(original, n);

        memcpy(arr1, original, sizeof(original));
        memcpy(arr2, original, sizeof(original));

        long long optimized = optimizedBubbleSort(arr1, n);
        long long traditional = traditionalBubbleSort(arr2, n);

        fprintf(fp, "%d %lld %lld\n",
                n,
                optimized,
                traditional);
    }

    fclose(fp);

    printf("Comparison data generated successfully.\n");
}

//-------------------------------------------------------------

void plotGraph()
{
    system("gnuplot scripts/bubble.gnu");
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int low, int high, int x, long long *comparisons);
int ternarySearch(int arr[], int low, int high, int x, long long *comparisons);

int main()
{
    FILE *fp = fopen("output/comparison.dat", "w");

    if (fp == NULL)
    {
        printf("Could not create output file.\n");
        return 1;
    }

    fprintf(fp, "# n Binary Ternary\n");

    srand((unsigned)time(NULL));

    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < count; i++)
    {
        int n = sizes[i];

        int *arr = malloc(n * sizeof(int));

        if (arr == NULL)
        {
            printf("Memory allocation failed for n = %d\n", n);
            fclose(fp);
            return 1;
        }

        for (int j = 0; j < n; j++)
            arr[j] = j + 1;

        int x = rand() % n + 1;

        long long binaryComparisons = 0;
        long long ternaryComparisons = 0;

        binarySearch(
            arr,
            0,
            n - 1,
            x,
            &binaryComparisons
        );

        ternarySearch(
            arr,
            0,
            n - 1,
            x,
            &ternaryComparisons
        );

        fprintf(
            fp,
            "%d %lld %lld\n",
            n,
            binaryComparisons,
            ternaryComparisons
        );

        printf(
            "n = %-8d Binary = %-4lld Ternary = %-4lld\n",
            n,
            binaryComparisons,
            ternaryComparisons
        );

        free(arr);
    }

    fclose(fp);

    printf("\nComparison data generated successfully.\n");
    printf("Launching GNUPlot...\n");

    system("gnuplot scripts/complexity.gnu");

    return 0;
}
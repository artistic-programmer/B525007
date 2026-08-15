#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int min;
    int max;
} Result;

long long comparisons = 0;

Result findMinMax(int arr[], int low, int high)
{
    Result result;

    // One element
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];

        return result;
    }

    // Two elements
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    int mid = low + (high - low) / 2;

    Result left = findMinMax(arr, low, mid);
    Result right = findMinMax(arr, mid + 1, high);

    comparisons++;

    result.min = (left.min < right.min)
                     ? left.min
                     : right.min;

    comparisons++;

    result.max = (left.max > right.max)
                     ? left.max
                     : right.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid array size.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    Result result = findMinMax(arr, 0, n - 1);

    printf("\nMinimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);
    printf("Number of comparisons = %lld\n", comparisons);

    printf("\nTheoretical bound (3n/2) = %.1f\n",
           1.5 * n);

    if (comparisons <= 1.5 * n)
        printf("Result: Comparison bound is satisfied.\n");
    else
        printf("Result: Comparison bound is NOT satisfied.\n");

    free(arr);

    return 0;
}
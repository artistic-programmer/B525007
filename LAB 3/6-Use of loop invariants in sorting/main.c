#include <stdio.h>
#include <stdlib.h>

long long selectionSort(int arr[], int n)
{
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            comparisons++;

            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    return comparisons;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
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

    printf("\nOriginal Array:\n");
    printArray(arr, n);

    long long comparisons = selectionSort(arr, n);

    printf("\nSorted Array:\n");
    printArray(arr, n);

    long long theoretical = (long long)n * (n - 1) / 2;

    printf("\nNumber of comparisons = %lld\n", comparisons);
    printf("Theoretical comparisons = %lld\n", theoretical);

    if (comparisons == theoretical)
        printf("Validation: Theta(n^2) comparison bound verified.\n");
    else
        printf("Validation failed.\n");

    free(arr);

    return 0;
}
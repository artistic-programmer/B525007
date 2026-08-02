#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int hasDuplicate(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] == arr[i + 1])
            return 1;
    }

    return 0;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    if (hasDuplicate(arr, n))
        printf("\nDuplicate elements found.\n");
    else
        printf("\nAll elements are unique.\n");

    return 0;
}
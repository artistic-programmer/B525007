#include <stdio.h>

int findPartitionPoint(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] != arr[i])
        {
            return i + 1;   // First occurrence of 1
        }
    }

    if (arr[0] == 1)
        return 0;       // Array contains only 1's

    return -1;          // Array contains only 0's
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the array elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int partition = findPartitionPoint(arr, n);

    if (partition == -1)
        printf("Array contains only 0's.\n");
    else
        printf("Partition Point = %d\n", partition);

    return 0;
}
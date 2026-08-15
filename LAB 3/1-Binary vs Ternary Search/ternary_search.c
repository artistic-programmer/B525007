int ternarySearch(int arr[], int low, int high, int x, long long *comparisons)
{
    if (low > high)
        return -1;

    int third = (high - low) / 3;

    int mid1 = low + third;
    int mid2 = high - third;

    (*comparisons)++;

    if (arr[mid1] == x)
        return mid1;

    (*comparisons)++;

    if (arr[mid2] == x)
        return mid2;

    if (x < arr[mid1])
        return ternarySearch(arr, low, mid1 - 1, x, comparisons);

    if (x > arr[mid2])
        return ternarySearch(arr, mid2 + 1, high, x, comparisons);

    return ternarySearch(arr, mid1 + 1, mid2 - 1, x, comparisons);
}
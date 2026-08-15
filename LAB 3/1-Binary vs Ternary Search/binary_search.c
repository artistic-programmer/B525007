int binarySearch(int arr[], int low, int high, int x, long long *comparisons)
{
    if (low > high)
        return -1;

    int mid = low + (high - low) / 2;

    (*comparisons)++;

    if (arr[mid] == x)
        return mid;

    if (x < arr[mid])
        return binarySearch(arr, low, mid - 1, x, comparisons);

    return binarySearch(arr, mid + 1, high, x, comparisons);
}
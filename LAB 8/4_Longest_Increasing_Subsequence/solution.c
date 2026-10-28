#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_lis(const int arr[], int n, int **subseq_out, int *len_out) {
    if (n <= 0) {
        *subseq_out = NULL;
        *len_out = 0;
        return 0;
    }

    int *lis = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        lis[i] = 1;
        parent[i] = -1;
    }

    int max_len = 1;
    int best_end = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && lis[j] + 1 > lis[i]) {
                lis[i] = lis[j] + 1;
                parent[i] = j;
            }
        }
        if (lis[i] > max_len) {
            max_len = lis[i];
            best_end = i;
        }
    }

    int *subseq = (int *)malloc(max_len * sizeof(int));
    int curr = best_end;
    for (int i = max_len - 1; i >= 0; i--) {
        subseq[i] = arr[curr];
        curr = parent[curr];
    }

    *subseq_out = subseq;
    *len_out = max_len;

    free(lis);
    free(parent);
    return max_len;
}

int main(void) {
    int n;
    printf("Enter number of elements in array (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("\n");

    printf("Input Array: [ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : " ");
    }
    printf("]\n");
    printf("---------------------------------------------------------\n");

    int *subseq = NULL;
    int lis_length = 0;
    find_lis(arr, n, &subseq, &lis_length);

    printf("Length of Longest Increasing Subsequence : %d\n", lis_length);
    printf("Reconstructed LIS Subsequence            : [ ");
    for (int i = 0; i < lis_length; i++) {
        printf("%d%s", subseq[i], (i < lis_length - 1) ? ", " : " ");
    }
    printf("]\n\n");

    free(arr);
    if (subseq) free(subseq);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long find_msis(const int arr[], int n, int **subseq_out, int *len_out) {
    if (n <= 0) {
        *subseq_out = NULL;
        *len_out = 0;
        return 0;
    }

    long long *msis = (long long *)malloc(n * sizeof(long long));
    int *parent = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        msis[i] = arr[i];
        parent[i] = -1;
    }

    long long max_sum = msis[0];
    int best_end = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && msis[j] + arr[i] > msis[i]) {
                msis[i] = msis[j] + arr[i];
                parent[i] = j;
            }
        }
        if (msis[i] > max_sum) {
            max_sum = msis[i];
            best_end = i;
        }
    }

    // Count elements in the MSIS
    int count = 0;
    int curr = best_end;
    while (curr != -1) {
        count++;
        curr = parent[curr];
    }

    int *subseq = (int *)malloc(count * sizeof(int));
    curr = best_end;
    for (int i = count - 1; i >= 0; i--) {
        subseq[i] = arr[curr];
        curr = parent[curr];
    }

    *subseq_out = subseq;
    *len_out = count;

    free(msis);
    free(parent);
    return max_sum;
}

int main(void) {
    int n;
    printf("Enter number of positive integers (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d positive integers: ", n);
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
    int count = 0;
    long long max_sum = find_msis(arr, n, &subseq, &count);

    printf("Maximum Possible Sum of Increasing Subsequence : %lld\n", max_sum);
    printf("Reconstructed MSIS Elements                     : [ ");
    for (int i = 0; i < count; i++) {
        printf("%d%s", subseq[i], (i < count - 1) ? " + " : " ");
    }
    printf("= %lld ]\n\n", max_sum);

    free(arr);
    if (subseq) free(subseq);
    return 0;
}

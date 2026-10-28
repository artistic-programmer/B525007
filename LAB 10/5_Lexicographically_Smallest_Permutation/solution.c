#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int n;
} PermDSU;

PermDSU* create_perm_dsu(int n) {
    PermDSU *dsu = (PermDSU *)malloc(sizeof(PermDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc((n + 1) * sizeof(int));
    dsu->rank = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) dsu->parent[i] = i;
    return dsu;
}

int find_root(PermDSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    return dsu->parent[x] = find_root(dsu, dsu->parent[x]);
}

void union_nodes(PermDSU *dsu, int a, int b) {
    int ra = find_root(dsu, a);
    int rb = find_root(dsu, b);
    if (ra != rb) {
        if (dsu->rank[ra] < dsu->rank[rb]) {
            dsu->parent[ra] = rb;
        } else if (dsu->rank[ra] > dsu->rank[rb]) {
            dsu->parent[rb] = ra;
        } else {
            dsu->parent[rb] = ra;
            dsu->rank[ra]++;
        }
    }
}

int compare_ints(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int main(void) {
    int n, m;
    printf("Enter sequence length (N) and number of swap pairs (M): ");
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0) {
        fprintf(stderr, "Invalid input parameters!\n");
        return 1;
    }
    int *arr = (int *)malloc((n + 1) * sizeof(int));
    printf("Enter %d elements of the initial permutation:\n", n);
    for (int i = 1; i <= n; i++) {
        printf("  Element at index %d: ", i);
        if (scanf("%d", &arr[i]) != 1) return 1;
    }
    PermDSU *dsu = create_perm_dsu(n);
    printf("Enter %d allowed swap pairs (1-indexed 'u v'):\n", m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        printf("  Swap pair %d: ", i);
        if (scanf("%d %d", &u, &v) != 2 || u < 1 || u > n || v < 1 || v > n) return 1;
        union_nodes(dsu, u, v);
    }
    printf("\n--- Connected Components & Value Redistribution ---\n");
    int *idx_buf = (int *)malloc(n * sizeof(int));
    int *val_buf = (int *)malloc(n * sizeof(int));
    int *visited_root = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        int root = find_root(dsu, i);
        if (visited_root[root]) continue;
        visited_root[root] = 1;
        int count = 0;
        for (int j = 1; j <= n; j++) {
            if (find_root(dsu, j) == root) {
                idx_buf[count] = j;
                val_buf[count] = arr[j];
                count++;
            }
        }
        qsort(val_buf, count, sizeof(int), compare_ints);
        printf(" Component Root %d (Size %d):\n", root, count);
        printf("   Indices: ");
        for (int k = 0; k < count; k++) printf("%d ", idx_buf[k]);
        printf("\n   Sorted Values Placed: ");
        for (int k = 0; k < count; k++) {
            arr[idx_buf[k]] = val_buf[k];
            printf("%d ", val_buf[k]);
        }
        printf("\n");
    }
    printf("----------------------------------------------------\n");
    printf("Lexicographically Smallest Permutation Achievable:\n  [ ");
    for (int i = 1; i <= n; i++) printf("%d ", arr[i]);
    printf("]\n");
    free(arr); free(idx_buf); free(val_buf); free(visited_root);
    free(dsu->parent); free(dsu->rank); free(dsu);
    return 0;
}

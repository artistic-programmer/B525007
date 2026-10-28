#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int *size;
    long long *weight;
    int n;
} WeightedDSU;

WeightedDSU* create_weighted_dsu(int n, const long long *weights) {
    WeightedDSU *dsu = (WeightedDSU *)malloc(sizeof(WeightedDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc((n + 1) * sizeof(int));
    dsu->rank = (int *)calloc(n + 1, sizeof(int));
    dsu->size = (int *)malloc((n + 1) * sizeof(int));
    dsu->weight = (long long *)malloc((n + 1) * sizeof(long long));
    for (int i = 1; i <= n; i++) {
        dsu->parent[i] = i;
        dsu->size[i] = 1;
        dsu->weight[i] = weights[i];
    }
    return dsu;
}

int find_set(WeightedDSU *dsu, int v) {
    if (v == dsu->parent[v]) return v;
    return dsu->parent[v] = find_set(dsu, dsu->parent[v]);
}

int union_sets(WeightedDSU *dsu, int a, int b) {
    int root_a = find_set(dsu, a);
    int root_b = find_set(dsu, b);
    if (root_a == root_b) return 0;
    if (dsu->rank[root_a] < dsu->rank[root_b]) {
        int temp = root_a; root_a = root_b; root_b = temp;
    }
    dsu->parent[root_b] = root_a;
    dsu->size[root_a] += dsu->size[root_b];
    dsu->weight[root_a] += dsu->weight[root_b];
    if (dsu->rank[root_a] == dsu->rank[root_b]) dsu->rank[root_a]++;
    return 1;
}

long long get_max_weight_under_limit(WeightedDSU *dsu, int max_size) {
    long long max_w = 0;
    for (int i = 1; i <= dsu->n; i++) {
        if (dsu->parent[i] == i && dsu->size[i] <= max_size && dsu->weight[i] > max_w) {
            max_w = dsu->weight[i];
        }
    }
    return max_w;
}

void free_weighted_dsu(WeightedDSU *dsu) {
    free(dsu->parent); free(dsu->rank);
    free(dsu->size); free(dsu->weight);
    free(dsu);
}

int main(void) {
    int n, m, k;
    printf("Enter number of vertices (N), edges (M), and size limit (K): ");
    if (scanf("%d %d %d", &n, &m, &k) != 3 || n <= 0 || m < 0 || k <= 0) {
        fprintf(stderr, "Invalid input parameters!\n");
        return 1;
    }
    long long *weights = (long long *)malloc((n + 1) * sizeof(long long));
    printf("Enter weights for %d vertices (1-indexed):\n", n);
    for (int i = 1; i <= n; i++) {
        printf("  Weight of vertex %d: ", i);
        if (scanf("%lld", &weights[i]) != 1) return 1;
    }
    WeightedDSU *dsu = create_weighted_dsu(n, weights);
    long long initial_max = get_max_weight_under_limit(dsu, k);
    printf("\nInitial maximum component weight with size <= %d: %lld\n\n", k, initial_max);
    printf("--- Sequential Edge Additions & Max Weight Evaluation ---\n");
    printf(" Edge # | Added Edge (u, v) | Component Merged? | Max Weight (Size <= %d)\n", k);
    printf("--------+-------------------+-------------------+-------------------------\n");
    for (int i = 1; i <= m; i++) {
        int u, v;
        printf("  Edge %d (u v): ", i);
        if (scanf("%d %d", &u, &v) != 2 || u < 1 || u > n || v < 1 || v > n) {
            fprintf(stderr, "Invalid edge endpoints!\n");
            free(weights); free_weighted_dsu(dsu);
            return 1;
        }
        int merged = union_sets(dsu, u, v);
        long long current_max = get_max_weight_under_limit(dsu, k);
        printf("  #%4d |      (%2d, %2d)     |        %s        |        %8lld\n",
               i, u, v, merged ? "YES" : " NO", current_max);
    }
    printf("--------------------------------------------------------------------------\n");
    long long final_ans = get_max_weight_under_limit(dsu, k);
    printf("Final Maximum Component Weight (Size <= %d): %lld\n", k, final_ans);
    free(weights);
    free_weighted_dsu(dsu);
    return 0;
}

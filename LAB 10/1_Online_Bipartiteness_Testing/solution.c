#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *parent;
    int *rank;
    int *parity;
    int n;
} BipartiteDSU;

BipartiteDSU* create_dsu(int n) {
    BipartiteDSU *dsu = (BipartiteDSU *)malloc(sizeof(BipartiteDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc((n + 1) * sizeof(int));
    dsu->rank = (int *)calloc(n + 1, sizeof(int));
    dsu->parity = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) dsu->parent[i] = i;
    return dsu;
}

int find_root(BipartiteDSU *dsu, int x) {
    if (dsu->parent[x] != x) {
        int orig_parent = dsu->parent[x];
        dsu->parent[x] = find_root(dsu, dsu->parent[x]);
        dsu->parity[x] ^= dsu->parity[orig_parent];
    }
    return dsu->parent[x];
}

int add_edge(BipartiteDSU *dsu, int u, int v, int *is_new_edge) {
    int ru = find_root(dsu, u);
    int rv = find_root(dsu, v);
    if (ru == rv) {
        *is_new_edge = 0;
        if (dsu->parity[u] == dsu->parity[v]) return 0; // Odd-length cycle
        return 1; // Even-length cycle
    }
    *is_new_edge = 1;
    if (dsu->rank[ru] < dsu->rank[rv]) {
        int temp = ru; ru = rv; rv = temp;
        temp = u; u = v; v = temp;
    }
    dsu->parent[rv] = ru;
    dsu->parity[rv] = dsu->parity[u] ^ dsu->parity[v] ^ 1;
    if (dsu->rank[ru] == dsu->rank[rv]) dsu->rank[ru]++;
    return 1;
}

void free_dsu(BipartiteDSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu->parity);
    free(dsu);
}

int main(void) {
    int V, E;
    printf("Enter number of vertices (V) and incoming edges (E): ");
    if (scanf("%d %d", &V, &E) != 2 || V <= 0 || E < 0) {
        fprintf(stderr, "Invalid input for vertices or edges!\n");
        return 1;
    }
    BipartiteDSU *dsu = create_dsu(V);
    printf("Enter %d edges as 'u v' pairs (1-indexed):\n", E);
    int accepted_count = 0, rejected_count = 0;
    printf("\n--- Online Bipartiteness Edge Processing ---\n");
    printf(" Edge # |  Edge (u, v)  |     Status     | Action / Consequence\n");
    printf("--------+---------------+----------------+------------------------------------\n");
    for (int i = 1; i <= E; i++) {
        int u, v;
        printf("  Edge %d: ", i);
        if (scanf("%d %d", &u, &v) != 2 || u < 1 || u > V || v < 1 || v > V) {
            fprintf(stderr, "Invalid vertex index for edge %d!\n", i);
            free_dsu(dsu);
            return 1;
        }
        int is_new_edge = 0;
        int status = add_edge(dsu, u, v, &is_new_edge);
        if (status) {
            accepted_count++;
            const char *desc = is_new_edge ? "Components merged (bipartite)" : "Forms even cycle (bipartite)";
            printf("  #%4d | (%3d, %3d)    | ACCEPTED       | %s\n", i, u, v, desc);
        } else {
            rejected_count++;
            printf("  #%4d | (%3d, %3d)    | REJECTED       | Violates bipartiteness (odd cycle)!\n", i, u, v);
        }
    }
    printf("-----------------------------------------------------------------------------\n");
    printf("Edges Accepted: %d | Edges Rejected: %d\n\n", accepted_count, rejected_count);
    printf("Final Bipartite Vertex Coloring Partition:\n");
    for (int i = 1; i <= V; i++) {
        find_root(dsu, i);
        printf("  Vertex %d: Component Root = %d | Color Parity = %d\n", i, dsu->parent[i], dsu->parity[i]);
    }
    printf("\nGraph Status: Bipartiteness tracking completed.\n");
    free_dsu(dsu);
    return 0;
}

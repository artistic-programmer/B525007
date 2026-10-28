#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjNode {
    int to;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int *parent, *rank;
    long long *weight;
} OfflineDSU;

OfflineDSU* create_offline_dsu(int n) {
    OfflineDSU *dsu = (OfflineDSU *)malloc(sizeof(OfflineDSU));
    dsu->parent = (int *)malloc((n + 1) * sizeof(int));
    dsu->rank = (int *)calloc(n + 1, sizeof(int));
    dsu->weight = (long long *)calloc(n + 1, sizeof(long long));
    for (int i = 1; i <= n; i++) dsu->parent[i] = i;
    return dsu;
}

int find_root(OfflineDSU *dsu, int v) {
    if (v == dsu->parent[v]) return v;
    return dsu->parent[v] = find_root(dsu, dsu->parent[v]);
}

long long union_roots(OfflineDSU *dsu, int a, int b) {
    int ra = find_root(dsu, a), rb = find_root(dsu, b);
    if (ra == rb) return dsu->weight[ra];
    if (dsu->rank[ra] < dsu->rank[rb]) {
        int temp = ra; ra = rb; rb = temp;
    }
    dsu->parent[rb] = ra;
    dsu->weight[ra] += dsu->weight[rb];
    if (dsu->rank[ra] == dsu->rank[rb]) dsu->rank[ra]++;
    return dsu->weight[ra];
}

void add_edge(AdjNode **adj, int u, int v) {
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    node->to = v; node->next = adj[u]; adj[u] = node;
}

void free_graph(AdjNode **adj, int n) {
    for (int i = 1; i <= n; i++) {
        AdjNode *curr = adj[i];
        while (curr) {
            AdjNode *temp = curr; curr = curr->next; free(temp);
        }
    }
    free(adj);
}

int main(void) {
    int n, m;
    printf("Enter number of vertices (N) and edges (M): ");
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0) return 1;
    long long *a = (long long *)malloc((n + 1) * sizeof(long long));
    printf("Enter weights for %d vertices:\n", n);
    for (int i = 1; i <= n; i++) {
        printf("  Weight of vertex %d: ", i);
        if (scanf("%lld", &a[i]) != 1) return 1;
    }
    AdjNode **adj = (AdjNode **)calloc(n + 1, sizeof(AdjNode *));
    printf("Enter %d undirected edges (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        printf("  Edge %d: ", i + 1);
        if (scanf("%d %d", &u, &v) != 2) return 1;
        add_edge(adj, u, v); add_edge(adj, v, u);
    }
    int *order = (int *)malloc((n + 1) * sizeof(int));
    printf("Enter destruction sequence permutation of %d vertices:\n", n);
    for (int i = 1; i <= n; i++) {
        printf("  Step %d to destroy: ", i);
        if (scanf("%d", &order[i]) != 1) return 1;
    }
    OfflineDSU *dsu = create_offline_dsu(n);
    bool *active = (bool *)calloc(n + 1, sizeof(bool));
    long long *ans = (long long *)malloc((n + 1) * sizeof(long long));
    long long current_max = 0;
    for (int step = n; step >= 1; step--) {
        ans[step] = current_max;
        int u = order[step];
        active[u] = true;
        dsu->weight[u] = a[u];
        if (a[u] > current_max) current_max = a[u];
        for (AdjNode *edge = adj[u]; edge; edge = edge->next) {
            int v = edge->to;
            if (active[v]) {
                long long combined = union_roots(dsu, u, v);
                if (combined > current_max) current_max = combined;
            }
        }
    }
    printf("\n--- Offline Vertex Destruction Query Results ---\n");
    printf(" Step # | Destroyed Vertex | Max Remaining Component Weight\n");
    printf("--------+------------------+-------------------------------\n");
    for (int i = 1; i <= n; i++) {
        printf("  #%4d |        %4d      |           %12lld\n", i, order[i], ans[i]);
    }
    printf("-----------------------------------------------------------\n");
    printf("Final State: All vertices destroyed, max remaining weight = 0\n");
    free(a); free(order); free(active); free(ans);
    free(dsu->parent); free(dsu->rank); free(dsu->weight); free(dsu);
    free_graph(adj, n);
    return 0;
}

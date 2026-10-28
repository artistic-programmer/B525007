#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *parent;
    int *rank;
    int size;
} GridDSU;

GridDSU* create_grid_dsu(int size) {
    GridDSU *dsu = (GridDSU *)malloc(sizeof(GridDSU));
    dsu->size = size;
    dsu->parent = (int *)malloc(size * sizeof(int));
    dsu->rank = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) dsu->parent[i] = -1;
    return dsu;
}

int find_root(GridDSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    return dsu->parent[x] = find_root(dsu, dsu->parent[x]);
}

int union_cells(GridDSU *dsu, int x, int y) {
    int rx = find_root(dsu, x);
    int ry = find_root(dsu, y);
    if (rx == ry) return 0;
    if (dsu->rank[rx] < dsu->rank[ry]) {
        dsu->parent[rx] = ry;
    } else if (dsu->rank[rx] > dsu->rank[ry]) {
        dsu->parent[ry] = rx;
    } else {
        dsu->parent[ry] = rx;
        dsu->rank[rx]++;
    }
    return 1;
}

void free_grid_dsu(GridDSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

int main(void) {
    int R, C, K;
    printf("Enter grid dimensions (rows cols) and number of operations (K): ");
    if (scanf("%d %d %d", &R, &C, &K) != 3 || R <= 0 || C <= 0 || K < 0) {
        fprintf(stderr, "Invalid input parameters!\n");
        return 1;
    }
    int total_cells = R * C;
    GridDSU *dsu = create_grid_dsu(total_cells);
    int *grid = (int *)calloc(total_cells, sizeof(int));
    int island_count = 0;
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    printf("Enter %d land addition operations as 'row col' (0-indexed):\n", K);
    printf("\n--- Dynamic Island Count Tracking ---\n");
    printf(" Op # | Added Cell (r, c) | Island Count | Action Notes\n");
    printf("------+-------------------+--------------+---------------------------------------\n");
    for (int op = 1; op <= K; op++) {
        int r, c;
        printf("  Op %d: ", op);
        if (scanf("%d %d", &r, &c) != 2 || r < 0 || r >= R || c < 0 || c >= C) {
            fprintf(stderr, "Invalid cell coordinates (%d, %d)!\n", r, c);
            free(grid);
            free_grid_dsu(dsu);
            return 1;
        }
        int idx = r * C + c;
        if (grid[idx] == 1) {
            printf("  #%4d |    (%3d, %3d)    |     %4d     | Cell already land (count unchanged)\n",
                   op, r, c, island_count);
            continue;
        }
        grid[idx] = 1;
        dsu->parent[idx] = idx;
        island_count++;
        int merges = 0;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                int nidx = nr * C + nc;
                if (grid[nidx] == 1) {
                    if (union_cells(dsu, idx, nidx)) {
                        island_count--;
                        merges++;
                    }
                }
            }
        }
        const char *note = (merges == 0) ? "New isolated island formed" : "Connected with neighboring island(s)";
        printf("  #%4d |    (%3d, %3d)    |     %4d     | %s (%d merges)\n",
               op, r, c, island_count, note, merges);
    }
    printf("-----------------------------------------------------------------------------\n");
    printf("Final Dynamic Connected Components (Islands): %d\n", island_count);
    free(grid);
    free_grid_dsu(dsu);
    return 0;
}

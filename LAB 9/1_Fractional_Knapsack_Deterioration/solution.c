#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    double v;      // base value
    double w;      // weight
    double lambda; // decay rate
    double density;
    double priority;
} Item;

int compare_items(const void *a, const void *b) {
    const Item *i1 = (const Item *)a;
    const Item *i2 = (const Item *)b;
    if (i2->priority > i1->priority) return 1;
    if (i2->priority < i1->priority) return -1;
    return 0;
}

int main(void) {
    int n;
    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    Item *items = (Item *)malloc(n * sizeof(Item));
    printf("Enter value, weight, and decay rate (v w lambda) for each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("  Item #%d (v w lambda): ", i + 1);
        if (scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda) != 3 || items[i].w <= 0) {
            fprintf(stderr, "Invalid item parameters!\n");
            free(items);
            return 1;
        }
        items[i].density = items[i].v / items[i].w;
        // Optimal priority combining base density and decay sensitivity
        items[i].priority = items[i].density + items[i].lambda;
    }

    double W;
    printf("Enter knapsack capacity (W): ");
    if (scanf("%lf", &W) != 1 || W <= 0) {
        fprintf(stderr, "Invalid input for capacity W!\n");
        free(items);
        return 1;
    }
    printf("\n");

    // Sort items by priority descending
    qsort(items, n, sizeof(Item), compare_items);

    printf("Optimal Scheduling and Selection Order:\n");
    printf("  Rank | Item ID | Base Density | Decay Rate | Weight Taken | Fraction | Net Value\n");
    printf("  -----+---------+--------------+------------+--------------+----------+----------\n");

    double cur_time = 0.0;
    double rem_W = W;
    double total_realized_value = 0.0;

    for (int i = 0; i < n && rem_W > 1e-9; i++) {
        double taken_w = (rem_W < items[i].w) ? rem_W : items[i].w;
        double fraction = taken_w / items[i].w;

        double mid_t = cur_time + (taken_w / 2.0);
        double eff_density = items[i].density - (items[i].lambda * mid_t);
        if (eff_density < 0.0) eff_density = 0.0;

        double val = eff_density * taken_w;
        total_realized_value += val;

        printf("  %4d | Item #%2d | %12.2f | %10.2f | %12.2f | %7.1f%% | %9.2f\n",
               i + 1, items[i].id, items[i].density, items[i].lambda, taken_w, fraction * 100.0, val);

        cur_time += taken_w;
        rem_W -= taken_w;
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("Total Knapsack Capacity Used  : %.2f / %.2f\n", W - rem_W, W);
    printf("Total Elapsed Consumption Time: %.2f units\n", cur_time);
    printf("Maximum Total Value Collected : %.2f\n\n", total_realized_value);

    free(items);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int distance;
    int fuel;
} Station;

typedef struct {
    Station *data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* create_max_heap(int capacity) {
    MaxHeap *h = (MaxHeap *)malloc(sizeof(MaxHeap));
    h->data = (Station *)malloc(capacity * sizeof(Station));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap_stations(Station *a, Station *b) {
    Station temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(MaxHeap *h, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < h->size && h->data[left].fuel > h->data[largest].fuel)
        largest = left;

    if (right < h->size && h->data[right].fuel > h->data[largest].fuel)
        largest = right;

    if (largest != idx) {
        swap_stations(&h->data[largest], &h->data[idx]);
        max_heapify(h, largest);
    }
}

void push_heap(MaxHeap *h, Station s) {
    h->size++;
    int i = h->size - 1;
    while (i && s.fuel > h->data[(i - 1) / 2].fuel) {
        h->data[i] = h->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->data[i] = s;
}

Station pop_heap(MaxHeap *h) {
    Station top = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    max_heapify(h, 0);
    return top;
}

int compare_stations(const void *a, const void *b) {
    return ((const Station *)a)->distance - ((const Station *)b)->distance;
}

int main(void) {
    int D, F;
    printf("Enter target destination distance (D): ");
    if (scanf("%d", &D) != 1 || D <= 0) {
        fprintf(stderr, "Invalid target distance D!\n");
        return 1;
    }

    printf("Enter initial starting fuel (F): ");
    if (scanf("%d", &F) != 1 || F < 0) {
        fprintf(stderr, "Invalid initial fuel F!\n");
        return 1;
    }

    int n;
    printf("Enter number of refueling stations along the route (n): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid number of stations!\n");
        return 1;
    }

    Station *stations = (Station *)malloc(n * sizeof(Station));
    if (n > 0) {
        printf("Enter distance from origin and refuel amount (distance fuel) for each station:\n");
        for (int i = 0; i < n; i++) {
            stations[i].id = i + 1;
            printf("  Station #%d: ", i + 1);
            if (scanf("%d %d", &stations[i].distance, &stations[i].fuel) != 2 || stations[i].distance < 0 || stations[i].fuel <= 0) {
                fprintf(stderr, "Invalid station data!\n");
                free(stations);
                return 1;
            }
        }
    }
    printf("\n");

    // Sort stations by distance
    qsort(stations, n, sizeof(Station), compare_stations);

    MaxHeap *heap = create_max_heap(n + 1);
    Station *chosen = (Station *)malloc((n + 1) * sizeof(Station));
    int stops = 0;

    int cur_fuel = F;
    int idx = 0;
    bool reachable = true;

    while (cur_fuel < D) {
        // Enqueue all stations reachable with current fuel
        while (idx < n && stations[idx].distance <= cur_fuel) {
            push_heap(heap, stations[idx]);
            idx++;
        }

        if (heap->size == 0) {
            reachable = false;
            break;
        }

        Station best = pop_heap(heap);
        cur_fuel += best.fuel;
        chosen[stops++] = best;
    }

    printf("--- Minimum Refueling Stops Analysis ---\n");
    printf("Target Distance (D) : %d km\n", D);
    printf("Initial Fuel (F)    : %d L\n", F);
    printf("Available Stations  : %d\n", n);
    printf("---------------------------------------------------------\n");

    if (!reachable) {
        printf("Result: Target is UNREACHABLE! Ran out of fuel before reaching %d km. (Return -1)\n\n", D);
    } else {
        printf("Minimum Refueling Stops Required : %d stops\n", stops);
        printf("Refueling Station Stop Schedule:\n");
        for (int i = 0; i < stops; i++) {
            printf("  Stop #%d: Station #%d at %d km (+%d L fuel)\n",
                   i + 1, chosen[i].id, chosen[i].distance, chosen[i].fuel);
        }
        printf("Final Reachable Distance         : %d km\n\n", cur_fuel);
    }

    free(stations);
    free(chosen);
    free(heap->data);
    free(heap);
    return 0;
}

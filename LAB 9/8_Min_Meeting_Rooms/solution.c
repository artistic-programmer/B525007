#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int id;
} Meeting;

typedef struct {
    int time;
    int type; // +1 for start, -1 for end
    int meeting_id;
} Event;

int compare_events(const void *a, const void *b) {
    const Event *ea = (const Event *)a;
    const Event *eb = (const Event *)b;
    if (ea->time != eb->time) {
        return ea->time - eb->time;
    }
    // If times are identical, end event (-1) comes before start event (+1)
    return ea->type - eb->type;
}

int min_meeting_rooms(Meeting *meetings, int n) {
    Event *events = (Event *)malloc(sizeof(Event) * 2 * n);
    for (int i = 0; i < n; i++) {
        events[2 * i].time = meetings[i].start;
        events[2 * i].type = +1;
        events[2 * i].meeting_id = meetings[i].id;

        events[2 * i + 1].time = meetings[i].end;
        events[2 * i + 1].type = -1;
        events[2 * i + 1].meeting_id = meetings[i].id;
    }

    qsort(events, 2 * n, sizeof(Event), compare_events);

    int current_rooms = 0;
    int max_rooms = 0;

    printf("\n--- Chronological Sweep-Line Simulation ---\n");
    printf("%-8s | %-12s | %-10s | %-16s | %-12s\n",
           "Time", "Action", "Meeting", "Occupied Rooms", "Max Observed");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < 2 * n; i++) {
        current_rooms += events[i].type;
        if (current_rooms > max_rooms) {
            max_rooms = current_rooms;
        }

        const char *action_str = (events[i].type == +1) ? "Start (+1)" : "End   (-1)";
        printf("%-8d | %-12s | #%-9d | %-16d | %-12d\n",
               events[i].time, action_str, events[i].meeting_id, current_rooms, max_rooms);
    }

    free(events);
    return max_rooms;
}

int main(void) {
    int n;
    printf("Enter number of meetings: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Invalid number of meetings.\n");
        return 1;
    }

    Meeting *meetings = (Meeting *)malloc(sizeof(Meeting) * n);
    printf("Enter meeting intervals as 'start end' pairs:\n");
    for (int i = 0; i < n; i++) {
        meetings[i].id = i + 1;
        printf("  Meeting %d: ", i + 1);
        if (scanf("%d %d", &meetings[i].start, &meetings[i].end) != 2 ||
            meetings[i].start < 0 || meetings[i].end <= meetings[i].start) {
            printf("Error: Invalid interval for meeting %d.\n", i + 1);
            free(meetings);
            return 1;
        }
    }

    printf("\n--- Meeting Schedule ---\n");
    for (int i = 0; i < n; i++) {
        printf("  Meeting #%d: [%d, %d)\n", meetings[i].id, meetings[i].start, meetings[i].end);
    }

    int result = min_meeting_rooms(meetings, n);

    printf("\nMinimum Conference Rooms Required: %d\n", result);

    free(meetings);
    return 0;
}

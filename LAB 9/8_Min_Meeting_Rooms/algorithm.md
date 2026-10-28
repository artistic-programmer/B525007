# Question 8: Minimum Number of Meeting Rooms

## Problem Statement
Given an array of meeting time intervals where each interval consists of a start time and an end time $[s_i, e_i)$, determine the **minimum number of conference rooms** required so that no two overlapping meetings share a room.
A meeting ending at time $t$ frees up its room immediately for any new meeting beginning at time $t$ (half-open interval $[s_i, e_i)$).

---

## Greedy Sweep-Line / Chronological Event Algorithm

### 1. Conceptual Principle
The problem can be modeled as finding the maximum number of concurrent meetings at any single point in time. By the Helly property and interval graph coloring theorem, the chromatic number of an interval graph equals its clique number:
$$\chi(G) = \omega(G) = \max_{t} |\{i : s_i \le t < e_i\}|$$
Every meeting start corresponds to an incoming demand ($+1$ room), and every meeting end corresponds to a room release ($-1$ room). By placing all transition events on a timeline and sweeping chronologically, we track the instantaneous room occupancy.

### 2. Algorithmic Steps
1. For each interval $[s_i, e_i)$, generate two discrete timeline events:
   - $(s_i, +1)$ denoting meeting start.
   - $(e_i, -1)$ denoting meeting end.
2. Sort all $2N$ events in ascending order of time:
   - **Tie-breaking rule**: If an end event and a start event share the identical timestamp $t$, process the end event ($-1$) **before** the start event ($+1$) because the room is freed at the exact instant the next meeting starts.
3. Initialize `current_rooms = 0` and `max_rooms = 0`.
4. Sweep through the sorted events:
   - `current_rooms += event.delta`
   - `max_rooms = max(max_rooms, current_rooms)`
5. Return `max_rooms`.

---

## Pseudocode

```text
Algorithm MinMeetingRooms(intervals, N):
    Input: Array of N intervals [start, end]
    Output: Minimum rooms required

    events = empty list of size 2 * N
    idx = 0
    For each [s, e] in intervals:
        events[idx++] = (time: s, type: +1)
        events[idx++] = (time: e, type: -1)

    Sort events by:
        primary key: time ascending
        secondary key: type ascending (-1 before +1 on ties)

    current_rooms = 0
    max_rooms = 0

    For each event in events:
        current_rooms += event.type
        If current_rooms > max_rooms:
            max_rooms = current_rooms

    Return max_rooms
```

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(N \log N)$ | Creating $2N$ events takes $\mathcal{O}(N)$, and sorting them takes $\mathcal{O}(N \log N)$. Sweeping takes $\mathcal{O}(N)$. |
| **Auxiliary Space** | $\mathcal{O}(N)$ | Storage for $2N$ event records. |

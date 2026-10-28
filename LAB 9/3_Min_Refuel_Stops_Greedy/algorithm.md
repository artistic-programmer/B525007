# Question 3: Minimum Refueling Stops (Reverse Greedy Algorithm)

## Problem Statement
A vehicle needs to travel to a destination target distance $D$, starting at position 0 with initial fuel $F$. Along the route are $n$ gas stations represented as $(d_i, f_i)$, where $d_i$ is the distance from the starting point and $f_i$ is the liters of fuel available. 1 liter of fuel provides 1 unit of distance. Find the minimum number of refueling stops required to reach $D$. If the destination cannot be reached, return $-1$.

---

## Reverse Greedy (Lazy Refueling with Max-Heap)

### Conceptual Principle
1. As the vehicle travels forward, it drives as far as its currently available fuel allows.
2. Every time the vehicle passes a gas station $i$ ($d_i \le \text{fuel}$), it records the station's available fuel $f_i$ into a **Max-Heap** (priority queue) without actually stopping.
3. When the vehicle runs out of fuel before reaching the next station or destination $D$:
   - It retroactively chooses to have stopped at the past passed station offering the **maximum fuel** (hence "reverse greedy" / "lazy refueling").
   - Extract the maximum fuel from the Max-Heap, add it to current fuel, and increment stop count.
   - If the Max-Heap is empty and the target is still out of reach, the destination is fundamentally unreachable.

---

## Pseudocode

```text
Algorithm MinRefuelStops(D, F, stations, n):
    Input: Target D, initial fuel F, array of n stations (d_i, f_i)
    Output: Minimum stops or -1, plus list of chosen refuel stations

    Sort stations by distance d_i ascending
    Initialize MaxHeap H

    current_fuel = F
    stops = 0
    station_idx = 0
    refueled_stations = []

    While current_fuel < D:
        While station_idx < n and stations[station_idx].d <= current_fuel:
            H.insert(stations[station_idx])
            station_idx += 1

        If H is empty:
            Return -1 (Unreachable)

        best_station = H.extract_max()
        current_fuel += best_station.f
        stops += 1
        refueled_stations.append(best_station)

    Return stops, refueled_stations
```

---

## Correctness Proof
- **Exchange Argument**:
  At any point where additional fuel is needed to proceed, picking any past available station offering less fuel $f_{sub} < f_{max}$ yields strictly less reach. Replacing $f_{sub}$ with $f_{max}$ extends the vehicle's reach strictly further without consuming additional stops. Thus, greedily picking the maximal fuel among all reachable stations minimizes the total stop count.

---

## Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Sorting Stations** | $\mathcal{O}(n \log n)$ | Chronological distance order. |
| **Heap Operations** | $\mathcal{O}(n \log n)$ | Each station is inserted and extracted at most once from the Max-Heap. |
| **Overall Time Complexity** | **$\mathcal{O}(n \log n)$** | Optimal greedy runtime. |
| **Auxiliary Space** | **$\mathcal{O}(n)$** | Max-Heap and output tracking array. |

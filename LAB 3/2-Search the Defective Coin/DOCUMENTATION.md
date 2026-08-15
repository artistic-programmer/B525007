# Defective Coin

A C implementation of a divide-and-conquer algorithm to find a defective coin that is lighter than the other coins, or determine that all coins have the same weight.

## Method Used

The coins are divided into three groups. Two groups are weighed against each other using a simulated balance scale.

- If the left group is lighter, the defective coin is in the left group.
- If the right group is lighter, the defective coin is in the right group.
- If both groups have equal weight, the defective coin, if present, is in the remaining group.

The process is recursively repeated until the defective coin is identified or no defective coin exists.

## Complexity

Each step reduces the number of candidate coins to approximately one-third.

- **Time Complexity:** `O(log₃ n)`
- **Space Complexity:** `O(log n)` due to recursion

Since:

`log₃ n < log₂ n`

the required `log₂ n + c` bound is satisfied.

## Build

```bash
gcc main.c defective_coin.c -o defective_coin
```

## Run

### Windows

```bash
.\defective_coin.exe
```

### Linux/macOS

```bash
./defective_coin
```

## Validation

The program simulates the balance scale and counts the number of weighings required to identify the defective coin or determine that no defective coin exists.
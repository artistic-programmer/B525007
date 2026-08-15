#include "defective_coin.h"

#include <stdio.h>
#include <stdlib.h>

#define GOOD_WEIGHT 100
#define DEFECTIVE_WEIGHT 99

static int weigh(Coin coins[], int group1[], int n1,
                 int group2[], int n2, int *weighings)
{
    int weight1 = 0;
    int weight2 = 0;

    for (int i = 0; i < n1; i++)
        weight1 += coins[group1[i]].weight;

    for (int i = 0; i < n2; i++)
        weight2 += coins[group2[i]].weight;

    (*weighings)++;

    if (weight1 < weight2)
        return -1;

    if (weight1 > weight2)
        return 1;

    return 0;
}

int findDefective(Coin coins[], int n, int goodIndex, int *weighings)
{
    if (n == 1)
    {
        int candidate = coins[0].index;

        if (goodIndex == -1)
            return -1;

        int group1[1] = {0};
        int group2[1] = {goodIndex};

        int result = weigh(coins, group1, 1, group2, 1, weighings);

        if (result < 0)
            return candidate;

        return -1;
    }

    if (n == 2)
    {
        int group1[1] = {0};
        int group2[1] = {1};

        int result = weigh(coins, group1, 1, group2, 1, weighings);

        if (result < 0)
            return coins[0].index;

        if (result > 0)
            return coins[1].index;

        return -1;
    }

    int size = n / 3;

    int *groupA = malloc(size * sizeof(int));
    int *groupB = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        groupA[i] = i;
        groupB[i] = i + size;
    }

    int result = weigh(
        coins,
        groupA,
        size,
        groupB,
        size,
        weighings
    );

    int answer = -1;

    if (result < 0)
    {
        Coin *next = malloc(size * sizeof(Coin));

        for (int i = 0; i < size; i++)
            next[i] = coins[groupA[i]];

        answer = findDefective(
            next,
            size,
            groupB[0],
            weighings
        );

        free(next);
    }
    else if (result > 0)
    {
        Coin *next = malloc(size * sizeof(Coin));

        for (int i = 0; i < size; i++)
            next[i] = coins[groupB[i]];

        answer = findDefective(
            next,
            size,
            groupA[0],
            weighings
        );

        free(next);
    }
    else
    {
        int remaining = n - 2 * size;

        if (remaining == 0)
        {
            answer = -1;
        }
        else
        {
            Coin *next = malloc(remaining * sizeof(Coin));

            for (int i = 0; i < remaining; i++)
                next[i] = coins[2 * size + i];

            answer = findDefective(
                next,
                remaining,
                groupA[0],
                weighings
            );

            free(next);
        }
    }

    free(groupA);
    free(groupB);

    return answer;
}

void generateComparisonData(void)
{
    FILE *fp = fopen("output/comparison.dat", "w");

    if (fp == NULL)
    {
        printf("Could not create output file.\n");
        return;
    }

    fprintf(fp, "# n maximum_weighings\n");

    int sizes[] = {
        3,
        9,
        27,
        81,
        243,
        729,
        2187,
        6561
    };

    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < count; s++)
    {
        int n = sizes[s];
        int maxWeighings = 0;

        for (int defective = -1; defective < n; defective++)
        {
            Coin *coins = malloc(n * sizeof(Coin));

            for (int i = 0; i < n; i++)
            {
                coins[i].index = i;
                coins[i].weight = GOOD_WEIGHT;
            }

            if (defective != -1)
                coins[defective].weight = DEFECTIVE_WEIGHT;

            int weighings = 0;

            findDefective(
                coins,
                n,
                -1,
                &weighings
            );

            if (weighings > maxWeighings)
                maxWeighings = weighings;

            free(coins);
        }

        fprintf(fp, "%d %d\n", n, maxWeighings);

        printf(
            "n = %-6d Maximum weighings = %d\n",
            n,
            maxWeighings
        );
    }

    fclose(fp);

    printf("\nComparison data generated successfully.\n");
}

void plotGraph(void)
{
    system("gnuplot scripts/complexity.gnu");
}
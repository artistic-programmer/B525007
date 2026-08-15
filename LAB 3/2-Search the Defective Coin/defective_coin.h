#ifndef DEFECTIVE_COIN_H
#define DEFECTIVE_COIN_H

typedef struct
{
    int index;
    int weight;
} Coin;

int findDefective(Coin coins[], int n, int goodIndex, int *weighings);

void generateComparisonData(void);
void plotGraph(void);

#endif
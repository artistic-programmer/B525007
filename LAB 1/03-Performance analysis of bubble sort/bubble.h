#ifndef BUBBLE_H
#define BUBBLE_H

#define START_SIZE 10
#define END_SIZE 100
#define STEP_SIZE 10

void generateRandomArray(int arr[], int n);

long long optimizedBubbleSort(int arr[], int n);
long long traditionalBubbleSort(int arr[], int n);

void generateComparisonData();
void plotGraph();

#endif
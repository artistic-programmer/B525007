#include <stdio.h>
#include <stdlib.h>

unsigned long long move_count = 0;

/**
 * Recursive function to simulate Towers of Hanoi.
 */
void towers_of_hanoi(int n, char source, char destination, char auxiliary) {
    if (n == 1) {
        move_count++;
        return;
    }
    towers_of_hanoi(n - 1, source, auxiliary, destination);
    move_count++;
    towers_of_hanoi(n - 1, auxiliary, destination, source);
}

int main(void) {
    int max_disks = 20;
    FILE *data_file = fopen("toh_data.txt", "w");

    if (data_file == NULL) {
        printf("Error: Unable to open data file.\n");
        return 1;
    }

    printf("Simulating Towers of Hanoi...\n");
    for (int n = 1; n <= max_disks; n++) {
        move_count = 0;
        towers_of_hanoi(n, 'A', 'C', 'B');
        fprintf(data_file, "%d %llu\n", n, move_count);
    }
    fclose(data_file);

    // Launch Gnuplot with -persist so the window stays open on screen
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe != NULL) {
        // Set an interactive terminal (qt, x11, or wxt)
        fprintf(gnuplotPipe, "set terminal qt title 'Towers of Hanoi - Live Plot'\n");
        
        // Setup plot styles and labels
        fprintf(gnuplotPipe, "set title 'Towers of Hanoi: Disks vs Total Moves'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of Disks (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Total Moves (Log Scale)'\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set logscale y\n"); // Exponential growth visually linear on log scale
        
        // Plot data live
        fprintf(gnuplotPipe, "plot 'toh_data.txt' using 1:2 with linespoints title 'Moves (2^n - 1)' lw 2 pt 7 lc rgb 'blue'\n");
        
        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
        printf("Live Gnuplot window launched successfully!\n");
    } else {
        printf("Error: Could not start Gnuplot process.\n");
    }

    return 0;
}
# GNUplot script to visualize Merging k sorted arrays (Method 1 vs Method 2)

set terminal pngcairo size 1200,900 font "Sans,11" linewidth 2
set output "plots/merge_k_arrays_plots.png"

set multiplot layout 2,2 title "Merging k Sorted Arrays: Method 1 (Sequential) vs Method 2 (Divide & Conquer)" font "Sans-Bold,14"

# Color Palette
set style line 1 lc rgb '#E63946' lt 1 lw 2 pt 7 ps 1.2 # Method 1 Red
set style line 2 lc rgb '#1D3557' lt 1 lw 2 pt 9 ps 1.2 # Method 2 Dark Blue

# -------------------------------------------------------------
# Plot 1: Execution Time vs Number of Arrays (k) [Fixed n = 1000]
# -------------------------------------------------------------
set title "Execution Time vs. Number of Arrays (k) [Fixed n = 1000]" font "Sans-Bold,12"
set xlabel "Number of Arrays (k)"
set ylabel "Time (seconds)"
set grid
set key top left box
plot "data/benchmark_k.dat" using 1:3 with linespoints ls 1 title "Method 1: Sequential O(n·k^2)", \
     "data/benchmark_k.dat" using 1:5 with linespoints ls 2 title "Method 2: Pairwise O(n·k log k)"

# -------------------------------------------------------------
# Plot 2: Comparisons vs Number of Arrays (k) [Fixed n = 1000]
# -------------------------------------------------------------
set title "Comparisons vs. Number of Arrays (k) [Fixed n = 1000]" font "Sans-Bold,12"
set xlabel "Number of Arrays (k)"
set ylabel "Number of Comparisons"
set grid
set key top left box
set format y "%.0e"
plot "data/benchmark_k.dat" using 1:4 with linespoints ls 1 title "Method 1: Sequential", \
     "data/benchmark_k.dat" using 1:6 with linespoints ls 2 title "Method 2: Pairwise"

# -------------------------------------------------------------
# Plot 3: Execution Time vs Array Length (n) [Fixed k = 64]
# -------------------------------------------------------------
set title "Execution Time vs. Array Length (n) [Fixed k = 64]" font "Sans-Bold,12"
set xlabel "Array Length (n)"
set ylabel "Time (seconds)"
set grid
set format y "%g"
set key top left box
plot "data/benchmark_n.dat" using 2:3 with linespoints ls 1 title "Method 1: Sequential O(n·k^2)", \
     "data/benchmark_n.dat" using 2:5 with linespoints ls 2 title "Method 2: Pairwise O(n·k log k)"

# -------------------------------------------------------------
# Plot 4: Comparisons vs Array Length (n) [Fixed k = 64]
# -------------------------------------------------------------
set title "Comparisons vs. Array Length (n) [Fixed k = 64]" font "Sans-Bold,12"
set xlabel "Array Length (n)"
set ylabel "Number of Comparisons"
set grid
set format y "%.0e"
set key top left box
plot "data/benchmark_n.dat" using 2:4 with linespoints ls 1 title "Method 1: Sequential", \
     "data/benchmark_n.dat" using 2:6 with linespoints ls 2 title "Method 2: Pairwise"

unset multiplot

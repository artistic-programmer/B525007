# Gnuplot script for Merge Sort vs Modified 3-Way Merge Sort
set terminal pngcairo size 1280,800 enhanced font 'Segoe UI,11'
set output 'runtime_comparison.png'

set multiplot layout 2, 1 title "Merge Sort vs. Modified 3-Way Merge Sort Performance Analysis" font 'Segoe UI Bold,14'

# Styling
set grid linecolor rgb '#E0E0E0' lw 1
set key top left box font 'Segoe UI,10'
set format y '%.1f'
set format x '%.0s%c'

# Plot 1: Execution Time
set title 'Empirical Running Time (ms) vs. Input Size (n)' font 'Segoe UI Semibold,12'
set xlabel 'Input Size (n)'
set ylabel 'Time (milliseconds)'
plot 'benchmark_results.dat' using 1:2 with linespoints lw 2 pt 7 ps 1.2 lc rgb '#1f77b4' title 'Standard 2-Way Merge Sort (Empirical)', \
     'benchmark_results.dat' using 1:3 with linespoints lw 2 pt 9 ps 1.2 lc rgb '#d62728' title 'Modified 3-Way Merge Sort (Empirical)'

# Plot 2: Total Comparisons Count
set title 'Total Key Comparisons vs. Input Size (n)' font 'Segoe UI Semibold,12'
set xlabel 'Input Size (n)'
set ylabel 'Number of Comparisons'
set format y '%.1s%c'
plot 'benchmark_results.dat' using 1:4 with linespoints lw 2 pt 7 ps 1.2 lc rgb '#2ca02c' title 'Standard 2-Way (Empirical Comparisons)', \
     'benchmark_results.dat' using 1:5 with linespoints lw 2 pt 9 ps 1.2 lc rgb '#ff7f0e' title 'Modified 3-Way (Empirical Comparisons)', \
     'benchmark_results.dat' using 1:6 with lines dt 2 lw 2 lc rgb '#1b7837' title 'Theoretical 2-Way bound ~ n*log2(n)', \
     'benchmark_results.dat' using 1:7 with lines dt 2 lw 2 lc rgb '#b2182b' title 'Theoretical 3-Way bound ~ 2n*log3(n)'

unset multiplot

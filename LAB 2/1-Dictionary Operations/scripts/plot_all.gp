# GNUplot script to generate 7 PNG plots (one for each dictionary operation)
# Each PNG contains 6 plots/curves corresponding to the 6 data structures.

set datafile separator ","
set key top left box
set grid linecolor rgb "#cccccc" lw 1

# Define custom line styles for 6 data structures
set style line 1 lc rgb '#e41a1c' pt 7 ps 1.2 lw 2.5 # Unsorted Array (Red)
set style line 2 lc rgb '#377eb8' pt 5 ps 1.2 lw 2.5 # Sorted Array (Blue)
set style line 3 lc rgb '#4daf4a' pt 9 ps 1.2 lw 2.5 # Singly Unsorted (Green)
set style line 4 lc rgb '#984ea3' pt 11 ps 1.2 lw 2.5 # Singly Sorted (Purple)
set style line 5 lc rgb '#ff7f00' pt 13 ps 1.2 lw 2.5 # Doubly Unsorted (Orange)
set style line 6 lc rgb '#a65628' pt 15 ps 1.2 lw 2.5 # Doubly Sorted (Brown)

# -----------------------------------------------------------------------------
# 1. Search Operation Plot
# -----------------------------------------------------------------------------
set terminal pngcairo size 1000, 650 font "Sans,12" linewidth 2
set output "plots/search_performance.png"
set title "Dictionary Search Operation - Order of Growth (Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/search.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(n)]", \
     "data/search.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(log n)]", \
     "data/search.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(n)]", \
     "data/search.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(n)]", \
     "data/search.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(n)]", \
     "data/search.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(n)]"

# -----------------------------------------------------------------------------
# 2. Insert Operation Plot
# -----------------------------------------------------------------------------
set output "plots/insert_performance.png"
set title "Dictionary Insert Operation - Order of Growth (Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/insert.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(1)]", \
     "data/insert.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(n)]", \
     "data/insert.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(1)]", \
     "data/insert.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(n)]", \
     "data/insert.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(1)]", \
     "data/insert.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(n)]"

# -----------------------------------------------------------------------------
# 3. Delete Operation Plot
# -----------------------------------------------------------------------------
set output "plots/delete_performance.png"
set title "Dictionary Delete Operation - Order of Growth (Given Pointer, Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/delete.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(1)]", \
     "data/delete.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(n)]", \
     "data/delete.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(n)]", \
     "data/delete.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(n)]", \
     "data/delete.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(1)]", \
     "data/delete.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(1)]"

# -----------------------------------------------------------------------------
# 4. Minimum Operation Plot
# -----------------------------------------------------------------------------
set output "plots/min_performance.png"
set title "Dictionary Min Operation - Order of Growth (Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/min.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(n)]", \
     "data/min.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(1)]", \
     "data/min.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(n)]", \
     "data/min.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(1)]", \
     "data/min.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(n)]", \
     "data/min.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(1)]"

# -----------------------------------------------------------------------------
# 5. Maximum Operation Plot
# -----------------------------------------------------------------------------
set output "plots/max_performance.png"
set title "Dictionary Max Operation - Order of Growth (Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/max.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(n)]", \
     "data/max.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(1)]", \
     "data/max.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(n)]", \
     "data/max.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(1)]", \
     "data/max.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(n)]", \
     "data/max.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(1)]"

# -----------------------------------------------------------------------------
# 6. Predecessor Operation Plot
# -----------------------------------------------------------------------------
set output "plots/predecessor_performance.png"
set title "Dictionary Predecessor Operation - Order of Growth (Given Pointer, Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/predecessor.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(n)]", \
     "data/predecessor.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(1)]", \
     "data/predecessor.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(n)]", \
     "data/predecessor.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(n)]", \
     "data/predecessor.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(n)]", \
     "data/predecessor.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(1)]"

# -----------------------------------------------------------------------------
# 7. Successor Operation Plot
# -----------------------------------------------------------------------------
set output "plots/successor_performance.png"
set title "Dictionary Successor Operation - Order of Growth (Given Pointer, Worst-Case)" font "Sans-Bold,14"
set xlabel "Input Size (N)" font "Sans-Bold,12"
set ylabel "Execution Time (microseconds)" font "Sans-Bold,12"

plot "data/successor.csv" using 1:2 with linespoints ls 1 title "Unsorted Array [O(n)]", \
     "data/successor.csv" using 1:3 with linespoints ls 2 title "Sorted Array [O(1)]", \
     "data/successor.csv" using 1:4 with linespoints ls 3 title "Singly Unsorted List [O(n)]", \
     "data/successor.csv" using 1:5 with linespoints ls 4 title "Singly Sorted List [O(1)]", \
     "data/successor.csv" using 1:6 with linespoints ls 5 title "Doubly Unsorted List [O(n)]", \
     "data/successor.csv" using 1:7 with linespoints ls 6 title "Doubly Sorted List [O(1)]"

print "GNUplot: All 7 PNG plots generated successfully!"

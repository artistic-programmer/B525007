set terminal wxt size 1000,600

set title "Binary Search vs Ternary Search"
set xlabel "Array Size (n)"
set ylabel "Number of Comparisons"

set grid
set key top left

plot \
    "output/comparison.dat" using 1:2 with linespoints lw 2 pt 7 title "Binary Search", \
    "output/comparison.dat" using 1:3 with linespoints lw 2 pt 5 title "Ternary Search"

pause -1
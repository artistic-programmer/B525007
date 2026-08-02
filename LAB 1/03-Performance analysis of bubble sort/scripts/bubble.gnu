set terminal wxt enhanced size 1000,600

set title "Bubble Sort Performance Analysis"
set xlabel "Array Size (n)"
set ylabel "Number of Comparisons"

set grid
set key top left

plot \
"output/comparison.dat" using 1:2 with linespoints lw 2 pt 7 title "Optimized Bubble Sort", \
"output/comparison.dat" using 1:3 with linespoints lw 2 pt 5 title "Traditional Bubble Sort"

pause -1
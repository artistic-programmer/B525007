set terminal wxt size 1000,600

set title "Special Pattern Matrix Multiplication - O(n^2)"
set xlabel "Matrix Size (n)"
set ylabel "Operations"

set grid
set key top left

plot \
    "output/complexity.dat" using 1:2 with linespoints lw 2 pt 7 title "Actual Operations", \
    "output/complexity.dat" using 1:3 with linespoints lw 2 pt 5 title "n^2 Reference"

pause -1
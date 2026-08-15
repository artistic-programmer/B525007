set terminal wxt size 1000,600

set title "Defective Coin - Maximum Weighings"
set xlabel "Number of Coins (n)"
set ylabel "Number of Weighings"

set grid
set key top left

set logscale x

plot \
"output/comparison.dat" using 1:2 with linespoints lw 2 pt 7 \
title "Divide and Conquer"

pause -1
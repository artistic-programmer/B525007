reset

set title "Function Graph"
set xlabel "n"
set ylabel "f(n)"

set grid
set key off

set terminal wxt enhanced

plot \
"output/single.dat" using 1:2 with lines lw 3

pause -1
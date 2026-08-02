reset

set title "Comparison of Growth Functions"
set xlabel "n"
set ylabel "f(n)"

set grid
set key outside
set logscale y

set terminal wxt enhanced

plot \
"output/functions.dat" using 1:2 with lines lw 2 title "1/n", \
"output/functions.dat" using 1:3 with lines lw 2 title "log2(n)", \
"output/functions.dat" using 1:4 with lines lw 2 title "n^0.51", \
"output/functions.dat" using 1:5 with lines lw 2 title "12sqrt(n)", \
"output/functions.dat" using 1:6 with lines lw 2 title "50sqrt(n)", \
"output/functions.dat" using 1:7 with lines lw 2 title "nlog2(n)", \
"output/functions.dat" using 1:8 with lines lw 2 title "n^2-324", \
"output/functions.dat" using 1:9 with lines lw 2 title "100n^2+6n", \
"output/functions.dat" using 1:10 with lines lw 2 title "2n^3", \
"output/functions.dat" using 1:11 with lines lw 2 title "2^32*n", \
"output/functions.dat" using 1:12 with lines lw 2 title "n^(log2 n)", \
"output/functions.dat" using 1:13 with lines lw 2 title "3^n"

pause -1
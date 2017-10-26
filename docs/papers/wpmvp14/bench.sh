#!/bin/bash
cat > map_abs.dat << EOF
CPython 1530
Pythran 1.72
Pythran+AVX 0.587
EOF

cat > map_fun.dat << EOF
CPython 141
Pythran 1.72
Pythran+AVX 0.587
EOF

cat > sum.dat << EOF
CPython 277
Pythran 1.07
Pythran+AVX 0.416
EOF

cat > sum_square.dat << EOF
CPython 292
Pythran 1.09
Pythran+AVX 0.452
EOF

cat > numexpr.dat << EOF
CPython 7.48
Pythran 6.19
Pythran+AVX 4.05
EOF

cat > rosen.dat << EOF
CPython 13.9
Pythran 2.98
Pythran+AVX 1.15
EOF

cat > arc.dat << EOF
CPython 178
Pythran 146
Pythran+AVX 53.8
EOF

cat > euler06.dat << EOF
CPython 12
Pythran 0.34
Pythran+AVX 0.30
EOF

cat > rosen_fs.dat << EOF
CPython 14.6
Pythran 4.47
Pythran+AVX 3.07
Pythran+AVX+fs 2.88
EOF


function logplot {
gnuplot << EOF
set terminal pdf
set logscale y
set grid
set style histogram
set style data histogram
set output "$1.pdf"
set ylabel "Elapsed Time(s)"
set xtics rotate by -45
set style fill solid 1.00 border 0
set title "$2"
plot '$1.dat' using 2:xtic(1) ti ""
EOF
}
function plot {
gnuplot << EOF
set terminal pdf
#set logscale y
set grid
set style histogram
set style data histogram
set output "$1.pdf"
set ylabel "Elapsed Time(s)"
set xtics rotate by -45
set yrange [0:]
set style fill solid 1.00 border 0
set title "$2"
plot '$1.dat' using 2:xtic(1) ti ""
EOF
}

logplot map_abs 'mapping abs on a ndarray'
logplot map_fun 'mapping a linear function on a ndarray'
logplot sum 'taking the sum of the elements of an ndarray'
logplot sum_square 'taking the sum of the square of the elements of an ndarray'
plot numexpr 'ternary numpy expression'
plot rosen 'rosen function'
plot rosen_fs 'rosen function'
plot arc 'arc distances'
logplot euler06 'euler06 problem'

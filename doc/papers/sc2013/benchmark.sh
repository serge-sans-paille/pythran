#!/bin/bash
NBITER=1000000
NBREP=5
NBPROCS=8
CXX=g++ #clang++
CC=gcc
LIBOMP=gomp #iomp5

# select custom clang version with openMP support
export PATH=$HOME/tmp/llvm/bin/:$PATH
export LD_LIBRARY_PATH=$HOME/sources/libomp_oss/exports/lin_32e/lib
export CPLUS_INCLUDE_PATH=$HOME/sources/libomp_oss/exports/common/include

##############################
# PI
##############################

# cleanup
rm -f *.so pi

# python part
python -m timeit -n 1 -r $NBREP -s "import pi" "pi.pi($NBITER)" | sed -e 's/^.*: //' -e 's/ per loop//' -e 's/ msec/\/1000/' | bc -l > pi.python.seq
python ../../../scripts/pythran pi.py
python -m timeit -n 1 -r $NBREP -s "import pi" "pi.pi($NBITER)" | sed -e 's/^.*: //' -e 's/ per loop//' -e 's/ msec/\/1000/' -e 's/ usec/\/1000000/' -e 's/ sec//' | bc -l > pi.pythran.seq

python ../../../scripts/pythran pi.py -fopenmp 
for i in `seq 1 $NBPROCS` ; do
    echo -n "$i "
    OMP_NUM_THREADS=$i python -m timeit -n 1 -r $NBREP -s "import pi" "pi.pi($NBITER)" | sed -e 's/^.*: //' -e 's/ per loop//' -e 's/ msec/\/1000/' -e 's/ usec/\/1000000/' -e 's/ sec//' | bc -l
done > pi.pythran.omp

# c part
$CXX -l$LIBOMP pi.cc -o pi -O2
for i in `seq 1 $NBREP` ; do
    ./pi $NBITER
done | numbound -l > pi.c.seq

$CXX -fopenmp pi.cc -o pi -O2
for i in `seq 1 $NBPROCS` ; do
    echo -n "$i "
    for j in `seq 1 $NBREP` ; do
        OMP_NUM_THREADS=$i ./pi $NBITER
    done | numbound -l
done > pi.c.omp

#plotting
gnuplot << EOF
set terminal pdf
set output "pi_omp_bench.pdf"
set xlabel "Number of Active Threads"
set ylabel "Elapsed Time(s)"
set style line 1 lc rgb '#8b1a0e' pt 1 ps 1 lt 1 lw 2 # --- red
set style line 2 lc rgb '#5e9c36' pt 6 ps 1 lt 1 lw 2 # --- green
plot 'pi.c.omp' with linespoints ls 1 title "C + OpenMP" , 'pi.pythran.omp' with linespoints ls 2 title "Pythran + OpenMP"
EOF


#############################
 Hyantes
#############################

m -f *.so hyantes
# python part
# tooo looong
#python -m timeit -n 1 -r $NBREP -s "import hyantes" "hyantes.run()" | sed -e 's/^.*: //' -e 's/ per loop//' -e 's/ msec/\/1000/' | bc -l > hyantes.python.seq
echo "56000" > hyantes.python.seq
python ../../../scripts/pythran hyantes_core.py
python -m timeit -n 1 -r $NBREP -s "import hyantes" "hyantes.run()" | sed -e 's/^.*: //' -e 's/ per loop//' -e 's/ msec/\/1000/' -e 's/ usec/\/1000000/' -e 's/ sec//' | bc -l > pythran.pythran.seq

python ../../../scripts/pythran hyantes_core.py -fopenmp 
for i in `seq 1 $NBPROCS` ; do
    echo -n "$i "
    OMP_NUM_THREADS=$i python -m timeit -n 1 -r $NBREP -s "import hyantes" "hyantes.run()" | sed -e 's/^.*: //' -e 's/ per loop//' -e 's/ msec/\/1000/' -e 's/ usec/\/1000000/' -e 's/ sec//' | bc -l
done > hyantes.pythran.omp

# c part
$CC -std=c99 -l$LIBOMP -lm hyantes.c -o hyantes -Ofast
for i in `seq 1 $NBREP` ; do
    ./hyantes Rhone-alpesXYLongLat_pop.txt 1.1 32 4 35 0.01 40
done | numbound -l > hyantes.c.seq

$CC -std=c99 -fopenmp -lm hyantes.c -o hyantes -Ofast
for i in `seq 1 $NBPROCS` ; do
    echo -n "$i "
    for j in `seq 1 $NBREP` ; do
        OMP_NUM_THREADS=$i ./hyantes Rhone-alpesXYLongLat_pop.txt 1.1 32 4 35 0.01 40
    done | numbound -l
done > hyantes.c.omp

#plotting
gnuplot << EOF
set terminal pdf
set output "hyantes_omp_bench.pdf"
set xlabel "Number of Active Threads"
set ylabel "Elapsed Time(s)"
set style line 1 lc rgb '#8b1a0e' pt 1 ps 1 lt 1 lw 2 # --- red
set style line 2 lc rgb '#5e9c36' pt 6 ps 1 lt 1 lw 2 # --- green
plot 'hyantes.c.omp' with linespoints ls 1 title "C + OpenMP" , 'hyantes.pythran.omp' with linespoints ls 2 title "Pythran + OpenMP"
EOF


##############################
# python benchmarks
##############################

function plot {
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
plot '$1.dat' using 2:xtic(1) ti ""
EOF
}

plot growcut
plot julia
plot pairwise
plot rosen_der

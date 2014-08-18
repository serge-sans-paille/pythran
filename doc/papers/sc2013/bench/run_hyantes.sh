#!/bin/sh
for i in `seq 1 8` ; do
    OMP_NUM_THREADS=$i python run_hyantes.py
done

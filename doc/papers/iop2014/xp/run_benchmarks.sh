#!/bin/sh
set -e

#CXX=~/sources/llvm/_build/install/bin/clang++
CXX=g++
CXXFLAGS=-O3
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..

# first clean all
find -name '*.pyc' -o -name '*.so' -o -name '*.c' -o -name '*.cpp' | xargs rm -f || true

# then build all cython stuff
for target in cython/*.pyx
do
    cython --cplus $target -o ${target%.pyx}.cpp
    $CXX $CXXFLAGS `python-config --cflags --libs` -shared ${target%.pyx}.cpp -fPIC -o ${target%.pyx}.so
done

# then build all pythran stuff
for target in pythran/*.py
do
    pythran $CXXFLAGS $target -I../../../../build/lib.linux-x86_64-2.7/pythran -o ${target%.py}.so
done

# then run tests

echo "==== arc distance ===="

SETUP='import numpy as np; N=1000000 ; a,b,c,d = np.random.random(N), np.random.random(N), np.random.random(N), np.random.random(N) ; from arc_distance import arc_distance'
RUN='arc_distance(a,b,c,d)'

printf "python " ;  PYTHONPATH=./python python -m timeit -s "$SETUP" "$RUN"
printf "cython " ;  PYTHONPATH=./cython python -m timeit -s "$SETUP" "$RUN"
printf "pythran " ; PYTHONPATH=./pythran python -m timeit -s "$SETUP" "$RUN"
printf "pypy " ;    PYTHONPATH=./pypy pypy -m timeit -s "from random import random ; import numpypy as np; N=1000000 ; a,b,c,d = np.array([random() for _ in range(N)]), np.array([random() for _ in range(N)]), np.array([random() for _ in range(N)]), np.array([random() for _ in range(N)]) ; from arc_distance import arc_distance" "$RUN"

echo "==== blacksholes ===="

SETUP='N=1000 ; from random import random ; a,b,c,d,e,f = [random() for _ in range(1,N)], [random() for _ in range(1,N)], [random() for _ in range(1,N)], 0.5, 0.76, 200 ; from blacksholes import BlackScholes'
RUN='BlackScholes(a,b,c,d,e,f)'

printf "python " ;  PYTHONPATH=./python python -m timeit -s "$SETUP" "$RUN"
printf "cython " ;  PYTHONPATH=./cython python -m timeit -s "$SETUP" "$RUN"
printf "pythran " ; PYTHONPATH=./pythran python -m timeit -s "$SETUP" "$RUN"
printf "pypy " ;    PYTHONPATH=./pypy pypy -m timeit -s "$SETUP" "$RUN"

echo "==== growcut ===="

SETUP='N=20 ; import numpy as np ; image = np.zeros((N, N, 3)) ; state = np.zeros((N, N, 2)) ; state_next = np.empty((N, N, 2)) ; state[0, 0, 0] = 1 ; state[0, 0, 1] = 1 ; from growcut import growcut'
RUN='growcut(image, state, state_next, 10)'

printf "python " ;  PYTHONPATH=./python python -m timeit -s "$SETUP" "$RUN"
printf "cython " ;  PYTHONPATH=./cython python -m timeit -s "$SETUP" "$RUN"
printf "pythran " ; PYTHONPATH=./pythran python -m timeit -s "$SETUP" "$RUN"
printf "pypy " ;    PYTHONPATH=./pypy pypy -m timeit -s "import numpypy ; $SETUP" "$RUN"

echo "==== n queens ===="

SETUP='N=8 ; from nqueens import n_queens'
RUN='n_queens(N)'

printf "python " ;  PYTHONPATH=./python python -m timeit -s "$SETUP" "$RUN"
printf "cython " ;  PYTHONPATH=./cython python -m timeit -s "$SETUP" "$RUN"
printf "pythran " ; PYTHONPATH=./pythran python -m timeit -s "$SETUP" "$RUN"
printf "pypy " ;    PYTHONPATH=./pypy pypy -m timeit -s "$SETUP" "$RUN"

echo "==== rosen_der ===="

SETUP='N=1000000 ; import numpy as np ; r =np.random.random(N) ; from rosen_der import rosen_der'
RUN='rosen_der(r)'

printf "python " ;  PYTHONPATH=./python python -m timeit -s "$SETUP" "$RUN"
printf "cython " ;  PYTHONPATH=./cython python -m timeit -s "$SETUP" "$RUN"
printf "pythran " ; PYTHONPATH=./pythran python -m timeit -s "$SETUP" "$RUN"
printf "pypy " ;    PYTHONPATH=./pypy pypy -m timeit -s "from random import random ; import numpypy as np; N=1000000 ; r = np.array([random() for _ in range(N)]); from rosen_der import rosen_der" "$RUN"


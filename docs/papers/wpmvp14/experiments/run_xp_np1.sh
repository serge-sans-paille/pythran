rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
python -m timeit -s 'from np1 import np1 as s ; import numpy as np ; a = np.random.rand(1000000)' 's(a)'
pythran -O2 np1.py
python -m timeit -s 'from np1 import np1 as s ;  import numpy as np ; a = np.random.rand(1000000)' 's(a)'
pythran -O2 -DUSE_BOOST_SIMD -march=native np1.py
python -m timeit -s 'from np1 import np1 as s ;  import numpy as np ; a = np.random.rand(1000000)' 's(a)'

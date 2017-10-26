rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
python -m timeit -s 'from np0 import np0 as s ; import numpy as np ; a = np.random.rand(1000000)' 's(a)'
pythran -O2 np0.py
python -m timeit -s 'from np0 import np0 as s ;  import numpy as np ; a = np.random.rand(1000000)' 's(a)'
pythran -O2 -DUSE_BOOST_SIMD -march=native np0.py
python -m timeit -s 'from np0 import np0 as s ;  import numpy as np ; a = np.random.rand(1000000)' 's(a)'

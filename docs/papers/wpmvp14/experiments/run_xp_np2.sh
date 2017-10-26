rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
python -m timeit -s 'from np2 import np2 as s ; import numpy as np ; a = np.random.rand(1000000); b = np.random.rand(len(a)); c = np.random.rand(1000000); d = np.random.rand(len(a))' 's(a,b,c,d)'
pythran -O2 np2.py
python -m timeit -s 'from np2 import np2 as s ; import numpy as np ; a = np.random.rand(1000000); b = np.random.rand(len(a)); c = np.random.rand(1000000); d = np.random.rand(len(a))' 's(a,b,c,d)'
pythran -O2 -DUSE_BOOST_SIMD -march=native np2.py
python -m timeit -s 'from np2 import np2 as s ; import numpy as np ; a = np.random.rand(1000000); b = np.random.rand(len(a)); c = np.random.rand(1000000); d = np.random.rand(len(a))' 's(a,b,c,d)'

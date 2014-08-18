rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vsum/sum/' sum0.py > ssum0.py
python -m timeit -s 'from ssum0 import sum0 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
rm -f ssum0.py
pythran -O2 sum0.py
python -m timeit -s 'from sum0 import sum0 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
pythran -O2 -DUSE_BOOST_SIMD -march=native sum0.py
python -m timeit -s 'from sum0 import sum0 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'

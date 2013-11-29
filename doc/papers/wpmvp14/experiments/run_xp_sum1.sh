rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vsum/sum/' sum1.py > ssum1.py
python -m timeit -s 'from ssum1 import sum1 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
rm -f ssum1.py
pythran -O2 sum1.py
python -m timeit -s 'from sum1 import sum1 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
pythran -O2 -DUSE_BOOST_SIMD -march=native sum1.py
python -m timeit -s 'from sum1 import sum1 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'

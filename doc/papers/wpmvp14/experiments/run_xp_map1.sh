rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vmap/map/' map1.py > smap1.py
python -m timeit -s 'from smap1 import map1 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
rm -f smap1.py
pythran -O2 map1.py
python -m timeit -s 'from map1 import map1 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
pythran -O2 -DUSE_BOOST_SIMD -march=native map1.py
python -m timeit -s 'from map1 import map1 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'

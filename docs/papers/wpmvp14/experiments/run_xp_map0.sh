rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vmap/map/' map0.py > smap0.py
python -m timeit -s 'from smap0 import map0 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
rm -f smap0.py
pythran -O2 map0.py
python -m timeit -s 'from map0 import map0 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'
pythran -O2 -DUSE_BOOST_SIMD -march=native map0.py
python -m timeit -s 'from map0 import map0 as s; import numpy as np ; r = np.random.rand(1000000)' 's(r)'

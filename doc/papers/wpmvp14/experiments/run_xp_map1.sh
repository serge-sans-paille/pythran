rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vmap/map/' map1.py > smap1.py
python -m timeit -s 'from smap1 import map1 as s' 's(1000000)'
rm -f smap1.py
pythran -Ofast map1.py
python -m timeit -s 'from map1 import map1 as s' 's(1000000)'
pythran -Ofast -DUSE_BOOST_SIMD -march=native map1.py
python -m timeit -s 'from map1 import map1 as s ' 's(1000000)'

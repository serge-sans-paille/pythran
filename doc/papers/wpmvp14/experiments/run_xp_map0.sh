rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vmap/map/' map0.py > smap0.py
python -m timeit -s 'from smap0 import map0 as s' 's(1000000)'
rm -f smap0.py
pythran -Ofast map0.py
python -m timeit -s 'from map0 import map0 as s' 's(1000000)'
pythran -Ofast -DUSE_BOOST_SIMD -march=native map0.py
python -m timeit -s 'from map0 import map0 as s ' 's(1000000)'

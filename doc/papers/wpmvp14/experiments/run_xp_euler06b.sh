rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed -e 's/vmap/map/' -e 's/vsum/sum/' euler06b.py > seuler06b.py
python -m timeit -s 'import seuler06b as e; s = e.solve' 's(100001)'
rm seuler06b.py
pythran -O3 -march=native euler06b.py
python -m timeit -s 'import euler06b as e; s = e.solve' 's(100001)'
pythran -O3 -march=native -DUSE_BOOST_SIMD euler06b.py
python -m timeit -s 'import euler06b as e; s = e.solve' 's(100001)'


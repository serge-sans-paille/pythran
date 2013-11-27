rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
sed 's/vsum/sum/' sum0.py > ssum0.py
python -m timeit -s 'from ssum0 import sum0 as s' 's(1000000)'
rm -f ssum0.py
pythran -Ofast sum0.py
python -m timeit -s 'from sum0 import sum0 as s' 's(1000000)'
pythran -Ofast -DUSE_BOOST_SIMD -march=native sum0.py
python -m timeit -s 'from sum0 import sum0 as s ' 's(1000000)'

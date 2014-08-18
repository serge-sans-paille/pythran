rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
python -m timeit -s 'import euler06 as e; s = e.solve' 's(100001)'
cc -shared -O3 -std=c99 euler06.c -o libeuler06.so
python -m timeit -s "from ctypes import cdll ; d = cdll.LoadLibrary('./libeuler06.so') ; s = d.solve" "s(100001)"
cc -shared -O3 -std=c99 -march=native euler06.c -o libeuler06.so
python -m timeit -s "from ctypes import cdll ; d = cdll.LoadLibrary('./libeuler06.so') ; s = d.solve" "s(100001)"
pythran -O3 -march=native euler06.py
python -m timeit -s 'import euler06 as e; s = e.solve' 's(100001)'


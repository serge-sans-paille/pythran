rm *.so
export PATH=../../../../scripts:$PATH
export PYTHONPATH=../../../..
python -m timeit -s 'from rosen_fs import rosen; import numpy as np ; r = np.random.rand(1000000)' 'rosen(r)'
pythran -O2 rosen_fs.py
python -m timeit -s 'from rosen_fs import rosen; import numpy as np ; r = np.random.rand(1000000)' 'rosen(r)'
rm -r no_lazy
mkdir no_lazy
cd no_lazy
git clone git@github.com:serge-sans-paille/pythran.git .
git checkout 22596f0f2936cc1cb5e83a07feee244c5530ef68
PYTHONPATH=. ./scripts/pythran -O2 -DUSE_BOOST_SIMD -march=native ../rosen_fs.py
python -m timeit -s 'from rosen_fs import rosen; import numpy as np ; r = np.random.rand(1000000)' 'rosen(r)'
cd ..
pythran -O2 -DUSE_BOOST_SIMD -march=native rosen_fs.py
python -m timeit -s 'from rosen_fs import rosen; import numpy as np ; r = np.random.rand(1000000)' 'rosen(r)'

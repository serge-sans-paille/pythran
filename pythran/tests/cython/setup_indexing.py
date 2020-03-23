from distutils.core import setup
from Cython.Build import cythonize

setup(
    name = "indexing",
    ext_modules = cythonize('indexing.pyx'),
    script_name = 'setup.py',
    script_args = ['build_ext', '--inplace']
)
import indexing
import numpy as np
print(indexing.indexing())


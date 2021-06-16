from distutils.core import setup
from Cython.Build import cythonize
import os

setup(
    name = "add",
    ext_modules = cythonize('add.pyx'),
    script_name = 'setup.py',
    script_args = ['build_ext', '--inplace']
)
import add
import numpy as np
print(add.add(np.ones((3,3)), np.ones((3,3))))


from distutils.core import setup
from Cython.Build import cythonize

setup(
    name = "tax",
    ext_modules = cythonize('tax.pyx'),
    script_name = 'setup.py',
    script_args = ['build_ext', '--inplace']
)
import tax
import numpy as np
print(tax.tax(np.ones(10)))



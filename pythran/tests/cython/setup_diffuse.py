from distutils.core import setup
from Cython.Build import cythonize

setup(
    name = "diffuse",
    ext_modules = cythonize('diffuse.pyx'),
    script_name = 'setup.py',
    script_args = ['build_ext', '--inplace']
)

import diffuse
diffuse.test()

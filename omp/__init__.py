'''
OpenMP wrapper using a (user provided) libgomp dynamically loaded library
'''

import os
import sys
import glob
from ctypes.util import find_library
import ctypes


class omp(object):
    LD_LIBRARY_PATHS = os.environ.get('LD_LIBRARY_PATH', '').split(':') + [
        "/usr/lib/x86_64-linux-gnu/",
        # MacPorts install gcc in a "non standard" path on OSX
    ] + glob.glob("/opt/local/lib/gcc*/")

    def __init__(self):
        # Paths are "non-standard" place to lookup
        paths = omp.LD_LIBRARY_PATHS

        # Try to load find libgomp shared library using loader search dirs
        libgomp_path = find_library("gomp")

        # Try to use custom paths if lookup failed
        for path in paths:
            if libgomp_path:
                break
            path = path.strip()
            if not os.path.isdir(path):
                continue
            libgomp_path = find_library(os.path.join(path, "libgomp"))

        if not libgomp_path:
            raise EnvironmentError("I can't find a shared library for libgomp,"
                                   " you may need to install it or adjust the "
                                   "LD_LIBRARY_PATH environment variable.")
        else:
            # Load the library (shouldn't fail with an absolute path right?)
            self.libomp = ctypes.CDLL(libgomp_path)

    def __getattribute__(self, name):
        if name == 'libomp':
            return object.__getattribute__(self, 'libomp')
        else:
            return getattr(self.libomp, 'omp_' + name)

# see http://mail.python.org/pipermail/python-ideas/2012-May/014969.html
sys.modules[__name__] = omp()

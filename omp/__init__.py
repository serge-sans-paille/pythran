'''
'''

import sys
import os
import ctypes


class omp(object):
    LD_LIBRARY_PATHS = (
            "/usr/lib/x86_64-linux-gnu/",
            )

    def __init__(self):
        try:
            self.libomp = ctypes.CDLL("libgomp.so.1")
        except OSError:
            old_path = os.environ.get("LD_LIBRARY_PATH", "")
            os.environ["LD_LIBRARY_PATH"] = ":".join(omp.LD_LIBRARY_PATHS)
            self.libomp = ctypes.CDLL("libgomp.so.1")
            os.environ["LD_LIBRARY_PATH"] = old_path

    def __getattribute__(self, name):
        if name == 'libomp':
            return object.__getattribute__(self, 'libomp')
        else:
            return getattr(self.libomp, 'omp_' + name)

# see http://mail.python.org/pipermail/python-ideas/2012-May/014969.html
sys.modules[__name__] = omp()

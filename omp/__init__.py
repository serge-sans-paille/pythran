"""OpenMP wrapper using a libgomp dynamically loaded library."""

from ctypes.util import find_library
from subprocess import check_output, CalledProcessError
from numpy.distutils.misc_util import msvc_runtime_major
import ctypes
import os
import sys

try:
    # there may be an environ modification when loading config
    from pythran.config import compiler
except ImportError:
    def compiler():
        return os.environ.get('CXX', 'c++')
cxx = compiler()


class OpenMP(object):

    """
    Internal representation of the OpenMP module.

    Custom class is used to dynamically add omp runtime function
    to this library when function is called.
    """

    def __init__(self):
        ver = msvc_runtime_major()
        if ver is None:
            self.init_not_msvc()
        else:
            self.init_msvc(ver)

    def init_msvc(self, ver):
        vcomp_path = find_library('vcomp%d.dll' % ver)
        if not vcomp_path:
            raise ImportError("I can't find a shared library for vcomp.")
        else:
            # Load the library (shouldn't fail with an absolute path right?)
            self.libomp = ctypes.CDLL(vcomp_path)
            self.version = 20

    def init_not_msvc(self):
        """ Find OpenMP library and try to load if using ctype interface. """
        # find_library() does not search automatically LD_LIBRARY_PATH
        paths = os.environ.get('LD_LIBRARY_PATH', '').split(':')
        for gomp in ('libgomp.so', 'libgomp.dylib'):
            if cxx is None:
                continue
            cmd = [cxx, '-print-file-name=' + gomp]
            # the subprocess can fail in various ways
            # in that case just give up that path
            try:
                path = os.path.dirname(check_output(cmd).strip())
                if path:
                    paths.append(path)
            except (OSError, CalledProcessError):
                pass

        # Try to load find libgomp shared library using loader search dirs
        libgomp_path = find_library("gomp")

        # Try to use custom paths if lookup failed
        for path in paths:
            if libgomp_path:
                break
            path = path.strip()
            if os.path.isdir(path):
                libgomp_path = find_library(os.path.join(str(path), "libgomp"))

        if not libgomp_path:
            raise ImportError("I can't find a shared library for libgomp,"
                              " you may need to install it or adjust the "
                              "LD_LIBRARY_PATH environment variable.")
        else:
            # Load the library (shouldn't fail with an absolute path right?)
            self.libomp = ctypes.CDLL(libgomp_path)
            self.version = 45

    def __getattr__(self, name):
        """
        Get correct function name from libgomp ready to be use.

        __getattr__ is call only `name != libomp` as libomp is a real
        attribute.
        """
        if name == 'VERSION':
            return self.version
        return getattr(self.libomp, 'omp_' + name)

# see http://mail.python.org/pipermail/python-ideas/2012-May/014969.html
sys.modules[__name__] = OpenMP()


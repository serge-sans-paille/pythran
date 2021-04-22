"""OpenMP wrapper using a libgomp dynamically loaded library."""

from ctypes.util import find_library
from subprocess import check_output, CalledProcessError
from numpy.distutils.misc_util import (
    msvc_runtime_major, get_shared_lib_extension
)
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

    def get_libomp_names(self):
        """Return list of OpenMP libraries to try, based on platform and
        compiler detected."""
        if cxx is None:
            # Can't tell what compiler we're using, guessing we need libgomp
            names = ['libgomp']
        else:
            cmd = [cxx, '--version']
            try:
                version_str = os.path.dirname(check_output(cmd).decode().strip())
            except (OSError, CalledProcessError):
                version_str = ''

            if 'clang' in version_str:
                names = ['libomp', 'libiomp5', 'libgomp']
            elif version_str.startswith('Intel'):
                names = ['libiomp5']
            else:
                # Too many GCC flavors and version strings, make this the default
                # rather than try to detect if it's GCC
                names = ['libgomp']

        return [name + get_shared_lib_extension() for name in names]

    def init_not_msvc(self):
        """ Find OpenMP library and try to load if using ctype interface. """
        # find_library() does not search automatically LD_LIBRARY_PATH
        paths = os.environ.get('LD_LIBRARY_PATH', '').split(':')

        for libomp_name in self.get_libomp_names():
            if cxx is None or sys.platform == 'win32':
                # Note: Clang supports -print-file-name, but not yet for
                # clang-cl as of v12.0.0 (April '21)
                continue

            cmd = [cxx, '-print-file-name=' + libomp_name]
            # the subprocess can fail in various ways in that case just give up
            try:
                path = os.path.dirname(check_output(cmd).decode().strip())
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


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
        # find_library() does not automatically search LD_LIBRARY_PATH
        # until Python 3.6+, so we explicitly add it.
        # LD_LIBRARY_PATH is used on Linux, while macOS uses DYLD_LIBRARY_PATH
        # and DYLD_FALLBACK_LIBRARY_PATH.
        env_vars = []
        if sys.platform == 'darwin':
            env_vars = ['DYLD_LIBRARY_PATH', 'DYLD_FALLBACK_LIBRARY_PATH']
        elif sys.platform.startswith('linux'):
            env_vars = ['LD_LIBRARY_PATH']

        paths = []
        for env_var in env_vars:
            paths += os.environ.get(env_var, '').split(os.pathsep)

        libomp_names = self.get_libomp_names()
        for libomp_name in libomp_names:
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

        for libomp_name in libomp_names:
            # Try to load find libomp shared library using loader search dirs
            libomp_path = find_library(libomp_name)

            # Try to use custom paths if lookup failed
            for path in paths:
                if libomp_path:
                    break
                path = path.strip()
                if os.path.isfile(os.path.join(path, libomp_name)):
                    libomp_path = os.path.join(path, libomp_name)

            if libomp_path:
                # Load the library
                try:
                    self.libomp = ctypes.CDLL(libomp_path)
                except OSError:
                    raise ImportError("found openMP library '{}' but couldn't load it. "
                                      "This may happen if you are cross-compiling.".format(libomp_path))
                self.version = 45
                return

        msg = "I can't find a shared library for libomp, you may need to install it"
        if env_vars:
            msg += " or adjust the "
            msg += " or ".join(env_vars)
            msg += " environment variable"
            if len(env_vars) > 1:
                msg += "s"
        msg += "."
        raise ImportError(msg)

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


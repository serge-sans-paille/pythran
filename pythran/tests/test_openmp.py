import unittest
from distutils.errors import CompileError
from pythran.tests import TestFromDir
import os
import pythran
from pythran.syntax import PythranSyntaxError
from pythran.spec import Spec

class TestOpenMP(TestFromDir):
    path = os.path.join(os.path.dirname(__file__), "openmp")

class TestOpenMP4(TestFromDir):
    path = os.path.join(os.path.dirname(__file__), "openmp.4")

    @staticmethod
    def interface(name, file=None):
        return Spec({name: []})

    @staticmethod
    def extract_runas(name, filepath):
        return ['#runas {}()'.format(name)]


class TestOpenMPLegacy(TestFromDir):
    '''
    Test old style OpenMP constructs, not using comments but strings
    and relying on function-scope locals
    '''
    path = os.path.join(os.path.dirname(__file__), "openmp.legacy")

    @staticmethod
    def interface(name, file=None):
        return Spec({name: []})

    @staticmethod
    def extract_runas(name, filepath):
        return ['#runas {}()'.format(name)]

# only activate OpenMP tests if the underlying compiler supports OpenMP
try:
    pythran.compile_cxxcode("omp", '#include <omp.h>',
                            extra_compile_args=['-fopenmp'],
                            extra_link_args=['-fopenmp'])
    import omp
    if '-fopenmp' in pythran.config.cfg.get('compiler', 'ldflags'):
        TestOpenMP4.populate(TestOpenMP4)
        TestOpenMP.populate(TestOpenMP)
        TestOpenMPLegacy.populate(TestOpenMPLegacy)
except PythranSyntaxError:
    raise
except (CompileError, ImportError):
    pass


if __name__ == '__main__':
    unittest.main()

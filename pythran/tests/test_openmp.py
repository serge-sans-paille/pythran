import unittest
from test_env import TestFromDir
import os
import pythran

class TestOpenMP(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"openmp")

class TestOpenMPLegacy(TestFromDir):
    '''
    Test old style OpenMP constructs, not using comments but strings
    and relying on function-scope locals
    '''
    path = os.path.join(os.path.dirname(__file__),"openmp.legacy")

# only activate OpenMP tests if the underlying compiler supports OpenMP
try:
    pythran.compile_cxxcode('#include <omp.h>')
    TestOpenMP.populate(TestOpenMP)
    TestOpenMPLegacy.populate(TestOpenMP)
except pythran.CompileError:
    pass


if __name__ == '__main__':
    unittest.main()

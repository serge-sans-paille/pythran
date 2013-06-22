import unittest
from test_env import TestFromDir
import os
import pythran

class TestOpenMP(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"openmp")

# only activate OpenMP tests if the underlying compiler supports OpenMP
try:
    pythran.compile_cxxcode('#include <omp.h>')
    TestOpenMP.populate(TestOpenMP)
except pythran.CompileError:
    pass


if __name__ == '__main__':
    unittest.main()

from test_env import TestEnv
import test_numpy
import test_cases

class TestSimd(test_numpy.TestNumpy, test_cases.TestCases):

    PYTHRAN_CXX_FLAGS = TestEnv.PYTHRAN_CXX_FLAGS + ['-DUSE_BOOST_SIMD', '-march=native']


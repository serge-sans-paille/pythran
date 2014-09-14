from test_env import TestEnv
import test_numpy_func, test_numpy_ufunc, test_ndarray
import test_cases


@TestEnv.module
class TestSimd(test_numpy_func.TestNumpyFunc, test_numpy_ufunc.TestNumpyUFunc, test_ndarray.TestNdarray, test_cases.TestCases):

    PYTHRAN_CXX_FLAGS = TestEnv.PYTHRAN_CXX_FLAGS + ['-DUSE_BOOST_SIMD', '-march=native']


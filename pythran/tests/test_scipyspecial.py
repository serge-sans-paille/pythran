import unittest
from pythran.tests import TestEnv
import numpy as np
import sys

from pythran.typing import NDArray, List, Tuple


@TestEnv.module
class TestNumpyFunc0(TestEnv):
    def test_spherical_jn_scalar(self):
        self.run_test("""
        from scipy.special import spherical_jn
        def spherical_bessel_j_scalar(v, x):
            return spherical_jn(v, x)""",
                      5, 1.414,
                      spherical_bessel_j_scalar=[int, float])

    def test_spherical_jn_1d(self):
        self.run_test("""
        from scipy.special import spherical_jn
        def spherical_bessel_j_1d(v, x):
            return spherical_jn(v, x)""",
                      5, np.array([1.0, 2.0, 3.0]),
                      spherical_bessel_j_1d=[int, NDArray[float,:]])

    def test_spherical_jn_order1d(self):
        self.run_test("""
        from scipy.special import spherical_jn
        def spherical_bessel_j_order1d(v, x):
            return spherical_jn(v, x)""",
                      np.array([1, 2, 3]), 5.0,
                      spherical_bessel_j_order1d=[NDArray[int,:], float])

    def test_spherical_jn_2d(self):
        self.run_test("""
        from scipy.special import spherical_jn
        def spherical_bessel_j_2d(v, x):
            return spherical_jn(v, x)""",
                      5, np.array([[1.0, 2.0], [3.0, 4.0]]),
                      spherical_bessel_j_2d=[int, NDArray[float,:,:]])

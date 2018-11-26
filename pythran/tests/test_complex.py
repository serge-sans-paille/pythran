import numpy as np

from pythran.config import cfg
from test_env import TestEnv
from pythran.typing import NDArray

import unittest

try:
    np.float128
    has_float128 = True
except AttributeError:
    has_float128 = False


class TestComplex(TestEnv):

    """ Check complex support in Pythran. """

    def test_complex_limited_range(self):
        """ Check complex computation is the same as numpy for corner case. """
        # see -fcx-limited-range
        if cfg.getboolean('pythran', 'complex_hook'):
            self.run_test("""
                def test_complex_limited_range(a, b):
                    return a * b""",
                          complex(-4, np.nan), complex(4, -np.inf),
                          test_complex_limited_range=[complex, complex])

    def test_conjugate(self):
        """
        Check complex conjugate.

        Checked for:
            * Method and numpy function call
            * conj and conjugate for each of them
            * complex and array (1 and 2 D)
        """
        self.run_test("""
            def test_conjugate(c, a, a2d):
                import numpy as np
                return (np.conj(c), np.conj(a), a2d.conj(),
                        np.conjugate(c), np.conjugate(a), a2d.conjugate())
                      """,
                      3 + 2j, np.array([3 + 2j]), np.array([[3 + 2j]]),
                      test_conjugate=[np.complex128,
                                      NDArray[np.complex128, :],
                                      NDArray[complex, :, :]])

    def test_complex_array_abs(self):
        self.run_test('def test_complex_array_abs(a): import numpy as np ; return np.abs(a)',
                      np.array([[3 + 2j]]),
                      test_complex_array_abs=[NDArray[complex, :, :]])

    def test_complex_floordiv(self):
        self.run_test('def complex_floordiv(x): import numpy as np; return np.floor_divide(x, 2 + 2j)',
                      3.5 - 3.5j,
                      complex_floordiv=[complex])

    def test_complex_array_sqr(self):
        self.run_test('def test_complex_array_sqr(a): return a ** 2',
                      np.array([[3 + 2j]]),
                      test_complex_array_sqr=[NDArray[complex, :, :]])

    def test_complex_array_mul_i(self):
        self.run_test('def test_complex_array_mul_i(e): return e + 1j * e',
                      np.array([[3.,2.,4.]]),
                      test_complex_array_mul_i=[NDArray[float, :, :]])

    def test_non_complex_array_real_imag(self):
        self.run_test('def test_non_complex_array_real_imag(e): return e.real + e.imag',
                      np.array([[3.,2.,4.]]),
                      test_non_complex_array_real_imag=[NDArray[float, :, :]])

    def test_complex_array_real_imag(self):
        self.run_test('def test_complex_array_real_imag(e): return e.real + e.imag',
                      np.array([[3.,2.,4.]], dtype=complex),
                      test_complex_array_real_imag=[NDArray[complex, :, :]])

    def test_complex_sum_different_types(self):
        self.run_test('def test_complex_different_types(a,b): return a + b',
                      np.array([[3 + 2j]],dtype=np.complex64),np.array([[8 + 1j]],dtype=np.complex128),
                      test_complex_different_types=[NDArray[np.complex64, :, :],NDArray[np.complex128, :, :]])

    def test_complex_sum_same_types(self):
        self.run_test('def test_complex_same_types(a): return a + a',
                      np.array([[3 + 2j]],dtype=np.complex64),
                      test_complex_same_types=[NDArray[np.complex64, :, :]])

    def test_complex_array_real_assign(self):
        self.run_test('def test_complex_array_real_assign(a): a.real = 1; return a',
                      np.array([[3 + 2j, 2, 1, 0]] * 3,dtype=np.complex64),
                      test_complex_array_real_assign=[NDArray[np.complex64, :, :]])

    def test_complex_array_gexpr_real_assign(self):
        self.run_test('def test_complex_array_gexpr_real_assign(a): a.real[1:] = 1; return a',
                      np.array([[3 + 2j, 2, 1, 0]] * 3,dtype=np.complex64),
                      test_complex_array_gexpr_real_assign=[NDArray[np.complex64, :, :]])

    def test_complex_array_iexpr_real_assign(self):
        self.run_test('def test_complex_array_iexpr_real_assign(a): a.real[1] = 1; return a',
                      np.array([[3 + 2j, 2, 1, 0]] * 3,dtype=np.complex64),
                      test_complex_array_iexpr_real_assign=[NDArray[np.complex64, :, :]])

    def test_complex_broadcast_scalar0(self):
        self.run_test('def complex_broadcast_scalar0(x): return x + 1.5, 1.3 +x, 3.1 - x, x - 3.7, x * 5.4, 7.6 * x',
                      5.1 + 3j,
                      complex_broadcast_scalar0=[complex])

    def test_complex_broadcast_scalar1(self):
        self.run_test('def complex_broadcast_scalar1(x): return x + 1.5, 1.3 +x, 3.1 - x, x - 3.7, x * 5.4, 7.6 * x',
                      np.complex64(5.1 + 3j),
                      complex_broadcast_scalar1=[np.complex64])

    def test_complex_array_imag_assign(self):
        self.run_test('def test_complex_array_imag_assign(a): a.imag = 1; return a',
                      np.array([[3 + 2j, 2, 1, 0]] * 3,dtype=np.complex64),
                      test_complex_array_imag_assign=[NDArray[np.complex64, :, :]])

    def test_complex_array_gexpr_imag_assign(self):
        self.run_test('def test_complex_array_gexpr_imag_assign(a): a.imag[1:] = 1; return a',
                      np.array([[3 + 2j, 2, 1, 0]] * 3,dtype=np.complex64),
                      test_complex_array_gexpr_imag_assign=[NDArray[np.complex64, :, :]])

    def test_complex_array_iexpr_imag_assign(self):
        self.run_test('def test_complex_array_iexpr_imag_assign(a): a.imag[1] = 1; return a',
                      np.array([[3 + 2j, 2, 1, 0]] * 3,dtype=np.complex64),
                      test_complex_array_iexpr_imag_assign=[NDArray[np.complex64, :, :]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_complex256_array0(self):
        self.run_test('def complex256_array0(x): import numpy as np; return np.cos(x * 2j)',
                      np.array([1.2,3.1], dtype=np.complex256) ** 6,
                      complex256_array0=[NDArray[np.complex256, :]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_complex256_array1(self):
        self.run_test('def complex256_array1(x): import numpy as np; return (x * 2j)**2',
                      np.array([1.2,3.1], dtype=np.complex256) ** 6,
                      complex256_array1=[NDArray[np.complex256, :]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_complex256_array2(self):
        self.run_test('def complex256_array2(x): import numpy as np; return np.ones(x, dtype=np.complex256)',
                      10,
                      complex256_array2=[int])

    @unittest.skipIf(not has_float128, "not float128")
    def test_complex256_array3(self):
        self.run_test('def complex256_array3(x): return x.real, x.imag',
                      np.array([2j, 2], dtype=np.complex256)** 5,
                      complex256_array3=[NDArray[np.complex256, :]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_complex256_array4(self):
        self.run_test('def complex256_array4(x): return x.conj(), x.sum()',
                      np.array([2j, 2], dtype=np.complex256)** 7,
                      complex256_array4=[NDArray[np.complex256, :]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_complex256_array5(self):
        self.run_test('def complex256_array5(x): return x',
                      np.complex256(1 + 1j),
                      complex256_array5=[np.complex256])

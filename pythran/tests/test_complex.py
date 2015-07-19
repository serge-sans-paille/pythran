import numpy as np

from pythran.config import cfg
from test_env import TestEnv


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

    def test_complex_number_conj_fun(self):
        self.run_test('def test_complex_number_conj_fun(a): import numpy as np ; return np.conj(a)',
                      3 + 2j,
                      test_complex_number_conj_fun=[np.complex128])

    def test_complex_array_conj_fun(self):
        self.run_test('def test_complex_array_conj_fun(a): import numpy as np ; return np.conj(a)',
                      np.array([3 + 2j]),
                      test_complex_array_conj_fun=[np.array([np.complex128])])

    def test_complex_array_conj_method(self):
        self.run_test('def test_complex_array_conj_method(a): return a.conj()',
                      np.array([[3 + 2j]]),
                      test_complex_array_conj_method=[np.array([[complex]])])

    def test_complex_number_conjugate_fun(self):
        self.run_test('def test_complex_number_conjugate_fun(a): import numpy as np ; return np.conjugate(a)',
                      3 + 2j,
                      test_complex_number_conjugate_fun=[np.complex128])

    def test_complex_number_conjugate_method(self):
        self.run_test('def test_complex_number_conjugate_method(a): import numpy as np ; return a.conjugate()',
                      3 + 2j,
                      test_complex_number_conjugate_method=[np.complex128])

    def test_complex_array_conjugate_fun(self):
        self.run_test('def test_complex_array_conjugate_fun(a): import numpy as np ; return np.conjugate(a)',
                      np.array([3 + 2j]),
                      test_complex_array_conjugate_fun=[np.array([np.complex128])])

    def test_complex_array_conjugate_method(self):
        self.run_test('def test_complex_array_conjugate_method(a): return a.conjugate()',
                      np.array([[3 + 2j]]),
                      test_complex_array_conjugate_method=[np.array([[complex]])])

    def test_complex_array_abs(self):
        self.run_test('def test_complex_array_abs(a): import numpy as np ; return np.abs(a)',
                      np.array([[3 + 2j]]),
                      test_complex_array_abs=[np.array([[complex]])])

    def test_complex_array_sqr(self):
        self.run_test('def test_complex_array_sqr(a): import numpy as np ; return a ** 2',
                      np.array([[3 + 2j]]),
                      test_complex_array_sqr=[np.array([[complex]])])

    def test_complex_array_mul_i(self):
        self.run_test('def test_complex_array_mul_i(e): return e + 1j * e',
                      np.array([[3.,2.,4.]]),
                      test_complex_array_mul_i=[np.array([[float]])])

    def test_non_complex_array_real_imag(self):
        self.run_test('def test_non_complex_array_real_imag(e): return e.real + e.imag',
                      np.array([[3.,2.,4.]]),
                      test_non_complex_array_real_imag=[np.array([[float]])])

    def test_complex_array_real_imag(self):
        self.run_test('def test_complex_array_real_imag(e): return e.real + e.imag',
                      np.array([[3.,2.,4.]], dtype=complex),
                      test_complex_array_real_imag=[np.array([[complex]])])

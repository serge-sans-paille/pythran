import unittest
import sys
from pythran.tests import TestEnv
import numpy

from pythran.typing import NDArray, List


@TestEnv.module
class TestNumpyFunc1(TestEnv):

    def test_sum_bool2(self):
        self.run_test("def np_sum_bool2(a): return a.sum()", numpy.ones(10,dtype=bool).reshape(2,5), np_sum_bool2=[NDArray[bool,:,:]])

    def test_sum_expr(self):
        self.run_test("def np_sum_expr(a):\n from numpy import ones\n return (a + ones(10)).sum()", numpy.arange(10), np_sum_expr=[NDArray[int,:]])

    def test_sum2_(self):
        self.run_test("def np_sum2_(a): return a.sum()", numpy.arange(10).reshape(2,5), np_sum2_=[NDArray[int,:,:]])

    def test_sum3_(self):
        self.run_test("def np_sum3_(a): return a.sum(1)", numpy.arange(10).reshape(2,5), np_sum3_=[NDArray[int,:,:]])

    def test_sum4_(self):
        self.run_test("def np_sum4_(a): return a.sum(0)", numpy.arange(10).reshape(2,5), np_sum4_=[NDArray[int,:,:]])

    def test_sum5_(self):
        self.run_test("def np_sum5_(a): return a.sum(0)", numpy.arange(10), np_sum5_=[NDArray[int,:]])

    def test_sum6_(self):
        self.run_test("def np_sum6_(a): return a.sum(0)", numpy.arange(12).reshape(2,3,2), np_sum6_=[NDArray[int,:,:,:]])

    def test_sum7_(self):
        self.run_test("def np_sum7_(a): return a.sum(1)", numpy.arange(12).reshape(2,3,2), np_sum7_=[NDArray[int,:,:,:]])

    def test_sum8_(self):
        self.run_test("def np_sum8_(a): return a.sum(2)", numpy.arange(12).reshape(2,3,2), np_sum8_=[NDArray[int,:,:,:]])

    def test_sum9_(self):
        self.run_test("def np_sum9_(a): import numpy as np ; return np.sum(a*a,0)", numpy.arange(12).reshape(2,3,2), np_sum9_=[NDArray[int,:,:,:]])

    def test_sum10_(self):
        self.run_test("def np_sum10_(a): import numpy as np ; return np.sum(a-a,1)", numpy.arange(12).reshape(2,3,2), np_sum10_=[NDArray[int,:,:,:]])

    def test_sum11_(self):
        self.run_test("def np_sum11_(a): import numpy as np ; return np.sum(a+a,2)", numpy.arange(12).reshape(2,3,2), np_sum11_=[NDArray[int,:,:,:]])

    @unittest.skipIf(sys.maxsize == (2**31 - 1), "overflow test")
    def test_sum12_(self):
        self.run_test("def np_sum12_(a): import numpy as np ; return np.sum(a)",
                      numpy.array([2**32-1, -2**32 +1 , -2**32 + 1], dtype=numpy.uint32), np_sum12_=[NDArray[numpy.uint32,:]])

    def test_sum13_(self):
        self.run_test("def np_sum13_(a): import numpy as np ; return np.sum(a)",
                      numpy.array([2**31-1, -2**31 +1 , -2**31 + 1], dtype=numpy.int32), np_sum13_=[NDArray[numpy.int32,:]])

    @unittest.skipIf(sys.maxsize == (2**31 - 1), "overflow test")
    def test_sum14_(self):
        self.run_test("def np_sum14_(a): import numpy as np ; return np.sum(a)",
                      numpy.array([2**31-1, 2**31 +1 , 2**31 + 1], dtype=numpy.int32), np_sum14_=[NDArray[numpy.int32,:]])

    def test_prod_(self):
        """ Check prod function for numpy array. """
        self.run_test("""
            def np_prod_(a):
                return a.prod()""",
                      numpy.arange(10),
                      np_prod_=[NDArray[int,:]])

    def test_prod_bool(self):
        self.run_test("def np_prod_bool(a): return (a > 2).prod()", numpy.arange(10), np_prod_bool=[NDArray[int,:]])

    def test_prod_bool2(self):
        self.run_test("def np_prod_bool2(a): return a.prod()", numpy.ones(10,dtype=bool).reshape(2,5), np_prod_bool2=[NDArray[bool,:,:]])

    def test_prod2_(self):
        self.run_test("def np_prod2_(a): return a.prod()", numpy.arange(10).reshape(2,5), np_prod2_=[NDArray[int,:,:]])

    def test_prod3_(self):
        self.run_test("def np_prod3_(a): return a.prod(1)", numpy.arange(10).reshape(2,5), np_prod3_=[NDArray[int,:,:]])

    def test_prod4_(self):
        self.run_test("def np_prod4_(a): return a.prod(0)", numpy.arange(10).reshape(2,5), np_prod4_=[NDArray[int,:,:]])

    def test_prod5_(self):
        self.run_test("def np_prod5_(a): return a.prod(0)", numpy.arange(10), np_prod5_=[NDArray[int,:]])

    def test_prod6_(self):
        self.run_test("def np_prod6_(a): return a.prod(0)", numpy.arange(12).reshape(2,3,2), np_prod6_=[NDArray[int,:,:,:]])

    def test_prod7_(self):
        self.run_test("def np_prod7_(a): return a.prod(1)", numpy.arange(12).reshape(2,3,2), np_prod7_=[NDArray[int,:,:,:]])

    def test_prod8_(self):
        self.run_test("def np_prod8_(a): return a.prod(2)", numpy.arange(12).reshape(2,3,2), np_prod8_=[NDArray[int,:,:,:]])

    def test_prod9_(self):
        self.run_test("def np_prod9_(a): import numpy as np ; return np.prod(a*a,0)", numpy.arange(12).reshape(2,3,2), np_prod9_=[NDArray[int,:,:,:]])

    def test_prod10_(self):
        self.run_test("def np_prod10_(a): import numpy as np ; return np.prod(a-a,1)", numpy.arange(12).reshape(2,3,2), np_prod10_=[NDArray[int,:,:,:]])

    def test_prod11_(self):
        self.run_test("def np_prod11_(a): import numpy as np ; return np.prod(a+a,2)", numpy.arange(12).reshape(2,3,2), np_prod11_=[NDArray[int,:,:,:]])

    def test_prod_expr(self):
        self.run_test("def np_prod_expr(a):\n from numpy import ones\n return (a + ones(10)).prod()", numpy.arange(10), np_prod_expr=[NDArray[int,:]])

    def test_amin_amax(self):
        self.run_test("def np_amin_amax(a):\n from numpy import amin,amax\n return amin(a), amax(a)",numpy.arange(10),  np_amin_amax=[NDArray[int,:]])

    def test_min_(self):
        self.run_test("def np_min_(a): return a.min()", numpy.arange(10), np_min_=[NDArray[int,:]])

    def test_min1_(self):
        self.run_test("def np_min1_(a): return (a+a).min()", numpy.arange(10), np_min1_=[NDArray[int,:]])

    def test_min2_(self):
        self.run_test("def np_min2_(a): return a.min()", numpy.arange(10).reshape(2,5), np_min2_=[NDArray[int,:,:]])

    def test_min3_(self):
        self.run_test("def np_min3_(a): return a.min(1)", numpy.arange(10).reshape(2,5), np_min3_=[NDArray[int,:,:]])

    def test_min4_(self):
        self.run_test("def np_min4_(a): return a.min(0)", numpy.arange(10).reshape(2,5), np_min4_=[NDArray[int,:,:]])

    def test_min5_(self):
        self.run_test("def np_min5_(a): return a.min(0)", numpy.arange(10), np_min5_=[NDArray[int,:]])

    def test_min6_(self):
        self.run_test("def np_min6_(a): return a.min(1)", numpy.arange(30).reshape(2,5,3), np_min6_=[NDArray[int,:,:,:]])

    def test_min7_(self):
        self.run_test("def np_min7_(a): return (a+a).min(1)", numpy.arange(30).reshape(2,5,3), np_min7_=[NDArray[int,:,:,:]])

    def test_min8_(self):
        self.run_test("def np_min8_(a): return a.min()", numpy.arange(4, dtype=numpy.int8), np_min8_=[NDArray[numpy.int8,:]])

    def test_max_(self):
        self.run_test("def np_max_(a): return a.max()", numpy.arange(10), np_max_=[NDArray[int,:]])

    def test_max1_(self):
        self.run_test("def np_max1_(a): return (a+a).max()", numpy.arange(10), np_max1_=[NDArray[int,:]])

    def test_max2_(self):
        self.run_test("def np_max2_(a): return a.max()", numpy.arange(10).reshape(2,5), np_max2_=[NDArray[int,:,:]])

    def test_max3_(self):
        self.run_test("def np_max3_(a): return a.max(1)", numpy.arange(10).reshape(2,5), np_max3_=[NDArray[int,:,:]])

    def test_max4_(self):
        self.run_test("def np_max4_(a): return a.max(0)", numpy.arange(10).reshape(2,5), np_max4_=[NDArray[int,:,:]])

    def test_max5_(self):
        self.run_test("def np_max5_(a): return a.max(0)", numpy.arange(10), np_max5_=[NDArray[int,:]])

    def test_max6_(self):
        self.run_test("def np_max6_(a): return a.max(1)", numpy.arange(30).reshape(2,5,3), np_max6_=[NDArray[int,:,:,:]])

    def test_max7_(self):
        self.run_test("def np_max7_(a): return (a+a).max(1)", numpy.arange(30).reshape(2,5,3), np_max7_=[NDArray[int,:,:,:]])

    def test_max8_(self):
        self.run_test("def np_max8_(a): return a.max()", numpy.arange(4, dtype=numpy.int8), np_max8_=[NDArray[numpy.int8,:]])

    def test_all_(self):
        self.run_test("def np_all_(a): return a.all()", numpy.arange(10), np_all_=[NDArray[int,:]])

    def test_all2_(self):
        self.run_test("def np_all2_(a): return a.all()", numpy.ones(10).reshape(2,5), np_all2_=[NDArray[float,:,:]])

    def test_all3_(self):
        self.run_test("def np_all3_(a): return a.all(1)", numpy.arange(10).reshape(2,5), np_all3_=[NDArray[int,:,:]])

    def test_all4_(self):
        self.run_test("def np_all4_(a): return a.all(0)", numpy.ones(10).reshape(2,5), np_all4_=[NDArray[float,:,:]])

    def test_all5_(self):
        self.run_test("def np_all5_(a): return a.all(0)", numpy.arange(10), np_all5_=[NDArray[int,:]])

    def test_all6_(self):
        self.run_test("def np_all6_(a): return a.all().all()", numpy.arange(10), np_all6_=[NDArray[int,:]])

    def test_all7_(self):
        self.run_test("def np_all7_(a): return a.all().all(0)", numpy.arange(10), np_all7_=[NDArray[int,:]])

    def test_transpose_(self):
        self.run_test("def np_transpose_(a): return a.transpose()", numpy.arange(24).reshape(2,3,4), np_transpose_=[NDArray[int,:,:,:]])

    def test_transpose_expr(self):
        self.run_test("def np_transpose_expr(a): return (a + a).transpose()", numpy.ones(24).reshape(2,3,4), np_transpose_expr=[NDArray[float,:,:,:]])

    def test_transpose2_(self):
        self.run_test("def np_transpose2_(a): return a.transpose((2,0,1))", numpy.arange(24).reshape(2,3,4), np_transpose2_=[NDArray[int,:,:,:]])

    def test_alen0(self):
        self.run_test("def np_alen0(a): from numpy import alen ; return alen(a)", numpy.ones((5,6)), np_alen0=[NDArray[float,:,:]])

    def test_alen1(self):
        self.run_test("def np_alen1(a): from numpy import alen ; return alen(-a)", numpy.ones((5,6)), np_alen1=[NDArray[float,:,:]])

    def test_allclose0(self):
        self.run_test("def np_allclose0(a): from numpy import allclose ; return allclose([1e10,1e-7], a)", [1.00001e10,1e-8], np_allclose0=[List[float]])

    def test_allclose1(self):
        self.run_test("def np_allclose1(a): from numpy import allclose; return allclose([1e10,1e-8], +a)", numpy.array([1.00001e10,1e-9]), np_allclose1=[NDArray[float,:]])

    def test_allclose2(self):
        self.run_test("def np_allclose2(a): from numpy import array, allclose; return allclose(array([1e10,1e-8]), a)", numpy.array([1.00001e10,1e-9]), np_allclose2=[NDArray[float,:]])

    def test_allclose3(self):
        self.run_test("def np_allclose3(a): from numpy import allclose; return allclose(a, a)", [1.0, numpy.nan], np_allclose3=[List[float]])

    def test_allclose4(self):
        """ Check allclose behavior with infinity values. """
        self.run_test("""
            def np_allclose4(a):
                from numpy import array, allclose
                return allclose(array([-float('inf'), float('inf'),
                                       -float('inf')]), a)""",
                      numpy.array([float("inf"), float("inf"), -float('inf')]),
                      np_allclose4=[NDArray[float,:]])

    def test_alltrue0(self):
        self.run_test("def np_alltrue0(b): from numpy import alltrue ; return alltrue(b)", numpy.array([True, False, True, True]), np_alltrue0=[NDArray[bool,:]])

    def test_alltrue1(self):
        self.run_test("def np_alltrue1(a): from numpy import alltrue ; return alltrue(a >= 5)", numpy.array([1, 5, 2, 7]), np_alltrue1=[NDArray[int,:]])

    def test_count_nonzero0(self):
        self.run_test("def np_count_nonzero0(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([[-1, -5, -2, 7], [9, 3, 0, -0]]), np_count_nonzero0=[NDArray[int,:,:]])

    def test_count_nonzero1(self):
        self.run_test("def np_count_nonzero1(a): from numpy import count_nonzero; return count_nonzero(a)",
                       numpy.array([-1, 5, -2, 0]), np_count_nonzero1=[NDArray[int,:]])

    def test_count_nonzero2(self):
        self.run_test("def np_count_nonzero2(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([-1., 0., -2., -1e-20]), np_count_nonzero2=[NDArray[float,:]])

    def test_count_nonzero3(self):
        self.run_test("def np_count_nonzero3(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([[0, 2, 0., 4 + 1j], [0.+0.j, 0.+4j, 1.+0j, 1j]]), np_count_nonzero3=[NDArray[complex,:,:]])

    def test_count_nonzero4(self):
        self.run_test("def np_count_nonzero4(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([[True, False], [False, False]]), np_count_nonzero4=[NDArray[bool,:,:]])

    def test_count_nonzero5(self):
        self.run_test("def np_count_nonzero5(a): from numpy import count_nonzero; return count_nonzero(a*2)",
                      numpy.array([[-1, -5, -2, 7], [9, 3, 0, -0]]), np_count_nonzero5=[NDArray[int,:,:]])


    def test_isclose0(self):
        self.run_test("def np_isclose0(u): from numpy import isclose; return isclose(u, u)",
                      numpy.array([[-1.01, 1e-10+1e-11, -0, 7., float('NaN')], [-1.0, 1e-10, 0., 7., float('NaN')]]),
                      np_isclose0=[NDArray[float,:,:]])

    def test_isclose1(self):
        self.run_test("def np_isclose1(u, v): from numpy import isclose; return isclose(u, v, 1e-19, 1e-16)",
                      numpy.array([-1.01, 1e-10+1e-11, float("inf"), 7.]),
                      numpy.array([9., 1e-10, float("inf"), float('NaN')]),
                      np_isclose1=[NDArray[float,:], NDArray[float,:]])

    def test_isclose2(self):
        self.run_test("def np_isclose2(u,v): from numpy import isclose; return isclose(u, v, 1e-16, 1e-19)",
                      numpy.array([-1.01, 1e-10+1e-11, -0, 7., float('NaN')]),
                      numpy.array([-1., 1e-10+2e-11, -0, 7.1, float('NaN')]),
                      np_isclose2=[NDArray[float,:], NDArray[float,:]])

    def test_isclose3(self):
        self.run_test("def np_isclose3(u): from numpy import isclose; return isclose(u, u)",
                      numpy.array([9.+3j, 1e-10, 1.1j, float('NaN')]),
                      np_isclose3=[NDArray[complex,:]])

    def test_isclose4(self):
        self.run_test("def np_isclose4(u,v): from numpy import isclose; return isclose(u, v)",
                      numpy.array([True, False, True, True, False]),
                      numpy.array([True, False, False, True, True]),
                      np_isclose4=[NDArray[bool,:], NDArray[bool,:]])

    def test_isclose5(self):
        self.run_test("def np_isclose5(u,v): from numpy import isclose; return isclose(u, v)",
                      1e-10,
                      1e-10+1e-11,
                      np_isclose5=[float, float])

    def test_isclose6(self):
        self.run_test("def np_isclose6(u, v): from numpy import isclose; return isclose(u, v, 1e-19, 1e-16)",
                      numpy.array([[-float("inf"), 1e-10+1e-11, -0, 7.],[9., 1e-10, 0., float('NaN')]]),
                      numpy.array([float("inf"), 1e-10, 0., float('NaN')]),
                      np_isclose6=[NDArray[float,:,:], NDArray[float,:]])

    def test_isclose7(self):
        self.run_test("def np_isclose7(u, v): from numpy import isclose; return isclose(u, v, 1e-19, 1e-16)",
                      numpy.array([9., 1e-10, 0., float('NaN')]),
                      numpy.array([[-1.01, 1e-10+1e-11, -0, 7.],[9., 1e-10, 0., float('NaN')]]),
                      np_isclose7=[NDArray[float,:], NDArray[float,:,:]])

    def test_remainder0(self):
        self.run_test("def np_remainder0(u, v): from numpy import remainder; return remainder(u, v)",
                      numpy.array([9., 9., -9., -9.]),
                      numpy.array([2., -2., 2., -2.]),
                      np_remainder0=[NDArray[float,:], NDArray[float,:]])

    def test_numpy_ones_list(self):
        self.run_test(
            "def np_ones_list(u): from numpy import ones; return ones([u,u])",
            2,
            np_ones_list=[int])

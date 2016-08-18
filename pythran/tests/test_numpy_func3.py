""" Tests for part of the numpy module. """

import unittest

import numpy

from test_env import TestEnv


@TestEnv.module
class TestNumpyFunc3(TestEnv):

    """
    This module includes tests for multiple numpy module function.

    Tested functions are:
    - numpy.dot
    - numpy.digitize
    - numpy.diff
    - numpy.trace
    - numpy.tri
    - numpy.trim_zeros
    - numpy.triu
    - numpy.tril
    - numpy.unique
    - numpy.unwrap

    and various combinations of +/-/** and trigonometric operations.
    """

    def test_dot0(self):
        self.run_test("def np_dot0(x, y): from numpy import dot; return dot(x, y)", 2, 3, np_dot0=[int, int])

    def test_dot1(self):
        self.run_test("def np_dot1(x): from numpy import dot ; y = [2, 3] ; return dot(x,y)", [2, 3], np_dot1=[[int]])

    def test_dot2(self):
        self.run_test("def np_dot2(x): from numpy import dot ; y = [2j, 3j] ; return dot(x,y)", [2j, 3j], np_dot2=[[complex]])

    def test_dot3(self):
        self.run_test("def np_dot3(x): from numpy import array ; y = array([2, 3]) ; return y.dot(x+x)", numpy.array([2, 3]), np_dot3=[numpy.array([int])])

    def test_dot4(self):
        self.run_test("def np_dot4(x): from numpy import dot ; y = [2, 3] ; return dot(x,y)", numpy.array([2, 3]), np_dot4=[numpy.array([int])])

    @unittest.skip("Illegal instruction on Travis")
    def test_dot5(self):
        """ Check for dgemm version of dot. """
        self.run_test("""
        def np_dot5(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
                      [[10, 11, 12], [13, 14, 15], [16, 17, 18]],
                      np_dot5=[[[float]], [[float]]])

    def test_dot6(self):
        """ Check for dot with "no blas type". """
        self.run_test("""
        def np_dot6(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9).reshape(3, 3),
                      numpy.arange(9, 18).reshape(3, 3),
                      np_dot6=[numpy.array([[int]]), numpy.array([[int]])])

    @unittest.skip("Illegal instruction on Travis")
    def test_dot7(self):
        """ Check for dgemm version of dot with rectangular shape. """
        self.run_test("""
        def np_dot7(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
                      [[10, 11, 12], [13, 14, 15], [16, 17, 18]],
                      np_dot7=[[[float]], [[float]]])

    def test_dot8(self):
        """ Check for dot with "no blas type" with rectangulare shape. """
        self.run_test("""
        def np_dot8(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6).reshape(3, 2),
                      numpy.arange(6, 12).reshape(2, 3),
                      np_dot8=[numpy.array([[int]]), numpy.array([[int]])])

    def test_dot9(self):
        """ Check for gemv version of dot. """
        self.run_test("""
        def np_dot9(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9).reshape(3, 3).tolist(),
                      [float(x) for x in range(9, 12)],
                      np_dot9=[[[float]], [float]])

    def test_dot10(self):
        """ Check for dot gemv with "no blas type". """
        self.run_test("""
        def np_dot10(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9).reshape(3, 3),
                      numpy.arange(9, 12),
                      np_dot10=[numpy.array([[int]]), numpy.array([int])])

    def test_dot11(self):
        """ Check for gemv version of dot with rectangular shape. """
        self.run_test("""
        def np_dot11(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6.).reshape(3, 2).tolist(),
                      [float(x) for x  in range(6, 8)],
                      np_dot11=[[[float]], [float]])

    def test_dot12(self):
        """ Check for dot gemv with "no blas type" with rectangulare shape. """
        self.run_test("""
        def np_dot12(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6).reshape(3, 2),
                      numpy.arange(6, 8),
                      np_dot12=[numpy.array([[int]]), numpy.array([int])])

    def test_dot13(self):
        """ Check for gevm version of dot. """
        self.run_test("""
        def np_dot13(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [float(x) for x in range(9, 12)],
                      numpy.arange(9.).reshape(3, 3).tolist(),
                      np_dot13=[[float], [[float]]])

    def test_dot14(self):
        """ Check for dot gevm with "no blas type". """
        self.run_test("""
        def np_dot14(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9, 12),
                      numpy.arange(9).reshape(3, 3),
                      np_dot14=[numpy.array([int]), numpy.array([[int]])])

    def test_dot15(self):
        """ Check for gevm version of dot with rectangular shape. """
        self.run_test("""
        def np_dot15(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [float(x) for x in range(6, 9)],
                      numpy.arange(6.).reshape(3, 2).tolist(),
                      np_dot15=[[float], [[float]]])

    def test_dot16(self):
        """ Check for dot gevm with "no blas type" with rectangulare shape. """
        self.run_test("""
        def np_dot16(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6, 9),
                      numpy.arange(6).reshape(3, 2),
                      np_dot16=[numpy.array([int]), numpy.array([[int]])])

    def test_digitize0(self):
        self.run_test("def np_digitize0(x): from numpy import array, digitize ; bins = array([0.0, 1.0, 2.5, 4.0, 10.0]) ; return digitize(x, bins)", numpy.array([0.2, 6.4, 3.0, 1.6]), np_digitize0=[numpy.array([float])])

    def test_digitize1(self):
        self.run_test("def np_digitize1(x): from numpy import array, digitize ; bins = array([ 10.0, 4.0, 2.5, 1.0, 0.0]) ; return digitize(x, bins)", numpy.array([0.2, 6.4, 3.0, 1.6]), np_digitize1=[numpy.array([float])])

    def test_diff0(self):
        self.run_test("def np_diff0(x): from numpy import diff; return diff(x)", numpy.array([1, 2, 4, 7, 0]), np_diff0=[numpy.array([int])])

    def test_diff1(self):
        self.run_test("def np_diff1(x): from numpy import diff; return diff(x,2)", numpy.array([1, 2, 4, 7, 0]), np_diff1=[numpy.array([int])])

    def test_diff2(self):
        self.run_test("def np_diff2(x): from numpy import diff; return diff(x)", numpy.array([[1, 3, 6, 10], [0, 5, 6, 8]]), np_diff2=[numpy.array([[int]])])

    def test_diff3(self):
        self.run_test("def np_diff3(x): from numpy import diff; return diff(x,2)", numpy.array([[1, 3, 6, 10], [0, 5, 6, 8]]), np_diff3=[numpy.array([[int]])])

    def test_diff4(self):
        self.run_test("def np_diff4(x): from numpy import diff; return diff(x + x)", numpy.array([1, 2, 4, 7, 0]), np_diff4=[numpy.array([int])])

    def test_trace0(self):
        self.run_test("def np_trace0(x): return x.trace()", numpy.arange(9).reshape(3,3), np_trace0=[numpy.array([[int]])])

    def test_trace1(self):
        self.run_test("def np_trace1(x): from numpy import trace; return trace(x, 1)", numpy.arange(12).reshape(3,4), np_trace1=[numpy.array([[int]])])

    def test_trace2(self):
        self.run_test("def np_trace2(x): from numpy import trace; return trace(x, 1)", numpy.arange(12).reshape(3,4), np_trace2=[numpy.array([[int]])])

    def test_tri0(self):
        self.run_test("def np_tri0(a): from numpy import tri; return tri(a)", 3, np_tri0=[int])

    def test_tri1(self):
        self.run_test("def np_tri1(a): from numpy import tri; return tri(a, 4)", 3, np_tri1=[int])

    def test_tri2(self):
        self.run_test("def np_tri2(a): from numpy import tri; return tri(a, 3, -1)", 4, np_tri2=[int])

    def test_tri3(self):
        self.run_test("def np_tri3(a): from numpy import tri, int64; return tri(a, 5, 1, int64)", 3, np_tri3=[int])

    def test_trim_zeros0(self):
        self.run_test("""
def np_trim_zeros0(x):
    from numpy import array, trim_zeros
    return trim_zeros(x)""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros0=[numpy.array([int])])

    def test_trim_zeros1(self):
        self.run_test("""
def np_trim_zeros1(x):
    from numpy import array, trim_zeros
    return trim_zeros(x, "f")""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros1=[numpy.array([int])])

    def test_trim_zeros2(self):
        self.run_test("""
def np_trim_zeros2(x):
    from numpy import trim_zeros
    return trim_zeros(x, "b")""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros2=[numpy.array([int])])

    def test_triu0(self):
        self.run_test("def np_triu0(x): from numpy import triu; return triu(x)", numpy.arange(12).reshape(3,4), np_triu0=[numpy.array([[int]])])

    def test_triu1(self):
        self.run_test("def np_triu1(x): from numpy import triu; return triu(x, 1)", numpy.arange(12).reshape(3,4), np_triu1=[numpy.array([[int]])])

    def test_triu2(self):
        self.run_test("def np_triu2(x): from numpy import triu; return triu(x, -1)", numpy.arange(12).reshape(3,4), np_triu2=[numpy.array([[int]])])

    def test_tril0(self):
        self.run_test("def np_tril0(x): from numpy import tril; return tril(x)", numpy.arange(12).reshape(3,4), np_tril0=[numpy.array([[int]])])

    def test_tril1(self):
        self.run_test("def np_tril1(x): from numpy import tril; return tril(x, 1)", numpy.arange(12).reshape(3,4), np_tril1=[numpy.array([[int]])])

    def test_tril2(self):
        self.run_test("def np_tril2(x): from numpy import tril; return tril(x, -1)", numpy.arange(12).reshape(3,4), np_tril2=[numpy.array([[int]])])

    def test_union1d(self):
        self.run_test("def np_union1d(x): from numpy import arange, union1d ; y = arange(1,4); return union1d(x, y)", numpy.arange(-1,2), np_union1d=[numpy.array([int])])

    def test_unique0(self):
        self.run_test("def np_unique0(x): from numpy import unique ; return unique(x)", numpy.array([1,1,2,2,2,1,5]), np_unique0=[numpy.array([int])])

    def test_unique1(self):
        self.run_test("def np_unique1(x): from numpy import unique ; return unique(x)", numpy.array([[1,2,2],[2,1,5]]), np_unique1=[numpy.array([[int]])])

    def test_unique2(self):
        self.run_test("def np_unique2(x): from numpy import unique ; return unique(x, True)", numpy.array([1,1,2,2,2,1,5]), np_unique2=[numpy.array([int])])

    def test_unique3(self):
        self.run_test("def np_unique3(x): from numpy import unique ; return unique(x, True, True)", numpy.array([1,1,2,2,2,1,5]), np_unique3=[numpy.array([int])])

    def test_unwrap0(self):
        self.run_test("def np_unwrap0(x): from numpy import unwrap, pi ; x[:3] += 2*pi; return unwrap(x)", numpy.arange(6, dtype=float), np_unwrap0=[numpy.array([float])])

    def test_unwrap1(self):
        self.run_test("def np_unwrap1(x): from numpy import unwrap, pi ; x[:3] += 2*pi; return unwrap(x, 4)", numpy.arange(6, dtype=float), np_unwrap1=[numpy.array([float])])

    def test_unwrap2(self):
        self.run_test("def np_unwrap2(x): from numpy import unwrap, pi ; x[:3] -= 2*pi; return unwrap(x, 4)", numpy.arange(6, dtype=float), np_unwrap2=[numpy.array([float])])

    def test_numpy_pow0(self):
        self.run_test('def numpy_pow0(a): return a ** 2',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_pow0=[numpy.array([[int]])])

    def test_numpy_pow1(self):
        self.run_test('def numpy_pow1(a): return a ** 2',
                      numpy.arange(100, dtype=float).reshape((10, 10)),
                      numpy_pow1=[numpy.array([[float]])])

    def test_numpy_pow2(self):
        self.run_test('def numpy_pow2(a): return a ** 2.2',
                      numpy.arange(100, dtype=float).reshape((10, 10)),
                      numpy_pow2=[numpy.array([[float]])])

    def test_add0(self):
        self.run_test("def np_add0(a, b): return a + b", numpy.ones(10), numpy.ones(10), np_add0=[numpy.array([float]), numpy.array([float])])

    def test_add1(self):
        self.run_test("def np_add1(a, b): return a + b + a", numpy.ones(10), numpy.ones(10), np_add1=[numpy.array([float]), numpy.array([float])])

    def test_add2(self):
        self.run_test("def np_add2(a, b): return a + b + 1", numpy.ones(10), numpy.ones(10), np_add2=[numpy.array([float]), numpy.array([float])])

    def test_add3(self):
        self.run_test("def np_add3(a, b): return 1. + a + b + 1.", numpy.ones(10), numpy.ones(10), np_add3=[numpy.array([float]), numpy.array([float])])

    def test_add4(self):
        self.run_test("def np_add4(a, b): return ( a + b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_add4=[numpy.array([float]), numpy.array([float])])

    def test_add5(self):
        self.run_test("def np_add5(a, b): return (-a) + (-b)", numpy.ones(10), numpy.ones(10), np_add5=[numpy.array([float]), numpy.array([float])])

    def test_sub0(self):
        self.run_test("def np_sub0(a, b): return a - b", numpy.ones(10), numpy.ones(10), np_sub0=[numpy.array([float]), numpy.array([float])])

    def test_sub1(self):
        self.run_test("def np_sub1(a, b): return a - b - a", numpy.ones(10), numpy.ones(10), np_sub1=[numpy.array([float]), numpy.array([float])])

    def test_sub2(self):
        self.run_test("def np_sub2(a, b): return a - b - 1", numpy.ones(10), numpy.ones(10), np_sub2=[numpy.array([float]), numpy.array([float])])

    def test_sub3(self):
        self.run_test("def np_sub3(a, b): return 1. - a - b - 1.", numpy.ones(10), numpy.ones(10), np_sub3=[numpy.array([float]), numpy.array([float])])

    def test_sub4(self):
        self.run_test("def np_sub4(a, b): return ( a - b ) - ( a - b )", numpy.ones(10), numpy.ones(10), np_sub4=[numpy.array([float]), numpy.array([float])])

    def test_addsub0(self):
        self.run_test("def np_addsub0(a, b): return a - b + a", numpy.ones(10), numpy.ones(10), np_addsub0=[numpy.array([float]), numpy.array([float])])

    def test_addsub1(self):
        self.run_test("def np_addsub1(a, b): return a + b - a", numpy.ones(10), numpy.ones(10), np_addsub1=[numpy.array([float]), numpy.array([float])])

    def test_addsub2(self):
        self.run_test("def np_addsub2(a, b): return a + b - 1", numpy.ones(10), numpy.ones(10), np_addsub2=[numpy.array([float]), numpy.array([float])])

    def test_addsub3(self):
        self.run_test("def np_addsub3(a, b): return 1. + a - b + 1.", numpy.ones(10), numpy.ones(10), np_addsub3=[numpy.array([float]), numpy.array([float])])

    def test_addsub4(self):
        self.run_test("def np_addsub4(a, b): return ( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addsub4=[numpy.array([float]), numpy.array([float])])

    def test_addcossub0(self):
        self.run_test("def np_addcossub0(a, b): from numpy import cos ; return a - b + cos(a)", numpy.ones(10), numpy.ones(10), np_addcossub0=[numpy.array([float]), numpy.array([float])])

    def test_addcossub1(self):
        self.run_test("def np_addcossub1(a, b): from numpy import cos ; return a + cos(b - a)", numpy.ones(10), numpy.ones(10), np_addcossub1=[numpy.array([float]), numpy.array([float])])

    def test_addcossub2(self):
        self.run_test("def np_addcossub2(a, b): from numpy import cos ; return a + cos(b - 1)", numpy.ones(10), numpy.ones(10), np_addcossub2=[numpy.array([float]), numpy.array([float])])

    def test_addcossub3(self):
        self.run_test("def np_addcossub3(a, b): from numpy import cos ; return cos(1. + a - b + cos(1.))", numpy.ones(10), numpy.ones(10), np_addcossub3=[numpy.array([float]), numpy.array([float])])

    def test_addcossub4(self):
        self.run_test("def np_addcossub4(a, b): from numpy import cos ; return cos( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addcossub4=[numpy.array([float]), numpy.array([float])])

    def test_sin0(self):
        self.run_test("def np_sin0(a, b): from numpy import sin ; return sin(a) + b", numpy.ones(10), numpy.ones(10), np_sin0=[numpy.array([float]), numpy.array([float])])

    def test_tan0(self):
        self.run_test("def np_tan0(a, b): from numpy import tan ; return tan(a - b)", numpy.ones(10), numpy.ones(10), np_tan0=[numpy.array([float]), numpy.array([float])])

    def test_arccos0(self):
        self.run_test("def np_arccos0(a, b): from numpy import arccos ; return arccos(a - b) + 1", numpy.ones(10), numpy.ones(10), np_arccos0=[numpy.array([float]), numpy.array([float])])

    def test_arcsin0(self):
        self.run_test("def np_arcsin0(a, b): from numpy import arcsin ; return arcsin(a + b - a + -b) + 1.", numpy.ones(10), numpy.ones(10), np_arcsin0=[numpy.array([float]), numpy.array([float])])

    def test_arctan0(self):
        self.run_test("def np_arctan0(a, b): from numpy import arctan ; return arctan(a -0.5) + a", numpy.ones(10), numpy.ones(10), np_arctan0=[numpy.array([float]), numpy.array([float])])

    def test_arctan20(self):
        self.run_test("def np_arctan20(a, b): from numpy import arctan2 ; return b - arctan2(a , b)", numpy.ones(10), numpy.ones(10), np_arctan20=[numpy.array([float]), numpy.array([float])])

    def test_cos1(self):
        self.run_test("def np_cos1(a): from numpy import cos; return cos(a)", 5, np_cos1=[int])

    def test_sin1(self):
        self.run_test("def np_sin1(a): from numpy import sin; return sin(a)", 0.5, np_sin1=[float])

    def test_tan1(self):
        self.run_test("def np_tan1(a): from numpy import tan; return tan(a)", 0.5, np_tan1=[float])

    def test_arccos1(self):
        self.run_test("def np_arccos1(a): from numpy import arccos ; return arccos(a)", 1, np_arccos1=[int])

    def test_arcsin1(self):
        self.run_test("def np_arcsin1(a): from numpy import arcsin ; return arcsin(a)", 1, np_arcsin1=[int])

    def test_arctan1(self):
        self.run_test("def np_arctan1(a): from numpy import arctan ; return arctan(a)", 0.5, np_arctan1=[float])

    def test_arctan21(self):
        self.run_test("def np_arctan21(a): from numpy import arctan2 ; b = .5 ; return arctan2(a , b)", 1., np_arctan21=[float])

    def test_negative_mod(self):
        self.run_test("def np_negative_mod(a): return a % 5", numpy.array([-1, -5, -2, 7]), np_negative_mod=[numpy.array([int])])

    def test_binary_op_list0(self):
        self.run_test("def np_binary_op_list0(n): return n + [1,2,3]", numpy.array([4,5,6]), np_binary_op_list0=[numpy.array([int])])

    def test_binary_op_list1(self):
        self.run_test("def np_binary_op_list1(n): return [1,2,3] + n", numpy.array([4,5,6]), np_binary_op_list1=[numpy.array([int])])

    def test_binary_op_list2(self):
        self.run_test("def np_binary_op_list2(n): return [[1],[2],[3]] + n", numpy.array([[4],[5],[6]]), np_binary_op_list2=[numpy.array([[int]])])

    def test_binary_op_array0(self):
        self.run_test("def np_binary_op_array0(n): return n + (1,2,3)", numpy.array([4,5,6]), np_binary_op_array0=[numpy.array([int])])

    def test_binary_op_array1(self):
        self.run_test("def np_binary_op_array1(n): return (1,2,3) + n", numpy.array([4,5,6]), np_binary_op_array1=[numpy.array([int])])

    def test_binary_op_array2(self):
        self.run_test("def np_binary_op_array2(n): return ((1,2,3),) + n", numpy.array([[4,5,6]]), np_binary_op_array2=[numpy.array([[int]])])

    def test_round_method(self):
        self.run_test("def np_round_method(a): return a.round()", numpy.array([[4.3,5.5,6.1]]), np_round_method=[numpy.array([[float]])])

    def test_list_imag0(self):
        self.run_test("def list_imag0(a): import numpy ; return numpy.imag(a)", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_imag0=[numpy.array([complex])])

    def test_list_imag1(self):
        self.run_test("def list_imag1(a): import numpy ; numpy.imag(a)[0] = 1; return a", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_imag1=[numpy.array([complex])])

    def test_list_real0(self):
        self.run_test("def list_real0(a): import numpy ; return numpy.real(a)", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_real0=[numpy.array([complex])])

    def test_list_real1(self):
        self.run_test("def list_real1(a): import numpy ; numpy.real(a)[0] = 1; return a", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_real1=[numpy.array([complex])])


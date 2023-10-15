""" Tests for part of the numpy module. """

import unittest

import numpy
from pythran.typing import List, NDArray, Tuple

from pythran.tests import TestEnv


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
        self.run_test("def np_dot1(x): from numpy import dot ; y = [2, 3] ; return dot(x,y)", [2, 3], np_dot1=[List[int]])

    def test_dot2(self):
        self.run_test("def np_dot2(x): from numpy import dot ; y = [2j, 3j] ; return dot(x,y)", [2j, 3j], np_dot2=[List[complex]])

    def test_dot3(self):
        self.run_test("def np_dot3(x): from numpy import array ; y = array([2, 3]) ; return y.dot(x+x)", numpy.array([2, 3]), np_dot3=[NDArray[int,:]])

    def test_dot4a(self):
        self.run_test("def np_dot4a(x): from numpy import dot ; y = [2, 3] ; return dot(x,y)", numpy.array([2, 3]), np_dot4a=[NDArray[int,:]])

    def test_dot4b(self):
        self.run_test("def np_dot4b(x): from numpy import dot ; y = [2., 3.] ; return dot(x[1:],y)", numpy.array([2, 3, 4], dtype=numpy.float32), np_dot4b=[NDArray[numpy.float32,:]])

    def test_dot4c(self):
        self.run_test("def np_dot4c(x): from numpy import dot ; return dot(x[1:],x[:-1])", numpy.array([2, 3, 4], dtype=numpy.float64), np_dot4c=[NDArray[float,:]])

    def test_dot4d(self):
        self.run_test("def np_dot4d(x): from numpy import dot ; return dot(x, x)", numpy.array([2j, 3j, 4.]), np_dot4d=[NDArray[complex,:]])

    def test_dot4e(self):
        self.run_test("def np_dot4e(x): from numpy import dot ; y = (2.j, 3.j) ; return dot(x[:-1],y)", numpy.array([2.j, 3.j, 4.j], dtype=numpy.complex64), np_dot4e=[NDArray[numpy.complex64,:]])

    def test_dot4f(self):
        self.run_test("def np_dot4f(x): from numpy import dot ; y = (1., 2., 3.) ; return dot(2*x, y)", numpy.array([2., 3., 4.]), np_dot4f=[NDArray[float,:]])

    def test_dot5(self):
        """ Check for dgemm version of dot. """
        self.run_test("""
        def np_dot5(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [[1., 2., 3.], [4., 5., 6.], [7., 8., 9.]],
                      [[10., 11., 12.], [13., 14., 15.], [16., 17., 18.]],
                      np_dot5=[List[List[float]], List[List[float]]])

    def test_dot6(self):
        """ Check for dot with "no blas type". """
        self.run_test("""
        def np_dot6(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9).reshape(3, 3),
                      numpy.arange(9, 18).reshape(3, 3),
                      np_dot6=[NDArray[int,:,:], NDArray[int,:,:]])

    def test_dot7(self):
        """ Check for dgemm version of dot with rectangular shape. """
        self.run_test("""
        def np_dot7(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [[1., 2., 3.], [4., 5., 6.], [7., 8., 9.]],
                      [[10., 11., 12.], [13., 14., 15.], [16., 17., 18.]],
                      np_dot7=[List[List[float]], List[List[float]]])

    def test_dot8(self):
        """ Check for dot with "no blas type" with rectangulare shape. """
        self.run_test("""
        def np_dot8(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6).reshape(3, 2),
                      numpy.arange(6, 12).reshape(2, 3),
                      np_dot8=[NDArray[int,:,:], NDArray[int,:,:]])

    def test_dot9(self):
        """ Check for gemv version of dot. """
        self.run_test("""
        def np_dot9(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9.).reshape(3, 3).tolist(),
                      [float(x) for x in range(9, 12)],
                      np_dot9=[List[List[float]], List[float]])

    def test_dot10(self):
        """ Check for dot gemv with "no blas type". """
        self.run_test("""
        def np_dot10(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9).reshape(3, 3),
                      numpy.arange(9, 12),
                      np_dot10=[NDArray[int,:,:], NDArray[int,:]])

    def test_dot11(self):
        """ Check for gemv version of dot with rectangular shape. """
        self.run_test("""
        def np_dot11(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6.).reshape(3, 2).tolist(),
                      [float(x) for x  in range(6, 8)],
                      np_dot11=[List[List[float]], List[float]])

    def test_dot12(self):
        """ Check for dot gemv with "no blas type" with rectangulare shape. """
        self.run_test("""
        def np_dot12(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6).reshape(3, 2),
                      numpy.arange(6, 8),
                      np_dot12=[NDArray[int,:,:], NDArray[int,:]])

    def test_dot12b(self):
        """ Check for dot gemv transposed. """
        self.run_test("""
        def np_dot12b(x, y):
            from numpy import dot
            return dot(x.T,y)""",
                      numpy.arange(6.).reshape(2, 3),
                      numpy.arange(6, 8.),
                      np_dot12b=[NDArray[float,:,:], NDArray[float,:]])

    def test_dot13(self):
        """ Check for gevm version of dot. """
        self.run_test("""
        def np_dot13(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [float(x) for x in range(9, 12)],
                      numpy.arange(9.).reshape(3, 3).tolist(),
                      np_dot13=[List[float], List[List[float]]])

    def test_dot14(self):
        """ Check for dot gevm with "no blas type". """
        self.run_test("""
        def np_dot14(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(9, 12),
                      numpy.arange(9).reshape(3, 3),
                      np_dot14=[NDArray[int,:], NDArray[int,:,:]])

    def test_dot14b(self):
        """ Check for dot gevm trabsposed. """
        self.run_test("""
        def np_dot14b(x, y):
            from numpy import dot
            return dot(x,y.T)""",
                      numpy.arange(9, 12.),
                      numpy.arange(12.).reshape(4, 3),
                      np_dot14b=[NDArray[float,:], NDArray[float,:,:]])

    def test_dot15(self):
        """ Check for gevm version of dot with rectangular shape. """
        self.run_test("""
        def np_dot15(x, y):
            from numpy import dot
            return dot(x,y)""",
                      [float(x) for x in range(6, 9)],
                      numpy.arange(6.).reshape(3, 2).tolist(),
                      np_dot15=[List[float], List[List[float]]])


    def test_dot16(self):
        """ Check for dot gevm with "no blas type" with rectangular shape. """
        self.run_test("""
        def np_dot16(x, y):
            from numpy import dot
            return dot(x,y)""",
                      numpy.arange(6.).reshape(2, 3),
                      numpy.arange(18.).reshape(3,6),
                      np_dot16=[NDArray[float,:,:], NDArray[float,:,:]])


    def test_dot17(self):
        """ Check for dot gevm with "no blas type" with rectangular shape,
        first arg transposed."""
        self.run_test("""
        def np_dot17(x, y):
            from numpy import dot
            return dot(x.T,y)""",
                      numpy.arange(6.).reshape(3, 2),
                      numpy.arange(18.).reshape(3,6),
                      np_dot17=[NDArray[float,:,:], NDArray[float,:,:]])



    def test_dot18(self):
        """ Check for dot gevm with "no blas type" with rectangular shape,
        second arg transposed"""
        self.run_test("""
        def np_dot18(x, y):
            from numpy import dot
            return dot(x,y.T)""",
                      numpy.arange(6.).reshape(2, 3),
                      numpy.arange(18.).reshape(6,3),
                      np_dot18=[NDArray[float,:,:], NDArray[float,:,:]])



    def test_dot19(self):
        """ Check for dot gevm with "no blas type" with rectangular shape,
        both args transposed"""
        self.run_test("""
        def np_dot19(x, y):
            from numpy import dot
            return dot(x.T,y.T)""",
                      numpy.array(numpy.arange(6.).reshape(3, 2)),
                      numpy.array(numpy.arange(18.).reshape(6,3)),
                      np_dot19=[NDArray[float,:,:], NDArray[float,:,:]])

    def test_dot20(self):
        ''' Mixed type: matrix x matrix'''
        self.run_test("""
        def np_dot20(x, y):
            from numpy import dot
            return dot(x, y)""",
                      numpy.array(numpy.arange(6.).reshape(2, 3),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(18.).reshape(3,6),
                                  dtype=numpy.float64),
                      np_dot20=[NDArray[numpy.float32,:,:],
                                NDArray[numpy.float64,:,:]])

    def test_dot21(self):
        ''' Mixed type: matrix x vector'''
        self.run_test("""
        def np_dot21(x, y):
            from numpy import dot
            return dot(x, y)""",
                      numpy.array(numpy.arange(6.).reshape(2, 3),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(3.).reshape(3),
                                  dtype=numpy.float64),
                      np_dot21=[NDArray[numpy.float32,:,:],
                                NDArray[numpy.float64,:]])

    def test_dot22(self):
        ''' Mixed type: matrix x vector'''
        self.run_test("""
        def np_dot22(x, y):
            from numpy import dot
            return dot(y, x)""",
                      numpy.array(numpy.arange(6.).reshape(3, 2),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(3.).reshape(3),
                                  dtype=numpy.float64),
                      np_dot22=[NDArray[numpy.float32,:,:],
                                NDArray[numpy.float64,:]])

    def test_dot23(self):
        ''' Nd x 1d, N > 2'''
        self.run_test("""
        def np_dot23(x, y):
            from numpy import dot
            return dot(x, y)""",
                      numpy.array(numpy.arange(24.).reshape(4, 3, 2),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(2.).reshape(2),
                                  dtype=numpy.float64),
                      np_dot23=[NDArray[numpy.float32,:,:,:],
                                NDArray[numpy.float64,:]])

    @unittest.skip("not implemented yet")
    def test_dot24(self):
        ''' Nd x 1d, N > 2'''
        self.run_test("""
        def np_dot24(x, y):
            from numpy import dot
            return dot(x, y)""",
                      numpy.array(numpy.arange(24.).reshape(4, 3, 2),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(24.).reshape(2,3,2,2),
                                  dtype=numpy.float64),
                      np_dot24=[NDArray[numpy.float32,:,:,:],
                                NDArray[numpy.float64,:,:,:,:]])

    def test_vdot0(self):
        self.run_test("""
        def np_vdot0(x, y):
            from numpy import vdot
            return vdot(x, y)""",
                      numpy.array(numpy.arange(6.).reshape(3, 2),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(6.).reshape(6),
                                  dtype=numpy.float32),
                      np_vdot0=[NDArray[numpy.float32,:,:],
                                NDArray[numpy.float32,:]])

    def test_vdot1(self):
        self.run_test("""
        def np_vdot1(x, y):
            from numpy import vdot
            return vdot(x, y)""",
                      numpy.array(numpy.arange(6.).reshape(3, 2),
                                  dtype=numpy.float32),
                      numpy.array(numpy.arange(6.).reshape(6),
                                  dtype=numpy.float64),
                      np_vdot1=[NDArray[numpy.float32,:,:],
                                NDArray[numpy.float64,:]])

    def test_vdot2(self):
        self.run_test("""
        def np_vdot2(x, y):
            from numpy import vdot
            return vdot(x, y)""",
                      numpy.array(numpy.arange(6.).reshape(3, 2),
                                  dtype=numpy.complex128),
                      numpy.array(numpy.arange(6.).reshape(6),
                                  dtype=numpy.complex128),
                      np_vdot2=[NDArray[numpy.complex128,:,:],
                                NDArray[numpy.complex128,:]])

    def test_vdot3(self):
        self.run_test("""
        def np_vdot3(x, y):
            from numpy import vdot
            return vdot(x, y)""",
                      numpy.array(numpy.arange(6.),
                                  dtype=numpy.complex128),
                      numpy.array(numpy.arange(6.),
                                  dtype=numpy.complex128) * -1j,
                      np_vdot3=[NDArray[numpy.complex128,:],
                                NDArray[numpy.complex128,:]])

    def test_digitize0(self):
        self.run_test("def np_digitize0(x): from numpy import array, digitize ; bins = array([0.0, 1.0, 2.5, 4.0, 10.0]) ; return digitize(x, bins)", numpy.array([0.2, 6.4, 3.0, 1.6]), np_digitize0=[NDArray[float,:]])

    def test_digitize1(self):
        self.run_test("def np_digitize1(x): from numpy import array, digitize ; bins = array([ 10.0, 4.0, 2.5, 1.0, 0.0]) ; return digitize(x, bins)", numpy.array([0.2, 6.4, 3.0, 1.6]), np_digitize1=[NDArray[float,:]])

    def test_diff0(self):
        self.run_test("def np_diff0(x): from numpy import diff; return diff(x)", numpy.array([1, 2, 4, 7, 0]), np_diff0=[NDArray[int,:]])

    def test_diff1(self):
        self.run_test("def np_diff1(x): from numpy import diff; return diff(x,2)", numpy.array([1, 2, 4, 7, 0]), np_diff1=[NDArray[int,:]])

    def test_diff2(self):
        self.run_test("def np_diff2(x): from numpy import diff; return diff(x)", numpy.array([[1, 3, 6, 10], [0, 5, 6, 8]]), np_diff2=[NDArray[int,:,:]])

    def test_diff3(self):
        self.run_test("def np_diff3(x): from numpy import diff; return diff(x,2)", numpy.array([[1, 3, 6, 10], [0, 5, 6, 8]]), np_diff3=[NDArray[int,:,:]])

    def test_diff4(self):
        self.run_test("def np_diff4(x): from numpy import diff; return diff(x + x)", numpy.array([1, 2, 4, 7, 0]), np_diff4=[NDArray[int,:]])

    def test_diff5(self):
        self.run_test("def np_diff5(x): from numpy import diff; return diff(x + x, 2, axis=0)", numpy.arange(100).reshape(10, 10)*2, np_diff5=[NDArray[int,:,:]])

    def test_diff6(self):
        self.run_test("def np_diff6(x): from numpy import diff; return diff(x, axis=0)", numpy.arange(100).reshape(10, 10)*2, np_diff6=[NDArray[int,:,:]])

    def test_diff7(self):
        self.run_test("def np_diff7(x): from numpy import diff; return diff(x, axis=0)", numpy.arange(300).reshape(3, 10, 10)*2, np_diff7=[NDArray[int,:,:,:]])

    def test_diff8(self):
        self.run_test("def np_diff8(x): from numpy import diff; return diff(x, axis=1)", numpy.arange(300).reshape(3, 10, 10)*2, np_diff8=[NDArray[int,:,:,:]])

    def test_diff9(self):
        self.run_test("def np_diff9(x): from numpy import diff; return diff(x, axis=2)", numpy.arange(300).reshape(3, 10, 10)*2, np_diff9=[NDArray[int,:,:,:]])

    def test_trace0(self):
        self.run_test("def np_trace0(x): return x.trace()", numpy.arange(9).reshape(3,3), np_trace0=[NDArray[int,:,:]])

    def test_trace1(self):
        self.run_test("def np_trace1(x): from numpy import trace; return trace(x, 1)", numpy.arange(12).reshape(3,4), np_trace1=[NDArray[int,:,:]])

    def test_trace2(self):
        self.run_test("def np_trace2(x): from numpy import trace; return trace(x, 1)", numpy.arange(12).reshape(3,4), np_trace2=[NDArray[int,:,:]])

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
    return trim_zeros(x)""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros0=[NDArray[int,:]])

    def test_trim_zeros1(self):
        self.run_test("""
def np_trim_zeros1(x):
    from numpy import array, trim_zeros
    return trim_zeros(x, "f")""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros1=[NDArray[int,:]])

    def test_trim_zeros2(self):
        self.run_test("""
def np_trim_zeros2(x):
    from numpy import trim_zeros
    return trim_zeros(x, "b")""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros2=[NDArray[int,:]])

    def test_triu0(self):
        self.run_test("def np_triu0(x): from numpy import triu; return triu(x)", numpy.arange(12).reshape(3,4), np_triu0=[NDArray[int,:,:]])

    def test_triu1(self):
        self.run_test("def np_triu1(x): from numpy import triu; return triu(x, 1)", numpy.arange(12).reshape(3,4), np_triu1=[NDArray[int,:,:]])

    def test_triu2(self):
        self.run_test("def np_triu2(x): from numpy import triu; return triu(x, -1)", numpy.arange(12).reshape(3,4), np_triu2=[NDArray[int,:,:]])

    def test_tril0(self):
        self.run_test("def np_tril0(x): from numpy import tril; return tril(x)", numpy.arange(12).reshape(3,4), np_tril0=[NDArray[int,:,:]])

    def test_tril1(self):
        self.run_test("def np_tril1(x): from numpy import tril; return tril(x, 1)", numpy.arange(12).reshape(3,4), np_tril1=[NDArray[int,:,:]])

    def test_tril2(self):
        self.run_test("def np_tril2(x): from numpy import tril; return tril(x, -1)", numpy.arange(12).reshape(3,4), np_tril2=[NDArray[int,:,:]])

    def test_union1d(self):
        self.run_test("def np_union1d(x): from numpy import arange, union1d ; y = arange(1,4); return union1d(x, y)", numpy.arange(-1,2), np_union1d=[NDArray[int,:]])

    def test_unique0(self):
        self.run_test("def np_unique0(x): from numpy import unique ; return unique(x)", numpy.array([1,1,2,2,2,1,5]), np_unique0=[NDArray[int,:]])

    def test_unique1(self):
        self.run_test("def np_unique1(x): from numpy import unique ; return unique(x)", numpy.array([[1,2,2],[2,1,5]]), np_unique1=[NDArray[int,:,:]])

    def test_unique2(self):
        self.run_test("def np_unique2(x): from numpy import unique ; return unique(x, True)", numpy.array([1,1,2,2,2,1,5]), np_unique2=[NDArray[int,:]])

    def test_unique3(self):
        self.run_test("def np_unique3(x): from numpy import unique ; return unique(x, True, True)", numpy.array([1,1,2,2,2,1,5]), np_unique3=[NDArray[int,:]])

    def test_unique4(self):
        self.run_test("def np_unique4(x): from numpy import unique ; return unique(x, True, True, True)", numpy.array([1,1,2,2,2,1,5]), np_unique4=[NDArray[int,:]])

    def test_unique5(self):
        self.run_test("def np_unique5(x): from numpy import unique ; return unique(x, False)", numpy.array([1,1,2,2,2,1,5]), np_unique5=[NDArray[int,:]])

    def test_unique6(self):
        self.run_test("def np_unique6(x): from numpy import unique ; return unique(x, False, True)", numpy.array([1,1,2,2,2,1,5]), np_unique6=[NDArray[int,:]])

    def test_unique7(self):
        self.run_test("def np_unique7(x): from numpy import unique ; return unique(x, False, False)", numpy.array([1,1,2,2,2,1,5]), np_unique7=[NDArray[int,:]])

    def test_unique8(self):
        self.run_test("def np_unique8(x): from numpy import unique ; return unique(x, return_inverse=True)", numpy.array([1,1,2,2,2,1,5]), np_unique8=[NDArray[int,:]])

    def test_unique9(self):
        self.run_test("def np_unique9(x): from numpy import unique ; return unique(x, True, False)", numpy.array([1,1,2,2,2,1,5]), np_unique9=[NDArray[int,:]])

    def test_unique10(self):
        self.run_test("def np_unique10(x): from numpy import unique ; return unique(x, True, True, False)", numpy.array([1,1,2,2,2,1,5]), np_unique10=[NDArray[int,:]])

    def test_unique11(self):
        self.run_test("def np_unique11(x): from numpy import unique ; return unique(x, True, False, False)", numpy.array([1,1,2,2,2,1,5]), np_unique11=[NDArray[int,:]])

    def test_unique12(self):
        self.run_test("def np_unique12(x): from numpy import unique ; return unique(x, True, False, True)", numpy.array([1,1,2,2,2,1,5]), np_unique12=[NDArray[int,:]])

    def test_unique13(self):
        self.run_test("def np_unique13(x): from numpy import unique ; return unique(x, False, True, False)", numpy.array([1,1,2,2,2,1,5]), np_unique13=[NDArray[int,:]])

    def test_unique14(self):
        self.run_test("def np_unique14(x): from numpy import unique ; return unique(x, False, True, True)", numpy.array([1,1,2,2,2,1,5]), np_unique14=[NDArray[int,:]])

    def test_unique15(self):
        self.run_test("def np_unique15(x): from numpy import unique ; return unique(x, False, False, False)", numpy.array([1,1,2,2,2,1,5]), np_unique15=[NDArray[int,:]])

    def test_unique16(self):
        self.run_test("def np_unique16(x): from numpy import unique ; return unique(x, False, False, True)", numpy.array([1,1,2,2,2,1,5]), np_unique16=[NDArray[int,:]])

    def test_unique17(self):
        self.run_test("def np_unique17(x): from numpy import unique ; return unique(x, return_counts=1)", numpy.array([1,1,2,2,2,1,5]), np_unique17=[NDArray[int,:]])

    def test_unwrap0(self):
        self.run_test("def np_unwrap0(x): from numpy import unwrap, pi ; x[:3] += 2.6*pi; return unwrap(x)", numpy.arange(6, dtype=float), np_unwrap0=[NDArray[float,:]])

    def test_unwrap1(self):
        self.run_test("def np_unwrap1(x): from numpy import unwrap, pi ; x[:3] += 2*pi; return unwrap(x, 4)", numpy.arange(6, dtype=float), np_unwrap1=[NDArray[float,:]])

    def test_unwrap2(self):
        self.run_test("def np_unwrap2(x): from numpy import unwrap, pi ; x[:3] -= 2*pi; return unwrap(x, 4)", numpy.arange(6, dtype=float), np_unwrap2=[NDArray[float,:]])

    def test_unravel_index_0(self):
        self.run_test("def np_unravel_index0(x, y): from numpy import unravel_index; return unravel_index(x, y)", 1621, (6, 7, 8, 9), np_unravel_index0=[int, Tuple[int, int, int, int]])

    def test_unravel_index_1(self):
        self.run_test("def np_unravel_index1(x, y): from numpy import unravel_index; return unravel_index(x, y, 'F')", 1621, (6, 7, 8, 9), np_unravel_index1=[int, Tuple[int, int, int, int]])

    def test_copyto_0(self):
        self.run_test("def np_copyto0(x, y): from numpy import copyto; copyto(x, y); return x",
                      numpy.array([1,2]), numpy.array([3,4]),
                      np_copyto0=[NDArray[int, :], NDArray[int, :]])

    def test_copyto_1(self):
        self.run_test("def np_copyto1(x, y): from numpy import copyto; copyto(x, y); return x",
                      numpy.array([[1,2], [7, 8]]), numpy.array([3,4]),
                      np_copyto1=[NDArray[int, :, :], NDArray[int, :]])

    def test_copyto_2(self):
        self.run_test("def np_copyto2(x, y): from numpy import copyto; return copyto(x.T, y), x",
                      numpy.array([[1,2], [7, 8]]), numpy.array([3,4]),
                      np_copyto2=[NDArray[int, :, :], NDArray[int, :]])

    def test_numpy_pow0(self):
        self.run_test('def numpy_pow0(a): return a ** 2',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_pow0=[NDArray[int,:,:]])

    def test_numpy_pow1(self):
        self.run_test('def numpy_pow1(a): return a ** 2',
                      numpy.arange(100, dtype=float).reshape((10, 10)),
                      numpy_pow1=[NDArray[float,:,:]])

    def test_numpy_pow2(self):
        self.run_test('def numpy_pow2(a): return a ** 2.2',
                      numpy.arange(100, dtype=float).reshape((10, 10)),
                      numpy_pow2=[NDArray[float,:,:]])

    def test_numpy_pow3(self):
        self.run_test('def numpy_pow3(a): return a ** -0.2',
                      numpy.arange(100, dtype=int),
                      numpy_pow3=[NDArray[int,:]])

    def test_add0(self):
        self.run_test("def np_add0(a, b): return a + b", numpy.ones(10), numpy.ones(10), np_add0=[NDArray[float,:], NDArray[float,:]])

    def test_add1(self):
        self.run_test("def np_add1(a, b): return a + b + a", numpy.ones(10), numpy.ones(10), np_add1=[NDArray[float,:], NDArray[float,:]])

    def test_add2(self):
        self.run_test("def np_add2(a, b): return a + b + 1", numpy.ones(10), numpy.ones(10), np_add2=[NDArray[float,:], NDArray[float,:]])

    def test_add3(self):
        self.run_test("def np_add3(a, b): return 1. + a + b + 1.", numpy.ones(10), numpy.ones(10), np_add3=[NDArray[float,:], NDArray[float,:]])

    def test_add4(self):
        self.run_test("def np_add4(a, b): return ( a + b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_add4=[NDArray[float,:], NDArray[float,:]])

    def test_add5(self):
        self.run_test("def np_add5(a, b): return (-a) + (-b)", numpy.ones(10), numpy.ones(10), np_add5=[NDArray[float,:], NDArray[float,:]])

    def test_sub0(self):
        self.run_test("def np_sub0(a, b): return a - b", numpy.ones(10), numpy.ones(10), np_sub0=[NDArray[float,:], NDArray[float,:]])

    def test_sub1(self):
        self.run_test("def np_sub1(a, b): return a - b - a", numpy.ones(10), numpy.ones(10), np_sub1=[NDArray[float,:], NDArray[float,:]])

    def test_sub2(self):
        self.run_test("def np_sub2(a, b): return a - b - 1", numpy.ones(10), numpy.ones(10), np_sub2=[NDArray[float,:], NDArray[float,:]])

    def test_sub3(self):
        self.run_test("def np_sub3(a, b): return 1. - a - b - 1.", numpy.ones(10), numpy.ones(10), np_sub3=[NDArray[float,:], NDArray[float,:]])

    def test_sub4(self):
        self.run_test("def np_sub4(a, b): return ( a - b ) - ( a - b )", numpy.ones(10), numpy.ones(10), np_sub4=[NDArray[float,:], NDArray[float,:]])

    def test_addsub0(self):
        self.run_test("def np_addsub0(a, b): return a - b + a", numpy.ones(10), numpy.ones(10), np_addsub0=[NDArray[float,:], NDArray[float,:]])

    def test_addsub1(self):
        self.run_test("def np_addsub1(a, b): return a + b - a", numpy.ones(10), numpy.ones(10), np_addsub1=[NDArray[float,:], NDArray[float,:]])

    def test_addsub2(self):
        self.run_test("def np_addsub2(a, b): return a + b - 1", numpy.ones(10), numpy.ones(10), np_addsub2=[NDArray[float,:], NDArray[float,:]])

    def test_addsub3(self):
        self.run_test("def np_addsub3(a, b): return 1. + a - b + 1.", numpy.ones(10), numpy.ones(10), np_addsub3=[NDArray[float,:], NDArray[float,:]])

    def test_addsub4(self):
        self.run_test("def np_addsub4(a, b): return ( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addsub4=[NDArray[float,:], NDArray[float,:]])

    def test_addcossub0(self):
        self.run_test("def np_addcossub0(a, b): from numpy import cos ; return a - b + cos(a)", numpy.ones(10), numpy.ones(10), np_addcossub0=[NDArray[float,:], NDArray[float,:]])

    def test_addcossub1(self):
        self.run_test("def np_addcossub1(a, b): from numpy import cos ; return a + cos(b - a)", numpy.ones(10), numpy.ones(10), np_addcossub1=[NDArray[float,:], NDArray[float,:]])

    def test_addcossub2(self):
        self.run_test("def np_addcossub2(a, b): from numpy import cos ; return a + cos(b - 1)", numpy.ones(10), numpy.ones(10), np_addcossub2=[NDArray[float,:], NDArray[float,:]])

    def test_addcossub3(self):
        self.run_test("def np_addcossub3(a, b): from numpy import cos ; return cos(1. + a - b + cos(1.))", numpy.ones(10), numpy.ones(10), np_addcossub3=[NDArray[float,:], NDArray[float,:]])

    def test_addcossub4(self):
        self.run_test("def np_addcossub4(a, b): from numpy import cos ; return cos( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addcossub4=[NDArray[float,:], NDArray[float,:]])

    def test_sin0(self):
        self.run_test("def np_sin0(a, b): from numpy import sin ; return sin(a) + b", numpy.ones(10), numpy.ones(10), np_sin0=[NDArray[float,:], NDArray[float,:]])

    def test_tan0(self):
        self.run_test("def np_tan0(a, b): from numpy import tan ; return tan(a - b)", numpy.ones(10), numpy.ones(10), np_tan0=[NDArray[float,:], NDArray[float,:]])

    def test_arccos0(self):
        self.run_test("def np_arccos0(a, b): from numpy import arccos ; return arccos(a - b) + 1", numpy.ones(10), numpy.ones(10), np_arccos0=[NDArray[float,:], NDArray[float,:]])

    def test_arcsin0(self):
        self.run_test("def np_arcsin0(a, b): from numpy import arcsin ; return arcsin(a + b - a + -b) + 1.", numpy.ones(10), numpy.ones(10), np_arcsin0=[NDArray[float,:], NDArray[float,:]])

    def test_arctan0(self):
        self.run_test("def np_arctan0(a, b): from numpy import arctan ; return arctan(a -0.5) + a", numpy.ones(10), numpy.ones(10), np_arctan0=[NDArray[float,:], NDArray[float,:]])

    def test_arctan20(self):
        self.run_test("def np_arctan20(a, b): from numpy import arctan2 ; return b - arctan2(a , b)", numpy.ones(10), numpy.ones(10), np_arctan20=[NDArray[float,:], NDArray[float,:]])

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
        self.run_test("def np_negative_mod(a): return a % 5", numpy.array([-1, -5, -2, 7]), np_negative_mod=[NDArray[int,:]])

    def test_binary_op_list0(self):
        self.run_test("def np_binary_op_list0(n): return n + [1,2,3]", numpy.array([4,5,6]), np_binary_op_list0=[NDArray[int,:]])

    def test_binary_op_list1(self):
        self.run_test("def np_binary_op_list1(n): return [1,2,3] + n", numpy.array([4,5,6]), np_binary_op_list1=[NDArray[int,:]])

    def test_binary_op_list2(self):
        self.run_test("def np_binary_op_list2(n): return [[1],[2],[3]] + n", numpy.array([[4],[5],[6]]), np_binary_op_list2=[NDArray[int,:,:]])

    def test_binary_op_array0(self):
        self.run_test("def np_binary_op_array0(n): return n + (1,2,3)", numpy.array([4,5,6]), np_binary_op_array0=[NDArray[int,:]])

    def test_binary_op_array1(self):
        self.run_test("def np_binary_op_array1(n): return (1,2,3) + n", numpy.array([4,5,6]), np_binary_op_array1=[NDArray[int,:]])

    def test_binary_op_array2(self):
        self.run_test("def np_binary_op_array2(n): return ((1,2,3),) + n", numpy.array([[4,5,6]]), np_binary_op_array2=[NDArray[int,:,:]])

    def test_round_method(self):
        self.run_test("def np_round_method(a): return a.round()", numpy.array([[4.3,5.5,6.1]]), np_round_method=[NDArray[float,:,:]])

    def test_list_imag0(self):
        self.run_test("def list_imag0(a): import numpy ; return numpy.imag(a)", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_imag0=[NDArray[complex,:]])

    def test_list_imag1(self):
        self.run_test("def list_imag1(a): import numpy ; numpy.imag(a)[0] = 1; return a", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_imag1=[NDArray[complex,:]])

    def test_list_real0(self):
        self.run_test("def list_real0(a): import numpy ; return numpy.real(a)", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_real0=[NDArray[complex,:]])

    def test_list_real1(self):
        self.run_test("def list_real1(a): import numpy ; numpy.real(a)[0] = 1; return a", numpy.array([complex(4.3,5.5),complex(6.1,3.2)]), list_real1=[NDArray[complex,:]])

    def test_fill_diagonal_0(self):
        self.run_test("def fill_diagonal_0(a): import numpy ; numpy.fill_diagonal(a, 0); return a", numpy.ones((4,4)), fill_diagonal_0=[NDArray[float,:,:]])

    def test_fill_diagonal_1(self):
        self.run_test("def fill_diagonal_1(a): import numpy ; numpy.fill_diagonal(a, 0); return a", numpy.ones((4,6)), fill_diagonal_1=[NDArray[float,:,:]])

    def test_fill_diagonal_2(self):
        self.run_test("def fill_diagonal_2(n): import numpy ; a = numpy.ones((n,n, 5));numpy.fill_diagonal(a[0], 0); return a", 4, fill_diagonal_2=[int])

    def test_fill_diagonal_3(self):
        self.run_test("def fill_diagonal_3(n): import numpy ; a = numpy.ones((n, n, 2, 2));numpy.fill_diagonal(a[0,1:3], 0); return a", 4, fill_diagonal_3=[int])

    def test_interp_0(self):
        self.run_test('def interp0(x,xp,fp): import numpy as np; return np.interp(x,xp,fp)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp0=[NDArray[float,:],NDArray[float,:],NDArray[float,:]])
    def test_interp_1(self):
        self.run_test('def interp1(x,xp,fp): import numpy as np; return np.interp(x,xp,fp,-10.,10.)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp1=[NDArray[float,:],NDArray[float,:],NDArray[float,:]])
    def test_interp_2(self):
        self.run_test('def interp2(x,xp,fp): import numpy as np; return np.interp(x,xp[::2],fp[::2],-10.,10.)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp2=[NDArray[float,:],NDArray[float,:],NDArray[float,:]])
    def test_interp_3(self):
        self.run_test('def interp3(x,xp,fp): import numpy as np; return np.interp(x[::3],xp[::2],fp[::2],-10.)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp3=[NDArray[float,:],NDArray[float,:],NDArray[float,:]])

    def test_interp_4(self):
        self.run_test('def interp4(x,xp,fp): import numpy as np; return np.interp(x,xp,fp,period=2.1)',
                      numpy.arange(-10.,3000),
                      numpy.arange(2000.),
                      numpy.cos(numpy.arange(2000.)*2*numpy.pi/2.1),
                      interp4=[NDArray[float,:],NDArray[float,:],NDArray[float,:]])

    def test_interp_5(self):
        self.run_test('def interp5(x,factor): N = len(x); import numpy as np; return np.interp(np.arange(0, N - 1, factor), np.arange(N), x, None, None, None)',
                      numpy.arange(100.) / .5,
                      10.,
                      interp5=[NDArray[float,:],float])

    def test_interp_6(self):
        self.run_test('def interp6(x,xp,fp): import numpy as np; return np.interp(x,xp,fp)',
                      1.4,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp6=[float,NDArray[float,:],NDArray[float,:]])

    def test_interp_7(self):
        self.run_test('def interp7(x,xp,fp): import numpy as np; return np.interp(x,xp,fp)',
                      1,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp7=[int,NDArray[float,:],NDArray[float,:]])

    def test_interp_8(self):
        self.run_test('def interp8(x,xp,fp): import numpy as np; return np.interp(x,xp,fp,-10,10)',
                      1.4,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7,
                      interp8=[float,NDArray[float,:],NDArray[float,:]])

    def test_interp_0c(self):
        self.run_test('def interp0c(x,xp,fp): import numpy as np; return np.interp(x,xp,fp)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp0c=[NDArray[float,:],NDArray[float,:],NDArray[complex,:]])

    def test_interp_1c(self):
        self.run_test('def interp1c(x,xp,fp): import numpy as np; return np.interp(x,xp,fp,-10.j,10.j)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp1c=[NDArray[float,:],NDArray[float,:],NDArray[complex,:]])

    def test_interp_2c(self):
        self.run_test('def interp2c(x,xp,fp): import numpy as np; return np.interp(x,xp[::2],fp[::2],-10.,10.)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp2c=[NDArray[float,:],NDArray[float,:],NDArray[complex,:]])
    def test_interp_3c(self):
        self.run_test('def interp3c(x,xp,fp): import numpy as np; return np.interp(x[::3],xp[::2],fp[::2],-10.j)',
                      numpy.arange(100.) / .5,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp3c=[NDArray[float,:],NDArray[float,:],NDArray[complex,:]])

    def test_interp_4c(self):
        self.run_test('def interp4c(x,xp,fp): import numpy as np; return np.interp(x,xp,fp,period=1.12)',
                      numpy.arange(-10.,30,.67),
                      numpy.arange(20.),
                      numpy.cos(numpy.arange(20.)*2*numpy.pi/1.12) * (1+.1j),
                      interp4c=[NDArray[float,:],NDArray[float,:],NDArray[complex,:]])

    def test_interp_5c(self):
        self.run_test('def interp5c(x,factor): N = len(x); import numpy as np; return np.interp(np.arange(0, N - 1, factor), np.arange(N), x, None, None, None)',
                      numpy.arange(100.) / .7 + numpy.arange(100.) * .6j,
                      10.,
                      interp5c=[NDArray[complex,:],float])

    def test_interp_6c(self):
        self.run_test('def interp6c(x,xp,fp): import numpy as np; return np.interp(x,xp,fp)',
                      1.4,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp6c=[float,NDArray[float,:],NDArray[complex,:]])

    def test_interp_7c(self):
        self.run_test('def interp7c(x,xp,fp): import numpy as np; return np.interp(x,xp,fp)',
                      1,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp7c=[int,NDArray[float,:],NDArray[complex,:]])

    def test_interp_8c(self):
        self.run_test('def interp8c(x,xp,fp): import numpy as np; return np.interp(x,xp,fp,-10j,10j)',
                      1.4,
                      numpy.arange(1000.) / .3,
                      numpy.arange(1000.) / .7 + numpy.arange(1000.) * .6j,
                      interp8c=[float,NDArray[float,:],NDArray[complex,:]])

    def test_setdiff1d0(self):
        self.run_test('def setdiff1d0(x,y): import numpy as np; return np.setdiff1d(x,y)',
                      numpy.random.randn(100),
                      numpy.random.randn(1000),
                      setdiff1d0=[NDArray[float,:],NDArray[float,:]])

    def test_setdiff1d1(self):
        self.run_test('def setdiff1d0(x,y): import numpy as np; return np.setdiff1d(x,y, True)',
                      numpy.unique(numpy.random.randn(1000)),
                      numpy.unique(numpy.random.randn(1000)),
                      setdiff1d0=[NDArray[float,:],NDArray[float,:]])

    def test_setdiff1d2(self):
        self.run_test('def setdiff1d2(x,y): import numpy as np; return np.setdiff1d(x,y)',
                      numpy.random.randn(100),
                      numpy.array([[1,2],[2,4]]),
                      setdiff1d2=[NDArray[float,:],NDArray[int,:,:]])

    def test_setdiff1d3(self):
        self.run_test('def setdiff1d3(x,y): import numpy as np; return np.setdiff1d(x,y, True)',
                      numpy.unique(numpy.random.randn(1000)),
                      numpy.array([[3,2],[5,4]]),
                      setdiff1d3=[NDArray[float,:],NDArray[int,:,:]])

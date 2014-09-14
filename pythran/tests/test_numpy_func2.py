import unittest
from test_env import TestEnv
import numpy


@TestEnv.module
class TestNumpyFunc2(TestEnv):

    def test_nonzero0(self):
        self.run_test("def np_nonzero0(x): from numpy import nonzero ; return nonzero(x)", numpy.arange(6), np_nonzero0=[numpy.array([int])])

    def test_nonzero1(self):
        self.run_test("def np_nonzero1(x): from numpy import nonzero ; return nonzero(x>8)", numpy.arange(6), np_nonzero1=[numpy.array([int])])

    def test_nonzero2(self):
        self.run_test("def np_nonzero2(x): from numpy import nonzero ; return nonzero(x>0)", numpy.arange(6).reshape(2,3), np_nonzero2=[numpy.array([[int]])])

    def test_diagflat3(self):
        self.run_test("def np_diagflat3(a): from numpy import diagflat ; return diagflat(a)", numpy.arange(2), np_diagflat3=[numpy.array([int])])

    def test_diagflat4(self):
        self.run_test("def np_diagflat4(a): from numpy import diagflat ; return diagflat(a,1)", numpy.arange(3), np_diagflat4=[numpy.array([int])])

    def test_diagflat5(self):
        self.run_test("def np_diagflat5(a): from numpy import diagflat ; return diagflat(a,-2)", numpy.arange(4), np_diagflat5=[numpy.array([int])])

    def test_diagonal0(self):
        self.run_test("def np_diagonal0(a): from numpy import diagonal ; return diagonal(a)", numpy.arange(10).reshape(2,5), np_diagonal0=[numpy.array([[int]])])

    def test_diagonal1(self):
        self.run_test("def np_diagonal1(a): from numpy import diagonal ; return diagonal(a,1)", numpy.arange(9).reshape(3,3), np_diagonal1=[numpy.array([[int]])])

    def test_diagonal2(self):
        self.run_test("def np_diagonal2(a): from numpy import diagonal ; return diagonal(a,-2)", numpy.arange(9).reshape(3,3), np_diagonal2=[numpy.array([[int]])])

    def test_diag0(self):
        self.run_test("def np_diag0(a): from numpy import diag ; return diag(a)", numpy.arange(10).reshape(2,5), np_diag0=[numpy.array([[int]])])

    def test_diag1(self):
        self.run_test("def np_diag1(a): from numpy import diag ; return diag(a,1)", numpy.arange(9).reshape(3,3), np_diag1=[numpy.array([[int]])])

    def test_diag2(self):
        self.run_test("def np_diag2(a): from numpy import diag ; return diag(a,-2)", numpy.arange(9).reshape(3,3), np_diag2=[numpy.array([[int]])])

    def test_diag2b(self):
        self.run_test("def np_diag2b(a): from numpy import diag ; return diag(a,-2)", numpy.arange(12).reshape(4,3), np_diag2b=[numpy.array([[int]])])

    def test_diag3(self):
        self.run_test("def np_diag3(a): from numpy import diag ; return diag(a)", numpy.arange(2), np_diag3=[numpy.array([int])])

    def test_diag4(self):
        self.run_test("def np_diag4(a): from numpy import diag ; return diag(a,1)", numpy.arange(3), np_diag4=[numpy.array([int])])

    def test_diag5(self):
        self.run_test("def np_diag5(a): from numpy import diag; return diag(a,-2)", numpy.arange(4), np_diag5=[numpy.array([int])])

    def test_delete0(self):
        self.run_test("def np_delete0(a): from numpy import delete ; return delete(a, 1)", numpy.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]), np_delete0=[numpy.array([[int]])])

    def test_delete1(self):
        self.run_test("def np_delete1(a): from numpy import delete ; return delete(a, [1,3,5])", numpy.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]), np_delete1=[numpy.array([[int]])])

    def test_where0(self):
        self.run_test("""def np_where0(a):
    from numpy import arange, where
    b = arange(5, 17).reshape((3,4))
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(c , a, b)""", numpy.arange(12).reshape(3,4), np_where0=[numpy.array([[int]])])

    def test_where1(self):
        self.run_test("""def np_where1(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, c)""", numpy.arange(12).reshape(3,4), np_where1=[numpy.array([[int]])])

    def test_where2(self):
        self.run_test("""def np_where2(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, c)""", numpy.arange(12).reshape(3,4), np_where2=[numpy.array([[int]])])

    def test_where3(self):
        self.run_test("""def np_where3(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, 5)""", numpy.arange(12).reshape(3,4), np_where3=[numpy.array([[int]])])

    def test_where4(self):
        self.run_test("""def np_where4(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, 6)""", numpy.arange(12).reshape(3,4), np_where4=[numpy.array([[int]])])

    def test_where5(self):
        self.run_test("""def np_where5(a):
    from numpy import arange, where
    b = arange(5, 17).reshape((3,4))
    return where(a>5 , a, b)""", numpy.arange(12).reshape(3,4), np_where5=[numpy.array([[int]])])

    def test_where6(self):
        self.run_test("""def np_where6(a):
    from numpy import arange, where
    return where(a>5 , 1, 2)""", numpy.arange(12).reshape(3,4), np_where6=[numpy.array([[int]])])

    def test_where7(self):
        self.run_test("""def np_where7(a):
    from numpy import arange, where
    return where(a>5)""", numpy.arange(12).reshape(3,4), np_where7=[numpy.array([[int]])])

    def test_cumprod_(self):
        self.run_test("def np_cumprod_(a):\n from numpy import cumprod\n return a.cumprod()", numpy.arange(10), np_cumprod_=[numpy.array([int])])

    def test_cumprod2_(self):
        self.run_test("def np_cumprod2_(a):\n from numpy import cumprod\n return a.cumprod()", numpy.arange(10).reshape(2,5), np_cumprod2_=[numpy.array([[int]])])

    def test_cumprod3_(self):
        self.run_test("def np_cumprod3_(a):\n from numpy import cumprod\n return a.cumprod(1)", numpy.arange(10).reshape(2,5), np_cumprod3_=[numpy.array([[int]])])

    def test_cumprod4_(self):
        self.run_test("def np_cumprod4_(a):\n from numpy import cumprod\n return a.cumprod(0)", numpy.arange(10).reshape(2,5), np_cumprod4_=[numpy.array([[int]])])

    def test_cumprod5_(self):
        self.run_test("def np_cumprod5_(a):\n from numpy import cumprod\n return a.cumprod(0)", numpy.arange(10), np_cumprod5_=[numpy.array([int])])

    def test_copy0(self):
        code= '''
def test_copy0(x):
    import numpy as np
    y = x
    z = np.copy(x)
    x[0] = 10
    return x[0], y[0], z[0]'''
        self.run_test(code, numpy.array([1, 2, 3]), test_copy0=[numpy.array([int])])

    def test_clip0(self):
        self.run_test("def np_clip0(a): from numpy import clip ; return clip(a,1,8)", numpy.arange(10), np_clip0=[numpy.array([int])])

    def test_clip1(self):
        self.run_test("def np_clip1(a): from numpy import  clip ; return clip(a,3,6)", numpy.arange(10), np_clip1=[numpy.array([int])])

    def test_concatenate0(self):
        self.run_test("def np_concatenate0(a): from numpy import array, concatenate ; b = array([[5, 6]]) ; return concatenate((a,b))", numpy.array([[1, 2], [3, 4]]), np_concatenate0=[numpy.array([[int]])])

    def test_bincount0(self):
        self.run_test("def np_bincount0(a): from numpy import bincount ; return bincount(a)", numpy.arange(5), np_bincount0=[numpy.array([int])])

    def test_bincount1(self):
        self.run_test("def np_bincount1(a, w): from numpy import bincount; return bincount(a,w)", numpy.array([0, 1, 1, 2, 2, 2]), numpy.array([0.3, 0.5, 0.2, 0.7, 1., -0.6]), np_bincount1=[numpy.array([int]), numpy.array([float])])

    def test_binary_repr0(self):
        self.run_test("def np_binary_repr0(a): from numpy import binary_repr ; return binary_repr(a)", 3, np_binary_repr0=[int])

    def test_binary_repr1(self):
        self.run_test("def np_binary_repr1(a): from numpy import binary_repr ; return binary_repr(a)", -3, np_binary_repr1=[int])

    def test_binary_repr2(self):
        self.run_test("def np_binary_repr2(a): from numpy import binary_repr ; return binary_repr(a,4)", 3, np_binary_repr2=[int])

    def test_binary_repr3(self):
        self.run_test("def np_binary_repr3(a): from numpy import binary_repr ; return binary_repr(a,4)", -3, np_binary_repr3=[int])

    def test_base_repr0(self):
        self.run_test("def np_base_repr0(a): from numpy import base_repr ; return base_repr(a)", 5, np_base_repr0=[int])

    def test_base_repr1(self):
        self.run_test("def np_base_repr1(a): from numpy import base_repr ; return base_repr(a,5)", 6, np_base_repr1=[int])

    def test_base_repr2(self):
        self.run_test("def np_base_repr2(a): from numpy import base_repr ; return base_repr(a,5,3)", 7, np_base_repr2=[int])

    def test_base_repr3(self):
        self.run_test("def np_base_repr3(a): from numpy import base_repr ; return base_repr(a, 16)", 10, np_base_repr3=[int])

    def test_base_repr4(self):
        self.run_test("def np_base_repr4(a): from numpy import base_repr ; return base_repr(a, 16)", 32, np_base_repr4=[int])

    def test_average0(self):
        self.run_test("def np_average0(a): from numpy import average ; return average(a)", numpy.arange(10), np_average0=[numpy.array([int])])

    def test_average1(self):
        self.run_test("def np_average1(a): from numpy import average ; return average(a,1)", numpy.arange(10).reshape(2,5), np_average1=[numpy.array([[int]])])

    def test_average2(self):
        self.run_test("def np_average2(a): from numpy import average ; return average(a,None, range(10))", numpy.arange(10), np_average2=[numpy.array([int])])

    def test_average3(self):
        self.run_test("def np_average3(a): from numpy import average ; return average(a,None, a)", numpy.arange(10).reshape(2,5), np_average3=[numpy.array([[int]])])

    def test_atleast_1d0(self):
        self.run_test("def np_atleast_1d0(a): from numpy import atleast_1d ; return atleast_1d(a)", 1, np_atleast_1d0=[int])

    def test_atleast_1d1(self):
        self.run_test("def np_atleast_1d1(a): from numpy import atleast_1d ; r = atleast_1d(a) ; return r is a", numpy.arange(2), np_atleast_1d1=[numpy.array([int])])

    def test_atleast_2d0(self):
        self.run_test("def np_atleast_2d0(a): from numpy import atleast_2d ; return atleast_2d(a)", 1, np_atleast_2d0=[int])

    def test_atleast_2d1(self):
        self.run_test("def np_atleast_2d1(a): from numpy import atleast_2d ; r = atleast_2d(a) ; return r is a", numpy.arange(2).reshape(1,2), np_atleast_2d1=[numpy.array([[int]])])

    def test_atleast_2d2(self):
        self.run_test("def np_atleast_2d2(a): from numpy import atleast_2d ; r = atleast_2d(a) ; return r", numpy.arange(2), np_atleast_2d2=[numpy.array([int])])

    def test_atleast_3d0(self):
        self.run_test("def np_atleast_3d0(a): from numpy import atleast_3d ; return atleast_3d(a)", 1, np_atleast_3d0=[int])

    def test_atleast_3d1(self):
        self.run_test("def np_atleast_3d1(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r is a", numpy.arange(8).reshape(2,2,2), np_atleast_3d1=[numpy.array([[[int]]])])

    def test_atleast_3d2(self):
        self.run_test("def np_atleast_3d2(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r", numpy.arange(8).reshape(2,4), np_atleast_3d2=[numpy.array([[int]])])

    def test_atleast_3d3(self):
        self.run_test("def np_atleast_3d3(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r", numpy.arange(8), np_atleast_3d3=[numpy.array([int])])

    def test_asscalar0(self):
        self.run_test("def np_asscalar0(a): from numpy import asscalar; return asscalar(a)", numpy.array([1], numpy.int32), np_asscalar0=[numpy.array([numpy.int32])])

    def test_asscalar1(self):
        self.run_test("def np_asscalar1(a): from numpy import asscalar; return asscalar(a)", numpy.array([[1]], numpy.int64), np_asscalar1=[numpy.array([[numpy.int64]])])

    def test_ascontiguousarray0(self):
        self.run_test("def np_ascontiguousarray0(a):\n from numpy import ascontiguousarray\n return ascontiguousarray(a)", (1,2,3), np_ascontiguousarray0=[(int, int, int)])

    def test_asarray_chkfinite0(self):
        self.run_test("def np_asarray_chkfinite0(a):\n from numpy import asarray_chkfinite\n return asarray_chkfinite(a)", (1,2,3), np_asarray_chkfinite0=[(int, int, int)])

    def test_asarray_chkfinite1(self):
        self.run_test("def np_asarray_chkfinite1(a, x):\n from numpy import asarray_chkfinite\n try: return asarray_chkfinite(a)\n except ValueError: return asarray_chkfinite(x)", [[1,2],[numpy.nan,4]], [[1.,2.],[3.,4.]], np_asarray_chkfinite1=[[[float]], [[float]]])

    def test_asarray0(self):
        self.run_test("def np_asarray0(a):\n from numpy import asarray\n return asarray(a)", (1,2,3), np_asarray0=[(int, int, int)])

    def test_asarray1(self):
        self.run_test("def np_asarray1(a):\n from numpy import asarray\n return asarray(a)", [(1,2),(3,4)], np_asarray1=[[(int, int)]])

    def test_asarray2(self):
        self.run_test("def np_asarray2(a):\n from numpy import asarray, int8\n return asarray(a, int8)", [1., 2., 3.], np_asarray2=[[float]])

    def test_asarray3(self):
        self.run_test("def np_asarray3(a):\n from numpy import asarray; b = asarray(a) ; return a is b", numpy.arange(3), np_asarray3=[numpy.array([int])])

    def test_array_str0(self):
        self.run_test("def np_array_str0(x): from numpy import array_str ; return array_str(x)", numpy.arange(3), np_array_str0=[numpy.array([int])])

    def test_array_split0(self):
        self.run_test("def np_array_split0(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, 3))", numpy.arange(12), np_array_split0=[numpy.array([int])])

    def test_array_split1(self):
        self.run_test("def np_array_split1(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, 5))", numpy.arange(12), np_array_split1=[numpy.array([int])])

    def test_array_split2(self):
        self.run_test("def np_array_split2(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, 4))", numpy.arange(12).reshape(6,2), np_array_split2=[numpy.array([[int]])])

    def test_array_split3(self):
        self.run_test("def np_array_split3(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, [0,1,5]))", numpy.arange(12).reshape(6,2), np_array_split3=[numpy.array([[int]])])

    def test_array_equiv0(self):
        self.run_test("def np_array_equiv0(a): from numpy import array_equiv ;  b = [1,2] ; return array_equiv(a,b)", [1, 2], np_array_equiv0=[[int]])

    def test_array_equiv1(self):
        self.run_test("def np_array_equiv1(a): from numpy import array_equiv ;  b = [1,3] ; return array_equiv(a,b)", [1, 2], np_array_equiv1=[[int]])

    def test_array_equiv2(self):
        self.run_test("def np_array_equiv2(a): from numpy import array_equiv ;  b = [[1,2],[1,2]] ; return array_equiv(a,b)", [1, 2], np_array_equiv2=[[int]])

    def test_array_equiv3(self):
        self.run_test("def np_array_equiv3(a): from numpy import array_equiv ;  b = [[1,2],[1,3]] ; return array_equiv(a,b)", [1, 2], np_array_equiv3=[[int]])

    def test_array_equal0(self):
        self.run_test("def np_array_equal0(a): from numpy import array_equal ;  b = [1,2] ; return array_equal(a,b)", [1, 2], np_array_equal0=[[int]])

    def test_array_equal1(self):
        self.run_test("def np_array_equal1(a): from numpy import array, array_equal ;  b = array([1,2]) ; return array_equal(a,b)", numpy.array([1,2]), np_array_equal1=[numpy.array([int])])

    def test_array_equal2(self):
        self.run_test("def np_array_equal2(a): from numpy import array, array_equal ;  b = array([[1,2],[3,5]]) ; return array_equal(a,b)", numpy.array([[1,2],[3,5]]), np_array_equal2=[numpy.array([[int]])])

    def test_array_equal3(self):
        self.run_test("def np_array_equal3(a): from numpy import array, array_equal ;  b = array([[1,2],[4,5]]) ; return array_equal(a,b)", numpy.array([[1,2],[3,5]]), np_array_equal3=[numpy.array([[int]])])

    def test_array_equal4(self):
        self.run_test("def np_array_equal4(a): from numpy import array, array_equal ;  b = array([1,2,3]) ; return array_equal(a,b)", numpy. array([1,2]), np_array_equal4=[numpy.array([int])])

    def test_array2string0(self):
        self.run_test("def np_array2string0(x): from numpy import array2string ; return array2string(x)", numpy.arange(3), np_array2string0=[numpy.array([int])])

    def test_argwhere0(self):
        self.run_test("def np_argwhere0(x): from numpy import argwhere ; return argwhere(x)", numpy.arange(6), np_argwhere0=[numpy.array([int])])

    def test_argwhere1(self):
        self.run_test("def np_argwhere1(x): from numpy import argwhere ; return argwhere(x>8)", numpy.arange(6), np_argwhere1=[numpy.array([int])])

    def test_argwhere2(self):
        self.run_test("def np_argwhere2(x): from numpy import argwhere ; return argwhere(x>0)", numpy.arange(6).reshape(2,3), np_argwhere2=[numpy.array([[int]])])

    def test_around0(self):
        self.run_test("def np_around0(x): from numpy import around ; return around(x)", [0.37, 1.64], np_around0=[[float]])

    def test_around1(self):
        self.run_test("def np_around1(x): from numpy import around ; return around(x, 1)", [0.37, 1.64], np_around1=[[float]])

    def test_around2(self):
        self.run_test("def np_around2(x): from numpy import  around ; return around(x, -1)", [0.37, 1.64], np_around2=[[float]])

    def test_around3(self):
        self.run_test("def np_around3(x): from numpy import around ; return around(x)", [.5, 1.5, 2.5, 3.5, 4.5], np_around3=[[float]])

    def test_around4(self):
        self.run_test("def np_around4(x): from numpy import around ; return around(x,1)", [1,2,3,11], np_around4=[[int]])

    def test_around5(self):
        self.run_test("def np_around5(x): from numpy import around ; return around(x,-1)", [1,2,3,11], np_around5=[[int]])

    def test_argsort0(self):
        self.run_test("def np_argsort0(x): from numpy import argsort ; return argsort(x)", numpy.array([3, 1, 2]), np_argsort0=[numpy.array([int])])

    def test_argsort1(self):
        self.run_test("def np_argsort1(x): from numpy import argsort ; return argsort(x)", numpy.array([[3, 1, 2], [1 , 2, 3]]), np_argsort1=[numpy.array([[int]])])

    def test_argmax0(self):
        self.run_test("def np_argmax0(a): from numpy import argmax ; return argmax(a)", numpy.arange(6).reshape(2,3), np_argmax0=[numpy.array([[int]])])

    def test_argmax1(self):
        self.run_test("def np_argmax1(a): from numpy import argmax ; return argmax(a+a)", numpy.arange(6).reshape(2,3), np_argmax1=[numpy.array([[int]])])

    def test_argmin0(self):
        self.run_test("def np_argmin0(a): from numpy import argmin ; return argmin(a)", numpy.arange(6).reshape(2,3), np_argmin0=[numpy.array([[int]])])

    def test_argmin1(self):
        self.run_test("def np_argmin1(a): from numpy import argmin ; return argmin(a)", [1,2,3], np_argmin1=[[int]])

    def test_append0(self):
        self.run_test("def np_append0(a): from numpy import append ; b = [[4, 5, 6], [7, 8, 9]] ; return append(a,b)", [1, 2, 3], np_append0=[[int]])

    def test_append1(self):
        self.run_test("def np_append1(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", [1, 2, 3], np_append1=[[int]])

    def test_append2(self):
        self.run_test("def np_append2(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", numpy.array([1, 2, 3]), np_append2=[numpy.array([int])])

    def test_angle0(self):
        self.run_test("def np_angle0(a): from numpy import angle ; return angle(a)", [1.0, 1.0j, 1+1j], np_angle0=[[complex]])

    def test_angle1(self):
        self.run_test("def np_angle1(a): from numpy import angle ; return angle(a)", numpy.array([1.0, 1.0j, 1+1j]), np_angle1=[numpy.array([complex])])

    def test_angle2(self):
        self.run_test("def np_angle2(a): from numpy import angle ; return angle(a,True)", 1 + 1j, np_angle2=[complex])

    def test_angle3(self):
        self.run_test("def np_angle3(a): from numpy import angle ; return angle(a,True)", 1, np_angle3=[int])

    def test_any0(self):
        self.run_test("def np_any0(a): from numpy import any ; return any(a)", numpy.array([[True, False], [True, True]]), np_any0=[numpy.array([[bool]])])

    def test_any1(self):
        self.run_test("def np_any1(a): from numpy import any ;  return any(a, 0)", numpy.array([[True, False], [False, False]]), np_any1=[numpy.array([[bool]])])

    def test_any2(self):
        self.run_test("def np_any2(a): from numpy import any ; return any(a)", [-1, 0, 5], np_any2=[[int]])

    def test_array1D_(self):
        self.run_test("def np_array1D_(a):\n from numpy import array\n return array(a)", [1,2,3], np_array1D_=[[int]])

    def test_array2D_(self):
        self.run_test("def np_array2D_(a):\n from numpy import array\n return array(a)", [[1,2],[3,4]], np_array2D_=[[[int]]])

    def test_array_typed(self):
        self.run_test("def np_array_typed(a):\n from numpy import array, int64\n return array(a, int64)", [1.,2.,3.], np_array_typed=[[float]])

    def test_zeros_(self):
        self.run_test("def np_zeros_(a): from numpy import zeros; return zeros(a)", (10, 5), np_zeros_=[(int, int)])

    def test_ones_(self):
        self.run_test("def np_ones_(a): from numpy import ones; return ones(a)", (10, 5), np_ones_=[(int, int)])

    def test_flat_zeros_(self):
        self.run_test("def np_flat_zeros_(a): from numpy import zeros; return zeros(a)", 10, np_flat_zeros_=[int])

    def test_flat_ones_(self):
        self.run_test("def np_flat_ones_(a): from numpy import ones; return ones(a)", 5, np_flat_ones_=[int])

    def test_input_array_(self):
        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", runas="import numpy; input_array_(numpy.array([[1,2],[3,4]]))", input_array_=[numpy.array([[int]])])

    def test_change_array1D_(self):
        self.run_test("def np_change_array1D_(a):\n a[0,0,0] = 36\n return a", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_change_array1D_=[numpy.array([[[int]]])])

    def test_str_(self):
        self.run_test("def np_str_(a): return str(a)", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_str_=[numpy.array([[[int]]])])

    def test_len_(self):
        self.run_test("def np_len_(a): return len(a)", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_len_=[numpy.array([[[int]]])])

    def test_empty_(self):
        self.run_test("def np_empty_(a):\n from numpy import empty\n a = empty(a)\n return a.strides, len(a)", (3, 2), np_empty_=[(int, int)])

    def test_arange(self):
        self.run_test("def np_arange_(a):\n from numpy import arange\n return arange(a)", 10, np_arange_=[int])

    def test_arange1(self):
        self.run_test("def np_arange1_(a):\n from numpy import arange\n return arange(a, 10)", 1, np_arange1_=[int])

    def test_arange2(self):
        self.run_test("def np_arange2_(a):\n from numpy import arange\n return arange(a, 10)", 0.5, np_arange2_=[float])

    def test_arange3(self):
        self.run_test("def np_arange3_(a):\n from numpy import arange\n return arange(a, 9.5)", 0.5, np_arange3_=[float])

    def test_arange4(self):
        self.run_test("def np_arange4_(a):\n from numpy import arange\n return arange(a, 9.3, 1)", 0.2, np_arange4_=[float])

    def test_arange5(self):
        self.run_test("def np_arange5_(a):\n from numpy import arange\n return arange(a, 2, 0.3)", 1, np_arange5_=[int])

    def test_arange6(self):
        self.run_test("def np_arange6_(a):\n from numpy import arange\n return arange(a, 3.3, 0.5)", 0.2, np_arange6_=[float])

    def test_arange7(self):
        self.run_test("def np_arange7_(a):\n from numpy import arange\n return arange(a, 4.5, -0.2)", 1, np_arange7_=[int])

    def test_arange8(self):
        self.run_test("def np_arange8_(a):\n from numpy import arange\n return arange(a, 1, -0.1)", 4.5, np_arange8_=[float])

    def test_arange9(self):
        self.run_test("def np_arange9_(a):\n from numpy import arange\n return arange(a, -12, -3.2)", 4.5, np_arange9_=[float])

    def test_arange10(self):
        self.run_test("def np_arange10_(a):\n from numpy import arange\n return arange(a, -5.5, -0.1)", -5, np_arange10_=[int])

    def test_arange11(self):
        self.run_test("def np_arange11_(a):\n from numpy import arange, uint8\n return arange(a, 255, 1, uint8)", 0, np_arange11_=[int])

    def test_arange12(self):
        self.run_test("def np_arange12_(a):\n from numpy import arange, float32\n return arange(a, 25, 1., float32)", 0, np_arange12_=[int])

    def test_linspace(self):
        self.run_test("def np_linspace_(a):\n from numpy import linspace\n return linspace(a,4,32)", 1, np_linspace_=[int])

    def test_linspace1(self):
        self.run_test("def np_linspace1_(a):\n from numpy import linspace\n return linspace(a,32.5,2)", 0.4, np_linspace1_=[float])

    def test_linspace2(self):
        self.run_test("def np_linspace2_(a):\n from numpy import linspace\n return linspace(a,32.5,32, False)", 0.4, np_linspace2_=[float])

    def test_linspace3(self):
        self.run_test("def np_linspace3_(a):\n from numpy import linspace\n return linspace(1,a)", 4, np_linspace3_=[int])

    def test_sin(self):
        self.run_test("def np_sin_(a):\n from numpy import sin\n return sin(a)", numpy.linspace(0,6), np_sin_=[numpy.array([float])])

    def test_pi(self):
        self.run_test("def np_pi_():\n from numpy import pi\n return pi", np_pi_=[])

    def test_e(self):
        self.run_test("def np_e_():\n from numpy import e\n return e", np_e_=[])

    def test_ones_like_(self):
        self.run_test("def np_ones_like_(a):\n from numpy import ones_like, array\n return ones_like(array(a))", [[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)], np_ones_like_=[[[int]]])

    def test_zeros_like_(self):
        self.run_test("def np_zeros_like_(a):\n from numpy import zeros_like, array\n return zeros_like(array(a))", [[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)], np_zeros_like_=[[[int]]])

    def test_empty_like_(self):
        self.run_test("def np_empty_like_(a):\n from numpy import empty_like, array\n return empty_like(array(a)).shape", [[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)], np_empty_like_=[[[int]]])

    def test_reshape0(self):
        self.run_test("def np_reshape0(a): return a.reshape((2,5))", numpy.arange(10), np_reshape0=[numpy.array([int])], check_refcount=True)

    def test_reshape1(self):
        self.run_test("def np_reshape1(a): return a.reshape((2,-1))", numpy.arange(10), np_reshape1=[numpy.array([int])], check_refcount=True)

    def test_duplicate(self):
        self.run_test("def np_duplicate(a): return a, a", numpy.arange(10), np_duplicate=[numpy.array([int])], check_refcount=True)

    def test_broadcast(self):
        self.run_test("def np_broadcast(): import numpy; a = numpy.arange(3); return a, a", np_broadcast=[], check_refcount=True)

    def test_broadcast_dup(self):
        self.run_test("def np_broadcast_dup(): import numpy; a = numpy.arange(10); return a, a.reshape((2,5))", np_broadcast_dup=[], check_refcount=True)

    def test_reshape_expr(self):
        self.run_test("def np_reshape_expr(a): return (a + a).reshape((2,5))", numpy.ones(10), np_reshape_expr=[numpy.array([float])])

    def test_cumsum_(self):
        self.run_test("def np_cumsum_(a): return a.cumsum()", numpy.arange(10), np_cumsum_=[numpy.array([int])])

    def test_cumsum2_(self):
        self.run_test("def np_cumsum2_(a): return a.cumsum()", numpy.arange(10).reshape(2,5), np_cumsum2_=[numpy.array([[int]])])

    def test_cumsum3_(self):
        self.run_test("def np_cumsum3_(a): return a.cumsum(1)", numpy.arange(10).reshape(2,5), np_cumsum3_=[numpy.array([[int]])])

    def test_cumsum4_(self):
        self.run_test("def np_cumsum4_(a): return a.cumsum(0)", numpy.arange(10).reshape(2,5), np_cumsum4_=[numpy.array([[int]])])

    def test_cumsum5_(self):
        self.run_test("def np_cumsum5_(a): return a.cumsum(0)", numpy.arange(10), np_cumsum5_=[numpy.array([int])])

    def test_sum_(self):
        self.run_test("def np_sum_(a): return a.sum()", numpy.arange(10), np_sum_=[numpy.array([int])])

    def test_sum_bool(self):
        self.run_test("def np_sum_bool(a): return (a > 2).sum()", numpy.arange(10), np_sum_bool=[numpy.array([int])])



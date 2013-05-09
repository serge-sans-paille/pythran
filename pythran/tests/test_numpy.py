import unittest
from test_env import TestEnv
import numpy

class TestNumpy(TestEnv):
#    def test_asarray0(self):
#        self.run_test("def np_asarray0():\n from numpy import asarray\n return asarray((1,2,3))", np_asarray0=[])
#       
#    def test_asarray1(self):
#        self.run_test("def np_asarray1():\n from numpy import asarray\n return asarray([(1,2),(3,4)])", np_asarray1=[])
#
#    def test_asarray2(self):
#        self.run_test("def np_asarray2():\n from numpy import asarray, int8\n return asarray([1.,2.,3.], int8)", np_asarray2=[])
#
#    def test_asarray3(self):
#        self.run_test("def np_asarray3():\n from numpy import arange, asarray; a = arange(3) ; b = asarray(a) ; return a is b", np_asarray3=[])
#
#    def test_array_str0(self):
#        self.run_test("def np_array_str0(): from numpy import arange, array_str ; x = arange(3) ; return array_str(x)", np_array_str0=[])
#
#    def test_array_split0(self):
#        self.run_test("def np_array_split0(): from numpy import arange, array_split,array2string ; a = arange(12) ; return map(array2string,array_split(a, 3))", np_array_split0=[])
#
#    def test_array_split1(self):
#        self.run_test("def np_array_split1(): from numpy import arange, array_split, array2string ; a = arange(12); return map(array2string,array_split(a, 5))", np_array_split1=[])
#
#    def test_array_split2(self):
#        self.run_test("def np_array_split2(): from numpy import arange, array_split, array2string ; a = arange(12).reshape(6,2); return map(array2string,array_split(a, 4))", np_array_split2=[])
#
#    def test_array_split3(self):
#        self.run_test("def np_array_split3(): from numpy import arange, array_split, array2string ; a = arange(12).reshape(6,2); return map(array2string,array_split(a, [0,1,5]))", np_array_split3=[])
#
#    def test_array_equiv0(self):
#        self.run_test("def np_array_equiv0(): from numpy import array_equiv ;  a,b = [1,2], [1,2] ; return array_equiv(a,b)", np_array_equiv0=[])
#
#    def test_array_equiv1(self):
#        self.run_test("def np_array_equiv1(): from numpy import array_equiv ;  a,b = [1,2], [1,3] ; return array_equiv(a,b)", np_array_equiv1=[])
#
#    def test_array_equiv2(self):
#        self.run_test("def np_array_equiv2(): from numpy import array_equiv ;  a,b = [1,2], [[1,2],[1,2]] ; return array_equiv(a,b)", np_array_equiv2=[])
#
#    def test_array_equiv3(self):
#        self.run_test("def np_array_equiv3(): from numpy import array_equiv ;  a,b = [1,2], [[1,2],[1,3]] ; return array_equiv(a,b)", np_array_equiv3=[])
#
#    def test_array_equal0(self):
#        self.run_test("def np_array_equal0(): from numpy import array_equal ;  a,b = [1,2], [1,2] ; return array_equal(a,b)", np_array_equal0=[])
#
#    def test_array_equal1(self):
#        self.run_test("def np_array_equal1(): from numpy import array, array_equal ;  a,b = array([1,2]), array([1,2]) ; return array_equal(a,b)", np_array_equal1=[])
#
#    def test_array_equal2(self):
#        self.run_test("def np_array_equal2(): from numpy import array, array_equal ;  a,b = array([[1,2],[3,5]]), array([[1,2],[3,5]]) ; return array_equal(a,b)", np_array_equal2=[])
#
#    def test_array_equal3(self):
#        self.run_test("def np_array_equal3(): from numpy import array, array_equal ;  a,b = array([[1,2],[3,5]]), array([[1,2],[4,5]]) ; return array_equal(a,b)", np_array_equal3=[])
#
#    def test_array_equal4(self):
#        self.run_test("def np_array_equal4(): from numpy import array, array_equal ;  a,b = array([1,2]), array([1,2,3]) ; return array_equal(a,b)", np_array_equal4=[])
#
#
#    def test_array2string0(self):
#        self.run_test("def np_array2string0(): from numpy import arange, array2string ; x = arange(3) ; return array2string(x)", np_array2string0=[])
#
#    def test_argwhere0(self):
#        self.run_test("def np_argwhere0(): from numpy import arange, argwhere ; x = arange(6) ; return argwhere(x)", np_argwhere0=[])
#
#    def test_argwhere1(self):
#        self.run_test("def np_argwhere1(): from numpy import arange, argwhere ; x = arange(6) ; return argwhere(x>8)", np_argwhere1=[])
#
#    def test_argwhere2(self):
#        self.run_test("def np_argwhere2(): from numpy import arange, argwhere ; x = arange(6).reshape(2,3) ; return argwhere(x>0)", np_argwhere2=[])
#
#    def test_around0(self):
#        self.run_test("def np_around0(): from numpy import array, around ; x = [0.37, 1.64] ; return around(x)", np_around0=[])
#
#    def test_around1(self):
#        self.run_test("def np_around1(): from numpy import array, around ; x = [0.37, 1.64] ; return around(x, 1)", np_around1=[])
#
#    def test_around2(self):
#        self.run_test("def np_around2(): from numpy import array, around ; x = [0.37, 1.64] ; return around(x, -1)", np_around2=[])
#
#    def test_around3(self):
#        self.run_test("def np_around3(): from numpy import array, around ; x = [.5, 1.5, 2.5, 3.5, 4.5] ; return around(x)", np_around3=[])
#
#    def test_around4(self):
#        self.run_test("def np_around4(): from numpy import array, around ; x = [1,2,3,11] ; return around(x,1)", np_around4=[])
#
#    def test_around5(self):
#        self.run_test("def np_around5(): from numpy import array, around ; x = [1,2,3,11] ; return around(x,-1)", np_around5=[])
#
#    def test_argsort0(self):
#        self.run_test("def np_argsort0(): from numpy import argsort, array ; x = array([3, 1, 2]) ; return argsort(x)", np_argsort0=[])
#
#    def test_argsort1(self):
#        self.run_test("def np_argsort1(): from numpy import argsort, array ; x = array([[3, 1, 2], [1 , 2, 3]]) ; return argsort(x)", np_argsort1=[])
#
#    def test_argmax0(self):
#        self.run_test("def np_argmax0(): from numpy import argmax, arange ; a = arange(6).reshape(2,3) ; return argmax(a)", np_argmax0=[])
#
#    def test_argmax1(self):
#        self.run_test("def np_argmax1(): from numpy import argmax, arange ; a = arange(6).reshape(2,3) ; return argmax(a+a)", np_argmax1=[])
#
#    def test_argmin0(self):
#        self.run_test("def np_argmin0(): from numpy import argmin, arange ; a = arange(6).reshape(2,3) ; return argmin(a)", np_argmin0=[])
#
#    def test_argmin1(self):
#        self.run_test("def np_argmin1(): from numpy import argmin, arange ; a =[1,2,3] ; return argmin(a)", np_argmin1=[])
#
#    def test_append0(self):
#        self.run_test("def np_append0(): from numpy import append ; a,b = [1, 2, 3], [[4, 5, 6], [7, 8, 9]] ; return append(a,b)", np_append0=[])
#
#    def test_append1(self):
#        self.run_test("def np_append1(): from numpy import append,array ; a,b = [1, 2, 3], array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", np_append1=[])
#
#    def test_append2(self):
#        self.run_test("def np_append2(): from numpy import append,array ; a,b = array([1, 2, 3]), array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", np_append2=[])
#    def test_angle0(self):
#        self.run_test("def np_angle0(): from numpy import angle, array ; a = [1.0, 1.0j, 1+1j] ; return angle(a)", np_angle0=[])
#
#    def test_angle1(self):
#        self.run_test("def np_angle1(): from numpy import angle, array ; a = array([1.0, 1.0j, 1+1j]) ; return angle(a)", np_angle1=[])
#
#    def test_angle2(self):
#        self.run_test("def np_angle2(): from numpy import angle, array ; a = 1 + 1j ; return angle(a,True)", np_angle2=[])
#
#    def test_angle3(self):
#        self.run_test("def np_angle3(): from numpy import angle, array ; a = 1  ; return angle(a,True)", np_angle3=[])
#
#    def test_any0(self):
#        self.run_test("def np_any0(): from numpy import any, array ; a = array([[True, False], [True, True]]) ; return any(a)", np_any0=[])
#
#    def test_any1(self):
#        self.run_test("def np_any1(): from numpy import any, array ; a = array([[True, False], [False, False]]) ; return any(a, 0)", np_any1=[])
#
#    def test_any2(self):
#        self.run_test("def np_any2(): from numpy import any ; a = [-1, 0, 5] ; return any(a)", np_any2=[])
#
#    def test_array1D_(self):
#        self.run_test("def np_array1D_():\n from numpy import array\n return array([1,2,3])", np_array1D_=[])
#       
#    def test_array2D_(self):
#        self.run_test("def np_array2D_():\n from numpy import array\n return array([[1,2],[3,4]])", np_array2D_=[])
#
#    def test_array_typed(self):
#        self.run_test("def np_array_typed():\n from numpy import array, int64\n return array([1.,2.,3.], int64)", np_array_typed=[])
#
#    def test_zeros_(self):
#        self.run_test("def np_zeros_():\n from numpy import zeros\n return zeros((10,5))", np_zeros_=[])
#
#    def test_ones_(self):
#        self.run_test("def np_ones_():\n from numpy import ones\n return ones((10,5))", np_ones_=[])
#
#    def test_flat_zeros_(self):
#        self.run_test("def np_flat_zeros_():\n from numpy import zeros\n return zeros(10)", np_flat_zeros_=[])
#
#    def test_flat_ones_(self):
#        self.run_test("def np_flat_ones_():\n from numpy import ones\n return ones(5)", np_flat_ones_=[])
#
#    def test_acces1D_(self):
#        self.run_test("def np_acces1D_():\n from numpy import array\n a =array([1,2,3])\n return a[1]", np_acces1D_=[])
#
#    def test_accesSimple_(self):
#        self.run_test("def np_accesSimple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1]", np_accesSimple_=[])
#
#    def test_accesMultiple_(self):
#        self.run_test("def np_accesMultiple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1,0]", np_accesMultiple_=[])
#
#    def test_accesMultipleND_(self):
#        self.run_test("def np_accesMultipleND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1,0]", np_accesMultipleND_=[])
#
#    def test_accesMultipleNDSplit_(self):
#        self.run_test("def np_accesMultipleNDSplit_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1][0]", np_accesMultipleNDSplit_=[])
#
#    def test_shape_(self):
#        self.run_test("def np_shape_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.shape", np_shape_=[])
#
#    def test_input_array_(self):
#        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", numpy.array([[1,2],[3,4]]), input_array_=[numpy.array([[int]])])
#
#    def test_change_array1D_(self):
#        self.run_test("def np_change_array1D_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0,0] = 36\n return a", np_change_array1D_=[])
#
#    def test_change_arrayND_(self):
#        self.run_test("def np_change_arrayND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0] = array([99,99])\n return a", np_change_arrayND_=[])
#
#    def test_ndim_(self):
#        self.run_test("def np_ndim_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.ndim", np_ndim_=[])
#
#    def test_stride_(self):
#        self.run_test("def np_stride_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.strides", np_stride_=[])
#
#    def test_size_(self):
#        self.run_test("def np_size_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.size", np_size_=[])
#
#    def test_itemsize_(self):
#        self.run_test("def np_itemsize_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.itemsize", np_itemsize_=[])
#
#    def test_nbytes_(self):
#        self.run_test("def np_nbytes_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.nbytes", np_nbytes_=[])
#
#    def test_flat_(self):
#        self.run_test("def np_flat_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return [i for i in a.flat]", np_flat_=[])
#
#    def test_str_(self):
#        self.run_test("def np_str_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return str(a)", np_str_=[])
#
#    def test_len_(self):
#        self.run_test("def np_len_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return len(a)", np_len_=[])
#
#    def test_empty_(self):
#        self.run_test("def np_empty_():\n from numpy import empty\n a = empty((3,2))\n return a.strides, len(a)", np_empty_=[])
#
#    def test_arange(self):
#        self.run_test("def np_arange_():\n from numpy import arange\n return arange(10)", np_arange_=[])
#
#    def test_arange1(self):
#        self.run_test("def np_arange1_():\n from numpy import arange\n return arange(1, 10)", np_arange1_=[])
#
#    def test_arange2(self):
#        self.run_test("def np_arange2_():\n from numpy import arange\n return arange(0.5, 10)", np_arange2_=[])
#
#    def test_arange3(self):
#        self.run_test("def np_arange3_():\n from numpy import arange\n return arange(0.5, 9.5)", np_arange3_=[])
#
#    def test_arange4(self):
#        self.run_test("def np_arange4_():\n from numpy import arange\n return arange(0.2, 9.3, 1)", np_arange4_=[])
#
#    def test_arange5(self):
#        self.run_test("def np_arange5_():\n from numpy import arange\n return arange(1, 2, 0.3)", np_arange5_=[])
#
#    def test_arange6(self):
#        self.run_test("def np_arange6_():\n from numpy import arange\n return arange(0.2, 3.3, 0.5)", np_arange6_=[])
#
#    def test_arange7(self):
#        self.run_test("def np_arange7_():\n from numpy import arange\n return arange(1, 4.5, -0.2)", np_arange7_=[])
#
#    def test_arange8(self):
#        self.run_test("def np_arange8_():\n from numpy import arange\n return arange(4.5, 1, -0.1)", np_arange8_=[])
#
#    def test_arange9(self):
#        self.run_test("def np_arange9_():\n from numpy import arange\n return arange(4.5, -12, -3.2)", np_arange9_=[])
#
#    def test_arange10(self):
#        self.run_test("def np_arange10_():\n from numpy import arange\n return arange(-5, -5.5, -0.1)", np_arange10_=[])
#
#    def test_linspace(self):
#        self.run_test("def np_linspace_():\n from numpy import linspace\n return linspace(1,4,32)", np_linspace_=[])
#
#    def test_linspace1(self):
#        self.run_test("def np_linspace1_():\n from numpy import linspace\n return linspace(0.4,32.5,2)", np_linspace1_=[])
#
#    def test_linspace2(self):
#        self.run_test("def np_linspace2_():\n from numpy import linspace\n return linspace(0.4,32.5,32, False)", np_linspace2_=[])
#
#    def test_linspace3(self):
#        self.run_test("def np_linspace3_():\n from numpy import linspace\n return linspace(1,4)", np_linspace3_=[])
#
#    def test_sin(self):
#        self.run_test("def np_sin_():\n from numpy import sin, linspace\n return sin(linspace(0,6))", np_sin_=[])
#
#    def test_pi(self):
#        self.run_test("def np_pi_():\n from numpy import pi\n return pi", np_pi_=[])
#
#    def test_e(self):
#        self.run_test("def np_e_():\n from numpy import e\n return e", np_e_=[])
#
#    def test_ones_like_(self):
#        self.run_test("def np_ones_like_():\n from numpy import ones_like, array\n return ones_like(array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)]))", np_ones_like_=[])
#
#    def test_zeros_like_(self):
#        self.run_test("def np_zeros_like_():\n from numpy import zeros_like, array\n return zeros_like(array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)]))", np_zeros_like_=[])
#
#    def test_empty_like_(self):
#        self.run_test("def np_empty_like_():\n from numpy import empty_like, array\n return empty_like(array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])).shape", np_empty_like_=[])
#
#    def test_reshape_(self):
#        self.run_test("def np_reshape_():\n from numpy import arange,reshape\n return arange(10).reshape(2,5)", np_reshape_=[])
#
#    def test_reshape_expr(self):
#        self.run_test("def np_reshape_expr():\n from numpy import ones,reshape\n return (ones(10) + ones(10)).reshape(2,5)", np_reshape_expr=[])
#
#    def test_cumsum_(self):
#        self.run_test("def np_cumsum_():\n from numpy import arange,cumsum\n return arange(10).cumsum()", np_cumsum_=[])
#
#    def test_cumsum2_(self):
#        self.run_test("def np_cumsum2_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum()", np_cumsum2_=[])
#
#    def test_cumsum3_(self):
#        self.run_test("def np_cumsum3_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum(1)", np_cumsum3_=[])
#
#    def test_cumsum4_(self):
#        self.run_test("def np_cumsum4_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum(0)", np_cumsum4_=[])
#
#    def test_cumsum5_(self):
#        self.run_test("def np_cumsum5_():\n from numpy import arange,cumsum\n return arange(10).cumsum(0)", np_cumsum5_=[])
#
#    def test_sum_(self):
#        self.run_test("def np_sum_():\n from numpy import arange,sum\n return arange(10).sum()", np_sum_=[])
#
#    def test_sum_expr(self):
#        self.run_test("def np_sum_expr():\n from numpy import arange, ones, sum\n return (arange(10)+ones(10)).sum()", np_sum_expr=[])
#
#    def test_sum2_(self):
#        self.run_test("def np_sum2_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum()", np_sum2_=[])
#
#    def test_sum3_(self):
#        self.run_test("def np_sum3_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum(1)", np_sum3_=[])
#
#    def test_sum4_(self):
#        self.run_test("def np_sum4_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum(0)", np_sum4_=[])
#
#    def test_sum5_(self):
#        self.run_test("def np_sum5_():\n from numpy import arange,sum\n return arange(10).sum(0)", np_sum5_=[])
#
#    def test_min_(self):
#        self.run_test("def np_min_():\n from numpy import arange,min\n return arange(10).min()", np_min_=[])
#
#    def test_min2_(self):
#        self.run_test("def np_min2_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min()", np_min2_=[])
#
#    def test_min3_(self):
#        self.run_test("def np_min3_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min(1)", np_min3_=[])
#
#    def test_min4_(self):
#        self.run_test("def np_min4_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min(0)", np_min4_=[])
#
#    def test_min5_(self):
#        self.run_test("def np_min5_():\n from numpy import arange,min\n return arange(10).min(0)", np_min5_=[])
#
#    def test_max_(self):
#        self.run_test("def np_max_():\n from numpy import arange,max\n return arange(10).max()", np_max_=[])
#
#    def test_max2_(self):
#        self.run_test("def np_max2_():\n from numpy import arange,max\n return arange(10).reshape(2,5).max()", np_max2_=[])
#
#    def test_max3_(self):
#        self.run_test("def np_max3_():\n from numpy import arange,max\n return arange(10).reshape(2,5).max(1)", np_max3_=[])
#
#    def test_max4_(self):
#        self.run_test("def np_max4_():\n from numpy import arange,max\n return arange(10).reshape(2,5).max(0)", np_max4_=[])
#
#    def test_max5_(self):
#        self.run_test("def np_max5_():\n from numpy import arange,max\n return arange(10).max(0)", np_max5_=[])
#
#    def test_all_(self):
#        self.run_test("def np_all_():\n from numpy import arange,all\n return arange(10).all()", np_all_=[])
#
#    def test_all2_(self):
#        self.run_test("def np_all2_():\n from numpy import ones,all\n return ones(10).reshape(2,5).all()", np_all2_=[])
#
#    def test_all3_(self):
#        self.run_test("def np_all3_():\n from numpy import arange,all\n return arange(10).reshape(2,5).all(1)", np_all3_=[])
#
#    def test_all4_(self):
#        self.run_test("def np_all4_():\n from numpy import ones,all\n return ones(10).reshape(2,5).all(0)", np_all4_=[])
#
#    def test_all5_(self):
#        self.run_test("def np_all5_():\n from numpy import arange,all\n return arange(10).all(0)", np_all5_=[])
#
#    def test_transpose_(self):
#        self.run_test("def np_transpose_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose()", np_transpose_=[])
#
#    def test_transpose_expr(self):
#        self.run_test("def np_transpose_expr():\n from numpy import arange,ones,transpose\n return (ones(24).reshape(2,3,4) + ones(24).reshape(2,3,4)).transpose()", np_transpose_expr=[])
#
#    def test_transpose2_(self):
#        self.run_test("def np_transpose2_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose((2,0,1))", np_transpose2_=[])
#
#    def test_add0(self):
#        self.run_test("def np_add0(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b", np_add0=[])
#
#    def test_add1(self):
#        self.run_test("def np_add1(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b + a", np_add1=[])
#
#    def test_add2(self):
#        self.run_test("def np_add2(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b + 1", np_add2=[])
#
#    def test_add3(self):
#        self.run_test("def np_add3(): from numpy import ones ; a, b = ones(10), ones(10) ; return 1. + a + b + 1.", np_add3=[])
#
#    def test_add4(self):
#        self.run_test("def np_add4(): from numpy import ones ; a, b = ones(10), ones(10) ; return ( a + b ) + ( a + b )", np_add4=[])
#
#    def test_add5(self):
#        self.run_test("def np_add5(): from numpy import ones ; a, b = ones(10), ones(10) ; return (-a) + (-b)", np_add5=[])
#
#    def test_sub0(self):
#        self.run_test("def np_sub0(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b", np_sub0=[])
#
#    def test_sub1(self):
#        self.run_test("def np_sub1(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b - a", np_sub1=[])
#
#    def test_sub2(self):
#        self.run_test("def np_sub2(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b - 1", np_sub2=[])
#
#    def test_sub3(self):
#        self.run_test("def np_sub3(): from numpy import ones ; a, b = ones(10), ones(10) ; return 1. - a - b - 1.", np_sub3=[])
#
#    def test_sub4(self):
#        self.run_test("def np_sub4(): from numpy import ones ; a, b = ones(10), ones(10) ; return ( a - b ) - ( a - b )", np_sub4=[])
#
#    def test_addsub0(self):
#        self.run_test("def np_addsub0(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b + a", np_addsub0=[])
#
#    def test_addsub1(self):
#        self.run_test("def np_addsub1(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b - a", np_addsub1=[])
#
#    def test_addsub2(self):
#        self.run_test("def np_addsub2(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b - 1", np_addsub2=[])
#
#    def test_addsub3(self):
#        self.run_test("def np_addsub3(): from numpy import ones ; a, b = ones(10), ones(10) ; return 1. + a - b + 1.", np_addsub3=[])
#
#    def test_addsub4(self):
#        self.run_test("def np_addsub4(): from numpy import ones ; a, b = ones(10), ones(10) ; return ( a - b ) + ( a + b )", np_addsub4=[])
#
#    def test_addcossub0(self):
#        self.run_test("def np_addcossub0(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return a - b + cos(a)", np_addcossub0=[])
#
#    def test_addcossub1(self):
#        self.run_test("def np_addcossub1(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return a + cos(b - a)", np_addcossub1=[])
#
#    def test_addcossub2(self):
#        self.run_test("def np_addcossub2(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return a + cos(b - 1)", np_addcossub2=[])
#
#    def test_addcossub3(self):
#        self.run_test("def np_addcossub3(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return cos(1. + a - b + cos(1.))", np_addcossub3=[])
#
#    def test_addcossub4(self):
#        self.run_test("def np_addcossub4(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return cos( a - b ) + ( a + b )", np_addcossub4=[])
#
#    def test_sin0(self):
#        self.run_test("def np_sin0(): from numpy import ones, sin ; a, b = ones(10), ones(10) ; return sin(a) + b", np_sin0=[])
#
#    def test_tan0(self):
#        self.run_test("def np_tan0(): from numpy import ones, tan ; a, b = ones(10), ones(10) ; return tan(a - b)", np_tan0=[])
#
#    def test_arccos0(self):
#        self.run_test("def np_arccos0(): from numpy import ones, arccos ; a, b = ones(10), ones(10) ; return arccos(a - b) + 1", np_arccos0=[])
#
#    def test_arcsin0(self):
#        self.run_test("def np_arcsin0(): from numpy import ones, arcsin ; a, b = ones(10), ones(10) ; return arcsin(a + b - a + -b) + 1.", np_arcsin0=[])
#
#    def test_arctan0(self):
#        self.run_test("def np_arctan0(): from numpy import ones, arctan ; a, b = ones(10), ones(10) ; return arctan(a -0.5) + a", np_arctan0=[])
#
#    def test_arctan20(self):
#        self.run_test("def np_arctan20(): from numpy import ones, arctan2 ; a, b = ones(10), ones(10) ; return b - arctan2(a , b)", np_arctan20=[])
#
#    def test_cos1(self):
#        self.run_test("def np_cos1(): from numpy import cos ; a = 5 ; return cos(a)", np_cos1=[])
#
#    def test_sin1(self):
#        self.run_test("def np_sin1(): from numpy import sin ; a = 0.5 ; return sin(a)", np_sin1=[])
#
#    def test_tan1(self):
#        self.run_test("def np_tan1(): from numpy import tan ; a = 0.5 ; return tan(a)", np_tan1=[])
#
#    def test_arccos1(self):
#        self.run_test("def np_arccos1(): from numpy import arccos ; a= 1 ; return arccos(a)", np_arccos1=[])
#
#    def test_arcsin1(self):
#        self.run_test("def np_arcsin1(): from numpy import arcsin ; a= 1 ; return arcsin(a)", np_arcsin1=[])
#
#    def test_arctan1(self):
#        self.run_test("def np_arctan1(): from numpy import arctan ; a = 0.5 ; return arctan(a)", np_arctan1=[])
#
#    def test_arctan21(self):
#        self.run_test("def np_arctan21(): from numpy import arctan2 ; a, b = 1., .5 ; return arctan2(a , b)", np_arctan21=[])
#
#    def test_sliced0(self):
#        self.run_test("def np_sliced0(): from numpy import ones ; a = ones(20) ; return a[2:12]", np_sliced0=[])
#
#    def test_sliced1(self):
#        self.run_test("def np_sliced1(): from numpy import ones ; a = ones(20) ; return a[2:12:3]", np_sliced1=[])
#
#    def test_sliced2(self):
#        self.run_test("def np_sliced2(): from numpy import ones ; a = ones(20) ; return -a[2:12:3]", np_sliced2=[])
#
#    def test_sliced3(self):
#        self.run_test("def np_sliced3(): from numpy import ones ; a = ones(20) ; return a[1:11:3] -a[2:12:3]", np_sliced3=[])
#
#    def test_sliced4(self):
#        self.run_test("def np_sliced4(): from numpy import ones ; a = ones(20) ; return a[1:11] -a[2:12]", np_sliced4=[])
#
#    def test_sliced5(self):
#        self.run_test("def np_sliced5(): from numpy import ones ; a = ones(20) ; return (-a[1:11]) + 3*a[2:12]", np_sliced5=[])
#
#    def test_sliced6(self):
#        self.run_test("def np_sliced6(): from numpy import arange ; a = arange(12).reshape(6,2) ; return a[3:4]", np_sliced6=[])
#
#    def test_alen0(self):
#        self.run_test("def np_alen0(): from numpy import ones, alen ; return alen(ones((5,6)))", np_alen0=[])
#
#    def test_alen1(self):
#        self.run_test("def np_alen1(): from numpy import ones, alen ; return alen(-ones((5,6)))", np_alen1=[])
#
#    def test_allclose0(self):
#        self.run_test("def np_allclose0(): from numpy import allclose ; return allclose([1e10,1e-7], [1.00001e10,1e-8])", np_allclose0=[])
#
#    def test_allclose1(self):
#        self.run_test("def np_allclose1(): from numpy import allclose,array ; return allclose([1e10,1e-8], +array([1.00001e10,1e-9]))", np_allclose1=[])
#
#    def test_allclose2(self):
#        self.run_test("def np_allclose2(): from numpy import allclose,array ; return allclose(array([1e10,1e-8]), [1.0001e10,1e-9])", np_allclose2=[])
#
#    def test_allclose3(self):
#        self.run_test("def np_allclose3(): from numpy import allclose,nan ; return allclose([1.0, nan], [1.0, nan])", np_allclose3=[])
#
#    def test_alltrue0(self):
#        self.run_test("def np_alltrue0(): from numpy import array, alltrue ; b = array([True, False, True, True]) ; return alltrue(b)", np_alltrue0=[])
#
#    def test_alltrue1(self):
#        self.run_test("def np_alltrue1(): from numpy import array, alltrue ; a = array([1, 5, 2, 7]) ; return alltrue(a >= 5)", np_alltrue1=[])
#
#
##automatic generation of basic test cases for ufunc
#binary_ufunc = (
#        'add','arctan2',
#        'bitwise_and', 'bitwise_or', 'bitwise_xor',
#        'copysign',
#        'divide',
#        'equal',
#        #'frexp', # todo
#        'floor_divide', 'fmax', 'fmin', 'fmod',
#        'greater', 'greater_equal',
#        'hypot',
#        'ldexp', 'left_shift', 'less', 'less_equal', 'logaddexp', 'logaddexp2', "logical_and", "logical_or", "logical_xor",
#        'maximum', 'minimum', 'mod','multiply',
#        'nextafter','not_equal', 
#        'power',
#        'remainder','right_shift', 
#        'subtract',
#        'true_divide',
#        )
#
#unary_ufunc = (
#        'abs', 'absolute', 'arccos', 'arccosh', 'arcsin', 'arcsinh', 'arctan', 'arctanh',
#        'bitwise_not',
#        'ceil',  'cos', 'cosh',
#        'deg2rad', 'degrees',
#        'exp', 'expm1',
#        'fabs', 'floor',
#        'isinf', 'isnan', 'invert', 'isfinite',
#        'log10', 'log1p', 'log2', 'logical_not',
#        'negative',
#        'rad2deg', 'radians','reciprocal', 'rint', 
#        'sign', 'signbit', 
#         'sin', 'sinh', 'spacing', 'sqrt', 'square', 
#        'tan', 'tanh','trunc', 
#        )
#
#for f in unary_ufunc:
#    if 'bitwise_' in f or 'invert' in f:
#        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a)', np_{0}=[])".format(f)))
#        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 1 ; return {0}(a)', np_{0}_scalar=[])".format(f)))
#    else:
#        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a)', np_{0}=[])".format(f)))
#        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 0.5 ; return {0}(a+0.5)', np_{0}_scalar=[])".format(f)))
#
#for f in binary_ufunc:
#    if 'bitwise_' in f or 'ldexp' in f or '_shift' in f :
#        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a,a)', np_{0}=[])".format(f)))
#        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 1 ; return {0}(a, a-1)', np_{0}_scalar=[])".format(f)))
#    else:
#        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a,a)', np_{0}=[])".format(f)))
#        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 0.5 ; return {0}(a+0.5, a+0.5)', np_{0}_scalar=[])".format(f)))

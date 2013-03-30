import unittest
from test_env import TestEnv
import numpy

class TestNumpy(TestEnv):

#    def test_array1D_(self):
#        self.run_test("def np_array1D_():\n from numpy import array\n return array([1,2,3])", np_array1D_=[])
#        
#    def test_array2D_(self):
#        self.run_test("def np_array2D_():\n from numpy import array\n return array([[1,2],[3,4]])", np_array2D_=[])
#
#    def test_arrayND_(self):
#        self.run_test("def np_arrayND_():\n from numpy import array\n return array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", np_arrayND_=[])
#
#    def test_zeros_(self):
#        self.run_test("def np_zeros_():\n from numpy import zeros\n return zeros((10,5))", np_zeros_=[])
#
#    def test_ones_(self):
#        self.run_test("def np_ones_():\n from numpy import zeros\n return zeros((10,5))", np_ones_=[])
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
#    #@unittest.skip("Work outside of tests") 
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
#        self.run_test("def np_ones_like_():\n from numpy import ones_like\n return ones_like([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", np_ones_like_=[])
#
#    def test_zeros_like_(self):
#        self.run_test("def np_zeros_like_():\n from numpy import zeros_like\n return zeros_like([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", np_zeros_like_=[])
#
#    def test_reshape_(self):
#        self.run_test("def np_reshape_():\n from numpy import arange,reshape\n return arange(10).reshape(2,5)", np_reshape_=[])
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
#    def test_transpose_(self):
#        self.run_test("def np_transpose_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose()", np_transpose_=[])
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
    pass

#automatic generation of basic test cases for ufunc
binary_ufunc = (
        #'add','arctan2',
        #'bitwise_and', 'bitwise_or', 'bitwise_xor',
        #'copysign',
        #'divide',
        #'equal',
        ##'frexp', # todo
        #'floor_divide', 'fmax', 'fmin', 'fmod',
        #'greater', 'greater_equal',
        #'hypot',
        #'ldexp', 'left_shift', 'less', 'less_equal', 'logaddexp', 'logaddexp2', "logical_and", "logical_or", "logical_xor",
        #'maximum', 'minimum', 'mod','multiply',
        #'nextafter','not_equal', 
        #'power',
        #'remainder','right_shift', 
        )

unary_ufunc = (
        #'absolute', 'arccos', 'arccosh', 'arcsin', 'arcsinh', 'arctan', 'arctanh',
        #'bitwise_not',
        #'ceil',  'cos', 'cosh',
        #'deg2rad', 'degrees',
        #'exp', 'expm1',
        #'fabs', 'floor',
        #'isinf', 'isnan', 'invert', 'isfinite',
        #'log10', 'log1p', 'log2', 'logical_not',
        #'negative',
        'rint', #'rad2deg', 'radians','reciprocal', 
        )

for f in unary_ufunc:
    if 'bitwise_' in f or 'invert' in f:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 1 ; return {0}(a)', np_{0}_scalar=[])".format(f)))
    else:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 0.5 ; return {0}(a+0.5)', np_{0}_scalar=[])".format(f)))

for f in binary_ufunc:
    if 'bitwise_' in f or 'ldexp' in f or '_shift' in f:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a,a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 1 ; return {0}(a, a-1)', np_{0}_scalar=[])".format(f)))
    else:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a,a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 0.5 ; return {0}(a+0.5, a+0.5)', np_{0}_scalar=[])".format(f)))

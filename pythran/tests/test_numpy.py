import unittest
from test_env import TestEnv
import numpy

class TestNumpy(TestEnv):

    def test_array1D_(self):
        self.run_test("def np_array1D_():\n from numpy import array\n return array([1,2,3])", np_array1D_=[])
        
    def test_array2D_(self):
        self.run_test("def np_array2D_():\n from numpy import array\n return array([[1,2],[3,4]])", np_array2D_=[])

    def test_arrayND_(self):
        self.run_test("def np_arrayND_():\n from numpy import array\n return array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", np_arrayND_=[])

    def test_zeros_(self):
        self.run_test("def np_zeros_():\n from numpy import zeros\n return zeros((10,5))", np_zeros_=[])

    def test_ones_(self):
        self.run_test("def np_ones_():\n from numpy import zeros\n return zeros((10,5))", np_ones_=[])

    def test_acces1D_(self):
        self.run_test("def np_acces1D_():\n from numpy import array\n a =array([1,2,3])\n return a[1]", np_acces1D_=[])

    def test_accesSimple_(self):
        self.run_test("def np_accesSimple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1]", np_accesSimple_=[])

    def test_accesMultiple_(self):
        self.run_test("def np_accesMultiple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1,0]", np_accesMultiple_=[])

    def test_accesMultipleND_(self):
        self.run_test("def np_accesMultipleND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1,0]", np_accesMultipleND_=[])

    def test_accesMultipleNDSplit_(self):
        self.run_test("def np_accesMultipleNDSplit_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1][0]", np_accesMultipleNDSplit_=[])

    def test_shape_(self):
        self.run_test("def np_shape_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.shape", np_shape_=[])

    def test_input_array_(self):
        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", numpy.array([[1,2],[3,4]]), input_array_=[numpy.array([[int]])])

    def test_change_array1D_(self):
        self.run_test("def np_change_array1D_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0,0] = 36\n return a", np_change_array1D_=[])

    def test_change_arrayND_(self):
        self.run_test("def np_change_arrayND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0] = array([99,99])\n return a", np_change_arrayND_=[])

    def test_ndim_(self):
        self.run_test("def np_ndim_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.ndim", np_ndim_=[])

    def test_stride_(self):
        self.run_test("def np_stride_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.strides", np_stride_=[])

    def test_size_(self):
        self.run_test("def np_size_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.size", np_size_=[])

    def test_itemsize_(self):
        self.run_test("def np_itemsize_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.itemsize", np_itemsize_=[])

    def test_nbytes_(self):
        self.run_test("def np_nbytes_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.nbytes", np_nbytes_=[])

    def test_flat_(self):
        self.run_test("def np_flat_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return [i for i in a.flat]", np_flat_=[])

    def test_str_(self):
        self.run_test("def np_str_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return str(a)", np_str_=[])

    def test_len_(self):
        self.run_test("def np_len_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return len(a)", np_len_=[])

    def test_arange(self):
        self.run_test("def np_arange_():\n from numpy import arange\n return arange(10)", np_arange_=[])

    def test_arange1(self):
        self.run_test("def np_arange1_():\n from numpy import arange\n return arange(1, 10)", np_arange1_=[])

    def test_arange2(self):
        self.run_test("def np_arange2_():\n from numpy import arange\n return arange(0.5, 10)", np_arange2_=[])

    def test_arange3(self):
        self.run_test("def np_arange3_():\n from numpy import arange\n return arange(0.5, 9.5)", np_arange3_=[])

    def test_arange4(self):
        self.run_test("def np_arange4_():\n from numpy import arange\n return arange(0.2, 9.3, 1)", np_arange4_=[])

    def test_arange5(self):
        self.run_test("def np_arange5_():\n from numpy import arange\n return arange(1, 2, 0.3)", np_arange5_=[])

    def test_arange6(self):
        self.run_test("def np_arange6_():\n from numpy import arange\n return arange(0.2, 3.3, 0.5)", np_arange6_=[])

    #@unittest.skip("Work outside of tests") 
    def test_arange7(self):
        self.run_test("def np_arange7_():\n from numpy import arange\n return arange(1, 4.5, -0.2)", np_arange7_=[])

    def test_arange8(self):
        self.run_test("def np_arange8_():\n from numpy import arange\n return arange(4.5, 1, -0.1)", np_arange8_=[])

    def test_arange9(self):
        self.run_test("def np_arange9_():\n from numpy import arange\n return arange(4.5, -12, -3.2)", np_arange9_=[])

    def test_arange10(self):
        self.run_test("def np_arange10_():\n from numpy import arange\n return arange(-5, -5.5, -0.1)", np_arange10_=[])

    def test_linspace(self):
        self.run_test("def np_linspace_():\n from numpy import linspace\n return linspace(1,4,32)", np_linspace_=[])

    def test_linspace1(self):
        self.run_test("def np_linspace1_():\n from numpy import linspace\n return linspace(0.4,32.5,2)", np_linspace1_=[])

    def test_linspace2(self):
        self.run_test("def np_linspace2_():\n from numpy import linspace\n return linspace(0.4,32.5,32, False)", np_linspace2_=[])

    def test_linspace3(self):
        self.run_test("def np_linspace3_():\n from numpy import linspace\n return linspace(1,4)", np_linspace3_=[])

    def test_sin(self):
        self.run_test("def np_sin_():\n from numpy import sin, linspace\n return sin(linspace(0,6))", np_sin_=[])

    def test_pi(self):
        self.run_test("def np_pi_():\n from numpy import pi\n return pi", np_pi_=[])

    def test_e(self):
        self.run_test("def np_e_():\n from numpy import e\n return e", np_e_=[])

    def test_ones_like_(self):
        self.run_test("def np_ones_like_():\n from numpy import ones_like\n return ones_like([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", np_ones_like_=[])

    def test_zeros_like_(self):
        self.run_test("def np_zeros_like_():\n from numpy import zeros_like\n return zeros_like([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", np_zeros_like_=[])

    def test_reshape_(self):
        self.run_test("def np_reshape_():\n from numpy import arange,reshape\n return arange(10).reshape(2,5)", np_reshape_=[])

    def test_cumsum_(self):
        self.run_test("def np_cumsum_():\n from numpy import arange,cumsum\n return arange(10).cumsum()", np_cumsum_=[])

    def test_cumsum2_(self):
        self.run_test("def np_cumsum2_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum()", np_cumsum2_=[])

    def test_cumsum3_(self):
        self.run_test("def np_cumsum3_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum(1)", np_cumsum3_=[])

    def test_cumsum4_(self):
        self.run_test("def np_cumsum4_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum(0)", np_cumsum4_=[])

    def test_cumsum5_(self):
        self.run_test("def np_cumsum5_():\n from numpy import arange,cumsum\n return arange(10).cumsum(0)", np_cumsum5_=[])

    def test_sum_(self):
        self.run_test("def np_sum_():\n from numpy import arange,sum\n return arange(10).sum()", np_sum_=[])

    def test_sum2_(self):
        self.run_test("def np_sum2_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum()", np_sum2_=[])

    def test_sum3_(self):
        self.run_test("def np_sum3_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum(1)", np_sum3_=[])

    def test_sum4_(self):
        self.run_test("def np_sum4_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum(0)", np_sum4_=[])

    def test_sum5_(self):
        self.run_test("def np_sum5_():\n from numpy import arange,sum\n return arange(10).sum(0)", np_sum5_=[])

    def test_min_(self):
        self.run_test("def np_min_():\n from numpy import arange,min\n return arange(10).min()", np_min_=[])

    def test_min2_(self):
        self.run_test("def np_min2_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min()", np_min2_=[])

    def test_min3_(self):
        self.run_test("def np_min3_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min(1)", np_min3_=[])

    def test_min4_(self):
        self.run_test("def np_min4_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min(0)", np_min4_=[])

    def test_min5_(self):
        self.run_test("def np_min5_():\n from numpy import arange,min\n return arange(10).min(0)", np_min5_=[])

    def test_transpose_(self):
        self.run_test("def np_transpose_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose()", np_transpose_=[])

    def test_transpose2_(self):
        self.run_test("def np_transpose2_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose((2,0,1))", np_transpose2_=[])

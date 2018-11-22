from test_env import TestEnv
from pythran.typing import NDArray, Tuple, List

import numpy

import unittest
import sys

try:
    numpy.float128
    has_float128 = True
except AttributeError:
    has_float128 = False



@TestEnv.module
class TestNdarray(TestEnv):

    def test_ndarray_intc(self):
        self.run_test('def ndarray_intc(a): import numpy as np; return np.intc(a), np.array([a, a], dtype=np.intc)',
                      numpy.intc(5),
                      ndarray_intc=[numpy.intc])

    def test_ndarray_uintc(self):
        self.run_test('def ndarray_uintc(a): import numpy as np; return np.uintc(a), np.array([a, a], dtype=np.uintc)',
                      numpy.uintc(5),
                      ndarray_uintc=[numpy.uintc])

    def test_ndarray_intp(self):
        self.run_test('def ndarray_intp(a): import numpy as np; return np.intp(a), np.array([a, a], dtype=np.intp)',
                      numpy.intp(-5),
                      ndarray_intp=[numpy.intp])

    def test_ndarray_uintp(self):
        self.run_test('def ndarray_uintp(a): import numpy as np; return np.uintp(a), np.array([a, a], dtype=np.uintp)',
                      numpy.uintp(5),
                      ndarray_uintp=[numpy.uintp])

    def test_ndarray_real_attr_read(self):
        self.run_test('def ndarray_real_attr_read(a): return a.real + 1',
                      numpy.arange(100, dtype=numpy.complex128).reshape((10, 10)),
                      ndarray_real_attr_read=[NDArray[complex, :, :]])

    def test_ndarray_imag_attr_read(self):
        self.run_test('def ndarray_imag_attr_read(a): return a.imag + 1',
                      1j * numpy.arange(10, dtype=numpy.complex128),
                      ndarray_imag_attr_read=[NDArray[complex, :]])

    def test_ndarray_real_attr_read_complex64(self):
        self.run_test('def ndarray_real_attr_read_complex64(a): return a.real + 1',
                      numpy.arange(100, dtype=numpy.complex64).reshape((10, 10)),
                      ndarray_real_attr_read_complex64=[NDArray[numpy.complex64, :, :]])

    def test_ndarray_imag_attr_read_complex64(self):
        self.run_test('def ndarray_imag_attr_read_complex64(a): return a.imag + 1',
                      1j * numpy.arange(10, dtype=numpy.complex64),
                      ndarray_imag_attr_read_complex64=[NDArray[numpy.complex64, :]])

    @unittest.expectedFailure
    def test_ndarray_real_attr_write(self):
        self.run_test('def ndarray_real_attr_read(a): a.real = 1 ; return a',
                      numpy.arange(100, dtype=numpy.complex128).reshape((10, 10)),
                      ndarray_real_attr_read=[NDArray[complex, :, :]])

    @unittest.expectedFailure
    def test_ndarray_imag_attr_write(self):
        self.run_test('def ndarray_imag_attr_read(a): a.imag = 1 ; return a',
                      1j * numpy.arange(10, dtype=numpy.complex128),
                      ndarray_imag_attr_read=[NDArray[complex, :]])

    def test_ndarray_real_fun_read(self):
        self.run_test('def ndarray_real_fun_read(a): import numpy as np ; return np.real(a)[1:]',
                      numpy.arange(100, dtype=numpy.complex128).reshape((10, 10)),
                      ndarray_real_fun_read=[NDArray[complex, :, :]])

    def test_ndarray_imag_fun_read(self):
        self.run_test('def ndarray_imag_fun_read(a): import numpy as np ; return - np.imag(a)',
                      1j * numpy.arange(10, dtype=numpy.complex128),
                      ndarray_imag_fun_read=[NDArray[complex, :]])

    def test_numpy_augassign0(self):
        self.run_test('def numpy_augassign0(a): a+=1; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign0=[NDArray[int, :, :]])

    def test_numpy_augassign1(self):
        self.run_test('def numpy_augassign1(a): a*=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign1=[NDArray[int, :, :]])

    def test_numpy_augassign2(self):
        self.run_test('def numpy_augassign2(a): a-=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign2=[NDArray[int, :, :]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_numpy_augassign3(self):
        self.run_test('def numpy_augassign3(a): a/=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign3=[NDArray[int, :, :]])

    def test_numpy_augassign4(self):
        self.run_test('def numpy_augassign4(a): a|=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign4=[NDArray[int, :, :]])

    def test_numpy_augassign5(self):
        self.run_test('def numpy_augassign5(a): a&=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign5=[NDArray[int, :, :]])

    def test_numpy_augassign6(self):
        self.run_test('def helper(x): x //= 2; x+=3\ndef numpy_augassign6(a): a&=2; helper(a); return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign6=[NDArray[int, :, :]])

    def test_numpy_faugassign0(self):
        self.run_test('def numpy_faugassign0(a): a[a>5]+=1; return a',
                      numpy.arange(100),
                      numpy_faugassign0=[NDArray[int, :]])

    def test_numpy_faugassign1(self):
        self.run_test('def numpy_faugassign1(a): a[a>3]*=2; return a',
                      numpy.arange(100),
                      numpy_faugassign1=[NDArray[int, :]])

    def test_numpy_faugassign2(self):
        self.run_test('def numpy_faugassign2(a): a[a>30]-=2; return a',
                      numpy.arange(100),
                      numpy_faugassign2=[NDArray[int, :]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_numpy_faugassign3(self):
        self.run_test('def numpy_faugassign3(a): a[a<40]/=2; return a',
                      numpy.arange(100),
                      numpy_faugassign3=[NDArray[int, :]])

    def test_numpy_faugassign4(self):
        self.run_test('def numpy_faugassign4(a): a[a<4]|=2; return a',
                      numpy.arange(100),
                      numpy_faugassign4=[NDArray[int, :]])

    def test_numpy_faugassign5(self):
        self.run_test('def numpy_faugassign5(a): a[a>8]&=2; return a',
                      numpy.arange(100),
                      numpy_faugassign5=[NDArray[int, :]])

    def test_broadcast0(self):
        self.run_test('def numpy_broadcast0(a): a[0] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast0=[NDArray[int, :, :]])

    def test_broadcast1(self):
        self.run_test('def numpy_broadcast1(a): a[1:-1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast1=[NDArray[int, :, :]])

    def test_broadcast2(self):
        self.run_test('def numpy_broadcast2(a): a[1:-1,1:-1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast2=[NDArray[int, :, :]])

    def test_broadcast3(self):
        self.run_test('def numpy_broadcast3(a): a[1:-1,1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast3=[NDArray[int, :, :]])

    def test_broadcast4(self):
        self.run_test('def numpy_broadcast4(a): a[:,1,1] = 1 ; return a',
                      numpy.arange(100).reshape((5,5,4)),
                      numpy_broadcast4=[NDArray[int, :, :, :]])

    def test_broadcast5(self):
        self.run_test('def numpy_broadcast5(a): import numpy as np ; return a + np.array([1,2,3,4])',
                      numpy.arange(20).reshape((5,4)),
                      numpy_broadcast5=[NDArray[int, :, :]])

    def test_extended_slicing0(self):
        self.run_test("def numpy_extended_slicing0(a): return a[2,1:-1]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing0=[NDArray[int, :, :]])

    def test_extended_slicing1(self):
        self.run_test("def numpy_extended_slicing1(a): return a[1:-1,2]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing1=[NDArray[int, :, :]])

    def test_extended_slicing2(self):
        self.run_test("def numpy_extended_slicing2(a): return a[2,1:-1]",
                      numpy.arange(30).reshape((3,5,2)),
                      numpy_extended_slicing2=[NDArray[int, :, :, :]])

    def test_extended_slicing3(self):
        self.run_test("def numpy_extended_slicing3(a): return a[1:-1,2]",
                      numpy.arange(30).reshape((3,5,2)),
                      numpy_extended_slicing3=[NDArray[int, :,:,:]])

    def test_extended_slicing4(self):
        self.run_test("def numpy_extended_slicing4(a): return a[1:-1,2:-2]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing4=[NDArray[int, :, :]])

    def test_extended_slicing5(self):
        self.run_test("def numpy_extended_slicing5(a): return a[1:-1]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing5=[NDArray[int, :, :]])

    def test_extended_slicing6(self):
        self.run_test("def numpy_extended_slicing6(a): return a[1:-1,2:-2, 3:-3]",
                      numpy.arange(5*6*7).reshape((5,6,7)),
                      numpy_extended_slicing6=[NDArray[int,:,:,:]])

    def test_extended_slicing7(self):
        self.run_test("def numpy_extended_slicing7(a): return a[1:-1, 2, 1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing7=[NDArray[int,:,:,:,:]])

    def test_extended_slicing8(self):
        self.run_test("def numpy_extended_slicing8(a): return a[1:-1,2:-2, 1:2]",
                      numpy.arange(60).reshape((3,5,4)),
                      numpy_extended_slicing8=[NDArray[int,:,:,:]])

    def test_extended_slicing9(self):
        self.run_test("def numpy_extended_slicing9(a): return a[1:-1, 2, 1, 1:2]",
                      numpy.arange(120).reshape((3,5,2,4)),
                      numpy_extended_slicing9=[NDArray[int,:,:,:,:]])

    def test_extended_slicing10(self):
        self.run_test("def numpy_extended_slicing10(a): return a[1, 2, 1:-1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing10=[NDArray[int,:,:,:,:]])

    def test_extended_slicing11(self):
        self.run_test("def numpy_extended_slicing11(a): return a[1, 2, 1:-1, 1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing11=[NDArray[int,:,:,:,:]])

    def test_numpy_mask0(self):
        self.run_test("def numpy_mask0(n): import numpy ; return n[n>0][ n[n>0] < 1]",
                      numpy.cos(numpy.arange(10)),
                      numpy_mask0=[NDArray[float, :]])

    def test_numpy_bool(self):
        self.run_test("def numpy_bool(n): import numpy ; return numpy.ones(n, bool)",
                      5,
                      numpy_bool=[int])

    def test_numpy_int(self):
        self.run_test("def numpy_int(n): import numpy ; return numpy.ones(n, int)",
                      5,
                      numpy_int=[int])

    def test_numpy_float(self):
        self.run_test("def numpy_float(n): import numpy ; return numpy.ones(n, float)",
                      5,
                      numpy_float=[int])

    def test_numpy_int16(self):
        self.run_test("def numpy_int16(n): import numpy ; return numpy.ones(n, numpy.int16)",
                      5,
                      numpy_int16=[int])

    def test_numpy_uint16(self):
        self.run_test("def numpy_uint16(n): import numpy ; return numpy.ones(n, numpy.uint16)",
                      5,
                      numpy_uint16=[int])

    def test_numpy_uint64(self):
        self.run_test("def numpy_uint64(n): import numpy ; return numpy.ones(n, numpy.uint64)",
                      5,
                      numpy_uint64=[int])

    def test_numpy_np_float(self):
        """ Check dtype == numpy.float for numpy array. """
        self.run_test("""
            def numpy_np_float(n):
                import numpy
                return numpy.ones(n, numpy.float)""",
                      5,
                      numpy_np_float=[int])

    def test_numpy_complex(self):
        self.run_test("def numpy_complex(n): import numpy ; return numpy.ones(n, numpy.complex)",
                      5,
                      numpy_complex=[int])

    def test_numpy_complex64(self):
        self.run_test("def numpy_complex64(n): import numpy ; return numpy.ones(n, numpy.complex64)",
                      5,
                      numpy_complex64=[int])

    def test_numpy_double(self):
        self.run_test("def numpy_double(n): import numpy ; return numpy.ones(n, numpy.double)",
                      5,
                      numpy_double=[int])

    def test_numpy_complex_export(self):
        self.run_test("def numpy_complex_export(a): import numpy ; return numpy.sum(a)",
                      numpy.array([1+1j]),
                      numpy_complex_export=[NDArray[complex, :]])

    def test_assign_gsliced_array(self):
        self.run_test("""def assign_gsliced_array():
   import numpy as np;
   a = np.array([[[1,2],[3,4]],[[5,6],[7,8]]])
   b = np.array([[[9,10],[11,12]],[[13,14],[15,16]]])
   a[:,:] = b[:,:]
   return a,b;""", assign_gsliced_array=[])

    def test_assign_sliced_array(self):
        self.run_test("""def assign_sliced_array():
   import numpy as np;
   a = np.array([1,2,3]);
   b = np.array([1,2,3]);
   c=a[1:]
   c=b[1:]
   b[2] = -1;
   return c;""", assign_sliced_array=[])

    def test_index_array_0(self):
        self.run_test('''
            def index_array_0(n):
                import numpy
                a = numpy.arange(n)
                return a[numpy.array([1, 0])]''',
                      10,
                      index_array_0=[int])

    def test_index_array_1(self):
        self.run_test('''
            def index_array_1(n):
                import numpy
                a = numpy.arange(n * 3).reshape(3, n)
                return a[numpy.array([0, 1, 0, 2])]''',
                      10,
                      index_array_1=[int])

    def test_filter_array_0(self):
        self.run_test('def filter_array_0(n): import numpy ; a = numpy.zeros(n) ; return a[a>1]',
                      10,
                      filter_array_0=[int])

    def test_filter_array_1(self):
        self.run_test('def filter_array_1(n): import numpy ; a = numpy.arange(n) ; return a[a>4]',
                      10,
                      filter_array_1=[int])

    def test_filter_array_2(self):
        self.run_test('def filter_array_2(n): import numpy ; a = numpy.arange(n) ; return (a+a)[a>4]',
                      10,
                      filter_array_2=[int])

    def test_filter_array_3(self):
        self.run_test('def filter_array_3(n): import numpy ; a = numpy.arange(n) ; return (-a)[a>4]',
                      10,
                      filter_array_3=[int])

    @unittest.skip("filtering a slice")
    def test_filter_array_4(self):
        self.run_test('def filter_array_4(n): import numpy ; a = numpy.arange(n) ; return a[1:-1][a[1:-1]>4]',
                      10,
                      filter_array_4=[int])

    @unittest.skip("filtering a slice")
    def test_filter_array_5(self):
        self.run_test('def filter_array_5(n): import numpy ; a = numpy.arange(n) ; return (a[1:-1])[a[1:-1]>4]',
                      10,
                      filter_array_5=[int])

    def test_assign_ndarray(self):
        code = """
def assign_ndarray(t):
    import numpy as np;
    a = np.array([1,2,3]);
    b = np.array([1,2,3]);
    if t:
      c = a;
    else:
      c=b;
    if t:
      c=b;
    b[0] = -1;
    return c;"""
        self.run_test(code,
                      1,
                      assign_ndarray=[int])

    def test_bitwise_nan_bool(self):
        self.run_test("def np_bitwise_nan_bool(a): import numpy as np ; return ~(a<5)", numpy.arange(10), np_bitwise_nan_bool=[NDArray[int, :]])

    def test_gslice0(self):
        self.run_test("def np_gslice0(a): import numpy as np; return a[1:9,5:7]", numpy.array(range(10*9)).reshape((10,9)), np_gslice0=[NDArray[int, :, :]])

    def test_gslice1(self):
        self.run_test("def np_gslice1(a): import numpy as np ; return a[1:9,0:1, 3:6]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice1=[NDArray[int, :, :, :]])

    def test_gslice2(self):
        self.run_test("def np_gslice2(a): import numpy as np ; return a[:,0:1, 3:6]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice2=[NDArray[int, :, :, :]])

    def test_gslice3(self):
        self.run_test("def np_gslice3(a): import numpy as np ; return a[:-1,0:-1, -3:7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice3=[NDArray[int, :, :, :]])

    def test_gslice4(self):
        self.run_test("def np_gslice4(a): import numpy as np ; return a[1,0:-1, -3:7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice4=[NDArray[int, :, :, :]])

    def test_gslice5(self):
        self.run_test("def np_gslice5(a): import numpy as np ; return a[1,0:-1, 7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice5=[NDArray[int, :, :, :]])

    def test_gslice6(self):
        self.run_test("def np_gslice6(a): import numpy as np ; return a[:-1, :][1:,:]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice6=[NDArray[int, :,:,:]])

    def test_iexpr0(self):
        self.run_test("def np_iexpr0(a,i): return a[i][0,0]", numpy.array(range(10*9*8)).reshape(10,9,8), 0, np_iexpr0=[NDArray[int, :,:,:], int])

    def test_iexpr1(self):
        self.run_test("def np_iexpr1(a,i): return a[i,0][0]", numpy.array(range(10*9*8)).reshape(10,9,8), 0, np_iexpr1=[NDArray[int, :,:,:], int])

    def test_iexpr2(self):
        self.run_test("def np_iexpr2(a,m): a[m==False] = 1; return a", numpy.arange(10).reshape(5,2), numpy.arange(10).reshape(5,2), np_iexpr2=[NDArray[int, :,:], NDArray[int, :,:]])

    def test_item0(self):
        self.run_test("def np_item0(a): return a.item(3)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item0=[NDArray[int, :,: ]])

    def test_item1(self):
        self.run_test("def np_item1(a): return a.item(7)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item1=[NDArray[int, :,: ]])

    def test_item2(self):
        self.run_test("def np_item2(a): return a.item((0,1))",numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]),  np_item2=[NDArray[int, :,: ]])

    def test_item3(self):
        self.run_test("def np_item3(a): return a.item((2,2))", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item3=[NDArray[int, :,: ]])

    def test_item4(self):
        self.run_test("def np_item4(a): return a.item(-2)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item4=[NDArray[int, :,: ]])

    def test_acces1D_(self):
        self.run_test("def np_acces1D_(a): return a[1]", numpy.array([1,2,3]), np_acces1D_=[NDArray[int, :]])

    def test_accesSimple_(self):
        self.run_test("def np_accesSimple_(a): return a[1]", numpy.array([[1,2],[3,4]]), np_accesSimple_=[NDArray[int, :,: ]])

    def test_accesMultiple_(self):
        self.run_test("def np_accesMultiple_(a): return a[1,0]", numpy.array([[1,2],[3,4]]), np_accesMultiple_=[NDArray[int, :,: ]])

    def test_accesMultipleND_(self):
        self.run_test("def np_accesMultipleND_(a): return a[1,0]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_accesMultipleND_=[NDArray[int, :,:,:]])

    def test_accesMultipleNDSplit_(self):
        self.run_test("def np_accesMultipleNDSplit_(a): return a[1][0]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_accesMultipleNDSplit_=[NDArray[int, :,:,:]])

    def test_shape_(self):
        self.run_test("def np_shape_(a): return a.shape", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_shape_=[NDArray[int, :,:,:]])

    def test_change_arrayND_(self):
        self.run_test("def np_change_arrayND_(a):\n from numpy import array\n a[0,0] = array([99,99])\n return a", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_change_arrayND_=[NDArray[int, :,:,:]])

    def test_ndim_(self):
        self.run_test("def np_ndim_(a): return a.ndim", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_ndim_=[NDArray[int, :,:,:]])

    def test_stride_(self):
        self.run_test("def np_stride_(a): return a.strides", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_stride_=[NDArray[int, :,:,:]])

    def test_size_(self):
        self.run_test("def np_size_(a): return a.size", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_size_=[NDArray[int, :,:,:]])

    def test_itemsize_(self):
        self.run_test("def np_itemsize_(a): return a.itemsize", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_itemsize_=[NDArray[int, :,:,:]])

    def test_nbytes_(self):
        self.run_test("def np_nbytes_(a): return a.nbytes", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_nbytes_=[NDArray[int, :,:,:]])

    def test_flat_(self):
        self.run_test("def np_flat_(a): return [i for i in a.flat]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_flat_=[NDArray[int, :,:,:]])

    def test_sliced0(self):
        self.run_test("def np_sliced0(a): return a[2:12]", numpy.ones(20), np_sliced0=[NDArray[float, :]])

    def test_sliced1(self):
        self.run_test("def np_sliced1(a): return a[2:12:3]", numpy.ones(20), np_sliced1=[NDArray[float, :]])

    def test_sliced2(self):
        self.run_test("def np_sliced2(a): return -a[2:12:3]", numpy.ones(20), np_sliced2=[NDArray[float, :]])

    def test_sliced3(self):
        self.run_test("def np_sliced3(a): return a[1:11:3] -a[2:12:3]", numpy.ones(20), np_sliced3=[NDArray[float, :]])

    def test_sliced4(self):
        self.run_test("def np_sliced4(a): return a[1:11] -a[2:12]", numpy.ones(20), np_sliced4=[NDArray[float, :]])

    def test_sliced5(self):
        self.run_test("def np_sliced5(a): return (-a[1:11]) + 3*a[2:12]", numpy.ones(20), np_sliced5=[NDArray[float, :]])

    def test_sliced6(self):
        self.run_test("def np_sliced6(a): return a[3:4]", numpy.arange(12).reshape(6,2), np_sliced6=[NDArray[int, :,: ]])

    def test_sliced7(self):
        self.run_test("def np_sliced7(a): a[3:4] = 1 ; return a", numpy.arange(12).reshape(6,2), np_sliced7=[NDArray[int, :,: ]])

    def test_sliced8(self):
        self.run_test("def np_sliced8(a): a[1:2] = 1 ; return a", numpy.arange(12).reshape(3,2,2), np_sliced8=[NDArray[int, :,:,:]])

    def test_sliced9(self):
        self.run_test("def np_sliced9(a): from numpy import arange ; a[1:2] = arange(4).reshape((1,2,2)) ; return a", numpy.arange(12).reshape(3,2,2), np_sliced9=[NDArray[int, :,:,:]])

    def test_sliced10(self):
        self.run_test("def np_sliced10(a): from numpy import arange ; a[1:-1:2] = arange(4).reshape((1,2,2)) ; return a", numpy.arange(12).reshape(3,2,2), np_sliced10=[NDArray[int, :,:,:]])

    def test_sliced11(self):
        self.run_test("def np_sliced11(a): return a[1::-2]", numpy.arange(12).reshape(3,2,2), np_sliced11=[NDArray[int, :,:,:]])

    def test_sliced12(self):
        self.run_test("def np_sliced12(a): return a[1::-2]", numpy.arange(12), np_sliced12=[NDArray[int, :]])

    def test_sliced13(self):
        self.run_test("def np_sliced13(a): return a[3::-3]", numpy.arange(11), np_sliced13=[NDArray[int, :]])

    def test_newaxis0(self):
        self.run_test("def np_newaxis0(a): return a[None]",
                      numpy.ones(5), np_newaxis0=[NDArray[float, :]])

    def test_newaxis1(self):
        self.run_test("def np_newaxis1(a): from numpy import newaxis; return a[newaxis]",
                      numpy.ones(5), np_newaxis1=[NDArray[float, :]])

    def test_newaxis2(self):
        self.run_test("def np_newaxis2(a): from numpy import newaxis; return a[newaxis,:,newaxis]",
                      numpy.ones(5), np_newaxis2=[NDArray[float, :]])

    def test_newaxis3(self):
        self.run_test("def np_newaxis3(a): from numpy import newaxis; return a[:,newaxis]",
                      numpy.ones(5), np_newaxis3=[NDArray[float, :]])

    def test_newaxis4(self):
                      self.run_test("def np_newaxis4(a): from numpy import newaxis; return a[newaxis,:,:]",
                                    numpy.ones((2,3)), np_newaxis4=[NDArray[float, :,: ]])

    def test_newaxis5(self):
        self.run_test("def np_newaxis5(a): from numpy import newaxis; return a[:,newaxis,:]",
                      numpy.ones((2,3)), np_newaxis5=[NDArray[float, :,: ]])

    def test_newaxis6(self):
        self.run_test("def np_newaxis6(a): from numpy import newaxis; return a[:,:,newaxis]",
                      numpy.ones((2,3)), np_newaxis6=[NDArray[float, :,: ]])

    def test_newaxis7(self):
        self.run_test("def np_newaxis7(a): from numpy import newaxis; return a[newaxis,1:,newaxis,:1,newaxis]",
                      numpy.ones((2,3)), np_newaxis7=[NDArray[float, :,: ]])

    def test_gexpr_composition0(self):
        self.run_test("def gexpr_composition0(a): return a[:,:,:][1]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition0=[NDArray[int, :,:,:, :]])

    def test_gexpr_composition1(self):
        self.run_test("def gexpr_composition1(a): return a[:,:,:][1,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition1=[NDArray[int,:,:,:,:]])

    def test_gexpr_composition2(self):
        self.run_test("def gexpr_composition2(a): return a[:,:,:][1,:,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition2=[NDArray[int,:,:,:,:]])

    def test_gexpr_composition3(self):
        self.run_test("def gexpr_composition3(a): return a[:,1,:][:,:,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition3=[NDArray[int,:,:,:,:]])

    def test_gexpr_composition4(self):
        self.run_test("def gexpr_composition4(a): return a[:,:,1][:,:,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition4=[NDArray[int,:,:,:,:]])

    def test_gexpr_composition5(self):
        self.run_test("def gexpr_composition5(a): return a[:,1,:][:,1,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition5=[NDArray[int,:,:,:,:]])

    def test_gexpr_composition6(self):
        self.run_test("def gexpr_composition6(a): return a[:,:,1][:,1,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition6=[NDArray[int,:,:,:,:]])

    def test_gexpr_composition7(self):
        self.run_test("def gexpr_composition7(a): return a[::2][::2]",
                      numpy.arange(16),
                      gexpr_composition7=[NDArray[int, :]])

    def test_gexpr_composition8(self):
        self.run_test("def gexpr_composition8(a): return a[1::2][2::2]",
                      numpy.arange(16),
                      gexpr_composition8=[NDArray[int, :]])

    def test_gexpr_composition9(self):
        self.run_test("def gexpr_composition9(a): return a[:1:2][:2:2]",
                      numpy.arange(16),
                      gexpr_composition9=[NDArray[int, :]])

    @unittest.skip("Unknown slice combination")
    def test_gexpr_composition10(self):
        self.run_test("def gexpr_composition10(a): return a[:-1:2][:-2:2]",
                      numpy.arange(16),
                      gexpr_composition10=[NDArray[int, :]])

    @unittest.skip("Unknown slice combination")
    def test_gexpr_composition11(self):
        self.run_test("def gexpr_composition11(a): return a[::2][::-2]",
                      numpy.arange(17),
                      gexpr_composition11=[NDArray[int, :]])

    @unittest.skip("Unknown slice combination")
    def test_gexpr_composition12(self):
        self.run_test("def gexpr_composition12(a): return a[::-2][::-2]",
                      numpy.arange(13),
                      gexpr_composition12=[NDArray[int, :]])

    def test_gexpr_composition13(self):
        self.run_test("def gexpr_composition13(a): return a[::-3][::2]",
                      numpy.arange(17),
                      gexpr_composition13=[NDArray[int, :]])

    def test_gexpr_composition14(self):
        self.run_test("def gexpr_composition14(a): return a[:,::2][:,1,::-2]",
                      numpy.arange(16).reshape(1,4,4),
                      gexpr_composition14=[NDArray[int, :,:,:]])

    def test_gexpr_composition15(self):
        self.run_test("def gexpr_composition15(a): return a[:,1,1:-1][:,:-1]",
                      numpy.arange(16).reshape(1,4,4),
                      gexpr_composition15=[NDArray[int, :,:,:]])

    def test_gexpr_composition16(self):
        self.run_test("def gexpr_composition16(a): return a[:,None][:,:,None]",
                      numpy.arange(16).reshape(4,4),
                      gexpr_composition16=[NDArray[int, :,:]])

    def test_gexpr_composition17(self):
        self.run_test("def gexpr_composition17(a): return a[:,None][:,None]",
                      numpy.arange(16).reshape(1,4,4),
                      gexpr_composition17=[NDArray[int, :,:,:]])

    def test_gexpr_composition18(self):
        self.run_test("def gexpr_composition18(a): return a[0,:,None][:,None]",
                      numpy.arange(24).reshape(2,3,4),
                      gexpr_composition18=[NDArray[int, :,:,:]])


    def test_gexpr_copy0(self):
        self.run_test("def gexpr_copy0(a,b): a[:,0] = b[:,0]; return a",
                      numpy.arange(16).reshape(8,2), numpy.arange(16).reshape(8,2),
                      gexpr_copy0=[NDArray[int, :,: ], NDArray[int, :,: ]])

    def test_ndarray_iter0(self):
        self.run_test("def ndarray_iter0(a): return map(str, a)",
                      numpy.arange(16),
                      ndarray_iter0=[NDArray[int, :]])

    def test_ndarray_iter1(self):
        self.run_test("""
                      def ndarray_iter1(a):
                        s = 0
                        for v in a:
                            s *= v
                        return s""",
                      numpy.arange(16),
                      ndarray_iter1=[NDArray[int, :]])

    def test_ndarray_str_dtype0(self):
        self.run_test("def ndarray_str_dtype0(a): return str(a.dtype)",
                      numpy.arange(16),
                      ndarray_str_dtype0=[NDArray[int, :]])

    def test_ndarray_str_dtype1(self):
        self.run_test("def ndarray_str_dtype1(a): return str(a.dtype)",
                      numpy.arange(16.),
                      ndarray_str_dtype1=[NDArray[float, :]])

    def test_ndarray_fancy_indexing0(self):
        self.run_test("def ndarray_fancy_indexing0(a,b): return a[b]",
                numpy.arange(8.),
                numpy.arange(8),
                ndarray_fancy_indexing0=[NDArray[float, :], NDArray[int, :]])

    def test_ndarray_fancy_indexing1(self):
        self.run_test("def ndarray_fancy_indexing1(a,b): return a[b]",
                numpy.arange(8.).reshape(4,2),
                numpy.array([0,1], dtype=int),
                ndarray_fancy_indexing1=[NDArray[float, :, :], NDArray[int, :]])

    def test_ndarray_fancy_indexing2(self):
        self.run_test("def ndarray_fancy_indexing2(a,b): return a[b]",
                numpy.arange(8.).reshape(4,2),
                numpy.array([3,2,1,0, 0], dtype=int),
                ndarray_fancy_indexing2=[NDArray[float, :, :], NDArray[int, :]])

    def test_ndarray_fancy_indexing3(self):
        self.run_test("def ndarray_fancy_indexing3(a,b): return a[b]",
                numpy.arange(8.).reshape(4,2),
                numpy.array([3,2,1,0], dtype=int),
                ndarray_fancy_indexing3=[NDArray[float, :, :], NDArray[int, :]])

    def test_ndarray_ubyte(self):
        self.run_test("def ndarray_ubyte(n): import numpy; return numpy.arange(0, n, 1, dtype=numpy.ubyte)",
                4,
                ndarray_ubyte=[int])

    def test_ndarray_1d_index(self):
        self.run_test(
            'def ndarray_1d_index(a): return a[1], a[-1]',
            numpy.arange(30).reshape((2,3,5)),
            ndarray_1d_index=[NDArray[int, :, :,:]])

    def test_ndarray_2d_index(self):
        self.run_test(
            'def ndarray_2d_index(a): return a[0,1], a[0, -1]',
            numpy.arange(30).reshape((2,3,5)),
            ndarray_2d_index=[NDArray[int, :, :,:]])

    def test_ndarray_3d_index(self):
        self.run_test(
            'def ndarray_3d_index(a): return a[0, 1, 2], a[0, -1, -2]',
            numpy.arange(30).reshape((2,3,5)),
            ndarray_3d_index=[NDArray[int, :, :,:]])

    def test_numpy_iexpr_1d_index(self):
        self.run_test(
            'def numpy_iexpr_1d_index(A): a = A[0]; return a[1], a[-1]',
            numpy.arange(30).reshape((1, 2,3,5)),
            numpy_iexpr_1d_index=[NDArray[int, :, :,:, :]])

    def test_numpy_iexpr_2d_index(self):
        self.run_test(
            'def numpy_iexpr_2d_index(A): a = A[0]; return a[0,1], a[0, -1]',
            numpy.arange(30).reshape((1, 2,3,5)),
            numpy_iexpr_2d_index=[NDArray[int, :, :,:, :]])

    def test_numpy_iexpr_3d_index(self):
        self.run_test(
            'def numpy_iexpr_3d_index(A): a = A[0]; return a[0, 1, 2], a[0, -1, -2]',
            numpy.arange(30).reshape((1, 2,3,5)),
            numpy_iexpr_3d_index=[NDArray[int, :, :,:, :]])


    def test_numpy_indexing_ex0(self):
        self.run_test(
            'def numpy_indexing_ex0(x, y): return x[y]',
            numpy.array([1,2,3,4]),
            (0,),
            numpy_indexing_ex0=[NDArray[int, :], Tuple[int]])

    def test_numpy_indexing_ex1(self):
        self.run_test(
            'def numpy_indexing_ex1(x, y): return x[y]',
            numpy.array([[1,2],[3,4]]),
            (0, 1),
            numpy_indexing_ex1=[NDArray[int, :, :], Tuple[int, int]])

    def test_numpy_indexing_ex2(self):
        self.run_test(
            'def numpy_indexing_ex2(x, y): return x[y, :]',
            numpy.array([[1,2],[3,4]]),
            0,
            numpy_indexing_ex2=[NDArray[int, :, :], int])

    def test_numpy_indexing_ex3(self):
        self.run_test(
            'def numpy_indexing_ex3(x, y): return x[y]',
            numpy.array([[1,2],[3,4]]),
            [1],
            numpy_indexing_ex3=[NDArray[int, :, :], List[int]])

    def test_numpy_indexing_ex4(self):
        self.run_test(
            'def numpy_indexing_ex4(x, y): return x[:,:][y]',
            numpy.array([[1,2],[3,4]]),
            [1],
            numpy_indexing_ex4=[NDArray[int, :, :], List[int]])

    def test_numpy_expr_combiner(self):
        code = '''
            import numpy as np

            def abcd(x, y):
                return np.linspace(0, x, y)

            def ops(a, b, o):
                return 4.0 * np.pi / a * np.sin(0.5 * np.arctan(o / b))

            def efgh(x, y):
                a = abcd(x, y)
                if x == 2:
                    c = ops(2.0, 3.0, a * 3.0) # Comment here
                    #c = a # decoment here
                else:
                    c = a # And here
                    #c = ops(2.0, 3.0, a * 3.0) # and here
                return c[:-1]

            def numpy_expr_combiner(x, y):
                b = efgh(x, y)
                return b'''
        self.run_test(code,
                      10, 10,
                      numpy_expr_combiner=[int, int])

    def test_bool_conversion_0(self):
        code = 'def bool_conversion_0(x): return bool(x)'
        self.run_test(code,
                      numpy.array([[1]]),
                      bool_conversion_0=[NDArray[int, :,:]])

    def test_bool_conversion_1(self):
        code = 'def bool_conversion_1(x): return bool(x > 1)'
        self.run_test(code,
                      numpy.array([1]),
                      bool_conversion_1=[NDArray[int, :]])

    def test_bool_conversion_2(self):
        code = 'def bool_conversion_2(x): return bool(x[1:,1,1:])'
        self.run_test(code,
                      numpy.array([[[1,1],[1,1]],
                                   [[1,0],[1,1]]]
                                   ),
                                   bool_conversion_2=[NDArray[int, :,:,:]])

    def test_bool_conversion_3(self):
        code = 'def bool_conversion_3(x): return bool(x[1])'
        self.run_test(code,
                      numpy.array([[1],[0]]),
                      bool_conversion_3=[NDArray[int, :,:]])

    def test_bool_conversion_4(self):
        code = 'def bool_conversion_4(x): return bool(x.T)'
        self.run_test(code,
                      numpy.array([[1]]),
                      bool_conversion_4=[NDArray[int, :,:]])

    def test_numpy_lazy_gexpr(self):
        code = '''
            import numpy as np

            def efgh2(s, m, x, y):
                if x == 0: # Without the if it doesn't compile
                    return np.zeros(10)[:-1]
                return np.zeros(10)[:-1]

            def numpy_lazy_gexpr(s, m, x, y):
                if m == 'a':
                    b = efgh2(s, m, x, y + 1)
                else:
                    b = efgh2(s, m, x, y)
                return b'''
        self.run_test(code,
                      10, "b", 10, 10,
                      numpy_lazy_gexpr=[int, str, int, int])

    def test_fexpr0(self):
        code = '''
            import numpy as np
            def test_fexpr0(peaks):
                peaks = peaks[peaks>30] # <- does not compiles
                lastBin = 0
                for peak in peaks:
                    lastBin = peak
                return lastBin'''
        self.run_test(code, numpy.array([1,32,33,4]), test_fexpr0=[NDArray[int, :]])

    def test_fexpr1(self):
        code = '''
            import numpy as np
            def yy(x):
                a = np.zeros(x, np.float32)
                return a[:-1]

            def test_fexpr1(x):
                c = yy(x)
                d = yy(x)
                c[d == 0] = np.nan
                return c'''
        self.run_test(code, 10, test_fexpr1=[int])


    def test_vexpr0(self):
        code = '''
            import numpy as np
            def vexpr0(a, b=None):
                if b is None:
                    assert len(a) > 0
                    b = np.copy(a[0])
                    a = a[1:]
                else:
                    b = np.copy(b)
                m = b >= 0
                for array in a:
                    b[m] *= array[m]
                return b'''
        self.run_test(code,
            [numpy.arange(10, dtype=numpy.int32).reshape(5,2)],
            2 * numpy.arange(10, dtype=numpy.int32).reshape(5,2),
            vexpr0=[List[NDArray[numpy.int32,:,:]], NDArray[numpy.int32,:,:]])

    def test_array_of_pshape(self):
        code = 'def array_of_pshape(x): from numpy import array; return array(x[None].shape)'
        self.run_test(code, numpy.arange(10), array_of_pshape=[NDArray[int,:]])

    def test_vexpr_of_texpr(self):
        code = '''
        import numpy as np
        def apply_mask(mat, mask):
            assert mask.shape == mat.shape
            mat[mask == False] = np.nan
            return mat

        def vexpr_of_texpr(a, b):
            return apply_mask(a.T, b), apply_mask(a, b.T), apply_mask(a.T, b.T)'''
        self.run_test(code,
                      numpy.arange(4., dtype=numpy.float32).reshape(2,2),
                      numpy.array([[False,True],[True, False]]),
                      vexpr_of_texpr=[NDArray[numpy.float32,:,:], NDArray[numpy.bool,:,:]])

    def test_indexing_through_int8(self):
        code = '''
            def indexing_through_int8(x):
                return x[x[0,0],x[0,1]]'''
        self.run_test(code,
                      numpy.arange(10, dtype=numpy.uint8).reshape(5,2),
                      indexing_through_int8=[NDArray[numpy.uint8,:,:]])

    def test_complex_scalar_broadcast(self):
        self.run_test('def complex_scalar_broadcast(a): return (a**2 * (1 + a) + 2) / 5.',
                      numpy.ones((10,10), dtype=complex),
                      complex_scalar_broadcast=[NDArray[complex, :, :]])


    @unittest.skipIf(not has_float128, "not float128")
    def test_float128_0(self):
        self.run_test('def float128_0(x): return x, x **2',
                      numpy.float128(numpy.finfo(numpy.float64).max),
                      float128_0=[numpy.float128])

    @unittest.skipIf(not has_float128, "not float128")
    def test_float128_1(self):
        self.run_test('def float128_1(x): return x, x **2',
                      numpy.ones((10,10), dtype=numpy.float128),
                      float128_1=[NDArray[numpy.float128,:, :]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_float128_2(self):
        self.run_test('def float128_2(x): from numpy import ones, float128; return ones(x,dtype=float128)',
                      3,
                      float128_2=[int])

    def test_texpr_expr_combined(self):
        self.run_test("def texpr_expr_combined(x, y):\n if x: return y.T\n else: return y * 2",
                      1,
                      numpy.arange(10).reshape(5, 2),
                      texpr_expr_combined=[int, NDArray[int,:,:]])

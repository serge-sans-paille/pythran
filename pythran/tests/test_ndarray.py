import unittest
from test_env import TestEnv
import numpy


@TestEnv.module
class TestNdarray(TestEnv):
    def test_ndarray_real_attr_read(self):
        self.run_test('def ndarray_real_attr_read(a): return a.real + 1',
                      numpy.arange(100, dtype=numpy.complex128).reshape((10, 10)),
                      ndarray_real_attr_read=[numpy.array([[complex]])])

    def test_ndarray_imag_attr_read(self):
        self.run_test('def ndarray_imag_attr_read(a): return a.imag + 1',
                      1j * numpy.arange(10, dtype=numpy.complex128),
                      ndarray_imag_attr_read=[numpy.array([complex])])

    def test_ndarray_real_attr_read_complex64(self):
        self.run_test('def ndarray_real_attr_read_complex64(a): return a.real + 1',
                      numpy.arange(100, dtype=numpy.complex64).reshape((10, 10)),
                      ndarray_real_attr_read_complex64=[numpy.array([[numpy.complex64]])])

    def test_ndarray_imag_attr_read_complex64(self):
        self.run_test('def ndarray_imag_attr_read_complex64(a): return a.imag + 1',
                      1j * numpy.arange(10, dtype=numpy.complex64),
                      ndarray_imag_attr_read_complex64=[numpy.array([numpy.complex64])])

    @unittest.expectedFailure
    def test_ndarray_real_attr_write(self):
        self.run_test('def ndarray_real_attr_read(a): a.real = 1 ; return a',
                      numpy.arange(100, dtype=numpy.complex128).reshape((10, 10)),
                      ndarray_real_attr_read=[numpy.array([[complex]])])

    @unittest.expectedFailure
    def test_ndarray_imag_attr_write(self):
        self.run_test('def ndarray_imag_attr_read(a): a.imag = 1 ; return a',
                      1j * numpy.arange(10, dtype=numpy.complex128),
                      ndarray_imag_attr_read=[numpy.array([complex])])

    def test_ndarray_real_fun_read(self):
        self.run_test('def ndarray_real_fun_read(a): import numpy as np ; return np.real(a)[1:]',
                      numpy.arange(100, dtype=numpy.complex128).reshape((10, 10)),
                      ndarray_real_fun_read=[numpy.array([[complex]])])

    def test_ndarray_imag_fun_read(self):
        self.run_test('def ndarray_imag_fun_read(a): import numpy as np ; return - np.imag(a)',
                      1j * numpy.arange(10, dtype=numpy.complex128),
                      ndarray_imag_fun_read=[numpy.array([complex])])

    def test_numpy_augassign0(self):
        self.run_test('def numpy_augassign0(a): a+=1; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign0=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign1(self):
        self.run_test('def numpy_augassign1(a): a*=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign1=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign2(self):
        self.run_test('def numpy_augassign2(a): a-=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign2=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign3(self):
        self.run_test('def numpy_augassign3(a): a/=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign3=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign4(self):
        self.run_test('def numpy_augassign4(a): a|=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign4=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign5(self):
        self.run_test('def numpy_augassign5(a): a&=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign5=[numpy.array([numpy.array([int])])])

    def test_numpy_faugassign0(self):
        self.run_test('def numpy_faugassign0(a): a[a>5]+=1; return a',
                      numpy.arange(100),
                      numpy_faugassign0=[numpy.array([int])])

    def test_numpy_faugassign1(self):
        self.run_test('def numpy_faugassign1(a): a[a>3]*=2; return a',
                      numpy.arange(100),
                      numpy_faugassign1=[numpy.array([int])])

    def test_numpy_faugassign2(self):
        self.run_test('def numpy_faugassign2(a): a[a>30]-=2; return a',
                      numpy.arange(100),
                      numpy_faugassign2=[numpy.array([int])])

    def test_numpy_faugassign3(self):
        self.run_test('def numpy_faugassign3(a): a[a<40]/=2; return a',
                      numpy.arange(100),
                      numpy_faugassign3=[numpy.array([int])])

    def test_numpy_faugassign4(self):
        self.run_test('def numpy_faugassign4(a): a[a<4]|=2; return a',
                      numpy.arange(100),
                      numpy_faugassign4=[numpy.array([int])])

    def test_numpy_faugassign5(self):
        self.run_test('def numpy_faugassign5(a): a[a>8]&=2; return a',
                      numpy.arange(100),
                      numpy_faugassign5=[numpy.array([int])])

    def test_broadcast0(self):
        self.run_test('def numpy_broadcast0(a): a[0] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast0=[numpy.array([numpy.array([int])])])

    def test_broadcast1(self):
        self.run_test('def numpy_broadcast1(a): a[1:-1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast1=[numpy.array([numpy.array([int])])])

    def test_broadcast2(self):
        self.run_test('def numpy_broadcast2(a): a[1:-1,1:-1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast2=[numpy.array([numpy.array([int])])])

    def test_broadcast3(self):
        self.run_test('def numpy_broadcast3(a): a[1:-1,1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast3=[numpy.array([numpy.array([int])])])

    def test_broadcast4(self):
        self.run_test('def numpy_broadcast4(a): a[:,1,1] = 1 ; return a',
                      numpy.arange(100).reshape((5,5,4)),
                      numpy_broadcast4=[numpy.array([[[int]]])])

    def test_broadcast5(self):
        self.run_test('def numpy_broadcast5(a): import numpy as np ; return a + np.array([1,2,3,4])',
                      numpy.arange(20).reshape((5,4)),
                      numpy_broadcast5=[numpy.array([[int]])])

    def test_extended_slicing0(self):
        self.run_test("def numpy_extended_slicing0(a): return a[2,1:-1]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing0=[numpy.array([numpy.array([int])])])

    def test_extended_slicing1(self):
        self.run_test("def numpy_extended_slicing1(a): return a[1:-1,2]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing1=[numpy.array([numpy.array([int])])])

    def test_extended_slicing2(self):
        self.run_test("def numpy_extended_slicing2(a): return a[2,1:-1]",
                      numpy.arange(30).reshape((3,5,2)),
                      numpy_extended_slicing2=[numpy.array([numpy.array([numpy.array([int])])])])

    def test_extended_slicing3(self):
        self.run_test("def numpy_extended_slicing3(a): return a[1:-1,2]",
                      numpy.arange(30).reshape((3,5,2)),
                      numpy_extended_slicing3=[numpy.array([[[int]]])])

    def test_extended_slicing4(self):
        self.run_test("def numpy_extended_slicing4(a): return a[1:-1,2:-2]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing4=[numpy.array([numpy.array([int])])])

    def test_extended_slicing5(self):
        self.run_test("def numpy_extended_slicing5(a): return a[1:-1]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing5=[numpy.array([numpy.array([int])])])

    def test_extended_slicing6(self):
        self.run_test("def numpy_extended_slicing6(a): return a[1:-1,2:-2, 3:-3]",
                      numpy.arange(5*6*7).reshape((5,6,7)),
                      numpy_extended_slicing6=[numpy.array([numpy.array([numpy.array([int])])])])

    def test_extended_slicing7(self):
        self.run_test("def numpy_extended_slicing7(a): return a[1:-1, 2, 1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing7=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_slicing8(self):
        self.run_test("def numpy_extended_slicing8(a): return a[1:-1,2:-2, 1:2]",
                      numpy.arange(60).reshape((3,5,4)),
                      numpy_extended_slicing8=[numpy.array([numpy.array([numpy.array([int])])])])

    def test_extended_slicing9(self):
        self.run_test("def numpy_extended_slicing9(a): return a[1:-1, 2, 1, 1:2]",
                      numpy.arange(120).reshape((3,5,2,4)),
                      numpy_extended_slicing9=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_slicing10(self):
        self.run_test("def numpy_extended_slicing10(a): return a[1, 2, 1:-1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing10=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_slicing11(self):
        self.run_test("def numpy_extended_slicing11(a): return a[1, 2, 1:-1, 1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing11=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_numpy_mask0(self):
        self.run_test("def numpy_mask0(n): import numpy ; return n[n>0][ n[n>0] < 1]",
                      numpy.cos(numpy.arange(10)),
                      numpy_mask0=[numpy.array([float])])

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
                      numpy_complex_export=[numpy.array([complex])])

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
        self.run_test("def np_bitwise_nan_bool(a): import numpy as np ; return ~(a<5)", numpy.arange(10), np_bitwise_nan_bool=[numpy.array([int])])

    def test_gslice0(self):
        self.run_test("def np_gslice0(a): import numpy as np; return a[1:9,5:7]", numpy.array(range(10*9)).reshape((10,9)), np_gslice0=[numpy.array([[int]])])

    def test_gslice1(self):
        self.run_test("def np_gslice1(a): import numpy as np ; return a[1:9,0:1, 3:6]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice1=[numpy.array([[[int]]])])

    def test_gslice2(self):
        self.run_test("def np_gslice2(a): import numpy as np ; return a[:,0:1, 3:6]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice2=[numpy.array([[[int]]])])

    def test_gslice3(self):
        self.run_test("def np_gslice3(a): import numpy as np ; return a[:-1,0:-1, -3:7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice3=[numpy.array([[[int]]])])

    def test_gslice4(self):
        self.run_test("def np_gslice4(a): import numpy as np ; return a[1,0:-1, -3:7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice4=[numpy.array([[[int]]])])

    def test_gslice5(self):
        self.run_test("def np_gslice5(a): import numpy as np ; return a[1,0:-1, 7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice5=[numpy.array([[[int]]])])

    def test_gslice6(self):
        self.run_test("def np_gslice6(a): import numpy as np ; return a[:-1, :][1:,:]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice6=[numpy.array([[[int]]])])

    def test_iexpr0(self):
        self.run_test("def np_iexpr0(a,i): return a[i][0,0]", numpy.array(range(10*9*8)).reshape(10,9,8), 0, np_iexpr0=[numpy.array([[[int]]]), int])

    def test_iexpr1(self):
        self.run_test("def np_iexpr1(a,i): return a[i,0][0]", numpy.array(range(10*9*8)).reshape(10,9,8), 0, np_iexpr1=[numpy.array([[[int]]]), int])

    def test_item0(self):
        self.run_test("def np_item0(a): return a.item(3)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item0=[numpy.array([[int]])])

    def test_item1(self):
        self.run_test("def np_item1(a): return a.item(7)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item1=[numpy.array([[int]])])

    def test_item2(self):
        self.run_test("def np_item2(a): return a.item((0,1))",numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]),  np_item2=[numpy.array([[int]])])

    def test_item3(self):
        self.run_test("def np_item3(a): return a.item((2,2))", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item3=[numpy.array([[int]])])

    def test_item4(self):
        self.run_test("def np_item4(a): return a.item(-2)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item4=[numpy.array([[int]])])

    def test_acces1D_(self):
        self.run_test("def np_acces1D_(a): return a[1]", numpy.array([1,2,3]), np_acces1D_=[numpy.array([int])])

    def test_accesSimple_(self):
        self.run_test("def np_accesSimple_(a): return a[1]", numpy.array([[1,2],[3,4]]), np_accesSimple_=[numpy.array([[int]])])

    def test_accesMultiple_(self):
        self.run_test("def np_accesMultiple_(a): return a[1,0]", numpy.array([[1,2],[3,4]]), np_accesMultiple_=[numpy.array([[int]])])

    def test_accesMultipleND_(self):
        self.run_test("def np_accesMultipleND_(a): return a[1,0]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_accesMultipleND_=[numpy.array([[[int]]])])

    def test_accesMultipleNDSplit_(self):
        self.run_test("def np_accesMultipleNDSplit_(a): return a[1][0]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_accesMultipleNDSplit_=[numpy.array([[[int]]])])

    def test_shape_(self):
        self.run_test("def np_shape_(a): return a.shape", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_shape_=[numpy.array([[[int]]])])

    def test_change_arrayND_(self):
        self.run_test("def np_change_arrayND_(a):\n from numpy import array\n a[0,0] = array([99,99])\n return a", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_change_arrayND_=[numpy.array([[[int]]])])

    def test_ndim_(self):
        self.run_test("def np_ndim_(a): return a.ndim", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_ndim_=[numpy.array([[[int]]])])

    def test_stride_(self):
        self.run_test("def np_stride_(a): return a.strides", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_stride_=[numpy.array([[[int]]])])

    def test_size_(self):
        self.run_test("def np_size_(a): return a.size", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_size_=[numpy.array([[[int]]])])

    def test_itemsize_(self):
        self.run_test("def np_itemsize_(a): return a.itemsize", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_itemsize_=[numpy.array([[[int]]])])

    def test_nbytes_(self):
        self.run_test("def np_nbytes_(a): return a.nbytes", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_nbytes_=[numpy.array([[[int]]])])

    def test_flat_(self):
        self.run_test("def np_flat_(a): return [i for i in a.flat]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_flat_=[numpy.array([[[int]]])])

    def test_sliced0(self):
        self.run_test("def np_sliced0(a): return a[2:12]", numpy.ones(20), np_sliced0=[numpy.array([float])])

    def test_sliced1(self):
        self.run_test("def np_sliced1(a): return a[2:12:3]", numpy.ones(20), np_sliced1=[numpy.array([float])])

    def test_sliced2(self):
        self.run_test("def np_sliced2(a): return -a[2:12:3]", numpy.ones(20), np_sliced2=[numpy.array([float])])

    def test_sliced3(self):
        self.run_test("def np_sliced3(a): return a[1:11:3] -a[2:12:3]", numpy.ones(20), np_sliced3=[numpy.array([float])])

    def test_sliced4(self):
        self.run_test("def np_sliced4(a): return a[1:11] -a[2:12]", numpy.ones(20), np_sliced4=[numpy.array([float])])

    def test_sliced5(self):
        self.run_test("def np_sliced5(a): return (-a[1:11]) + 3*a[2:12]", numpy.ones(20), np_sliced5=[numpy.array([float])])

    def test_sliced6(self):
        self.run_test("def np_sliced6(a): return a[3:4]", numpy.arange(12).reshape(6,2), np_sliced6=[numpy.array([[int]])])

    def test_sliced7(self):
        self.run_test("def np_sliced7(a): a[3:4] = 1 ; return a", numpy.arange(12).reshape(6,2), np_sliced7=[numpy.array([[int]])])

    def test_sliced8(self):
        self.run_test("def np_sliced8(a): a[1:2] = 1 ; return a", numpy.arange(12).reshape(3,2,2), np_sliced8=[numpy.array([[[int]]])])

    def test_sliced9(self):
        self.run_test("def np_sliced9(a): from numpy import arange ; a[1:2] = arange(4).reshape((1,2,2)) ; return a", numpy.arange(12).reshape(3,2,2), np_sliced9=[numpy.array([[[int]]])])

    def test_sliced10(self):
        self.run_test("def np_sliced10(a): from numpy import arange ; a[1:-1:2] = arange(4).reshape((1,2,2)) ; return a", numpy.arange(12).reshape(3,2,2), np_sliced10=[numpy.array([[[int]]])])

    def test_sliced11(self):
        self.run_test("def np_sliced11(a): return a[1::-2]", numpy.arange(12).reshape(3,2,2), np_sliced11=[numpy.array([[[int]]])])

    def test_sliced12(self):
        self.run_test("def np_sliced12(a): return a[1::-2]", numpy.arange(12), np_sliced12=[numpy.array([int])])

    def test_sliced13(self):
        self.run_test("def np_sliced13(a): return a[3::-3]", numpy.arange(11), np_sliced13=[numpy.array([int])])

    def test_newaxis0(self):
        self.run_test("def np_newaxis0(a): return a[None]",
                      numpy.ones(5), np_newaxis0=[numpy.array([float])])

    def test_newaxis1(self):
        self.run_test("def np_newaxis1(a): from numpy import newaxis; return a[newaxis]",
                      numpy.ones(5), np_newaxis1=[numpy.array([float])])

    def test_newaxis2(self):
        self.run_test("def np_newaxis2(a): from numpy import newaxis; return a[newaxis,:,newaxis]",
                      numpy.ones(5), np_newaxis2=[numpy.array([float])])

    def test_newaxis3(self):
        self.run_test("def np_newaxis3(a): from numpy import newaxis; return a[:,newaxis]",
                      numpy.ones(5), np_newaxis3=[numpy.array([float])])

    def test_newaxis4(self):
                      self.run_test("def np_newaxis4(a): from numpy import newaxis; return a[newaxis,:,:]",
                      numpy.ones((2,3)), np_newaxis4=[numpy.array([[float]])])

    def test_newaxis5(self):
        self.run_test("def np_newaxis5(a): from numpy import newaxis; return a[:,newaxis,:]",
                      numpy.ones((2,3)), np_newaxis5=[numpy.array([[float]])])

    def test_newaxis6(self):
        self.run_test("def np_newaxis6(a): from numpy import newaxis; return a[:,:,newaxis]",
                      numpy.ones((2,3)), np_newaxis6=[numpy.array([[float]])])

    def test_newaxis7(self):
        self.run_test("def np_newaxis7(a): from numpy import newaxis; return a[newaxis,1:,newaxis,:1,newaxis]",
                      numpy.ones((2,3)), np_newaxis7=[numpy.array([[float]])])

    def test_gexpr_composition0(self):
        self.run_test("def gexpr_composition0(a): return a[:,:,:][1]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition0=[numpy.array([[[[int]]]])])

    def test_gexpr_composition1(self):
        self.run_test("def gexpr_composition1(a): return a[:,:,:][1,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition1=[numpy.array([[[[int]]]])])

    def test_gexpr_composition2(self):
        self.run_test("def gexpr_composition2(a): return a[:,:,:][1,:,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition2=[numpy.array([[[[int]]]])])

    def test_gexpr_composition3(self):
        self.run_test("def gexpr_composition3(a): return a[:,1,:][:,:,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition3=[numpy.array([[[[int]]]])])

    def test_gexpr_composition4(self):
        self.run_test("def gexpr_composition4(a): return a[:,:,1][:,:,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition4=[numpy.array([[[[int]]]])])

    def test_gexpr_composition5(self):
        self.run_test("def gexpr_composition5(a): return a[:,1,:][:,1,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition5=[numpy.array([[[[int]]]])])

    def test_gexpr_composition6(self):
        self.run_test("def gexpr_composition6(a): return a[:,:,1][:,1,:]",
                      numpy.arange(16).reshape(2,2,2,2),
                      gexpr_composition6=[numpy.array([[[[int]]]])])

    def test_gexpr_composition7(self):
        self.run_test("def gexpr_composition7(a): return a[::2][::2]",
                      numpy.arange(16),
                      gexpr_composition7=[numpy.array([int])])

    def test_gexpr_composition8(self):
        self.run_test("def gexpr_composition8(a): return a[1::2][2::2]",
                      numpy.arange(16),
                      gexpr_composition8=[numpy.array([int])])

    def test_gexpr_composition9(self):
        self.run_test("def gexpr_composition9(a): return a[:1:2][:2:2]",
                      numpy.arange(16),
                      gexpr_composition9=[numpy.array([int])])

    @unittest.skip("Unknown slice combination")
    def test_gexpr_composition10(self):
        self.run_test("def gexpr_composition10(a): return a[:-1:2][:-2:2]",
                      numpy.arange(16),
                      gexpr_composition10=[numpy.array([int])])

    @unittest.skip("Unknown slice combination")
    def test_gexpr_composition11(self):
        self.run_test("def gexpr_composition11(a): return a[::2][::-2]",
                      numpy.arange(17),
                      gexpr_composition11=[numpy.array([int])])

    @unittest.skip("Unknown slice combination")
    def test_gexpr_composition12(self):
        self.run_test("def gexpr_composition12(a): return a[::-2][::-2]",
                      numpy.arange(13),
                      gexpr_composition12=[numpy.array([int])])

    def test_gexpr_composition13(self):
        self.run_test("def gexpr_composition13(a): return a[::-3][::2]",
                      numpy.arange(17),
                      gexpr_composition13=[numpy.array([int])])

    def test_gexpr_composition14(self):
        self.run_test("def gexpr_composition14(a): return a[:,::2][:,1,::-2]",
                      numpy.arange(16).reshape(1,4,4),
                      gexpr_composition14=[numpy.array([[[int]]])])

    def test_gexpr_composition15(self):
        self.run_test("def gexpr_composition15(a): return a[:,1,1:-1][:,:-1]",
                      numpy.arange(16).reshape(1,4,4),
                      gexpr_composition15=[numpy.array([[[int]]])])

    def test_gexpr_copy0(self):
        self.run_test("def gexpr_copy0(a,b): a[:,0] = b[:,0]; return a",
                      numpy.arange(16).reshape(8,2), numpy.arange(16).reshape(8,2),
                      gexpr_copy0=[numpy.array([[int]]), numpy.array([[int]])])

    def test_ndarray_iter0(self):
        self.run_test("def ndarray_iter0(a): return map(str, a)",
                      numpy.arange(16),
                      ndarray_iter0=[numpy.array([int])])

    def test_ndarray_iter1(self):
        self.run_test("""
                      def ndarray_iter1(a):
                        s = 0
                        for v in a:
                            s *= v
                        return s""",
                      numpy.arange(16),
                      ndarray_iter1=[numpy.array([int])])


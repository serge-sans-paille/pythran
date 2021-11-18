import numpy as np
import unittest
from pythran.typing import *

from pythran.tests import TestEnv

try:
    np.float128
    has_float128 = True
except AttributeError:
    has_float128 = False

class TestConversion(TestEnv):

    def test_list_of_uint16(self):
        self.run_test('def list_of_uint16(l): return l', [np.uint16(1),np.uint16(2)], list_of_uint16=[List[np.uint16]])

    def test_set_of_int32(self):
        self.run_test('def set_of_int32(l): return l', {np.int32(1),np.int32(-4)}, set_of_int32=[Set[np.int32]])

    def test_dict_of_int64_and_int8(self):
        self.run_test('def dict_of_int64_and_int8(l): return l',
                      {np.int64(1):np.int8(1),
                       np.int64(2):np.int8(3),
                       np.int64(3):np.int8(4),
                       np.int64(-4):np.int8(-5)},
                      dict_of_int64_and_int8=[Dict[np.int64,np.int8]])

    def test_tuple_of_uint8_and_int16(self):
        self.run_test('def tuple_of_uint8_and_int16(l): return l', (np.uint8(5), np.int16(-146)), tuple_of_uint8_and_int16=[Tuple[np.uint8, np.int16]])

    def test_array_of_uint32(self):
        self.run_test('def array_of_uint32(l): return l', np.ones(2,dtype=np.uint32), array_of_uint32=[NDArray[np.uint32, :]])

    def test_array_of_uint64_to_uint32(self):
        self.run_test('def array_of_uint64_to_uint32(l): import numpy ; return l, numpy.array(l, numpy.uint32)', np.ones(2,dtype=np.uint64), array_of_uint64_to_uint32=[NDArray[np.uint64, :]])

    def test_list_of_float64(self):
        self.run_test('def list_of_float64(l): return [2. * _ for _ in l]', [1.,2.], list_of_float64=[List[np.float64]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_list_of_float128(self):
        self.run_test('def list_of_float128(l): return [2. * _ for _ in l]', [np.float128(1.),np.float128(2.)], list_of_float128=[List[np.float128]])

    @unittest.skipIf(not has_float128, "not float128")
    def test_array_of_float128(self):
        self.run_test('def array_of_float128(l): return l + 1', np.array([1.,2.], dtype=np.float128), array_of_float128=[NDArray[np.float128, :]])

    def test_set_of_float32(self):
        """ Check np.float32 conversion. """
        code = """
def set_of_float32(l):
    return { _ / 2 for _ in l}"""
        self.run_test(code, {np.float32(1), np.float32(2)},
                      set_of_float32=[Set[np.float32]])

    def test_dict_of_complex64_and_complex_128(self):
        """ Check numpy complex type conversion. """
        code = """
def dict_of_complex64_and_complex_128(l):
    return list(l.keys()), list(l.values())"""
        interface = [Dict[np.complex64, np.complex128]]
        self.run_test(code, {np.complex64(3.1 + 1.1j): 4.5 + 5.5j},
                      dict_of_complex64_and_complex_128=interface)

    def test_ndarray_bad_dimension(self):
        code = 'def ndarray_bad_dimension(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.ones((10,10)),
                          ndarray_bad_dimension=[NDArray[float, :]])

    def test_ndarray_bad_dtype(self):
        code = 'def ndarray_bad_dtype(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.ones((10,10)),
                          ndarray_bad_dtype=[NDArray[np.uint8, :, :]])

    def test_ndarray_bad_stride_type(self):
        """ Check an error is raised when pythran input is strided. """
        code = 'def ndarray_bad_stride_type(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.ones((10, 10), dtype=np.uint8)[::2],
                          ndarray_bad_stride_type=[NDArray[np.uint8, :, :]])

    def test_ndarray_with_stride_type(self):
        code = 'def ndarray_with_stride_type(a): return a'
        self.run_test(code, np.arange((10), dtype=np.uint8)[::2],
                      ndarray_with_stride_type=[NDArray[np.uint8, ::-1]])

    def test_ndarray_with_stride_and_offset(self):
        code = 'def ndarray_with_stride_and_offset(a): return a'
        self.run_test(code, np.arange((10), dtype=np.uint8)[1::2],
                      ndarray_with_stride_and_offset=[NDArray[np.uint8, ::-1]])

    def test_ndarray_with_negative_stride(self):
        code = 'def ndarray_with_negative_stride(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.arange((10), dtype=np.uint8)[::-2],
                          ndarray_with_negative_stride=[NDArray[np.uint8, ::-1]])


    def iexpr_with_strides_and_offsets(self):
        code = 'def iexpr_with_strides_and_offsets(a): return a'
        self.run_test(code, np.array(np.arange((160), dtype=np.uint8).reshape((4, 5, 8)))[1][1::][:-1],
                      ndarray_with_strides_and_offsets=[NDArray[np.uint8, :, ::-1]])

    def test_ndarray_with_strides_and_offsets(self):
        code = 'def ndarray_with_strides_and_offsets(a): return a'
        self.run_test(code, np.array(np.arange((128), dtype=np.uint8).reshape((16,8)))[1::3,2::2],
                      ndarray_with_strides_and_offsets=[NDArray[np.uint8, :, ::-1]])


    def test_ndarray_with_stride_and_offset_and_end(self):
        code = 'def ndarray_with_stride_and_offset_and_end(a): return a'
        self.run_test(code, np.arange((10), dtype=np.uint16)[1:6:2],
                      ndarray_with_stride_and_offset_and_end=[NDArray[np.uint16, ::-1]])

    def test_ndarray_with_multi_strides(self):
        code = 'def ndarray_with_multi_strides(a): return a'
        self.run_test(code, np.array(np.arange((128), dtype=np.uint8).reshape((16,8)))[:,1::3],
                      ndarray_with_multi_strides=[NDArray[np.uint8, :, ::-1]])

    def test_ndarray_unsupported_reshaped_array_with_stride(self):
        code = 'def ndarray_unsupported_reshaped_array_with_stride(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.arange((128), dtype=np.uint8).reshape((16,8))[1::3,2::2],
                          ndarray_unsupported_reshaped_array_with_stride=[NDArray[np.uint8, :, ::-1]])

    def test_transposed_arg0(self):
        self.run_test("def np_transposed_arg0(a): return a", np.arange(9).reshape(3,3).T, np_transposed_arg0=[NDArray[int, -1::, :]])

    def test_transposed_arg1(self):
        self.run_test("def np_transposed_arg1(a): return a", np.arange(12).reshape(3,4).T, np_transposed_arg1=[NDArray[int, -1::, :]])

    def test_transposed_arg2(self):
        self.run_test("def np_transposed_arg2(a): return a", np.arange(12, dtype=complex).reshape(3,4).T, np_transposed_arg2=[NDArray[complex, -1::, :]])

    def test_transposed_targ0(self):
        self.run_test("def np_transposed_targ0(a): return a.T", np.arange(9).reshape(3,3).T, np_transposed_targ0=[NDArray[int, -1::, :]])

    def test_transposed_targ1(self):
        self.run_test("def np_transposed_targ1(a): return a.T", np.arange(12).reshape(3,4).T, np_transposed_targ1=[NDArray[int, -1::, :]])

    def test_transposed_targ2(self):
        self.run_test("def np_transposed_targ2(a): return a.T", np.arange(12, dtype=complex).reshape(3,4).T, np_transposed_targ2=[NDArray[complex, -1::, :]])

    def test_transposed_argt0(self):
        self.run_test("def np_transposed_argt0(a): return a.T", np.arange(9).reshape(3,3), np_transposed_argt0=[NDArray[int, :, :]])

    def test_transposed_argt1(self):
        self.run_test("def np_transposed_argt1(a): return a.T", np.arange(12).reshape(3,4), np_transposed_argt1=[NDArray[int, :, :]])

    def test_transposed_argt2(self):
        self.run_test("def np_transposed_argt2(a): return a.T", np.arange(12, dtype=complex).reshape(3,4), np_transposed_argt2=[NDArray[complex, :, :]])

    def test_transposed_expr0(self):
        self.run_test("def np_transposed_expr0(a): return (a + 1).T",
                      np.arange(12, dtype=complex).reshape(3,4),
                      np_transposed_expr0=[NDArray[complex, :, :]])

    def test_transposed_expr1(self):
        self.run_test("def np_transposed_expr1(a, b): return (a + b[0]).T",
                      np.arange(16, dtype=complex).reshape(4,4),
                      1j*np.arange(16, dtype=complex).reshape(4,4),
                      np_transposed_expr1=[NDArray[complex, :, :],
                                           NDArray[complex, :, :]])

    def test_transposed_expr2(self):
        self.run_test("def np_transposed_expr2(a, b): return (-(a + b[0])).T",
                      np.arange(16, dtype=complex).reshape(4,4),
                      1j*np.arange(16, dtype=complex).reshape(4,4),
                      np_transposed_expr2=[NDArray[complex, :, :],
                                           NDArray[complex, :, :]])

    def test_broadcasted_int8(self):
        self.run_test('def broadcasted_int8(l): return l + 4', np.ones(10,dtype=np.int8).reshape(5,2), broadcasted_int8=[NDArray[np.int8, :, :]])

    def test_broadcasted_uint8(self):
        self.run_test('def broadcasted_uint8(l): return l - 4', np.ones(10,dtype=np.uint8).reshape(5,2), broadcasted_uint8=[NDArray[np.uint8, :, :]])

    def test_broadcasted_int16(self):
        self.run_test('def broadcasted_int16(l): return l * 4', np.ones(10,dtype=np.int16).reshape(5,2), broadcasted_int16=[NDArray[np.int16, :, :]])

    def test_broadcasted_uint16(self):
        self.run_test('def broadcasted_uint16(l): return l / 4', np.ones(10,dtype=np.uint16).reshape(5,2), broadcasted_uint16=[NDArray[np.uint16, :, :]])

    @unittest.skip("no dynamic type promotion in pythran :-/")
    def test_broadcasted_large_int8(self):
        self.run_test('def broadcasted_large_int8(l): return l + 400', np.ones(10,dtype=np.int8).reshape(5,2), broadcasted_large_int8=[NDArray[np.int8, :, :]])

    def test_builtin_type0(self):
        self.run_test("def builtin_type0(x): return type(x)(x)", 1, builtin_type0=[int])

    def test_builtin_type1(self):
        self.run_test("def builtin_type1(x): return type(x)(x)", True, builtin_type1=[bool])

    def test_builtin_type2(self):
        self.run_test("def builtin_type2(x): return type(x)(x)", 1., builtin_type2=[float])

    def test_builtin_type3(self):
        self.run_test("def builtin_type3(x): return type(x)(x)", (1,), builtin_type3=[Tuple[int]])

    def test_builtin_type3b(self):
        self.run_test("def builtin_type3b(x): return type(x)(x)", (1,1.), builtin_type3b=[Tuple[int, float]])

    def test_builtin_type4(self):
        self.run_test("def builtin_type4(x): return type(x)(x)", [1], builtin_type4=[List[int]])

    def test_builtin_type5(self):
        self.run_test("def builtin_type5(x): return type(x)(x)", {1}, builtin_type5=[Set[int]])

    def test_builtin_type6(self):
        self.run_test("def builtin_type6(x): return type(x)(x)", {1:1}, builtin_type6=[Dict[int, int]])

    def test_builtin_type7(self):
        self.run_test("def builtin_type7(x): s = type(x)([1]); s[0] = 9; return s", np.array([2, 4, 8]), builtin_type7=[NDArray[int, :]])

    def test_builtin_type8(self):
        self.run_test("def builtin_type8(x): return type(x)(x)", "1", builtin_type8=[str])

    def test_builtin_type9(self):
        npt = ("numpy.int8",
               "numpy.uint8",
               "numpy.int16",
               "numpy.uint16",
               "numpy.int32",
               "numpy.uint32",
               "numpy.int64",
               "numpy.uint64",
               "numpy.intp",
               "numpy.uintp",)
        for i, t in enumerate(npt):
            kwargs = {"builtin_type9p{}".format(i): [int]}
            self.run_test("def builtin_type9p{}(x): import numpy; x = {}(x); return type(x)(x)".format(i, t),
                          1,
                          **kwargs)

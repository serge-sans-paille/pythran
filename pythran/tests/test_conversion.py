import numpy as np
import unittest

from test_env import TestEnv

class TestConversion(TestEnv):

    def test_list_of_uint16(self):
        self.run_test('def list_of_uint16(l): return l', [1,2,3,4], list_of_uint16=[[np.uint16]])

    def test_set_of_int32(self):
        self.run_test('def set_of_int32(l): return l', {1,2,3,-4}, set_of_int32=[{np.int32}])

    def test_dict_of_int64_and_int8(self):
        self.run_test('def dict_of_int64_and_int8(l): return l', {1:1,2:3,3:4,-4:-5}, dict_of_int64_and_int8=[{np.int64:np.int8}])

    def test_tuple_of_uint8_and_int16(self):
        self.run_test('def tuple_of_uint8_and_int16(l): return l', (5, -146), tuple_of_uint8_and_int16=[(np.uint8, np.int16)])

    def test_array_of_uint32(self):
        self.run_test('def array_of_uint32(l): return l', np.ones(2,dtype=np.uint32), array_of_uint32=[np.array([np.uint32])])

    def test_array_of_uint64_to_uint32(self):
        self.run_test('def array_of_uint64_to_uint32(l): import numpy ; return l, numpy.array(l, numpy.uint32)', np.ones(2,dtype=np.uint64), array_of_uint64_to_uint32=[np.array([np.uint64])])

    def test_list_of_float64(self):
        self.run_test('def list_of_float64(l): return [2 * _ for _ in l]', [1,2], list_of_float64=[[np.float64]])

    @unittest.skip("No np.float32 python_to_pythran converter exists.")
    def test_set_of_float32(self):
        """ Check np.float32 conversion. """
        code = """
def set_of_float32(l):
    return { _ / 2 for _ in l}"""
        self.run_test(code, {np.float32(1), np.float32(2)},
                      set_of_float32=[{np.float32}])

    @unittest.skip("No np.complex64 python_to_pythran converter exists.")
    def test_dict_of_complex64_and_complex_128(self):
        """ Check numpy complex type conversion. """
        code = """
def dict_of_complex64_and_complex_128(l):
    return l.keys(), l.values()"""
        interface = [{np.complex64: np.complex128}]
        self.run_test(code, {np.complex64(3.1 + 1.1j): 4.5 + 5.5j},
                      dict_of_complex64_and_complex_128=interface)

    def test_ndarray_bad_dimension(self):
        code = 'def ndarray_bad_dimension(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.ones((10,10)), ndarray_bad_dimension=[np.array([float])])

    def test_ndarray_bad_dtype(self):
        code = 'def ndarray_bad_dtype(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.ones((10,10)), ndarray_bad_dtype=[np.array([[np.uint8]])])

    def test_ndarray_bad_stride_type(self):
        """ Check an error is raised when pythran input is strided. """
        code = 'def ndarray_bad_stride_type(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.ones((10, 10), dtype=np.uint8)[::2],
                          ndarray_bad_stride_type=[np.array([[np.uint8]])])

    def test_ndarray_with_stride_type(self):
        code = 'def ndarray_with_stride_type(a): return a'
        self.run_test(code, np.arange((10), dtype=np.uint8)[::2],
                      ndarray_with_stride_type=[np.array([np.uint8])[::-1]])

    def test_ndarray_with_stride_and_offset(self):
        code = 'def ndarray_with_stride_and_offset(a): return a'
        self.run_test(code, np.arange((10), dtype=np.uint8)[1::2],
                      ndarray_with_stride_and_offset=[np.array([np.uint8])[::-1]])

    def test_ndarray_with_negative_stride(self):
        code = 'def ndarray_with_negative_stride(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.arange((10), dtype=np.uint8)[::-2],
                          ndarray_with_negative_stride=[np.array([np.uint8])[::-1]])


    def test_ndarray_with_strides_and_offsets(self):
        code = 'def ndarray_with_strides_and_offsets(a): return a'
        self.run_test(code, np.array(np.arange((128), dtype=np.uint8).reshape((16,8)))[1::3,2::2],
                      ndarray_with_strides_and_offsets=[np.array([[np.uint8]])[::-1]])


    def test_ndarray_with_stride_and_offset_and_end(self):
        code = 'def ndarray_with_stride_and_offset_and_end(a): return a'
        self.run_test(code, np.arange((10), dtype=np.uint8)[1:6:2],
                      ndarray_with_stride_and_offset_and_end=[np.array([np.uint8])[::-1]])

    def test_ndarray_with_multi_strides(self):
        code = 'def ndarray_with_multi_strides(a): return a'
        self.run_test(code, np.array(np.arange((128), dtype=np.uint8).reshape((16,8)))[:,1::3],
                      ndarray_with_multi_strides=[np.array([[np.uint8]])[::-1]])

    def test_ndarray_unsupported_reshaped_array_with_stride(self):
        code = 'def ndarray_unsupported_reshaped_array_with_stride(a): return a'
        with self.assertRaises(BaseException):
            self.run_test(code, np.arange((128), dtype=np.uint8).reshape((16,8))[1::3,2::2],
                          ndarray_unsupported_reshaped_array_with_stride=[np.array([[np.uint8]])[::-1]])

    def test_transposed_arg0(self):
        self.run_test("def np_transposed_arg0(a): return a", np.arange(9).reshape(3,3).T, np_transposed_arg0=[np.array([[int]]).T])

    def test_transposed_arg1(self):
        self.run_test("def np_transposed_arg1(a): return a", np.arange(12).reshape(3,4).T, np_transposed_arg1=[np.array([[int]]).T])

    def test_transposed_arg2(self):
        self.run_test("def np_transposed_arg2(a): return a", np.arange(12, dtype=complex).reshape(3,4).T, np_transposed_arg2=[np.array([[complex]]).T])

    def test_broadcasted_int8(self):
        self.run_test('def broadcasted_int8(l): return l + 4', np.ones(10,dtype=np.int8).reshape(5,2), broadcasted_int8=[np.array([[np.int8]])])

    def test_broadcasted_uint8(self):
        self.run_test('def broadcasted_uint8(l): return l - 4', np.ones(10,dtype=np.uint8).reshape(5,2), broadcasted_uint8=[np.array([[np.uint8]])])

    def test_broadcasted_int16(self):
        self.run_test('def broadcasted_int16(l): return l * 4', np.ones(10,dtype=np.int16).reshape(5,2), broadcasted_int16=[np.array([[np.int16]])])

    def test_broadcasted_uint16(self):
        self.run_test('def broadcasted_uint16(l): return l / 4', np.ones(10,dtype=np.uint16).reshape(5,2), broadcasted_uint16=[np.array([[np.uint16]])])

    @unittest.skip("no dynamic type promotion in pythran :-/")
    def test_broadcasted_large_int8(self):
        self.run_test('def broadcasted_large_int8(l): return l + 400', np.ones(10,dtype=np.int8).reshape(5,2), broadcasted_large_int8=[np.array([[np.int8]])])


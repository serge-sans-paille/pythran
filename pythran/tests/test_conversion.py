from test_env import TestEnv
from unittest import skip
import numpy as np

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

    def test_set_of_float32(self):
        self.run_test('def set_of_float32(l): return { _ / 2 for _ in l}', {np.float32(1),np.float32(2)}, set_of_float32=[{np.float32}])

    def test_dict_of_complex64_and_complex_128(self):
        self.run_test('def dict_of_complex64_and_complex_128(l): return l.keys(), l.values()', {np.complex64(3.1+1.1j):4.5+5.5j}, dict_of_complex64_and_complex_128=[{np.complex64:np.complex128}])


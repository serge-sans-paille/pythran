from pythran.tests import TestEnv

import unittest
from tempfile import mkstemp
import os
import sys

class TestArray(TestEnv):

    @unittest.skipIf(sys.implementation.name == 'pypy', "non supported upstream")
    def test_typecodes(self):
        self.run_test("def typecodes_(i): import array; return array.typecodes[i]",
                      2, typecodes_=[int])

    def test_array_empty(self):
        self.run_test("def array_empty_(): import array; return len(array.array('b'))",
                      array_empty_=[])

    def test_array_seq(self):
        self.run_test("def array_seq_(): import array; return len(array.array('h', [1, 2, 3]))",
                      array_seq_=[])

    def test_array_seq_tuple(self):
        self.run_test("def array_seq_tuple_(): import array; return len(array.array('h', (8, 9, 10)))",
                      array_seq_tuple_=[])

    def test_array_tolist(self):
        self.run_test("def array_tolist_(n): import array; return array.array('h', [n]).tolist()",
                      2, array_tolist_=[int])

    def test_array_append(self):
        self.run_test("def array_append_(n): import array; x = array.array('h', [n]); x.append(1); return x.tolist()",
                      2, array_append_=[int])

    def test_array_buffer_info(self):
        self.run_test("def array_buffer_info_(n): import array; x = array.array('h', [n]); return x.buffer_info()[1]",
                      2, array_buffer_info_=[int])

    def test_array_byteswap(self):
        self.run_test("def array_byteswap_(n): import array; x = array.array('H', [n]); x.byteswap(); return x.tolist()",
                      2, array_byteswap_=[int])

    def test_array_count(self):
        self.run_test("def array_count_(n): import array; x = array.array('H', [n, n]); return x.count(1), x.count(2)",
                      2, array_count_=[int])

    def test_array_extend(self):
        self.run_test("def array_extend_(n): import array; x = array.array('h', [n]); x.extend((1, 1)); return x.tolist()",
                      2, array_extend_=[int])

    def test_array_fromfile(self):
        filename = mkstemp()[1]
        with open(filename, "w") as fd:
            fd.write("12345678"*100)
        self.run_test("def array_fromfile_(s): import array; x = array.array('h'); x.fromfile(open(s, 'rb'), 8); return x.tolist()",
                      filename, array_fromfile_=[str])
        os.remove(filename)

    def test_array_fromlist(self):
        self.run_test("def array_fromlist_(f): import array; x = array.array('f'); x.fromlist([f]); return x.tolist()",
                      3., array_fromlist_=[float])

    def test_array_frombytes(self):
        filename = mkstemp()[1]
        with open(filename, "w") as fd:
            fd.write("12345678"*10)
        self.run_test("def array_frombytes_(s): import array; x = array.array('i'); x.frombytes(open(s, 'rb').read()); return x.tolist()",
                      filename, array_frombytes_=[str])
        os.remove(filename)

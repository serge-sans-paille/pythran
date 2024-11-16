import numpy
import pytest
import sys
import unittest

from pythran.tests import TestEnv
from pythran.typing import *

class TestBase(TestEnv):
    def test_simple_ann_stmt(self):
        self.run_test("def simple_ann_stmt(a):\n b: int = a; return b, b",
                      1,
                      simple_ann_stmt=[int])

    def test_dead_ann_stmt(self):
        self.run_test("def dead_ann_stmt(a): b: float = 2; return a",
                      1,
                      dead_ann_stmt=[int])

    def test_fwd_ann_stmt(self):
        self.run_test("def fwd_ann_stmt(a): b: float; b = 1.; return a + b",
                      1,
                      fwd_ann_stmt=[int])

class TestTypeAnnotation(TestEnv):

    def test_int_ann(self):
        self.run_test("def int_ann(a):\n b: int = 1; return a + b",
                      1,
                      int_ann=[int])

    def test_bool_ann(self):
        self.run_test("def bool_ann(a):\n b: bool = a; return b",
                      True,
                      bool_ann=[bool])

    def test_float_ann(self):
        self.run_test("def float_ann(a):\n b: float = 2.; return b * a",
                      1,
                      float_ann=[int])

    def test_complex_ann(self):
        self.run_test("def complex_ann(a):\n b: complex = 2.j; return b * a",
                      1,
                      complex_ann=[int])

    def test_tuple_ann(self):
        self.run_test("def tuple_ann(a):\n b: tuple[int, float] = (a, 1.); return b",
                      1,
                      tuple_ann=[int])

    def test_list_ann(self):
        self.run_test("def list_ann(a):\n b: list[int] = []; return b * a",
                      1,
                      list_ann=[int])

    def test_set_ann(self):
        self.run_test("def set_ann(a):\n b: set[int] = set(); return b",
                      1,
                      set_ann=[int])

    def test_dict_ann(self):
        self.run_test("def dict_ann(a):\n b: dict[int, str] = {}; return b",
                      1,
                      dict_ann=[int])

    def test_typeof_ann_arg(self):
        self.run_test("def typeof_ann_arg(a):\n b: dict[int, type(a)] = {}; return b",
                      1,
                      typeof_ann_arg=[int])

    def test_typeof_ann_local(self):
        self.run_test("def typeof_ann_local(a):\n c = a + 1\n b: list[type(c)] = []; return b * a, c",
                      1,
                      typeof_ann_local=[int])

    def test_ann_union(self):
        self.run_test("def typeof_ann_union(a):\n b: list[type(a) | float] = [1.]; b.append(a); return b",
                      1,
                      typeof_ann_union=[int])

    def test_ann_union_redundant(self):
        self.run_test("def typeof_ann_union_redundant(a):\n b: list[float | float] = [1.]; b.append(a); return b",
                      1,
                      typeof_ann_union_redundant=[int])

    def test_ann_union_none(self):
        self.run_test("def typeof_ann_union_none(a):\n b: list[None | int] = [a]; return b[0] is None",
                      1,
                      typeof_ann_union_none=[int])

    def test_ann_union_none_init(self):
        self.run_test("def typeof_ann_union_none_init(a):\n b: type(a) | None = None\n if a: b = a\n return b",
                      1,
                      typeof_ann_union_none_init=[int])

    def test_typeof_ann_expr(self):
        self.run_test("def typeof_ann_expr(a):\n b: list[type(a * 2)] = []; return b * a",
                      1,
                      typeof_ann_expr=[int])

    def test_typeof_ann_backward(self):
        self.run_test("""
import numpy as np
def poo(b, a):
    b.append(a)
    b.append(2)

def typeof_ann_backward(a):
    b = []
    c : type(b) = []
    poo(b, a)
    return b, c""",
                      1,
                      typeof_ann_backward=[int])

    def test_np_int_ann(self):
        self.run_test("import numpy as np\ndef npint_ann(a):\n b: np.int8 = 1; return a + b",
                      1,
                      npint_ann=[int])

    def test_np_ndarray_ann(self):
        self.run_test("import numpy as np\ndef npndarray_ann(a):\n b: np.ndarray[np.float32, 2] = np.ones((400,4), dtype=np.float32); return a + b",
                      1,
                      npndarray_ann=[int])


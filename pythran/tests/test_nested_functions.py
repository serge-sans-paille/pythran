#encoding: utf8
from pythran.tests import TestEnv

from unittest import skip, skipIf
import numpy

from pythran.typing import *
from packaging.version import Version

class TestNestedFunctions(TestEnv):

    def test_capture_argument(self):
        code = '''
def capture_argument(n):
    def foo(y):
        return n + y
    return foo(n)'''
        self.run_test(code, 42, capture_argument=[int])

    def test_capture_and_update_argument(self):
        code = '''
def capture_and_update_argument(n, i):
    def foo(y):
        n.append(y)
    foo(i)
    return n'''
        self.run_test(code, [3], 42, capture_and_update_argument=[List[int], int])

    def test_capture_argument_then_use(self):
        code = '''
def capture_argument_then_use(n):
    def foo(y):
        return n + y
    t = foo(n)
    return t, n'''
        self.run_test(code, 42, capture_argument_then_use=[int])

    def test_capture_argument_then_use_twice(self):
        code = '''
def capture_argument_then_use_twice(n):
    def foo(y):
        n.append(y)
    foo(len(n))
    foo(len(n))
    return n'''
        self.run_test(code, [42], capture_argument_then_use_twice=[List[int]])

    def test_capture_argument_then_update(self):
        code = '''
def capture_argument_then_update(n):
    def foo(y):
        return n + y
    t = foo(n)
    n += 1
    return t, n'''
        self.run_test(code, 42, capture_argument_then_update=[int])

    def test_capture_local(self):
        code = '''
def capture_local(y):
    n = y
    def foo(y):
        return n + y
    return foo(n)'''
        self.run_test(code, 42, capture_local=[int])

    def test_capture_and_update_local(self):
        code = '''
def capture_and_update_local(y, i):
    n = y
    def foo(y):
        n.append(y)
    foo(i)
    return n'''
        self.run_test(code, [3], 42, capture_and_update_local=[List[int], int])

    def test_capture_local_then_rebind(self):
        code = '''
def capture_local_then_rebind(n):
    m = []
    def foo(y):
        m.append(y)
    foo(len(m))
    p = list(m)
    m = []
    foo(len(m))
    return p, m'''
        self.run_test(code, 42, capture_local_then_rebind=[int])

    def test_redef_arg(self):
        code = '''
def redef_arg(x):
    z = 1
    def foo(x, y):
        def bar(x, y, z):
            return x, y, z
        return bar(x, y, z)
    return foo(x, "e")'''
        self.run_test(code, 42, redef_arg=[int])

    def test_ultra_nested_functions(self):
        code = '''
def ultra_nested_function(n):
    def foo(y):
        def bar(t): return t
        return bar(y)
    return foo(n)'''
        self.run_test(code, 42, ultra_nested_function=[int])

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

    def test_nested_with_conflicting_argument_names(self):
        code = '''
def nested_with_conflicting_argument_names(a1):
    def f2():
        r2 = a1
        def f3():
            r3 = a1
            return r3
        return r2 + f3()
    return f2()'''
        self.run_test(code, 5, nested_with_conflicting_argument_names=[int])

    def test_nonlocal_simple(self):
        code = '''
    def nonlocal_simple(x):
      def myfunc2():
        nonlocal x
        x = "hello"
      myfunc2()
      return x'''
        self.run_test(code, 'yo', nonlocal_simple=[str])

    def test_nonlocal_base(self):
        code = '''
def nonlocal_base(a):
    ret = 0
    def modify_ret (delta):
        nonlocal ret
        ret += delta
    for i in range(a):
        modify_ret (10)
    return ret'''
        self.run_test(code, 5, nonlocal_base=[int])

    def test_nonlocal_deep(self):
        code = '''
def nonlocal_deep(a):
    ret = 0
    def foo (delta):
        def bar(beta):
            nonlocal ret
            ret += delta + beta
        for i in range(a):
            bar (10)
    for i in range(a):
        foo (3)
    return ret'''
        self.run_test(code, 5, nonlocal_deep=[int])

    def test_nonlocal_shadow_global(self):
        code = '''
            x = 0
            def nonlocal_shadow_global(x):
                x = 1
                def inner():
                    nonlocal x
                    x = 2

                inner()'''
        self.run_test(code, 8, nonlocal_shadow_global=[int])

    def test_long_capture_list(self):
        code = '''
import numpy
def long_capture_list():
    arr = numpy.ones(shape = (3, 20))

    a1 = 1
    a2 = 2
    a3 = 3
    a4 = 4
    a5 = 5
    a6 = 6
    a7 = 7
    a8 = 8
    a9 = 9
    a10 = 10

    a11 = 11
    a12 = 12
    a13 = 13
    a14 = 14
    a15 = 15
    a16 = 16
    a17 = 17
    a18 = 18
    a19 = 19
    a20 = 20

    def save_step():
        arr[0][:] = [
            a1,
            a2,
            a3,
            a4,
            a5,
            a6,
            a7,
            a8,
            a9,
            a10,
            a11,
            a12,
            a13,
            a14,
            a15,
            a16,
            a17,
            a18,
            a19,
            a20,
        ]
    save_step()
    return arr'''
        self.run_test(code, long_capture_list=[])



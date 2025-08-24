from pythran.tests import TestEnv
from pythran.syntax import PythranSyntaxError

class TestNamedParameters(TestEnv):

    def test_call_with_named_argument(self):
        self.run_test("""
def foo(a):
    return a
def call_with_named_argument(n):
    return foo(a=n)""", 1, call_with_named_argument=[int])

    def test_call_with_named_arguments(self):
        self.run_test("""
def foo(a,b):
    return a / b
def call_with_named_arguments(n):
    return foo(b=n, a=2*n)""", 1, call_with_named_arguments=[int])

    def test_call_with_args_and_named_argument(self):
        self.run_test("""
def foo(a, b):
    return a - b
def call_with_args_and_named_argument(m,n):
    return foo(m, b=n)""", 1, 2, call_with_args_and_named_argument=[int, int])

    def test_call_with_args_and_named_arguments(self):
        self.run_test("""
def foo(a,b,c):
    return c + a / b
def call_with_args_and_named_arguments(n, m):
    return foo(m, c=2*n, b=n)""", 1, 2, call_with_args_and_named_arguments=[int, int])

    def test_call_with_default_and_named_argument(self):
        self.run_test("""
def foo(a, b=1):
    return a - b
def call_with_default_and_named_argument(m,n):
    return foo(a=m)""", 1, 2, call_with_default_and_named_argument=[int, int])

    def test_call_with_default_and_named_arguments(self):
        self.run_test("""
def foo(a,b,c=1):
    return c + a / b
def call_with_default_and_named_arguments(n, m):
    return foo(m, b=n)""", 1, 2, call_with_default_and_named_arguments=[int, int])

    def test_intrinsic_named_argument(self):
        """ Check named arguments with attributes as value. """
        self.run_test("""
            def intrinsic_named_argument(n):
                import numpy
                return numpy.ones(n, dtype=numpy.uint8).nbytes""",
                      4, intrinsic_named_argument=[int])

    def test_intrinsic_named_argument_without_default(self):
        self.run_test("""
            def intrinsic_named_argument_without_default(n):
                import numpy as np
                return np.expand_dims(np.ones(n), axis=0)""",
                      4, intrinsic_named_argument_without_default=[int])

    def test_nested_function_with_named_arguments(self):
        self.run_test('''
def nested_function_with_named_arguments(a):
    b = a * 2
    def foo(c):
        return b + c
    return foo(c=a)''',
        4, nested_function_with_named_arguments=[int])

    def test_nested_function_with_several_named_arguments(self):
        self.run_test('''
def nested_function_with_several_named_arguments(a):
    b = a * 2
    def foo(c, e):
        return b + c + e
    return foo(e = 4, c=a)''',
        4, nested_function_with_several_named_arguments=[int])

    def test_aliasing_functions_with_named_arguments(self):
        self.run_test('''
            def aliasing_functions_with_named_arguments(n):
                import numpy
                if n > 10:
                    my = numpy.ones
                else:
                    my = numpy.zeros
                return my(n, dtype=numpy.uint8).nbytes''',
                      4, aliasing_functions_with_named_arguments=[int])

    def test_aliasing_functions_with_different_structural_types(self):
        with self.assertRaises(PythranSyntaxError):
            self.run_test('''
def aliasing_functions_with_different_structural_types(n):
    import numpy
    if n > 10:
        my = sum
    else:
        my = numpy.zeros
    return my(n, dtype=numpy.uint8).nbytes''',
            4, aliasing_functions_with_different_structural_types=[int])

    def test_default_argument_all_filled(self):
        code = '''
            def default_argument_all_filled(x):
                return test2(x,2)

            def test2(a, b=3):
                return a, b'''
        self.run_test(code, 10, default_argument_all_filled=[int])

    def test_func_as_param0(self):
        code = '''
        def helper(c, i):
            if i:
                return c(i, j=1)
            else:
                return c(i, k=2)
        def func_as_param0(n):
            return helper((lambda i, j=0, k=0: (i, j, k)), n)'''
        self.run_test(code, 0, func_as_param0=[int])
        self.run_test(code, 1, func_as_param0=[int])

    def test_func_as_param1(self):
        code = '''
        def helper(c, i):
            if i:
                return c(i, x=1)
            else:
                return c(i)
        def foo0(i, x=1): return i, x
        def foo1(i, x=1): return i, x
        def func_as_param1(n):
            return helper(foo0, n), helper(foo1, 1)'''
        self.run_test(code, 0, func_as_param1=[int])
        self.run_test(code, 1, func_as_param1=[int])

    def test_func_as_param2(self):
        code = '''
        def helper(c, i):
            if i:
                return c(i, x=3)
            else:
                return c(i, y=1000)
        def foo0(i, x=1, y=2): return i, x
        def foo1(i, x=10, y=100): return i, x
        def func_as_param2(n):
            return helper(foo0, n), helper(foo1, 1)'''
        with self.assertRaises(PythranSyntaxError):
            self.run_test(code, 0, func_as_param2=[int])

    def test_func_as_param3(self):
        code = '''
        def helper(c, i):
            if i:
                return c(i, x=1)
            else:
                return c(i)
        def foo0(i, x=1): return i, x
        def foo1(i, x=10): return i, x
        def func_as_param3(n):
            return helper(foo0, n), helper(foo1, 1 - n)'''
        self.run_test(code, 0, func_as_param3=[int])
        self.run_test(code, 1, func_as_param3=[int])

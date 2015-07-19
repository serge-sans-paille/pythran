from test_env import TestEnv
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

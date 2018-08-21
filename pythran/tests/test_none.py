from test_env import TestEnv
from unittest import skip
from pythran.typing import List
import pythran

class TestNone(TestEnv):

    def test_returned_none(self):
        code = '''
def dummy(l):
    if l: return None
    else: return l
def returned_none(a):
    return dummy(a)'''
        self.run_test(code, [1, 2], returned_none=[List[int]])

    def test_returned_none_member(self):
        code = '''
def dummy(l):
    if not l: return None
    else: return l
def returned_none_member(a):
    t = dummy(a)
    if t is None:
        return None
    else:
        return t.count(1)'''
        self.run_test(code, [1, 2], returned_none_member=[List[int]])

    def test_use_none(self):
        code = """
            def none_input(a):
                l = list(range(10))
                if a is None:
                    return l[a:8]
                else:
                    return l[a:3]
            """
        self.run_test(code, None, none_input=[type(None)])

    def test_is_none_default(self):
        code = '''
        import numpy as np
        def is_none_default(sr,N):
            C = test2(sr, N)
            return C

        def test2(sr, N,fmax=None):
            if fmax is None:
                fmax = float(sr) / 2
            A = np.arange(1.+N/2)
            B = np.arange(1.+fmax/2)
            return A[0] - B[0]'''
        self.run_test(code, 1, 3, is_none_default=[int, int])

    def test_return_in_true(self):
        code = '''
        def return_in_true(x):
            return helper(x, x), helper(x, None)

        def helper(x, y):
            if y == None:
                return x
            return x + 1'''
        self.run_test(code, 1, return_in_true=[int])

    def test_return_in_false(self):
        code = '''
        def return_in_false(x):
            return helper(x, x), helper(x, None)

        def helper(x, y):
            if y != None:
                x += y
            else:
                return x
            return x + 1'''
        self.run_test(code, 1, return_in_false=[int])

    def test_potential_return_in_true(self):
        code = '''
        def potential_return_in_true(x):
            return helper(0, x), helper(x, None), helper(18, x)

        def helper(x, y):
            if None != y:
                if y > 1:
                    return 5
                else:
                    x += y
            else:
                return x
            return x + 1'''
        self.run_test(code, 1, potential_return_in_true=[int])

    def test_potential_return_in_false(self):
        code = '''
        def potential_return_in_false(x):
            return helper(0, x), helper(x, None), helper(18, x)

        def helper(x, y):
            if None is not y:
                x += y
            else:
                if x > 1:
                    return x
                else:
                    return 7
            return x + 1'''
        self.run_test(code, 1, potential_return_in_false=[int])

    def test_and_is_none(self):
        code = '''
        def and_is_none(x):
            return helper(0, x), helper(x, None), helper(18, x)

        def helper(x, y):
            if None is not y and x is not None:
                x += y
            else:
                return 7
            return x + 1'''
        self.run_test(code, 1, and_is_none=[int])

    def test_multiple_is_none(self):
        code = '''
        def multiple_is_none(x):
            return helper(0, x), helper(x, None), helper(18, x)

        def helper(x, y):
            if not (x is None is y):
                x += y
            else:
                return 7
            return x + 1'''
        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            self.run_test(code, 1, multiple_is_none=[int])

    def test_different_return(self):
        code = '''
        def different_return(x):
            return helper(0, x), helper(x, None), helper(18, x)

        def helper(x, y):
            if not (x is None is y):
                return "7"
            else:
                return 7
            return x + 1'''
        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            self.run_test(code, 1, different_return=[int])

    def test_is_none_in_expr(self):
        code = '''
        def is_none_in_expr(x):
            return (1 if None == x else 2), (x if None is x else 1), (1 if None != x else 2), (x if None is not x else 1)
        '''
        self.run_test(code, 1, is_none_in_expr=[int])

    def test_987(self):
        code = '''
        def test_987(x):
            a = None
            if x == 5:
                a = 3
            if a is not None:
                return 1
            return 0'''
        self.run_test(code, 1, test_987=[int])

    def test_987_0(self):
        code = '''
        def test_987_0(x):
            a = None
            if x == 5:
                a = 3
            if a is not None:
                return 1
            return 0'''
        self.run_test(code, 5, test_987_0=[int])

    def test_987_1(self):
        code = '''
        def test_987_1(x):
            a = None
            b = 0 
            if x != 12: 
                a = x 
            if a is not None and a < 5:
                b = 1 
            return (b, a)'''
        self.run_test(code, 12, test_987_1=[int])

    def test_987_2(self):
        code = '''
        def test_987_2(x):
            a = None
            b = 0 
            if x != 12: 
                a = x 
            if a is not None and a < 5:
                b = 1 
            return (b, a)'''
        self.run_test(code, 13, test_987_2=[int])

    def test_987_3(self):
        code = '''
        def test_987_3(x):
            a = None
            b = 0 
            if x != 12: 
                a = x 
            if a is not None and a < 5:
                b = 1 
            return (b, a)'''
        self.run_test(code, 3, test_987_3=[int])
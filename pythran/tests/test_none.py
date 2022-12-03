from pythran.tests import TestEnv
from unittest import skip
from pythran.typing import List, Dict, NDArray
import pythran
import numpy as np

class TestNone(TestEnv):

    def test_returned_none(self):
        code = '''
def dummy(l):
    if l: return None
    else: return l
def returned_none(a):
    return dummy(a)'''
        self.run_test(code, [1, 2], returned_none=[List[int]])

    def test_eq_neq_scalar(self):
        code = 'def eq_neq_scalar(x): return x == 1, x!= 1'
        self.run_test(code, 1, eq_neq_scalar=[int])

    def test_eq_neq_nonscalar(self):
        code = 'def eq_neq_nonscalar(x): return x == [1], x!= [1]'
        self.run_test(code, [1], eq_neq_nonscalar=[List[int]])

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

    def test_is_none_return_None(self):
        code = '''
import numpy as np
def is_none_return_None(signal=None):
    if signal is None:
        return
    signal[0,] += 1.2'''
        self.run_test(code, np.array([1.]), is_none_return_None=[NDArray[float, :]])

    def test_is_none_return_None_bis(self):
        code = '''
import numpy as np
def is_none_return_None_bis(signal=None):
    if signal is None:
        return
    signal[0,] += 1.2'''
        self.run_test(code, is_none_return_None_bis=[])

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

    def test_none_bool_tuple(self):
        code = '''
        def none_bool_tuple(x):
            if x > 2:
                y = (1, '2')
            else:
                y = None
            if x > 2:
                z = ()
            else:
                z = None
            return bool(y), bool(z)'''
        self.run_test(code, 1, none_bool_tuple=[int])

    def test_none_large_cond(self):
        code = '''
        def none_large_cond(x):
            return helper(x, None, None), helper(None, x, None), helper(None, None, x)

        def helper(x, y, z):
            if x is None or y is None and z is None:
                return 5
            else:
                return 6'''
        self.run_test(code, 1, none_large_cond=[int])

    def test_none_mixed_test0(self):
        code = '''
        def none_mixed_test0(x):
            return helper(x, 1), helper(x, 3)

        def helper(x, y):
            if x is None or x > 2:
                return 5
            if y > 0 or x is not None:
                return 6'''
        self.run_test(code, 1, none_mixed_test0=[int])

    def test_none_mixed_test1(self):
        code = '''
        def none_mixed_test1(x):
            return helper(x, 1), helper(x, 3)

        def helper(x, y):
            if x is not None and x > 2 and x < 8:
                return 5
            if y > 0 and x is not None:
                return 6'''
        self.run_test(code, 1, none_mixed_test1=[int])

    def test_none_mixed_test2(self):
        code = '''
        def none_mixed_test2(x):
            return helper(x, 1), helper(x, 3)

        def helper(x, y):
            if x is not None and x > 2 or x < 8:
                return 5
            if y > 0 or x is None:
                return 6'''
        self.run_test(code, 1, none_mixed_test2=[int])

    def test_none_mixed_test3(self):
        code = '''
        def none_mixed_test3(x):
            return helper(x, 1), helper(x, 3)

        def helper(x, y):
            return 5 if x is None or x > 2 or x < 8 else 6'''
        self.run_test(code, 1, none_mixed_test3=[int])

    def test_none_mixed_test4(self):
        code = '''
        def none_mixed_test4(x):
            return helper(x, 4), helper(x, 3)

        def helper(x, y):
            return 5 if x is not None and x > 2 and x < 8 else 6'''
        self.run_test(code, 4, none_mixed_test4=[int])

    def test_none_mixed_test5(self):
        code = '''
        def none_mixed_test5(x):
            return helper(x, 1), helper(x, 3)

        def helper(x, y):
            return 5 if x is not None and x > 5 or x < 8 else 6'''
        self.run_test(code, 1, none_mixed_test5=[int])

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

    def test_none_to_str(self):
        code = """
        def dump_as_str(x):
            y = x
            return str(y) + str(y) * 2
        def none_to_str(x):
            if x > 1:
                y = None
            else:
                y = 2
            return dump_as_str(None), dump_as_str(y)"""
        self.run_test(code, 0, none_to_str=[int])

    def test_is_none_attribute(self):
        code = '''
            def is_none_attribute(x):
                a = [x, x]
                if x is not None:
                    a.pop()
                return a'''
        self.run_test(code, 0, is_none_attribute=[int])

    def test_none_combine_tuple(self):
        code = '''
            def none_combine_tuple(n):
                def get_header(name):
                    if name:
                        return 1
                    else:
                        return None

                a = None

                lpix = get_header(n)

                # Don't work
                if lpix is None:
                    a = 3

                return a'''
        self.run_test(code, 'hello', none_combine_tuple=[str])

    def test_none_tuple(self):
        code = '''
            def test_none_tuple(i):
                a = 0
                b = 0
                c = 0
                h = None
                if i % 2 == 0:
                    h = (1, 2, 3)
                if h is not None:
                    a, b, c = h
                return a'''
        self.run_test(code, 10, test_none_tuple=[int])

    def test_none_loop_break(self):
        code = '''
            def none_loop_break(n):
                x = [None if i%2 else 1 for i in range(n)]
                s = 3
                for j in x:
                    if j is None:
                        break
                    s += 1
                return s'''
        self.run_test(code, 7, none_loop_break=[int])

    def test_none_loop_continue(self):
        code = '''
            def none_loop_continue(n):
                x = [None if i%2 else 1 for i in range(n)]
                s = 3
                for j in x:
                    if j is None:
                        continue
                    s += 1
                return s'''
        self.run_test(code, 7, none_loop_continue=[int])

    def test_none_loop_break_continue(self):
        code = '''
            def none_loop_break_continue(n):
                x = [None if i%2 else 1 for i in range(n)]
                s = 3
                for j in x:
                    if j is None:
                        s *= 9
                        continue
                    else:
                        s += 1
                        break
                return s'''
        self.run_test(code, 7, none_loop_break_continue=[int])

    def test_none_loop_break_or_ret(self):
        code = '''
            def none_loop_break_or_ret(n):
                x = [None if i%2 else 1 for i in range(n)]
                s = 3
                for j in x:
                    if j is None:
                        break
                    else:
                        return 3
                    s += 1
                return s'''
        self.run_test(code, 7, none_loop_break_or_ret=[int])

    def test_none_loop_continue_or_ret(self):
        code = '''
            def none_loop_continue_or_ret(n):
                x = [None if i%2 else 1 for i in range(n)]
                s = 3
                for j in x:
                    if j is None:
                        continue
                    else:
                        return 3
                    s += 1
                return s'''
        self.run_test(code, 7, none_loop_continue_or_ret=[int])

    def test_none_loop_break_continue_or_ret(self):
        code = '''
            def none_loop_break_continue_or_ret(n):
                x = [None if i%2 else 1 for i in range(n)]
                s = 3
                for j in x:
                    if j is None:
                        s *= 9
                        break
                    elif j < 5:
                        s += 1
                        continue
                    else:
                        return 8
                return s'''
        self.run_test(code, 7, none_loop_break_continue_or_ret=[int])

    def test_none_operators0(self):
        code = '''
            def helper(x):
                if x is not None:
                    x = 3.5
                x += 1
                x *= 5
                x -= 3
                x /= 2
                x //= 2
                return (x + 1,
                        x - 1,
                        x / 3,
                        x // 3,
                        x % 3,
                        x * 3,
                        x ** 3)
            def none_operators0(x):
                if x > 1:
                    y = None
                else:
                    y = 2
                return helper(x), helper(y)'''

        self.run_test(code, 0, none_operators0=[int])

    def test_none_diorcet0(self):
        code = '''
            def none_diorcet0(a):
                x = None if a < 0 else 1
                y = None if a % 2 else 2
                z = -1

                # Doesn't compile
                if x is not None and y is not None:  # Without test on other than none it doesn't work
                    z = 0

                # Doesn't compile
                if x is not None:
                    if y is not None:
                        return 0

                # Doesn't compile
                if x is not None:
                    if y is not None and a != -666:
                        z = 0

                # Compile but wrong results
                if x is not None:
                    if y is not None:
                        z = 0

                # Compile but wrong results (not the same that previous one)
                if x is not None and a != -666 and y is not None:
                    z = 0
                return z'''
        self.run_test(code, 3, none_diorcet0=[int])
        self.run_test(code, 2, none_diorcet0=[int])
        self.run_test(code, -2, none_diorcet0=[int])
        self.run_test(code, -3, none_diorcet0=[int])

    def test_none_diorcet1(self):
        code = '''
            def none_diorcet1(l):
                import numpy as np
                return tuple([None if np.isnan(a) else a for a in l])'''
        self.run_test(code, [3., float('nan')], none_diorcet1=[List[float]])

    def test_none_diorcet2(self):
        code = '''
            def none_diorcet2(headers):
                errors = []
                xxx = None

                def add_error(type, args):
                    errors.append((type, args))

                if "DUMMY_PYTHRAN" in headers:
                    xxx = True

                if xxx is not None:
                    add_error(1, ['AAAAA'])

                if xxx is not None and xxx: # Can't compile
                    add_error(1, ['AAAAA'])

                if "DUMMY_PYTHRAN" in headers: # Without that we have a missing symbol at runtime
                    add_error(2, ['DUMMY_PYTHRAN'])
                return errors'''
        self.run_test(code, {"DUMMY_PYTHRAN":"DUMMY_PYTHRAN"}, none_diorcet2=[Dict[str,str]])

    def test_none_escaping0(self):
        code = '''
            def none_escaping0(i):
                a = 0 
                c = None
                if i % 2 == 0:
                    c = 1
                if c is not None:
                    a = 2 
                    b = 3 
                    if i < 5:
                        print(b + i)
                return a'''
        self.run_test(code, 3, none_escaping0=[int])

    def test_none_escaping1(self):
        code = '''
            def none_escaping1(headers):
                def get_header():
                        return None

                lpix = float(headers.get('a'))

                diameter = None
                if lpix is not None and lpix > 0.0:
                    diameter = 20.0
                return diameter'''
        self.run_test(code, {'a': '10'}, none_escaping1=[Dict[str,str]])


class TestTypeIs(TestEnv):

    def test_typeis_0(self):
        self.run_test(
            'def typeis0(x): return x if type(x) is str else str(x)',
            1,
            typeis0=[int])

    def test_typeis_1(self):
        self.run_test(
            'def typeis1(x): return x if type(x) == str else str(x)',
            1,
            typeis1=[int])

    def test_typeis_2(self):
        self.run_test(
            'def typeis2(x): return x if str == type(x) else str(x)',
            1,
            typeis2=[int])

    def test_typeis_3(self):
        self.run_test(
            'def typeis3(x): return x if type(x) == str else str(x)',
            1,
            typeis3=[int])

    def test_typeis_4(self):
        self.run_test(
            'def typeis4(x): return x if type(x) == str == type(x) else str(x)',
            1,
            typeis4=[int])

    def test_typeis_5(self):
        self.run_test(
            'def typeis5(x): return x if str == type(x) is str else str(x)',
            1,
            typeis5=[int])


class TestIsInstance(TestEnv):

    def test_isinstance_int0(self):
        self.run_test(
            'def isinstance_int0(x, y): return isinstance(x, int), isinstance(y, int)',
            1, '1',
            isinstance_int0=[int, str])

    def test_isinstance_int1(self):
        code = 'def isinstance_int1a(x):\n if isinstance(x, int): return x  + 1\n else: return  x * 3'
        self.run_test(code, 1, isinstance_int1a=[int])
        code = 'def isinstance_int1b(x):\n if isinstance(x, int): return x  + 1\n else: return  x * 3'
        self.run_test(code, '1', isinstance_int1b=[str])

    def test_isinstance_int2(self):
        code = 'def isinstance_int2(x):\n if isinstance(x, int): return 1\n else: return  "3"'
        self.run_test(code, 1, isinstance_int2=[int])

    def test_isinstance_int3(self):
        code = 'def isinstance_int3(x):\n if isinstance(x, int) or x is None: return 1\n else: return  "3"'
        self.run_test(code, 1, isinstance_int3=[int])

    def test_isinstance_multi0(self):
        code = 'def isinstance_multi0(x):\n if isinstance(x, (int, float)): return 1\n else: return  "3"'
        self.run_test(code, 1, isinstance_multi0=[int])

    def test_isinstance_multi1(self):
        code = 'def isinstance_multi1(x):\n if isinstance(x, (int, float)): return 1\n else: return  "3"'
        self.run_test(code, 1., isinstance_multi1=[float])

    def test_isinstance_multi2(self):
        code = 'def isinstance_multi2(x):\n if isinstance(x, (int, float)): return 1\n else: return  "3"'
        self.run_test(code, "1", isinstance_multi2=[str])

    def test_isinstance_complex0(self):
        code = '''
            import numpy as np

            def conj (x):
                if isinstance(x.dtype, complex):
                    return x.real - 1j*x.imag
                else:
                    return x

            def isinstance_complex0(x):
                return x * conj(x)'''
        self.run_test(code, np.ones(5, dtype=int),
                      isinstance_complex0=[NDArray[int,:]])

    def test_isinstance_complex1(self):
        code = '''
            import numpy as np

            def conj (x):
                if isinstance(x.dtype, complex):
                    return x.real - 1j*x.imag
                else:
                    return x

            def isinstance_complex1(x):
                return x * conj(x)'''
        self.run_test(code, np.ones(5, dtype=complex) * 2j,
                      isinstance_complex1=[NDArray[complex,:]])

    def test_inner_loop_break(self):
        code = '''
import numpy as np
from math import sqrt

def hex_area (spot_radius):
    return sqrt(3)/2 * 3 * spot_radius**2

def inner_loop_break(center, pts, radius, spot_radius, target_area=None):
    spot_area = hex_area (spot_radius)
    pts_within_radius = pts[np.abs (pts - center) <= radius]
    if target_area is None:
        return pts_within_radius
    else:
        area = 0
        pts_list = []
        for pt in pts_within_radius:
            area += spot_area
            if area < target_area:
                pts_list.append (pt)
            else:
                break
        return pts_list
            '''
        self.run_test(code, 1j, np.array([1j]), 1., 1., 1., inner_loop_break=[complex, NDArray[complex, :], float, float, float])

    def test_escape_redef(self):
        code = '''
    def escape_redef(a=None):
        l = []
        if a is None:
            for ii in range(10):
                l.append(ii)
        else:
            a=a

        for ii in range(10):
            l.append(ii)
        return l'''
        self.run_test(code, escape_redef=[])

    def test_nested_static_if0(self):
        code = '''
def nested_static_if0 (
        free_age_vars,
        n_calls
):
    if n_calls is not None:
        n_calls[0] += 1

    cpp_free = free_age_vars[0] and free_age_vars[1]

    QQQQ = 1


    if QQQQ == 0:
        pass
    elif QQQQ == 1:
        if cpp_free:
            if n_calls is not None and n_calls[0] == 1:
                return 4.
        else:
            pass
    elif QQQQ == 2:
        pass

    return 123.'''
        self.run_test(code, [0,1], [0], nested_static_if0=[List[int], List[int]])

from test_env import TestEnv
import unittest
import numpy as np
import pythran
from textwrap import dedent

from pythran.typing import List, Dict, NDArray

class TestTyping(TestEnv):

    def test_index_dict_with_constant(self):
        code = 'def index_dict_with_constant(d): return d[0]'
        return self.run_test(code, {0:2}, index_dict_with_constant=[Dict[int,int]])

    def test_module_bad_attribute(self):
        code = 'def module_bad_attribute(): import random as m; return m.real'

        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            pythran.compile_pythrancode("dumbo", code)

    def test_list_of_set(self):
        code = '''
def list_of_set():
    l=[set()]
    l[0].add("12")
    return l'''
        self.run_test(code, list_of_set=[])

    def test_dict_of_set(self):
        code = '''
def dict_of_set():
    l={0:set()}
    l[0].add("12")
    return l'''
        self.run_test(code, dict_of_set=[])

    def test_typing_aliasing_and_indices(self):
        self.run_test('def typing_aliasing_and_indices(i): d={};e={}; f = e or d; f[1]=i; return d,e,f', 118, typing_aliasing_and_indices=[int])

    def test_typing_aliasing_and_combiner(self):
        self.run_test('def typing_aliasing_and_combiner(i): d=set();e=set(); f = e or d; f.add(i); return d,e,f', 117, typing_aliasing_and_combiner=[int])

    def test_typing_aliasing_and_combiner_back(self):
        self.run_test('def typing_aliasing_and_combiner_back(i): d=set();e=set(); f = e or d; e.add(i); return d,e,f', 116, typing_aliasing_and_combiner_back=[int])

    def test_typing_aliasing_and_fwd(self):
        self.run_test('def typing_aliasing_and_fwd(i): fwd = lambda x:x; l = []; fwd(l).append(i); return l', 115, typing_aliasing_and_fwd=[int])

    def test_typing_aliasing_and_constant_subscript(self):
        code = '''
        def typing_aliasing_and_constant_subscript(i):
            a=[]
            b=(a,)
            b[0].append(i)
            return a, b
        '''
        self.run_test(code, 118, typing_aliasing_and_constant_subscript=[int])

    def test_typing_aliasing_and_variable_subscript(self):
        code = '''
        def typing_aliasing_and_variable_subscript(i):
            a=[]
            b=[a]
            b[i].append(i)
            return a, b
        '''
        self.run_test(code, 0, typing_aliasing_and_variable_subscript=[int])

    def test_typing_aliasing_and_variable_subscript_combiner(self):
        code = '''
        def typing_aliasing_and_variable_subscript_combiner(i):
            a=[list.append, lambda x,y: x.extend([y])]
            b = []
            a[i](b, i)
            return b
        '''
        self.run_test(code, 1, typing_aliasing_and_variable_subscript_combiner=[int])

    def test_typing_and_function_dict(self):
        code = '''
            def typing_and_function_dict(a):
                funcs = {
                    'zero' : lambda x: x.add(0),
                    'one' : lambda x: x.add(1),
                }
                s = set()
                funcs[a](s)
                return s
        '''
        self.run_test(code, 'one', typing_and_function_dict=[str])

    def test_typing_and_iterate_over_function_list(self):
        code = '''
            def typing_and_iterate_over_function_list():
                funcs = [
                    lambda x: x.add(0),
                    lambda x: x.add(2),
                ]
                s = set()
                for f in funcs:
                    f(s)
                return s
        '''
        self.run_test(code, typing_and_iterate_over_function_list=[])


    def test_typing_aliasing_and_update(self):
        code = '''
def foo(d):
    f=d
    f+=[1]
def typing_aliasing_and_update():
    a= []
    foo(a)
    return a'''
        self.run_test(code, typing_aliasing_and_update=[])

    def test_typing_aliasing_and_update_and_globals(self):
        code = '''
def f(l): return len(l)
def g(l): l.append(1) ; return 0
foo=[f,g]
def typing_aliasing_and_update_and_globals(i):
    h = []
    return foo[i](h), h'''
        self.run_test(code, 1, typing_aliasing_and_update_and_globals=[int])

    def test_typing_aliasing_and_update_and_multiple_aliasing0(self):
        code = '''
def f(l): return len(l)
def g(l): l.append(1) ; return 0
def foo(i):
    if i < 1:
        return f
    else:
        return g
def typing_aliasing_and_update_and_multiple_aliasing0(i):
    h = []
    return foo(i)(h), h'''
        self.run_test(code, 1, typing_aliasing_and_update_and_multiple_aliasing0=[int])

    def test_typing_aliasing_and_update_and_multiple_aliasing1(self):
        code = '''
def foo(i):
    if i < 1:
        return list.remove
    else:
        return list.append
def typing_aliasing_and_update_and_multiple_aliasing1(i):
    h = []
    foo(i)(h, 1)
    return h'''
        self.run_test(code, 1, typing_aliasing_and_update_and_multiple_aliasing1=[int])


    def test_functional_variant_assign0(self):
        code='''
def functional_variant_assign0(n):
    if n > 3:
        x = "e" * n
        f = lambda y: x + y
    else:
        x = "g" * n
        f = lambda y: x + "er"
    return f("re")'''
        self.run_test(code, 12, functional_variant_assign0=[int])

    def test_functional_variant_assign1(self):
        code='''
def functional_variant_assign1(n):
    if n > 3:
        x = "e" * n
        f = lambda y: x + y
    else:
        x = "g" * n
        f = lambda y: x + "er"
    return f("re")'''
        self.run_test(code, 1, functional_variant_assign1=[int])

    def test_functional_variant_container0(self):
        code='''
import math
def functional_variant_container0(i):
    l=[]
    l.append(math.cos)
    l.append(math.sin)
    return l[i](12)'''
        self.run_test(code, 0, functional_variant_container0=[int])

    def test_functional_variant_container1(self):
        code='''
import math
def functional_variant_container1(i):
    l=[math.cos, math.sin]
    return l[i](12)'''
        self.run_test(code, 1, functional_variant_container1=[int])

    def test_functional_variant_container2(self):
        code='''
import math
l = [math.cos, math.sin, math.asin, math.acos, math.sqrt]
def functional_variant_container2(i):
    return l[i](1.)'''
        self.run_test(code, 4, functional_variant_container2=[int])

    @unittest.skip("bad typing: need backward propagation")
    def test_type_set_in_loop(self):
        code = '''
def type_set_in_loop():
    a = [[]]
    for i in range(2):
        b = []
        for j in a:
            b += [j] + [[1]]
        a = b
    return a,b'''
        self.run_test(code, type_set_in_loop=[])

    @unittest.skip("bad typing: need backward propagation")
    def test_type_set_in_while(self):
        code = '''
def type_set_in_while():
    a = [[]]
    n = 3
    while n:
        b = []
        for j in a:
            b += [j] + [[1]]
        a = b
        n -= 1
    return a,b'''
        self.run_test(code, type_set_in_while=[])

    @unittest.skip("issue #78")
    def test_recursive_interprocedural_typing0(self):
        code = '''
from cmath import exp, pi

def fft(x):
    N = len(x)
    if N <= 1: return x
    even = fft(x[0::2])
    odd =  fft(x[1::2])
    return [even[k] + exp(-2j*pi*k/N)*odd[k] for k in xrange(N/2)] + \
           [even[k] - exp(-2j*pi*k/N)*odd[k] for k in xrange(N/2)]

def recursive_interprocedural_typing0():
   l = [1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0]
   z = fft(l)
   return z'''
        self.run_test(code, recursive_interprocedural_typing0=[])

    @unittest.skip("issue #89")
    def test_recursive_interprocedural_typing1(self):
        code = '''
def s_perm(seq):
    if not seq:
        return [[]]
    else:
        new_items = []
        for item in s_perm(seq[:-1]):
            new_items += [item + seq for i in range(1)]
        return new_items
def recursive_interprocedural_typing1():
    l = [1,2,3]
    return s_perm(l)'''
        self.run_test(code, recursive_interprocedural_typing1=[])

    def test_print_numpy_types(self):
        self.run_test('''
            import numpy
            def print_type(t): print(t)
            def print_numpy_types(n):
                print_type(numpy.ones(n, dtype=bool).dtype)
                print_type(numpy.ones(n, dtype=int).dtype)
                print_type(numpy.ones(n, dtype=complex).dtype)
                print_type(numpy.ones(n, dtype=float).dtype)
                print_type(numpy.ones(n, dtype=numpy.uint8).dtype)
                print_type(numpy.ones(n, dtype=numpy.uint16).dtype)
                print_type(numpy.ones(n, dtype=numpy.uint64).dtype)
                print_type(numpy.ones(n, dtype=numpy.double).dtype)
                print_type(numpy.ones(n, dtype=numpy.complex).dtype)
            ''',
            3,
            print_numpy_types=[int])

    def test_constant_argument_variant_functor0(self):
        self.run_test('''
            def foo(x): x[0] = 0
            def bar(x): x[1] = 1
            l = [foo, bar]
            def constant_argument_variant_functor0(i):
                x = [-1, -1]
                l[i](x)
                return x''',
            0,
            constant_argument_variant_functor0=[int])

    def test_constant_argument_variant_functor1(self):
        self.run_test('''
            def foo(x): x[0] = 0
            def bar(x): x[1] = 1
            l = [foo, bar]
            def constant_argument_variant_functor1(i):
                x = [i, i]
                [f(x) for f in l]
                return x''',
            -1,
            constant_argument_variant_functor1=[int])

    def test_slice_assign(self):
        self.run_test('''
            import numpy as np
            def slice_assign (M):
                errs = np.zeros (M)
                errs[0] = 1
                errs[:] = 0
                return errs''',
            4,
            slice_assign=[int])

    def verify_type_error(self, code):
        with self.assertRaises(pythran.types.tog.PythranTypeError):
            _, eh = pythran.generate_cxx("dumbo", dedent(code))
            eh()

    def test_type_inference0(self):
        code = '''
        def wc(content):
            d = {}

            for word in content.split():
                d[word] = d.get(word, 0) + 1

            # Use list comprehension
            l = [(freq, word) for word, freq in d.items()]

            return sorted(l)
        '''
        self.run_test(code, "cha-la head cha-la", wc=[str])

        code_bis = code.replace("1", "'1'")
        self.verify_type_error(code_bis)

        code_ter = code.replace("0", "None")
        self.verify_type_error(code_ter)

    def test_type_inference1(self):
        code = '''
            def invalid_augassign(n):
                s = n + "1"
                s += 2
                return s'''
        self.verify_type_error(code)


    def test_type_inference2(self):
        code = '''
            def invalid_ifexp(n):
                return 1 if n else "1"'''
        self.verify_type_error(code)


    def test_type_inference3(self):
        code = '''
            def invalid_unary_op(n):
                return -(n + 'n')'''
        self.verify_type_error(code)


    def test_type_inference4(self):
        code = '''
            def invalid_list(n):
                return [n, len(n)]'''
        self.verify_type_error(code)


    def test_type_inference5(self):
        code = '''
            def invalid_set(n):
                return {n, len(n)}'''
        self.verify_type_error(code)

    def test_type_inference6(self):
        code = '''
            def invalid_dict_key(n):
                return {n:1, len(n):2}'''
        self.verify_type_error(code)


    def test_type_inference7(self):
        code = '''
            def invalid_dict_value(n):
                return {1:n, 2:len(n)}'''
        self.verify_type_error(code)

    def test_type_inference8(self):
        code = '''
            def invalid_multi_return(n):
                for i in n:
                    return [n]
                return {n}'''
        self.verify_type_error(code)

    def test_type_inference9(self):
        code = '''
            def invalid_multi_yield(n):
                for i in n:
                    yield [n]
                yield n'''
        self.verify_type_error(code)


    def test_type_inference10(self):
        code = '''
            def valid_augassign(l):
                l *= 0
                return l[1:2]'''
        return self.run_test(code, np.array([0,1,2,3,4]), valid_augassign=[NDArray[int, :]])

    def test_type_inference11(self):
        code = '''
            def valid_tuple_index(l):
                return (1, 2, 3, 4)[l]'''
        return self.run_test(code, 0, valid_tuple_index=[int])

    def test_exact_float_check(self):
        code = 'def exact_float_check(i): return i'
        return self.run_test(code, np.float64(1.1), exact_float_check=[float])

    def test_exact_complex_check(self):
        code = 'def exact_complex_check(i): return i'
        return self.run_test(code, np.complex128(2), exact_complex_check=[complex])

    def test_alias_update_in_loop_and_test(self):
        code = '''
            def alias_update_in_loop_and_test(X,f):
                for i in range(2):
                    if i==0: A = f*X[:,i]
                    else: A+=f*X[:,i]
                return A'''
        return self.run_test(code, np.arange(9).reshape(3,3), 3, alias_update_in_loop_and_test=[NDArray[int,:,:], int])

    def test_alias_update_in_multiple_opaque_tests(self):
        code = '''
            def alias_update_in_multiple_opaque_tests(X,f):
                if f > 3:
                    A = (f * X[:, 0])
                else:
                    A += (f * X[:, 0])
                pass
                if f <= 3:
                    A = (f * X[:, 1])
                else:
                    A += (f * X[:, 1])'''

        return self.run_test(code, np.arange(9).reshape(3,3), 9, alias_update_in_multiple_opaque_tests=[NDArray[int,:,:], int])

    def test_alias_update_in_multiple_different_opaque_tests(self):
        code = '''
            def alias_update_in_multiple_different_opaque_tests(f):
                if f > 3:
                    A = 1
                else:
                    A = 2

                if f <= 3:
                    A = "e" * A
                else:
                    A = "f" * A
                return A'''

        return self.run_test(code, 9, alias_update_in_multiple_different_opaque_tests=[int])

    def test_lambda_partial_merge(self):
        code = '''
            def lambda_partial_merge(a, c, s):
              if s == "a":
                x = lambda y:y 
              else:
                x = lambda y:y+c
              return x(a)'''
        return self.run_test(code, 1, 2, "A", lambda_partial_merge=[int, int, str])

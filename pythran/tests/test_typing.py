from test_env import TestEnv
import unittest
import numpy as np
import pythran

class TestTyping(TestEnv):

    def test_index_dict_with_constant(self):
        code = 'def index_dict_with_constant(d): return d[0]'
        return self.run_test(code, {0:2}, index_dict_with_constant=[{int:int}])

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
        self.run_test('def typing_aliasing_and_indices(): d={};e={}; f = e or d; f[1]="e"; return d,e,f', typing_aliasing_and_indices=[])

    def test_typing_aliasing_and_combiner(self):
        self.run_test('def typing_aliasing_and_combiner(): d=set();e=set(); f = e or d; f.add("e"); return d,e,f', typing_aliasing_and_combiner=[])

    def test_typing_aliasing_and_combiner_back(self):
        self.run_test('def typing_aliasing_and_combiner_back(): d=set();e=set(); f = e or d; e.add("e"); return d,e,f', typing_aliasing_and_combiner_back=[])

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

    def test_functional_variant_container0(self):
        code='''
import math
def functional_variant_container0():
    l=[]
    l.append(math.cos)
    l.append(math.sin)
    return l[0](12)'''
        self.run_test(code, functional_variant_container0=[])

    def test_functional_variant_container1(self):
        code='''
import math
def functional_variant_container1():
    l=[math.cos, math.sin]
    return l[0](12)'''
        self.run_test(code, functional_variant_container1=[])

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


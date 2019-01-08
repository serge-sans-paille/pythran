from test_env import TestEnv
from pythran.typing import List
import unittest


import pythran

import sys


class TestOptimization(TestEnv):

    def test_constant_fold_nan(self):
        code = "def constant_fold_nan(a): from numpy import nan; a[0] = nan; return a"
        self.run_test(code, [1., 2.], constant_fold_nan=[List[float]])

    def test_constant_fold_divide_by_zero(self):
        code = "def constant_fold_divide_by_zero(): return 1/0"
        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            self.check_ast(code, "syntax error anyway", ["pythran.optimizations.ConstantFolding"])

    def test_genexp(self):
        self.run_test("def test_genexp(n): return sum((x*x for x in range(n)))", 5, test_genexp=[int])

    def test_genexp_2d(self):
        self.run_test("def test_genexp_2d(n1, n2): return sum((x*y for x in range(n1) for y in range(n2)))", 2, 3, test_genexp_2d=[int, int])

    def test_genexp_if(self):
        self.run_test("def test_genexp_if(n): return sum((x*x for x in range(n) if x < 4))", 5, test_genexp_if=[int])

    def test_genexp_mixedif(self):
        self.run_test("def test_genexp_mixedif(m, n): return sum((x*y for x in range(m) for y in range(n) if x < 4))", 2, 3, test_genexp_mixedif=[int, int])

    def test_genexp_triangular(self):
        self.run_test("def test_genexp_triangular(n): return sum((x*y for x in range(n) for y in range(x)))", 2, test_genexp_triangular=[int])

    def test_aliased_readonce(self):
        self.run_test("""
def foo(f,l):
    return map(f,l[1:])
def alias_readonce(n):
    map = foo
    return map(lambda (x,y): x*y < 50, zip(range(n), range(n)))
""", 10, alias_readonce=[int])

    def test_replace_aliased_map(self):
        self.run_test("""
def alias_replaced(n):
    map = filter
    return list(map(lambda x : x < 5, range(n)))
""", 10, alias_replaced=[int])

    def test_listcomptomap_alias(self):
        self.run_test("""
def foo(f,l):
    return map(f,l[3:])
def listcomptomap_alias(n):
    map = foo
    return list([x for x in range(n)])
""", 10, listcomptomap_alias=[int])

    def test_readonce_return(self):
        self.run_test("""
def foo(l):
    return l
def readonce_return(n):
    l = foo(range(n))
    return l[:]
""", 5, readonce_return=[int])

    def test_readonce_assign(self):
        self.run_test("""
def foo(l):
    l[2] = 5
    return range(10)
def readonce_assign(n):
    return foo(range(n))
""", 5, readonce_assign=[int])

    def test_readonce_assignaug(self):
        self.run_test("""
def foo(l):
    l += [2,3]
    return range(10)
def readonce_assignaug(n):
    return foo(range(n))
""", 5, readonce_assignaug=[int])

    def test_readonce_for(self):
        self.run_test("""
def foo(l):
    s = []
    for x in range(10):
        s.extend(list(l))
    return s
def readonce_for(n):
    return foo(range(n))
""", 5, readonce_for=[int])

    def test_readonce_2for(self):
        self.run_test("""
def foo(l):
    s = 0
    for x in l:
        s += x
    for x in l:
        s += x
    return range(s)
def readonce_2for(n):
    return foo(range(n))
""", 5, readonce_2for=[int])

    def test_readonce_while(self):
        self.run_test("""
def foo(l):
    r = []
    while (len(r) < 50):
        r.extend(list(l))
    return r
def readonce_while(n):
    return foo(range(n))
""", 5, readonce_while=[int])

    def test_readonce_if(self):
        self.run_test("""
def h(l):
    return sum(l)
def g(l):
    return sum(l)
def foo(l):
    if True:
        return g(l)
    else:
        return h(l)
def readonce_if(n):
    return foo(range(n))
""", 5, readonce_if=[int])

    def test_readonce_if2(self):
        self.run_test("""
def h(l):
    return sum(l)
def g(l):
    return max(l[1:])
def foo(l):
    if True:
        return g(l)
    else:
        return h(l)
def readonce_if2(n):
    return foo(range(n))
""", 5, readonce_if2=[int])

    def test_readonce_slice(self):
        self.run_test("""
def foo(l):
    return list(l[:])
def readonce_slice(n):
    return foo(range(n))
""", 5, readonce_slice=[int])

    def test_readonce_listcomp(self):
        self.run_test("""
def foo(l):
    return [z for x in l for y in l for z in range(x+y)]
def readonce_listcomp(n):
    return foo(range(n))
""", 5, readonce_listcomp=[int])

    def test_readonce_genexp(self):
        self.run_test("""
def foo(l):
    return (z for x in l for y in l for z in range(x+y))
def readonce_genexp(n):
    return list(foo(range(n)))
""", 5, readonce_genexp=[int])

    def test_readonce_recursive(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return foo(l,n+1)
    else:
        return sum(l)
def readonce_recursive(n):
    return foo(range(n),0)
""", 5, readonce_recursive=[int])

    def test_readonce_recursive2(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return foo(l,n+1)
    else:
        return sum(l[1:])
def readonce_recursive2(n):
    return foo(range(n),0)
""", 5, readonce_recursive2=[int])

    def test_readonce_cycle(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return bar(l,n)
    else:
        return sum(l)
def bar(l,n):
    return foo(l, n+1)
def readonce_cycle(n):
    return foo(range(n),0)
""", 5, readonce_cycle=[int])

    def test_readonce_cycle2(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return bar(l,n)
    else:
        return sum(l)
def bar(l,n):
    return foo(l, n+1)
def readonce_cycle2(n):
    return foo(range(n),0)
""", 5, readonce_cycle2=[int])

    def test_omp_forwarding(self):
        init = """
from __future__ import print_function
def foo():
    a = 2
    #omp parallel
    if 1:
        __builtin__.print(a)
"""
        ref = """\
def foo():
    a = 2
    'omp parallel'
    if 1:
        __builtin__.print(a)
    return __builtin__.None"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_omp_forwarding2(self):
        init = """
from __future__ import print_function
def foo():
    #omp parallel
    if 1:
        a = 2
        __builtin__.print(a)
"""
        ref = """\
def foo():
    'omp parallel'
    if 1:
        pass
        __builtin__.print(2)
    return __builtin__.None"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_omp_forwarding3(self):
        init = """
from __future__ import print_function
def foo():
    #omp parallel
    if 1:
        a = 2
    __builtin__.print(a)
"""
        ref = """\
def foo():
    'omp parallel'
    if 1:
        a = 2
    __builtin__.print(a)
    return __builtin__.None"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_full_unroll0(self):
        init = """
def full_unroll0():
    k = []
    for i,j in zip([1,2,3],[4,5,6]): k.append((i,j))
    return k"""

        ref = '''def full_unroll0():
    k = []
    __tuple0 = (1, 4)
    j = __tuple0[1]
    i = __tuple0[0]
    __builtin__.list.append(k, (i, j))
    __tuple0 = (2, 5)
    j = __tuple0[1]
    i = __tuple0[0]
    __builtin__.list.append(k, (i, j))
    __tuple0 = (3, 6)
    j = __tuple0[1]
    i = __tuple0[0]
    __builtin__.list.append(k, (i, j))
    return k'''
        self.check_ast(init, ref, ["pythran.optimizations.ConstantFolding", "pythran.optimizations.LoopFullUnrolling"])


    def test_full_unroll1(self):
        self.run_test("""
def full_unroll1():
    c = 0
    for i in range(3):
        for j in range(3):
            for k in range(3):
                for l in range(3):
                    c += 1
    return c""", full_unroll1=[])

    def test_deadcodeelimination(self):
        init = """
from __future__ import print_function
def bar(a):
    __builtin__.print(a)
    return 10
def foo(a):
    if 1 < bar(a):
        b = 2
    return b"""
        ref = """\
def bar(a):
    __builtin__.print(a)
    return 10
def foo(a):
    (1 < bar(a))
    return 2"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution", "pythran.optimizations.DeadCodeElimination"])

    def test_deadcodeelimination2(self):
        init = """
def foo(a):
    if 1 < max(a, 2):
        b = 2
    return b"""
        ref = """def foo(a):
    pass
    return 2"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution", "pythran.optimizations.DeadCodeElimination"])

    def test_deadcodeelimination3(self):
        init = """
def bar(a):
    return a
def foo(a):
    "omp flush"
    bar(a)
    return 2"""
        ref = """def bar(a):
    return a
def foo(a):
    'omp flush'
    pass
    return 2"""
        self.check_ast(init, ref, ["pythran.optimizations.DeadCodeElimination"])

    def test_deadcodeelimination4(self):
        init = 'def noeffect(i): a=[];b=[a]; __builtin__.list.append(b[0],i); return None'
        ref = 'def noeffect(i):\n    pass\n    pass\n    pass\n    return __builtin__.None'
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution",
                                   "pythran.optimizations.ConstantFolding",
                                   "pythran.optimizations.DeadCodeElimination"])

    def test_patternmatching(self):
        init = """
def foo(a):
    return len(set(range(len(set(a)))))"""
        ref = """def foo(a):
    return __builtin__.pythran.len_set(__builtin__.range(__builtin__.pythran.len_set(a)))"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_patternmatching2(self):
        init = """
def foo(a):
    return reversed(range(len(set(a))))"""
        ref = """def foo(a):
    return __builtin__.range((__builtin__.pythran.len_set(a) - 1), (-1), (-1))"""
        if sys.version_info.major == 2:
            init = init.replace('range', 'xrange')
            ref = ref.replace('range', 'xrange')

        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_patternmatching3(self):
        init = """
def foo(a):
    return a * a"""
        ref = """def foo(a):
    return (a ** 2)"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])


class TestConstantUnfolding(TestEnv):

    def test_constant_folding_int_literals(self):
        self.run_test("def constant_folding_int_literals(): return 1+2*3.5", constant_folding_int_literals=[])

    def test_constant_folding_str_literals(self):
        self.run_test("def constant_folding_str_literals(): return \"1\"+'2'*3", constant_folding_str_literals=[])

    def test_constant_folding_list_literals(self):
        self.run_test("def constant_folding_list_literals(): return [1]+[2]*3", constant_folding_list_literals=[])

    def test_constant_folding_set_literals(self):
        self.run_test("def constant_folding_set_literals(): return {1,2,3,3}", constant_folding_set_literals=[])

    def test_constant_folding_builtins(self):
        self.run_test("def constant_folding_builtins(): return map(len,zip(range(2), range(2)))", constant_folding_builtins=[])

    def test_constant_folding_imported_functions(self):
        self.run_test("def constant_folding_imported_functions(): from math import cos ; return float(int(10*cos(1)))", constant_folding_imported_functions=[])

    def test_constant_folding_list_method_calls(self):
        self.run_test("def foo(n): l=[] ; l.append(n) ; return l\ndef constant_folding_list_method_calls(n): return foo(n)", 1, constant_folding_list_method_calls=[int])

    def test_constant_folding_complex_calls(self):
        self.run_test("def constant_folding_complex_calls(): return complex(1,1)", constant_folding_complex_calls=[])

    def test_constant_folding_expansive_calls(self):
        self.run_test("def constant_folding_expansive_calls(): return range(2**6)", constant_folding_expansive_calls=[])

    def test_constant_folding_too_expansive_calls(self):
        self.run_test("def constant_folding_too_expansive_calls(): return range(2**16)", constant_folding_too_expansive_calls=[])


class TestAnalyses(TestEnv):

    def test_imported_ids_shadow_intrinsic(self):
        self.run_test("def imported_ids_shadow_intrinsic(range): return [ i*range for i in [1,2,3] ]", 2, imported_ids_shadow_intrinsic=[int])

    def test_shadowed_variables(self):
        self.run_test("def shadowed_variables(a): b=1 ; b+=a ; a= 2 ; b+=a ; return a,b", 18, shadowed_variables=[int])

    def test_decl_shadow_intrinsic(self):
        self.run_test("def decl_shadow_intrinsic(l): len=lambda l:1 ; return len(l)", [1,2,3], decl_shadow_intrinsic=[List[int]])

    def test_used_def_chains(self):
        self.run_test("def use_def_chain(a):\n i=a\n for i in range(4):\n  print(i)\n  i=5.4\n  print(i)\n  break\n  i = 4\n return i", 3, use_def_chain=[int])

    def test_used_def_chains2(self):
        self.run_test("def use_def_chain2(a):\n i=a\n for i in range(4):\n  print(i)\n  i='lala'\n  print(i)\n  i = 4\n return i", 3, use_def_chain2=[int])

    @unittest.skip("Variable defined in a branch in loops are not accepted.")
    def test_importedids(self):
        self.run_test("def importedids(a):\n i=a\n for i in range(4):\n  if i==0:\n   b = []\n  else:\n   b.append(i)\n return b", 3, importedids=[int])

    def test_falsepoly(self):
        self.run_test("def falsepoly():\n i = 2\n if i:\n  i='ok'\n else:\n  i='lolo'\n return i", falsepoly=[])

    def test_global_effects_unknown(self):
        code = '''
            def bb(x):
                return x[0]()


            def ooo(a):
                def aa():
                    return a
                return aa,

            def global_effects_unknown(a):
                    return bb(ooo(a))'''
        self.run_test(code,
                      1,
                      global_effects_unknown=[int])

    def test_argument_effects_unknown(self):
        code = '''
            def int_datatype(n):
                return list, str, n

            def list_datatype(parent):
                def parser(value):
                    return parent[0](value)

                def formatter(value):
                    return parent[1](value)

                return parser, formatter


            def argument_effects_unknown(n):
                list_datatype(int_datatype(n))'''

        self.run_test(code,
                      1,
                      argument_effects_unknown=[int])


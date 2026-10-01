from pythran.tests import TestEnv
from pythran.typing import List, NDArray
from pythran.backend import Python
from pythran.optimizations import CommonSubexpressionElimination
from pythran.passmanager import PassManager
from pythran.middlend import refine
from pythran.analyses.repeated_expressions import (
    _children_with_conditionality)
from pythran import frontend
from textwrap import dedent
import builtins
import gast as ast
import unittest
import numpy

import pythran


class TestOptimization(TestEnv):

    def test_constant_fold_nan(self):
        code = "def constant_fold_nan(a): from numpy import nan; a[0] = nan; return a"
        self.run_test(code, [1., 2.], constant_fold_nan=[List[float]])

    def test_constant_fold_restrict_assign(self):
        code = """
import numpy as np
def make_signal():
    y = np.ones((44100,2))
    y[:, 1:] = 0. #<--- the issue.
    return y

def constant_fold_restrict_assign():
    x = make_signal()
    return x
    """
        self.run_test(code, constant_fold_restrict_assign=[])

    def test_constant_fold_subscript(self):
        code = '''
def aux(n):
    arr = [0] * n
    for i in range(10):
        arr[i] += 1
    return arr
def constant_fold_subscript(): return aux(10)
        '''
        self.run_test(code, constant_fold_subscript=[])

    def test_constant_fold_empty_array(self):
        code = "def constant_fold_empty_array(): from numpy import ones; return ones((0,0,0)).shape"
        self.run_test(code, constant_fold_empty_array=[])

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
    return list(map(lambda t: (t[0]*t[1] < 50), list(zip(range(n), range(n)))))
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

    def test_readonce_nested_calls(self):
        self.run_test("""
def readonce_nested_calls(Lq):
    import numpy as np
    return np.prod(np.sign(Lq))
""", [-5.], readonce_nested_calls=[List[float]])

    def test_readonce_return(self):
        self.run_test("""
def foo(l):
    return l
def readonce_return(n):
    l = list(foo(range(n)))
    return l[:]
""", 5, readonce_return=[int])

    def test_readonce_assign(self):
        self.run_test("""
def foo(l):
    l[2] = 5
    return list(range(10))
def readonce_assign(n):
    return foo(list(range(n)))
""", 5, readonce_assign=[int])

    def test_readonce_assignaug(self):
        self.run_test("""
def foo(l):
    l += [2,3]
    return range(10)
def readonce_assignaug(n):
    return list(foo(list(range(n))))
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
    return list(range(s))
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
    return foo(list(range(n)))
""", 5, readonce_if2=[int])

    def test_readonce_slice(self):
        self.run_test("""
def foo(l):
    return list(l[:])
def readonce_slice(n):
    return foo(list(range(n)))
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
    return foo(list(range(n)),0)
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

    def test_readonce_list(self):
        init = "def foo(l): return sum(list(l))"
        ref = """def foo(l):
    return builtins.sum(l)"""

        self.check_ast(init, ref, ["pythran.optimizations.IterTransformation"])

    def test_readonce_tuple(self):
        init = "def foo(l): return sum(tuple(l))"
        ref = """def foo(l):
    return builtins.sum(l)"""

        self.check_ast(init, ref, ["pythran.optimizations.IterTransformation"])

    def test_readonce_array(self):
        init = "def foo(l): import numpy as np; return sum(np.array(l))"
        ref = """import numpy as __pythran_import_numpy
def foo(l):
    return builtins.sum(l)"""

        self.check_ast(init, ref, ["pythran.optimizations.IterTransformation"])

    def test_readonce_np_sum_copy(self):
        init = "def foo(l): import numpy as np; return np.sum(np.copy(l))"
        ref = """import numpy as __pythran_import_numpy
def foo(l):
    return __pythran_import_numpy.sum(l)"""

        self.check_ast(init, ref, ["pythran.optimizations.IterTransformation"])


    def test_omp_forwarding(self):
        init = """
def foo():
    a = 2
    #omp parallel
    if 1:
        builtins.print(a)
"""
        ref = """\
def foo():
    a = 2
    'omp parallel'
    if 1:
        builtins.print(a)
    return None"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_omp_forwarding2(self):
        init = """
def foo():
    #omp parallel
    if 1:
        a = 2
        builtins.print(a)
"""
        ref = """\
def foo():
    'omp parallel'
    if 1:
        pass
        builtins.print(2)
    return None"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_omp_forwarding3(self):
        init = """
def foo():
    #omp parallel
    if 1:
        a = 2
    builtins.print(a)
"""
        ref = """\
def foo():
    'omp parallel'
    if 1:
        a = 2
    builtins.print(a)
    return None"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_forwarding0(self):
        init = '''
            def foo(x):
                for i in x:
                    if i:
                        j = i
                return j'''
        ref = init
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_forwarding1(self):
        init = 'def f(i):\n while i:\n  if i > 3: x=1; continue\n  x=2\n return x'
        ref = 'def f(i):\n    while i:\n        if (i > 3):\n            x = 1\n            continue\n        x = 2\n    return x'
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_forwarding2(self):
        init = '''
        def foo(a):
            l = [0]
            if a:
                builtins.list.append(l, 1)
            ret = 0
            for i in l:
                ret += i
            return ret'''
        ref = init
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_full_unroll0(self):
        init = """
def full_unroll0():
    k = []
    for i,j in zip([1,2,3],[4,5,6]): k.append((i,j))
    return k"""

        ref = '''
        import __dispatch__ as __pythran_import___dispatch__
        def full_unroll0():
            k = []
            __tuple0 = (1, 4)
            j = __tuple0[1]
            i = __tuple0[0]
            __pythran_import___dispatch__.append(k, (i, j))
            __tuple0 = (2, 5)
            j = __tuple0[1]
            i = __tuple0[0]
            __pythran_import___dispatch__.append(k, (i, j))
            __tuple0 = (3, 6)
            j = __tuple0[1]
            i = __tuple0[0]
            __pythran_import___dispatch__.append(k, (i, j))
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
def bar(a):
    builtins.print(a)
    return 10
def foo(a):
    if 1 < bar(a):
        b = 2
    return b"""
        ref = """\
def bar(a):
    builtins.print(a)
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
        init = 'def noeffect(i): a=[];b=[a]; builtins.list.append(b[0],i); return 1'
        ref = 'def noeffect(i):\n    return 1'
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution",
                                   "pythran.optimizations.ConstantFolding",
                                   "pythran.optimizations.DeadCodeElimination"])

    def test_deadcodeelimination5(self):
        init = 'def noeffect(l):\n for i in l:\n  a = 1\n  b = 2'
        ref = 'def noeffect(l):\n    for i in l:\n        pass\n    return None'
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution",
                                   "pythran.optimizations.ConstantFolding",
                                   "pythran.optimizations.DeadCodeElimination"])


    def test_patternmatching(self):
        init = """
def foo(a):
    return len(set(range(len(set(a)))))"""
        ref = """def foo(a):
    return builtins.pythran.len_set(builtins.range(builtins.pythran.len_set(a)))"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_patternmatching2(self):
        init = """
def foo(a):
    return reversed(range(len(set(a))))"""
        ref = """def foo(a):
    return builtins.range((builtins.pythran.len_set(a) - 1), (-1), (-1))"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_patternmatching3(self):
        init = """
def foo(a):
    return a * a"""
        ref = """def foo(a):
    return (a ** 2)"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_patternmatching4(self):
        init = """
def foo(a):
    return a ** .5"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.sqrt(a)"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_patternmatching5(self):
        init = """
def foo(a):
    return a ** (1./3.)"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.cbrt(a)"""
        self.check_ast(init, ref, ["pythran.optimizations.ConstantFolding",
                                   "pythran.optimizations.PatternTransform"])

    def test_patternmatching6(self):
        init = """
import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.argmax(a * 3.)"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.argmax(a)"""
        self.check_ast(init, ref, ["pythran.optimizations.PatternTransform"])

    def test_lambda_patterns0(self):
        init = """
def foo(a):
    return lambda x, y: x + y"""
        ref = """import operator as __pythran_import_operator
def foo(a):
    return __pythran_import_operator.add"""
        self.check_ast(init, ref, ["pythran.transformations.RemoveLambdas"])

    def test_lambda_patterns1(self):
        init = """
def foo(a):
    return (lambda x, y: x + 1), (lambda z, w: z + 1)"""
        ref = """def foo(a):
    return (foo_lambda0, foo_lambda0)
def foo_lambda0(x, y):
    return (x + 1)"""
        self.check_ast(init, ref, ["pythran.transformations.RemoveLambdas"])


    def test_inline_builtins_broadcasting0(self):
        init = """
import numpy as np
def foo(a):
    return np.array([a, 1]) == 1"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.array(((a == 1), (1 == 1)))"""
        self.check_ast(init, ref, ["pythran.optimizations.InlineBuiltins"])

    def test_inline_builtins_broadcasting1(self):
        init = """
import numpy as np
def foo(a):
    return np.asarray([a, 1]) + 1"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.array(((a + 1), (1 + 1)))"""
        self.check_ast(init, ref, ["pythran.optimizations.InlineBuiltins"])

    def test_inline_builtins_broadcasting2(self):
        init = """
import numpy as np
def foo(a):
    return - np.asarray([a, 1])"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.array(((- a), (- (1))))"""
        self.check_ast(init, ref, ["pythran.optimizations.InlineBuiltins"])

    def test_inline_builtins_broadcasting3(self):
        init = """
import numpy as np
def foo(a):
    return np.asarray([a, 1]) + (3, 3)"""
        ref = """import numpy as __pythran_import_numpy
def foo(a):
    return __pythran_import_numpy.array(((a + 3), (1 + 3)))"""
        self.check_ast(init, ref, ["pythran.optimizations.InlineBuiltins"])

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

    def test_constant_folding_comparators(self):
        self.run_test("def constant_folding_comparators(): return 1 > 1, 1>=1, 1 < 1, 1 <= 1, 1 == 1, 1 != 1, 1 is 2, (1 < 2 < 3), 1 in [1, 2] in [(1,2)], 1 not in [1, 2]",
                      constant_folding_comparators=[])

    def test_constant_folding_builtins(self):
        self.run_test("def constant_folding_builtins(): return list(map(len,zip(range(2), range(2))))", constant_folding_builtins=[])

    def test_constant_folding_imported_functions(self):
        self.run_test("def constant_folding_imported_functions(): from math import cos ; return float(int(10*cos(1)))", constant_folding_imported_functions=[])

    def test_constant_folding_list_method_calls(self):
        self.run_test("def foo(n): l=[] ; l.append(n) ; return l\ndef constant_folding_list_method_calls(n): return foo(n)", 1, constant_folding_list_method_calls=[int])

    def test_constant_folding_complex_calls(self):
        self.run_test("def constant_folding_complex_calls(): return complex(1,1)", constant_folding_complex_calls=[])

    def test_constant_folding_expansive_calls(self):
        self.run_test("def constant_folding_expansive_calls(): return list(range(2**6))", constant_folding_expansive_calls=[])

    def test_constant_folding_too_expansive_calls(self):
        self.run_test("def constant_folding_too_expansive_calls(): return list(range(2**16))", constant_folding_too_expansive_calls=[])

    def test_constant_folding_bool_array(self):
        self.run_test("def constant_folding_bool_array(): import numpy as np; return np.concatenate([np.array([True]),np.array([True])])", constant_folding_bool_array=[])


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

    def test_inlining_globals_side_effect(self):
        code = '''
            import random
            r = random.random()
            def inlining_globals_side_effect():
                return r == r == r
            '''

        self.run_test(code,
                      inlining_globals_side_effect=[])

    def test_subscript_function_aliasing(self):
        code = '''
            SP = 0x20
            STX = 0x02
            ETX = 0x03


            def _div_tuple(base, div):
                a = base // div
                b = base % div
                return a, b


            def number_datatype(base, dc, fs=6):
                def parser(value):
                    if not value.isdigit():
                        raise ValueError("Invalid number")
                    value = int(value)
                    ret = []
                    while value > 0:
                        a, b = _div_tuple(value, len(base))
                        ret.insert(0, ord(base[b]))
                        value = a
                    ret = [ord('0')] * (dc - len(ret)) + ret
                    ret = [SP] * (fs - len(ret)) + ret
                    return ret

                def formatter(v):
                    ret = 0
                    for a in [chr(c) for c in v][-dc:]:
                        ret = ret * len(base) + base.index(a)
                    return str(int(ret))

                return parser, formatter


            def int_datatype(dc, fs=6):
                return number_datatype(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], dc, fs)


            def hex_datatype(dc, fs=6):
                return number_datatype(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'], dc, fs)

            simple_commands = [('aa', 107, int_datatype(4)),
                               ('bb', 112, int_datatype(1)),
                               ]

            str_commands = {c: (c, v, f) for c, v, f in simple_commands}


            def subscript_function_aliasing(id, ai, pfc, value):
                data = [0x0] * 16
                _, pfc, fcts = str_commands[pfc]
                data[5:9] = int_datatype(4, 4)[0](str(pfc))
                data[9:15] = fcts[0](value)
                return data'''
        self.run_test(code, 'aa', 2, 'bb', '3', subscript_function_aliasing=[str, int, str, str])

    def test_range_simplify_jl(self):
        code = '''
import numpy as np
silent = 0

def B(n):
    TS = 10
    outSig = []
    while n:
        outSamps = np.zeros((10, 2))
        outSig.append(outSamps.copy())
    outSamps = np.zeros((10, 2))
    outSig.append(outSamps.copy())
    return outSig, TS

def range_simplify_jl(n):
    outSignal, TS = B(n)
    return (outSignal)'''
        self.run_test(code, 0, range_simplify_jl=[int])

    def test_range_simplify_subscript(self):
        code = '''
def LooperMaster___init__():
    self_userUseTempo = 1
    self = [self_userUseTempo]
    return self

def range_simplify_subscript(n):
    ML = LooperMaster___init__()
    ML[0] = n
    return ML'''
        self.run_test(code, 1, range_simplify_subscript=[int])

    def test_range_simplify_call_same_identifiers(self):
        code = '''
import math
import numpy
def test_range_simplify_call_same_identifiers(b, c, y, t, m):
    ta = ftc (b, c, y, t, m)
    gis = 0.
    tno = numpy.empty(shape = (2))
    for cnum in ([0,1] if m else [0]):
        tno[cnum] = 123.
    for cnum in ([0,1] if m else [0]):
        gis += cnum
    ret = gis - ta
    return ret

def ftc (b, c, y, t, m):
    cin = [7,8]
    ed = []
    for cnum in [0,1]:
        if b < 5:
            ed.append (456.)
        else:
            ed.append (0.)
    ret = 0.
    if (c + y) < 65 and t[y] and m and cin[1] is not None:
        ret += 543.21
    return ret
'''
        self.run_test(code,
                      True, 60, 60, numpy.asarray([False] * 80), True,
                      test_range_simplify_call_same_identifiers=[bool, int, int,
                                                                 NDArray[bool,:],
                                                                 bool])

    def test_insert_none0(self):
        code = '''
            def insert_none0(x):
                for ii in range(len(x)):
                    if x[ii]: return x[ii]
                else:
                    return 0'''
        self.run_test(code, [], insert_none0=[List[int]])

    def test_inline_in_while_test(self):
        code = '''
def is_even(n: int) -> int:
    return (n & 1) == 0

def inline_in_while_test(n: int) -> int:
    result = 0
    while is_even(n):
        n >>= 1
        result += 1
    return result
        '''
        self.run_test(code, 7, inline_in_while_test=[int])


class TestCommonSubexpressionElimination(TestEnv):

    CSE = ["pythran.optimizations.CommonSubexpressionElimination"]

    @staticmethod
    def apply_cse(code):
        pm = PassManager("testing")
        node = ast.parse(dedent(code))
        updated, node = pm.apply(CommonSubexpressionElimination, node)
        return updated, pm.dump(Python, node)

    @staticmethod
    def optimize(code):
        pm = PassManager("testing")
        ir, _ = frontend.parse(pm, dedent(code))
        refine(pm, ir, [CommonSubexpressionElimination])
        return pm.dump(Python, ir)

    def assert_same_behavior(self, code, name, arguments):
        code = dedent(code)
        optimized = self.optimize(code)
        before, after = {}, {"builtins": builtins}
        exec(code, before)
        exec(optimized, after)
        for args in arguments:
            try:
                expected = before[name](*args)
            except Exception as e:
                with self.assertRaises(type(e)):
                    after[name](*args)
            else:
                self.assertEqual(expected, after[name](*args))
        return optimized

    def assert_hoisted(self, code, assignment, remaining):
        updated, content = self.apply_cse(code)
        self.assertTrue(updated)
        self.assertIn(assignment, content)
        self.assertEqual(content.count(remaining), 1)
        return content

    def assert_untouched(self, code):
        updated, content = self.apply_cse(code)
        self.assertFalse(updated)
        self.assertNotIn("__cse", content)

    def test_cse_binop(self):
        init = """
            def foo(a, b, c, d):
                return (a + b) * c + (a + b) * d"""
        ref = """
            def foo(a, b, c, d):
                __cse0 = (a + b)
                return ((__cse0 * c) + (__cse0 * d))"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_three_occurrences(self):
        init = """
            def foo(a, b, c, d, e):
                return (a + b) * c + (a + b) * d + (a + b) * e"""
        ref = """
            def foo(a, b, c, d, e):
                __cse0 = (a + b)
                return (((__cse0 * c) + (__cse0 * d)) + (__cse0 * e))"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_inserted_before_first_use(self):
        init = """
            def foo(a, b):
                x = (a + b) * 2
                y = (a + b) * 3
                return x + y"""
        ref = """
            def foo(a, b):
                __cse0 = (a + b)
                x = (__cse0 * 2)
                y = (__cse0 * 3)
                return (x + y)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_unaryop(self):
        init = """
            def foo(a, b):
                return (- (a * b)) + (- (a * b)) * 2"""
        ref = """
            def foo(a, b):
                __cse0 = (- (a * b))
                return (__cse0 + (__cse0 * 2))"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_compare(self):
        self.assert_hoisted("""
            def foo(a, b, c):
                if a < b * c:
                    return a
                if a < b * c:
                    return b
                return c""", "__cse0 = (a < (b * c))", "(a < (b * c))")

    def test_cse_call(self):
        init = """
            import math
            def foo(a, b):
                return math.sqrt(a * b) + math.sqrt(a * b)"""
        ref = """
            import math as __pythran_import_math
            def foo(a, b):
                __cse0 = __pythran_import_math.sqrt((a * b))
                return (__cse0 + __cse0)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_attribute_operand(self):
        init = """
            import math
            def foo(a, b):
                return math.pi * (a + b) + math.pi * (a + b)"""
        ref = """
            import math as __pythran_import_math
            def foo(a, b):
                __cse0 = (__pythran_import_math.pi * (a + b))
                return (__cse0 + __cse0)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_boolop(self):
        init = """
            def foo(a, b, c):
                x = (a > 0) and (b > 0)
                y = (a > 0) and (b > 0)
                return x or y or c"""
        ref = """
            def foo(a, b, c):
                __cse0 = ((a > 0) and (b > 0))
                x = __cse0
                y = __cse0
                return (x or y or c)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_ifexp(self):
        init = """
            def foo(a, b, c):
                x = (a if c > 0 else b) + 1
                y = (a if c > 0 else b) + 2
                return x + y"""
        ref = """
            def foo(a, b, c):
                __cse0 = (a if (c > 0) else b)
                x = (__cse0 + 1)
                y = (__cse0 + 2)
                return (x + y)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_single_occurrence(self):
        self.assert_untouched("""
            def foo(a, b):
                return a + b""")

    def test_cse_cheap_forms_untouched(self):
        self.assert_untouched("""
            def foo(a):
                return a + a""")
        self.assert_untouched("""
            def foo():
                return 42 + 42""")
        self.assert_untouched("""
            def foo(a):
                return -a + -a""")
        self.assert_untouched("""
            def foo():
                import math
                return math.pi + math.pi""")

    def test_cse_subscript_untouched(self):
        self.assert_untouched("""
            def foo(a, i):
                return a[i] + a[i]""")

    def test_cse_literals_untouched(self):
        self.assert_untouched("""
            def foo(a, b):
                return [a, b] + [a, b]""")
        self.assert_untouched("""
            def foo(a, b):
                x = (a, b)
                y = (a, b)
                return x, y""")
        self.assert_untouched("""
            def foo(a, b):
                x = {a, b}
                y = {a, b}
                return x, y""")
        self.assert_untouched("""
            def foo(a, b):
                x = {"a": a, "b": b}
                y = {"a": a, "b": b}
                return x, y""")

    def test_cse_comprehension_not_hoisted(self):
        pm = PassManager("testing")
        node = ast.parse(dedent("""
            def foo(a, b, items):
                x = [a + b for _ in items]
                y = [a + b for _ in items]
                z = ((c for c in items), a + b)
                w = ((c for c in items), a + b)
                return x, y, z, w"""))
        pm.apply(CommonSubexpressionElimination, node)
        for stmt in ast.walk(node):
            if (isinstance(stmt, ast.Assign) and
                    isinstance(stmt.targets[0], ast.Name) and
                    stmt.targets[0].id.startswith("__cse")):
                self.assertNotIsInstance(stmt.value, (ast.ListComp,
                                                      ast.GeneratorExp))

    def test_cse_rebound_operand(self):
        self.assert_untouched("""
            def foo(a, b):
                x = (a + b) * 2
                a = a + 1
                y = (a + b) * 3
                return x + y""")

    def test_cse_operand_rebound_in_branch(self):
        self.assert_untouched("""
            def foo(a, b, c, d):
                x = (a + b) * c
                if d:
                    a = a + 1
                y = (a + b) * c
                return x + y""")

    def test_cse_operand_rebound_in_loop(self):
        init = """
            def foo(a, b, c, d):
                x = (a + b) * c
                for i in range(d):
                    a = a + i
                y = (a + b) * c
                return x + y"""
        ref = """
            def foo(a, b, c, d):
                a_ = a
                x = ((a_ + b) * c)
                for i in builtins.range(d):
                    a_ = (a_ + i)
                y = ((a_ + b) * c)
                return (x + y)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_across_branches(self):
        self.assert_untouched("""
            def foo(a, b, c):
                if c > 0:
                    x = (a + b) * 2
                else:
                    x = (a + b) * 3
                return x""")

    def test_cse_across_try_block(self):
        self.assert_untouched("""
            def foo(a, b, c):
                try:
                    x = (a + b) * c
                except:
                    x = 0
                y = (a + b) * c
                return x + y""")

    def test_cse_across_with_block(self):
        pm = PassManager("testing")
        node = ast.parse(dedent("""
            def foo(a, b, c, mgr):
                with mgr:
                    x = (a + b) * c
                    pass
                y = (a + b) * c
                return x + y"""))
        updated, _ = pm.apply(CommonSubexpressionElimination, node)
        self.assertFalse(updated)
        self.assertEqual([n for n in ast.walk(node)
                          if isinstance(n, ast.Name) and
                          n.id.startswith("__cse")], [])

    def test_cse_loop_body(self):
        init = """
            def foo(a, b, n):
                out = 0
                for i in range(n):
                    out += (a + b) * i + (a + b) * i
                return out"""
        ref = """
            def foo(a, b, n):
                out = 0
                for i in builtins.range(n):
                    __cse0 = ((a + b) * i)
                    out += (__cse0 + __cse0)
                return out"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_omp_loop(self):
        init = """
            def foo(a, b, n):
                out = 0
                "omp parallel for reduction(+:out)"
                for i in range(n):
                    out += (a + b) * i + (a + b) * i
                return out"""
        ref = """
            def foo(a, b, n):
                out = 0
                'omp parallel for reduction(+:out)'
                for i in builtins.range(n):
                    out += (((a + b) * i) + ((a + b) * i))
                return out"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_omp_in_other_function(self):
        init = """
            def foo(a, b, c, d):
                return (a + b) * c + (a + b) * d
            def bar(a, b, n):
                out = 0
                "omp parallel for reduction(+:out)"
                for i in range(n):
                    out += (a + b) * i + (a + b) * i
                return out"""
        ref = """
            def foo(a, b, c, d):
                __cse0 = (a + b)
                return ((__cse0 * c) + (__cse0 * d))
            def bar(a, b, n):
                out = 0
                'omp parallel for reduction(+:out)'
                for i in builtins.range(n):
                    out += (((a + b) * i) + ((a + b) * i))
                return out"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_avoids_existing_name(self):
        init = """
            def foo(a, b, __cse0):
                return (a + b) + (a + b) + __cse0"""
        ref = """
            def foo(a, b, __cse0):
                __cse1 = (a + b)
                return ((__cse1 + __cse1) + __cse0)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_counter_resets_per_function(self):
        init = """
            def foo(a, b):
                return (a + b) + (a + b)
            def bar(c, d):
                return (c * d) + (c * d)"""
        ref = """
            def foo(a, b):
                __cse0 = (a + b)
                return (__cse0 + __cse0)
            def bar(c, d):
                __cse0 = (c * d)
                return (__cse0 + __cse0)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_names_follow_source_order(self):
        init = """
            def foo(a, b, c, d):
                p = (a + b)
                q = (a + b)
                r = (c + d)
                s = (c + d)
                return (p, q, r, s)"""
        ref = """
            def foo(a, b, c, d):
                __cse0 = (a + b)
                p = __cse0
                __cse1 = (c + d)
                q = __cse0
                r = __cse1
                s = __cse1
                return (p, q, r, s)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_outer_expression_first(self):
        updated, content = self.apply_cse("""
            def foo(a, b, c, d):
                x = (a + b) * c
                y = (a + b) * c
                return x + y + d""")
        self.assertTrue(updated)
        self.assertIn("__cse0 = ((a + b) * c)", content)
        self.assertIn("x = __cse0", content)
        self.assertIn("y = __cse0", content)

    def test_cse_inner_expression_on_next_iteration(self):
        init = """
            def foo(a, b, c, d):
                x = (a + b) * c
                y = (a + b) * c
                z = (a + b) + 1
                return x + y + z + d"""
        ref = """
            def foo(a, b, c, d):
                __cse1 = (a + b)
                __cse0 = (__cse1 * c)
                x = __cse0
                y = __cse0
                z = (__cse1 + 1)
                return (((x + y) + z) + d)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_is_deterministic(self):
        code = """
            def foo(a, b, c, d):
                return (a + b) * c + (a + b) * d"""
        first = self.apply_cse(code)
        for _ in range(3):
            self.assertEqual(first, self.apply_cse(code))

    def test_cse_reaches_fixed_point(self):
        code = """
            def foo(a, b, c, d):
                return (a + b) * c + (a + b) * d"""
        updated, content = self.apply_cse(code)
        self.assertTrue(updated)
        updated, again = self.apply_cse(content)
        self.assertFalse(updated)
        self.assertEqual(content, again)

    def test_cse_preserves_value(self):
        code = dedent("""
            def foo(a, b, c, d):
                x = (a + b) * c
                y = (a + b) * c - d
                return x * y + (a + b) * c""")
        _, content = self.apply_cse(code)
        before, after = {}, {}
        exec(code, before)
        exec(content, after)
        for args in [(1, 2, 3, 4), (-5, 7, 11, 13), (0, 0, 0, 0)]:
            self.assertEqual(before["foo"](*args), after["foo"](*args))

    def test_cse_bool_operands_after_first_are_conditional(self):
        code = """
            def foo(a, i):
                return i < len(a) and a[i] > 0 and a[i] < 9"""
        self.assert_same_behavior(code, "foo", [([1, 5], 0), ([1, 5], 1),
                                                ([1, 5], 2), ([1, 5], 7)])
        code = """
            def foo(x):
                return x and (1 / x) * 2 + (1 / x) * 3"""
        optimized = self.assert_same_behavior(code, "foo",
                                              [(0.,), (2.,), (-4.,)])
        self.assertNotIn("__cse", optimized)

    def test_cse_ifexp_branches_are_conditional(self):
        code = """
            def foo(x):
                return 1 / x + 1 / x if x else 0"""
        optimized = self.assert_same_behavior(code, "foo", [(0.,), (4.,)])
        self.assertNotIn("__cse", optimized)

    def test_cse_ifexp_test_is_unconditional(self):
        code = """
            def foo(a, b, c):
                x = (a + b) * 2 if (a + b) > c else c
                return x"""
        optimized = self.assert_same_behavior(code, "foo", [(1, 2, 0),
                                                            (1, 2, 5)])
        self.assertNotIn("__cse", optimized)

    def test_cse_chained_comparison_is_conditional(self):
        self.assert_untouched("""
            def foo(x):
                return 0 < x < 1 / x + 1 / x""")

    def test_cse_assert_message_is_conditional(self):
        code = """
            def foo(x):
                assert x, 1 / x + 1 / x
                return x"""
        optimized = self.assert_same_behavior(code, "foo", [(1.,), (3.,)])
        self.assertNotIn("__cse", optimized)

    def test_cse_comprehension_body_is_conditional(self):
        pm = PassManager("testing")
        node = ast.parse(dedent("""
            def foo(a, b, items):
                x = [(a + b) * i + (a + b) * i for i in items]
                y = [i for i in items if (a + b) * i > (a + b) * i]
                return x, y"""))
        updated, _ = pm.apply(CommonSubexpressionElimination, node)
        self.assertFalse(updated)

    def test_cse_lambda_body_is_conditional(self):
        node = ast.parse("lambda: (a + b) * c + (a + b) * c").body[0].value
        self.assertTrue(all(conditional for _, conditional in
                            _children_with_conditionality(node, False)))

    def test_cse_conditional_occurrence_is_left_alone(self):
        updated, content = self.apply_cse("""
            def foo(a, b, c):
                x = (a + b) * 2
                y = (a + b) * 3
                z = c and (a + b) * 4
                return x, y, z""")
        self.assertTrue(updated)
        self.assertIn("__cse0 = (a + b)", content)
        self.assertIn("x = (__cse0 * 2)", content)
        self.assertIn("y = (__cse0 * 3)", content)
        self.assertIn("z = (c and ((a + b) * 4))", content)

    def test_cse_conditional_occurrence_alone_does_not_count(self):
        self.assert_untouched("""
            def foo(a, b, c):
                x = (a + b) * 2
                z = c and (a + b) * 4
                return x, z""")

    def test_cse_first_bool_operand_is_unconditional(self):
        init = """
            def foo(a, b, c):
                x = ((a + b) > c) and c
                y = ((a + b) > c) or c
                return x, y"""
        ref = """
            def foo(a, b, c):
                __cse0 = ((a + b) > c)
                x = (__cse0 and c)
                y = (__cse0 or c)
                return (x, y)"""
        self.check_ast(init, ref, self.CSE)

from pythran.tests import TestEnv
from pythran.toolchain import generate_cxx, generate_py
from pythran.typing import List, NDArray
from textwrap import dedent
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

    def check_untouched(self, code, optimizations=CSE):
        content = generate_py("test", dedent(code), optimizations=optimizations)
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

    def test_cse_across_statements(self):
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

    def test_cse_call_argument(self):
        init = """
            import math
            def foo(a, b):
                return math.sqrt(a * b + 1) + math.cos(a * b + 1)"""
        ref = """
            import math as __pythran_import_math
            def foo(a, b):
                __cse0 = ((a * b) + 1)
                return (__pythran_import_math.sqrt(__cse0) + __pythran_import_math.cos(__cse0))"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_larger_expression_first(self):
        init = """
            def foo(a, b, c):
                return (a + b) * c * 2 + (a + b) * c * 3 + (a + b)"""
        ref = """
            def foo(a, b, c):
                __cse1 = (a + b)
                __cse0 = (__cse1 * c)
                return (((__cse0 * 2) + (__cse0 * 3)) + __cse1)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_index(self):
        init = """
            def foo(u, i, n):
                return u[i + 1] - u[i + 1:n - 1] * u[0:n - 1]"""
        ref = """
            def foo(u, i, n):
                __cse0 = (i + 1)
                __cse1 = (n - 1)
                return (u[__cse0] - (u[__cse0:__cse1] * u[0:__cse1]))"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_if_tests(self):
        init = """
            def foo(a, b, c):
                x = 0
                if a < b * c:
                    x = 1
                if a < b * c:
                    x += 2
                return x"""
        ref = """
            def foo(a, b, c):
                x = 0
                __cse0 = (a < (b * c))
                if __cse0:
                    x = 1
                if __cse0:
                    x += 2
                return x"""
        self.check_ast(init, ref, self.CSE)

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

    def test_cse_assigned_by_last_statement(self):
        init = """
            def foo(a, b, n):
                c = a
                for i in range(n):
                    c = (c + b) * 2 + (c + b) * 3
                return c"""
        ref = """
            def foo(a, b, n):
                c = a
                for i in builtins.range(n):
                    __cse0 = (c + b)
                    c = ((__cse0 * 2) + (__cse0 * 3))
                return c"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_lazy(self):
        code = """
            def foo(a, b, c):
                return (a + b) * c + (a + b) / c"""
        module, _ = generate_cxx("test", dedent(code),
                                 optimizations=self.CSE)
        self.assertRegex(str(module), "pythonic::lazy<.*>::type __cse0")

    def test_cse_existing_name(self):
        init = """
            def foo(a, b, __cse0):
                return (a + b) + (a + b) + __cse0
            def bar(c, d):
                return (c * d) + (c * d)"""
        ref = """
            def foo(a, b, __cse0):
                __cse1 = (a + b)
                return ((__cse1 + __cse1) + __cse0)
            def bar(c, d):
                __cse0 = (c * d)
                return (__cse0 + __cse0)"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_cheap(self):
        self.check_untouched("""
            import math
            def foo(a, x):
                p = -a * -a
                q = math.pi * math.pi
                r = x.real * x.real
                s = (a + 1) * (a + 1.)
                return p, q, r, s""")

    def test_cse_subscript(self):
        self.check_untouched("""
            def foo(a, i):
                return a[i] * 2 + a[i] * 3""")

    def test_cse_bound_values(self):
        self.check_untouched("""
            def foo(a, b):
                x = a + b
                y = a + b
                return x, y""")
        self.check_untouched("""
            def foo(a, b):
                x = abs(a + b)
                y = abs(a + b)
                return x, y""")
        self.check_untouched("""
            def foo(a, b):
                return (a + b) is (a + b)""")

    def test_cse_view(self):
        init = """
            import numpy as np
            def foo(x):
                return np.transpose(x) * 2 + np.transpose(x) * 3"""
        ref = """
            import numpy as __pythran_import_numpy
            def foo(x):
                __cse0 = __pythran_import_numpy.transpose(x)
                return ((__cse0 * 2) + (__cse0 * 3))"""
        self.check_ast(init, ref, self.CSE)
        self.check_untouched("""
            import numpy as np
            def foo(x):
                y = np.transpose(x) * 2 + np.transpose(x) * 3
                x[0, 0] = 7
                return y""")
        self.check_untouched("""
            import numpy as np
            def foo(x):
                y = np.transpose(x[1:]) * 2 + np.transpose(x[1:]) * 3
                x[1, 0] = 7
                return y""")
        self.check_untouched("""
            def foo(a, b, c):
                y = (a if c else b) * 2 + (a if c else b) * 3
                a[0] = 7
                return y""")
        self.check_untouched("""
            def foo(a, b):
                y = (a + b) * 2 + (a + b) * 3
                a[0] = 7
                return y""")

    def test_cse_inlinable(self):
        self.check_untouched("""
            def foo(a, b):
                return (a + b) * 2 + (a + b) * 3
            def bar(a, b):
                return foo(a, b) + 1""")

    def test_cse_iterator(self):
        self.check_untouched("""
            def foo(l):
                return max(map(abs, l)) - min(map(abs, l))""")

    def test_cse_in_place_update(self):
        self.check_untouched("""
            def foo(a, b, c):
                x = (a + b) * c
                c[0] = 1
                return x + (a + b) / c""")
        self.check_untouched("""
            def foo(a, b):
                c = a * 2
                x = (a + b) * c
                c += 1
                return x + (a + b) / c""")
        self.check_untouched("""
            def foo(l):
                a = len(l) + 1
                l.append(3)
                b = len(l) + 1
                return a + b""")

    def test_cse_rebound_operand(self):
        self.check_untouched("""
            def foo(a, b):
                c = a
                x = (c + b) * 2
                c = c + 1
                y = (c + b) * 3
                return x + y""")
        self.check_untouched("""
            def foo(a, b, d):
                c = a
                x = (c + b) * 2
                if d:
                    c = c + 1
                y = (c + b) * 3
                return x + y""")

    def test_cse_stored_index(self):
        init = """
            def foo(dx, L, i):
                dx[i + 1] = dx[i + 1] - dx[i + 1] * L
                dx[dx > L / 2] = dx[dx > L / 2] - L
                return dx"""
        ref = """
            def foo(dx, L, i):
                __cse0 = (i + 1)
                dx[__cse0] = (dx[__cse0] - (dx[__cse0] * L))
                dx[(dx > (L / 2))] = (dx[(dx > (L / 2))] - L)
                return dx"""
        self.check_ast(init, ref, self.CSE)

    def test_cse_forwarded_value(self):
        self.check_untouched("""
            import numpy as np
            def foo(a, lo, out):
                mask = a < lo
                out[mask] = 0
                return out, np.logical_not(mask)""",
                             ["pythran.optimizations.ForwardSubstitution"] + self.CSE)

    def test_cse_across_branches(self):
        self.check_untouched("""
            def foo(a, b, c):
                if c > 0:
                    x = (a + b) * 2
                else:
                    x = (a + b) * 3
                return x""")

    def test_cse_while_test(self):
        self.check_untouched("""
            def foo(a, b):
                n = 0
                while (a + b) * n < (a + b) * 2 - n:
                    n += 1
                return n""")

    def test_cse_guarded(self):
        self.check_untouched("""
            def foo(a, b):
                x = (a / b) * 2 if b else 0
                y = b and (a / b) * 3
                return x, y""")

    def test_cse_static(self):
        self.check_untouched("""
            def foo(a):
                return isinstance(a, int) * 2 + isinstance(a, int) * 3""")

    def test_cse_yield(self):
        self.check_untouched("""
            def foo(a, b):
                x = (a + b) * 2
                yield x
                y = (a + b) * 3
                yield y""")

    def test_cse_omp(self):
        self.check_untouched("""
            def foo(a, b, n):
                out = 0
                "omp parallel for reduction(+:out)"
                for i in range(n):
                    out += (a + b) * i + (a + b) * i
                return out""")
        self.check_untouched("""
            def foo(a, b, n):
                x = (a + b) * 2
                out = 0
                "omp parallel for reduction(+:out)"
                for i in range(n):
                    out += i
                y = (a + b) * 3
                return x + y + out""")

    def test_cse_run_array(self):
        code = """
import numpy as np
def cse_run_array(a, b):
    return (a + b) * np.cos(a + b) - (a + b)[1:].sum()"""
        self.run_test(code, numpy.arange(5.), numpy.ones(5),
                      cse_run_array=[NDArray[float, :], NDArray[float, :]])

    def test_cse_run_scalar(self):
        code = """
def cse_run_scalar(x, n):
    s = 0.
    for i in range(n):
        s += (x * i + 1.) * (x * i + 1.) - (x * i + 1.)
    return s"""
        self.run_test(code, 1.5, 10, cse_run_scalar=[float, int])

    def test_cse_run_fresh_arrays(self):
        code = """
import numpy as np
def cse_run_fresh_arrays(n):
    a = np.zeros(n)
    b = np.zeros(n)
    a[0] = 1
    return a, b"""
        self.run_test(code, 3, cse_run_fresh_arrays=[int])

    def test_cse_run_in_place_update(self):
        code = """
def cse_run_in_place_update(a, b, c):
    x = (a + b) * c
    c[0] = 7
    return x + (a + b) / c"""
        self.run_test(code, numpy.arange(4.), numpy.ones(4), numpy.ones(4),
                      cse_run_in_place_update=[NDArray[float, :],
                                               NDArray[float, :],
                                               NDArray[float, :]])

    def test_cse_run_view(self):
        code = """
import numpy as np
def cse_run_view(x):
    y = np.transpose(x) * 2 + np.transpose(x) * 3
    x[0, 0] = 7
    return y"""
        self.run_test(code, numpy.arange(6.).reshape(2, 3),
                      cse_run_view=[NDArray[float, :, :]])

    def test_cse_run_forwarded(self):
        code = """
def cse_run_forwarded(a, b):
    y = (a + b) * 2 + (a + b) * 3
    a[0] = 7
    return y"""
        self.run_test(code, numpy.arange(4.), numpy.ones(4),
                      cse_run_forwarded=[NDArray[float, :],
                                         NDArray[float, :]])

    def test_cse_run_impure_call(self):
        code = """
def cse_run_impure_call(l):
    a = len(l) + 1
    l.append(3)
    b = len(l) + 1
    return a, b"""
        self.run_test(code, [1, 2], cse_run_impure_call=[List[int]])

    def test_cse_run_stored_index(self):
        code = """
def cse_run_stored_index(dx, L):
    dx[dx > L / 2] = dx[dx > L / 2] - L
    return dx"""
        self.run_test(code, numpy.arange(10.), 8.,
                      cse_run_stored_index=[NDArray[float, :], float])

    def test_cse_run_iterator(self):
        code = """
def cse_run_iterator(l):
    return max(map(abs, l)) - min(map(abs, l))"""
        self.run_test(code, [1, -5, 3], cse_run_iterator=[List[int]])

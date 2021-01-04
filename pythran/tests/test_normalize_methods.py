from pythran.tests import TestEnv

import numpy

from tempfile import mkstemp
import unittest
from pythran.typing import List, Set, Dict, NDArray

class TestNormalizeMethods(TestEnv):

    def test_normalize_methods0(self):
        self.run_test("def normalize_methods0(): c = complex(1) ; return complex.conjugate(c)", normalize_methods0=[])

    def test_function_alias0(self):
        self.run_test("""
                      def function_alias0():
                        def p(): return 0
                        g = p
                        return g()""",
                      function_alias0=[])

    def test_function_alias1(self):
        self.run_test("""
                      def function_alias1(n):
                        def p(): return 0
                        def q(): return 1
                        g = p if n else q
                        return g()
                      """,
                      1,
                      function_alias1=[int])

    def test_function_alias2(self):
        self.run_test("""
                      def function_alias2(n):
                        def p(): return 0
                        def q(): return 1
                        if n:
                            g = p
                        else:
                            g = q
                        return g()
                      """,
                      1,
                      function_alias2=[int])

    def test_module_alias0(self):
        self.run_test("def module_alias0(c): import math ; m = math; return m.cos(c)", 1., module_alias0=[float])

    def test_module_alias1(self):
        self.run_test("def module_alias1(c): import math as ma; m = ma; return m.cos(c)", 1., module_alias1=[float])

    def test_module_alias2(self):
        self.run_test("import math as ma\ndef module_alias2(c): m = ma; return m.cos(c)", 1., module_alias2=[float])

    def test_module_alias3(self):
        self.run_test("import math as ma; m = ma\ndef module_alias3(c): return m.cos(c)", 1., module_alias3=[float])

    def test_module_alias4(self):
        self.run_test("""
                      import math as ma
                      def module_alias4(c):
                        import math as ma2
                        m = ma
                        def mab():
                            return m.cos(c) + ma2.cos(c)
                        return mab()""",
                      1.,
                      module_alias4=[float])

    def test_module_alias5(self):
        self.run_test("import math as m2\ndef module_alias5(math): m = m2 ; return m.cos(math)", 1., module_alias5=[float])

    def test_shadow_import0(self):
        self.run_test("def shadow_import0(math): math.add(1)", {1,2}, shadow_import0=[Set[int]])

    def test_shadow_import1(self):
        self.run_test("def shadow_import1(v): math={ v } ; math.add(1)", 1, shadow_import1=[int])

    def test_shadow_import2(self):
        self.run_test("def shadow_import2(s):\n for set in s : set.add(1)", [{1},{2}], shadow_import2=[List[Set[int]]])

    def test_shadow_import3(self):
        self.run_test("def shadow_import3(s): import math ; math = set ; set.add(s, 1)", {1}, shadow_import3=[Set[int]])

    def test_shadow_import4(self):
        self.run_test("import math\ndef shadow_import4(math): math.add(1)", {1}, shadow_import4=[Set[int]])

    def test_builtin_support0(self):
        self.run_test("def builtin_support0(a): import builtins; return builtins.list(a)", [1, 2],  builtin_support0=[List[int]])

    def test_dispatch_clear(self):
        self.run_test("def dispatch_clear(s, d): set.clear(s); dict.clear(d); s.clear(); d.clear() ; return s, d",
                      {1}, {1:1},
                      dispatch_clear=[Set[int],Dict[int,int]])

    def test_dispatch_conjugate(self):
        self.run_test("def dispatch_conjugate(c, n): import numpy; return complex.conjugate(c), numpy.conjugate(n), c.conjugate(), n.conjugate()",
                      2.j, numpy.array([1.j+1.]),
                      dispatch_conjugate=[complex, NDArray[complex, :]])

    def test_dispatch_copy(self):
        self.run_test("def dispatch_copy(d, s, n): import numpy; return dict.copy(d), set.copy(s), numpy.copy(n), d.copy(), s.copy(), n.copy()",
                      {1:1}, {1}, numpy.ones(1),
                      dispatch_copy=[Dict[int,int], Set[int], NDArray[float, :]])

    def test_dispatch_count(self):
        self.run_test("def dispatch_count(s, l): return str.count(s,'1'), list.count(l,1), s.count('1'), l.count(1)",
                      "1", [1],
                      dispatch_count=[str, List[int]])

    def test_dispatch_pop(self):
        self.run_test("def dispatch_pop(l, d): list.pop(l); dict.pop(d,1); l.pop(); d.pop(2); return l, d",
                      [1,2], {1:1, 2:2},
                      dispatch_pop=[List[int], Dict[int,int]])

    def test_dispatch_remove(self):
        self.run_test("def dispatch_remove(s, l): list.remove(l,1); set.remove(s,1); l.remove(2); s.remove(2); return s, l",
                      {1, 2}, [1,2],
                      dispatch_remove=[Set[int], List[int]])

    def test_dispatch_update(self):
        self.run_test("def dispatch_update(s, d): set.update(s, s); dict.update(d,d); s.update(s); d.update(d); return s, d",
                      {1}, {1:1},
                      dispatch_update=[Set[int], Dict[int,int]])

    def test_capture_bound_method(self):
        code = '''
def capture_bound_method(fname, r):
    if r:
        f = open(fname,'w')
        write_line = f.write
    else:
        write_line = fake_write
    for i in range(10):
        write_line(str(i))
    if r:
        f.close()

def fake_write(s):
    return 0'''
        self.run_test(code, "none", False,
                      capture_bound_method=[str, bool])

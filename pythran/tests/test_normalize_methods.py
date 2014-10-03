from test_env import TestEnv
import numpy
from tempfile import mkstemp

class TestBase(TestEnv):

    def test_normalize_methods0(self):
        self.run_test("def normalize_methods0(): c = complex(1) ; return complex.conjugate(c)", normalize_methods0=[])

    def test_shadow_import0(self):
        self.run_test("def shadow_import0(math): math.add(1)", {1,2}, shadow_import0=[{int}])

    def test_shadow_import1(self):
        self.run_test("def shadow_import1(): math={ 1 } ; math.add(1)", shadow_import1=[])

    def test_shadow_import2(self):
        self.run_test("def shadow_import2(s):\n for set in s : set.add(1)", [{1},{2}], shadow_import2=[[{int}]])

    def test_shadow_import3(self):
        self.run_test("def shadow_import3(s): import math ; math = set ; set.add(s, 1)", {1}, shadow_import3=[{int}])

    def test_shadow_import4(self):
        self.run_test("import math\ndef shadow_import4(math): math.add(1)", {1}, shadow_import4=[{int}])

    def test_builtin_support0(self):
        self.run_test("def builtin_support0(a): return __builtin__.list(a)", [1, 2],  builtin_support0=[[int]])

    def test_dispatch_clear(self):
        self.run_test("def dispatch_clear(s, d): set.clear(s); dict.clear(d); s.clear(); d.clear() ; return s, d",
                      {1}, {1:1},
                      dispatch_clear=[{int},{int:int}])

    def test_dispatch_conjugate(self):
        self.run_test("def dispatch_conjugate(c, n): import numpy; return complex.conjugate(c), numpy.conjugate(n), c.conjugate(), n.conjugate()",
                      2.j, numpy.array([1.j+1.]),
                      dispatch_conjugate=[complex, numpy.array([complex])])

    def test_dispatch_copy(self):
        self.run_test("def dispatch_copy(d, s, n): import numpy; return dict.copy(d), set.copy(s), numpy.copy(n), d.copy(), s.copy(), n.copy()",
                      {1:1}, {1}, numpy.ones(1),
                      dispatch_copy=[{int:int}, {int}, numpy.array([float])])

    def test_dispatch_count(self):
        self.run_test("def dispatch_count(s, l): return str.count(s,'1'), list.count(l,1), s.count('1'), l.count(1)",
                      "1", [1],
                      dispatch_count=[str, [int]])

    def test_dispatch_next(self):
        filename = mkstemp()[1]
        with open(filename,"w") as f:
            f.write("a\nb\nc\n")
        self.run_test("def dispatch_next(fn): f = file(fn) ; a = file.next(f); b = f.next(); return a, b",
                      filename,
                      dispatch_next=[str])

    def test_dispatch_pop(self):
        self.run_test("def dispatch_pop(l, d): list.pop(l); dict.pop(d,1); l.pop(); d.pop(2); return l, d",
                      [1,2], {1:1, 2:2},
                      dispatch_pop=[[int], {int:int}])

    def test_dispatch_remove(self):
        self.run_test("def dispatch_remove(s, l): list.remove(l,1); set.remove(s,1); l.remove(2); s.remove(2); return s, l",
                      {1, 2}, [1,2],
                      dispatch_remove=[{int}, [int]])

    def test_dispatch_update(self):
        self.run_test("def dispatch_update(s, d): set.update(s, s); dict.update(d,d); s.update(s); d.update(d); return s, d",
                      {1}, {1:1},
                      dispatch_update=[{int}, {int:int}])

from test_env import TestEnv

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

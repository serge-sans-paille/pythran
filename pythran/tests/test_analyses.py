from test_env import TestEnv
import unittest

class TestAnalyses(TestEnv):

    def test_imported_ids_shadow_intrinsic(self):
        self.run_test("def imported_ids_shadow_intrinsic(range): return [ i*range for i in [1,2,3] ]", 2, imported_ids_shadow_intrinsic=[int])

    def test_shadowed_variables(self):
        self.run_test("def shadowed_variables(a): b=1 ; b+=a ; a= 2 ; b+=a ; return a,b", 18, shadowed_variables=[int])

    def test_decl_shadow_intrinsic(self):
        self.run_test("def decl_shadow_intrinsic(l): len=lambda l:1 ; return len(l)", [1,2,3], decl_shadow_intrinsic=[[int]])

    def test_used_def_chains(self):
        self.run_test("def use_def_chain(a):\n i=a\n for i in xrange(4):\n  print i\n  i=5.4\n  print i\n  break\n  i = 4\n return i", 3, use_def_chain=[int])

    def test_used_def_chains2(self):
        self.run_test("def use_def_chain2(a):\n i=a\n for i in xrange(4):\n  print i\n  i='lala'\n  print i\n  i = 4\n return i", 3, use_def_chain2=[int])

    @unittest.skip("Variable defined in a branch in loops are not accepted.")
    def test_importedids(self):
        self.run_test("def importedids(a):\n i=a\n for i in xrange(4):\n  if i==0:\n   b = []\n  else:\n   b.append(i)\n return b", 3, importedids=[int])

    def test_falsepoly(self):
        self.run_test("def falsepoly():\n i = 2\n if i:\n  i='ok'\n else:\n  i='lolo'\n return i", falsepoly=[])

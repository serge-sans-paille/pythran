from test_env import TestEnv
import unittest 

class TestAnalyses(TestEnv):

    def test_imported_ids_shadow_intrinsic(self):
        self.run_test("def imported_ids_shadow_intrinsic(range): return [ i*range for i in [1,2,3] ]", 2, imported_ids_shadow_intrinsic=[int])

    def test_shadowed_variables(self):
        self.run_test("def shadowed_variables(a): b=1 ; b+=a ; a= 2 ; b+=a ; return a,b", 18, shadowed_variables=[int])

    def test_decl_shadow_intrinsic(self):
        self.run_test("def decl_shadow_intrinsic(l): len=lambda l:1 ; return len(l)", [1,2,3], decl_shadow_intrinsic=[[int]])

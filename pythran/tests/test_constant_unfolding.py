from test_env import TestEnv

class TestConstantUnfolding(TestEnv):

    def test_constant_unfolding_int_literals(self):
        self.run_test("def constant_unfolding_int_literals(): return 1+2*3.5", constant_unfolding_int_literals=[])

    def test_constant_unfolding_str_literals(self):
        self.run_test("def constant_unfolding_str_literals(): return \"1\"+'2'*3", constant_unfolding_str_literals=[])

    def test_constant_unfolding_list_literals(self):
        self.run_test("def constant_unfolding_list_literals(): return [1]+[2]*3", constant_unfolding_list_literals=[])

    def test_constant_unfolding_set_literals(self):
        self.run_test("def constant_unfolding_set_literals(): return {1,2,3,3}", constant_unfolding_set_literals=[])

    def test_constant_unfolding_builtins(self):
        self.run_test("def constant_unfolding_builtins(): return map(len,zip(range(2), range(2)))", constant_unfolding_builtins=[])

    def test_constant_unfolding_imported_functions(self):
        self.run_test("def constant_unfolding_imported_functions(): from math import cos ; return float(int(10*cos(1)))", constant_unfolding_imported_functions=[])

    def test_constant_unfolding_list_method_calls(self):
        self.run_test("def foo(n): l=[] ; l.append(n) ; return l\ndef constant_unfolding_list_method_calls(n): return foo(n)", 1, constant_unfolding_list_method_calls=[int])

    def test_constant_unfolding_complex_calls(self):
        self.run_test("def constant_unfolding_complex_calls(): return complex(1,1)", constant_unfolding_complex_calls=[])

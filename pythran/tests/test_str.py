from test_env import TestEnv

class TestStr(TestEnv):

    def test_str_endswith0(self):
        self.run_test("def str_endswith0(s0, s1): return s0.endswith(s1)", "barbapapa", "papa", str_endswith0=[str, str])

    def test_str_endswith1(self):
        self.run_test("def str_endswith1(s0, s1): return s0.endswith(s1)", "barbapapa", "papy", str_endswith1=[str, str])



from test_env import TestEnv

class TestStr(TestEnv):

    def test_str_endswith0(self):
        self.run_test("def str_endswith0(s0, s1): return s0.endswith(s1)", "barbapapa", "papa", str_endswith0=[str, str])

    def test_str_endswith1(self):
        self.run_test("def str_endswith1(s0, s1): return s0.endswith(s1)", "barbapapa", "papy", str_endswith1=[str, str])

    def test_str_empty(self):
        self.run_test("def str_empty(s0): return '>o_/' if s0 else '0x0'", "", str_empty=[str])

    def test_str_failed_conversion(self):
        self.run_test("def str_failed_conversion(s):\n try: return long(s)\n except: return 42", "prout", str_failed_conversion=[str])

    def test_str_replace0(self):
        self.run_test("def str_replace0(s): return s.replace('er', 'rer')", "parler", str_replace0=[str])

    def test_str_replace1(self):
        self.run_test("def str_replace1(s): return s.replace('er', 'rer', 1)", "erlang manger dessert", str_replace1=[str])

    def test_str_replace2(self):
        self.run_test("def str_replace2(s): return s.replace('', 'du vide surgit rien', 1)", "j aime les moulinettes a fromage", str_replace2=[str])

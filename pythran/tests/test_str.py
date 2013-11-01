from test_env import TestEnv

class TestStr(TestEnv):

   def test_str_startswith0(self):
        self.run_test("def str_startswith0(s0, s1): return s0.startswith(s1)", "barbapapa", "barba", str_startswith0=[str, str])

    def test_str_startswith1(self):
        self.run_test("def str_startswith1(s0, s1): return s0.startswith(s1)", "barbapapa", "barbi", str_startswith1=[str, str])

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

    def test_str_ascii_letters(self):
        self.run_test("def str_ascii_letters(): import string; return string.ascii_letters", str_ascii_letters=[])

    def test_str_ascii_lowercase(self):
        self.run_test("def str_ascii_lowercase(): import string; return string.ascii_lowercase", str_ascii_lowercase=[])

    def test_str_ascii_uppercase(self):
        self.run_test("def str_ascii_uppercase(): import string; return string.ascii_uppercase", str_ascii_uppercase=[])

    def test_str_digits(self):
        self.run_test("def str_digits(): import string; return string.digits", str_digits=[])

    def test_str_hexdigits(self):
        self.run_test("def str_hexdigits(): import string; return string.hexdigits", str_hexdigits=[])

    def test_str_octdigits(self):
        self.run_test("def str_octdigits(): import string; return string.octdigits", str_octdigits=[])

    def test_str_lower(self):
        self.run_test("def str_lower(s): return s.lower()", "ThiS iS a TeST", str_lower=[str])

    def test_str_upper(self):
        self.run_test("def str_upper(s): return s.upper()", "ThiS iS a TeST", str_upper=[str])

    def test_str_capitalize(self):
        self.run_test("def str_capitalize(s): return s.capitalize()", "thiS iS a TeST", str_capitalize=[str])

    def test_str_strip(self):
        self.run_test("def str_strip(s): return s.strip()", "       ThiS iS a TeST        ", str_strip=[str])

    def test_str_strip2(self):
        self.run_test("def str_strip2(s): return s.strip(\"TSih\")", "ThiS iS a TeST", str_strip2=[str])

    def test_str_lstrip(self):
        self.run_test("def str_lstrip(s): return s.lstrip()", "       ThiS iS a TeST        ", str_lstrip=[str])

    def test_str_lstrip2(self):
        self.run_test("def str_lstrip2(s): return s.lstrip(\"TSih\")", "ThiS iS a TeST", str_lstrip2=[str])

    def test_str_rstrip(self):
        self.run_test("def str_rstrip(s): return s.rstrip()", "       ThiS iS a TeST        ", str_rstrip=[str])

    def test_str_rstrip2(self):
        self.run_test("def str_rstrip2(s): return s.rstrip(\"TSih\")", "ThiS iS a TeST", str_rstrip2=[str])

    def test_str_format(self):
        self.run_test("def str_format(): a = 43.23; return '%.2f %.2f' % (a, a)", str_format=[])

    def test_str_join0(self):
        self.run_test("def str_join0(): a = ['1'] ; a.pop() ; return 'e'.join(a)", str_join0=[])

    def test_str_join1(self):
        self.run_test("def str_join1(): a = ['l', 'l'] ; return 'o'.join(a)", str_join1=[])

    def test_str_join2(self):
        self.run_test("def str_join2(): from itertools import ifilter ; a = ['l', 'l'] ; return 'o'.join(ifilter(len, a))", str_join2=[])

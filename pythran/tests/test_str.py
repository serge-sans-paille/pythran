from pythran.tests import TestEnv
from pythran.typing import List

import unittest


class TestStr(TestEnv):

    def test_str_noarg(self):
        self.run_test("def str_noarg(n): return (str if n else lambda: '1')()",
                      1, str_noarg=[int])

    def test_str_startswith0(self):
        self.run_test("def str_startswith0(s0, s1): return s0.startswith(s1)", "barbapapa", "barba", str_startswith0=[str, str])
        self.run_test("def str_startswith0a(s0, s1): return s0[0].startswith(s1)", "barbapapa", "barba", str_startswith0a=[str, str])

    def test_str_startswith1(self):
        self.run_test("def str_startswith1(s0, s1): return s0.startswith(s1)", "barbapapa", "barbi", str_startswith1=[str, str])
        self.run_test("def str_startswith1a(s0, s1): return s0[0].startswith(s1)", "barbapapa", "barbi", str_startswith1a=[str, str])

    def test_str_endswith0(self):
        self.run_test("def str_endswith0(s0, s1): return s0.endswith(s1)", "barbapapa", "papa", str_endswith0=[str, str])
        self.run_test("def str_endswith0a(s0, s1): return s0[0].endswith(s1)", "barbapapa", "papa", str_endswith0a=[str, str])

    def test_str_endswith1(self):
        self.run_test("def str_endswith1(s0, s1): return s0.endswith(s1)", "barbapapa", "papy", str_endswith1=[str, str])
        self.run_test("def str_endswith1a(s0, s1): return s0[0].endswith(s1)", "barbapapa", "papy", str_endswith1a=[str, str])

    def test_str_empty(self):
        self.run_test("def str_empty(s0): return '>o_/' if s0 else '0x0'", "", str_empty=[str])

    def test_str_failed_conversion(self):
        self.run_test("def str_failed_conversion(s):\n try: return int(s)\n except: return 42", "prout", str_failed_conversion=[str])
        self.run_test("def str_failed_conversion_a(s):\n try: return int(s[0])\n except: return 42", "prout", str_failed_conversion_a=[str])

    def test_str_replace0(self):
        self.run_test("def str_replace0(s): return s.replace('er', 'rer')", "parler", str_replace0=[str])
        self.run_test("def str_replace0a(s): return s.replace('er', 'r')", "parler", str_replace0a=[str])
        self.run_test("def str_replace0b(s): return s[0].replace('er', 'r')", "parler", str_replace0b=[str])

    def test_str_replace1(self):
        self.run_test("def str_replace1(s): return s.replace('er', 'rer', 1)", "erlang manger dessert", str_replace1=[str])
        self.run_test("def str_replace1a(s): return s.replace('er', 'r', 1)", "erlang manger dessert", str_replace1a=[str])
        self.run_test("def str_replace1b(s): return s[0].replace('er', 'r', 1)", "erlang manger dessert", str_replace1b=[str])

    def test_str_replace2(self):
        self.run_test("def str_replace2(s): return s.replace('', 'du vide surgit rien', 1)", "j aime les moulinettes a fromage", str_replace2=[str])
        self.run_test("def str_replace2a(s): return s[0].replace('', 'du vide surgit rien', 1)", "j aime les moulinettes a fromage", str_replace2a=[str])

    def test_str_ascii_letters(self):
        self.run_test("def str_ascii_letters(): import string; return string.ascii_letters", str_ascii_letters=[])

    def test_str_ascii_lowercase(self):
        self.run_test("def str_ascii_lowercase(): import string; return string.ascii_lowercase", str_ascii_lowercase=[])

    def test_str_ascii_uppercase(self):
        self.run_test("def str_ascii_uppercase(): import string; return string.ascii_uppercase", str_ascii_uppercase=[])

    def test_str_digits(self):
        self.run_test("def str_digits(): import string; return string.digits", str_digits=[])

    def test_str_with_backslash(self):
        self.run_test("def str_with_backslash(): return '''\h'''",
                      str_with_backslash=[])

    def test_str_hexdigits(self):
        self.run_test("def str_hexdigits(): import string; return string.hexdigits", str_hexdigits=[])

    def test_str_octdigits(self):
        self.run_test("def str_octdigits(): import string; return string.octdigits", str_octdigits=[])

    def test_str_lower(self):
        self.run_test("def str_lower(s): return s.lower()", "ThiS iS a TeST", str_lower=[str])
        self.run_test("def str_lower_a(s): return s[0].lower()", "ThiS iS a TeST", str_lower_a=[str])

    def test_str_upper(self):
        self.run_test("def str_upper(s): return s.upper()", "ThiS iS a TeST", str_upper=[str])
        self.run_test("def str_upper_a(s): return s[0].upper()", "ThiS iS a TeST", str_upper_a=[str])

    def test_str_capitalize(self):
        self.run_test("def str_capitalize(s): return s.capitalize()", "thiS iS a TeST", str_capitalize=[str])
        self.run_test("def str_capitalize_a(s): return s[0].capitalize()", "thiS iS a TeST", str_capitalize_a=[str])

    def test_str_strip(self):
        self.run_test("def str_strip(s): return s.strip()", "       ThiS iS a TeST        ", str_strip=[str])
        self.run_test("def str_strip_a(s): return s[0].strip()", "       ThiS iS a TeST        ", str_strip_a=[str])

    def test_str_strip2(self):
        self.run_test("def str_strip2(s): return s.strip(\"TSih\")", "ThiS iS a TeST", str_strip2=[str])

    def test_str_lstrip(self):
        self.run_test("def str_lstrip(s): return s.lstrip()", "       ThiS iS a TeST        ", str_lstrip=[str])
        self.run_test("def str_lstrip_a(s): return s[0].lstrip()", "       ThiS iS a TeST        ", str_lstrip_a=[str])

    def test_str_lstrip2(self):
        self.run_test("def str_lstrip2(s): return s.lstrip(\"TSih\")", "ThiS iS a TeST", str_lstrip2=[str])

    def test_str_rstrip(self):
        self.run_test("def str_rstrip(s): return s.rstrip()", "       ThiS iS a TeST        ", str_rstrip=[str])
        self.run_test("def str_rstrip_a(s): return s[0].rstrip()", "       ThiS iS a TeST        ", str_rstrip_a=[str])

    def test_str_rstrip2(self):
        self.run_test("def str_rstrip2(s): return s.rstrip(\"TSih\")", "ThiS iS a TeST", str_rstrip2=[str])

    def test_str_split1(self):
        self.run_test("def str_split1(s): return s.split()", "ThiS iS a TeST", str_split1=[str])
        self.run_test("def str_split1_a(s): return s[0].split()", "ThiS iS a TeST", str_split1_a=[str])

    def test_str_split2(self):
        self.run_test("def str_split2(s): return s.split('S')", "ThiS iS a TeST", str_split2=[str])

    def test_str_split3(self):
        self.run_test("def str_split3(s): return s.split()", "ThiS  iS\t a TeST", str_split3=[str])

    def test_str_split4(self):
        self.run_test("def str_split4(s): return s.split()", "", str_split4=[str])

    def test_str_format(self):
        self.run_test("def str_format(a): return '%.2f %.2f' % (a, a)", 43.23, str_format=[float])

    def test_str_join0(self):
        self.run_test("def str_join0(): a = ['1'] ; a.pop() ; return '+e+'.join(a)", str_join0=[])
        self.run_test("def str_join0a(): a = ['1'] ; a.pop() ; return 'e'.join(a)", str_join0a=[])

    def test_str_join1(self):
        self.run_test("def str_join1(): a = ['l', 'l'] ; return 'o'.join(a)", str_join1=[])

    def test_str_join2(self):
        self.run_test("def str_join2(a): return 'o'.join(filter(len, a))", ['l', 'l'], str_join2=[List[str]])

    def test_str_find0(self):
        self.run_test("def str_find0(s): return s.find('pop')", "popop", str_find0=[str])
        self.run_test("def str_find0a(s): return s.find('p')", "popop", str_find0a=[str])
        self.run_test("def str_find0b(s): return s[0].find('p')", "popop", str_find0b=[str])

    def test_str_find1(self):
        self.run_test("def str_find1(s): return s.find('pap')", "popop", str_find1=[str])

    def test_str_reversal(self):
        self.run_test("def str_reversal(s): return list(map(ord,reversed(s)))", "dear", str_reversal=[str])
        self.run_test("def str_reversal_a(s): return list(map(ord,reversed(s[0])))", "dear", str_reversal_a=[str])

    def test_str_substring_iteration(self):
        self.run_test("def str_substring_iteration(s): return list(map(ord, s[1:-1]))", "pythran", str_substring_iteration=[str])

    def test_str_isalpha(self):
        self.run_test("def str_isalpha(s, t, u): return s.isalpha(), t.isalpha(), u.isalpha()", "e", "1", "", str_isalpha=[str,str, str])
        self.run_test("def str_isalpha_a(s, t): return s[0].isalpha(), t[0].isalpha()", "e", "1", str_isalpha_a=[str,str])

    def test_str_isdigit(self):
        self.run_test("def str_isdigit(s, t, u): return s.isdigit(), t.isdigit(), u.isdigit()", "e", "1", "", str_isdigit=[str,str, str])
        self.run_test("def str_isdigit_a(s, t): return s[0].isdigit(), t[0].isdigit()", "e", "1", str_isdigit_a=[str,str])

    def test_str_count(self):
        self.run_test("def str_count(s, t, u, v): return s.count(t), s.count(u), s.count(v)",
                      "pythran is good for health", "py", "niet", "t",
                      str_count=[str, str, str, str])
        self.run_test("def str_count_a(s, t, u, v): return s[0].count(t), s[1].count(u), s.count(v[0])",
                      "pythran is good for health", "py", "niet", "t",
                      str_count_a=[str, str, str, str])

    def test_str_literal_cmp(self):
        code = '''
            def eee(a, i):
                if a == "ABCD":
                    return 2 * i
                elif a != "ZDSD":
                    return 1 * i
                return 3 * i

            def str_literal_cmp(a, i):
                if a == "EEE":
                   return eee("ZZZ", i), eee("ABCD", i)
                else:
                   return eee("YYY", i), 3'''
        self.run_test(code, "EEE", 2, str_literal_cmp=[str, int])

    def test_str_literal_cmp1(self):
        code = '''
            def eee(a, i):
                if a > "ABCD":
                    return 2 * i
                elif a <= "ZDSD":
                    return 1 * i
                return 3 * i

            def str_literal_cmp1(a, i):
                if a == "EEE":
                   return eee("ZZZ", i), eee("ABCD", i)
                else:
                   return eee("YYY", i), 3'''
        self.run_test(code, "EEE", 2, str_literal_cmp1=[str, int])

    def test_str_literal_cmp2(self):
        code = '''
            def eee(a, i):
                if a < "ABCD":
                    return 2 * i
                elif a >= "ZDSD":
                    return 1 * i
                return 3 * i

            def str_literal_cmp2(a, i):
                if a == "EEE":
                   return eee("ZZZ", i), eee("ABCD", i)
                else:
                   return eee("YYY", i), 3'''
        self.run_test(code, "EEE", 2, str_literal_cmp2=[str, int])

    def test_str_literal_add(self):
        code = '''
            def eee(a, i):
                if i > 0:
                    return a + "ABCD"
                else:
                    return a + "BCD"

            def str_literal_add(a, i):
                if a == "EEE":
                   return eee("ZZZ", i), eee("ABCD", i)
                else:
                   return eee("YYY", i), "3"'''
        self.run_test(code, "EEE", 2, str_literal_add=[str, int])

    def test_str_literal_mult(self):
        code = '''
            def eee(a, i):
                if i > 0:
                    return a * i
                else:
                    return a * 3

            def str_literal_mult(a, i):
                if a == "EEE":
                   return eee("ZZZ", i), eee("ABCD", i)
                else:
                   return eee("YYY", i), "3"'''
        self.run_test(code, "EEE", 2, str_literal_mult=[str, int])

    def test_str_float(self):
        self.run_test("def str_float(s): return float(s)", "0.000012", str_float=[str])

    def test_str_numpy_float32(self):
        self.run_test("def str_numpy_float32(s): import numpy; return numpy.float32(s)", "0.000012",
                      str_numpy_float32=[str])

    def test_str_numpy_float64(self):
        self.run_test("def str_numpy_float64(s): import numpy; return numpy.float64(s)", "0.000012",
                      str_numpy_float64=[str])

    def test_str_int(self):
        self.run_test("def str_int(s): return int(s)", "12", str_int=[str])

    def test_str_id(self):
        self.run_test("def str_id(x): return id(x) != 0", "hello", str_id=[str])

    def test_str_slice_assign(self):
        self.run_test('''
            def str_slice_assign(s, c):
                if s.startswith(c):
                    s = s[len(c):];
                return s''', "LEFT-B6", "LEFT-",
                      str_slice_assign=[str, str])

    def test_str_slice_assign2(self):
        self.run_test('''
        def sample_datatype(value):
            definitions = [ 
                ('LEFT-', 1), 
                ('RIGHT-', 2), 
                ('', 3)
            ]   
        
            plate_number = None
            for definition in definitions:
                s, n = definition
                if value.startswith(s):
                    plate_number = n 
                    value = value[len(s):]
                    break
            if plate_number is None:   # Comment for make it works
               raise ValueError("Invalid value")
            return None

        def str_slice_assign2(s1):
            sample_datatype(s1)
            return s1''', "LEFT-B6", str_slice_assign2=[str])

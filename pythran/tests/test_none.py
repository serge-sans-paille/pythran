from test_env import TestEnv
from unittest import skip
from pythran.typing import List

class TestNone(TestEnv):

    def test_returned_none(self):
        code = '''
def dummy(l):
    if l: return None
    else: return l
def returned_none(a):
    return dummy(a)'''
        self.run_test(code, [1, 2], returned_none=[List[int]])

    def test_returned_none_member(self):
        code = '''
def dummy(l):
    if not l: return None
    else: return l
def returned_none_member(a):
    t = dummy(a)
    if t is None:
        return None
    else:
        return t.count(1)'''
        self.run_test(code, [1, 2], returned_none_member=[List[int]])

    def test_use_none(self):
        code = """
            def none_input(a):
                l = list(range(10))
                if a is None:
                    return l[a:8]
                else:
                    return l[a:8]
            """
        self.run_test(code, None, none_input=[type(None)])

    def test_none_as_default_param(self):
        code = """
            def  none_as_default_param(x):
                if x is None:
                    x = -1
                return abs(x)"""
        self.run_test(code, None, none_as_default_param=[type(None)])

    def test_none_as_default_param_eq(self):
        code = """
            def  none_as_default_param_eq(x):
                if x == None:
                    x = -1
                return abs(x)"""
        self.run_test(code, -2, none_as_default_param_eq=[int])

    def test_none_as_default_param_swap(self):
        code = """
            def  none_as_default_param_swap(x):
                if None is x:
                    x = -1
                return abs(x)"""
        self.run_test(code, None, none_as_default_param_swap=[type(None)])

    def test_none_orelse(self):
        code = '''
                def none_orelse(x) :
                  if x is None :
                      y = 1
                  else:
                      y = x
                  return abs(y)'''
        self.run_test(code, None, none_orelse=[type(None)])

    def test_none_orelse2(self):
        code = '''
                def none_orelse2(x) :
                  if x is None :
                      y = 1
                  else:
                      y = x
                  return abs(y)'''
        self.run_test(code, 3, none_orelse2=[int])

    def test_none_orelse3(self):
        code = '''
                def none_orelse3(x) :
                  y = 3
                  if x is None :
                      y = 1
                  else:
                      y *= x
                  return abs(y)'''
        self.run_test(code, 3, none_orelse3=[int])

    def test_none_orelse4(self):
        code = '''
                def none_orelse4(x) :
                  if x is None :
                      x = 1
                  else:
                      x *= 2
                  return abs(x)'''
        self.run_test(code, 4, none_orelse4=[int])

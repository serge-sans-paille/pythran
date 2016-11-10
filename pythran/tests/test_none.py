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

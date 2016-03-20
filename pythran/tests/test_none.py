from test_env import TestEnv
from unittest import skip

class TestNone(TestEnv):

    def test_returned_none(self):
        code = '''
def dummy(l):
    if l: return None
    else: return l
def returned_none(a):
    return dummy(a)'''
        self.run_test(code, [1, 2], returned_none=[[int]])

    def test_returned_none_member(self):
        code = '''
def dummy(l):
    if not l: return None
    else: return l
def returned_none_member(a):
    return dummy(a).count(1)'''
        self.run_test(code, [1, 2], returned_none_member=[[int]])

    def test_use_none(self):
        code = """
            def none_input(a):
                return range(10)[a:8]
            """
        self.run_test(code, None, none_input=[type(None)])

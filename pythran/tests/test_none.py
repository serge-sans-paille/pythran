from test_env import TestEnv
from unittest import skip

class TestNone(TestEnv):

    def test_returned_none(self):
        code = '''
def dummy(l):
    if l: return None
    else: return l
def returned_none():
    return dummy([1,2])'''
        self.run_test(code, returned_none=[])

    def test_returned_none_member(self):
        code = '''
def dummy(l):
    if not l: return None
    else: return l
def returned_none_member():
    return dummy([1,2]).count(1)'''
        self.run_test(code, returned_none_member=[])

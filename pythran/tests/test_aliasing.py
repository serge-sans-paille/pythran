from test_env import TestEnv

class TestAliasing(TestEnv):

    def test_aliasing0(self):
        code='''
def aliasing0(e):
        if 1:
            t = e
        else:
            f = e'''
        self.run_test(code, range(10), aliasing0=[[int]])


from test_env import TestEnv

class TestAdvanced(TestEnv):

    def test_generator_enumeration(self):
        code = '''
def dummy_generator(l):
    for i in l: yield i
def generator_enumeration():
    return [i for i in enumerate(dummy_generator(range(2,10)))]'''
        self.run_test(code, generator_enumeration=[])

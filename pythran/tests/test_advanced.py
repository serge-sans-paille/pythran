from test_env import TestEnv

class TestAdvanced(TestEnv):

    def test_generator_enumeration(self):
        code = '''
def dummy_generator(l):
    for i in l: yield i
def generator_enumeration():
    return [i for i in enumerate(dummy_generator(range(2,10)))]'''
        self.run_test(code, generator_enumeration=[])

    def test_augassign_floordiv(self):
        self.run_test("def augassign_floordiv(i,j): k=i ; k//=j; return k",
                2, 5, augassign_floordiv=[int, int])

    def test_builtin_constructors(self):
        self.run_test("def builtin_constructors(l): return map(int,l)",
                [1.5, 2.5], builtin_constructors=[[float]])

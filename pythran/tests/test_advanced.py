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

    def test_tuple_sum(self):
        self.run_test("def tuple_sum(): return sum((1,2,3.5))", tuple_sum=[])

    def test_minus_unary_minus(self):
        self.run_test("def minus_unary_minus(a): return a - -1", 1, minus_unary_minus=[int])

    def test_bool_op_casting(self):
        self.run_test('''
def bool_op_casting():
    l=[]
    L=[1]
    M=[2]
    if (l and L) or M:
        return (l and L) or M
    else:
        return M''', bool_op_casting=[])

    def test_map_on_generator(self):
        self.run_test('def map_on_generator(l): return map(float,(x*x for x in l))', [1,2,3], map_on_generator=[[int]])

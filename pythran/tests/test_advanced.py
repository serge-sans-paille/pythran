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

    def test_map_none_on_generator(self):
        self.run_test('def map_none_on_generator(l): return map(None,(x*x for x in l))', [1,2,3], map_none_on_generator=[[int]])

    def test_map_none2_on_generator(self):
        self.run_test('def map_none2_on_generator(l): return map(None,(x*x for x in l), (2*x for x in l))', [1,2,3], map_none2_on_generator=[[int]])

    def test_max_interface_arity(self):
        self.run_test('def max_interface_arity({0}):pass'.format(*['_'+str(i) for i in xrange(42)]), range(42), max_interface_arity=[[int]*42])

    def test_multiple_max(self):
        self.run_test('def multiple_max(i,j,k): return max(i,j,k)', 1, 1.5, False, multiple_max=[int, float, bool])

    def test_zip_on_generator(self):
        self.run_test('def zip_on_generator(n): return zip((i for i in xrange(n)), (i*2 for i in xrange(1,n+1)))', 5, zip_on_generator=[int])

    def test_parallel_enumerate(self):
        self.run_test('def parallel_enumerate(l):\n k = [0]*(len(l) + 1)\n "omp parallel for private(i,j)"\n for i,j in enumerate(l):\n  k[i+1] = j\n return k', range(1000), parallel_enumerate=[[int]])

from test_env import TestEnv
from unittest import skip

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

    def test_map2_on_generator(self):
        self.run_test('def map2_on_generator(l): return map(lambda x,y : x*y, l, (y for x in l for y in l if x < 1))', [0,1,2,3], map2_on_generator=[[int]])

    def test_map_none_on_generator(self):
        self.run_test('def map_none_on_generator(l): return map(None,(x*x for x in l))', [1,2,3], map_none_on_generator=[[int]])

    def test_enumerate_on_generator(self):
        self.run_test("def enumerate_on_generator(n): return map(lambda (x,y) : x, enumerate((y for x in xrange(n) for y in xrange(x))))", 5, enumerate_on_generator=[int])

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

    def test_ultra_nested_functions(self):
        code = '''
def ultra_nested_function(n):
	def foo(y):
		def bar(t): return t
		return bar(y)
	return foo(n)'''
        self.run_test(code, 42, ultra_nested_function=[int])
        
    def test_generator_sum(self):
        code = '''
def generator_sum(l0,l1):
    return sum(x*y for x,y in zip(l0,l1))'''
        self.run_test(code, range(10), range(10), generator_sum=[[int],[int]])

    def test_tuple_to_list(self):
        self.run_test('def tuple_to_list(t): return list(t)', (1,2,3), tuple_to_list=[(int, int, int)])

    def test_in_generator(self):
        self.run_test("def in_generator(n):return 1. in (i*i for i in xrange(n))", 5, in_generator=[int])

    def test_tuple_unpacking_in_generator(self):
        code = '''
def foo(l):
    a,b= 1,0
    yield a
    yield b
def tuple_unpacking_in_generator():
    f = foo(range(10))
    return 0 in f'''
        self.run_test(code, tuple_unpacking_in_generator=[])

    def test_loop_tuple_unpacking_in_generator(self):
        code= '''
def foo(l):
    for i,j in enumerate(l):
        yield i,j
def loop_tuple_unpacking_in_generator():
    f = foo(range(10))
    return (0,0) in f'''
        self.run_test(code, loop_tuple_unpacking_in_generator=[])

    def test_assign_in_except(self):
        code = '''
def assign_in_except():
    try:
        a=1
    except:
        a+=a
    return a'''
        self.run_test(code, assign_in_except=[])

    def test_combiner_on_empty_list(self):
        code = '''
def b(l):
    l+=[1]
    return l
def combiner_on_empty_list():
    return b(list()) + b([])'''
        self.run_test(code, combiner_on_empty_list=[])

    def test_dict_comprehension_with_tuple(self):
        self.run_test('def dict_comprehension_with_tuple(n): return { x:y for x,y in zip(range(n), range(1+n)) }', 10, dict_comprehension_with_tuple=[int])

    def test_nested_comprehension_with_tuple(self):
        self.run_test('def nested_comprehension_with_tuple(l): return [[ x+y for x,y in sqrpoints ] for sqrpoints in l]', [[(x,x)]*5 for x in range(10)], nested_comprehension_with_tuple=[[[(int,int)]]])

    def test_hashable_tuple(self):
        self.run_test('def hashable_tuple(): return { (1,"e", 2.5) : "r" }', hashable_tuple=[])

    def test_conflicting_names(self):
        self.run_test('def map(): return 5', map=[])

    def test_multiple_compares(self):
        self.run_test('def multiple_compares(x): return 1 < x <2, 1< x+1 < 2', 0.5, multiple_compares=[float])

    def test_default_arg0(self):
        self.run_test('def default_arg0(n=12): return n', default_arg0=[])

    def test_default_arg1(self):
        self.run_test('def default_arg1(m,n=12): return m+n', 1, default_arg1=[int])

    def test_default_arg2(self):
        self.run_test('def default_arg2(n=12): return n', 1, default_arg2=[int])

    def test_default_arg3(self):
        self.run_test('def default_arg3(m,n=12): return m+n', 1, 2, default_arg3=[int,int])

    def test_long_to_float_conversion(self):
        self.run_test('def long_to_float_conversion(l): return float(l)', 12345678912345678L, long_to_float_conversion=[long])

    @skip("lists as zeros parameter are not supported")
    def test_list_as_zeros_parameter(self):
        self.run_test('def list_as_zeros_parameter(n): from numpy import zeros ; return zeros([n,n])', 3, list_as_zeros_parameter=[int])

from test_env import TestEnv

from pythran.config import have_gmp_support

from unittest import skip, skipIf
import sys

class TestAdvanced(TestEnv):

    def test_generator_enumeration(self):
        code = '''
def dummy_generator(l):
    for i in l: yield i
def generator_enumeration(begin, end):
    return [i for i in enumerate(dummy_generator(range(begin,end)))]'''
        self.run_test(code, 2, 10, generator_enumeration=[int, int])

    def test_augassign_floordiv(self):
        self.run_test("def augassign_floordiv(i,j): k=i ; k//=j; return k",
                2, 5, augassign_floordiv=[int, int])

    def test_builtin_constructors(self):
        self.run_test("def builtin_constructors(l): return list(map(int,l))",
                [1.5, 2.5], builtin_constructors=[[float]])

    def test_tuple_sum(self):
        self.run_test("def tuple_sum(tpl): return sum(tpl)", (1, 2, 3.5), tuple_sum=[(int, int, float)])

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
        self.run_test('def map_on_generator(l): return list(map(float,(x*x for x in l)))', [1,2,3], map_on_generator=[[int]])

    def test_map2_on_generator(self):
        self.run_test('def map2_on_generator(l): return list(map(lambda x,y : x*y, l, (y for x in l for y in l if x < 1)))', [0,1,2,3], map2_on_generator=[[int]])

    @skipIf(sys.version_info.major == 3, "None is not callable in Python3")
    def test_map_none_on_generator(self):
        self.run_test('def map_none_on_generator(l): return list(map(None,(x*x for x in l)))', [1,2,3], map_none_on_generator=[[int]])

    def test_enumerate_on_generator(self):
        self.run_test("def enumerate_on_generator(n): return list(map(lambda (x,y) : x, enumerate((y for x in xrange(n) for y in xrange(x)))))", 5, enumerate_on_generator=[int])

    @skipIf(sys.version_info.major == 3, "None is not callable in Python3")
    def test_map_none2_on_generator(self):
        self.run_test('def map_none2_on_generator(l): return map(None,(x*x for x in l), (2*x for x in l))', [1,2,3], map_none2_on_generator=[[int]])

    def test_max_interface_arity(self):
        self.run_test('def max_interface_arity({0}):pass'.format(*['_'+str(i) for i in range(42)]), list(range(42)), max_interface_arity=[[int]*42])

    def test_multiple_max(self):
        self.run_test('def multiple_max(i,j,k): return max(i,j,k)', 1, 1.5, False, multiple_max=[int, float, bool])

    def test_zip_on_generator(self):
        self.run_test('def zip_on_generator(n): return zip((i for i in xrange(n)), (i*2 for i in xrange(1,n+1)))', 5, zip_on_generator=[int])

    def test_parallel_enumerate(self):
        self.run_test('def parallel_enumerate(l):\n k = [0]*(len(l) + 1)\n "omp parallel for"\n for i,j in enumerate(l):\n  k[i+1] = j\n return k', list(range(1000)), parallel_enumerate=[[int]])

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
        self.run_test(code, list(range(10)), list(range(10)), generator_sum=[[int],[int]])

    def test_tuple_to_list(self):
        self.run_test('def tuple_to_list(t): return list(t)', (1,2,3), tuple_to_list=[(int, int, int)])

    def test_in_generator(self):
        self.run_test("def in_generator(n):return 1. in (i*i for i in xrange(n))", 5, in_generator=[int])

    def test_tuple_unpacking_in_generator(self):
        code = '''
def foo(l):
    a, b = 1,0
    yield a
    yield b
def tuple_unpacking_in_generator(n):
    f = foo(range(n))
    return 0 in f'''
        self.run_test(code, 10, tuple_unpacking_in_generator=[int])

    def test_loop_tuple_unpacking_in_generator(self):
        code= '''
def foo(l):
    for i,j in enumerate(l):
        yield i,j
def loop_tuple_unpacking_in_generator(n):
    f = foo(range(n))
    return (0,0) in f'''
        self.run_test(code, 10, loop_tuple_unpacking_in_generator=[int])

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
        self.run_test('def nested_comprehension_with_tuple(l): return [[ x+y for x,y in sqrpoints ] for sqrpoints in l]', [[(x,x)]*5 for x in list(range(10))], nested_comprehension_with_tuple=[[[(int,int)]]])

    def test_hashable_tuple(self):
        self.run_test('def hashable_tuple(): return { (1,"e", 2.5) : "r" }', hashable_tuple=[])

    def test_conflicting_names(self):
        self.run_test('def map(): return 5', map=[])

    def test_multiple_compares(self):
        self.run_test('def multiple_compares(x): return 1 < x < 2, 1 < x + 1 < 2', 0.5, multiple_compares=[float])

    def test_default_arg0(self):
        self.run_test('def default_arg0(n=12): return n', default_arg0=[])

    def test_default_arg1(self):
        self.run_test('def default_arg1(m,n=12): return m+n', 1, default_arg1=[int])

    def test_default_arg2(self):
        self.run_test('def default_arg2(n=12): return n', 1, default_arg2=[int])

    def test_default_arg3(self):
        self.run_test('def default_arg3(m,n=12): return m+n', 1, 2, default_arg3=[int,int])

    @skipIf(
        not have_gmp_support(extra_compile_args=TestEnv.PYTHRAN_CXX_FLAGS),
        "Require big int support")
    def test_long_to_float_conversion(self):
        """Check long to float conversion."""
        self.run_test("""
            def long_to_float_conversion(l):
                return float(l)""",
                      123456789123456789120, long_to_float_conversion=[long])

    @skip("lists as zeros parameter are not supported")
    def test_list_as_zeros_parameter(self):
        self.run_test('def list_as_zeros_parameter(n): from numpy import zeros ; return zeros([n,n])', 3, list_as_zeros_parameter=[int])

    def test_add_arrays(self):
        self.run_test('def add_arrays(s): return (s,s) + (s,)', 1, add_arrays=[int])

    def test_tuple_to_tuple(self):
        self.run_test('def tuple_to_tuple(t): return tuple((1, t))',
                      '2',
                      tuple_to_tuple=[str])

    def test_array_to_tuple(self):
        self.run_test('def array_to_tuple(t): return tuple((1, t))',
                      2,
                      array_to_tuple=[int])

    def test_list_to_tuple(self):
        self.run_test('def list_to_tuple(t): return tuple([1, t])',
                      2,
                      list_to_tuple=[int])

    def test_print_intrinsic(self):
        self.run_test('def print_intrinsic(): print(len)',
                      print_intrinsic=[])

    def test_function_redefinition(self):
        code = 'def function_redefinition(x):pass\ndef function_redefinition():pass'
        with self.assertRaises(SyntaxError):
            self.run_test(code, function_redefinition=[])

    def test_global_redefinition(self):
        code = 'foo=0\nfoo=1\ndef global_redefinition(x):pass'
        with self.assertRaises(SyntaxError):
            self.run_test(code, global_redefinition=[])

    def test_invalid_call0(self):
        code = 'def foo(x):pass\ndef invalid_call0(): return foo()'
        with self.assertRaises(SyntaxError):
            self.run_test(code, invalid_call0=[])

    def test_invalid_call1(self):
        code = 'def foo(x=1):pass\ndef invalid_call1(l): return foo(l,l)'
        with self.assertRaises(SyntaxError):
            self.run_test(code, 1, invalid_call1=[int])

    def test_invalid_call2(self):
        code = 'def foo(x):pass\ndef bar():pass\ndef invalid_call2(l): return (foo if l else bar)(l)'
        with self.assertRaises(SyntaxError):
            self.run_test(code, 1, invalid_call2=[int])

#encoding: utf8
from pythran.tests import TestEnv

from unittest import skip, skipIf
import numpy

from pythran.typing import *
from packaging.version import Version

class TestAdvanced(TestEnv):

    def test_generator_enumeration(self):
        code = '''
            def dummy_generator(l):
                for i in l: yield i
            def generator_enumeration(begin, end):
                return [i for i in enumerate(dummy_generator(range(begin,end)))]'''
        self.run_test(code, 2, 10, generator_enumeration=[int, int])

    def test_value_fill_max(self):
        code = '''
def value_fill_max(x, dic):
    key_type = type(next(iter(dic)))
    x = key_type(x)
    return x if x in dic else max(dic.keys())'''
        self.run_test(code, "2", {1:13}, value_fill_max=[str, Dict[int,int]])

    def test_augassign_floordiv(self):
        self.run_test("def augassign_floordiv(i,j): k=i ; k//=j; return k",
                2, 5, augassign_floordiv=[int, int])

    def test_builtin_constructors(self):
        self.run_test("def builtin_constructors(l): return list(map(int,l))",
                [1.5, 2.5], builtin_constructors=[List[float]])

    def test_tuple_sum(self):
        self.run_test("def tuple_sum(tpl): return sum(tpl)", (1, 2, 3.5), tuple_sum=[Tuple[int, int, float]])

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
        self.run_test('def map_on_generator(l): return list(map(float,(x*x for x in l)))', [1,2,3], map_on_generator=[List[int]])

    def test_map2_on_generator(self):
        self.run_test('def map2_on_generator(l): return list(map(lambda x,y : x*y, l, (y for x in l for y in l if x < 1)))', [0,1,2,3], map2_on_generator=[List[int]])

    def test_enumerate_on_generator(self):
        self.run_test("def enumerate_on_generator(n): return list(map(lambda z: z[0], enumerate((y for x in range(n) for y in range(x)))))", 5, enumerate_on_generator=[int])

    def test_enumerate_iterate(self):
        self.run_test("""
                      def enumerate_iterate(n):
                        s = 0
                        for x in enumerate(n):
                          for y in x:
                            s += y
                        return s""",
                      [5, 6],
                      enumerate_iterate=[List[int]])

    def test_max_interface_arity(self):
        self.run_test('def max_interface_arity({0}):pass'.format(', '.join('_'+str(i) for i in range(42))), *list(range(42)), max_interface_arity=[int]*42)

    def test_max_kwonly_key(self):
        self.run_test('def max_kwonly_key(x): return max(x, key=lambda x:-x)',
                      list(range(42)), max_kwonly_key=[List[int]])

    def test_multiple_max(self):
        self.run_test('def multiple_max(i,j,k): return max(i,j,k)', 1, 1.5, False, multiple_max=[int, float, bool])

    def test_zip_on_generator(self):
        self.run_test('def zip_on_generator(n): return list(zip((i for i in range(n)), (i*2 for i in range(1,n+1))))', 5, zip_on_generator=[int])

    def test_parallel_enumerate(self):
        self.run_test('def parallel_enumerate(l):\n k = [0]*(len(l) + 1)\n "omp parallel for"\n for i,j in enumerate(l):\n  k[i+1] = j\n return k', list(range(1000)), parallel_enumerate=[List[int]])

    def test_generator_sum(self):
        code = '''
def generator_sum(l0,l1):
    return sum(x*y for x,y in zip(l0,l1))'''
        self.run_test(code, list(range(10)), list(range(10)), generator_sum=[List[int],List[int]])

    def test_tuple_to_list(self):
        self.run_test('def tuple_to_list(t): return list(t)', (1,2,3), tuple_to_list=[Tuple[int, int, int]])

    def test_in_generator(self):
        self.run_test("def in_generator(n):return 1. in (i*i for i in range(n))", 5, in_generator=[int])

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
        self.run_test('def nested_comprehension_with_tuple(l): return [[ x+y for x,y in sqrpoints ] for sqrpoints in l]', [[(x,x)]*5 for x in list(range(10))], nested_comprehension_with_tuple=[List[List[Tuple[int,int]]]])

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

    def test_default_arg4(self):
        code = '''
            import numpy as np
            def default_arg4(signal,sR):
                N = 30
                F = 0.
                F2 = 22000
                FF = 10
                W = test2(sR, FF, N, F, F2)
                return W

            def test2(sr,N,M=128,F=0.0,F2=0,B=False,No=1):
                W = np.zeros(10)
                return W'''
        self.run_test(code, 1, 2, default_arg4=[int,int])

    def test_default_arg5(self):
        self.run_test('import numpy\ndef default_arg5(m,n=-numpy.inf): return m, n', 1, default_arg5=[int])

    def test_default_arg6(self):
        code = 'from numpy import empty\ndef default_arg6(x=empty(3)):pass'
        with self.assertRaises(SyntaxError):
            self.run_test(code, default_arg6=[])

    def test_default_arg7(self):
        code = '''
import numpy as np

def A(I0, I1=0):
    AA = I1
    A2 = 1000
    if AA:
        A2 //= 2
    self = tuple([[AA],[A2]])
    return self

def B(sRate):
    BB = A(np.empty((sRate, 2)))
    self = tuple([[BB]])
    return self

def default_arg7(n):
    BBB = B(n)
    return BBB'''
        self.run_test(code, 48000, default_arg7=[int])

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

    def test_tuple_to_shape(self):
        self.run_test('def tuple_to_shape(n): from numpy import zeros; return zeros((n,4))', 5, tuple_to_shape=[int])

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

    def test_global_update(self):
        code = 'foo=[]\ndef global_update(x): x.append(1)'
        with self.assertRaises(SyntaxError):
            self.run_test(code, global_update=[])

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

    def test_ellipsis(self):
        code = 'def ellipsis_(x): return x[...,1]'
        with self.assertRaises(SyntaxError):
            self.run_test(code, numpy.ones((3,3)), ellipsis=[NDArray[float,:,:]])

    def test_multiple_lambda(self):
        code = '''
            def multiple_lambda(x):
                g = lambda : x
                return foo(g)
            def foo(t):
                g = lambda : 1
                return t() + g()
            '''
        self.run_test(code, 1, multiple_lambda=[int])

    def test_function_with_non_ascii_docstring(self):
        code = '''
            def function_with_non_ascii_docstring():
                'éàea'
        '''
        self.run_test(code, function_with_non_ascii_docstring=[])

    def test_matmul_operator(self):
        code = 'def matmul_operator(x, y): return x @ y'
        self.run_test(
            code,
            numpy.array([[1., 1.], [2., 2.]]),
            numpy.array([[0., 2.], [1., 3.]]),
            matmul_operator=[NDArray[float, :,:], NDArray[float, :,:]])

    @skipIf(Version(numpy.__version__) <= Version('1.26'), "Not supported upstream")
    def test_imatmul_operator(self):
        code = 'def imatmul_operator(x, y): x @= y; return x'
        self.run_test(
            code,
            numpy.array([[1., 1.], [2., 2.]]),
            numpy.array([[0., 2.], [1., 3.]]),
            imatmul_operator=[NDArray[float, :,:], NDArray[float, :,:]])

    def test_generator_handler_name(self):
        code = '''
            def foo(x):
                for i in range(x):
                    if i > 1:
                        break
                    yield i

            def generator_handler_name(n):
                return list(foo(n))'''
        self.run_test(code,
                      3,
                      generator_handler_name=[int])

    def test_generator_handler_name2(self):
        code = '''
            def foo(x):
                for i in ["1"] * x:
                    if len(i) == 1:
                        break
                    yield i

            def generator_handler_name2(n):
                return list(foo(n))'''
        self.run_test(code,
                      3,
                      generator_handler_name2=[int])

    def test_builtin_slices(self):
        code = '''
            def builtin_slices(x):
                s = slice(2, None, None)
                return (s.start, s.stop, s.step, s,
                        x[s],
                        x[slice(3)],
                        x[slice(1,2)],
                        x[slice(1,10,2)],
                        x[slice(3, None)],
                        x[slice(None,4)],
                        x[slice(None,4, None)])'''
        self.run_test(code,
                      numpy.arange(15),
                      builtin_slices=[NDArray[int,:]])

    def test_slicing_tuple(self):
        code = '''
            def testFunc():
                x=2
                y=3
                z=4
                return x,y,z

            def slicing_tuple(n):
                x,y = testFunc()[0:n]
                return x,y'''
        self.run_test(code, 2, slicing_tuple=[int])

    def test_static_list0(self):
        code = '''
            def static_list0(n):
                s = list(n)
                s[1] = 1
                return tuple(s)'''
        self.run_test(code, (2, 2), static_list0=[Tuple[int, int]])

    def test_static_list1(self):
        code = '''
            def foo(x, y):
                return len(y) + x
            def static_list1(n):
                s = list(n)
                s[1] = foo(len(s), s)
                return tuple(s)'''
        self.run_test(code, (2, 2), static_list1=[Tuple[int, int]])

    def test_static_list2(self):
        code = '''
            def static_list2(t0, t1):
                s = [slice(x, y, 1) for x,y in zip(t0, t1)]
                return tuple(s)'''
        self.run_test(code, (2, 2), (3,3), static_list2=[Tuple[int, int], Tuple[int, int]])

    def test_static_list3(self):
        code = '''
            import numpy as np

            def StridedSlice(x,begins, ends, strides):
                slices = tuple([slice(b, e if e else None, s) for b, e, s in zip(begins,ends, strides)])
                return x[slices]

            def static_list3(x):
                return StridedSlice(x,[0,2,3], [5,0,7], [1,1,1])'''
        self.run_test(code, numpy.arange(1000).reshape(10,10,10), static_list3=[NDArray[int, :,:,:]])

    def test_static_list4(self):
        code = '''
            import numpy as np

            def StridedSlice(x,begins, ends, strides):
                slices = tuple([slice(b, e if e else None, s) for b, e, s in zip(begins,ends, strides)])
                return x[slices]

            def static_list4(x):
                return StridedSlice(x,np.array([0,2,3]), np.array([5,0,7]), [1,1,1])'''
        self.run_test(code, numpy.arange(1000).reshape(10,10,10), static_list4=[NDArray[int, :,:,:]])

    def test_tuple_slicing0(self):
        code = '''
            def tuple_slicing0(n):
                X = tuple([[1,2,3,4],[1,2,3,4]])
                B = X[0:1]
                B[0][3]=n
                return B, X'''
        self.run_test(code, 20, tuple_slicing0=[int])

    def test_tuple_slicing1(self):
        code = '''
            def tuple_slicing1(n):
                X = tuple([[1,2,3,4],[1,2,3,4], [5,6,7,8]])
                B = X[0::2]
                B[0][3]=n
                return B, X'''
        self.run_test(code, 20, tuple_slicing1=[int])

    def test_reserved_identifier0(self):
        code = '''
        def reserved_identifier0(x):
            if x == 1:
                case = 1
            else:
                case = 2
            return case'''
        self.run_test(code, 3, reserved_identifier0=[int])

    def test_global_effects_partial0(self):
        code = '''
g = [1, 2]

def return_partial(x):
    def partial(_):
        return x

    return partial

def call_partial(fct):
    return return_partial(fct)

all_commands = call_partial(g)

def global_effects_partial0(l):
    return all_commands(l)'''
        self.run_test(code, 3, global_effects_partial0=[int])

    def test_dynamic_tuple_compare(self):
        code = '''
           def dynamic_tuple_compare(x, y):
               y = tuple(y)
               x = tuple(x)
               return x < y, x <= y, x > y, x >= y'''
        self.run_test(code, [1, 2], [1, 3], dynamic_tuple_compare=[List[int], List[int]])

    def test_annotations(self):
        code  = '''
        import numpy as np
        def annotations(x: np.ndarray) -> np.ndarray:
            return x'''
        self.run_test(code, numpy.ones(1), annotations=[NDArray[float, :]])

    def test_flat_size_empty_container(self):
        code = '''
def flat_size_empty_container(x):
    import numpy as np
    y = [[1] * x]
    return np.flatnonzero(y)'''
        self.run_test(code, 0, flat_size_empty_container=[int])

    def test_tuple_indexable_container(self):
        code = """
import numpy as np
def A_I():
    s = np.array([0.70817816, 0.68863678], dtype=np.float64)
    m = np.array([-1.11312199, -0.99629629], dtype=np.float64)
    self = tuple([100, s, m])
    return self

def A_F1(self, Input_x):
    Input_x = (Input_x - self[2]) / self[1]
    return Input_x

def B_I():
    self = tuple([0.0, 0])
    return self


def C_I(sRate):
    a = A_I()
    b = B_I()
    self = tuple([0, sRate, 0, a, b])
    return self


def C_Test(self):
    F = np.zeros((1, 1, 1))
    ret = A_F1(self[3], F.astype(np.float32))
    return ret

def tuple_indexable_container(n):
    TD = C_I(n)
    return C_Test(TD)"""
        self.run_test(code, 44100, tuple_indexable_container=[int])

    def test_filter_enumerate(self):
        code = 'def filt_enum(l): return [p for _,p in enumerate(l) if p%2]'
        self.run_test(code, [10, 11, 12, 13],
                      filt_enum=[List[int]])

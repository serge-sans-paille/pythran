from test_env import TestEnv

class TestBase(TestEnv):

    def test_pass(self):
        self.run_test("def pass_(a):pass", 1, pass_=[int])

    def test_empty_return(self):
        self.run_test("def empty_return(a,b,c):return", 1,1,True, empty_return=[int,float,bool])

    def test_identity(self):
        self.run_test("def identity(a): return a", 1.5, identity=[float])

    def test_compare(self):
        self.run_test("def compare(a,b,c):\n if a <b < c: return a\n else: return b != c", 1,2,3, compare=[int, int, int])

    def test_arithmetic(self):
        self.run_test("def arithmetic(a,b,c): return a+b*c", 1,2,3.3, arithmetic=[int,int, float])

    def test_boolop(self):
        self.run_test("def boolop(a,b,c): return a and b or c", True, True, False, boolop=[bool,bool, bool])

    def test_operator(self):
        self.run_test("def operator_(a,b,c): return (a+b-b*a/(a%b)**(a<<a>>b|b^a&a/b)//c)",1,2,1.5, operator_=[int,int, float])

    def test_unaryop(self):
        self.run_test("def unaryop(a): return not(~(+(-a)))", 1, unaryop=[int])

    def test_expression(self):
        self.run_test("def expression(a,b,c): a+b*c", 1,2,3.3, expression=[int,int, float])

    def test_recursion(self):
        code="""
def fibo(n): return n if n <2 else fibo(n-1) + fibo(n-2)
def fibo2(n): return fibo2(n-1) + fibo2(n-2) if n > 1 else n
"""
        self.run_test(code, 4, fibo=[int], fibo2=[float])

    def test_manual_list_comprehension(self):
        self.run_test("def f(l):\n ll=list()\n for k in l:\n  ll+=[k]\n return ll\ndef manual_list_comprehension(l): return f(l)", [1,2,3], manual_list_comprehension=[[int]])
 
    def test_list_comprehension(self):
        self.run_test("def list_comprehension(l): return [ x*x for x in l ]", [1,2,3], list_comprehension=[[int]])
 
    def test_dict_comprehension(self):
        self.run_test("def dict_comprehension(l): return { i: 1 for i in l if len(i)>1 }", ["1","12","123"], dict_comprehension=[[str]])
 
    def test_filtered_list_comprehension(self):
        self.run_test("def filtered_list_comprehension(l): return [ x*x for x in l if x > 1 if x <10]", [1,2,3], filtered_list_comprehension=[[int]])

    def test_multilist_comprehension(self):
        self.run_test("def multilist_comprehension(l): return [ x*y for x in l for y in l]", [1,2,3], multilist_comprehension=[[int]])

    def test_zipped_list_comprehension(self):
        self.run_test("def zipped_list_comprehension(l): return [ x*y for x,y in zip(l,l) ]", [1,2,3], zipped_list_comprehension=[[int]])

    def test_zip(self):
        self.run_test("def zip_(l0,l1): return zip(l0,l1)", [1,2,3],["one", "two", "three"], zip_=[[int], [str]])

    def test_multizip(self):
        self.run_test("def multizip(l0,l1): return zip(l0,zip(l0,l1))", [1,2,3],["one", "two", "three"], multizip=[[int], [str]])

    def test_reduce(self):
        self.run_test("def reduce_(l): return reduce(lambda x,y:x+y, l)", [0,1.1,2.2,3.3], reduce_=[[float]])

    def test_another_reduce(self):
        self.run_test("def another_reduce(l0,l1): return reduce(lambda x,(y,z):x+y+z, zip(l0, l1),0)", [0.4,1.4,2.4,3.4], [0,1.1,2.2,3.3], another_reduce=[[float],[float]])

    def test_sum(self):
        self.run_test("def sum_(l): return sum( l)", [0,1.1,2.2,3.3], sum_=[[float]])

    def test_multisum(self):
        self.run_test("def multisum(l0,l1): return sum(l0)+sum(l1)", [0,1.1,2.2,3.3],[1,2,3], multisum=[[float],[int]])

    def test_max(self):
        self.run_test("def max_(l):return max(l)", [ 1.1, 2.2 ], max_=[[float]])

    def test_multimax(self):
        self.run_test("def multimax(l,v):return max(v,max(l))", [ 1.1, 2.2 ], 3, multimax=[[float],int])

    def test_min(self):
        self.run_test("def min_(l):return min(l)", [ 1.1, 2.2 ], min_=[[float]])

    def test_multimin(self):
        self.run_test("def multimin(l,v):return min(v,min(l))", [ 1.1, 2.2 ], 3, multimin=[[float],int])

    def test_map_none(self):
        self.run_test("def map_none(l0): return map(None, l0)", [0,1,2], map_none=[[int]])

    def test_map_none2(self):
        self.run_test("def map_none2(l0): return map(None, l0, l0)", [0,1,2], map_none2=[[int]])

    def test_map(self):
        self.run_test("def map_(l0, l1,v): return map(lambda x,y:x*v+y, l0, l1)", [0,1,2], [0,1.1,2.2], 2, map_=[[int], [float], int])
    
    def test_multimap(self):
        self.run_test("def multimap(l0, l1,v): return map(lambda x,y:x*v+y, l0, map(lambda z:z+1,l1))", [0,1,2], [0,1.1,2.2], 2, multimap=[[int], [float], int])

    def test_intrinsic_map(self):
        self.run_test("def intrinsic_map(l): return map(max,l)",[[0,1,2],[2,0,1]], intrinsic_map=[[[int]]])

    def test_range1(self):
        self.run_test("def range1_(e): return range(e)", 3, range1_=[int])
    
    def test_range2(self):
        self.run_test("def range2_(b,e): return range(b,e)", 1, 3, range2_=[int,int])
    
    def test_range3(self):
        self.run_test("def range3_(b,e,s): return range(b,e,s)", 8,3,-2, range3_=[int,int,int])
    
    def test_range4(self):
        self.run_test("def range4_(b,e,s): return range(b,e,s)", 8,2,-2, range4_=[int,int,int])
    
    def test_range5(self):
        self.run_test("def range5_(b,e,s): return range(b,e,s)", 3,8,1, range5_=[int,int,int])

    def test_range6(self):
        self.run_test("def range6_(b,e,s): return range(b,e,s)", 3,8,3, range6_=[int,int,int])

    def test_range7(self):
        self.run_test("def range7_(b,e,s): return range(b,e,s)", 3,9,3, range7_=[int,int,int])

    def test_rrange1(self):
        self.run_test("def rrange1_(e): return list(reversed(range(e)))", 3, rrange1_=[int])
    
    def test_rrange2(self):
        self.run_test("def rrange2_(b,e): return set(reversed(range(b,e)))", 1, 3, rrange2_=[int,int])
    
    def test_rrange3(self):
        self.run_test("def rrange3_(b,e,s): return list(reversed(range(b,e,s)))", 8,3,-2, rrange3_=[int,int,int])
    
    def test_rrange4(self):
        self.run_test("def rrange4_(b,e,s): return set(reversed(range(b,e,s)))", 8,2,-2, rrange4_=[int,int,int])
    
    def test_rrange5(self):
        self.run_test("def rrange5_(b,e,s): return list(reversed(range(b,e,s)))", 3,8,1, rrange5_=[int,int,int])

    def test_rrange6(self):
        self.run_test("def rrange6_(b,e,s): return set(reversed(range(b,e,s)))", 3,8,3, rrange6_=[int,int,int])

    def test_rrange7(self):
        self.run_test("def rrange7_(b,e,s): return list(reversed(range(b,e,s)))", 3,9,3, rrange7_=[int,int,int])

    def test_multirange(self):
        self.run_test("def multirange(i): return map(lambda x,y:y*x/2, range(1,i), range(i,1,-1))", 3, multirange=[int])
    
    def test_xrange1(self):
        self.run_test("def xrange1_(e): return list(xrange(e))", 3, xrange1_=[int])
    
    def test_xrange2(self):
        self.run_test("def xrange2_(b,e): return list(xrange(b,e))", 1, 3, xrange2_=[int,int])
    
    def test_xrange3(self):
        self.run_test("def xrange3_(b,e,s): return list(xrange(b,e,s))", 8,3,-2, xrange3_=[int,int,int])
    
    def test_xrange4(self):
        self.run_test("def xrange4_(b,e,s): return list(xrange(b,e,s))", 3,8,1, xrange4_=[int,int,int])

    def test_xrange5(self):
        self.run_test("def xrange5_(e): return max(xrange(e))", 3, xrange5_=[int])

    def test_multixrange(self):
        self.run_test("def multixrange(i): return map(lambda x,y:y*x/2, xrange(1,i), xrange(i,1,-1))", 3, multixrange=[int])
    
    def test_print(self):
        self.run_test("def print_(a,b,c,d): print a,b,c,d,'e',1.5,", [1,2,3.1],3,True, "d", print_=[[float], int, bool, str])

    def test_assign(self):
        self.run_test("def assign(a): b=2*a ; return b", 1, assign=[int])

    def test_multiassign(self):
        self.run_test("def multiassign(a):\n c=b=a\n return c", [1], multiassign=[[int]])

    def test_list(self):
        self.run_test("def list_(a): b=2*a;c=b/2;return max(c,b)", 1, list_=[int])

    def test_if(self):
        self.run_test("def if_(a,b):\n if a>b: return a\n else: return b", 1, 1.1, if_=[int, float])

    def test_while(self):
        self.run_test("def while_(a):\n while(a>0): a-=1\n return a", 8, while_=[int])

    def test_for(self):
        self.run_test("def for_(l):\n s=0\n for i in l:\n  s+=i\n return s", [0,1,2], for_=[[float]])

    def test_declarations(self):
        code = """
def declarations():
    if True:
        a=0
        while a <3:
            b = 1
            a = b + a
    else:
        a=1
    return a + b
"""
        self.run_test(code, declarations=[])

    def test_lambda(self):
        code = """
def lambda_():
    l=lambda x,y: x+y
    return l(1,2) + l(1.2,2)
"""
        self.run_test(code, lambda_=[])

    def test_multidef1(self):
        self.run_test("def def10(): pass\ndef def11(): def10()", def11=[])

    def test_multidef2(self):
        self.run_test("def def21(): def20()\ndef def20(): pass", def21=[])
        
    def test_multidef3(self):
        self.run_test("def def31(): return 1\ndef def30(): return def31()", def31=[])
        
    def test_multidef4(self):
       self.run_test("def def41(): return def40()\ndef def40(): return 1", def41=[])
        
    def test_tuple(self):
        self.run_test("def tuple_(t): return t[0]+t[1]", (0,1), tuple_=[(int, int)])

    def test_nested_list_comprehension(self):
        self.run_test("def nested_list_comprehension(): return [ [ x+y for x in xrange(10) ] for y in xrange(20) ]", nested_list_comprehension=[])

    def test_delete(self):
        self.run_test("def delete_(v): del v", 1, delete_=[int])

    def test_continue(self):
        self.run_test("def continue_():\n for i in xrange(3):continue\n return i", continue_=[])

    def test_break(self):
        self.run_test("def break_():\n for i in xrange(3):break\n return i", break_=[])

    def test_assert(self):
        self.run_test("def assert_(i): assert i > 0", 1, assert_=[int])

    def test_assert_with_msg(self):
        self.run_test("def assert_with_msg(i): assert i > 0, 'hell yeah'", 1, assert_with_msg=[int])

    def test_import_from(self):
        self.run_test("def import_from(): from math import cos ; return cos(1.)", import_from=[])

    def test_len(self):
        self.run_test("def len_(i,j,k): return len(i)+len(j)+len(k)", "youpi", [1,2],[], len_=[str,[int], [float]])

    def test_in_string(self):
        self.run_test("def in_string(i,j): return i in j", "yo", "youpi", in_string=[str,str])

    def test_not_in_string(self):
        self.run_test("def not_in_string(i,j): return i not in j", "yo", "youpi", not_in_string=[str,str])

    def test_in_list(self):
        self.run_test("def in_list(i,j): return i in j", 1, [1,2,3], in_list=[int,[int]])

    def test_not_in_list(self):
        self.run_test("def not_in_list(i,j): return i not in j", False, [True, True, True], not_in_list=[bool,[bool]])

    def test_subscript(self):
        self.run_test("def subscript(l,i): l[0]=l[0]+l[i]", [1], 0, subscript=[[int], int])

    def test_nested_lists(self):
        self.run_test("def nested_lists(l,i): return l[0][i]", [[1]], 0, nested_lists=[[[int]],int])

    def test_nested_tuples(self):
        self.run_test("def nested_tuples(l,i): return l[i][1]", [(0.1,1,)], 0, nested_tuples=[[(float,int)],int])

    def test_return_empty_list(self):
        self.run_test("def return_empty_list(): return list()", return_empty_list=[])

    def test_empty_list(self):
        self.run_test("def empty_list(): a=[]", empty_list=[])

    def test_multi_list(self):
        self.run_test("def multi_list(): return [[[2.0],[1,2,3]],[[2.0],[1,2,3]]]", multi_list=[])

    def test_empty_tuple(self):
        self.run_test("def empty_tuple(): a=()", empty_tuple=[])

    def test_multi_tuple(self):
        self.run_test("def multi_tuple(): return (1,('e',2.0),[1,2,3])", multi_tuple=[])

    def test_augmented_assign(self):
        self.run_test("def augmented_assign():\n a=0\n a+=1.5\n return a", augmented_assign=[])

    def test_augmented_list_assign(self):
        self.run_test("def augmented_list_assign(l):\n a=list()\n a+=l\n return a", [1,2], augmented_list_assign=[[int]])

    def test_initialization_list(self):
        self.run_test("def initialization_list(): return [1, 2.3]", initialization_list=[])

    def test_multiple_assign(self):
        self.run_test("def multiple_assign():\n a=0 ; b = a\n a=1.5\n return a, b", multiple_assign=[])

    def test_multiple_return1(self):
        self.run_test("def multiple_return1(a):\n if True:return 1\n else:\n  return a", 2,  multiple_return1=[int])

    def test_multiple_return2(self):
        self.run_test("def multiple_return2(a):\n if True:return 1\n else:\n  b=a\n  return b", 2,  multiple_return2=[int])

    def test_multiple_return3(self):
        self.run_test("def multiple_return3(a):\n if True:return 1\n else:\n  b=a\n  return a+b", 2,  multiple_return3=[int])

    def test_id(self):
        self.run_test("def id_(a):\n c=a\n return id(a)==id(c)", [1,2,3], id_=[[int]])

    def test_delayed_max(self):
        self.run_test("def delayed_max(a,b,c):\n m=max\n return m(a,b) + m(b,c)", 1, 2, 3.5, delayed_max=[int, int, float])

    def test_slicing(self):
        self.run_test("def slicing(l): return l[0:1] + l[:-1]",[1,2,3,4], slicing=[[int]])

    def test_not_so_deep_recursive_calls(self):
        code="""
def a(i): return b(i)
def b(i): return b(a(i-1)) if i else i
def not_so_deep_recursive_calls(i):return b(i)"""
        self.run_test(code,3, not_so_deep_recursive_calls=[int])

    def test_deep_recursive_calls(self):
        code="""
def a(i): return a(i-1) + b(i) if i else i
def b(i): return b(i-1)+a(i-1) if i else c(i-1) if i+1 else i
def c(i): return c(i-1) if i>0 else 1
def deep_recursive_calls(i):a(i)+b(i) +c(i)"""
        self.run_test(code,3, deep_recursive_calls=[int])

    def test_dummy_nested_def(self):
        code="""
def dummy_nested_def(a):
    def the_dummy_nested_def(b):return b
    return the_dummy_nested_def(a)"""
        self.run_test(code,3, dummy_nested_def=[int])

    def test_nested_def(self):
        code="""
def nested_def(a):
    def the_nested_def(b):return a+b
    return the_nested_def(3)"""
        self.run_test(code,3, nested_def=[int])

    def test_none(self):
        self.run_test("def none_(l):\n if len(l)==0: return\n else: return l", [], none_=[[int]])

    def test_import(self):
        self.run_test("import math\ndef import_(): return math.cos(1)", import_=[])

    def test_local_import(self):
        self.run_test("def local_import_(): import math;return math.cos(1)", local_import_=[])

    def test_abs(self):
        self.run_test("def abs_(a): return abs(a)", -1.3, abs_=[float])

    def test_all(self):
        self.run_test("def all_(a): return all(a)", [True, False, True], all_=[[bool]])

    def test_any(self):
        self.run_test("def any_(a): return any(a)", [0, 1, 2], any_=[[int]])

    def test_bin(self):
        self.run_test("def bin_(a): return bin(a)", 54321, bin_=[int])

    def test_chr(self):
        self.run_test("def chr_(a): return chr(a)", 42, chr_=[int])

    def test_cmp(self):
        self.run_test("def cmp_(a,b): return cmp(a,b)", 1, 4.5, cmp_=[int, float])

    def test_complex(self):
        self.run_test("def complex_(a): return complex(a)", 1, complex_=[int])

    def test_divmod(self):
        self.run_test("def divmod_(a,b): return divmod(a,b)", 5, 2, divmod_=[int,int])

    def test_enumerate(self):
        self.run_test("def enumerate_(l): return [ x for x in enumerate(l) ]", ["a","b","c"], enumerate_=[[str]])

    def test_enumerat2(self):
        self.run_test("def enumerate2_(l): return [ x for x in enumerate(l, 3) ]", ["a","b","c"], enumerate2_=[[str]])

    def test_filter(self):
        self.run_test("def filter_(l): return filter(lambda x:x%2, l)", [1,2,3], filter_=[[int]])

    def test_hex(self):
        self.run_test("def hex_(a): return hex(a)", 18, hex_=[int])

    def test_oct(self):
        self.run_test("def oct_(a): return oct(a)", 18, oct_=[int])

    def test_pow(self):
        self.run_test("def pow_(a): return pow(a,15)", 18, pow_=[int])

    def test_reversed(self):
        self.run_test("def reversed_(l): return [x for x in reversed(l)]", [1,2,3], reversed_=[[int]])

    def test_round(self):
        self.run_test("def round_(v): return round(v) + round(v,2)", 0.1234, round_=[float])

    def test_sorted(self):
        self.run_test("def sorted_(l): return [x for x in sorted(l)]", [1,2,3], sorted_=[[int]])

    def test_str(self):
        self.run_test("def str_(l): return str(l)", [1,2,3.5], str_=[[float]])

    def test_append(self):
        self.run_test("def append(): l=[] ; l.append(1) ; return l", append=[])

    def test_append_in_call(self):
        self.run_test("def call(l):l.append(1.)\ndef append_in_call(): l=[] ; call(l) ; l.append(1) ; return l", append_in_call=[])

    def test_complex_append_in_call(self):
        code="""
def foo(a,b):
	i = 3*b
	if not i in a:
		a.append(i)
def complex_append_in_call(l1,l2):
	b = []
	for x in l1:
		if not x in l2:
			foo(b,x)"""
        self.run_test(code, [1,2,3],[2],complex_append_in_call=[[int],[int]])

    def test_complex_number(self):
        code="""
def complex_number():
    c=complex(0,1)
    return c.real + c.imag"""
        self.run_test(code, complex_number=[])

    def test_raise(self):
        self.run_test("def raise_():\n raise RuntimeError('pof')", raise_=[])

    def test_complex_number_serialization(self):
        self.run_test("def complex_number_serialization(l): return [x+y for x in l for y in l]", [complex(1,0), complex(1,0)], complex_number_serialization=[[complex]])

    def test_complex_conj(self):
        self.run_test("def complex_conjugate(c): return c.conjugate()", complex(0,1), complex_conjugate=[complex])

    def test_cast(self):
        self.run_test("def cast(i,f): return float(i)+int(f)", 1,1.5, cast=[int, float])

    def test_subscript_assignment(self):
        code="""
def foo(A):
    A[0]=1.5
def subscript_assignment ():
    a=range(1)
    foo(a)
    return a[0]"""
        self.run_test(code,subscript_assignment=[])

    def test_conflicting_keywords(self):
        code="""
def export(template):
    return [ new*new for new in template ]"""
        self.run_test(code, [1], export=[[int]])

    def test_forelse(self):
        code="""
def forelse():
    l=0
    for i in range(10):
        if i > 3:break
        for j in range(10):
            if j > 5:break
            l+=1
        else:
            l*=2
    else:
        l*=3
    return l"""
        self.run_test(code, forelse=[])

    def test_tuples(self):
        self.run_test("def tuples(n): return ((1,2.,'e') , [ x for x in tuple([1,2,n])] )", 1, tuples=[int])

    def test_long_assign(self):
        self.run_test("def _long_assign():\n b=10L\n c = b + 10\n return c", _long_assign=[])

    def test_long(self):
        self.run_test("def _long(a): return a+34",111111111111111L, _long=[long])

    def test_reversed_slice(self):
        self.run_test("def reversed_slice(l): return l[::-2]", [0,1,2,3,4], reversed_slice=[[int]])

    def test_shadow_parameters(self):
        code="""
def shadow_parameters(l):
    if False:l=None
    return l"""
        self.run_test(code, [1], shadow_parameters=[[int]])

    def test_yielder(self):
        code="""
def iyielder(i):
    for k in xrange(i+18):
        yield k
    return

def yielder():
    f=iyielder(1)
    b=f.next()
    return [i*i for i in f]"""
        self.run_test(code, yielder=[])

    def test_yield_with_default_param(self):
        code="""
def foo(a=1000):
    for i in xrange(10):
        yield a

def yield_param():
    it = foo()
    return [i for i in it]"""
        self.run_test(code, yield_param=[])

    def test_set(self):
        code="""
def set_(a,b):
    S=set()
    S.add(a)
    S.add(b)
    return len(S)"""
        self.run_test(code, 1,2,set_=[int, int])
    def test_in_set(self):
        code="""
def in_set(a):
    S=set()
    S.add(a)
    return a in S"""
        self.run_test(code, 1.5, in_set=[float])

    def test_return_set(self):
        self.run_test("def return_set(l): return set(l)", [1,2,3,3], return_set=[[int]])

    def test_import_set(self):
        self.run_test("def import_set(l): l.add(1) ; return l", {0,2}, import_set=[{int}])

    def test_raw_set(self):
        self.run_test("def raw_set(): return { 1, 1., 2 }", raw_set=[])

    def test_iter_set(self):
        self.run_test("def iter_set(s):\n l=0\n for k in s: l+=1\n return l", { "a", "b", "c" } , iter_set=[{str}])

    def test_set_comprehension(self):
        self.run_test("def set_comprehension(l): return { i*i for i in l }", [1 , 2, 1, 3], set_comprehension=[[int]])

    def test_slicer(self):
        code="""
def slicer(l):
    l[2:5]=[1,2]
    return l"""
        self.run_test(code,[1,2,3,4,5,6,7,8,9], slicer=[[int]])

    def test_generator_expression(self):
        code="""
def generator_expression(l):
    return sum(x for x in l if x == 1)"""
        self.run_test(code,[1,1,1,2], generator_expression=[[int]])

    def test_default_parameters(self):
        code="""
def dp(b,a=1.2):
    return a

def default_parameters():
    a=1
    c=dp(a)
    d=dp(5,"yeah")
    return str(c)+d"""
        self.run_test(code, default_parameters=[])

    def test_import_as(self):
        code="""
from math import cos as COS
def import_as():
    x=.42
    import math as MATH
    return MATH.sin(x)**2 + COS(x)**2"""
        self.run_test(code, import_as=[])

    def test_tuple_unpacking(self):
        self.run_test("def tuple_unpacking(t): a,b = t ; return a, b", (1,"e"), tuple_unpacking=[(int, str)])

    def test_list_unpacking(self):
        self.run_test("def list_unpacking(t): [a,b] = t ; return a, b", (1,2), list_unpacking=[(int, int)])

    def test_recursive_attr(self):
        self.run_test("def recursive_attr(): return {1,2,3}.union({1,2}).union({5})", recursive_attr=[])

    def test_range_negative_step(self):
        self.run_test("""def range_negative_step(n):
        o=[]
        for i in xrange(n, 0, -1): o.append(i)
        return o""", 10, range_negative_step=[int])

    def test_reversed_range_negative_step(self):
        self.run_test("""def reversed_range_negative_step(n):
        o=[]
        for i in reversed(xrange(n, 0, -1)): o.append(i)
        return o""", 10, reversed_range_negative_step=[int])

    def test_update_empty_list(self):
        self.run_test('''
def update_empty_list(l):
    p = list()
    return p + l[:1]''', range(5), update_empty_list=[[int]])

    def test_update_list_with_slice(self):
        self.run_test('''
def update_list_with_slice(l):
    p = list()
    for i in xrange(10):
        p += l[:1]
    return p,i''', range(5), update_list_with_slice=[[int]])

    def test_add_slice_to_list(self):
        self.run_test('''
def add_slice_to_list(l):
    p = list()
    for i in xrange(10):
        p = p + l[:1]
    return p,i''', range(5), add_slice_to_list=[[int]])

    def test_bool_(self):
        self.run_test("def _bool(d): return bool(d)", 3, _bool=[int])

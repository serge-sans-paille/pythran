from pythran import python_interface
import unittest

class TestBase(unittest.TestCase):

    def run_test(self, code, *params, **interface):
        for name in sorted(interface.keys()):
            mod = python_interface("test_"+name, code, **interface)
            res = getattr(mod,name)(*params)
            print res

    def test_pass(self):
        self.run_test("def pass_(a):pass", 1, pass_=("int"))

    def test_empty_return(self):
        self.run_test("def empty_return(a,b,c):return", 1,1,True, empty_return=("int","float","bool"))

    def test_identity(self):
        self.run_test("def identity(a): return a", 1.5, identity=('float'))


    def test_arithmetic(self):
        self.run_test("def arithmetic(a,b,c): return a+b*c", 1,2,3.3, arithmetic=('int','int', 'float'))

    def test_expression(self):
        self.run_test("def expression(a,b,c): a+b*c", 1,2,3.3, expression=('int','int', 'float'))

    def test_recursion(self):
        code="""
def fibo(n): return n if n <2 else fibo(n-1) + fibo(n-2)
def fibo2(n): return fibo2(n-1) + fibo2(n-2) if n > 1 else n
"""
        self.run_test(code, 4, fibo=('int'), fibo2=('float'))

    def test_list_comprehension(self):
        self.run_test("def list_comprehension(l): return [ x*x for x in l ]", [1,2,3], list_comprehension=("int list"))

    def test_zip(self):
        self.run_test("def zip_(l0,l1): return zip(l0,l1)", [1,2,3],["one", "two", "three"], zip_=("int list", "string list"))

    def test_multizip(self):
        self.run_test("def multizip(l0,l1): return zip(l0,zip(l0,l1))", [1,2,3],["one", "two", "three"], multizip=("int list", "string list"))

    def test_reduce(self):
        self.run_test("def reduce_(l): return reduce(lambda x,y:x+y, l)", [0,1.1,2.2,3.3], reduce_=("float list"))

    def test_sum(self):
        self.run_test("def sum_(l): return sum( l)", [0,1.1,2.2,3.3], sum_=("float list"))

    def test_multisum(self):
        self.run_test("def multisum(l0,l1): return sum(l0)+sum(l1)", [0,1.1,2.2,3.3],[True,False,True], multisum=("float list","bool list"))

    def test_max(self):
        self.run_test("def max_(l):return max(l)", [ 1.1, 2.2 ], max_=("float list"))

    def test_multimax(self):
        self.run_test("def multimax(l,v):return max(v,max(l))", [ 1.1, 2.2 ], 3, multimax=("float list","int"))

    def test_min(self):
        self.run_test("def min_(l):return min(l)", [ 1.1, 2.2 ], min_=("float list"))

    def test_multimin(self):
        self.run_test("def multimin(l,v):return min(v,min(l))", [ 1.1, 2.2 ], 3, multimin=("float list","int"))

    def test_map(self):
        self.run_test("def map_(l0, l1,v): return map(lambda x,y:x*v+y, l0, l1)", [0,1,2], [0,1.1,2.2], 2, map_=("int list", "float list", "int"))
    
    def test_multimap(self):
        self.run_test("def multimap(l0, l1,v): return map(lambda x,y:x*v+y, l0, map(lambda z:z+1,l1))", [0,1,2], [0,1.1,2.2], 2, multimap=("int list", "float list", "int"))

    def test_range1(self):
        self.run_test("def range1_(e): return range(e)", 3, range1_=("int"))
    
    def test_range2(self):
        self.run_test("def range2_(b,e): return range(b,e)", 1, 3, range2_=("int","int"))
    
    def test_range3(self):
        self.run_test("def range3_(b,e,s): return range(b,e,s)", 8,3,-2, range3_=("int","int","int"))
    
    def test_range4(self):
        self.run_test("def range4_(b,e,s): return range(b,e,s)", 3,8,1, range4_=("int","int","int"))

    def test_multirange(self):
        self.run_test("def multirange(i): return map(lambda x,y:y*x/2, range(1,i), range(i,1,-1))", 3, multirange=("int"))
    
    def test_xrange1(self):
        self.run_test("def xrange1_(e): return xrange(e)", 3, xrange1_=("int"))
    
    def test_xrange2(self):
        self.run_test("def xrange2_(b,e): return xrange(b,e)", 1, 3, xrange2_=("int","int"))
    
    def test_xrange3(self):
        self.run_test("def xrange3_(b,e,s): return xrange(b,e,s)", 8,3,-2, xrange3_=("int","int","int"))
    
    def test_xrange4(self):
        self.run_test("def xrange4_(b,e,s): return xrange(b,e,s)", 3,8,1, xrange4_=("int","int","int"))

    def test_multixrange(self):
        self.run_test("def multixrange(i): return map(lambda x,y:y*x/2, xrange(1,i), xrange(i,1,-1))", 3, multixrange=("int"))
    
    def test_print(self):
        self.run_test("def print_(a,b,c,d): print a,b,c,d,'e',1.5,", [1,2,3.1],3,True, "d", print_=("float list", "int", "bool", "string"))

    def test_sequence(self):
        self.run_test("def sequence_(a): b=2*a;c=b/2;return max(c,b)", 1, sequence_=("int"))

    def test_if(self):
        self.run_test("def if_(a,b):\n if a>b: return a\n else: return b", 1, 1.1, if_=("int", "float"))

    def test_while(self):
        self.run_test("def while_(a):\n while(a>0): a-=1\n else: a=0\n return a", 8, while_=("int"))

    def test_for(self):
        self.run_test("def for_(l):\n s=0\n for i in l:\n  s+=i\n return s", [0,1,2], for_=("float list"))

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
        self.run_test(code, declarations=())
    def test_lambda(self):
        code = """
def lambda_():
    l=lambda x,y: x+y
    return l(1,2) + l(1.2,2)
"""
        self.run_test(code, lambda_=())

    def test_multidef1(self):
        self.run_test("def def10(): pass\ndef def11(): def10()", def11=())

    def test_multidef2(self):
        self.run_test("def def21(): def20()\ndef def20(): pass", def21=())
        
    def test_multidef3(self):
        self.run_test("def def31(): return 1\ndef def30(): return def31()", def31=())
        
    def test_multidef4(self):
        self.run_test("def def41(): return def40()\ndef def40(): return 1", def41=())
        

if __name__ == '__main__':
        unittest.main()

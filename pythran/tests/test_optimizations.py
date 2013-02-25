from test_env import TestEnv


class TestBase(TestEnv):

    def test_genexp(self):
        self.run_test("def test_genexp(n): return sum((x*x for x in xrange(n)))", 5, test_genexp=[int])

    def test_genexp_2d(self):
        self.run_test("def test_genexp_2d(n1, n2): return sum((x*y for x in xrange(n1) for y in xrange(n2)))", 2, 3, test_genexp_2d=[int, int])

    def test_genexp_if(self):
        self.run_test("def test_genexp_if(n): return sum((x*x for x in xrange(n) if x < 4))", 5, test_genexp_if=[int])

    def test_genexp_mixedif(self):
        self.run_test("def test_genexp_mixedif(m, n): return sum((x*y for x in xrange(m) for y in xrange(n) if x < 4))", 2, 3, test_genexp_mixedif=[int, int])

    def test_genexp_triangular(self):
        self.run_test("def test_genexp_triangular(n): return sum((x*y for x in xrange(n) for y in xrange(x)))", 2, test_genexp_triangular=[int])

    def test_aliased_readonce(self):
        self.run_test("""
def foo(f,l):
    return map(f,l[1:])
def alias_readonce(n): 
    map = foo
    return map(lambda (x,y): x*y < 50, zip(xrange(n), xrange(n)))
""", 10, alias_readonce=[int]) 

    def test_replace_aliased_map(self):
        self.run_test("""
def alias_replaced(n): 
    map = filter
    return list(map(lambda x : x < 5, xrange(n)))
""", 10, alias_replaced=[int]) 

    def test_listcomptomap_alias(self):
        self.run_test("""
def foo(f,l):
    return map(f,l[3:])
def listcomptomap_alias(n): 
    map = foo
    return list([x for x in xrange(n)])
""", 10, listcomptomap_alias=[int]) 

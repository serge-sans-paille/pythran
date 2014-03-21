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

    def test_readonce_return(self):
        self.run_test("""
def foo(l):
    return l
def readonce_return(n):
    l = foo(range(n))
    return l[:]
""", 5, readonce_return=[int])

    def test_readonce_assign(self):
        self.run_test("""
def foo(l):
    l[2] = 5
    return range(10)
def readonce_assign(n):
    return foo(range(n))
""", 5, readonce_assign=[int])

    def test_readonce_assignaug(self):
        self.run_test("""
def foo(l):
    l += [2,3]
    return range(10)
def readonce_assignaug(n):
    return foo(range(n))
""", 5, readonce_assignaug=[int])

    def test_readonce_for(self):
        self.run_test("""
def foo(l):
    s = []
    for x in xrange(10):
        s.extend(list(l))
    return s
def readonce_for(n):
    return foo(range(n))
""", 5, readonce_for=[int])

    def test_readonce_2for(self):
        self.run_test("""
def foo(l):
    s = 0
    for x in l:
        s += x
    for x in l:
        s += x
    return range(s)
def readonce_2for(n):
    return foo(range(n))
""", 5, readonce_2for=[int])

    def test_readonce_while(self):
        self.run_test("""
def foo(l):
    r = []
    while (len(r) < 50):
        r.extend(list(l))
    return r
def readonce_while(n):
    return foo(range(n))
""", 5, readonce_while=[int])

    def test_readonce_if(self):
        self.run_test("""
def h(l):
    return sum(l)
def g(l):
    return sum(l)
def foo(l):
    if True:
        return g(l)
    else:
        return h(l)
def readonce_if(n):
    return foo(range(n))
""", 5, readonce_if=[int])

    def test_readonce_if2(self):
        self.run_test("""
def h(l):
    return sum(l)
def g(l):
    return max(l[1:])
def foo(l):
    if True:
        return g(l)
    else:
        return h(l)
def readonce_if2(n):
    return foo(range(n))
""", 5, readonce_if2=[int])

    def test_readonce_slice(self):
        self.run_test("""
def foo(l):
    return list(l[:])
def readonce_slice(n):
    return foo(range(n))
""", 5, readonce_slice=[int])

    def test_readonce_listcomp(self):
        self.run_test("""
def foo(l):
    return [z for x in l for y in l for z in range(x+y)]
def readonce_listcomp(n):
    return foo(range(n))
""", 5, readonce_listcomp=[int])

    def test_readonce_genexp(self):
        self.run_test("""
def foo(l):
    return (z for x in l for y in l for z in range(x+y))
def readonce_genexp(n):
    return list(foo(range(n)))
""", 5, readonce_genexp=[int])

    def test_readonce_recursive(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return foo(l,n+1)
    else:
        return sum(l)
def readonce_recursive(n): 
    return foo(range(n),0)
""", 5, readonce_recursive=[int])

    def test_readonce_recursive2(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return foo(l,n+1)
    else:
        return sum(l[1:])
def readonce_recursive2(n): 
    return foo(range(n),0)
""", 5, readonce_recursive2=[int])

    def test_readonce_cycle(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return bar(l,n)
    else:
        return sum(l)
def bar(l,n):
    return foo(l, n+1)
def readonce_cycle(n): 
    return foo(range(n),0)
""", 5, readonce_cycle=[int])

    def test_readonce_cycle2(self):
        self.run_test("""
def foo(l,n):
    if n < 5:
        return bar(l,n)
    else:
        return sum(l)
def bar(l,n):
    return foo(l, n+1)
def readonce_cycle2(n): 
    return foo(range(n),0)
""", 5, readonce_cycle2=[int])

    def test_full_unroll0(self):
        self.run_test("""
def full_unroll0():
    k = []
    for i,j in zip([1,2,3],[4,5,6]): k.append((i,j))
    return k""", full_unroll0=[])


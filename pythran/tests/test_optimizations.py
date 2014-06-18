from test_env import TestEnv


class TestOptimization(TestEnv):

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

    def test_omp_forwarding(self):
        init = """
def foo():
    a = 2
    #omp parallel
    if 1:
        print a
"""
        ref = """import itertools
def foo():
    a = 2
    'omp parallel'
    if 1:
        print a
    return __builtin__.None
def __init__():
    return __builtin__.None
__init__()"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_omp_forwarding2(self):
        init = """
def foo():
    #omp parallel
    if 1:
        a = 2
        print a
"""
        ref = """import itertools
def foo():
    'omp parallel'
    if 1:
        pass
        print 2
    return __builtin__.None
def __init__():
    return __builtin__.None
__init__()"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_omp_forwarding3(self):
        init = """
def foo():
    #omp parallel
    if 1:
        a = 2
    print a
"""
        ref = """import itertools
def foo():
    'omp parallel'
    if 1:
        a = 2
    print a
    return __builtin__.None
def __init__():
    return __builtin__.None
__init__()"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution"])

    def test_full_unroll0(self):
        init = """
def full_unroll0():
    k = []
    for i,j in zip([1,2,3],[4,5,6]): k.append((i,j))
    return k"""

        ref = """import itertools
def full_unroll0():
    k = []
    __tuple1 = (1, 4)
    j = __tuple1[1]
    i = __tuple1[0]
    __list__.append(k, (i, j))
    __tuple1 = (2, 5)
    j = __tuple1[1]
    i = __tuple1[0]
    __list__.append(k, (i, j))
    __tuple1 = (3, 6)
    j = __tuple1[1]
    i = __tuple1[0]
    __list__.append(k, (i, j))
    return k
def __init__():
    return __builtin__.None
__init__()"""

        self.check_ast(init, ref, ["pythran.optimizations.ConstantFolding", "pythran.optimizations.LoopFullUnrolling"])


    def test_full_unroll1(self):
        self.run_test("""
def full_unroll1():
    c = 0
    for i in range(3):
        for j in range(3):
            for k in range(3):
                for l in range(3):
                    for m in range(3):
                        c += 1
    return c""", full_unroll1=[])

    def test_deadcodeelimination(self):
        init = """
def bar(a):
    print a
    return 10
def foo(a):
    if 1 < bar(a):
        b = 2
    return b"""
        ref = """import itertools
def bar(a):
    print a
    return 10
def foo(a):
    (1 < bar(a))
    return 2
def __init__():
    return __builtin__.None
__init__()"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution", "pythran.optimizations.DeadCodeElimination"])

    def test_deadcodeelimination2(self):
        init = """
def foo(a):
    if 1 < max(a, 2):
        b = 2
    return b"""
        ref = """import itertools
def foo(a):
    pass
    return 2
def __init__():
    return __builtin__.None
__init__()"""
        self.check_ast(init, ref, ["pythran.optimizations.ForwardSubstitution", "pythran.optimizations.DeadCodeElimination"])

    def test_deadcodeelimination3(self):
        init = """
def bar(a):
    return a
def foo(a):
    "omp flush"
    bar(a)
    return 2"""
        ref = """import itertools
def bar(a):
    return a
def foo(a):
    'omp flush'
    pass
    return 2
def __init__():
    return __builtin__.None
__init__()"""
        self.check_ast(init, ref, ["pythran.optimizations.DeadCodeElimination"])

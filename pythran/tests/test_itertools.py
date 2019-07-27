from pythran.tests import TestEnv

import sys
import unittest

from pythran.typing import List


@TestEnv.module
class TestItertools(TestEnv):

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap(self):
        self.run_test("def imap_(l0,v): from itertools import imap; return sum(imap(lambda x:x*v, l0))", [0,1,2], 2, imap_=[List[int], int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_on_generator(self):
        self.run_test("def imap_on_generator(l,v): from itertools import imap; return sum(imap(lambda x:x*v, (y for x in l for y in xrange(x))))", [2,3,5], 1, imap_on_generator=[List[int], int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap2(self):
        self.run_test("def imap2_(l0, l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, l0, l1))", [0,1,2], [0.,1.1,2.2], 1, imap2_=[List[int], List[float], int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap2_ineq_size(self):
        """ Check imap with different size for the two list operand. """
        self.run_test("""
            def imap2_ineq_size(l0, l1, v):
                from itertools import imap
                return sum(imap(lambda x, y : x * v + y, l0, l1))""",
                      [0, 1, 2, 3], [0., 1.1, 2.2], 1,
                      imap2_ineq_size=[List[int], List[float], int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap2_on_generator(self):
        self.run_test("def imap2_on_generator(l0,l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, (z*z for x in l0 for z in xrange(x)), (z*2 for y in l1 for z in xrange(y))))", [0,1,2,3], [3,2,1,0], 2, imap2_on_generator=[List[int], List[int], int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_none(self):
        self.run_test("""
def imap_none(l0):
    from itertools import imap
    t= 0
    for a in imap(None, l0) :
        t += a[0]
    return t
""", [0,1,2], imap_none=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_none2(self):
        self.run_test("""
def imap_none2(l0):
    from itertools import imap
    t=0
    for a in imap(None, l0, l0) :
        t += sum(a)
    return t
""", [0,1,2], imap_none2=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_none_on_generators(self):
        self.run_test("""
def imap_none_g(l0):
    from itertools import imap
    t= 0
    for a in imap(None, (y for x in l0 for y in xrange(x))) :
        t += a[0]
    return t
""", [0,1,2], imap_none_g=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_none2_on_generators(self):
        self.run_test("""
def imap_none2_g(l0):
    from itertools import imap
    t=0
    for a in imap(None, (z for x in l0 for z in xrange(x)), (z for y in l0 for z in xrange(y))) :
        t += sum(a)
    return t
""", [0,1,2], imap_none2_g=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_ifilter_init(self):
        self.run_test("def ifilter_init(l0): from itertools import ifilter; return list(ifilter(lambda x: x > 2 , l0))", [0,1,2,3,4,5], ifilter_init=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_ifilter_final(self):
        self.run_test("def ifilter_final(l0): from itertools import ifilter; return list(ifilter(lambda x: x < 2, l0))", [0,1,2,3,4,5], ifilter_final=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_ifilter_on_generator(self):
        self.run_test("def ifilterg_(l0): from itertools import ifilter; return list(ifilter(lambda x: (x % 2) == 1, (y for x in l0 for y in xrange(x))))", [0,1,2,3,4,5], ifilterg_=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_ifilter_none(self):
        self.run_test("""
def ifiltern_(l0):
  from itertools import ifilter;
  s = 0
  for b in (ifilter(None, l0)):
    s += 1
  return b,s
""", [True,False,True,True], ifiltern_=[List[bool]])

    def test_product(self):
        self.run_test("def product_(l0,l1): from itertools import product; return sum(map(lambda (x,y) : x*y, product(l0,l1)))", [0,1,2,3,4,5], [10,11], product_=[List[int],List[int]])

    def test_product_on_generator(self):
        self.run_test("def product_g(l0,l1): from itertools import product; return sum(map(lambda (x,y) : x*y, product((y for x in l0 for y in xrange(x)),(y for x in l1 for y in xrange(x)))))", [0,1,2,3,4], [4,3,2,1,0], product_g=[List[int],List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_itertools(self):
        self.run_test("def test_it(l0,l1): import itertools; return sum(itertools.imap(lambda (x,y) : x*y, itertools.product(itertools.ifilter(lambda x : x > 2, l0), itertools.ifilter(lambda x : x < 12, l1))))", [0,1,2,3,4,5], [10,11,12,13,14,15], test_it=[List[int],List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_izip(self):
        self.run_test("def izip_(l0,l1): from itertools import izip; return sum(map(lambda (x,y) : x*y, izip(l0,l1)))", [0,1,2], [10,11,12], izip_=[List[int],List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_izip_on_generator(self):
        self.run_test("def izipg_(l0,l1): from itertools import izip; return sum(map(lambda (x,y) : x*y, izip((z for x in l0 for z in xrange(x)),(z for x in l1 for z in xrange(x)))))", [0,1,2,3], [3,2,1,0], izipg_=[List[int],List[int]])

    def test_zip_iter(self):
        self.run_test("""
            def zip_iter(l0):
              from itertools import izip
              s = 0
              for x in izip(l0, l0):
                for y in x:
                  s += y
              return s""",
            [0,1,2],
            zip_iter=[List[int]])

    def test_islice0(self):
        self.run_test("def islice0(l): from itertools import islice ; return [x for x in islice(l, 1,30,3)]", list(range(100)), islice0=[List[int]])

    def test_islice1(self):
        self.run_test("def islice1(l): from itertools import islice ; return [x for x in islice(l, 16)]", list(range(100)), islice1=[List[int]])

    def test_count0(self):
        self.run_test("def count0(): from itertools import count ; c = count() ; next(c); next(c); return next(c)", count0=[])

    def test_count1(self):
        self.run_test("def count1(n): from itertools import count ; c = count(n) ; next(c); next(c); return next(c)", 100, count1=[int])

    def test_count2(self):
        self.run_test("def count2(n): from itertools import count ; c = count(n,3.2) ; next(c); next(c); return next(c)", 100, count2=[int])

    def test_count3(self):
        self.run_test("def count3(n):\n from itertools import count\n j = 1\n for i in count(n):\n  if i == 10: return j\n  else: j +=1", 1, count3=[int])

    def test_next_enumerate(self):
        self.run_test("def next_enumerate(n): x = enumerate(n) ; next(x) ; return map(None, x)", list(range(5)), next_enumerate=[List[int]])

    def test_next_generator(self):
        self.run_test("def next_generator(n): x = (i for i in xrange(n) for j in xrange(i)) ; next(x) ; return map(None, x)", 5, next_generator=[int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_next_imap(self):
        self.run_test("def next_imap(n): from itertools import imap ; x = imap(abs,n) ; next(x) ; return map(None, x)", range(-5,5), next_imap=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_next_imap_none(self):
        self.run_test("def next_imap_none(n): from itertools import imap ; x = imap(None,n) ; next(x) ; return map(None, x)", range(-5,5), next_imap_none=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_next_ifilter(self):
        self.run_test("def next_ifilter(n): from itertools import ifilter ; x = ifilter(abs,n) ; next(x) ; return map(None, x)", range(-5,5), next_ifilter=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_next_ifilter_none(self):
        self.run_test("def next_ifilter_none(n): from itertools import ifilter ; x = ifilter(None,n) ; next(x) ; return map(None, x)", range(-5,5), next_ifilter_none=[List[int]])

    def test_product_next(self):
        self.run_test("def next_product(n): from itertools import product ; x = product(n,n) ; next(x) ; return map(None, x)", list(range(-5,5)), next_product=[List[int]])

    def test_product_iter(self):
        self.run_test("""
                      def product_iter(n):
                        from itertools import product
                        s = 0
                        for x in product(n,n):
                          for y in x:
                            s += y
                        return s""",
                      list(range(-5,5)), product_iter=[List[int]])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_next_izip(self):
        self.run_test("def next_izip(n): from itertools import izip ; x = izip(n,n) ; next(x) ; return map(None, x)", range(-5,5), next_izip=[List[int]])

    def test_next_islice(self):
        self.run_test("def next_islice(n): from itertools import islice ; x = islice(n,8) ; next(x) ; return map(None, x)", list(range(-5,5)), next_islice=[List[int]])

    def test_next_count(self):
        self.run_test("def next_count(n): from itertools import count ; x = count(n) ; next(x) ; return next(x)", 5, next_count=[int])

    def test_iter(self):
        self.run_test("def iter_(n): r = iter(range(5,n)) ; next(r) ; return next(r)", 12, iter_=[int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_ifilter_with_nested_lambdas(self):
        code = '''
def ifilter_with_nested_lambdas(N):
    perf = lambda n: n == sum(i for i in xrange(1, n) if n % i == 0)
    return map(perf, xrange(20))'''
        self.run_test(code, 10, ifilter_with_nested_lambdas=[int])

    def test_combinations_on_generator(self):
        self.run_test("def combinations_g(l0,a): from itertools import combinations; return sum(map(lambda (x,y) : x*y, combinations((y for x in l0 for y in xrange(x)),a)))", [0,1,2], 2, combinations_g=[List[int],int])

    def test_next_combinations(self):
        self.run_test("def next_combinations(n): from itertools import combinations ; x = combinations(n,2) ; next(x) ; return map(None, x)", list(range(5)), next_combinations=[List[int]])

    def test_combinations(self):
        self.run_test("def combinations_(l0,a): from itertools import combinations; return sum(map(lambda (x,y) : x*y, combinations(l0,a)))", [0,1,2,3,4,5], 2, combinations_=[List[int],int])

    def test_permutations_on_generator(self):
        self.run_test("def permutations_g(l0,a): from itertools import permutations; return sum(map(lambda (x,y) : x*y, permutations((y for x in l0 for y in xrange(x)),a)))", [0,1,2], 2, permutations_g=[List[int],int])

    def test_next_permutations(self):
        self.run_test("def next_permutations(n):"
                      "  from itertools import permutations ;"
                      "  x = permutations(n,2) ;"
                      "  next(x) ;"
                      "  return map(None, x)",
                      list(range(5)),
                      next_permutations=[List[int]])

    def test_permutations(self):
        '''Test permutation without second arg'''
        self.run_test("def permutations_2_(l0): "
                      "  from itertools import permutations;"
                      "  return list(permutations(l0))",
                      [0, 1, 2, 3],
                      permutations_2_=[List[int]])

    def test_permutations_with_prefix(self):
        self.run_test("def permutations_(l0,a):"
                      "  from itertools import permutations;"
                      "  return list(permutations(l0,a))",
                      [0,1,2,3,4,5], 2,
                      permutations_=[List[int],int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_over_array(self):
        self.run_test("def imap_over_array(l):"
                      "  from itertools import imap ;"
                      "  from numpy import arange ;"
                      "  t = tuple(imap(lambda x: 1, (l,l))) ;"
                      "  return arange(10).reshape((5,2))[t]",
                      3,
                      imap_over_array=[int])

    @unittest.skipIf(sys.version_info.major == 3, "not supported in pythran3")
    def test_imap_over_several_arrays(self):
        self.run_test("def imap_over_several_arrays(l):"
                      "  from itertools import imap ;"
                      "  from numpy import arange ;"
                      "  t = tuple(imap(lambda x,y: 1, (l,l), (l, l, l))) ;"
                      "  return arange(10).reshape((5,2))[t]",
                      3,
                      imap_over_several_arrays=[int])

    def test_itertools_repeat0(self):
        code = 'def itertools_repeat0(n): import itertools; return list(itertools.repeat(n, n))'
        self.run_test(code, 3, itertools_repeat0=[int])

    def test_itertools_repeat1(self):
        code = '''
        def itertools_repeat1(n):
            import itertools
            s = []
            i = 0
            for l in itertools.repeat([n]):
                s.append(l)
                i += 1
                if i < n:
                    break
            return s'''
        self.run_test(code, 3, itertools_repeat1=[int])


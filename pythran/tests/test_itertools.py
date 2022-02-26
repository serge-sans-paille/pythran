from pythran.tests import TestEnv

import unittest
import numpy as np

from pythran.typing import List, NDArray


@TestEnv.module
class TestItertools(TestEnv):

    def test_imap(self):
        self.run_test("def imap_(l0,v): return sum(map(lambda x:x*v, l0))", [0,1,2], 2, imap_=[List[int], int])

    def test_imap_on_generator(self):
        self.run_test("def imap_on_generator(l,v): return sum(map(lambda x:x*v, (y for x in l for y in range(x))))", [2,3,5], 1, imap_on_generator=[List[int], int])

    def test_imap2(self):
        self.run_test("def imap2_(l0, l1,v): return sum(map(lambda x,y:x*v+y, l0, l1))", [0,1,2], [0.,1.1,2.2], 1, imap2_=[List[int], List[float], int])

    def test_imap2_ineq_size(self):
        """ Check imap with different size for the two list operand. """
        self.run_test("""
            def imap2_ineq_size(l0, l1, v):
                return sum(map(lambda x, y : x * v + y, l0, l1))""",
                      [0, 1, 2, 3], [0., 1.1, 2.2], 1,
                      imap2_ineq_size=[List[int], List[float], int])

    def test_imap2_on_generator(self):
        self.run_test("def imap2_on_generator(l0,l1,v): return sum(map(lambda x,y:x*v+y, (z*z for x in l0 for z in range(x)), (z*2 for y in l1 for z in range(y))))", [0,1,2,3], [3,2,1,0], 2, imap2_on_generator=[List[int], List[int], int])


    def test_ifilter_init(self):
        self.run_test("def ifilter_init(l0): return list(filter(lambda x: x > 2 , l0))", [0,1,2,3,4,5], ifilter_init=[List[int]])

    def test_ifilter_final(self):
        self.run_test("def ifilter_final(l0): return list(filter(lambda x: x < 2, l0))", [0,1,2,3,4,5], ifilter_final=[List[int]])

    def test_ifilter_on_generator(self):
        self.run_test("def ifilterg_(l0): return list(filter(lambda x: (x % 2) == 1, (y for x in l0 for y in range(x))))", [0,1,2,3,4,5], ifilterg_=[List[int]])

    def test_product(self):
        self.run_test("def product_(l0,l1): from itertools import product; return sum(map(lambda t : t[0]*t[1], product(l0,l1)))", [0,1,2,3,4,5], [10,11], product_=[List[int],List[int]])

    def test_product_on_generator(self):
        self.run_test("def product_g(l0,l1): from itertools import product; return sum(map(lambda t : t[0]*t[1], product((y for x in l0 for y in range(x)),(y for x in l1 for y in range(x)))))", [0,1,2,3,4], [4,3,2,1,0], product_g=[List[int],List[int]])

    def test_itertools(self):
        self.run_test("def test_it(l0,l1): import itertools; return sum(map(lambda t : t[0]*t[1], itertools.product(filter(lambda x : x > 2, l0), filter(lambda x : x < 12, l1))))", [0,1,2,3,4,5], [10,11,12,13,14,15], test_it=[List[int],List[int]])

    def test_izip(self):
        self.run_test("def izip_(l0,l1): return sum(map(lambda t : t[0]*t[1], zip(l0,l1)))", [0,1,2], [10,11,12], izip_=[List[int],List[int]])

    def test_izip_on_generator(self):
        self.run_test("def izipg_(l0,l1): return sum(map(lambda t : t[0]*t[1], zip((z for x in l0 for z in range(x)),(z for x in l1 for z in range(x)))))", [0,1,2,3], [3,2,1,0], izipg_=[List[int],List[int]])

    def test_zip_iter(self):
        self.run_test("""
            def zip_iter(l0):
              s = 0
              for x in zip(l0, l0):
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
        self.run_test("def next_enumerate(n): x = enumerate(n) ; next(x) ; return list(map(str, x))", list(range(5)), next_enumerate=[List[int]])

    def test_next_generator(self):
        self.run_test("def next_generator(n): x = (i for i in range(n) for j in range(i)) ; next(x) ; return list(map(str, x))", 5, next_generator=[int])

    def test_next_imap(self):
        self.run_test("def next_imap(n): x = map(abs,n) ; next(x) ; return list(map(str, x))", list(range(-5,5)), next_imap=[List[int]])

    def test_next_imap_none(self):
        self.run_test("def next_imap_none(n): x = map(str,n) ; next(x) ; return list(map(str, x))", list(range(-5,5)), next_imap_none=[List[int]])

    def test_next_ifilter(self):
        self.run_test("def next_ifilter(n): x = filter(abs,n) ; next(x) ; return list(map(str, x))", list(range(-5,5)), next_ifilter=[List[int]])

    def test_product_next(self):
        self.run_test("def next_product(n): from itertools import product ; x = product(n,n) ; next(x) ; return list(map(str, x))", list(range(-5,5)), next_product=[List[int]])

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

    def test_next_izip(self):
        self.run_test("def next_izip(n): x = zip(n,n) ; next(x) ; return list(map(str, x))", list(range(-5,5)), next_izip=[List[int]])

    def test_next_islice(self):
        self.run_test("def next_islice(n): from itertools import islice ; x = islice(n,8) ; next(x) ; return list(map(str, x))", list(range(-5,5)), next_islice=[List[int]])

    def test_next_count(self):
        self.run_test("def next_count(n): from itertools import count ; x = count(n) ; next(x) ; return next(x)", 5, next_count=[int])

    def test_iter(self):
        self.run_test("def iter_(n): r = iter(range(5,n)) ; next(r) ; return next(r)", 12, iter_=[int])

    def test_ifilter_with_nested_lambdas(self):
        code = '''
def ifilter_with_nested_lambdas(N):
    perf = lambda n: n == sum(i for i in range(1, n) if n % i == 0)
    return list(map(perf, range(20)))'''
        self.run_test(code, 10, ifilter_with_nested_lambdas=[int])

    def test_combinations_on_generator(self):
        self.run_test("def combinations_g(l0,a): from itertools import combinations; return sum(map(lambda t : t[0]*t[1], combinations((y for x in l0 for y in range(x)),a)))", [0,1,2], 2, combinations_g=[List[int],int])

    def test_next_combinations(self):
        self.run_test("def next_combinations(n): from itertools import combinations ; x = combinations(n,2) ; next(x) ; return list(map(lambda y:y, x))", list(range(5)), next_combinations=[List[int]])

    def test_combinations(self):
        self.run_test("def combinations_(l0,a): from itertools import combinations; return sum(map(lambda t : t[0]*t[1], combinations(l0,a)))", [0,1,2,3,4,5], 2, combinations_=[List[int],int])

    def test_permutations_on_generator(self):
        self.run_test("def permutations_g(l0,a): from itertools import permutations; return sum(map(lambda t : t[0]*t[1], permutations((y for x in l0 for y in range(x)),a)))", [0,1,2], 2, permutations_g=[List[int],int])

    def test_next_permutations(self):
        self.run_test("def next_permutations(n, p):"
                      "  from itertools import permutations ;"
                      "  x = permutations(n,p) ;"
                      "  next(x) ;"
                      "  return list(map(str, x))",
                      list(range(5)),
                      2,
                      next_permutations=[List[int], int])

    def test_next_permutations_static(self):
        self.run_test("def next_permutations_static(n):"
                      "  from itertools import permutations ;"
                      "  x = permutations(n,2) ;"
                      "  next(x) ;"
                      "  return list(map(str, x))",
                      list(range(5)),
                      next_permutations_static=[List[int]])

    def test_next_permutations_static_2(self):
        self.run_test("def next_permutations_static2(x):"
                      "  from itertools import permutations ;"
                      "  p = permutations(range(x.shape[0]), x.ndim,) ;"
                      "  t = next(p) ;"
                      "  return x[t]",
                      np.arange(10.).reshape(2, 5),
                      next_permutations_static2=[NDArray[float, :, :]])

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

    def test_imap_over_array(self):
        self.run_test("def imap_over_array(l):"
                      "  from numpy import arange ;"
                      "  t = tuple(map(lambda x: 1, (l,l))) ;"
                      "  return arange(10).reshape((5,2))[t]",
                      3,
                      imap_over_array=[int])

    def test_imap_over_several_arrays(self):
        self.run_test("def imap_over_several_arrays(l):"
                      "  from numpy import arange ;"
                      "  t = tuple(map(lambda x,y: 1, (l,l), (l, l, l))) ;"
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


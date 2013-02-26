import unittest
from test_env import TestEnv

class TestItertools(TestEnv):

    def test_imap(self):
        self.run_test("def imap_(l0,v): from itertools import imap; return sum(imap(lambda x:x*v, l0))", [0,1,2], 2, imap_=[[int], int])

    def test_imap_on_generator(self):
        self.run_test("def imap_on_generator(l,v): from itertools import imap; return sum(imap(lambda x:x*v, (y for x in l for y in xrange(x))))", [2,3,5], 1, imap_on_generator=[[int], int])  

    def test_imap2(self):
        self.run_test("def imap2_(l0, l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, l0, l1))", [0,1,2], [0,1.1,2.2], 1, imap2_=[[int], [float], int]) 

    @unittest.skip("Not supported yet.")
    def test_imap2_ineq_size(self):
        self.run_test("def imap2_(l0, l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, l0, l1))", [0,1,2,3], [0,1.1,2.2], 1, imap2_=[[int], [float], int]) 

    def test_imap2_on_generator(self):
        self.run_test("def imap2_on_generator(l0,l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, (z*z for x in l0 for z in xrange(x)), (z*2 for y in l1 for z in xrange(y))))", [0,1,2,3], [3,2,1,0], 2, imap2_on_generator=[[int], [float], int])

    def test_imap_none(self):
        self.run_test("""
def imap_none(l0): 
    from itertools import imap
    t= 0
    for a in imap(None, l0) : 
        t += a[0]
    return t
""", [0,1,2], imap_none=[[int]])

    def test_imap_none2(self):
        self.run_test("""
def imap_none2(l0): 
    from itertools import imap
    t=0 
    for a in imap(None, l0, l0) : 
        t += sum(a)
    return t
""", [0,1,2], imap_none2=[[int]])

    def test_imap_none_on_generators(self):
        self.run_test("""
def imap_none_g(l0): 
    from itertools import imap
    t= 0
    for a in imap(None, (y for x in l0 for y in xrange(x))) : 
        t += a[0]
    return t
""", [0,1,2], imap_none_g=[[int]])

    def test_imap_none2_on_generators(self):
        self.run_test("""
def imap_none2_g(l0): 
    from itertools import imap
    t=0 
    for a in imap(None, (z for x in l0 for z in xrange(x)), (z for y in l0 for z in xrange(y))) : 
        t += sum(a)
    return t
""", [0,1,2], imap_none2_g=[[int]])

    def test_ifilter_init(self):
        self.run_test("def ifilter_init(l0): from itertools import ifilter; return list(ifilter(lambda x: x > 2 , l0))", [0,1,2,3,4,5], ifilter_init=[[int]]) 

    def test_ifilter_final(self):
        self.run_test("def ifilter_final(l0): from itertools import ifilter; return list(ifilter(lambda x: x < 2, l0))", [0,1,2,3,4,5], ifilter_final=[[int]]) 

    def test_ifilter_on_generator(self):
        self.run_test("def ifilterg_(l0): from itertools import ifilter; return list(ifilter(lambda x: (x % 2) == 1, (y for x in l0 for y in xrange(x))))", [0,1,2,3,4,5], ifilterg_=[[int]])  

    def test_ifilter_none(self):
        self.run_test("""
def ifiltern_(l0): 
  from itertools import ifilter; 
  s = 0
  for b in (ifilter(None, l0)):
    s += 1
  return s
""", [True,False,True,True], ifiltern_=[[bool]])  

    def test_product(self):
        self.run_test("def product_(l0,l1): from itertools import product; return sum(map(lambda (x,y) : x*y, product(l0,l1)))", [0,1,2,3,4,5], [10,11], product_=[[int],[int]])

    def test_product_on_generator(self):
        self.run_test("def product_g(l0,l1): from itertools import product; return sum(map(lambda (x,y) : x*y, product((y for x in l0 for y in xrange(x)),(y for x in l1 for y in xrange(x)))))", [0,1,2,3,4], [4,3,2,1,0], product_g=[[int],[int]])

    def test_itertools(self):
        self.run_test("def test_it(l0,l1): import itertools; return sum(itertools.imap(lambda (x,y) : x*y, itertools.product(itertools.ifilter(lambda x : x > 2, l0), itertools.ifilter(lambda x : x < 12, l1))))", [0,1,2,3,4,5], [10,11,12,13,14,15], test_it=[[int],[int]])

    def test_izip(self):
        self.run_test("def izip_(l0,l1): from itertools import izip; return sum(map(lambda (x,y) : x*y, izip(l0,l1)))", [0,1,2], [10,11,12], izip_=[[int],[int]]) 

    def test_izip_on_generator(self):
        self.run_test("def izipg_(l0,l1): from itertools import izip; return sum(map(lambda (x,y) : x*y, izip((z for x in l0 for z in xrange(x)),(z for x in l1 for z in xrange(x)))))", [0,1,2,3], [3,2,1,0], izipg_=[[int],[int]]) 



import unittest
from test_env import TestEnv

class TestBase(TestEnv):

    def test_imap(self):
        self.run_test("def imap_(l0,v): from itertools import imap; return sum(imap(lambda x:x*v, l0))", [0,1,2], 2, imap_=[[int], int])

    def test_imap_on_generator(self):
        self.run_test("def imap_on_generator(l,v): from itertools import imap; return sum(imap(lambda x:x*v, (x for x in l)))", [2,3,5], 1, imap_on_generator=[[int], int])  

    def test_imap2(self):
        self.run_test("def imap2_(l0, l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, l0, l1))", [0,1,2], [0,1.1,2.2], 1, imap2_=[[int], [float], int]) 

    @unittest.skip("Not supported yet.")
    def test_imap2_ineq_size(self):
        self.run_test("def imap2_(l0, l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, l0, l1))", [0,1,2,3], [0,1.1,2.2], 1, imap2_=[[int], [float], int]) 

    def test_imap2_on_generator(self):
        self.run_test("def imap2_on_generator(l0,l1,v): from itertools import imap; return sum(imap(lambda x,y:x*v+y, (x*x for x in l0), (y*y for y in l1)))", [0,1,2], [0,1.1,2.2], 2, imap2_on_generator=[[int], [float], int])

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
    for a in imap(None, (x for x in l0)) : 
        t += a[0]
    return t
""", [0,1,2], imap_none_g=[[int]])

    def test_imap_none2_on_generators(self):
        self.run_test("""
def imap_none2_g(l0): 
    from itertools import imap
    t=0 
    for a in imap(None, (x for x in l0), (y for y in l0)) : 
        t += sum(a)
    return t
""", [0,1,2], imap_none2_g=[[int]])

    def test_ifilter(self):
        self.run_test("def ifilter_(l0): from itertools import ifilter; return sum(ifilter(lambda x: (x % 2) == 1, l0))", [0,1,2,3,4,5], ifilter_=[[int]])  

    def test_ifilter_on_generator(self):
        self.run_test("def ifilterg_(l0): from itertools import ifilter; return sum(ifilter(lambda x: (x % 2) == 1, (x for x in l0)))", [0,1,2,3,4,5], ifilterg_=[[int]])  

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

    def test_itertools(self):
        self.run_test("def test_it(l0,l1): import itertools; return sum(itertools.imap(lambda (x,y) : x*y, itertools.ifilter(lambda (x,y) : x*y > 25, itertools.product(l0,l1))))", [0,1,2,3,4,5], [10,11], test_it=[[int],[int]])

    def test_izip(self):
        self.run_test("def izip_(l0,l1): from itertools import izip; return sum(map(lambda (x,y) : x*y, izip(l0,l1)))", [0,1,2], [10,11,12], izip_=[[int],[int]]) 

    def test_izip_on_generator(self):
        self.run_test("def izipg_(l0,l1): from itertools import izip; return sum(map(lambda (x,y) : x*y, izip((x for x in l0),(x for x in l1))))", [0,1,2], [10,11,12], izipg_=[[int],[int]]) 



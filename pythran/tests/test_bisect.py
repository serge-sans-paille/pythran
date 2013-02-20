
import unittest
from test_env import TestEnv

class TestBisect(TestEnv):

    def test_bisect_left0(self):
        self.run_test("def bisect_left0(l,a): from bisect import bisect_left ; return bisect_left(l,a)", [0,1,2,3],2, bisect_left0=[[int],int])

    def test_bisect_left1(self):
        self.run_test("def bisect_left1(l,a): from bisect import bisect_left ; return bisect_left(l,a,1)", [0,1,2,3],2, bisect_left1=[[int],int])

    def test_bisect_left2(self):
        self.run_test("def bisect_left2(l,a): from bisect import bisect_left ; return bisect_left(l,a)", [1,1,1,1],1, bisect_left2=[[int],int])

    def test_bisect_left3(self):
        self.run_test("def bisect_left3(l,a): from bisect import bisect_left ; return bisect_left(l,a,1,2)", [0,1,1,3],2, bisect_left3=[[int],int])

    def test_bisect_left4(self):
        self.run_test("def bisect_left4(l,a): from bisect import bisect_left ; return bisect_left(l,a)", [1,1,1,1],2, bisect_left4=[[int],int])

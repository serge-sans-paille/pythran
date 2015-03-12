from test_env import TestEnv


@TestEnv.module
class TestNumpyRandom(TestEnv):

    def test_numpy_random0(self):
        self.run_test("def numpy_random0(n): from numpy.random import random ; s= sum(random() for x in range(n)) ; return abs(s/n -.5) < .05", 10**5, numpy_random0=[int])

    def test_numpy_random1(self):
        self.run_test("def numpy_random1(n): from numpy.random import random ; s= sum(random(size=n)) ; return abs(s/n -.5) < .05", 10**5, numpy_random1=[int])

    def test_numpy_random2(self):
        self.run_test("def numpy_random2(n): from numpy.random import random ; from numpy import sum;  s= sum(random((n,n))) ; return abs(s/n -.5) < .05", 10**3, numpy_random2=[int])


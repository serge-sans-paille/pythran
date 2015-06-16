from test_env import TestEnv


@TestEnv.module
class TestNumpyRandom(TestEnv):

    def test_numpy_random0(self):
        self.run_test("def numpy_random0(n): from numpy.random import random ; s= sum(random() for x in range(n)) ; assert(abs(s/n -.5) < .05)", 10**5, numpy_random0=[int])

    def test_numpy_random1(self):
        self.run_test("def numpy_random1(n): from numpy.random import random ; s= sum(random(size=n)) ; assert(abs(s/n -.5) < .05)", 10**5, numpy_random1=[int])

    def test_numpy_random2(self):
        self.run_test("def numpy_random2(n): from numpy.random import random ; from numpy import sum; s=sum(random((n,n))); assert(abs(s/(n*n) - .5) < 5e-3)", 10**3, numpy_random2=[int])

    def test_numpy_binomial0(self):
        code = """
        def numpy_binomial0(n, p, size):
         from numpy.random import binomial
         from numpy import var
         a = [binomial(n, p) for x in range(size)]
         assert(abs(float(sum(a))/size - n * p) < .05 and abs(var(a) - n*p*(1-p)) < .05)
        """
        self.run_test(code, 10, .2, 10**5, numpy_binomial0=[float, float, int])

    def test_numpy_binomial1(self):
        code = """
        def numpy_binomial1(n, p, size):
         from numpy.random import binomial
         from numpy import var
         a=binomial(n, p, size)
         assert(abs(float(sum(a))/size - n * p) < .05 and abs(var(a) - n*p*(1-p)) < .05)
        """
        self.run_test(code, 7, .2, 10**5, numpy_binomial1=[float, float, int])

    def test_numpy_binomial2(self):
        code = """
        def numpy_binomial2(n, p, size):
         from numpy.random import binomial
         from numpy import sum, var
         a=binomial(n, p, (size, size))
         assert(abs(float(sum(a))/(size*size) - n * p) < .05 and abs(var(a) - n*p*(1-p)) < .05)
        """
        self.run_test(code, 9, .2, 10**3, numpy_binomial2=[float, float, int])

    def test_numpy_binomial_exception(self):
        code = """
        def numpy_binomial_exception():
         from numpy.random import binomial;
         c = 0;
         try:  binomial(-1, 0.1);
         except ValueError:  c += 1;
         try:  binomial(1, -1);
         except ValueError:  c += 1;
         try:  binomial(1, 10);
         except ValueError:  c += 1;
         assert(c == 3)
         return c
        """
        self.run_test(code, numpy_binomial_exception=[])

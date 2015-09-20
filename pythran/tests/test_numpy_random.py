from test_env import TestEnv


@TestEnv.module
class TestNumpyRandom(TestEnv):

    ###########################################################################
    # Tests for numpy.random.random
    ###########################################################################

    def test_numpy_random0(self):
        """ Check numpy random without arguments. """
        self.run_test("""
            def numpy_random0(n):
                from numpy.random import random
                s = sum(random() for x in range(n))
                assert(abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random0=[int])

    def test_numpy_random1(self):
        """ Check numpy random with size argument. """
        self.run_test("""
            def numpy_random1(n):
                from numpy.random import random
                s = sum(random(size=n))
                assert(abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random1=[int])

    def test_numpy_random2(self):
        """ Check numpy random with shape argument. """
        self.run_test("""
            def numpy_random2(n):
                from numpy.random import random
                from numpy import sum
                s = sum(random((n, n)))
                assert(abs(s / (n * n) - .5) < 5e-3)""",
                      10 ** 3, numpy_random2=[int])

    ###########################################################################
    # Tests for numpy.random.random_sample
    ###########################################################################

    def test_numpy_random_sample0(self):
        """ Check numpy random_sample without arguments. """
        self.run_test("""
            def numpy_random_sample0(n):
                from numpy.random import random_sample
                s = sum(random_sample() for x in range(n))
                assert(abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random_sample0=[int])

    def test_numpy_random_sample1(self):
        """ Check numpy random_sample with size argument. """
        self.run_test("""
            def numpy_random_sample1(n):
                from numpy.random import random_sample
                s = sum(random_sample(size=n))
                assert(abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random_sample1=[int])

    def test_numpy_random_sample2(self):
        """ Check numpy random_sample with shape argument. """
        self.run_test("""
            def numpy_random_sample2(n):
                from numpy.random import random_sample
                from numpy import sum
                s = sum(random_sample((n, n)))
                assert(abs(s / (n * n) - .5) < 5e-3)""",
                      10 ** 3, numpy_random_sample2=[int])

    ###########################################################################
    # Tests for numpy.random.rand
    ###########################################################################

    def test_numpy_rand0(self):
        """ Check numpy rand without arguments. """
        self.run_test("""
            def numpy_rand0(n):
                from numpy.random import rand
                s = sum(rand() for x in range(n))
                assert(abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_rand0=[int])

    def test_numpy_rand1(self):
        """ Check numpy rand with multiple arguments. """
        self.run_test("""
            def numpy_rand1(n):
                from numpy.random import rand
                from numpy import sum
                s = sum(rand(n, n))
                assert(abs(s / (n * n) - .5) < 5e-3)""",
                      10 ** 3, numpy_rand1=[int])

    ###########################################################################
    # Tests for numpy.random.binomial
    ###########################################################################

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

    ###########################################################################
    # Tests for numpy.random.standard_normal
    ###########################################################################

    def test_numpy_standard_normal0(self):
        """ Check standard_normal without argument with mean and variance. """
        code = """
        def numpy_standard_normal0(size):
            from numpy.random import standard_normal
            from numpy import var, mean
            a = [standard_normal() for x in range(size)]
            print mean(a)
            assert(abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_normal0=[int])

    def test_numpy_standard_normal1(self):
        """ Check standard_normal with size argument with mean and variance."""
        code = """
        def numpy_standard_normal1(size):
            from numpy.random import standard_normal
            from numpy import var, mean
            a = standard_normal(size)
            print mean(a)
            assert(abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_normal1=[int])

    def test_numpy_standard_normal2(self):
        """Check standard_normal with shape argument with mean and variance."""
        code = """
        def numpy_standard_normal2(size):
            from numpy.random import standard_normal
            from numpy import mean, var
            a = standard_normal((size, size))
            print mean(a)
            assert(abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_standard_normal2=[int])

    ###########################################################################
    # Tests for numpy.random.randn
    ###########################################################################

    def test_numpy_randn0(self):
        """ Check numpy randn without arguments. """
        self.run_test("""
            def numpy_randn0(n):
                from numpy.random import randn
                from numpy import mean, var
                a = [randn() for x in range(n)]
                assert(abs(mean(a)) < .05 and abs(var(a) - 1) < .05)""",
                      10 ** 5, numpy_randn0=[int])

    def test_numpy_randn1(self):
        """ Check numpy randn with multiple arguments. """
        self.run_test("""
            def numpy_randn1(n):
                from numpy.random import randn
                from numpy import mean, var
                a = randn(n, n)
                assert(abs(mean(a)) < .05 and abs(var(a) - 1) < .05)""",
                      10 ** 3, numpy_randn1=[int])

    ###########################################################################
    # Tests for numpy.random.randint
    ###########################################################################

    def test_numpy_randint0(self):
        """ Check numpy randint with one argument. """
        self.run_test("""
            def numpy_randint0(n):
                from numpy.random import randint
                from numpy import mean, var
                a = [randint(11) for x in range(n)]
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_randint0=[int])

    def test_numpy_randint1(self):
        """ Check numpy randint with min/max argument. """
        self.run_test("""
            def numpy_randint1(n):
                from numpy.random import randint
                from numpy import mean, var
                a = [randint(10, 21) for x in range(n)]
                assert(abs(mean(a) - 15) < .05)""",
                      10 ** 5, numpy_randint1=[int])

    def test_numpy_randint2(self):
        """ Check numpy randint with size argument. """
        self.run_test("""
            def numpy_randint2(n):
                from numpy.random import randint
                from numpy import mean, var
                a = randint(10, 21, n)
                assert(abs(mean(a) - 15) < .05)""",
                      10 ** 5, numpy_randint2=[int])

    def test_numpy_randint3(self):
        """ Check numpy randint with shape argument. """
        self.run_test("""
            def numpy_randint3(n):
                from numpy.random import randint
                from numpy import mean, var
                a = randint(10, 21, (n, n))
                assert(abs(mean(a) - 15) < .05)""",
                      10 ** 3, numpy_randint3=[int])

    ###########################################################################
    # Tests for numpy.random.random_integer
    ###########################################################################

    def test_numpy_random_integers0(self):
        """ Check numpy random_integers with one argument. """
        self.run_test("""
            def numpy_random_integers0(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = [random_integers(9) for x in range(n)]
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_integers0=[int])

    def test_numpy_random_integers1(self):
        """ Check numpy random_integers with min/max argument. """
        self.run_test("""
            def numpy_random_integers1(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = [random_integers(10, 20) for x in range(n)]
                assert(abs(mean(a) - 15) < .05)""",
                      10 ** 5, numpy_random_integers1=[int])

    def test_numpy_random_integers2(self):
        """ Check numpy random_integers with size argument. """
        self.run_test("""
            def numpy_random_integers2(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = random_integers(10, 20, n)
                assert(abs(mean(a) - 15) < .05)""",
                      10 ** 5, numpy_random_integers2=[int])

    def test_numpy_random_integers3(self):
        """ Check numpy random_integers with shape argument. """
        self.run_test("""
            def numpy_random_integers3(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = random_integers(10, 20, (n, n))
                assert(abs(mean(a) - 15) < .05)""",
                      10 ** 3, numpy_random_integers3=[int])

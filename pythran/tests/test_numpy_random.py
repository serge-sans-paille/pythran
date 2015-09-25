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
    # Tests for numpy.random.ranf
    ###########################################################################

    def test_numpy_ranf0(self):
        """ Check numpy ranf without arguments. """
        self.run_test("""
            def numpy_ranf0(n):
                from numpy.random import ranf
                from numpy import mean
                s = [ranf() for x in range(n)]
                assert(abs(mean(s) - .5) < .05)""",
                      10 ** 5, numpy_ranf0=[int])

    def test_numpy_ranf1(self):
        """ Check numpy ranf with size argument. """
        self.run_test("""
            def numpy_ranf1(n):
                from numpy.random import ranf
                from numpy import mean
                a = ranf(size=n)
                assert(abs(mean(a) - .5) < .05)""",
                      10 ** 5, numpy_ranf1=[int])

    def test_numpy_ranf2(self):
        """ Check numpy ranf with shape argument. """
        self.run_test("""
            def numpy_ranf2(n):
                from numpy.random import ranf
                from numpy import mean
                a = ranf((n, n))
                assert(abs(mean(a) - .5) < 5e-3)""",
                      10 ** 3, numpy_ranf2=[int])

    ###########################################################################
    # Tests for numpy.random.sample
    ###########################################################################

    def test_numpy_sample0(self):
        """ Check numpy sample without arguments. """
        self.run_test("""
            def numpy_sample0(n):
                from numpy.random import sample
                from numpy import mean
                s = [sample() for x in range(n)]
                assert(abs(mean(s) - .5) < .05)""",
                      10 ** 5, numpy_sample0=[int])

    def test_numpy_sample1(self):
        """ Check numpy sample with size argument. """
        self.run_test("""
            def numpy_sample1(n):
                from numpy.random import sample
                from numpy import mean
                s = sample(size=n)
                assert(abs(mean(s) - .5) < .05)""",
                      10 ** 5, numpy_sample1=[int])

    def test_numpy_sample2(self):
        """ Check numpy sample with shape argument. """
        self.run_test("""
            def numpy_sample2(n):
                from numpy.random import sample
                from numpy import mean
                s = sample((n, n))
                assert(abs(mean(s) - .5) < 5e-3)""",
                      10 ** 3, numpy_sample2=[int])

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

    ###########################################################################
    # Tests for numpy.random.choice
    ###########################################################################

    def test_numpy_random_choice0(self):
        """ Check numpy.random.choice with one int argument. """
        self.run_test("""
            def numpy_random_choice0(n):
                from numpy.random import choice
                from numpy import mean, var
                a = [choice(11) for _ in range(n)]
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice0=[int])

    def test_numpy_random_choice1(self):
        """ Check numpy.random.choice with one ndarray argument. """
        self.run_test("""
            def numpy_random_choice1(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = [choice(arange(11)) for _ in range(n)]
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice1=[int])

    def test_numpy_random_choice2(self):
        """ Check numpy.random.choice with one numpy_expr argument. """
        self.run_test("""
            def numpy_random_choice2(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = [choice(arange(11) + n) for _ in range(n)]
                assert(abs(mean(a) - (5 + n)) < .05)""",
                      10 ** 5, numpy_random_choice2=[int])

    def test_numpy_random_choice3(self):
        """ Check numpy.random.choice with int and int argument. """
        self.run_test("""
            def numpy_random_choice3(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(11, n)
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice3=[int])

    def test_numpy_random_choice4(self):
        """ Check numpy.random.choice with int and tuple argument. """
        self.run_test("""
            def numpy_random_choice4(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(11, (n, n))
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 3, numpy_random_choice4=[int])

    def test_numpy_random_choice5(self):
        """ Check numpy.random.choice with int, tuple and proba argument. """
        self.run_test("""
            def numpy_random_choice5(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(5, (n, n), True, [0.3, 0.3, 0.2, 0.1, 0.1])
                assert(abs(mean(a) - 1.4) < .05)""",
                      10 ** 3, numpy_random_choice5=[int])

    def test_numpy_random_choice6(self):
        """ Check numpy.random.choice with int, int and proba argument. """
        self.run_test("""
            def numpy_random_choice6(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(5, n, True, [0.3, 0.3, 0.2, 0.1, 0.1])
                assert(abs(mean(a) - 1.4) < .05)""",
                      10 ** 5, numpy_random_choice6=[int])

    def test_numpy_random_choice7(self):
        """ Check numpy.random.choice with ndarray and int argument. """
        self.run_test("""
            def numpy_random_choice7(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(11), n)
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice7=[int])

    def test_numpy_random_choice8(self):
        """ Check numpy.random.choice with ndarray and tuple argument. """
        self.run_test("""
            def numpy_random_choice8(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(11), (n, n))
                assert(abs(mean(a) - 5) < .05)""",
                      10 ** 3, numpy_random_choice8=[int])

    def test_numpy_random_choice9(self):
        """Check numpy.random.choice with ndarray, tuple and proba argument."""
        self.run_test("""
            def numpy_random_choice9(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(5), (n, n), True, [0.3, 0.3, 0.2, 0.1, 0.1])
                assert(abs(mean(a) - 1.4) < .05)""",
                      10 ** 3, numpy_random_choice9=[int])

    def test_numpy_random_choice10(self):
        """ Check numpy.random.choice with ndarray, int and proba argument. """
        self.run_test("""
            def numpy_random_choice10(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(5), n, True, [0.3, 0.3, 0.2, 0.1, 0.1])
                assert(abs(mean(a) - 1.4) < .05)""",
                      10 ** 5, numpy_random_choice10=[int])

    ###########################################################################
    # Tests for numpy.random.bytes
    ###########################################################################

    def test_numpy_random_bytes1(self):
        """ Check numpy.random.bytes. """
        self.run_test("""
            def numpy_random_bytes1(n):
                from numpy.random import bytes
                from numpy import mean, fromstring, uint8
                a = bytes(n)
                assert(abs(mean(fromstring(a, uint8)) - 127.5) < .05)""",
                      10 ** 8, numpy_random_bytes1=[int])

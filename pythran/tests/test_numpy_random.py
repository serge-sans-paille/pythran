from pythran.tests import TestEnv
import warnings
warnings.filterwarnings("ignore",category=DeprecationWarning)


class TestNumpyRandom(TestEnv):

    ###########################################################################
    #Tests for numpy.random.random
    ###########################################################################

    def test_numpy_random0(self):
        """ Check numpy random without arguments. """
        self.run_test("""
            def numpy_random0(n):
                from numpy.random import random
                s = sum(random() for x in range(n))
                return (abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random0=[int])

    def test_numpy_random1(self):
        """ Check numpy random with size argument. """
        self.run_test("""
            def numpy_random1(n):
                from numpy.random import random
                s = sum(random(size=n))
                return (abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random1=[int])

    def test_numpy_random2(self):
        """ Check numpy random with shape argument. """
        self.run_test("""
            def numpy_random2(n):
                from numpy.random import random
                from numpy import sum
                s = sum(random((n, n)))
                return (abs(s / (n * n) - .5) < .05)""",
                      10 ** 3, numpy_random2=[int])

    def test_numpy_random3(self):
        """ Check numpy random with constant size argument. """
        self.run_test("""
            def numpy_random3(n):
                from numpy.random import random
                s = sum(random(10 ** 5))
                return (abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random3=[int])


    ###########################################################################
    #Tests for numpy.random.random_sample
    ###########################################################################

    def test_numpy_random_sample0(self):
        """ Check numpy random_sample without arguments. """
        self.run_test("""
            def numpy_random_sample0(n):
                from numpy.random import random_sample
                s = sum(random_sample() for x in range(n))
                return (abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random_sample0=[int])

    def test_numpy_random_sample1(self):
        """ Check numpy random_sample with size argument. """
        self.run_test("""
            def numpy_random_sample1(n):
                from numpy.random import random_sample
                s = sum(random_sample(size=n))
                return (abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_random_sample1=[int])

    def test_numpy_random_sample2(self):
        """ Check numpy random_sample with shape argument. """
        self.run_test("""
            def numpy_random_sample2(n):
                from numpy.random import random_sample
                from numpy import sum
                s = sum(random_sample((n, n)))
                return (abs(s / (n * n) - .5) < .05)""",
                      10 ** 3, numpy_random_sample2=[int])

    ###########################################################################
    #Tests for numpy.random.ranf
    ###########################################################################

    def test_numpy_ranf0(self):
        """ Check numpy ranf without arguments. """
        self.run_test("""
            def numpy_ranf0(n):
                from numpy.random import ranf
                from numpy import mean
                s = [ranf() for x in range(n)]
                return (abs(mean(s) - .5) < .05)""",
                      10 ** 5, numpy_ranf0=[int])

    def test_numpy_ranf1(self):
        """ Check numpy ranf with size argument. """
        self.run_test("""
            def numpy_ranf1(n):
                from numpy.random import ranf
                from numpy import mean
                a = ranf(size=n)
                return (abs(mean(a) - .5) < .05)""",
                      10 ** 5, numpy_ranf1=[int])

    def test_numpy_ranf2(self):
        """ Check numpy ranf with shape argument. """
        self.run_test("""
            def numpy_ranf2(n):
                from numpy.random import ranf
                from numpy import mean
                a = ranf((n, n))
                return (abs(mean(a) - .5) < .05)""",
                      10 ** 3, numpy_ranf2=[int])

    ###########################################################################
    #Tests for numpy.random.sample
    ###########################################################################

    def test_numpy_sample0(self):
        """ Check numpy sample without arguments. """
        self.run_test("""
            def numpy_sample0(n):
                from numpy.random import sample
                from numpy import mean
                s = [sample() for x in range(n)]
                return (abs(mean(s) - .5) < .05)""",
                      10 ** 5, numpy_sample0=[int])

    def test_numpy_sample1(self):
        """ Check numpy sample with size argument. """
        self.run_test("""
            def numpy_sample1(n):
                from numpy.random import sample
                from numpy import mean
                s = sample(size=n)
                return (abs(mean(s) - .5) < .05)""",
                      10 ** 5, numpy_sample1=[int])

    def test_numpy_sample2(self):
        """ Check numpy sample with shape argument. """
        self.run_test("""
            def numpy_sample2(n):
                from numpy.random import sample
                from numpy import mean
                s = sample((n, n))
                return (abs(mean(s) - .5) < .05)""",
                      10 ** 3, numpy_sample2=[int])

    ###########################################################################
    #Tests for numpy.random.rand
    ###########################################################################

    def test_numpy_rand0(self):
        """ Check numpy rand without arguments. """
        self.run_test("""
            def numpy_rand0(n):
                from numpy.random import rand
                s = sum(rand() for x in range(n))
                return (abs(s / n - .5) < .05)""",
                      10 ** 5, numpy_rand0=[int])

    def test_numpy_rand1(self):
        """ Check numpy rand with multiple arguments. """
        self.run_test("""
            def numpy_rand1(n):
                from numpy.random import rand
                from numpy import sum
                s = sum(rand(n, n))
                return (abs(s / (n * n) - .5) < .05)""",
                      10 ** 3, numpy_rand1=[int])

    ###########################################################################
    #Tests for numpy.random.binomial
    ###########################################################################

    def test_numpy_binomial0(self):
        code = """
        def numpy_binomial0(n, p, size):
         from numpy.random import binomial
         from numpy import var
         a = [binomial(n, p) for x in range(size)]
         return (abs(float(sum(a))/size - n * p) < .05 and abs(var(a) - n*p*(1-p)) < .05)
        """
        self.run_test(code, 10., .2, 10**5, numpy_binomial0=[float, float, int])

    def test_numpy_binomial1(self):
        code = """
        def numpy_binomial1(n, p, size):
         from numpy.random import binomial
         from numpy import var
         a=binomial(n, p, size)
         return (abs(float(sum(a))/size - n * p) < .05 and abs(var(a) - n*p*(1-p)) < .05)
        """
        self.run_test(code, 7., .2, 10**5, numpy_binomial1=[float, float, int])

    def test_numpy_binomial2(self):
        code = """
        def numpy_binomial2(n, p, size):
         from numpy.random import binomial
         from numpy import sum, var
         a=binomial(n, p, (size, size))
         return (abs(float(sum(a))/(size*size) - n * p) < .05 and abs(var(a) - n*p*(1-p)) < .05)
        """
        self.run_test(code, 9., .2, 10**3, numpy_binomial2=[float, float, int])

    def test_numpy_binomial_exception(self):
        code = """
        def numpy_binomial_exception():
            from numpy.random import binomial
            c = 0;
            try : binomial(-1, 0.1) 
            except ValueError : c += 1
            try : binomial(1, -1)
            except ValueError : c += 1
            try : binomial(1, 10)
            except ValueError : c += 1
            return c
        """
        self.run_test(code, numpy_binomial_exception=[])

    ###########################################################################
    #Tests for numpy.random.standard_normal
    ###########################################################################

    def test_numpy_standard_normal0(self):
        """ Check standard_normal without argument with mean and variance. """
        code = """
        def numpy_standard_normal0(size):
            from numpy.random import standard_normal
            from numpy import var, mean
            a = [standard_normal() for x in range(size)]
            print(mean(a))
            return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_normal0=[int])

    def test_numpy_standard_normal1(self):
        """ Check standard_normal with size argument with mean and variance."""
        code = """
        def numpy_standard_normal1(size):
            from numpy.random import standard_normal
            from numpy import var, mean
            a = standard_normal(size)
            print(mean(a))
            return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_normal1=[int])

    def test_numpy_standard_normal2(self):
        """Check standard_normal with shape argument with mean and variance."""
        code = """
        def numpy_standard_normal2(size):
            from numpy.random import standard_normal
            from numpy import mean, var
            a = standard_normal((size, size))
            print(mean(a))
            return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_standard_normal2=[int])

    ###########################################################################
    #Tests for numpy.random.normal
    ###########################################################################

    def test_numpy_normal0(self):
        """ Check normal without argument with mean and variance. """
        code = """
        def numpy_normal0(size):
            from numpy.random import normal
            from numpy import var, mean
            a = [normal() for x in range(size)]
            print(mean(a))
            return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_normal0=[int])

    def test_numpy_normal0a(self):
        """ Check normal with 1 argument with mean and variance. """
        code = """
        def numpy_normal0a(size):
            from numpy.random import normal
            from numpy import var, mean
            a = [normal(3.) for x in range(size)]
            print(mean(a))
            return (abs(mean(a)-3) < 0.05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_normal0a=[int])

    def test_numpy_normal0b(self):
        """ Check normal with 2 argument with mean and variance. """
        code = """
        def numpy_normal0b(size):
            from numpy.random import normal
            from numpy import var, mean, sqrt
            mu, sigma = 0, 0.1
            a = normal(mu, sigma, size)
            print(mean(a))
            return (abs(mu - mean(a)) < 0.05 and abs(sigma - sqrt(var(a,ddof=1))) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_normal0b=[int])



    def test_numpy_normal1(self):
        """ Check normal with size argument with mean and variance."""
        code = """
        def numpy_normal1(size):
            from numpy.random import normal
            from numpy import var, mean
            a = normal(size=size)
            print(mean(a))
            return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_normal1=[int])

    def test_numpy_normal2(self):
        """Check normal with shape argument with mean and variance."""
        code = """
        def numpy_normal2(size):
            from numpy.random import normal
            from numpy import mean, var
            a = normal(size=(size, size))
            print(mean(a))
            return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_normal2=[int])

    ###########################################################################
    #Tests for numpy.random.poisson
    ###########################################################################

    def test_numpy_poisson0(self):
        """ Check poisson without argument with mean and variance. """
        code = """
        def numpy_poisson0(size):
            from numpy.random import poisson
            from numpy import var, mean
            a = [poisson() for x in range(size)]
            print(mean(a))
            return (abs(mean(a)-1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_poisson0=[int])

    def test_numpy_poisson0a(self):
        """ Check poisson with 1 argument with mean and variance. """
        code = """
        def numpy_poisson0a(size):
            from numpy.random import poisson
            from numpy import var, mean
            a = [poisson(3.) for x in range(size)]
            print(mean(a))
            return (abs(mean(a)-3) < .05 and abs(var(a) - 3) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_poisson0a=[int])

    def test_numpy_poisson0b(self):
        """ Check poisson with 2 argument with mean and variance. """
        code = """
        def numpy_poisson0b(size):
            from numpy.random import poisson
            from numpy import var, mean, sqrt
            lam = 10
            a = poisson(lam, size)
            print(mean(a))
            return (abs(mean(a)-lam) < 0.05 and abs(sqrt(lam) - sqrt(var(a,ddof=1))) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_poisson0b=[int])



    def test_numpy_poisson1(self):
        """ Check poisson with size argument with mean and variance."""
        code = """
        def numpy_poisson1(size):
            from numpy.random import poisson
            from numpy import var, mean
            a = poisson(size=size)
            print(mean(a))
            return (abs(mean(a)-1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_poisson1=[int])

    def test_numpy_poisson2(self):
        """Check poisson with shape argument with mean and variance."""
        code = """
        def numpy_poisson2(size):
            from numpy.random import poisson
            from numpy import mean, var
            a = poisson(size=(size, size))
            print(mean(a))
            return (abs(mean(a)-1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_poisson2=[int])

    ###########################################################################
    #Tests for numpy.random.randn
    ###########################################################################

    def test_numpy_randn0(self):
        """ Check numpy randn without arguments. """
        self.run_test("""
            def numpy_randn0(n):
                from numpy.random import randn
                from numpy import mean, var
                a = [randn() for x in range(n)]
                return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)""",
                      10 ** 5, numpy_randn0=[int])

    def test_numpy_randn1(self):
        """ Check numpy randn with multiple arguments. """
        self.run_test("""
            def numpy_randn1(n):
                from numpy.random import randn
                from numpy import mean, var
                a = randn(n, n)
                return (abs(mean(a)) < .05 and abs(var(a) - 1) < .05)""",
                      10 ** 3, numpy_randn1=[int])

    ###########################################################################
    #Tests for numpy.random.randint
    ###########################################################################

    def test_numpy_randint0(self):
        """ Check numpy randint with one argument. """
        self.run_test("""
            def numpy_randint0(n):
                from numpy.random import randint
                from numpy import mean, var
                a = [randint(11) for x in range(n)]
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_randint0=[int])

    def test_numpy_randint1(self):
        """ Check numpy randint with min/max argument. """
        self.run_test("""
            def numpy_randint1(n):
                from numpy.random import randint
                from numpy import mean, var
                a = [randint(10, 21) for x in range(n)]
                return (abs(mean(a) - 15) < .05)""",
                      10 ** 5, numpy_randint1=[int])

    def test_numpy_randint2(self):
        """ Check numpy randint with size argument. """
        self.run_test("""
            def numpy_randint2(n):
                from numpy.random import randint
                from numpy import mean, var
                a = randint(10, 21, n)
                return (abs(mean(a) - 15) < .05)""",
                      10 ** 5, numpy_randint2=[int])

    def test_numpy_randint3(self):
        """ Check numpy randint with shape argument. """
        self.run_test("""
            def numpy_randint3(n):
                from numpy.random import randint
                from numpy import mean, var
                a = randint(10, 21, (n, n))
                return (abs(mean(a) - 15) < .05)""",
                      10 ** 3, numpy_randint3=[int])

    def test_numpy_randint4(self):
        """ Check numpy randint with shape argument. """
        self.run_test("""
            def numpy_randint4(n):
                from numpy.random import randint
                from numpy import mean, var
                a = randint(10, size=n)
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 3, numpy_randint4=[int])

    ###########################################################################
    #Tests for numpy.random.random_integer
    ###########################################################################

    def test_numpy_random_integers0(self):
        """ Check numpy random_integers with one argument. """
        self.run_test("""
            def numpy_random_integers0(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = [random_integers(9) for x in range(n)]
                return all(0<=r<=9 for r in a)""",
                      3, numpy_random_integers0=[int])

    def test_numpy_random_integers1(self):
        """ Check numpy random_integers with min/max argument. """
        self.run_test("""
            def numpy_random_integers1(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = [random_integers(10, 20) for x in range(n)]
                return all(10<=r<=20 for r in a)""",
                      3, numpy_random_integers1=[int])

    def test_numpy_random_integers2(self):
        """ Check numpy random_integers with size argument. """
        self.run_test("""
            def numpy_random_integers2(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = random_integers(10, 20, n)
                return all(10<=r<=20 for r in a)""",
                      3, numpy_random_integers2=[int])

    def test_numpy_random_integers3(self):
        """ Check numpy random_integers with shape argument. """
        self.run_test("""
            def numpy_random_integers3(n):
                from numpy.random import random_integers
                from numpy import mean, var
                a = random_integers(10, 20, (n, n))
                return all(10<=r<=20 for r in a.flat)""",
                      3, numpy_random_integers3=[int])

    ###########################################################################
    #Tests for numpy.random.choice
    ###########################################################################

    def test_numpy_random_choice0(self):
        """ Check numpy.random.choice with one int argument. """
        self.run_test("""
            def numpy_random_choice0(n):
                from numpy.random import choice
                from numpy import mean, var
                a = [choice(11) for _ in range(n)]
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice0=[int])

    def test_numpy_random_choice1(self):
        """ Check numpy.random.choice with one ndarray argument. """
        self.run_test("""
            def numpy_random_choice1(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = [choice(arange(11)) for _ in range(n)]
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice1=[int])

    def test_numpy_random_choice2(self):
        """ Check numpy.random.choice with one numpy_expr argument. """
        self.run_test("""
            def numpy_random_choice2(n, x):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = [choice(arange(11) + n) for _ in range(n)]
                return (abs(mean(a) - (5 + x)) < .05)""",
                      10 ** 5, 1, numpy_random_choice2=[int, int])

    def test_numpy_random_choice3(self):
        """ Check numpy.random.choice with int and int argument. """
        self.run_test("""
            def numpy_random_choice3(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(11, n)
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice3=[int])

    def test_numpy_random_choice4(self):
        """ Check numpy.random.choice with int and tuple argument. """
        self.run_test("""
            def numpy_random_choice4(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(11, (n, n))
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 3, numpy_random_choice4=[int])

    def test_numpy_random_choice5(self):
        """ Check numpy.random.choice with int, tuple and proba argument. """
        self.run_test("""
            def numpy_random_choice5(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(5, (n, n), True, [0.3, 0.3, 0.2, 0.1, 0.1])
                return (abs(mean(a) - 1.4) < .05)""",
                      10 ** 3, numpy_random_choice5=[int])

    def test_numpy_random_choice6(self):
        """ Check numpy.random.choice with int, int and proba argument. """
        self.run_test("""
            def numpy_random_choice6(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(5, n, True, [0.3, 0.3, 0.2, 0.1, 0.1])
                return (abs(mean(a) - 1.4) < .05)""",
                      10 ** 5, numpy_random_choice6=[int])

    def test_numpy_random_choice7(self):
        """ Check numpy.random.choice with ndarray and int argument. """
        self.run_test("""
            def numpy_random_choice7(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(11), n)
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 5, numpy_random_choice7=[int])

    def test_numpy_random_choice8(self):
        """ Check numpy.random.choice with ndarray and tuple argument. """
        self.run_test("""
            def numpy_random_choice8(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(11), (n, n))
                return (abs(mean(a) - 5) < .05)""",
                      10 ** 3, numpy_random_choice8=[int])

    def test_numpy_random_choice9(self):
        """Check numpy.random.choice with ndarray, tuple and proba argument."""
        self.run_test("""
            def numpy_random_choice9(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(5), (n, n), True, [0.3, 0.3, 0.2, 0.1, 0.1])
                return (abs(mean(a) - 1.4) < .05)""",
                      10 ** 3, numpy_random_choice9=[int])

    def test_numpy_random_choice10(self):
        """ Check numpy.random.choice with ndarray, int and proba argument. """
        self.run_test("""
            def numpy_random_choice10(n):
                from numpy.random import choice
                from numpy import mean, var, arange
                a = choice(arange(5), n, True, [0.3, 0.3, 0.2, 0.1, 0.1])
                return (abs(mean(a) - 1.4) < .05)""",
                      10 ** 5, numpy_random_choice10=[int])

    ###########################################################################
    #Tests for numpy.random.bytes
    ###########################################################################

    def test_numpy_random_bytes1(self):
        """ Check numpy.random.bytes. """
        self.run_test("""
            def numpy_random_bytes1(n):
                from numpy.random import bytes
                from numpy import mean, frombuffer, uint8, asarray
                a = bytes(n)
                return (abs(mean(asarray(frombuffer(a, uint8), dtype=float)) - 127.5) < .05)""",
                      10 ** 7, numpy_random_bytes1=[int])

    ###########################################################################
    #Tests for numpy.random.exponential
    ###########################################################################

    def test_numpy_exponential0(self):
        """ Check exponential without argument with mean and variance. """
        code = """
        def numpy_exponential0(size):
            from numpy.random import exponential
            from numpy import var, mean
            a = [exponential() for x in range(size)]
            return (abs(mean(a) -1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_exponential0=[int])

    def test_numpy_exponential0a(self):
        """ Check exponential with 1 argument with mean and variance. """
        code = """
        def numpy_exponential0a(size):
            from numpy.random import exponential
            from numpy import var, mean
            scale = 2.
            a = [exponential(scale) for x in range(size)]
            return (abs(mean(a) - scale) < 0.05 and abs(var(a) - scale**2) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_exponential0a=[int])

    def test_numpy_exponential0b(self):
        """ Check exponential with 2 argument with mean and variance. """
        code = """
        def numpy_exponential0b(size):
            from numpy.random import exponential
            from numpy import var, mean, sqrt
            scale = 2
            a = exponential(scale, size)
            return (abs(mean(a) - scale) < 0.05 and abs(var(a,ddof=1) - scale**2 ) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_exponential0b=[int])

    def test_numpy_exponential1(self):
        """ Check exponential with size argument with mean and variance."""
        code = """
        def numpy_exponential1(size):
            from numpy.random import exponential
            from numpy import var, mean
            a = exponential(size=size)
            return (abs(mean(a) -1 )< .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_exponential1=[int])

    def test_numpy_exponential2(self):
        """Check exponential with shape argument with mean and variance."""
        code = """
        def numpy_exponential2(size):
            from numpy.random import exponential
            from numpy import mean, var
            a = exponential(size=(size, size))
            return (abs(mean(a)) -1 < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_exponential2=[int])

    ###########################################################################
    #Tests for numpy.random.chisquare
    ###########################################################################

    def test_numpy_chisquare0a(self):
        """ Check chisquare with 1 argument with mean and variance. """
        code = """
        def numpy_chisquare0a(size):
            from numpy.random import chisquare
            from numpy import var, mean
            df = 3.
            a = [chisquare(df) for x in range(size)]
            return (abs(mean(a) - df) < 0.05 and abs(var(a) - 2*df) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_chisquare0a=[int])

    def test_numpy_chisquare0b(self):
        """ Check chisquare with 2 argument with mean and variance. """
        code = """
        def numpy_chisquare0b(size):
            from numpy.random import chisquare
            from numpy import var, mean, sqrt
            df = 2
            a = chisquare(df, size)
            return (abs(mean(a) - df) < 0.05 and abs(var(a) - df*2 ) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_chisquare0b=[int])

    def test_numpy_chisquare2(self):
        """Check chisquare with shape argument with mean and variance."""
        code = """
        def numpy_chisquare2(size):
            from numpy.random import chisquare
            from numpy import mean, var
            df = 1
            a = chisquare(df, size=(size, size))
            return (abs(mean(a)) - df < .05 and abs(var(a) - 2*df) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_chisquare2=[int])

    ###########################################################################
    #Tests for numpy.random.gamma
    ###########################################################################

    def test_numpy_gamma0a(self):
        """ Check gamma with 1 argument with mean and variance. """
        code = """
        def numpy_gamma0a(size):
            from numpy.random import gamma
            from numpy import var, mean
            shape = 1
            a = [gamma(3.) for x in range(size)]
            return (abs(mean(a)- shape) < 0.1 and abs(var(a) - shape) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_gamma0a=[int])

    def test_numpy_gamma0b(self):
        """ Check gamma with 2 argument with mean and variance. """
        code = """
        def numpy_gamma0b(size):
            from numpy.random import gamma
            from numpy import var, mean, sqrt
            shape, scale = 1,2
            a = gamma(shape, scale, size)
            return (abs(mean(a) - shape*scale) < 0.05 and abs(var(a) - shape*scale**2) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_gamma0b=[int])

    def test_numpy_gamma2(self):
        """Check gamma with shape argument with mean and variance."""
        code = """
        def numpy_gamma2(size):
            from numpy.random import gamma
            from numpy import mean, var
            shape = 2
            a = gamma(shape = shape, size=(size, size))
            return (abs(mean(a) - shape) < .05 and abs(var(a) - shape) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_gamma2=[int])

    ###########################################################################
    #Tests for numpy.random.weibull
    ###########################################################################

    def test_numpy_weibull0a(self):
        """ Check weibull with 1 argument with mean and variance. """
        code = """
        def numpy_weibull0a(size):
            from numpy.random import weibull
            from numpy import var, mean
            pa = 3.
            a = [weibull(pa) for x in range(size)]
            return (abs(mean(a) - pa) < 0.05 and abs(var(a) - 2*pa) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_weibull0a=[int])

    def test_numpy_weibull0b(self):
        """ Check weibull with 2 argument with mean and variance. """
        code = """
        def numpy_weibull0b(size):
            from numpy.random import weibull
            from numpy import var, mean, sqrt
            pa = 2
            a = weibull(pa, size)
            return (abs(mean(a) - pa) < 0.05 and abs(var(a) - pa*2 ) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_weibull0b=[int])

    def test_numpy_weibull2(self):
        """Check weibull with shape argument with mean and variance."""
        code = """
        def numpy_weibull2(size):
            from numpy.random import weibull
            from numpy import mean, var
            pa = 1
            a = weibull(pa, size=(size, size))
            return (abs(mean(a)) - pa < .05 and abs(var(a) - 2*pa) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_weibull2=[int])

    ###########################################################################
    #Tests for numpy.random.lognormal
    ###########################################################################

    def test_numpy_lognormal0(self):
        """ Check lognormal without argument with mean and variance. """
        code = """
        def numpy_lognormal0(size):
            from numpy.random import lognormal
            from numpy import var, mean, e
            a = [lognormal() for x in range(size)]
            m = 0
            s = 1/2
            rmean = e**(m+(s**2/2))  
            rvar = (e**(s**2) - 1)*e**(2*m+s**2) 
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_lognormal0=[int])

    def test_numpy_lognormal0a(self):
        """ Check lognormal with 1 argument with mean and variance. """
        code = """
        def numpy_lognormal0a(size):
            from numpy.random import lognormal
            from numpy import var, mean, e
            m = 0
            s = 1/5
            a = [lognormal(m) for x in range(size)]
            rmean = e**(m+(s**2/2))  
            rvar = (e**(s**2) - 1)*e**(2*m+s**2) 
            return (abs(mean(a)- rmean) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_lognormal0a=[int])

    def test_numpy_lognormal0b(self):
        """ Check lognormal with 2 argument with mean and variance. """
        code = """
        def numpy_lognormal0b(size):
            from numpy.random import lognormal
            from numpy import var, mean, e
            m = 1
            s = 1/8
            a = lognormal(m, s, size)
            rmean = e**(m+(s**2/2))  
            rvar = (e**(s**2) - 1)*e**(2*m+s**2)
            return (abs(mean(a) - rmean) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_lognormal0b=[int])

    def test_numpy_lognormal1(self):
        """ Check lognormal with size argument with mean and variance."""
        code = """
        def numpy_lognormal1(size):
            from numpy.random import lognormal
            from numpy import var, mean, e
            m = 0
            s = 1/4
            rmean = e**(m+(s**2/2))  
            rvar = (e**(s**2) - 1)*e**(2*m+s**2) 
            a = lognormal(size=size)
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_lognormal1=[int])

    def test_numpy_lognormal2(self):
        """Check lognormal with shape argument with mean and variance."""
        code = """
        def numpy_lognormal2(size):
            from numpy.random import lognormal
            from numpy import mean, var, e
            m = 2
            s = 1/2
            rmean = e**(m+(s**2/2))  
            rvar = (e**(s**2) - 1)*e**(2*m+s**2) 
            a = lognormal(size=(size, size))
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 3, numpy_lognormal2=[int])

    ###########################################################################
    #Tests for numpy.random.geometric
    ###########################################################################

    def test_numpy_geometric0a(self):
        """ Check geometric with 1 argument with mean and variance. """
        code = """
        def numpy_geometric0a(size):
            from numpy.random import geometric
            from numpy import var, mean
            a = [geometric(0.6) for x in range(size)]
            return (abs(mean(a)- 2) < .05 and abs(var(a) - 3) < 1/8)
        """
        self.run_test(code, 10 ** 6, numpy_geometric0a=[int])

    def test_numpy_geometric0b(self):
        """ Check geometric with 2 argument with mean and variance. """
        code = """
        def numpy_geometric0b(size):
            from numpy.random import geometric
            from numpy import var, mean, sqrt
            p = 0.25
            a = geometric(p, size)
            return (abs(mean(a)- 4) < 0.05 and abs(sqrt(p) - sqrt(var(a,ddof=1))) < 1/64)
        """
        self.run_test(code, 10 ** 6, numpy_geometric0b=[int])




    def test_numpy_geometric2(self):
        """Check geometric with shape argument with mean and variance."""
        code = """
        def numpy_geometric2(size):
            from numpy.random import geometric
            from numpy import mean, var
            p = 0.5
            a = geometric(p, size=(size, size))
            return (abs(mean(a)-2) < .05 and abs(var(a) - 1) < 1/8)
        """
        self.run_test(code, 10 ** 3, numpy_geometric2=[int])


    ###########################################################################
    #Tests for numpy.random.pareto
    ###########################################################################

    def test_numpy_pareto0a(self):
        """ Check pareto with 1 argument with mean and variance. """
        code = """
        def numpy_pareto0a(size):
            from numpy.random import pareto
            from numpy import var, mean
            alpha = 10
            rvar = alpha/((alpha-1)**2*(alpha-2))
            a = [pareto(alpha) for x in range(size)]
            return (abs(mean(a)- 0.5) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_pareto0a=[int])

    def test_numpy_pareto0b(self):
        """ Check pareto with 2 argument with mean and variance. """
        code = """
        def numpy_pareto0b(size):
            from numpy.random import pareto
            from numpy import var, mean, sqrt
            alpha = 6
            rvar = alpha/((alpha-1)**2*(alpha-2))
            a = pareto(alpha, size)
            return (abs(mean(a)- 0.5) < 0.05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_pareto0b=[int])

    def test_numpy_pareto2(self):
        """Check pareto with shape argument with mean and variance."""
        code = """
        def numpy_pareto2(size):
            from numpy.random import pareto
            from numpy import mean, var
            alpha = 5
            rvar = alpha/((alpha-1)**2*(alpha-2))
            a = pareto(alpha, size=(size, size))
            return (abs(mean(a)- 0.5) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_pareto2=[int])

    ###########################################################################
        #Tests for numpy.random.power
    ###########################################################################

    def test_numpy_power0a(self):
        """ Check power with 1 argument with mean and variance. """
        code = """
        def numpy_power0a(size):
            from numpy.random import power
            from numpy import var, mean
            alpha = 1
            rmean = alpha / (alpha + 1)
            rvar = alpha/((alpha+1)**2*(alpha+2))
            a = [power(alpha) for x in range(size)]
            return (abs(mean(a)- rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_power0a=[int])

    def test_numpy_power0b(self):
        """ Check power with 2 argument with mean and variance. """
        code = """
        def numpy_power0b(size):
            from numpy.random import power
            from numpy import var, mean, sqrt
            alpha = 1
            rmean = alpha / (alpha + 1)
            rvar = alpha/((alpha+1)**2*(alpha+2))
            a = power(alpha, size)
            return (abs(mean(a)- rmean) < 0.05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_power0b=[int])

    def test_numpy_power2(self):
        """Check power with shape argument with mean and variance."""
        code = """
        def numpy_power2(size):
            from numpy.random import power
            from numpy import mean, var
            alpha = 1
            rmean = alpha / (alpha + 1)
            rvar = alpha/((alpha+1)**2*(alpha+2))
            a = power(alpha, size=(size, size))
            return (abs(mean(a)- rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_power2=[int])

    ###########################################################################
    #Tests for numpy.random.rayleigh
    ###########################################################################

    def test_numpy_rayleigh0(self):
        """ Check rayleigh without argument with mean and variance. """
        code = """
        def numpy_rayleigh0(size):
            from numpy.random import rayleigh
            from numpy import var, mean, sqrt, pi
            a = [rayleigh() for x in range(size)]
            s = 2
            rmean = s*sqrt(pi/2)
            rvar = ((4-pi)/2)*s**2
            return (abs(mean(a)-rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_rayleigh0=[int])

    def test_numpy_rayleigh0a(self):
        """ Check rayleigh with 1 argument with mean and variance. """
        code = """
        def numpy_rayleigh0a(size):
            from numpy.random import rayleigh
            from numpy import var, mean, sqrt, pi
            s = 2
            a = [rayleigh(s) for x in range(size)]
            rmean = s*sqrt(pi/2)
            rvar = ((4-pi)/2)*s**2
            return (abs(mean(a)-rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_rayleigh0a=[int])

    def test_numpy_rayleigh0b(self):
        """ Check rayleigh with 2 argument with mean and variance. """
        code = """
        def numpy_rayleigh0b(size):
            from numpy.random import rayleigh
            from numpy import var, mean, sqrt, pi
            s = 2
            a = rayleigh(s, size)
            rmean = s*sqrt(pi/2)
            rvar = ((4-pi)/2)*s**2
            return (abs(mean(a)-rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_rayleigh0b=[int])

    def test_numpy_rayleigh1(self):
        """ Check rayleigh with size argument with mean and variance."""
        code = """
        def numpy_rayleigh1(size):
            from numpy.random import rayleigh
            from numpy import var, mean, sqrt, pi
            a = rayleigh(size=size)
            s = 2
            rmean = s*sqrt(pi/2)
            rvar = ((4-pi)/2)*s**2
            return (abs(mean(a)-rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_rayleigh1=[int])

    def test_numpy_rayleigh2(self):
        """Check rayleigh with shape argument with mean and variance."""
        code = """
        def numpy_rayleigh2(size):
            from numpy.random import rayleigh
            from numpy import mean, var, sqrt, pi
            a = rayleigh(size=(size, size))
            s = 2
            rmean = s*sqrt(pi/2)
            rvar = ((4-pi)/2)*s**2
            return (abs(mean(a)-rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_rayleigh2=[int])

    ###########################################################################
    #Tests for numpy.random.f
    ###########################################################################

    def test_numpy_f0a(self):
        """ Check f with 2 argument with mean and variance. """
        code = """
        def numpy_f0a(size):
            from numpy.random import f
            from numpy import var, mean
            dfnum = 50
            dfden = 50
            rmean =  dfden / (dfden - 2)
            rvar = (2 * dfden**2 *( dfnum + dfden -2))/(dfnum * (dfden -2)**2 * (dfden -4))
            a = [f(dfnum, dfden) for x in range(size)]
            return (abs(mean(a)- rmean) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_f0a=[int])

    def test_numpy_f0b(self):
        """ Check f with 2 argument with mean and variance. """
        code = """
        def numpy_f0b(size):
            from numpy.random import f
            from numpy import var, mean
            dfnum = 50
            dfden = 50
            rmean =  dfden / (dfden - 2)
            rvar = (2 * dfden**2 *( dfnum + dfden -2))/(dfnum * (dfden -2)**2 * (dfden -4))
            a = f(dfnum, dfden, size)
            return (abs(mean(a) - rmean) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_f0b=[int])

    def test_numpy_f2(self):
        """Check f with shape argument with mean and variance."""
        code = """
        def numpy_f2(size):
            from numpy.random import f
            from numpy import mean, var
            dfnum = 50
            dfden = 50
            rmean =  dfden / (dfden - 2)
            rvar = (2 * dfden**2 *( dfnum + dfden -2))/(dfnum * (dfden -2)**2 * (dfden -4))
            a = f(dfnum, dfden, size=(size, size))
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 3, numpy_f2=[int])

    ###########################################################################
    #Tests for numpy.random.negative_binomial
    ###########################################################################

    def test_numpy_negative_binomial0a(self):
        """ Check negative_binomial with 1 argument with mean and variance. """
        code = """
        def numpy_negative_binomial0a(size):
            from numpy.random import negative_binomial
            from numpy import var, mean
            n = 1000
            p = .1
            rmean = (n*(1-p))/p
            rvar = (n*(1-p))/p**2
            a = [negative_binomial(n,p) for x in range(size)]
            return (abs(mean(a)- rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_negative_binomial0a=[int])

    def test_numpy_negative_binomial0b(self):
        """ Check negative_binomial with 2 argument with mean and variance. """
        code = """
        def numpy_negative_binomial0b(size):
            from numpy.random import negative_binomial
            from numpy import var, mean
            n = 1000
            p = .1
            rmean = (n*(1-p))/p
            rvar = (n*(1-p))/p**2
            a = negative_binomial(n, p, size)
            return (abs(mean(a)- rmean) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_negative_binomial0b=[int])

    def test_numpy_negative_binomial2(self):
        """Check negative_binomial with shape argument with mean and variance."""
        code = """
        def numpy_negative_binomial2(size):
            from numpy.random import negative_binomial
            from numpy import mean, var
            n = 1000
            p = .1
            rmean = (n*(1-p))/p
            rvar = (n*(1-p))/p**2
            a = negative_binomial(n, p , size=(size, size))
            print(mean(a), rmean)
            return (abs(mean(a)- rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 3, numpy_negative_binomial2=[int])

    ###########################################################################
    #Tests for numpy.random.standard_exponential
    ###########################################################################

    def test_numpy_standard_exponential0(self):
        """ Check standard_exponential without argument with mean and variance. """
        code = """
        def numpy_standard_exponential0(size):
            from numpy.random import standard_exponential
            from numpy import var, mean
            a = [standard_exponential() for x in range(size)]
            return (abs(mean(a) - 1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_exponential0=[int])

    def test_numpy_standard_exponential1(self):
        """ Check standard_exponential with size argument with mean and variance."""
        code = """
        def numpy_standard_exponential1(size):
            from numpy.random import standard_exponential
            from numpy import var, mean
            a = standard_exponential(size)
            return (abs(mean(a) - 1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_exponential1=[int])

    def test_numpy_standard_exponential2(self):
        """Check standard_exponential with shape argument with mean and variance."""
        code = """
        def numpy_standard_exponential2(size):
            from numpy.random import standard_exponential
            from numpy import mean, var
            a = standard_exponential((size, size))
            return (abs(mean(a) - 1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_standard_exponential2=[int])

    ###########################################################################
    #Tests for numpy.random.standard_gamma
    ###########################################################################

    def test_numpy_standard_gamma0(self):
        """ Check standard_gamma without argument with mean and variance. """
        code = """
        def numpy_standard_gamma0(size):
            from numpy.random import standard_gamma
            from numpy import var, mean
            a = [standard_gamma(1) for x in range(size)]
            return (abs(mean(a) - 1) < .05 and abs(var(a) - 1) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_gamma0=[int])

    def test_numpy_standard_gamma1(self):
        """ Check standard_gamma with size argument with mean and variance."""
        code = """
        def numpy_standard_gamma1(size):
            from numpy.random import standard_gamma
            from numpy import var, mean
            a = standard_gamma(2, size)
            return (abs(mean(a) - 2) < .05 and abs(var(a) - 2) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_standard_gamma1=[int])

    def test_numpy_standard_gamma2(self):
        """Check standard_gamma with shape argument with mean and variance."""
        code = """
        def numpy_standard_gamma2(size):
            from numpy.random import standard_gamma
            from numpy import mean, var
            a = standard_gamma(3, (size, size))
            return (abs(mean(a) - 3) < .05 and abs(var(a) - 3) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_standard_gamma2=[int])

    ###########################################################################
    #Tests for numpy.random.gumbel
    ###########################################################################

    def test_numpy_gumbel0(self):
        """ Check gumbel without argument with mean and variance. """
        code = """
        def numpy_gumbel0(size):
            from numpy.random import gumbel
            from numpy import var, mean, pi
            u = 0.
            rmean = u + 0.57721
            rvar = (pi**2/6)
            a = [gumbel() for x in range(size)]
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_gumbel0=[int])

    def test_numpy_gumbel0a(self):
        """ Check gumbel with 1 argument with mean and variance. """
        code = """
        def numpy_gumbel0a(size):
            from numpy.random import gumbel
            from numpy import var, mean, pi
            u = 1
            rmean = u + 0.57721
            rvar = (pi**2/6)
            a = [gumbel(u) for x in range(size)]
            return (abs(mean(a) - rmean ) < 0.05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_gumbel0a=[int])

    def test_numpy_gumbel0b(self):
        """ Check gumbel with 2 argument with mean and variance. """
        code = """
        def numpy_gumbel0b(size):
            from numpy.random import gumbel
            from numpy import var, mean, pi
            u = 1.5
            s = 2
            rmean = u + 0.57721*s
            rvar = (pi**2/6)*s**2
            a = gumbel(u, s, size)
            return (abs(mean(a) - rmean) < 0.05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_gumbel0b=[int])

    def test_numpy_gumbel1(self):
        """ Check gumbel with size argument with mean and variance."""
        code = """
        def numpy_gumbel1(size):
            from numpy.random import gumbel
            from numpy import var, mean
            from numpy import var, mean, pi
            u = 0.
            s = 1
            rmean = u + 0.57721*s
            rvar = (pi**2/6)*s**2
            a = gumbel(size=size)
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_gumbel1=[int])

    def test_numpy_gumbel2(self):
        """Check gumbel with shape argument with mean and variance."""
        code = """
        def numpy_gumbel2(size):
            from numpy.random import gumbel
            from numpy import mean, var
            from numpy import var, mean, pi
            u = 0
            s = 1
            rmean = u + 0.57721*s
            rvar = (pi**2/6)*s**2
            a = gumbel(size=(size, size))
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_gumbel2=[int])

    ###########################################################################
    #Tests for numpy.random.logistic
    ###########################################################################

    def test_numpy_logistic0(self):
        """ Check logistic without argument with mean and variance. """
        code = """
        def numpy_logistic0(size):
            from numpy.random import logistic
            from numpy import var, mean, pi
            u = 0.
            rmean = u
            rvar = (pi**2/3)
            a = [logistic() for x in range(size)]
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_logistic0=[int])

    def test_numpy_logistic0a(self):
        """ Check logistic with 1 argument with mean and variance. """
        code = """
        def numpy_logistic0a(size):
            from numpy.random import logistic
            from numpy import var, mean, pi
            u = 2
            rmean = u
            rvar = (pi**2/3)
            a = [logistic(u) for x in range(size)]
            return (abs(mean(a) - rmean ) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_logistic0a=[int])

    def test_numpy_logistic0b(self):
        """ Check logistic with 2 argument with mean and variance. """
        code = """
        def numpy_logistic0b(size):
            from numpy.random import logistic
            from numpy import var, mean, pi
            u = 2.
            s = 2
            rmean = u
            rvar = ((s**2*pi**2)/3)
            a = logistic(u, s, size)
            return (abs(mean(a) - rmean) < 0.1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_logistic0b=[int])

    def test_numpy_logistic1(self):
        """ Check logistic with size argument with mean and variance."""
        code = """
        def numpy_logistic1(size):
            from numpy.random import logistic
            from numpy import var, mean
            from numpy import var, mean, pi
            u = 0.
            s = 1
            rmean = u
            rvar = ((s**2*pi**2)/3)
            a = logistic(size=size)
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 6, numpy_logistic1=[int])

    def test_numpy_logistic2(self):
        """Check logistic with shape argument with mean and variance."""
        code = """
        def numpy_logistic2(size):
            from numpy.random import logistic
            from numpy import mean, var
            from numpy import var, mean, pi
            u = 0
            s = 1
            rmean = u
            rvar = ((s**2*pi**2)/3)
            a = logistic(size=(size, size))
            return (abs(mean(a) - rmean) < .1 and abs(var(a) - rvar) < .1)
        """
        self.run_test(code, 10 ** 3, numpy_logistic2=[int])

    ###########################################################################
    #Tests for numpy.random.laplace
    ###########################################################################

    def test_numpy_laplace0(self):
        """ Check laplace without argument with mean and variance. """
        code = """
        def numpy_laplace0(size):
            from numpy.random import laplace
            from numpy import var, mean, pi
            u = 0.
            s = 1
            rmean = u
            rvar = 2*s**2
            a = [laplace() for x in range(size)]
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_laplace0=[int])

    def test_numpy_laplace0a(self):
        """ Check laplace with 1 argument with mean and variance. """
        code = """
        def numpy_laplace0a(size):
            from numpy.random import laplace
            from numpy import var, mean, pi
            u = 2
            s = 1
            rmean = u
            rvar = 2*s**2
            a = [laplace(u) for x in range(size)]
            return (abs(mean(a) - rmean ) < 0.05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_laplace0a=[int])

    def test_numpy_laplace0b(self):
        """ Check laplace with 2 argument with mean and variance. """
        code = """
        def numpy_laplace0b(size):
            from numpy.random import laplace
            from numpy import var, mean, pi
            u = 2.
            s = 2
            rmean = u
            rvar = 2*s**2
            a = laplace(u, s, size)
            return (abs(mean(a) - rmean) < 0.05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_laplace0b=[int])

    def test_numpy_laplace1(self):
        """ Check laplace with size argument with mean and variance."""
        code = """
        def numpy_laplace1(size):
            from numpy.random import laplace
            from numpy import var, mean
            from numpy import var, mean, pi
            u = 0.
            s = 1
            rmean = u
            rvar = 2*s**2
            a = laplace(size=size)
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 6, numpy_laplace1=[int])

    def test_numpy_laplace2(self):
        """Check laplace with shape argument with mean and variance."""
        code = """
        def numpy_laplace2(size):
            from numpy.random import laplace
            from numpy import mean, var
            from numpy import var, mean, pi
            u = 0
            s = 1
            rmean = u
            rvar = 2*s**2
            a = laplace(size=(size, size))
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_laplace2=[int])

    ###########################################################################
    #Tests for numpy.random.logseries
    ###########################################################################

    def test_numpy_logseries0(self):
        """ Check logseries without argument with mean and variance. """
        code = """
        def numpy_logseries0(size):
            from numpy.random import logseries
            from numpy import var, mean, log
            s = 0.5
            rmean = s / (log(1 - s)*(s - 1))
            rvar = -(s*(s+log(1-s)))/((s - 1)**2*(log(1-s))**2)      
            a = [logseries(s) for x in range(size)]
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_logseries0=[int])

    def test_numpy_logseries1(self):
        """ Check logseries with size argument with mean and variance."""
        code = """
        def numpy_logseries1(size):
            from numpy.random import logseries
            from numpy import var, mean, log
            s = 0.25
            rmean = s / (log(1 - s)*(s - 1))
            rvar = -(s*(s+log(1-s)))/((s - 1)**2*(log(1-s))**2)             
            a = logseries(s, size)
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 5, numpy_logseries1=[int])

    def test_numpy_logseries2(self):
        """Check logseries with shape argument with mean and variance."""
        code = """
        def numpy_logseries2(size):
            from numpy.random import logseries
            from numpy import mean, var, log
            s = 0.2
            rmean = s / (log(1 - s)*(s - 1))
            rvar = -(s*(s+log(1-s)))/((s - 1)**2*(log(1-s))**2)           
            a = logseries(s, (size, size))
            return (abs(mean(a) - rmean) < .05 and abs(var(a) - rvar) < .05)
        """
        self.run_test(code, 10 ** 3, numpy_logseries2=[int])

    ###########################################################################
    # Tests for numpy.random.uniform
    ###########################################################################

    def test_numpy_uniform_no_arg(self):
        """ Check logseries without argument with mean and variance. """
        code = """
        def numpy_uniform_no_arg(size):
            import numpy as np
            from numpy.random import uniform
            low, high = 0.0, 1.0
            a = np.array([uniform() for _ in range(size)])
            rmean = 0.5 * (low + high)
            rvar = (high - low) ** 2 / 12
            cond_mean = (a.mean() - rmean) / rmean < 0.05
            cond_var = (np.var(a) - rvar) / rvar < 0.05
            return cond_mean and cond_var
        """
        self.run_test(code, 4000, numpy_uniform_no_arg=[int])

    def test_numpy_uniform_size_int(self):
        """ Check logseries with arguments with mean and variance. """
        code = """
        def numpy_uniform_size_int(size):
            import numpy as np
            from numpy.random import uniform
            low, high = 0., 1234.
            rmean = 0.5 * (low + high)
            rvar = (high - low) ** 2 / 12
            a = uniform(low, high, size)
            cond_mean = (a.mean() - rmean) / rmean < 0.05
            cond_var = (np.var(a) - rvar) / rvar < 0.05
            return cond_mean and cond_var
        """
        self.run_test(code, 4000, numpy_uniform_size_int=[int])


    def test_numpy_uniform_size_tuple(self):
        """ Check logseries with arguments with mean and variance. """
        code = """
        def numpy_uniform_size_tuple(size):
            import numpy as np
            from numpy.random import uniform
            low, high = -987., 12345.
            rmean = 0.5 * (low + high)
            rvar = (high - low) ** 2 / 12
            a = uniform(low, high, (size, size))
            cond_mean = (a.mean() - rmean) / rmean < 0.05
            cond_var = (np.var(a) - rvar) / rvar < 0.05
            return cond_mean and cond_var
        """
        self.run_test(code, 70, numpy_uniform_size_tuple=[int])

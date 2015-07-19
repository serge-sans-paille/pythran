""" Check the random module behavior. """
from test_env import TestEnv


@TestEnv.module
class TestRandom(TestEnv):

    """
    Check implementation for usual random functions.

    Functions are:
    - random.random
    - random.gauss
    - random.uniform
    - random.expovariate
    - random.randrange
    - random.randint
    - random.sample
    - random.choice
    - random.seed
    """

    def test_random(self):
        """ Check random.random is a uniform distributed generator. """
        self.run_test("""
        def random(n):
            from random import random
            s = sum(random() for x in range(n))
            return abs(s / n - 0.5) < .05""",
                      10 ** 5, random=[int])

    def test_gauss(self):
        """ Check random.gauss distribution. """
        self.run_test("""
        def gauss(n, mu, sigma):
            from random import gauss
            s = sum(gauss(mu,sigma) for x in range(n))
            return abs(s / n - mu) / sigma < .05""",
                      10 ** 6, 5, 2, gauss=[int, int, int])

    def test_uniform(self):
        """ Check uniform distribution between b and e. """
        self.run_test("""
        def uniform(n, b, e):
            from random import uniform
            s = sum(uniform(b, e) for x in range(n))
            return abs(s / n - (b + e) * .5) < .05""",
                      10 ** 6, 5, 25, uniform=[int, int, int])

    def test_expovariate(self):
        """ Check expovariate distribution. """
        self.run_test("""
        def expovariate(n, l):
            from random import expovariate
            s = sum(expovariate(l) for x in range(n))
            return abs(s / n - 1 / l) < .05""",
                      10 ** 6, 5., expovariate=[int, float])

    def test_randrange0(self):
        """ Check randrange with only end value. """
        self.run_test("""
        def randrange0(n):
            from random import randrange
            s = sum(randrange(n) for x in range(n))
            return abs(s / float(n * n) - .5) < .05""",
                      10 ** 5, randrange0=[int])

    def test_randrange1(self):
        """ Check randrange with begin and end. """
        self.run_test("""
        def randrange1(n):
            from random import randrange
            s = sum(randrange(-n, n + 1) for x in range(n))
            return abs(s / float(n * n)) < .05""", 10 ** 5, randrange1=[int])

    def test_randrange2(self):
        """ Check randrange step generated values. """
        self.run_test("""
        def randrange2(n):
            from random import randrange
            return all(randrange(3, n, 3) % 3 == 0 for x in range(n))""",
                      10 ** 4, randrange2=[int])

    def test_randint(self):
        """ Check randint distribution. """
        self.run_test("""
        def randint(n):
            from random import randint
            s = sum(randint(0,100) for x in range(n))
            return abs(s / float(n * 100) - 1 / 2.) < .05""",
                      10 ** 6, randint=[int])

    def test_sample_(self):
        """ Check sample picked values distribution. """
        self.run_test("""
        def sample(n, k):
            from random import sample
            s = sum(sum(sample(range(100), k)) for x in range(n))
            return abs(s / float(k * n) - 99 / 2.) < .05""",
                      10 ** 6, 4, sample=[int, int])

    def test_shuffle1(self):
        """ Check shuffling with default random function. """
        self.run_test("""
        def shuffle1(n):
            from random import shuffle
            r = range(n)
            shuffle(r)
            return r != range(n) and sorted(r) == range(n)""",
                      10, shuffle1=[int])

    def test_shuffle2(self):
        """ Check shuffling with custom function. """
        self.run_test("""
        def shuffle2(n):
            from random import shuffle
            r = range(n)
            shuffle(r, lambda: 0)
            return r != range(n) and sorted(r) == range(n)""",
                      10 ** 4, shuffle2=[int])

    def test_shuffle3(self):
        """ Check shuffling with random function. """
        self.run_test("""
        def shuffle3(n):
            from random import shuffle, random
            r = range(n)
            shuffle(r, random)
            return r != range(n) and sorted(r) == range(n)""",
                      10 ** 4, shuffle3=[int])

    def test_choice(self):
        """ Check choice picked values distribution. """
        self.run_test("""
        def choice(n):
            from random import choice
            s = sum(choice(range(100)) for x in xrange(n))
            return abs(s / float(n) - 99 / 2.) < .05""",
                      10 ** 7, choice=[int])

    def test_random_seed(self):
        """ Check seeded random generate always the same value. """
        self.run_test("""
        def random_seed():
            from random import random, seed
            seed(1)
            a = random()
            seed(1)
            b = random()
            return a == b""", random_seed=[])

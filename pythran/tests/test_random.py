from test_env import TestEnv

class TestRandom(TestEnv):

    def test_random_(self):
        self.run_test("def random_(n): from random import random ; s= sum(random() for x in range(n)) ; return abs(s/n -.5) < .05", 10**5, random_=[int])

    def test_gauss_(self):
        self.run_test("def gauss_(n, mu, sigma): from random import gauss ; s= sum(gauss(mu,sigma) for x in range(n)) ; return abs(s/n -mu)/sigma < .05", 10**6, 5, 2, gauss_=[int, int, int])

    def test_uniform_(self):
        self.run_test("def uniform_(n,b,e): from random import uniform ; s= sum(uniform(b,e) for x in range(n)) ; return abs(s/n - (b+e)*.5) < .05", 10**6, 5, 25, uniform_=[int, int, int])

    def test_expovariate_(self):
        self.run_test("def expovariate_(n,l): from random import expovariate ; s= sum(expovariate(l) for x in range(n)) ; return abs(s/n - 1/l) < .05", 10**6, 5., expovariate_=[int,  float])

    def test_randrange0(self):
        self.run_test("def randrange0(n): from random import randrange ; s= sum(randrange(n) for x in range(n)) ; return abs(s/n - n/2) < .05", 10**7,  randrange0=[int])

    def test_randrange1(self):
        self.run_test("def randrange1(n): from random import randrange ; s= sum(randrange(-n,n) for x in range(n)) ; return abs(s/n) < .05", 10**7,  randrange1=[int])

    def test_randrange2(self):
        self.run_test("def randrange2(n): from random import randrange ; s= [randrange(3,n,3)%3==0 for x in range(n)] ; return all(s)" , 10**4,  randrange2=[int])

    def test_randint(self):
        self.run_test("def randint_(n): from random import randint ; s= [randint(0,n/1000) for x in range(n)] ; return abs(sum(s)/n) < .05, len(set(s))", 10**6,  randint_=[int])

    def test_sample_(self):
        self.run_test("def sample_(n,k): from random import sample ; s = sum(sum(sample(range(n),k)) for x in range(n)) ; return abs(s/float(n*n)) < .05  ", 10**4, 4, sample_=[int, int])

    def test_choice(self):
        self.run_test("def choice_(n): from random import choice ; s= sum(choice(range(n)) for x in xrange(n)) ; return abs(s/n - n/2) < .05", 10**5,  choice_=[int])

    def test_random_seed(self):
        self.run_test("def random_seed(): from random import random, seed ; seed(1) ; a = random() ; seed(1); b = random(); return a == b", random_seed=[])

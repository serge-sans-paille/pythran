from pythran.tests import TestEnv

class TestBase(TestEnv):

    def test_rec0(self):
        self.run_test("""
def test_rec0(n):
  z = 1
  if n > 1:
    z = n * test_rec0(n-1)
  return z""", 5, test_rec0=[int])

    def test_rec1(self):
        self.run_test("""
def test_rec1(n):
  z = 1
  while n > 1:
    z = n * test_rec1(n-1)
    n -= 1
  return z""", 5, test_rec1=[int])

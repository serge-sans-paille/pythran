from test_env import TestEnv

class TestMath(TestEnv):

    def test_cos_(self):
        self.run_test("def cos_(a):\n from math import cos\n return cos(a)", 1, cos_=[int])

    def test_exp_(self):
        self.run_test("def exp_(a):\n from math import exp\n return exp(a)", 1, exp_=[int])

    def test_sqrt_(self):
        self.run_test("def sqrt_(a):\n from math import sqrt\n return sqrt(a)", 1, sqrt_=[int])

    def test_log10_(self):
        self.run_test("def log10_(a):\n from math import log10\n return log10(a)", 1, log10_=[int])

    def test_isnan_(self):
        self.run_test("def isnan_(a):\n from math import isnan\n return isnan(a)", 1, isnan_=[int])

    def test_pi_(self):
        self.run_test("def pi_():\n from math import pi\n return pi", pi_=[])

    def test_e_(self):
        self.run_test("def e_():\n from math import e\n return e", e_=[])


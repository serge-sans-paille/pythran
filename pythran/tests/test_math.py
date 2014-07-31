from test_env import TestEnv


@TestEnv.module
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

    def test_asinh_(self):
        self.run_test("def asinh_(a):\n from math import asinh\n return asinh(a)",1, asinh_=[float])

    def test_atanh_(self):
        self.run_test("def atanh_(a):\n from math import atanh\n return atanh(a)",.1, atanh_=[float])

    def test_acosh_(self):
        self.run_test("def acosh_(a):\n from math import acosh\n return acosh(a)",1, acosh_=[int])

    def test_radians_(self):
        self.run_test("def radians_(a):\n from math import radians\n return radians(a)",1, radians_=[int])

    def test_degrees_(self):
        self.run_test("def degrees_(a):\n from math import degrees\n return degrees(a)",1, degrees_=[int])

    def test_hypot_(self):
        self.run_test("def hypot_(a,b):\n from math import hypot\n return hypot(a,b)",3,4, hypot_=[int,int])

    def test_tanh_(self):
        self.run_test("def tanh_(a):\n from math import tanh\n return tanh(a)",1, tanh_=[int])

    def test_cosh_(self):
        self.run_test("def cosh_(a):\n from math import cosh\n return cosh(a)",1, cosh_=[float])

    def test_sinh_(self):
        self.run_test("def sinh_(a):\n from math import sinh\n return sinh(a)",1, sinh_=[int])

    def test_atan_(self):
        self.run_test("def atan_(a):\n from math import atan\n return atan(a)",1, atan_=[int])

    def test_atan2_(self):
        self.run_test("def atan2_(a,b):\n from math import atan2\n return atan2(a,b)",2,4, atan2_=[int,int])

    def test_asin_(self):
        self.run_test("def asin_(a):\n from math import asin\n return asin(a)",1, asin_=[int])

    def test_tan_(self):
        self.run_test("def tan_(a):\n from math import tan\n return tan(a)",1, tan_=[int])

    def test_log_(self):
        self.run_test("def log_(a):\n from math import log\n return log(a)",1, log_=[int])

    def test_log1p_(self):
        self.run_test("def log1p_(a):\n from math import log1p\n return log1p(a)",1, log1p_=[int])

    def test_expm1_(self):
        self.run_test("def expm1_(a):\n from math import expm1\n return expm1(a)",1, expm1_=[int])

    def test_ldexp_(self):
        self.run_test("def ldexp_(a,b):\n from math import ldexp\n return ldexp(a,b)",3,4, ldexp_=[int,int])

    def test_fmod_(self):
        self.run_test("def fmod_(a,b):\n from math import fmod\n return fmod(a,b)",5.3,2, fmod_=[float,int])

    def test_fabs_(self):
        self.run_test("def fabs_(a):\n from math import fabs\n return fabs(a)",1, fabs_=[int])

    def test_copysign_(self):
        self.run_test("def copysign_(a,b):\n from math import copysign\n return copysign(a,b)",2,-2, copysign_=[int,int])

    def test_acos_(self):
        self.run_test("def acos_(a):\n from math import acos\n return acos(a)",1, acos_=[int])

    def test_erf_(self):
        self.run_test("def erf_(a):\n from math import erf\n return erf(a)",1, erf_=[int])

    def test_erfc_(self):
        self.run_test("def erfc_(a):\n from math import erfc\n return erfc(a)",1, erfc_=[int])

    def test_gamma_(self):
        self.run_test("def gamma_(a):\n from math import gamma\n return gamma(a)",1, gamma_=[int])

    def test_lgamma_(self):
        self.run_test("def lgamma_(a):\n from math import lgamma\n return lgamma(a)",1, lgamma_=[int])

    def test_trunc_(self):
        self.run_test("def trunc_(a):\n from math import trunc\n return trunc(a)",1, trunc_=[int])

    def test_factorial_(self):
        self.run_test("def factorial_(a):\n from math import factorial\n return factorial(a)",2, factorial_=[int])

    def test_modf_(self):
        self.run_test("def modf_(a):\n from math import modf\n return modf(a)",2, modf_=[int])

    def test_frexp_(self):
        self.run_test("def frexp_(a):\n from math import frexp\n return frexp(a)",2.2, frexp_=[float])

    def test_isinf_(self):
        self.run_test("def isinf_(a):\n from math import isinf\n n=1\n while not isinf(a):\n  a=a*a\n  n+=1\n return isinf(a)", 2., isinf_=[float])

import unittest
from test_env import TestEnv

class TestLong(TestEnv):
    def test_cos_(self):
        self.run_test("def cos_(a):\n from math import cos\n return cos(a)", 1L, cos_=[long])

    def test_exp_(self):
        self.run_test("def exp_(a):\n from math import exp\n return exp(a)", 1L, exp_=[long])

    def test_sqrt_(self):
        self.run_test("def sqrt_(a):\n from math import sqrt\n return sqrt(a)", 1L, sqrt_=[long])

    def test_log10_(self):
        self.run_test("def log10_(a):\n from math import log10\n return log10(a)", 1L, log10_=[long])

    def test_isnan_(self):
        self.run_test("def isnan_(a):\n from math import isnan\n return isnan(a)", 1L, isnan_=[long])

    def test_asinh_(self):
        self.run_test("def asinh_(a):\n from math import asinh\n return asinh(a)",1L, asinh_=[long])

    def test_atanh_(self):
        self.run_test("def atanh_(a):\n from math import atanh\n return atanh(a)",0L, atanh_=[long])

    def test_acosh_(self):
        self.run_test("def acosh_(a):\n from math import acosh\n return acosh(a)",1L, acosh_=[long])

    def test_radians_(self):
        self.run_test("def radians_(a):\n from math import radians\n return radians(a)",1L, radians_=[long])

    def test_degrees_(self):
        self.run_test("def degrees_(a):\n from math import degrees\n return degrees(a)",1L, degrees_=[long])

#    def test_hypot_(self):
#        self.run_test("def hypot_(a,b):\n from math import hypot\n return hypot(a,b)",3L,4, hypot_=[long,int])

    def test_tanh_(self):
        self.run_test("def tanh_(a):\n from math import tanh\n return tanh(a)",1L, tanh_=[long])

    def test_cosh_(self):
        self.run_test("def cosh_(a):\n from math import cosh\n return cosh(a)",1L, cosh_=[long])

    def test_sinh_(self):
        self.run_test("def sinh_(a):\n from math import sinh\n return sinh(a)",1L, sinh_=[long])

    def test_atan_(self):
        self.run_test("def atan_(a):\n from math import atan\n return atan(a)",1L, atan_=[long])

#    def test_atan2_(self):
#        self.run_test("def atan2_(a,b):\n from math import atan2\n return atan2(a,b)",2,4L, atan2_=[int,long])

    def test_asin_(self):
        self.run_test("def asin_(a):\n from math import asin\n return asin(a)",1L, asin_=[long])

    def test_tan_(self):
        self.run_test("def tan_(a):\n from math import tan\n return tan(a)",1L, tan_=[long])

    def test_log_(self):
        self.run_test("def log_(a):\n from math import log\n return log(a)",1L, log_=[long])

    def test_log1p_(self):
        self.run_test("def log1p_(a):\n from math import log1p\n return log1p(a)",1L, log1p_=[long])

    def test_expm1_(self):
        self.run_test("def expm1_(a):\n from math import expm1\n return expm1(a)",1L, expm1_=[long])

    def test_ldexp_(self):
        self.run_test("def ldexp_(a,b):\n from math import ldexp\n return ldexp(a,b)",3L,4, ldexp_=[long,int])

    def test_fmod_(self):
        self.run_test("def fmod_(a,b):\n from math import fmod\n return fmod(a,b)",5.3,2L, fmod_=[float,long])

    def test_fabs_(self):
        self.run_test("def fabs_(a):\n from math import fabs\n return fabs(a)",1L, fabs_=[long])

    def test_copysign_(self):
        self.run_test("def copysign_(a,b):\n from math import copysign\n return copysign(a,b)",2,-2L, copysign_=[int,long])

    def test_acos_(self):
        self.run_test("def acos_(a):\n from math import acos\n return acos(a)",1L, acos_=[long])

    def test_erf_(self):
        self.run_test("def erf_(a):\n from math import erf\n return erf(a)",1L, erf_=[long])

    def test_erfc_(self):
        self.run_test("def erfc_(a):\n from math import erfc\n return erfc(a)",1L, erfc_=[long])

    def test_gamma_(self):
        self.run_test("def gamma_(a):\n from math import gamma\n return gamma(a)",1L, gamma_=[long])

    def test_lgamma_(self):
        self.run_test("def lgamma_(a):\n from math import lgamma\n return lgamma(a)",1L, lgamma_=[long])

    def test_trunc_(self):
        self.run_test("def trunc_(a):\n from math import trunc\n return trunc(a)",1L, trunc_=[long])

    def test_factorial_(self):
        self.run_test("def factorial_(a):\n from math import factorial\n return factorial(a)",2L, factorial_=[long])

    def test_modf_(self):
        self.run_test("def modf_(a):\n from math import modf\n return modf(a)",2L, modf_=[long])

    def test_frexp_(self):
        self.run_test("def frexp_(a):\n from math import frexp\n return frexp(a)",2L, frexp_=[long])

    def test_isinf_(self):
        self.run_test("def isinf_(a):\n from math import isinf\n return isinf(a)", 2L, isinf_=[long])

if __name__ == '__main__':
    unittest.main()
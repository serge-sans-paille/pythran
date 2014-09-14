import unittest
from test_env import TestEnv
import numpy


@TestEnv.module
class TestNumpyUFuncUnary(TestEnv):
    def test_numpy_pow0(self):
        self.run_test('def numpy_pow0(a): return a ** 2',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_pow0=[numpy.array([[int]])])

    def test_numpy_pow1(self):
        self.run_test('def numpy_pow1(a): return a ** 2',
                      numpy.arange(100, dtype=float).reshape((10, 10)),
                      numpy_pow1=[numpy.array([[float]])])

    def test_numpy_pow2(self):
        self.run_test('def numpy_pow2(a): return a ** 2.2',
                      numpy.arange(100, dtype=float).reshape((10, 10)),
                      numpy_pow2=[numpy.array([[float]])])

    def test_add0(self):
        self.run_test("def np_add0(a, b): return a + b", numpy.ones(10), numpy.ones(10), np_add0=[numpy.array([float]), numpy.array([float])])

    def test_add1(self):
        self.run_test("def np_add1(a, b): return a + b + a", numpy.ones(10), numpy.ones(10), np_add1=[numpy.array([float]), numpy.array([float])])

    def test_add2(self):
        self.run_test("def np_add2(a, b): return a + b + 1", numpy.ones(10), numpy.ones(10), np_add2=[numpy.array([float]), numpy.array([float])])

    def test_add3(self):
        self.run_test("def np_add3(a, b): return 1. + a + b + 1.", numpy.ones(10), numpy.ones(10), np_add3=[numpy.array([float]), numpy.array([float])])

    def test_add4(self):
        self.run_test("def np_add4(a, b): return ( a + b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_add4=[numpy.array([float]), numpy.array([float])])

    def test_add5(self):
        self.run_test("def np_add5(a, b): return (-a) + (-b)", numpy.ones(10), numpy.ones(10), np_add5=[numpy.array([float]), numpy.array([float])])

    def test_sub0(self):
        self.run_test("def np_sub0(a, b): return a - b", numpy.ones(10), numpy.ones(10), np_sub0=[numpy.array([float]), numpy.array([float])])

    def test_sub1(self):
        self.run_test("def np_sub1(a, b): return a - b - a", numpy.ones(10), numpy.ones(10), np_sub1=[numpy.array([float]), numpy.array([float])])

    def test_sub2(self):
        self.run_test("def np_sub2(a, b): return a - b - 1", numpy.ones(10), numpy.ones(10), np_sub2=[numpy.array([float]), numpy.array([float])])

    def test_sub3(self):
        self.run_test("def np_sub3(a, b): return 1. - a - b - 1.", numpy.ones(10), numpy.ones(10), np_sub3=[numpy.array([float]), numpy.array([float])])

    def test_sub4(self):
        self.run_test("def np_sub4(a, b): return ( a - b ) - ( a - b )", numpy.ones(10), numpy.ones(10), np_sub4=[numpy.array([float]), numpy.array([float])])

    def test_addsub0(self):
        self.run_test("def np_addsub0(a, b): return a - b + a", numpy.ones(10), numpy.ones(10), np_addsub0=[numpy.array([float]), numpy.array([float])])

    def test_addsub1(self):
        self.run_test("def np_addsub1(a, b): return a + b - a", numpy.ones(10), numpy.ones(10), np_addsub1=[numpy.array([float]), numpy.array([float])])

    def test_addsub2(self):
        self.run_test("def np_addsub2(a, b): return a + b - 1", numpy.ones(10), numpy.ones(10), np_addsub2=[numpy.array([float]), numpy.array([float])])

    def test_addsub3(self):
        self.run_test("def np_addsub3(a, b): return 1. + a - b + 1.", numpy.ones(10), numpy.ones(10), np_addsub3=[numpy.array([float]), numpy.array([float])])

    def test_addsub4(self):
        self.run_test("def np_addsub4(a, b): return ( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addsub4=[numpy.array([float]), numpy.array([float])])

    def test_addcossub0(self):
        self.run_test("def np_addcossub0(a, b): from numpy import cos ; return a - b + cos(a)", numpy.ones(10), numpy.ones(10), np_addcossub0=[numpy.array([float]), numpy.array([float])])

    def test_addcossub1(self):
        self.run_test("def np_addcossub1(a, b): from numpy import cos ; return a + cos(b - a)", numpy.ones(10), numpy.ones(10), np_addcossub1=[numpy.array([float]), numpy.array([float])])

    def test_addcossub2(self):
        self.run_test("def np_addcossub2(a, b): from numpy import cos ; return a + cos(b - 1)", numpy.ones(10), numpy.ones(10), np_addcossub2=[numpy.array([float]), numpy.array([float])])

    def test_addcossub3(self):
        self.run_test("def np_addcossub3(a, b): from numpy import cos ; return cos(1. + a - b + cos(1.))", numpy.ones(10), numpy.ones(10), np_addcossub3=[numpy.array([float]), numpy.array([float])])

    def test_addcossub4(self):
        self.run_test("def np_addcossub4(a, b): from numpy import cos ; return cos( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addcossub4=[numpy.array([float]), numpy.array([float])])

    def test_sin0(self):
        self.run_test("def np_sin0(a, b): from numpy import sin ; return sin(a) + b", numpy.ones(10), numpy.ones(10), np_sin0=[numpy.array([float]), numpy.array([float])])

    def test_tan0(self):
        self.run_test("def np_tan0(a, b): from numpy import tan ; return tan(a - b)", numpy.ones(10), numpy.ones(10), np_tan0=[numpy.array([float]), numpy.array([float])])

    def test_arccos0(self):
        self.run_test("def np_arccos0(a, b): from numpy import arccos ; return arccos(a - b) + 1", numpy.ones(10), numpy.ones(10), np_arccos0=[numpy.array([float]), numpy.array([float])])

    def test_arcsin0(self):
        self.run_test("def np_arcsin0(a, b): from numpy import arcsin ; return arcsin(a + b - a + -b) + 1.", numpy.ones(10), numpy.ones(10), np_arcsin0=[numpy.array([float]), numpy.array([float])])

    def test_arctan0(self):
        self.run_test("def np_arctan0(a, b): from numpy import arctan ; return arctan(a -0.5) + a", numpy.ones(10), numpy.ones(10), np_arctan0=[numpy.array([float]), numpy.array([float])])

    def test_arctan20(self):
        self.run_test("def np_arctan20(a, b): from numpy import arctan2 ; return b - arctan2(a , b)", numpy.ones(10), numpy.ones(10), np_arctan20=[numpy.array([float]), numpy.array([float])])

    def test_cos1(self):
        self.run_test("def np_cos1(a): from numpy import cos; return cos(a)", 5, np_cos1=[int])

    def test_sin1(self):
        self.run_test("def np_sin1(a): from numpy import sin; return sin(a)", 0.5, np_sin1=[float])

    def test_tan1(self):
        self.run_test("def np_tan1(a): from numpy import tan; return tan(a)", 0.5, np_tan1=[float])

    def test_arccos1(self):
        self.run_test("def np_arccos1(a): from numpy import arccos ; return arccos(a)", 1, np_arccos1=[int])

    def test_arcsin1(self):
        self.run_test("def np_arcsin1(a): from numpy import arcsin ; return arcsin(a)", 1, np_arcsin1=[int])

    def test_arctan1(self):
        self.run_test("def np_arctan1(a): from numpy import arctan ; return arctan(a)", 0.5, np_arctan1=[float])

    def test_arctan21(self):
        self.run_test("def np_arctan21(a): from numpy import arctan2 ; b = .5 ; return arctan2(a , b)", 1., np_arctan21=[float])

    def test_negative_mod(self):
        self.run_test("def np_negative_mod(a): return a % 5", numpy.array([-1, -5, -2, 7]), np_negative_mod=[numpy.array([int])])


# automatic generation of basic test cases for ufunc

unary_ufunc = (
        'abs', 'absolute', 'arccos', 'arccosh', 'arcsin', 'arcsinh', 'arctan', 'arctanh',
        'bitwise_not',
        'ceil', 'conj', 'conjugate', 'cos', 'cosh',
        'deg2rad', 'degrees',
        'exp', 'expm1',
        'fabs', 'floor',
        'isinf', 'isneginf', 'isposinf', 'isnan', 'invert', 'isfinite',
        'log', 'log10', 'log1p', 'log2', 'logical_not',
        'negative',
        'rad2deg', 'radians','reciprocal', 'rint', 'round', 'round_',
        'sign', 'signbit',
         'sin', 'sinh', 'spacing', 'sqrt', 'square',
        'tan', 'tanh','trunc',
        )

for f in unary_ufunc:
    if 'bitwise_' in f or 'invert' in f:
        setattr(TestNumpyUFuncUnary, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from numpy import {0} ; return {0}(a)', numpy.ones(10, numpy.int32), np_{0}=[numpy.array([numpy.int32])])".format(f)))
        setattr(TestNumpyUFuncUnary, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from numpy import {0} ; return {0}(a)', 1, np_{0}_scalar=[int])".format(f)))
        setattr(TestNumpyUFuncUnary, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from numpy import {0} ; return {0}(a)', numpy.ones((5,2), numpy.int32), np_{0}_matrix=[numpy.array([numpy.array([numpy.int32])])])".format(f)))
    else:
        setattr(TestNumpyUFuncUnary, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from numpy import {0} ; return {0}(a)', numpy.ones(10), np_{0}=[numpy.array([float])])".format(f)))
        setattr(TestNumpyUFuncUnary, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from numpy import {0} ; return {0}(a+0.5)', 0.5, np_{0}_scalar=[float])".format(f)))
        setattr(TestNumpyUFuncUnary, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from numpy import {0} ; return {0}(a)', numpy.ones((2,5)), np_{0}_matrix=[numpy.array([numpy.array([float])])])".format(f)))


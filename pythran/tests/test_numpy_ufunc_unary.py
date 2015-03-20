import unittest
from test_env import TestEnv
import numpy


@TestEnv.module
class TestNumpyUFuncUnary(TestEnv):
    pass
# automatic generation of basic test cases for ufunc

unary_ufunc = (
        'abs', 'absolute', 'arccos', 'arccosh', 'arcsin', 'arcsinh', 'arctan', 'arctanh',
        'bitwise_not',
        'ceil', 'conj', 'conjugate', 'cos', 'cosh',
        'deg2rad', 'degrees',
        'exp', 'expm1',
        'fabs', 'float32', 'float64', 'floor',
        'int8', 'int16', 'int32', 'int64', 'isinf', 'isneginf', 'isposinf', 'isnan', 'invert', 'isfinite',
        'log', 'log10', 'log1p', 'log2', 'logical_not',
        'negative',
        'rad2deg', 'radians','reciprocal', 'rint', 'round', 'round_',
        'sign', 'signbit',
         'sin', 'sinh', 'spacing', 'sqrt', 'square',
        'tan', 'tanh','trunc',
        'uint8', 'uint16', 'uint32', 'uint64'
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


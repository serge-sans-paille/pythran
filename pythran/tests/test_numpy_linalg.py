import unittest
from test_env import TestEnv
import numpy


@TestEnv.module
class TestNumpyLinalg(TestEnv):

    def test_linalg_norm0(self):
        self.run_test("def linalg_norm0(x): from numpy.linalg import norm ; return norm(x)", numpy.arange(6.), linalg_norm0=[numpy.array([float])])

    def test_linalg_norm1(self):
        self.run_test("def linalg_norm1(x): from numpy.linalg import norm ; return norm(x)", numpy.arange(6.).reshape(2,3), linalg_norm1=[numpy.array([[float]])])

    def test_linalg_norm2(self):
        self.run_test("def linalg_norm2(x): from numpy.linalg import norm ; from numpy import inf ; return norm(x, inf)", numpy.arange(6.), linalg_norm2=[numpy.array([float])])

    def test_linalg_norm3(self):
        self.run_test("def linalg_norm3(x): from numpy.linalg import norm ; from numpy import inf ; return norm(x, -inf)", numpy.arange(6.), linalg_norm3=[numpy.array([float])])

    def test_linalg_norm4(self):
        self.run_test("def linalg_norm4(x): from numpy.linalg import norm ; from numpy import inf ; return norm(x, 0)", numpy.arange(6.), linalg_norm4=[numpy.array([float])])

    def test_linalg_norm5(self):
        self.run_test("def linalg_norm5(x): from numpy.linalg import norm ; from numpy import inf ; return norm(x, ord=inf, axis=1)", (numpy.arange(9) - 4).reshape((3,3)), linalg_norm5=[numpy.array([[int]])])

    def test_linalg_norm6(self):
        self.run_test("def linalg_norm6(x): from numpy.linalg import norm ; from numpy import inf ; return norm(x, ord=5, axis=(0,))", (numpy.arange(9) - 4).reshape((3,3)), linalg_norm6=[numpy.array([[int]])])

    def test_linalg_norm7(self):
        self.run_test("def linalg_norm7(x): from numpy.linalg import norm ; return norm(x)", numpy.arange(6).reshape(2,3), linalg_norm7=[numpy.array([[int]])])

    def test_linalg_norm_pydoc(self):
        self.run_test('''
            def linalg_norm_pydoc(x):
                      import numpy as np
                      from numpy import linalg as LA
                      a = np.arange(9) - x
                      b = a.reshape((3, 3))
                      c = np.array([[ 1, 2, 3], [-1, 1, x]])
                      return (LA.norm(a), LA.norm(b),
                              LA.norm(a, np.inf), #LA.norm(b, np.inf),
                              LA.norm(a, -np.inf), #LA.norm(b, -np.inf),
                              LA.norm(a, 1), #LA.norm(b, 1),
                              LA.norm(a, -1), #LA.norm(b, -1),
                              LA.norm(a, 2), #LA.norm(b, 2),
                              LA.norm(a, -2), #LA.norm(b, -2),
                              LA.norm(a, 3), LA.norm(a, -3),
                              LA.norm(c, axis=0),
                              LA.norm(c, axis=1),
                              LA.norm(c, ord=1, axis=1),
                     )''',
                      10, linalg_norm_pydoc=[int])

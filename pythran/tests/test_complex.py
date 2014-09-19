from test_env import TestEnv
from unittest import skip
import numpy as np

class TestComplex(TestEnv):

    def test_complex_limited_range(self):
        #see -fcx-limited-range
        self.run_test('def test_complex_limited_range(a,b): return a*b', complex(-4, np.nan), complex(4, -np.inf), test_complex_limited_range=[complex, complex])

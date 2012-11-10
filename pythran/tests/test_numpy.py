from test_env import TestEnv

class TestNumpy(TestEnv):

    def test_polyfit(self):
        code="""
import numpy
def polyfit():
    a=[0.0, 1.0, 2.0, 3.0,  4.0,  5.0]
    b=[0.0, 0.8, 0.9, 0.1, -0.8, -1.0]
    z=numpy.polyfit(a,b,3)
    return sum(z)"""
        self.run_test(code, polyfit=[])


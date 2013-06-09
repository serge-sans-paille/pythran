import unittest
from test_env import TestFromDir
import os


class TestOpenMP(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"openmp")


TestOpenMP.populate(TestOpenMP)


if __name__ == '__main__':
    unittest.main()

import unittest
from test_env import TestFromDir
import os

class TestGWebb(TestFromDir):

    path = os.path.join(os.path.dirname(__file__),"g webb")


TestGWebb.populate(TestGWebb)


if __name__ == '__main__':
    unittest.main()

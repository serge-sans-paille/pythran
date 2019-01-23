import unittest
from pythran.tests import TestFromDir
import os


class TestRosetta(TestFromDir):

    path = os.path.join(os.path.dirname(__file__),"rosetta")

TestRosetta.populate(TestRosetta)

if __name__ == '__main__':
    unittest.main()

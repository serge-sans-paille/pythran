import unittest
from test_env import TestFromDir
import os


class TestRosetta(TestFromDir):

    path = os.path.join(os.path.dirname(__file__),"rosetta")
    check_output = False # FIXME this is buggy!

    @staticmethod
    def interface(name=None, file=None):
        return { "test": [] }

TestRosetta.populate(TestRosetta)

if __name__ == '__main__':
    unittest.main()

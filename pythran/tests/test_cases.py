""" Tests for test cases directory. """

# TODO: check http://code.google.com/p/unladen-swallow/wiki/Benchmarks
import os
import unittest

from test_env import TestFromDir


class TestCases(TestFromDir):

    """ Class to check all tests in the cases directory. """

    path = os.path.join(os.path.dirname(__file__), "cases")


TestCases.populate(TestCases)


if __name__ == '__main__':
    unittest.main()

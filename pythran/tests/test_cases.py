""" Tests for test cases directory. """

# TODO: check http://code.google.com/p/unladen-swallow/wiki/Benchmarks
import os
from packaging.version import Version
import numpy
import unittest

from pythran.tests import TestFromDir


class TestCases(TestFromDir):

    """ Class to check all tests in the cases directory. """

    path = os.path.join(os.path.dirname(__file__), "cases")


TestCases.populate(TestCases)

if Version(numpy.__version__) >= Version('1.20'):
    del TestCases.test_train_equalizer_norun0
    del TestCases.test_train_eq_run0
    del TestCases.test_train_eq_run1

# too template intensive for old g++
if os.environ.get('CXX', None) == 'g++-5':
    del TestCases.test_loopy_jacob_run0


if __name__ == '__main__':
    unittest.main()

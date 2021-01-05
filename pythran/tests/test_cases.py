""" Tests for test cases directory. """

# TODO: check http://code.google.com/p/unladen-swallow/wiki/Benchmarks
import os
from distutils.version import LooseVersion
import numpy
import unittest

from pythran.tests import TestFromDir


class TestCases(TestFromDir):

    """ Class to check all tests in the cases directory. """

    path = os.path.join(os.path.dirname(__file__), "cases")


TestCases.populate(TestCases)

if LooseVersion(numpy.__version__) >= '1.20':
    del TestCases.test_train_eq_run0
    del TestCases.test_train_eq_run1


if __name__ == '__main__':
    unittest.main()

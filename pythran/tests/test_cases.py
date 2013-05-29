# todo: check http://code.google.com/p/unladen-swallow/wiki/Benchmarks
import unittest
from test_env import TestFromDir
import os

class TestCases(TestFromDir):

    path = os.path.join(os.path.dirname(__file__),"cases")
    check_output = False # FIXME really?


TestCases.populate(TestCases)


if __name__ == '__main__':
    unittest.main()

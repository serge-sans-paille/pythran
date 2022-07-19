import unittest
from pythran.tests import TestFromDir
import os
import glob

class TestICC(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"icc")
    files = glob.glob(os.path.join(path,"*.py"))

TestICC.populate(TestICC)

if __name__ == '__main__':
    unittest.main()

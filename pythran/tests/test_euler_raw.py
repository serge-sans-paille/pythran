import unittest
from test_env import TestFromDir
import os
import glob

class TestEulerRaw(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"euler_raw")
    files = glob.glob(os.path.join(path,"euler*.py"))

TestEulerRaw.populate(TestEulerRaw)

if __name__ == '__main__':
    unittest.main()

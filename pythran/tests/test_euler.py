import unittest
from test_env import TestFromDir
import os
import glob

class TestEuler(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"euler")
    files = glob.glob(os.path.join(path,"euler*.py"))

    @staticmethod
    def interface(name=None, file=None):
        return { "solve": [] }

TestEuler.populate(TestEuler)

if __name__ == '__main__':
    unittest.main()

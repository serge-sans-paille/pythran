import unittest
from test_env import TestFromDir
import os
import glob

class TestUserImport(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"user_defined_import")
    files = glob.glob(os.path.join(path,"*_main.py"))

TestUserImport.populate(TestUserImport)

if __name__ == '__main__':
    unittest.main()

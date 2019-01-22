import unittest
from pythran.tests import TestFromDir
import os
import glob
import pythran

class TestUserImport(TestFromDir):
    path = os.path.join(os.path.dirname(__file__),"user_defined_import")
    files = glob.glob(os.path.join(path,"*_main.py"))
    files.append(os.path.join(path, "tiny_project", "level", "dummy.py"))


TestUserImport.populate(TestUserImport)

if __name__ == '__main__':
    unittest.main()

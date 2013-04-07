import unittest
import pythran
import os

class CompileTest(object):
    def __init__(self, module_name):
        self.module_name=module_name
        
    def __call__(self):
        module_path=os.path.join(os.path.dirname(__file__),"rosetta",self.module_name+".py")
        specs = pythran.spec_parser(module_path)
        print self.module_name
        module= pythran.cxx_generator(self.module_name, file(module_path).read(), specs)
        pythran.compile(os.environ.get("CXX","c++"), module, check=False)

class TestCase(unittest.TestCase):
    pass

import glob
for f in glob.glob(os.path.join(os.path.dirname(__file__),"rosetta", "*.py")):
    name=os.path.splitext(os.path.basename(f))[0]
    setattr(TestCase,"test_"+name, CompileTest(name))

if __name__ == '__main__':
    unittest.main()

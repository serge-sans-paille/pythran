import unittest
import glob
import os
import pythran

def compile_test(self, path):
    specs = pythran.spec_parser(path)
    modulename = os.path.splitext(os.path.basename(path))[0]
    print modulename
    module= pythran.cxx_generator(modulename, file(path).read(), specs)
    pythran.compile(module)

TestCase=type('TestCase', (unittest.TestCase,),
        { "test_{0}".format(os.path.basename(f)) : lambda self: compile_test(self,f) for f in glob.glob("cases/*.py") })

if __name__ == '__main__':
    unittest.main()

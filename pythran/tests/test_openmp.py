import unittest
import pythran
import os
from imp import load_dynamic


class CompileTest(unittest.TestCase):
    def __init__(self, module_name):
        self.module_name = module_name

    def __call__(self, check_output=False):
        module_path = os.path.join(os.path.dirname(__file__), "openmp",
                self.module_name + ".py")
        print self.module_name

        specs = {self.module_name: []}
        module_code = file(module_path).read()
        if "unittest.skip" in module_code:
            return self.skipTest("Marked as skipable")
        mod = pythran.cxx_generator(self.module_name, module_code, specs)
        pymod = load_dynamic(self.module_name,
                pythran.compile(os.environ.get("CXX", "c++"), mod, check=False,
                    cxxflags=['-O0', '-fopenmp']))

        res = getattr(pymod, self.module_name)()
        assert res, 'Test Failed'


class TestCase(unittest.TestCase):
    pass


import glob
for f in glob.glob(os.path.join(os.path.dirname(__file__), "openmp", "*.py")):
    name = os.path.splitext(os.path.basename(f))[0]
    setattr(TestCase, "test_" + name, CompileTest(name))

if __name__ == '__main__':
    unittest.main()

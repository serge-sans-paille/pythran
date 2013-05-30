import unittest
import pythran
import os
from imp import load_dynamic

class CompileTest(object):
    def __init__(self, module_name):
        self.module_name=module_name

    def __name__(self):
        return self.module_name

    def __call__(self, check_output=False):
        module_path=os.path.join(os.path.dirname(__file__),"euler",self.module_name+".py")
        print self.module_name

        specs = { "solve": [] }
        module_code = file(module_path).read()
        if "unittest.skip" in module_code:
            return self.skipTest("Marked as skipable")
        mod = pythran.cxx_generator(self.module_name, module_code, specs)
        pymod=load_dynamic(self.module_name, pythran.compile(mod))
        if check_output:
            res = getattr(pymod,"solve")()
            compiled_code=compile(file(module_path).read(),"","exec")
            env={}
            eval(compiled_code, env)
            ref=eval("solve()",env)
            if ref != res:
              print ref, res

class TestCase(unittest.TestCase):
    pass

import glob
for f in glob.glob(os.path.join(os.path.dirname(__file__),"euler", "euler*.py")):
    name=os.path.splitext(os.path.basename(f))[0]
    setattr(TestCase,"test_"+name, CompileTest(name))

if __name__ == '__main__':
    unittest.main()

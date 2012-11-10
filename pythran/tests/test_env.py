from pythran import cxx_generator
from pythran import compile as pythran_compile
from imp import load_dynamic
import unittest
import os


class TestEnv(unittest.TestCase):

    def assertAlmostEqual(self, ref, res):
        if hasattr(ref,'__iter__'):
            self.assertEqual(len(ref), len(res))
            for iref, ires in zip(ref,res):
                self.assertAlmostEqual(iref, ires)
        else:
            unittest.TestCase.assertAlmostEqual(self,ref, res)

    def run_test(self, code, *params, **interface):
        for name in sorted(interface.keys()):
            modname="test_"+name
            print modname
            compiled_code=compile(code,"","exec")
            env={}
            eval(compiled_code, env)
            ref=eval("{0}({1})".format(name, ",".join(("'{0}'".format(p) if isinstance(p,str) else str(p)) for p in params)),env)
            mod = cxx_generator(modname, code, interface)
            pymod = load_dynamic(modname,pythran_compile(os.environ.get("CXX","c++"),mod,  cxxflags=["-O0","-fno-implicit-inline-templates", "-fopenmp"]))
            res = getattr(pymod,name)(*params)
            if ref != res:
                print ref, res
                self.assertAlmostEqual(ref, res)


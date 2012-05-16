from pythran import cxx_generator, compile
from imp import load_dynamic
import unittest

class TestEnv(unittest.TestCase):

    def run_test(self, code, *params, **interface):
        for name in sorted(interface.keys()):
            modname="test_"+name
            print modname
            mod = cxx_generator(modname, code, interface)
            pymod = load_dynamic(modname,compile(mod))
            res = getattr(pymod,name)(*params)
            print res


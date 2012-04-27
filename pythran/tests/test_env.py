from pythran import cxx_generator, compile
import unittest

class TestEnv(unittest.TestCase):

    def run_test(self, code, *params, **interface):
        for name in sorted(interface.keys()):
            mod = cxx_generator("test_"+name, code, interface)
            pymod = compile(mod)
            res = getattr(pymod,name)(*params)
            print res


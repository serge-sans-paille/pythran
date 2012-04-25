from pythran import python_interface
import unittest

class TestEnv(unittest.TestCase):

    def run_test(self, code, *params, **interface):
        for name in sorted(interface.keys()):
            mod = python_interface("test_"+name, code, **interface)
            res = getattr(mod,name)(*params)
            print res


import unittest
import doctest
import pythran
import inspect

class TestDoctest(unittest.TestCase):
    '''
    Enable automatic doctest integration to unittest

    Every module in the pythran package is scanned for doctests
    and one test per module is created
    '''
    def test_tutorial(self):
        failed, _ = doctest.testfile('../../doc/TUTORIAL.rst')
        self.assertEqual(failed, 0)

    def test_internal(self):
        failed, _ = doctest.testfile('../../doc/INTERNAL.rst')
        self.assertEqual(failed, 0)


def generic_test_package(self, mod):
    failed, _ = doctest.testmod(mod)
    self.assertEqual(failed, 0)

def add_module_doctest(module_name):
    module = getattr(pythran, module_name)
    if inspect.ismodule(module):
        setattr(TestDoctest, 'test_' + module_name,
            lambda self: generic_test_package(self, module))

map(add_module_doctest, dir(pythran))

if __name__ == '__main__':
    unittest.main()

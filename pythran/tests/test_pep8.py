import unittest
import pythran
import pep8
import inspect
import os

class TestPEP8(unittest.TestCase):
    '''
    Enable automatic pep8 compliance testing

    Every module in the pythran package is scanned for pep8 errors
    '''
    pass


def generic_test_package(self, mod):
    base, _ = os.path.splitext(mod.__file__)
    mod_file = base + '.py'  # takes care of .pyc or .pyo
    chk = pep8.Checker(mod_file)
    chk.report._ignore_code = lambda s: s in ('E121', 'E122', 'E123', 'E124', 'E125', 'E126', 'E127', 'E128', 'E129')
    failed = chk.check_all()
    self.assertEqual(failed, 0)

def add_module_pep8_test(module_name):
    module = getattr(pythran, module_name)
    if inspect.ismodule(module):
        setattr(TestPEP8, 'test_' + module_name,
            lambda self: generic_test_package(self, module))

map(add_module_pep8_test, dir(pythran))

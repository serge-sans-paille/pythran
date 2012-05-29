import unittest
import pythran
import os

def compile_test(self, module_name):
    module_path=os.path.join(os.path.dirname(__file__),"cases",module_name+".py")
    specs = pythran.spec_parser(module_path)
    print module_name
    module= pythran.cxx_generator(module_name, file(module_path).read(), specs)
    pythran.compile(module)

class TestCase(unittest.TestCase):
    pass
TestCase.test_bubble_sort=lambda self:compile_test(self,"bubble_sort")
TestCase.test_insertion_sort=lambda self:compile_test(self,"insertion_sort")
TestCase.test_multi_export=lambda self:compile_test(self,"multi_export")
TestCase.test_primes_sieve=lambda self:compile_test(self,"primes_sieve")
TestCase.test_zero=lambda self:compile_test(self,"zero")
if __name__ == '__main__':
    unittest.main()

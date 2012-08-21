# todo: check http://code.google.com/p/unladen-swallow/wiki/Benchmarks
import unittest
import pythran
import os

def compile_test(self, module_name):
    module_path=os.path.join(os.path.dirname(__file__),"cases",module_name+".py")
    specs = pythran.spec_parser(module_path)
    print module_name
    module= pythran.cxx_generator(module_name, file(module_path).read(), specs)
    pythran.compile(os.environ.get("CXX","c++"), module)

class TestCase(unittest.TestCase):
    pass
TestCase.test_bubble_sort=lambda self:compile_test(self,"bubble_sort")
TestCase.test_insertion_sort=lambda self:compile_test(self,"insertion_sort")
TestCase.test_multi_export=lambda self:compile_test(self,"multi_export")
TestCase.test_primes_sieve=lambda self:compile_test(self,"primes_sieve")
TestCase.test_primes_sieve2=lambda self:compile_test(self,"primes_sieve2")
TestCase.test_zero=lambda self:compile_test(self,"zero")
TestCase.test_select=lambda self:compile_test(self,"select")
TestCase.test_pselect=lambda self:compile_test(self,"pselect")
TestCase.test_caxpy=lambda self:compile_test(self,"caxpy")
TestCase.test_ccopy=lambda self:compile_test(self,"ccopy")
TestCase.test_cdotc=lambda self:compile_test(self,"cdotc")
TestCase.test_cdotu=lambda self:compile_test(self,"cdotu")
TestCase.test_crotg=lambda self:compile_test(self,"crotg")
TestCase.test_gauss=lambda self:compile_test(self,"gauss")
TestCase.test_pivot=lambda self:compile_test(self,"pivot")
TestCase.test_guerre=lambda self:compile_test(self,"guerre")
TestCase.test_deriv=lambda self:compile_test(self,"deriv")
TestCase.test_ramsurf=lambda self:compile_test(self,"ramsurf")
TestCase.test_hyantes_core=lambda self:compile_test(self,"hyantes_core")
TestCase.test_mandel=lambda self:compile_test(self,"mandel")
TestCase.test_approximated_callgraph=lambda self:compile_test(self,"approximated_callgraph")
TestCase.test_sum_primes=lambda self:compile_test(self,"sum_primes")
TestCase.test_factorize_naive=lambda self:compile_test(self,"factorize_naive")
TestCase.test_quicksort=lambda self:compile_test(self,"quicksort")
TestCase.test_another_quicksort=lambda self:compile_test(self,"another_quicksort")
TestCase.test_perm=lambda self:compile_test(self,"perm")
TestCase.test_nqueens=lambda self:compile_test(self,"nqueens")
TestCase.test_monte_carlo=lambda self:compile_test(self,"monte_carlo")
TestCase.test_pi_buffon=lambda self:compile_test(self,"pi_buffon")
TestCase.test_brownian=lambda self:compile_test(self,"brownian")
TestCase.test_stone=lambda self:compile_test(self,"stone")
TestCase.test_extrema=lambda self:compile_test(self,"extrema")
if __name__ == '__main__':
    unittest.main()

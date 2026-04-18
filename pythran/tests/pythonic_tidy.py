import os
import sys
import unittest
import subprocess

pythonic = os.path.abspath(os.path.join(os.path.dirname(__file__),
                        "..",
                        "pythonic"))

class TestPythonic(unittest.TestCase):
    """
    Test various invariant on pythonic at the C++ level
    """


try:
    subprocess.check_call(['clang-tidy', '--version'])
    have_clang_tidy = True
except:
    have_clang_tidy = False

try:
    subprocess.check_call(['clang++', '--version'])
    have_clang = True
except:
    have_clang = False

try:
    import scipy_openblas64
    openblas_dir = scipy_openblas64.get_include_dir()
except ImportError:
    openblas_dir = None

try:
    import diskarzhan
except ImportError:
    diskarzhan = None

if all([have_clang, have_clang_tidy, openblas_dir]):

    common_flags = [
            '-xc++', '-std=c++17', '-Ipythran',
            '-fsyntax-only',
            '-DPYTHONIC_NS_BEGIN=namespace pythonic {',
            '-DPYTHONIC_NS_END=}',
            '-DPYTHRAN_BLAS_SCIPY_OPENBLAS',
            '-fopenmp',
            '-I' + openblas_dir,
            ]

    checks = [
            'modernize-type-traits',
            'modernize-replace-random-shuffle',
            'modernize-min-max-use-initializer-list',
            'modernize-return-braced-init-list',
            'modernize-unary-static-assert',
            'modernize-use-structured-binding',
            'modernize-use-equals-default',
            'modernize-use-using',
            'performance-for-range-copy',
            'performance-inefficient-algorithm',
            'performance-inefficient-vector-operation',
            'performance-move-const-arg',
            'performance-noexcept-move-constructor',
            'performance-unnecessary-value-param',
            'performance-unnecessary-copy-initialization',
            'performance-trivially-destructible',
            'performance-use-std-move',
            ]


    def make_independent_header_test(path):
        def method(self):
            subprocess.check_call(['clang++', '-w', path] + common_flags)
        return method


    def make_clang_tidy_test(path):
        def method(self):
            subprocess.check_call(
                    ['clang-tidy',] +
                    ['--extra-arg-before={}'.format(flag) for flag in common_flags] +
                    ['-checks=-*,' + ','.join(checks)] +
                    ['--warnings-as-errors=*', path])
        return method

    def make_diskarzhan_test(path):
        def method(self):
            assert diskarzhan.lint([path]) == 0
        return method

    # Those files are part of X-MACRO
    skiplist = {
            'icommon.hpp',
            'numpy_binary_op.hpp',
            'numpy_ufunc.hpp',
            'numpy_nary_expr.hpp',
            'numpy_unary_op.hpp',
            'numpy_binary_op.hpp',
            'ufunc_accumulate.hpp',
            'ufunc_reduce.hpp',
            }

    topics = ('independent_header', 'clang_tidy')
    if diskarzhan:
        topics += ('diskarzhan',)

    # Dynamically fill the test bed
    for root, dirs, files in os.walk(pythonic):
        for name in files:
            if not name.endswith('.hpp'):
                continue
            if name in skiplist:
                continue
            path = os.path.join(root, name)
            for topic in topics:
                suffix = path[len(pythonic):-4].replace(os.path.sep, '_')
                methodname = '_'.join(['test', topic, suffix])
                generator = globals()['_'.join(['make', topic, 'test'])]
                setattr(TestPythonic, methodname, classmethod(generator(path)))

if __name__ == '__main__':
    unittest.main()

""" Check unary functions for the numpy module. """

import numpy

try:
    import scipy
except ImportError:
    scipy = None

from pythran.tests import TestEnv
from pythran.tables import MODULES
from pythran.intrinsic import UFunc
from pythran.typing import NDArray


@TestEnv.module
class TestNumpyUFuncBinary(TestEnv):
    pass

#automatic generation of basic test cases for ufunc
binary_ufunc = ([("numpy", k) for k, v in MODULES["numpy"].items() if isinstance(v, UFunc)] +
                [("scipy.special", k) for k, v in MODULES["scipy"]["special"].items() if isinstance(v, UFunc)])

reduced_ufunc = {'add', 'minimum', 'maximum', 'multiply', 'bitwise_or',
                 'bitwise_and', 'bitwise_xor'}

for ns, f in binary_ufunc:
    if 'bitwise_' in f or 'ldexp' in f or '_shift' in f :
        setattr(TestNumpyUFuncBinary, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from {1} import {0} ; return {0}(a,a)', numpy.ones(10, numpy.int32), np_{0}=[NDArray[numpy.int32,:]])".format(f, ns)))
        setattr(TestNumpyUFuncBinary, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from {1} import {0} ; return {0}(a, a-1)', 1, np_{0}_scalar=[int])".format(f, ns)))
        setattr(TestNumpyUFuncBinary, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from {1} import {0} ; return {0}(a,a)', numpy.ones((2,5), numpy.int32), np_{0}_matrix=[NDArray[numpy.int32, :, :]])".format(f, ns)))
        # Tests for accumulation
        if f != "ldexp":
            # accumulate doesn't work with ldexp as typing is incorrect for
            # accumulation.
            setattr(TestNumpyUFuncBinary, 'test_accumulate_' + f, eval("lambda self: self.run_test('def np_{0}_accumulate(a): from {1} import {0} ; return {0}.accumulate(a)', numpy.ones(10, numpy.int32), np_{0}_accumulate=[NDArray[numpy.int32, :]])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_accumulate_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix_accumulate(a): from {1} import {0} ; return {0}.accumulate(a)', numpy.ones((2,5), numpy.int32), np_{0}_matrix_accumulate=[NDArray[numpy.int32,:,:]])".format(f, ns)))
        # Tests for reduction
        if f in reduced_ufunc:
            setattr(TestNumpyUFuncBinary, 'test_reduce_' + f, eval("lambda self: self.run_test('def np_{0}_reduce(a): from {1} import {0} ; return {0}.reduce(a)', numpy.ones(10, numpy.int32), np_{0}_reduce=[NDArray[numpy.int32, :]])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_reduce_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix_reduce(a): from {1} import {0} ; return {0}.reduce(a)', numpy.ones((2,5), numpy.int32), np_{0}_matrix_reduce=[NDArray[numpy.int32,:,:]])".format(f, ns)))
    else:
        if 'scipy' in ns and scipy is None:
            continue

        if 'spherical' in f and 'scipy' in ns:
            setattr(TestNumpyUFuncBinary, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from {1} import {0}; import numpy; return {0}(numpy.array(a, dtype=int) +2 ,a)', numpy.ones(10), np_{0}=[NDArray[float, :]])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from {1} import {0} ; return {0}(int(a+3), a+0.5)', 0.5, np_{0}_scalar=[float])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from {1} import {0}; import numpy; return {0}(numpy.array(a, dtype=int),a)', numpy.ones((2,5)) - 0.2 , np_{0}_matrix=[NDArray[float,:,:]])".format(f, ns)))
            ## Tests for integral numbers
            try:
                eval('{1}.{0}(1, 1)'.format(f, ns))
                setattr(TestNumpyUFuncBinary, 'test_' + f + '_integer', eval("lambda self: self.run_test('def np_{0}_integer(a): from {1} import {0} ; return {0}(a, a)', numpy.ones(10,dtype=int), np_{0}_integer=[NDArray[int, :]])".format(f, ns)))
            except TypeError:
                pass
        else:
            setattr(TestNumpyUFuncBinary, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from {1} import {0} ; return {0}(a,a)', numpy.ones(10), np_{0}=[NDArray[float, :]])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from {1} import {0} ; return {0}(a+0.5, a+0.5)', 0.5, np_{0}_scalar=[float])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from {1} import {0} ; return {0}(a,a)', numpy.ones((2,5)) - 0.2 , np_{0}_matrix=[NDArray[float,:,:]])".format(f, ns)))
            ## Tests for complex numbers
            try:
                eval('{1}.{0}(1.j, 1.j)'.format(f, ns))
                setattr(TestNumpyUFuncBinary, 'test_' + f + '_complex', eval("lambda self: self.run_test('def np_{0}_complex(a): from {1} import {0} ; return {0}(a,a)', numpy.ones(10)*1.j, np_{0}_complex=[NDArray[complex, :]])".format(f, ns)))
            except TypeError:
                pass
            ## Tests for integral numbers
            try:
                eval('{1}.{0}(1, 1)'.format(f, ns))
                setattr(TestNumpyUFuncBinary, 'test_' + f + '_integer', eval("lambda self: self.run_test('def np_{0}_integer(a): from {1} import {0} ; return {0}(a, a)', numpy.ones(10,dtype=int), np_{0}_integer=[NDArray[int, :]])".format(f, ns)))
            except TypeError:
                pass

        ## Tests for accumulation
        if 'scipy' not in ns:
            setattr(TestNumpyUFuncBinary, 'test_accumulate_' + f, eval("lambda self: self.run_test('def np_{0}_accumulate(a): from {1} import {0} ; return {0}.accumulate(a)', numpy.ones(10), np_{0}_accumulate=[NDArray[float,:]])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_accumulate_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix_accumulate(a): from {1} import {0} ; return {0}.accumulate(a)', numpy.ones((2,5)) - 0.2 , np_{0}_matrix_accumulate=[NDArray[float, :, :]])".format(f, ns)))
        ## Tests for reduction
        if f in reduced_ufunc:
            setattr(TestNumpyUFuncBinary, 'test_reduce_' + f, eval("lambda self: self.run_test('def np_{0}_reduce(a): from {1} import {0} ; return {0}.reduce(a)', numpy.ones(10), np_{0}_reduce=[NDArray[float,:]])".format(f, ns)))
            setattr(TestNumpyUFuncBinary, 'test_reduce_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix_reduce(a): from {1} import {0} ; return {0}.reduce(a)', numpy.ones((2,5)) - 0.2 , np_{0}_matrix_reduce=[NDArray[float, :, :]])".format(f, ns)))

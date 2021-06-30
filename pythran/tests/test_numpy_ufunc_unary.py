import unittest
from pythran.tests import TestEnv
import numpy
from pythran.typing import NDArray

try:
    import scipy
except ImportError:
    scipy = None


@TestEnv.module
class TestNumpyUFuncUnary(TestEnv):
    pass


# automatic generation of basic test cases for ufunc
unary_func_by_module = {
    'numpy': (
        'abs', 'absolute', 'arccos', 'arccosh', 'arcsin', 'arcsinh', 'arctan',
        'arctanh',
        'bitwise_not',
        'cbrt', 'ceil', 'conj', 'conjugate', 'cos', 'cosh',
        'deg2rad', 'degrees',
        'exp', 'expm1',
        'fabs', 'float32', 'float64', 'floor',
        'int8', 'int16', 'int32', 'int64', 'isinf', 'isneginf', 'isposinf',
        'isnan', 'invert', 'isfinite',
        'log', 'log10', 'log1p', 'log2', 'logical_not',
        'negative',
        'rad2deg', 'radians', 'reciprocal', 'rint', 'round', 'round_',
        'sign', 'signbit',
        'sin', 'sinh', 'spacing', 'sqrt', 'square',
        'tan', 'tanh', 'trunc',
        'uint8', 'uint16', 'uint32', 'uint64'
    ),
    'scipy.special': ('gammaln', 'gamma')
}

if scipy is None:
    del unary_func_by_module['scipy.special']

test_inputs_by_type = {
    'float': {
        '_scalar': ('0.5', '[float]'),
        '': ('numpy.ones(10)', '[NDArray[float,:]]'),
        '_matrix': ('numpy.ones((2,5))', '[NDArray[float,:,:]]')
    },
    'complex': {
        '_scalar': ('0.5j', '[complex]'),
        '': ('numpy.ones(10)*1.j', '[NDArray[complex,:]]'),
        '_matrix': ('numpy.ones((2,5))*1.j', '[NDArray[complex,:,:]]')
    },
    'numpy.int32': {
        '_scalar': ('numpy.int32(1)', '[numpy.int32]'),
        '': ('numpy.ones(10, numpy.int32)', '[NDArray[numpy.int32,:]]'),
        '_matrix': ('numpy.ones((2,5), numpy.int32)',
                    '[NDArray[numpy.int32,:,:]]')
    }
}

for module, functions in unary_func_by_module.items():
    for f in functions:
        for input_type in ('float', 'complex'):
            try:
                eval('{}.{}({})'.format(module, f, test_inputs_by_type[input_type]['_scalar'][0]))
            except TypeError:
                if input_type == 'float':
                    input_type = 'numpy.int32'
                else:
                    continue  # no need to test that, it does not work on numpy

            if input_type == 'complex' and 'gamma' in f:
                continue  # skip


            for test_suffix, (input, pythran_input_type) \
                    in test_inputs_by_type[input_type].items():

                func_name = "numpy_ufunc_unary_{}_{}{}_{}".format(module.replace('.', '_'), f,
                                             test_suffix, input_type.replace('.','_'))

                code = """
                    lambda self: self.run_test(
                        '''{func}''', 
                        {input}, 
                        {func_name}={pythran_input_type}
                    )
                    """.replace('\n', '').format(
                        func="""
                        def {func_name}(a):
                            from {module} import {f}
                            return {f}(a)
                        """.format(func_name=func_name, module=module, f=f),
                        func_name=func_name,
                        input=input,
                        pythran_input_type=pythran_input_type,
                    )

                setattr(
                    TestNumpyUFuncUnary,
                    'test_numpy_ufunc_unary_{}'.format(func_name),
                    eval(code)
                )

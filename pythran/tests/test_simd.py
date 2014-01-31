from test_env import TestEnv
import numpy

class TestSimd(TestEnv):

    PYTHRAN_CXX_FLAGS = TestEnv.PYTHRAN_CXX_FLAGS + ['-DUSE_BOOST_SIMD', '-march=native']

    def test_simd_arc_distance(self):
        code = '''
import numpy as np
def simd_arc_distance_kernel(theta_1, phi_1,
                       theta_2, phi_2):
    """
    Calculates the pairwise arc distance between all points in vector a and b.
    """
    temp = np.sin((theta_2-theta_1)/2)**2+np.cos(theta_1)*np.cos(theta_2)*np.sin((phi_2-phi_1)/2)**2
    distance_matrix = 2 * (np.arctan2(np.sqrt(temp),np.sqrt(1-temp)))
    return distance_matrix
def simd_arc_distance(n):
    r = np.ones(n)
    return simd_arc_distance_kernel(r, r, r, r)
'''
        self.run_test(code, 40, simd_arc_distance=[int])

    def test_simd_rosen(self):
        code = '''
import numpy
def simd_rosen_der(n):
    x = numpy.ones(n)
    xm = x[1:-1]
    xm_m1 = x[:-2]
    xm_p1 = x[2:]
    der = numpy.zeros_like(x)
    der[1:-1] = (+ 200 * (xm - xm_m1 ** 2)
                 - 400 * (xm_p1 - xm ** 2) * xm
                 - 2 * (1 - xm))
    der[0] = -400 * x[0] * (x[1] - x[0] ** 2) - 2 * (1 - x[0])
    der[-1] = 200 * (x[-1] - x[-2] ** 2)
    return der'''
        self.run_test(code, 40, simd_rosen_der=[int])



# automatic generation of basic test cases for ufunc
binary_ufunc = (
        'add','arctan2',
        'bitwise_and', 'bitwise_or', 'bitwise_xor',
        'copysign',
        'divide',
        #'equal',
        'floor_divide', 'fmax', 'fmin', 'fmod',
        #'greater', 'greater_equal',
        'hypot',
        #'less', 'less_equal',  'logaddexp2', "logical_and", "logical_or", "logical_xor",
        'ldexp', 'left_shift', 'logaddexp',
        'maximum', 'minimum', 'mod','multiply',
        #'not_equal',
        'nextafter',
        'power',
        'remainder','right_shift',
        'subtract',
        'true_divide',
        )

unary_ufunc = (
        'abs', 'absolute', 'arccos', 'arccosh', 'arcsin', 'arcsinh', 'arctan', 'arctanh',
        'bitwise_not',
        'ceil', 'conj', 'conjugate', 'cos', 'cosh',
        'deg2rad', 'degrees',
        'exp', 'expm1',
        'fabs', 'floor',
        # 'isneginf', 'isposinf'
        'isinf', 'isnan', 'invert', 'isfinite',
        # 'logical_not'
        'log10', 'log1p', 'log2',
        'negative',
        'rad2deg', 'radians','reciprocal', 'rint', 'round', 'round_',
        'sign', 'signbit',
        'sin', 'sinh', 'spacing', 'sqrt', 'square',
        'tan', 'tanh','trunc',
        )

for f in unary_ufunc:
    if 'bitwise_' in f or 'invert' in f:
        setattr(TestSimd, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a)', np_{0}=[])".format(f)))
    else:
        setattr(TestSimd, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a)', np_{0}=[])".format(f)))

for f in binary_ufunc:
    if 'bitwise_' in f or 'ldexp' in f or '_shift' in f :
        setattr(TestSimd, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a,a)', np_{0}=[])".format(f)))
    else:
        setattr(TestSimd, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a,a)', np_{0}=[])".format(f)))

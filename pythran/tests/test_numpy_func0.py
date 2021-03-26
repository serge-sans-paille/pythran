import unittest
from pythran.tests import TestEnv
import numpy
import tempfile
import os

from pythran.typing import NDArray, List, Tuple


@TestEnv.module
class TestNumpyFunc0(TestEnv):

    def test_extended_sum0(self):
        self.run_test("def numpy_extended_sum0(a): import numpy ; return numpy.sum(a)",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum0=[NDArray[int,:,:,:,:]])

    def test_extended_sum1(self):
        self.run_test("def numpy_extended_sum1(a): import numpy ; return numpy.sum(a[1])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum1=[NDArray[int,:,:,:,:]])

    def test_extended_sum2(self):
        self.run_test("def numpy_extended_sum2(a): import numpy ; return numpy.sum(a[1,0])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum2=[NDArray[int,:,:,:,:]])

    def test_extended_sum3(self):
        self.run_test("def numpy_extended_sum3(a): import numpy ; return numpy.sum(a[1:-1])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum3=[NDArray[int,:,:,:,:]])

    def test_extended_sum4(self):
        self.run_test("def numpy_extended_sum4(a): import numpy ; return numpy.sum(a[1:-1,0])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum4=[NDArray[int,:,:,:,:]])

    def test_extended_sum5(self):
        self.run_test("def numpy_extended_sum5(a): import numpy ; return numpy.sum(a)",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum5=[NDArray[int,:,:,:,:]])

    def test_out_sum0(self):
        self.run_test("def numpy_out_sum0(a, b): import numpy ; return numpy.sum(a, axis=0, out=b)",
                      numpy.arange(10).reshape((5,2)),
                      numpy.zeros(2, dtype=int),
                      numpy_out_sum0=[NDArray[int,:,:], NDArray[int,:]])

    def test_out_sum1(self):
        self.run_test("def numpy_out_sum1(a, b): import numpy ; return numpy.sum(a, axis=0, out=b)",
                      numpy.arange(10).reshape((5,2)),
                      numpy.ones(2, dtype=int),
                      numpy_out_sum1=[NDArray[int,:,:], NDArray[int,:]])

    def test_out_sum2(self):
        self.run_test("def numpy_out_sum2(a, b): import numpy ; return numpy.sum(a, axis=1, out=b)",
                      numpy.arange(10).reshape((5,2)),
                      numpy.zeros(5, dtype=int),
                      numpy_out_sum2=[NDArray[int,:,:], NDArray[int,:]])


    def test_numpy_shape_as_function(self):
         self.run_test("def numpy_shape_as_function(a): import numpy ; return numpy.shape(a)",
                       numpy.ones(3, numpy.int16),
                       numpy_shape_as_function=[NDArray[numpy.int16,:]])

    def test_numpy_size_as_function(self):
         self.run_test("def numpy_size_as_function(a): import numpy ; return numpy.size(a)",
                       numpy.ones(3, numpy.int16),
                       numpy_size_as_function=[NDArray[numpy.int16,:]])

    def test_numpy_ndim_as_function(self):
         self.run_test("def numpy_ndim_as_function(a): import numpy ; return numpy.ndim(a)",
                       numpy.ones(3, numpy.int16),
                       numpy_ndim_as_function=[NDArray[numpy.int16,:]])

    def test_frexp0(self):
        self.run_test("def np_frexp0(a): import numpy as np ; return np.frexp(a)", 1.5, np_frexp0=[float])

    def test_frexp1(self):
        self.run_test("def np_frexp1(a): import numpy as np ; return np.frexp(a)", numpy.array([1.1,2.2,3.3]), np_frexp1=[NDArray[float,:]])

    def test_frexp2(self):
        self.run_test("def np_frexp2(a): import numpy as np ; return np.frexp(a+a)", numpy.array([1.1,2.2,3.3]), np_frexp2=[NDArray[float,:]])

    def test_ndindex0(self):
        self.run_test("def np_ndindex0(): import numpy as np ; return [x for x in np.ndindex(5,6)]",
                      np_ndindex0=[])

    def test_ndindex1(self):
        self.run_test("def np_ndindex1(a): import numpy as np ; return [x for x in np.ndindex(a)]", 3, np_ndindex1=[int])

    def test_ndindex2(self):
        self.run_test("def np_ndindex2(n): import numpy as np ; return [x for x in np.ndindex((n,n))]", 3, np_ndindex2=[int])

    def test_ndenumerate0(self):
        self.run_test("def np_ndenumerate0(a): import numpy as np ; return [x for x in np.ndenumerate(a)]", numpy.array([[1, 2], [3, 4]]), np_ndenumerate0=[NDArray[int,:,:]])

    def test_ndenumerate1(self):
        self.run_test("def np_ndenumerate1(a): import numpy as np ; return [x for x in np.ndenumerate(a)]", numpy.array([1, 2, 3, 4]), np_ndenumerate1=[NDArray[int,:]])

    def test_nansum0(self):
        self.run_test("def np_nansum0(a): import numpy as np  ; return np.nansum(a)" , numpy.array([[1, 2], [3, numpy.nan]]), np_nansum0=[NDArray[float,:,:]])

    def test_nansum1(self):
        self.run_test("def np_nansum1(a): import numpy as np ; return np.nansum(a)" , numpy.array([[1, 2], [numpy.NINF, numpy.nan]]), np_nansum1=[NDArray[float,:,:]])

    def test_nansum2(self):
        self.run_test("def np_nansum2(a): import numpy as np ; return np.nansum(a)", [1., numpy.nan], np_nansum2=[List[float]])

    def test_nanmin0(self):
        self.run_test("def np_nanmin0(a): import numpy as np ; return np.nanmin(a)" , numpy.array([[1, 2], [3, numpy.nan]]), np_nanmin0=[NDArray[float,:,:]])

    def test_nanmin1(self):
        self.run_test("def np_nanmin1(a): import numpy as np ; return np.nanmin(a)" , numpy.array([[1, 2], [numpy.NINF, numpy.nan]]), np_nanmin1=[NDArray[float,:,:]])

    def test_nanmin2(self):        
         self.run_test("def np_nanmin2(a): import numpy as np ; return np.nanmin(a)" , numpy.array([[numpy.nan, numpy.nan], [numpy.nan, numpy.nan]]), np_nanmin2=[NDArray[float,:,:]])

    def test_nanmax0(self):
        self.run_test("def np_nanmax0(a): import numpy as np ; return np.nanmax(a)" , numpy.array([[1, 2], [3, numpy.nan]]),  np_nanmax0=[NDArray[float,:,:]])

    def test_nanmax1(self):
        self.run_test("def np_nanmax1(a): import numpy as np ; return np.nanmax(a)" , numpy.array([[1, 2], [numpy.inf, numpy.nan]]) , np_nanmax1=[NDArray[float,:,:]])

    def test_nanmax2(self):        
         self.run_test("def np_nanmax2(a): import numpy as np ; return np.nanmax(a)" , numpy.array([[numpy.nan, numpy.nan], [numpy.nan, numpy.nan]]), np_nanmax2=[NDArray[float,:,:]])

    def test_np_residual(self):
        self.run_test("""import numpy as np
def np_residual():
    nx, ny, nz= 75, 75, 100
    hx, hy = 1./(nx-1), 1./(ny-1)

    P_left, P_right = 0, 0
    P_top, P_bottom = 1, 0
    P = np.ones((nx, ny, nz), np.float64)
    d2x = np.zeros_like(P)
    d2y = np.zeros_like(P)

    d2x[1:-1] = (P[2:]   - 2*P[1:-1] + P[:-2]) / hx/hx
    d2x[0]    = (P[1]    - 2*P[0]    + P_left)/hx/hx
    d2x[-1]   = (P_right - 2*P[-1]   + P[-2])/hx/hx

    d2y[:,1:-1] = (P[:,2:] - 2*P[:,1:-1] + P[:,:-2])/hy/hy
    d2y[:,0]    = (P[:,1]  - 2*P[:,0]    + P_bottom)/hy/hy
    d2y[:,-1]   = (P_top   - 2*P[:,-1]   + P[:,-2])/hy/hy

    return d2x + d2y + 5*np.cosh(P).mean()**2
""", np_residual=[])

    def test_np_func2(self):
        self.run_test("""import numpy as np
def np_func2(x):
    f = [x[0] * np.cos(x[1]) - 4,
         x[1]*x[0] - x[1] - 5]
    df = np.array([[np.cos(x[1]), -x[0] * np.sin(x[1])],
                   [x[1], x[0] - 1]])
    return f, df
""", [1.0, 2.0, 3.0], np_func2=[List[float]])

    def test_np_peval(self):
        self.run_test("""import numpy
def np_peval(x, p):
    return p[0]*numpy.sin(2*numpy.pi*p[1]*x+p[2])
""", 12., [1.0, 2.0, 3.0], np_peval=[float, List[float]])

    def test_np_residuals(self):
        self.run_test("""import numpy
def np_residuals():
    x = numpy.arange(0,6e-2,6e-2/30)
    A,k,theta = 10, 1.0/3e-2, numpy.pi/6
    return A*numpy.sin(2*numpy.pi*k*x+theta)
""", np_residuals=[])

    def test_np_func_deriv(self):
        self.run_test("""import numpy
def np_func_deriv(x, sign=1.0):
    dfdx0 = sign*(-2*x[0] + 2*x[1] + 2)
    dfdx1 = sign*(2*x[0] - 4*x[1])
    return numpy.array([ dfdx0, dfdx1 ])
""", [-1.0, 1.0], -1.0, np_func_deriv=[List[float], float])

    def test_np_func(self):
        self.run_test("""import numpy
def np_func(x, sign=1.0):
    return sign*(2*x[0]*x[1] + 2*x[0] - x[0]**2 - 2*x[1]**2)
""", [-1.0, 1.0], -1.0, np_func=[List[float], float])

    def test_rosen_hess_p(self):
        self.run_test("""import numpy
def np_rosen_hess_p(x, p):
    x = numpy.asarray(x)
    Hp = numpy.zeros_like(x)
    Hp[0] = (1200*x[0]**2 - 400*x[1] + 2)*p[0] - 400*x[0]*p[1]
    Hp[1:-1] = -400*x[:-2]*p[:-2]+(202+1200*x[1:-1]**2-400*x[2:])*p[1:-1] \
               -400*x[1:-1]*p[2:]
    Hp[-1] = -400*x[-2]*p[-2] + 200*p[-1]
    return Hp
""",
                      numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]),
                      numpy.array([2.3, 1.7, 1.8, 2.9, 2.2]),
                      np_rosen_hess_p=[NDArray[float,:], NDArray[float,:]])

    def test_rosen_hess(self):
        self.run_test("""import numpy
def np_rosen_hess(x):
    x = numpy.asarray(x)
    H = numpy.diag(-400*x[:-1],1) - numpy.diag(400*x[:-1],-1)
    diagonal = numpy.zeros_like(x)
    diagonal[0] = 1200*x[0]**2-400*x[1]+2
    diagonal[-1] = 200
    diagonal[1:-1] = 202 + 1200*x[1:-1]**2 - 400*x[2:]
    H = H + numpy.diag(diagonal)
    return H
""",
                      numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]),
                      np_rosen_hess=[NDArray[float,:]])

    def test_rosen_der(self):
        self.run_test("""import numpy
def np_rosen_der(x):
    xm = x[1:-1]
    xm_m1 = x[:-2]
    xm_p1 = x[2:]
    der = numpy.zeros_like(x)
    der[1:-1] = 200*(xm-xm_m1**2) - 400*(xm_p1 - xm**2)*xm - 2*(1-xm)
    der[0] = -400*x[0]*(x[1]-x[0]**2) - 2*(1-x[0])
    der[-1] = 200*(x[-1]-x[-2]**2)
    return der
""",
                      numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]),
                      np_rosen_der=[NDArray[float,:]])

    def test_rosen(self):
        self.run_test("import numpy\ndef np_rosen(x): return sum(100.0*(x[1:]-x[:-1]**2.0)**2.0 + (1-x[:-1])**2.0)",
                      numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]),
                      np_rosen=[NDArray[float,:]])

    def test_nanargmax0(self):
        self.run_test("def np_nanargmax0(a): from numpy import nanargmax; return nanargmax(a)", numpy.array([[numpy.nan, 4], [2, 3]]),  np_nanargmax0=[NDArray[float,:,:]])

    def test_nanargmin0(self):
        self.run_test("def np_nanargmin0(a): from numpy import nanargmin ; return nanargmin(a)", numpy.array([[numpy.nan, 4], [2, 3]]), np_nanargmin0=[NDArray[float,:,:]])

    def test_nan_to_num0(self):
        self.run_test("def np_nan_to_num0(a): import numpy as np ; return np.nan_to_num(a)", numpy.array([numpy.inf, -numpy.inf, numpy.nan, -128, 128]), np_nan_to_num0=[NDArray[float,:]])

    def test_median0(self):
        self.run_test("def np_median0(a): from numpy import median ; return median(a)", numpy.array([[1, 2], [3, 4]]), np_median0=[NDArray[int,:,:]])

    def test_median1(self):
        self.run_test("def np_median1(a): from numpy import median ; return median(a)", numpy.array([1, 2, 3, 4,5]), np_median1=[NDArray[int,:]])

    def test_median2(self):
        self.run_test("def np_median2(a): from numpy import median ; return median(a, None)", numpy.array([1, 2, 3, 4,5]), np_median2=[NDArray[int,:]])

    def test_median3(self):
        self.run_test("def np_median3(a): from numpy import median ; return median(a, 0)", numpy.array([[1, 2, 3], [4,5,6]]), np_median3=[NDArray[int,:,:]])

    def test_median4(self):
        self.run_test("def np_median4(a): from numpy import median ; return median(a, 1)", numpy.array([[1, 2, 3], [4,5,6]]), np_median4=[NDArray[int,:,:]])

    def test_median5(self):
        self.run_test("def np_median5(a): from numpy import median ; return median(a, -1)", numpy.array([[[1], [2], [3]], [[4],[5],[6]]]), np_median5=[NDArray[int,:,:,:]])

    def test_median6(self):
        self.run_test("def np_median6(l): from numpy import median ; return l + median(l)", numpy.array([3, 1]), np_median6=[NDArray[int, :]])

    def test_mean0(self):
        self.run_test("def np_mean0(a): from numpy import mean ; return mean(a)", numpy.array([[1, 2], [3, 4]]), np_mean0=[NDArray[int,:,:]])

    def test_mean1(self):
        self.run_test("def np_mean1(a): from numpy import mean ; return mean(a, 1)", numpy.array([[1, 2], [3, 4.]]), np_mean1=[NDArray[float,:,:]])

    def test_mean2(self):
        self.run_test("def np_mean2(a): from numpy import mean ; return mean(a)", numpy.array([[[1, 2], [3, 4.]]]), np_mean2=[NDArray[float,:,:,:]])

    def test_mean3(self):
        self.run_test("def np_mean3(a): from numpy import mean ; return mean(a, 0)", numpy.array([[[1, 2], [3, 4.]]]), np_mean3=[NDArray[float,:,:,:]])

    def test_mean4(self):
        self.run_test("def np_mean4(a): from numpy import mean ; return mean(a, 1)", numpy.array([[[1, 2], [3, 4.]]]), np_mean4=[NDArray[float,:,:,:]])

    def test_mean5(self):
        self.run_test("def np_mean5(a): from numpy import mean ; return mean(a, 2)", numpy.array([[[1, 2], [3, 4.]]]), np_mean5=[NDArray[float,:,:,:]])

    def test_var0(self):
        self.run_test("def np_var0(a): return a.var()", numpy.array([[1, 2], [3, 4]], dtype=float), np_var0=[NDArray[float,:,:]])

    def test_var1(self):
        self.run_test("def np_var1(a): from numpy import var ; return var(a, 1)", numpy.array([[1, 2], [3, 4.]]), np_var1=[NDArray[float,:,:]])

    def test_var2(self):
        self.run_test("def np_var2(a): from numpy import var ; return var(a)", numpy.array([[[1, 2], [3, 4.]]]), np_var2=[NDArray[float,:,:,:]])

    def test_var3(self):
        self.run_test("def np_var3(a): from numpy import var ; return var(a, 0)", numpy.array([[[1, 2], [3, 4.]]]), np_var3=[NDArray[float,:,:,:]])

    def test_var4(self):
        self.run_test("def np_var4(a): from numpy import var ; return var(a, 1)", numpy.array([[[1, 2], [3, 4.]]]), np_var4=[NDArray[float,:,:,:]])

    def test_var5(self):
        self.run_test("def np_var5(a): from numpy import var ; return var(a, 2)", numpy.array([[[1, 2], [3, 4.]]]), np_var5=[NDArray[float,:,:,:]])

    def test_var6(self):
        self.run_test("def np_var6(a): from numpy import var ; return var(1j * a)", numpy.array([[[1, 2], [3, 4.]]]), np_var6=[NDArray[float,:,:,:]])

    def test_var7(self):
        self.run_test("def np_var7(a): from numpy import var ; return var(1j * a, 2)", numpy.array([[[1, 2], [3, 4.]]]), np_var7=[NDArray[float,:,:,:]])

    def test_var8(self):
        self.run_test("def np_var8(a): from numpy import var ; return var(1j * a, 2)", numpy.array([[[1, 2], [3, 4]]]), np_var8=[NDArray[int,:,:,:]])

    def test_var9(self):
        self.run_test("def np_var9(a): from numpy import var ; return var(1j * a)", numpy.array([[[1, 2], [3, 4]]]), np_var9=[NDArray[int,:,:,:]])

    def test_std0(self):
        self.run_test("def np_std0(a): from numpy import std ; return std(a)", numpy.array([[[1, 2], [3, 4]]]), np_std0=[NDArray[int, :, :, :]])

    def test_std1(self):
        self.run_test("def np_std1(a): from numpy import std ; return std(a, 0)", numpy.array([[[1, 2], [3, 4]]]), np_std1=[NDArray[int, :, :, :]])

    def test_std2(self):
        self.run_test("def np_std2(a): from numpy import std ; return std(a, 1)", numpy.array([[[1, 2], [3, 4]]]), np_std2=[NDArray[int, :, :, :]])

    def test_std3(self):
        self.run_test("def np_std3(a): from numpy import std ; return std(1j*a, 1)", numpy.array([[[1, 2], [3, 4]]]), np_std3=[NDArray[int, :, :, :]])

    def test_logspace0(self):
        self.run_test("def np_logspace0(start, stop): from numpy import logspace ; start, stop = 3., 4. ; return logspace(start, stop, 4)", 3., 4., np_logspace0=[float, float])

    def test_logspace1(self):
        self.run_test("def np_logspace1(start, stop): from numpy import logspace ; return logspace(start, stop, 4, False)", 3., 4., np_logspace1=[float, float])

    def test_logspace2(self):
        self.run_test("def np_logspace2(start, stop): from numpy import logspace ; return logspace(start, stop, 4, True, 2.0)", 3., 4., np_logspace2=[float, float])

    def test_lexsort0(self):
        self.run_test("def np_lexsort0(surnames): from numpy import lexsort ; first_names = ('Heinrich', 'Galileo', 'Gustav') ; return lexsort((first_names, surnames))", ('Hertz',    'Galilei', 'Hertz'), np_lexsort0=[Tuple[str, str, str]])

    def test_lexsort1(self):
        self.run_test("def np_lexsort1(a): from numpy import lexsort ; b = [1,5,1,4,3,4,4] ; return lexsort((a,b))", [9,4,0,4,0,2,1], np_lexsort1=[List[int]])

    def test_lexsort2(self):
        self.run_test("def np_lexsort2(a): from numpy import lexsort ; return lexsort((a+1,a-1))", numpy.array([1,5,1,4,3,4,4]), np_lexsort2=[NDArray[int,:]])

    def test_issctype0(self):
        self.run_test("def np_issctype0(): from numpy import issctype, int32 ; a = int32 ; return issctype(a)", np_issctype0=[])

    def test_issctype1(self):
        self.run_test("def np_issctype1(): from numpy import issctype ; a = list ; return issctype(a)", np_issctype1=[])

    def test_issctype2(self):
        self.run_test("def np_issctype2(a): from numpy import issctype ; return issctype(a)", 3.1, np_issctype2=[float])

    def test_isscalar0(self):
        self.run_test("def np_isscalar0(a): from numpy import isscalar ; return isscalar(a)", 3.1, np_isscalar0=[float])

    def test_isscalar1(self):
        self.run_test("def np_isscalar1(a): from numpy import isscalar ; return isscalar(a)", [3.1], np_isscalar1=[List[float]])

    def test_isscalar2(self):
        self.run_test("def np_isscalar2(a): from numpy import isscalar ; return isscalar(a)", '3.1', np_isscalar2=[str])

    def test_isrealobj0(self):
        self.run_test("def np_isrealobj0(a): from numpy import isrealobj ; return isrealobj(a)", numpy.array([1,2,3.]), np_isrealobj0=[NDArray[float,:]])

    def test_isrealobj1(self):
        self.run_test("def np_isrealobj1(a): from numpy import isrealobj ; return isrealobj(a)", numpy.array([1,2,3.,4 + 1j]).reshape((2,2)), np_isrealobj1=[NDArray[complex,:,:]])

    def test_isreal0(self):
        self.run_test("def np_isreal0(a): from numpy import isreal ; return isreal(a)", numpy.array([1,2,3.]), np_isreal0=[NDArray[float,:]])

    def test_isreal1(self):
        self.run_test("def np_isreal1(a): from numpy import isreal ; return isreal(a)", numpy.array([1,2,3.,4 + 1j]).reshape((2,2)), np_isreal1=[NDArray[complex,:,:]])

    def test_iscomplex0(self):
        self.run_test("def np_iscomplex0(a): from numpy import iscomplex ; return iscomplex(a)", numpy.array([1, 2, 3.]), np_iscomplex0=[NDArray[float,:]])

    def test_iscomplex1(self):
        self.run_test("def np_iscomplex1(a): from numpy import iscomplex ; return iscomplex(a)", numpy.array([1,2,3.,4 + 1j]).reshape((2,2)), np_iscomplex1=[NDArray[complex,:,:]])

    def test_intersect1d0(self):
        self.run_test("def np_intersect1d0(a): from numpy import intersect1d ; b = [3, 1, 2, 1] ; return intersect1d(a,b)", [1, 3, 4, 3], np_intersect1d0=[List[int]])

    def test_insert0(self):
        self.run_test("def np_insert0(a): from numpy import insert ; return insert(a, 1, 5)", numpy.array([[1, 1], [2, 2], [3, 3]]), np_insert0=[NDArray[int,:,:]])

    def test_insert1(self):
        self.run_test("def np_insert1(a): from numpy import insert ; return insert(a, [1,2], [5,6])", numpy.array([[1, 1], [2, 2], [3, 3]]), np_insert1=[NDArray[int,:,:]])

    def test_insert2(self):
        self.run_test("def np_insert2(a): from numpy import insert ; return insert(a, [1,1], [5.2,6])", numpy.array([[1, 1], [2, 2], [3, 3]]), np_insert2=[NDArray[int,:,:]])

    def test_inner0(self):
        self.run_test("def np_inner0(x): from numpy import inner ; y = 3 ; return inner(x,y)", 2, np_inner0=[int])

    def test_inner1(self):
        self.run_test("def np_inner1(x): from numpy import inner ; y = [2, 3] ; return inner(x,y)", [2, 3], np_inner1=[List[int]])

    def test_indices0(self):
        self.run_test("def np_indices0(s): from numpy import indices ; return indices(s)", (2, 3), np_indices0=[Tuple[int, int]])

    def test_identity0(self):
        self.run_test("def np_identity0(a): from numpy import identity ; return identity(a)", 3, np_identity0=[int])

    def test_identity1(self):
        self.run_test("def np_identity1(a): from numpy import identity ;return identity(a)", 4, np_identity1=[int])

    def test_tofile0(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.randint(0,2**8,1000).astype(numpy.uint8)
        try:
            self.run_test("def np_tofile0(x,file): import numpy ; x.tofile(file); return numpy.fromfile(file)", x, temp_name, np_tofile0=[NDArray[numpy.uint8,:], str])
        finally:
            os.remove(temp_name)

    def test_tofile1(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.randint(0,2**16,1000).astype(numpy.uint16)
        try:
            self.run_test("def np_tofile1(x,file): import numpy ; x.tofile(file); return numpy.fromfile(file)", x, temp_name, np_tofile1=[NDArray[numpy.uint16,:], str])
        finally:
            os.remove(temp_name)

    def test_tofile2(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.randint(0,2**31,1000).astype(numpy.uint32)
        try:
            self.run_test("def np_tofile2(x,file): import numpy ; x.tofile(file); return numpy.fromfile(file)", x, temp_name, np_tofile2=[NDArray[numpy.uint32,:], str])
        finally:
            os.remove(temp_name)

    def test_tofile3(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.random(1000).astype(numpy.float32)
        try:
            self.run_test("def np_tofile3(x,file): import numpy ; x.tofile(file); return numpy.fromfile(file)", x, temp_name, np_tofile3=[NDArray[numpy.float32,:], str])
        finally:
            os.remove(temp_name)

    def test_tofile4(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.random(1000).astype(numpy.float64)
        try:
            self.run_test("def np_tofile4(x,file): import numpy ; x.tofile(file); return numpy.fromfile(file)", x, temp_name, np_tofile4=[NDArray[numpy.float64,:], str])
        finally:
            os.remove(temp_name)

    def test_fromfile0(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.randint(0,2**8,1000).astype(numpy.uint8)
        x.tofile(temp_name)
        try:
            self.run_test("def np_fromfile0(file): from numpy import fromfile, uint8 ; return fromfile(file, uint8)", temp_name, np_fromfile0=[str])
        finally:
            os.remove(temp_name)

    def test_fromfile1(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.randint(0,2**16,1000).astype(numpy.uint16)
        x.tofile(temp_name)
        try:
            self.run_test("def np_fromfile1(file): from numpy import fromfile, uint16 ; return fromfile(file, uint16)", temp_name, np_fromfile1=[str])
        finally:
            os.remove(temp_name)

    def test_fromfile2(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.randint(0,2**31,1000).astype(numpy.uint32)
        x.tofile(temp_name)
        try:
            self.run_test("def np_fromfile2(file): from numpy import fromfile, uint32 ; return fromfile(file, uint32)", temp_name, np_fromfile2=[str])
        finally:
            os.remove(temp_name)

    def test_fromfile3(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.random(1000).astype(numpy.float32)
        x.tofile(temp_name)
        try:
            self.run_test("def np_fromfile3(file): from numpy import fromfile, float32 ; return fromfile(file, float32)", temp_name, np_fromfile3=[str])
        finally:
            os.remove(temp_name)

    def test_fromfile4(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.random(1000).astype(numpy.float64)
        x.tofile(temp_name)
        try:
            self.run_test("def np_fromfile4(file): from numpy import fromfile, float64 ; return fromfile(file, float64)", temp_name, np_fromfile4=[str])
        finally:
            os.remove(temp_name)

    def test_fromfile5(self):
        temp_name = tempfile.mkstemp()[1]
        x = numpy.random.random(1000).astype(numpy.float64)
        x.tofile(temp_name)
        try:
            self.run_test("def np_fromfile5(file): from numpy import fromfile, float64 ; return fromfile(file, float64, 100)", temp_name, np_fromfile5=[str])
        finally:
            os.remove(temp_name)

    def test_fromstring0(self):
        self.run_test("def np_fromstring0(a): from numpy import fromstring, uint8 ; return fromstring(a, uint8)", '\x01\x02', np_fromstring0=[str])

    def test_fromstring1(self):
        self.run_test("def np_fromstring1(a): from numpy import fromstring, uint8 ; a = '\x01\x02\x03\x04' ; return fromstring(a, uint8,3)", '\x01\x02\x03\x04', np_fromstring1=[str])

    def test_fromstring2(self):
        self.run_test("def np_fromstring2(a): from numpy import fromstring, uint32 ; return fromstring(a, uint32,-1, ' ')", '1 2 3 4', np_fromstring2=[str])

    def test_fromstring3(self):
        self.run_test("def np_fromstring3(a): from numpy import fromstring, uint32 ; return fromstring(a, uint32,2, ',')", '1,2, 3, 4', np_fromstring3=[str])

    def test_outer0(self):
        self.run_test("def np_outer0(x): from numpy import outer ; return outer(x, x+2)", numpy.arange(6).reshape(2,3), np_outer0=[NDArray[int,:,:]])

    def test_outer1(self):
        self.run_test("def np_outer1(x): from numpy import outer; return outer(x, range(6))", numpy.arange(6).reshape((2,3)), np_outer1=[NDArray[int,:,:]])

    def test_place0(self):
        self.run_test("def np_place0(x): from numpy import place, ravel ; place(x, x>1, ravel(x**2)); return x", numpy.arange(6).reshape((2,3)), np_place0=[NDArray[int,:,:]])

    def test_place1(self):
        self.run_test("def np_place1(x): from numpy import place ; place(x, x>1, [57, 58]); return x", numpy.arange(6).reshape((2,3)), np_place1=[NDArray[int,:,:]])

    def test_product(self):
        self.run_test("def np_product(x):\n from numpy import product\n return product(x)", numpy.arange(1, 10), np_product=[NDArray[int,:]])

    def test_ptp0(self):
        self.run_test("def np_ptp0(x): return x.ptp()", numpy.arange(4).reshape((2,2)), np_ptp0=[NDArray[int,:,:]])

    def test_ptp1(self):
        self.run_test("def np_ptp1(x): from numpy import ptp ; return ptp(x,0)", numpy.arange(4).reshape((2,2)), np_ptp1=[NDArray[int,:,:]])

    def test_ptp2(self):
        self.run_test("def np_ptp2(x): from numpy import ptp ; return ptp(x,1)", numpy.arange(4).reshape((2,2)), np_ptp2=[NDArray[int,:,:]])

    def test_put0(self):
        self.run_test("def np_put0(x): x.put([0,2], [-44, -55]); return x", numpy.arange(5), np_put0=[NDArray[int,:]])

    def test_put1(self):
        self.run_test("def np_put1(x): from numpy import put ; put(x, [0,2,3], [57, 58]); return x", numpy.arange(6).reshape((2, 3)), np_put1=[NDArray[int,:,:]])

    def test_put2(self):
        self.run_test("def np_put2(x): from numpy import put ; put(x, 2, 57); return x", numpy.arange(6).reshape((2,3)), np_put2=[NDArray[int,:,:]])

    def test_putmask0(self):
        self.run_test("def np_putmask0(x): from numpy import putmask ; putmask(x, x>1, x**2); return x", numpy.arange(6).reshape((2,3)), np_putmask0=[NDArray[int,:,:]])

    def test_putmask1(self):
        self.run_test("def np_putmask1(x): from numpy import putmask; putmask(x, x>1, [57, 58]); return x", numpy.arange(6).reshape((2,3)), np_putmask1=[NDArray[int,:,:]])

    def test_ravel0(self):
        self.run_test("def np_ravel0(x): from numpy import ravel ; return ravel(x)", numpy.arange(6).reshape((2,3)), np_ravel0=[NDArray[int,:,:]])

    def test_ravel1(self):
        self.run_test("def np_ravel1(x): return x.ravel()", numpy.arange(6).reshape((2,3)), np_ravel1=[NDArray[int,:,:]])

    def test_ravel2(self):
        self.run_test("def np_ravel2(x): y = x.ravel(); y[3] = 10; return x", numpy.arange(6).reshape((2,3)), np_ravel2=[NDArray[int,:,:]])

    def test_repeat0(self):
        self.run_test("def np_repeat0(x): from numpy import repeat; return repeat(x, 3)", numpy.arange(3), np_repeat0=[NDArray[int,:]])

    def test_repeat1(self):
        self.run_test("def np_repeat1(x): return x.repeat(3)", numpy.arange(6).reshape(2,3), np_repeat1=[NDArray[int,:,:]])

    def test_repeat2(self):
        self.run_test("def np_repeat2(x): from numpy import repeat; return repeat(x, 4, axis=0)", numpy.arange(6).reshape(2,3), np_repeat2=[NDArray[int,:,:]])

    def test_repeat3(self):
        self.run_test("def np_repeat3(x): from numpy import repeat; return repeat(x, 4, axis=1)", numpy.arange(6).reshape(2,3), np_repeat3=[NDArray[int,:,:]])

    def test_resize4(self):
        self.run_test("def np_resize4(x): from numpy import resize ; return resize(x, (6,7))", numpy.arange(24).reshape((2,3,4)), np_resize4=[NDArray[int, :, :, :]])

    def test_resize3(self):
        self.run_test("def np_resize3(x): from numpy import resize; return resize(x, (6,6))", numpy.arange(24).reshape((2,3,4)), np_resize3=[NDArray[int, :, :, :]])

    def test_resize2(self):
        self.run_test("def np_resize2(x): from numpy import resize; return resize(x, (3,3))", numpy.arange(24).reshape((2,3,4)), np_resize2=[NDArray[int, :, :, :]])

    def test_resize1(self):
        self.run_test("def np_resize1(x): from numpy import resize; return resize(x, 32)", numpy.arange(24), np_resize1=[NDArray[int,:]])

    def test_resize0(self):
        self.run_test("def np_resize0(x): from numpy import resize; return resize(x, 12)", numpy.arange(24), np_resize0=[NDArray[int,:]])

    def test_rollaxis3(self):
        self.run_test("def np_rollaxis3(x): from numpy import rollaxis; return rollaxis(x, 0, 3)", numpy.arange(24).reshape((2,3,4)), np_rollaxis3=[NDArray[int, :, :, :]])

    def test_rollaxis2(self):
        self.run_test("def np_rollaxis2(x): from numpy import rollaxis; return rollaxis(x, 2)", numpy.arange(24).reshape((2,3,4)), np_rollaxis2=[NDArray[int, :, :, :]])

    def test_rollaxis1(self):
        self.run_test("def np_rollaxis1(x): from numpy import rollaxis; return rollaxis(x, 1, 2)", numpy.arange(24).reshape(2,3,4), np_rollaxis1=[NDArray[int, :, :, :]])

    def test_rollaxis0(self):
        self.run_test("def np_rollaxis0(x): from numpy import rollaxis; return rollaxis(x, 1)", numpy.arange(24).reshape(2,3,4), np_rollaxis0=[NDArray[int, :, :, :]])

    def test_roll6(self):
        self.run_test("def np_roll6(x): from numpy import roll; return roll(x[:,:,:-1], -1, 2)", numpy.arange(24).reshape(2,3,4), np_roll6=[NDArray[int, :, :, :]])

    def test_roll5(self):
        self.run_test("def np_roll5(x): from numpy import roll; return roll(x, -1, 2)", numpy.arange(24).reshape(2,3,4), np_roll5=[NDArray[int, :, :, :]])

    def test_roll4(self):
        self.run_test("def np_roll4(x): from numpy import roll; return roll(x, 1, 1)", numpy.arange(24).reshape(2,3,4), np_roll4=[NDArray[int, :, :, :]])

    def test_roll3(self):
        self.run_test("def np_roll3(x): from numpy import roll; return roll(x, -1, 0)", numpy.arange(24).reshape(2,3,4), np_roll3=[NDArray[int, :, :, :]])

    def test_roll2(self):
        self.run_test("def np_roll2(x): from numpy import roll; return roll(x, -1)", numpy.arange(24).reshape(2,3,4), np_roll2=[NDArray[int, :, :, :]])

    def test_roll1(self):
        self.run_test("def np_roll1(x): from numpy import roll; return roll(x, 10)", numpy.arange(24).reshape(2,3,4), np_roll1=[NDArray[int, :, :, :]])

    def test_roll0(self):
        self.run_test("def np_roll0(x): from numpy import roll; return roll(x, 3)", numpy.arange(24).reshape(2,3,4), np_roll0=[NDArray[int, :, :, :]])

    def test_searchsorted3(self):
        self.run_test("def np_searchsorted3(x): from numpy import searchsorted; return searchsorted(x, [[3,4],[1,87]])", numpy.arange(6), np_searchsorted3=[NDArray[int,:]])

    def test_searchsorted2(self):
        self.run_test("def np_searchsorted2(x): from numpy import searchsorted; return searchsorted(x, [[3,4],[1,87]], 'right')", numpy.arange(6), np_searchsorted2=[NDArray[int,:]])

    def test_searchsorted1(self):
        self.run_test("def np_searchsorted1(x): from numpy import searchsorted; return searchsorted(x, 3)", numpy.arange(6), np_searchsorted1=[NDArray[int,:]])

    def test_searchsorted0(self):
        self.run_test("def np_searchsorted0(x): from numpy import searchsorted; return searchsorted(x, 3, 'right')", numpy.arange(6), np_searchsorted0=[NDArray[int,:]])

    def test_rot904(self):
        self.run_test("def np_rot904(x): from numpy import rot90; return rot90(x, 4)", numpy.arange(24).reshape(2,3,4), np_rot904=[NDArray[int, :, :, :]])

    def test_rot903(self):
        self.run_test("def np_rot903(x): from numpy import rot90; return rot90(x, 2)", numpy.arange(24).reshape(2,3,4), np_rot903=[NDArray[int, :, :, :]])

    def test_rot902(self):
        self.run_test("def np_rot902(x): from numpy import rot90; return rot90(x, 3)", numpy.arange(24).reshape(2,3,4), np_rot902=[NDArray[int, :, :, :]])

    def test_rot900(self):
        self.run_test("def np_rot900(x): from numpy import rot90; return rot90(x)", numpy.arange(24).reshape(2,3,4), np_rot900=[NDArray[int, :, :, :]])

    def test_rot901(self):
        self.run_test("def np_rot901(x): from numpy import rot90; return rot90(x)", numpy.arange(4).reshape(2,2), np_rot901=[NDArray[int,:,:]])

    def test_select2(self):
        self.run_test("def np_select2(x): from numpy import select; condlist = [x<3, x>5]; choicelist = [x**3, x**2]; return select(condlist, choicelist)", numpy.arange(10).reshape(2,5), np_select2=[NDArray[int,:,:]])

    def test_select1(self):
        self.run_test("def np_select1(x): from numpy import select; condlist = [x<3, x>5]; choicelist = [x+3, x**2]; return select(condlist, choicelist)", numpy.arange(10), np_select1=[NDArray[int,:]])

    def test_select0(self):
        self.run_test("def np_select0(x): from numpy import select; condlist = [x<3, x>5]; choicelist = [x, x**2]; return select(condlist, choicelist)", numpy.arange(10), np_select0=[NDArray[int,:]])

    def test_sometrue0(self):
        self.run_test("def np_sometrue0(a): from numpy import sometrue ; return sometrue(a)", numpy.array([[True, False], [True, True]]), np_sometrue0=[NDArray[bool,:,:]])

    def test_sometrue1(self):
        self.run_test("def np_sometrue1(a): from numpy import sometrue ; return sometrue(a, 0)", numpy.array([[True, False], [False, False]]), np_sometrue1=[NDArray[bool,:,:]])

    def test_sometrue2(self):
        self.run_test("def np_sometrue2(a): from numpy import sometrue ; return sometrue(a)", [-1, 0, 5], np_sometrue2=[List[int]])

    def test_sort0(self):
        self.run_test("def np_sort0(a): from numpy import sort ; return sort(a)", numpy.array([[1,6],[7,5]]), np_sort0=[NDArray[int,:,:]])

    def test_sort1(self):
        self.run_test("def np_sort1(a): from numpy import sort ; return sort(a)", numpy.array([2, 1, 6, 3, 5]), np_sort1=[NDArray[int,:]])

    def test_sort2(self):
        self.run_test("def np_sort2(a): from numpy import sort ; return sort(a)", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort2=[NDArray[int, :, :, :]])

    def test_sort3(self):
        self.run_test("def np_sort3(a): from numpy import sort ; return sort(a, 0)", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort3=[NDArray[int, :, :, :]])

    def test_sort4(self):
        self.run_test("def np_sort4(a): from numpy import sort ; return sort(a, 1, kind='quicksort')", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort4=[NDArray[int, :, :, :]])

    def test_sort5(self):
        self.run_test("def np_sort5(a): from numpy import sort ; return sort(a, 1, kind='heapsort')", numpy.arange(2*3*5, 0, -1).reshape(2,3,5), np_sort5=[NDArray[int, :, :, :]])

    def test_sort6(self):
        self.run_test("def np_sort6(a): from numpy import sort ; return sort(a, 0, kind='stable')", numpy.arange(2*3*6, 0, -1).reshape(2,3,6), np_sort6=[NDArray[int, :, :, :]])

    def test_sort7(self):
        self.run_test("def np_sort7(a): from numpy import sort ; return sort(a, 2, kind='mergesort')", numpy.arange(2*3*7, 0, -1).reshape(2,3,7), np_sort7=[NDArray[int, :, :, :]])

    def test_sort8(self):
        self.run_test("def np_sort8(a): from numpy import sort ; return sort(a, None)", numpy.arange(2*3*7, 0, -1).reshape(2,3,7), np_sort8=[NDArray[int, :, :, :]])

    def test_sort9(self):
        self.run_test("def np_sort9(a): from numpy import sort ; return sort(2 * a, None)", numpy.arange(2*3*7, 0, -1).reshape(2,3,7), np_sort9=[NDArray[int, :, :, :]])

    def test_sort10(self):
        self.run_test("def np_sort10(a): from numpy import sort ; return sort(3*a, 0)", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort10=[NDArray[int, :, :, :]])

    def test_sort_complex0(self):
        self.run_test("def np_sort_complex0(a): from numpy import sort_complex ; return sort_complex(a)", numpy.array([[1,6],[7,5]]), np_sort_complex0=[NDArray[int,:,:]])

    def test_sort_complex1(self):
        self.run_test("def np_sort_complex1(a): from numpy import sort_complex ; return sort_complex(a)", numpy.array([1 + 2j, 2 - 1j, 3 - 2j, 3 - 3j, 3 + 5j]), np_sort_complex1=[NDArray[complex,:]])

    def test_split0(self):
        self.run_test("def np_split0(a): from numpy import split,array2string ; return list(map(array2string,split(a, 3)))", numpy.arange(12), np_split0=[NDArray[int,:]])

    def test_split1(self):
        self.run_test("def np_split1(a):\n from numpy import split\n try:\n  print(split(a, 5))\n  return False\n except ValueError:\n  return True", numpy.arange(12), np_split1=[NDArray[int,:]])

    def test_split2(self):
        self.run_test("def np_split2(a): from numpy import split, array2string; return list(map(array2string,split(a, [0,1,5])))", numpy.arange(12).reshape(6,2), np_split2=[NDArray[int,:,:]])

    @unittest.skip("Require numpy_fexpr for multidim array")
    def test_take0(self):
        self.run_test("def np_take0(a):\n from numpy import take\n return take(a, [0,1])", numpy.arange(24).reshape(2,3,4), np_take0=[NDArray[int, :, :, :]])

    @unittest.skip("Require numpy_fexpr for multidim array")
    def test_take1(self):
        self.run_test("def np_take1(a):\n from numpy import take\n return take(a, [[0,0,2,2],[1,0,1,2]])", numpy.arange(24).reshape(2,3,4), np_take1=[NDArray[int, :, :, :]])

    @unittest.skip("Require numpy_fexpr with indices")
    def test_take2(self):
        self.run_test("def np_take2(a):\n from numpy import take\n return take(a, [1,0,1,2])", numpy.arange(24), np_take2=[NDArray[int,:]])

    def test_swapaxes_(self):
        self.run_test("def np_swapaxes_(a):\n from numpy import swapaxes\n return swapaxes(a, 1, 2)", numpy.arange(24).reshape(2,3,4), np_swapaxes_=[NDArray[int, :, :, :]])

    def test_tile0(self):
        self.run_test("def np_tile0(a): from numpy import tile ; return tile(a, 3)", numpy.arange(4), np_tile0=[NDArray[int,:]])

    def test_tile1(self):
        self.run_test("def np_tile1(a): from numpy import tile ; return tile(a, (3, 2))", numpy.arange(4), np_tile1=[NDArray[int,:]])

    def test_tile2(self):
        self.run_test("def np_tile2(a): from numpy import tile ; return tile(a, (1, 2))", numpy.arange(12).reshape(3,4), np_tile2=[NDArray[int,:,:]])

    def test_tolist0(self):
        self.run_test("def np_tolist0(a): return a.tolist()", numpy.arange(12), np_tolist0=[NDArray[int,:]])

    def test_tolist1(self):
        self.run_test("def np_tolist1(a): return a.tolist()", numpy.arange(12).reshape(3,4), np_tolist1=[NDArray[int,:,:]])

    def test_tolist2(self):
        self.run_test("def np_tolist2(a): return a.tolist()", numpy.arange(2*3*4*5).reshape(2,3,4,5), np_tolist2=[NDArray[int, :, :, :, :]])

    @unittest.skip("bytes/str confusion")
    def test_tostring0(self):
        self.run_test("def np_tostring0(a): return a.tostring()", numpy.arange(80, 100), np_tostring0=[NDArray[int,:]])

    @unittest.skip("bytes/str confusion")
    def test_tostring1(self):
        self.run_test("def np_tostring1(a): return a.tostring()", numpy.arange(500, 600), np_tostring1=[NDArray[int,:]])

    def test_fromiter0(self):
        self.run_test("def g(): yield 1 ; yield 2\ndef np_fromiter0(): from numpy import fromiter, float32 ; iterable = g() ; return fromiter(iterable, float32)", np_fromiter0=[])

    def test_fromiter1(self):
        self.run_test("def np_fromiter1(): from numpy import fromiter, float32 ; iterable = (x*x for x in range(5)) ; return fromiter(iterable, float32, 5)", np_fromiter1=[])

    def test_fromiter2(self):
        self.run_test("def np_fromiter2(): from numpy import fromiter, float64 ; iterable = (x-x for x in range(5)) ; return fromiter(iterable, count=2, dtype=float64)", np_fromiter2=[])

    def test_fromfunction0(self):
        self.run_test("def np_fromfunction0(s): from numpy import fromfunction ; return fromfunction(lambda i: i == 1, s)", (3,), np_fromfunction0=[Tuple[int]])

    def test_fromfunction1(self):
        self.run_test("def np_fromfunction1(s): from numpy import fromfunction; return fromfunction(lambda i, j: i + j, s)", (3, 3), np_fromfunction1=[Tuple[int, int]])

    def test_flipud0(self):
        self.run_test("def np_flipud0(x): from numpy import flipud ; return flipud(x)", numpy.arange(9).reshape(3,3), np_flipud0=[NDArray[int,:,:]])

    def test_fliplr0(self):
        self.run_test("def np_fliplr0(x): from numpy import fliplr ; return fliplr(x)", numpy.arange(9).reshape(3,3), np_fliplr0=[NDArray[int,:,:]])

    def test_flip3(self):
        self.run_test("def np_flip3(x): from numpy import flip; return flip(x[:,:,:-1], 2)", numpy.arange(24).reshape(2,3,4), np_flip3=[NDArray[int, :, :, :]])

    def test_flip2(self):
        self.run_test("def np_flip2(x): from numpy import flip; return flip(x, 2)", numpy.arange(24).reshape(2,3,4), np_flip2=[NDArray[int, :, :, :]])

    def test_flip1(self):
        self.run_test("def np_flip1(x): from numpy import flip; return flip(x, 1)", numpy.arange(24).reshape(2,3,4), np_flip1=[NDArray[int, :, :, :]])

    def test_flip0(self):
        self.run_test("def np_flip0(x): from numpy import flip; return flip(x, 0)", numpy.arange(24).reshape(2,3,4), np_flip0=[NDArray[int, :, :, :]])

    def test_flatten0(self):
        self.run_test("def np_flatten0(x): return x.flatten()", numpy.array([[1,2], [3,4]]), np_flatten0=[NDArray[int,:,:]])

    def test_flatnonzero0(self):
        self.run_test("def np_flatnonzero0(x): from numpy import flatnonzero ; return flatnonzero(x)", numpy.arange(-2, 3), np_flatnonzero0=[NDArray[int,:]])

    def test_flatnonzero1(self):
        self.run_test("def np_flatnonzero1(x): from numpy import flatnonzero ;  return flatnonzero(x[1:-1])", numpy.arange(-2, 3), np_flatnonzero1=[NDArray[int,:]])

    def test_fix0(self):
        self.run_test("def np_fix0(x): from numpy import fix ; return fix(x)", 3.14, np_fix0=[float])

    def test_fix1(self):
        self.run_test("def np_fix1(x): from numpy import fix ; return fix(x)", 3, np_fix1=[int])

    def test_fix2(self):
        self.run_test("def np_fix2(x): from numpy import fix ; return fix(x)", numpy.array([2.1, 2.9, -2.1, -2.9]), np_fix2=[NDArray[float,:]])

    def test_fix3(self):
        self.run_test("def np_fix3(x): from numpy import fix ; return fix(x)", numpy.array([2.1, 2.9, -2.1, -2.9]), np_fix3=[NDArray[float,:]])

    def test_fix4(self):
        self.run_test("def np_fix4(x): from numpy import fix ; return fix(x+x)", numpy.array([2.1, 2.9, -2.1, -2.9]), np_fix4=[NDArray[float,:]])

    def test_cross1(self):
        self.run_test("def np_cross1(x): from numpy import cross ; return cross(x, [3,4,5])", numpy.array([2.1, 2.9]), np_cross1=[NDArray[float,:]])

    def test_cross2(self):
        self.run_test("def np_cross2(x): from numpy import cross ; return cross(x, -x)", numpy.array([2.1, 2.9, -2.1]), np_cross2=[NDArray[float,:]])

    def test_cross3(self):
        self.run_test("def np_cross3(x): from numpy import cross ; return cross(x, 2 * x)", numpy.array([[2.1, 2.9, -2.9]]), np_cross3=[NDArray[float,:, :]])

    def test_cross4(self):
        self.run_test("def np_cross4(x): from numpy import cross ; return cross(x, [[1,2]])", numpy.array([[2.9, -2.1, -2.9]]), np_cross4=[NDArray[float,:, :]])

    def test_finfo0(self):
        self.run_test("def np_finfo0(): from numpy import finfo, float64 ; x = finfo(float64) ; return x.eps", np_finfo0=[])

    def test_finfo1(self):
        self.run_test("def np_finfo1(x): from numpy import finfo ; f = finfo(x.dtype) ; return f.eps", numpy.ones(1), np_finfo1=[NDArray[float,:]])

    def test_fill0(self):
        self.run_test("def np_fill0(x): x.fill(5) ; return x", numpy.ones((2, 3)), np_fill0=[NDArray[float,:,:]])

    def test_eye0(self):
        self.run_test("def np_eye0(x): from numpy import eye ; return eye(x)", 2, np_eye0=[int])

    def test_eye1(self):
        self.run_test("def np_eye1(x): from numpy import eye ; return eye(x, x+1)", 2, np_eye1=[int])

    def test_eye1b(self):
        self.run_test("def np_eye1b(x): from numpy import eye ; return eye(x, x-1)", 3, np_eye1b=[int])

    def test_eye2(self):
        self.run_test("def np_eye2(x): from numpy import eye ; return eye(x, x, 1)", 2, np_eye2=[int])

    def test_eye3(self):
        self.run_test("def np_eye3(x): from numpy import eye, int32 ; return eye(x, x, 1, int32)", 2, np_eye3=[int])

    def test_eye4(self):
        self.run_test("def np_eye4(x): from numpy import eye, uint32 ; return eye(x, dtype=uint32)", 2, np_eye4=[int])

    def test_ediff1d0(self):
        self.run_test("def np_ediff1d0(x): from numpy import ediff1d ; return ediff1d(x)", [1,2,4,7,0], np_ediff1d0=[List[int]])

    def test_ediff1d1(self):
        self.run_test("def np_ediff1d1(x): from numpy import ediff1d ; return ediff1d(x)", [[1,2,4],[1,6,24]], np_ediff1d1=[List[List[int]]])

    def test_print_slice(self):
        self.run_test("def np_print_slice(a): print(a[:-1])", numpy.arange(12), np_print_slice=[NDArray[int,:]])

    def test_print_expr(self):
        self.run_test("def np_print_expr(a): print(a * 2)", numpy.arange(12), np_print_expr=[NDArray[int,:]])

    def test_broadcast_to0(self):
        self.run_test("def np_broadcast_to0(a, s): import numpy as np; return np.broadcast_to(a, s)", numpy.arange(12), (4, 12), np_broadcast_to0=[NDArray[int,:], Tuple[int, int]])

    def test_broadcast_to1(self):
        self.run_test("def np_broadcast_to1(a, s): import numpy as np; return np.broadcast_to(a, s)", numpy.arange(1), (4, 12), np_broadcast_to1=[NDArray[int,:], Tuple[int, int]])

    def test_broadcast_to2(self):
        self.run_test("def np_broadcast_to2(a, s): import numpy as np; return np.broadcast_to(a, s)", 5., (12, 2), np_broadcast_to2=[float, Tuple[int, int]])

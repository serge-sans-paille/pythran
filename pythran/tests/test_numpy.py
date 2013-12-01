import unittest
from test_env import TestEnv
import numpy

class TestNumpy(TestEnv):
    def test_numpy_int16(self):
        self.run_test("def numpy_int16(n): import numpy ; return numpy.ones(n, numpy.int16)", 5, numpy_int16=[int])

    def test_numpy_uint16(self):
        self.run_test("def numpy_uint16(n): import numpy ; return numpy.ones(n, numpy.uint16)", 5, numpy_uint16=[int])

    def test_numpy_uint64(self):
        self.run_test("def numpy_uint64(n): import numpy ; return numpy.ones(n, numpy.uint64)", 5, numpy_uint64=[int])

    def test_numpy_float(self):
        self.run_test("def numpy_float(n): import numpy ; return numpy.ones(n, numpy.float)", 5, numpy_float=[int])

    def test_numpy_complex(self):
        self.run_test("def numpy_complex(n): import numpy ; return numpy.ones(n, numpy.complex)", 5, numpy_complex=[int])

    def test_numpy_complex64(self):
        self.run_test("def numpy_complex64(n): import numpy ; return numpy.ones(n, numpy.complex64)", 5, numpy_complex64=[int])

    def test_numpy_double(self):
        self.run_test("def numpy_double(n): import numpy ; return numpy.ones(n, numpy.double)", 5, numpy_double=[int])

    def test_assign_gsliced_array(self):
        self.run_test("""def assign_gsliced_array():
   import numpy as np;
   a = np.array([[[1,2],[3,4]],[[5,6],[7,8]]])
   b = np.array([[[9,10],[11,12]],[[13,14],[15,16]]])
   a[:,:] = b[:,:]
   return a,b;""", assign_gsliced_array=[])

    def test_assign_sliced_array(self):
        self.run_test("""def assign_sliced_array():
   import numpy as np;
   a = np.array([1,2,3]);
   b = np.array([1,2,3]);
   c=a[1:]
   c=b[1:]
   b[2] = -1;
   return c;""", assign_sliced_array=[])

    def test_filter_array_0(self):
        self.run_test('def filter_array_0(n): import numpy ; a = numpy.zeros(n) ; return a[a>1]', 10, filter_array_0=[int])

    def test_filter_array_1(self):
        self.run_test('def filter_array_1(n): import numpy ; a = numpy.arange(n) ; return a[a>4]', 10, filter_array_1=[int])

    def test_filter_array_2(self):
        self.run_test('def filter_array_2(n): import numpy ; a = numpy.arange(n) ; return (a+a)[a>4]', 10, filter_array_2=[int])

    def test_filter_array_3(self):
        self.run_test('def filter_array_3(n): import numpy ; a = numpy.arange(n) ; return (-a)[a>4]', 10, filter_array_3=[int])

    def test_filter_array_4(self):
        self.run_test('def filter_array_4(n): import numpy ; a = numpy.arange(n) ; return a[1:-1][a[1:-1]>4]', 10, filter_array_4=[int])

    def test_filter_array_5(self):
        self.run_test('def filter_array_5(n): import numpy ; a = numpy.arange(n) ; return (a[1:-1])[a[1:-1]>4]', 10, filter_array_5=[int])

    def test_assign_ndarray(self):
        self.run_test("""def assign_ndarray(t):
                           import numpy as np;
                           a = np.array([1,2,3]);
                           b = np.array([1,2,3]);
                           if t:
                             c = a;
                           else:
                             c=b;
                           if t:
                             c=b;
                           b[0] = -1;
                           return c;
                           """,
                           1,assign_ndarray=[int])

    def test_bitwise_nan_bool(self):
        self.run_test("def np_bitwise_nan_bool(): import numpy as np ; a = np.arange(10) ; return ~(a<5)", np_bitwise_nan_bool=[])

    def test_frexp0(self):
        self.run_test("def np_frexp0(): import numpy as np ; a = 1.5 ; return np.frexp(a)", np_frexp0=[])

    def test_frexp1(self):
        self.run_test("def np_frexp1(): import numpy as np ; a = np.array([1.1,2.2,3.3]) ; return np.frexp(a)", np_frexp1=[])

    def test_frexp2(self):
        self.run_test("def np_frexp2(): import numpy as np ; a = np.array([1.1,2.2,3.3]) ; return np.frexp(a+a)", np_frexp2=[])

    def test_gslice0(self):
        self.run_test("def np_gslice0(): import numpy as np ; a = np.array(range(10*9)).reshape(10,9) ; return a[1:9,5:7]", np_gslice0=[])

    def test_gslice1(self):
        self.run_test("def np_gslice1(): import numpy as np ; a = np.array(range(10*9*8)).reshape(10,9,8) ; return a[1:9,0:1, 3:6]", np_gslice1=[])

    def test_gslice2(self):
        self.run_test("def np_gslice2(): import numpy as np ; a = np.array(range(10*9*8)).reshape(10,9,8) ; return a[:,0:1, 3:6]", np_gslice2=[])

    def test_gslice3(self):
        self.run_test("def np_gslice3(): import numpy as np ; a = np.array(range(10*9*8)).reshape(10,9,8) ; return a[:-1,0:-1, -3:7]", np_gslice3=[])

    def test_gslice4(self):
        self.run_test("def np_gslice4(): import numpy as np ; a = np.array(range(10*9*8)).reshape(10,9,8) ; return a[1,0:-1, -3:7]", np_gslice4=[])

    def test_gslice5(self):
        self.run_test("def np_gslice5(): import numpy as np ; a = np.array(range(10*9*8)).reshape(10,9,8) ; return a[1,0:-1, 7]", np_gslice5=[])

    def test_ndindex0(self):
        self.run_test("def np_ndindex0(): import numpy as np ; return [x for x in np.ndindex(5,6)]", np_ndindex0=[])

    def test_ndindex1(self):
        self.run_test("def np_ndindex1(): import numpy as np ; a = 3 ; return [x for x in np.ndindex(a)]", np_ndindex1=[])

    def test_ndenumerate0(self):
        self.run_test("def np_ndenumerate0(): import numpy as np ; a = np.array([[1, 2], [3, 4]]) ; return [x for x in np.ndenumerate(a)]", np_ndenumerate0=[])

    def test_ndenumerate1(self):
        self.run_test("def np_ndenumerate1(): import numpy as np ; a = np.array([1, 2, 3, 4]) ; return [x for x in np.ndenumerate(a)]", np_ndenumerate1=[])

    def test_nansum0(self):
        self.run_test("def np_nansum0(): import numpy as np ; a = np.array([[1, 2], [3, np.nan]]) ; return np.nansum(a)" , np_nansum0=[])

    def test_nansum1(self):
        self.run_test("def np_nansum1(): import numpy as np ; a = np.array([[1, 2], [np.NINF, np.nan]]) ; return np.nansum(a)" , np_nansum1=[])

    def test_nansum2(self):
        self.run_test("def np_nansum2(): import numpy as np ; a= [1, np.nan] ; return np.nansum(a)", np_nansum2=[])

    def test_nanmin0(self):
        self.run_test("def np_nanmin0(): import numpy as np ; a = np.array([[1, 2], [3, np.nan]]) ; return np.nanmin(a)" , np_nanmin0=[])

    def test_nanmin1(self):
        self.run_test("def np_nanmin1(): import numpy as np ; a = np.array([[1, 2], [np.NINF, np.nan]]) ; return np.nanmin(a)" , np_nanmin1=[])

    def test_nanmax0(self):
        self.run_test("def np_nanmax0(): import numpy as np ; a = np.array([[1, 2], [3, np.nan]]) ; return np.nanmax(a)" , np_nanmax0=[])

    def test_nanmax1(self):
        self.run_test("def np_nanmax1(): import numpy as np ; a = np.array([[1, 2], [np.inf, np.nan]]) ; return np.nanmax(a)" , np_nanmax1=[])

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
""", [1.0, 2.0, 3.0], np_func2=[[float]])

    def test_np_peval(self):
        self.run_test("""import numpy
def np_peval(x, p):
    return p[0]*numpy.sin(2*numpy.pi*p[1]*x+p[2])
""", 12., [1.0, 2.0, 3.0], np_peval=[float, [float]])

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
""", [-1.0, 1.0], -1.0, np_func_deriv=[[float], float])

    def test_np_func(self):
        self.run_test("""import numpy
def np_func(x, sign=1.0):
    return sign*(2*x[0]*x[1] + 2*x[0] - x[0]**2 - 2*x[1]**2)
""", [-1.0, 1.0], -1.0, np_func=[[float], float])

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
                      runas="""
import numpy; np_rosen_hess_p(numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]), numpy.array([2.3, 1.7, 1.8, 2.9, 2.2]))""",
                      np_rosen_hess_p=[numpy.array([float]), numpy.array([float])])

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
                      runas="import numpy; np_rosen_hess(numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]))",
                      np_rosen_hess=[numpy.array([float])])

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
                      runas="import numpy; np_rosen_der( numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]))",
                      np_rosen_der=[numpy.array([float])])

    def test_rosen(self):
        self.run_test("import numpy\ndef np_rosen(x): return sum(100.0*(x[1:]-x[:-1]**2.0)**2.0 + (1-x[:-1])**2.0)",
                      runas="import numpy; np_rosen(numpy.array([1.3, 0.7, 0.8, 1.9, 1.2]))",
                      np_rosen=[numpy.array([float])])

    def test_nanargmax0(self):
        self.run_test("def np_nanargmax0(): from numpy import array, nanargmax, nan ; a = array([[nan, 4], [2, 3]]) ; return nanargmax(a)", np_nanargmax0=[])

    def test_nanargmin0(self):
        self.run_test("def np_nanargmin0(): from numpy import array, nanargmin, nan ; a = array([[nan, 4], [2, 3]]) ; return nanargmin(a)", np_nanargmin0=[])

    def test_nan_to_num0(self):
        self.run_test("def np_nan_to_num0(): import numpy as np ; a = np.array([np.inf, -np.inf, np.nan, -128, 128]) ; return np.nan_to_num(a)", np_nan_to_num0=[])

    def test_median0(self):
        self.run_test("def np_median0(): from numpy import array, median ; a = array([[1, 2], [3, 4]]) ; return median(a)", np_median0=[])

    def test_median1(self):
        self.run_test("def np_median1(): from numpy import array, median ; a = array([1, 2, 3, 4,5]) ; return median(a)", np_median1=[])

    def test_mean0(self):
        self.run_test("def np_mean0(): from numpy import array, mean ; a = array([[1, 2], [3, 4]]) ; return mean(a)", np_mean0=[])

    def test_logspace0(self):
        self.run_test("def np_logspace0(): from numpy import logspace ; start, stop = 3., 4. ; return logspace(start, stop, 4)", np_logspace0=[])

    def test_logspace1(self):
        self.run_test("def np_logspace1(): from numpy import logspace ; start, stop = 3., 4. ; return logspace(start, stop, 4, False)", np_logspace1=[])

    def test_logspace2(self):
        self.run_test("def np_logspace2(): from numpy import logspace ; start, stop = 3., 4. ; return logspace(start, stop, 4, True, 2.0)", np_logspace2=[])

    def test_lexsort0(self):
        self.run_test("def np_lexsort0(): from numpy import lexsort ; surnames =    ('Hertz',    'Galilei', 'Hertz') ; first_names = ('Heinrich', 'Galileo', 'Gustav') ; return lexsort((first_names, surnames))", np_lexsort0=[])

    def test_lexsort1(self):
        self.run_test("def np_lexsort1(): from numpy import lexsort ; a  = [1,5,1,4,3,4,4]; b = [9,4,0,4,0,2,1] ; return lexsort((a,b))", np_lexsort1=[])

    def test_item0(self):
        self.run_test("def np_item0(): from numpy import array ; a = array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]) ; return a.item(3)", np_item0=[])

    def test_item1(self):
        self.run_test("def np_item1(): from numpy import array ; a = array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]) ; return a.item(7)", np_item1=[])

    def test_item2(self):
        self.run_test("def np_item2(): from numpy import array ; a = array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]) ; return a.item((0,1))", np_item2=[])

    def test_item3(self):
        self.run_test("def np_item3(): from numpy import array ; a = array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]) ; return a.item((2,2))", np_item3=[])

    def test_issctype0(self):
        self.run_test("def np_issctype0(): from numpy import issctype, int32 ; a = int32 ; return issctype(a)", np_issctype0=[])

    def test_issctype1(self):
        self.run_test("def np_issctype1(): from numpy import issctype ; a = list ; return issctype(a)", np_issctype1=[])

    @unittest.skip('NIY')
    def test_issctype2(self):
        self.run_test("def np_issctype2(): from numpy import issctype ; a = 3.1 ; return issctype(a)", np_issctype2=[])

    def test_isscalar0(self):
        self.run_test("def np_isscalar0(): from numpy import isscalar ; a = 3.1 ; return isscalar(a)", np_isscalar0=[])

    def test_isscalar1(self):
        self.run_test("def np_isscalar1(): from numpy import isscalar ; a = [3.1] ; return isscalar(a)", np_isscalar1=[])

    def test_isscalar2(self):
        self.run_test("def np_isscalar2(): from numpy import isscalar ; a = '3.1' ; return isscalar(a)", np_isscalar2=[])

    def test_isrealobj0(self):
        self.run_test("def np_isrealobj0(): from numpy import array, isrealobj ; a = array([1,2,3.]) ; return isrealobj(a)", np_isrealobj0=[])

    def test_isrealobj1(self):
        self.run_test("def np_isrealobj1(): from numpy import array, isrealobj ; a = array([1,2,3.,4 + 1j]).reshape(2,2) ; return isrealobj(a)", np_isrealobj1=[])

    def test_isreal0(self):
        self.run_test("def np_isreal0(): from numpy import array, isreal ; a = array([1,2,3.]) ; return isreal(a)", np_isreal0=[])

    def test_isreal1(self):
        self.run_test("def np_isreal1(): from numpy import array, isreal ; a = array([1,2,3.,4 + 1j]).reshape(2,2) ; return isreal(a)", np_isreal1=[])

    def test_iscomplex0(self):
        self.run_test("def np_iscomplex0(): from numpy import array, iscomplex ; a = array([1,2,3.]) ; return iscomplex(a)", np_iscomplex0=[])

    def test_iscomplex1(self):
        self.run_test("def np_iscomplex1(): from numpy import array, iscomplex ; a = array([1,2,3.,4 + 1j]).reshape(2,2) ; return iscomplex(a)", np_iscomplex1=[])

    def test_intersect1d0(self):
        self.run_test("def np_intersect1d0(): from numpy import intersect1d ; a,b = [1, 3, 4, 3], [3, 1, 2, 1] ; return intersect1d(a,b)", np_intersect1d0=[])

    def test_insert0(self):
        self.run_test("def np_insert0(): from numpy import array, insert ; a = array([[1, 1], [2, 2], [3, 3]]) ; return insert(a, 1, 5)", np_insert0=[])

    def test_insert1(self):
        self.run_test("def np_insert1(): from numpy import array, insert ; a = array([[1, 1], [2, 2], [3, 3]]) ; return insert(a, [1,2], [5,6])", np_insert1=[])

    def test_insert2(self):
        self.run_test("def np_insert2(): from numpy import array, insert ; a = array([[1, 1], [2, 2], [3, 3]]) ; return insert(a, [1,1], [5.2,6,7])", np_insert2=[])

    def test_inner0(self):
        self.run_test("def np_inner0(): from numpy import array, inner ; x, y = 2, 3 ; return inner(x,y)", np_inner0=[])

    def test_inner1(self):
        self.run_test("def np_inner1(): from numpy import array, inner ; x, y = [2, 3], [2, 3] ; return inner(x,y)", np_inner1=[])

    def test_indices0(self):
        self.run_test("def np_indices0(): from numpy import indices ; s = (2,3) ; return indices(s)", np_indices0=[])

    def test_identity0(self):
        self.run_test("def np_identity0(): from numpy import identity ; a = 3; return identity(a)", np_identity0=[])

    def test_identity1(self):
        self.run_test("def np_identity1(): from numpy import identity, uint8 ; a = 4; return identity(a)", np_identity1=[])

    def test_fromstring0(self):
        self.run_test("def np_fromstring0(): from numpy import fromstring, uint8 ; a = '\x01\x02' ; return fromstring(a, uint8)", np_fromstring0=[])

    def test_fromstring1(self):
        self.run_test("def np_fromstring1(): from numpy import fromstring, uint8 ; a = '\x01\x02\x03\x04' ; return fromstring(a, uint8,3)", np_fromstring1=[])

    def test_fromstring2(self):
        self.run_test("def np_fromstring2(): from numpy import fromstring, uint32 ; a = '1 2 3 4' ; return fromstring(a, uint32,-1, ' ')", np_fromstring2=[])

    def test_fromstring3(self):
        self.run_test("def np_fromstring3(): from numpy import fromstring, uint32 ; a = '1,2, 3, 4' ; return fromstring(a, uint32,2, ',')", np_fromstring3=[])

    def test_outer0(self):
        self.run_test("def np_outer0(): from numpy import outer, arange, ravel ; x = arange(6).reshape(2,3); return outer(x, x+2)", np_outer0=[])

    def test_outer1(self):
        self.run_test("def np_outer1(): from numpy import outer, arange ; x = arange(6).reshape(2,3); return outer(x, range(6))", np_outer1=[])

    def test_place0(self):
        self.run_test("def np_place0(): from numpy import place, arange, ravel ; x = arange(6).reshape(2,3); place(x, x>1, ravel(x**2)); return x", np_place0=[])

    def test_place1(self):
        self.run_test("def np_place1(): from numpy import place, arange ; x = arange(6).reshape(2,3); place(x, x>1, [57, 58]); return x", np_place1=[])

    def test_product(self):
        self.run_test("def np_product():\n from numpy import arange,product\n return product(arange(1, 10))", np_product=[])

    def test_prod_(self):
        self.run_test("def np_prod_():\n from numpy import arange,prod\n return arange(1, 10).prod()", np_prod_=[])

    def test_prod_expr(self):
        self.run_test("def np_prod_expr():\n from numpy import arange, ones, prod\n return (arange(10)+ones(10)).prod()", np_prod_expr=[])

    def test_prod2_(self):
        self.run_test("def np_prod2_():\n from numpy import arange,prod\n return arange(1, 11).reshape(2,5).prod()", np_prod2_=[])

    def test_prod3_(self):
        self.run_test("def np_prod3_():\n from numpy import arange,prod\n return arange(1, 11).reshape(2,5).prod(1)", np_prod3_=[])

    def test_prod4_(self):
        self.run_test("def np_prod4_():\n from numpy import arange,prod\n return arange(1, 11).reshape(2,5).prod(0)", np_prod4_=[])

    def test_prod5_(self):
        self.run_test("def np_prod5_():\n from numpy import arange,prod\n return arange(1, 11).prod(0)", np_prod5_=[])

    def test_ptp0(self):
        self.run_test("def np_ptp0(): from numpy import ptp, arange ; x = arange(4).reshape(2,2); return ptp(x)", np_ptp0=[])

    def test_ptp1(self):
        self.run_test("def np_ptp1(): from numpy import ptp, arange ; x = arange(4).reshape(2,2); return ptp(x,0)", np_ptp1=[])

    def test_ptp2(self):
        self.run_test("def np_ptp2(): from numpy import ptp, arange ; x = arange(4).reshape(2,2); return ptp(x,1)", np_ptp2=[])

    def test_put0(self):
        self.run_test("def np_put0(): from numpy import put, arange ; x = arange(5); put(x, [0,2], [-44, -55]); return x", np_put0=[])

    def test_put1(self):
        self.run_test("def np_put1(): from numpy import put, arange ; x = arange(6).reshape(2,3); put(x, [0,2,3], [57, 58]); return x", np_put1=[])

    def test_put2(self):
        self.run_test("def np_put2(): from numpy import put, arange ; x = arange(6).reshape(2,3); put(x, 2, 57); return x", np_put2=[])

    def test_putmask0(self):
        self.run_test("def np_putmask0(): from numpy import putmask, arange ; x = arange(6).reshape(2,3); putmask(x, x>1, x**2); return x", np_putmask0=[])

    def test_putmask1(self):
        self.run_test("def np_putmask1(): from numpy import putmask, arange ; x = arange(6).reshape(2,3); putmask(x, x>1, [57, 58]); return x", np_putmask1=[])

    def test_ravel(self):
        self.run_test("def np_ravel(): from numpy import ravel, arange ; x = arange(6).reshape(2,3); return ravel(x)", np_ravel=[])

    def test_repeat(self):
        self.run_test("def np_repeat(): from numpy import repeat, arange ; x = arange(3); return repeat(x, 3)", np_repeat=[])

    def test_resize3(self):
        self.run_test("def np_resize3(): from numpy import resize, arange ; x = arange(24).reshape(2,3,4); return resize(x, (6,6))", np_resize3=[])

    def test_resize2(self):
        self.run_test("def np_resize2(): from numpy import resize, arange ; x = arange(24).reshape(2,3,4); return resize(x, (3,3))", np_resize2=[])

    def test_resize1(self):
        self.run_test("def np_resize1(): from numpy import resize, arange ; x = arange(24); return resize(x, 32)", np_resize1=[])

    def test_resize0(self):
        self.run_test("def np_resize0(): from numpy import resize, arange ; x = arange(24); return resize(x, 12)", np_resize0=[])

    def test_rollaxis2(self):
        self.run_test("def np_rollaxis2(): from numpy import rollaxis, arange ; x = arange(24).reshape(2,3,4); return rollaxis(x, 2)", np_rollaxis2=[])

    def test_rollaxis1(self):
        self.run_test("def np_rollaxis1(): from numpy import rollaxis, arange ; x = arange(24).reshape(2,3,4); return rollaxis(x, 1, 2)", np_rollaxis1=[])

    def test_rollaxis0(self):
        self.run_test("def np_rollaxis0(): from numpy import rollaxis, arange ; x = arange(24).reshape(2,3,4); return rollaxis(x, 1)", np_rollaxis0=[])

    def test_roll2(self):
        self.run_test("def np_roll2(): from numpy import roll, arange ; x = arange(6).reshape(2,3); return roll(x, -1)", np_roll2=[])

    def test_roll1(self):
        self.run_test("def np_roll1(): from numpy import roll, arange ; x = arange(6).reshape(2,3); return roll(x, 10)", np_roll1=[])

    def test_roll0(self):
        self.run_test("def np_roll0(): from numpy import roll, arange ; x = arange(6).reshape(2,3); return roll(x, 3)", np_roll0=[])

    def test_searchsorted3(self):
        self.run_test("def np_searchsorted3(): from numpy import searchsorted, arange ; x = arange(6); return searchsorted(x, [[3,4],[1,87]])", np_searchsorted3=[])

    def test_searchsorted2(self):
        self.run_test("def np_searchsorted2(): from numpy import searchsorted, arange ; x = arange(6); return searchsorted(x, [[3,4],[1,87]], 'right')", np_searchsorted2=[])

    def test_searchsorted1(self):
        self.run_test("def np_searchsorted1(): from numpy import searchsorted, arange ; x = arange(6); return searchsorted(x, 3)", np_searchsorted1=[])

    def test_searchsorted0(self):
        self.run_test("def np_searchsorted0(): from numpy import searchsorted, arange ; x = arange(6); return searchsorted(x, 3, 'right')", np_searchsorted0=[])

    def test_rank1(self):
        self.run_test("def np_rank1(): from numpy import rank, arange ; x = arange(24).reshape(2,3,4); return rank(x)", np_rank1=[])

    def test_rank0(self):
        self.run_test("def np_rank0(): from numpy import rank, arange ; x = arange(6); return rank(x)", np_rank0=[])

    def test_rot904(self):
        self.run_test("def np_rot904(): from numpy import rot90, arange ; x = arange(24).reshape(2,3,4); return rot90(x, 4)", np_rot904=[])

    def test_rot903(self):
        self.run_test("def np_rot903(): from numpy import rot90, arange ; x = arange(24).reshape(2,3,4); return rot90(x, 2)", np_rot903=[])

    def test_rot902(self):
        self.run_test("def np_rot902(): from numpy import rot90, arange ; x = arange(24).reshape(2,3,4); return rot90(x, 3)", np_rot902=[])

    def test_rot900(self):
        self.run_test("def np_rot900(): from numpy import rot90, arange ; x = arange(24).reshape(2,3,4); return rot90(x)", np_rot900=[])

    def test_rot901(self):
        self.run_test("def np_rot901(): from numpy import rot90, arange ; x = arange(4).reshape(2,2); return rot90(x)", np_rot901=[])

    def test_select2(self):
        self.run_test("def np_select2(): from numpy import select, arange ; x = arange(10).reshape(2,5); condlist = [x<3, x>5]; choicelist = [x, x**2]; return select(condlist, choicelist)", np_select2=[])

    def test_select1(self):
        self.run_test("def np_select1(): from numpy import select, arange ; x = arange(10); condlist = [x<3, x>5]; choicelist = [x+3, x**2]; return select(condlist, choicelist)", np_select1=[])

    def test_select0(self):
        self.run_test("def np_select0(): from numpy import select, arange ; x = arange(10); condlist = [x<3, x>5]; choicelist = [x, x**2]; return select(condlist, choicelist)", np_select0=[])

    def test_sometrue0(self):
        self.run_test("def np_sometrue0(): from numpy import sometrue, array ; a = array([[True, False], [True, True]]) ; return sometrue(a)", np_sometrue0=[])

    def test_sometrue1(self):
        self.run_test("def np_sometrue1(): from numpy import sometrue, array ; a = array([[True, False], [False, False]]) ; return sometrue(a, 0)", np_sometrue1=[])

    def test_sometrue2(self):
        self.run_test("def np_sometrue2(): from numpy import sometrue ; a = [-1, 0, 5] ; return sometrue(a)", np_sometrue2=[])

    def test_sort0(self):
        self.run_test("def np_sort0(): from numpy import array, sort ; a = array([[1,6],[7,5]]) ; return sort(a)", np_sort0=[])

    def test_sort1(self):
        self.run_test("def np_sort1(): from numpy import array, sort ; a = array([2, 1, 6, 3, 5]) ; return sort(a)", np_sort1=[])

    def test_sort2(self):
        self.run_test("def np_sort2(): from numpy import arange, sort ; a = arange(2*3*4, 0, -1).reshape(2,3,4) ; return sort(a)", np_sort2=[])

    def test_sort3(self):
        self.run_test("def np_sort3(): from numpy import arange, sort ; a = arange(2*3*4, 0, -1).reshape(2,3,4) ; return sort(a, 0)", np_sort3=[])

    def test_sort4(self):
        self.run_test("def np_sort4(): from numpy import arange, sort ; a = arange(2*3*4, 0, -1).reshape(2,3,4) ; return sort(a, 1)", np_sort4=[])

    def test_sort_complex0(self):
        self.run_test("def np_sort_complex0(): from numpy import array, sort_complex ; a = array([[1,6],[7,5]]) ; return sort_complex(a)", np_sort_complex0=[])

    def test_sort_complex1(self):
        self.run_test("def np_sort_complex1(): from numpy import array, sort_complex ; a = array([1 + 2j, 2 - 1j, 3 - 2j, 3 - 3j, 3 + 5j]) ; return sort_complex(a)", np_sort_complex1=[])

    def test_split0(self):
        self.run_test("def np_split0(): from numpy import arange, split,array2string ; a = arange(12) ; return map(array2string,split(a, 3))", np_split0=[])

    def test_split1(self):
        self.run_test("def np_split1():\n from numpy import arange, split\n a = arange(12)\n try:\n  split(a, 5)\n  return False\n except ValueError:\n  return True", np_split1=[])

    def test_split2(self):
        self.run_test("def np_split2(): from numpy import arange, split, array2string ; a = arange(12).reshape(6,2); return map(array2string,split(a, [0,1,5]))", np_split2=[])

    def test_take0(self):
        self.run_test("def np_take0():\n from numpy import arange, take\n a = arange(24).reshape(2,3,4)\n return take(a, [0,1])", np_take0=[])

    def test_take1(self):
        self.run_test("def np_take1():\n from numpy import arange, take\n a = arange(24).reshape(2,3,4)\n return take(a, [[0,0,2,2],[1,0,1,2]])", np_take1=[])

    def test_swapaxes_(self):
        self.run_test("def np_swapaxes_():\n from numpy import arange, swapaxes\n a = arange(24).reshape(2,3,4)\n return swapaxes(a, 1, 2)", np_swapaxes_=[])

    def test_tile0(self):
        self.run_test("def np_tile0(): from numpy import arange, tile ; a = arange(4) ; return tile(a, 3)", np_tile0=[])

    def test_tile1(self):
        self.run_test("def np_tile1(): from numpy import arange, tile ; a = arange(4) ; return tile(a, (3, 2))", np_tile1=[])

    def test_tolist0(self):
        self.run_test("def np_tolist0(): from numpy import arange ; a = arange(12) ; return a.tolist()", np_tolist0=[])

    def test_tolist1(self):
        self.run_test("def np_tolist1(): from numpy import arange ; a = arange(12).reshape(3,4) ; return a.tolist()", np_tolist1=[])

    def test_tolist2(self):
        self.run_test("def np_tolist2(): from numpy import arange ; a = arange(2*3*4*5).reshape(2,3,4,5) ; return a.tolist()", np_tolist2=[])

    def test_tostring0(self):
        self.run_test("def np_tostring0(): from numpy import arange ; a = arange(80, 100) ; return a.tostring()", np_tostring0=[])

    def test_tostring1(self):
        self.run_test("def np_tostring1(): from numpy import arange ; a = arange(500, 600) ; return a.tostring()", np_tostring1=[])

    def test_fromiter0(self):
        self.run_test("def g(): yield 1 ; yield 2\ndef np_fromiter0(): from numpy import fromiter, float32 ; iterable = g() ; return fromiter(iterable, float32)", np_fromiter0=[])

    def test_fromiter1(self):
        self.run_test("def np_fromiter1(): from numpy import fromiter, float32 ; iterable = (x*x for x in range(5)) ; return fromiter(iterable, float32, 5)", np_fromiter1=[])

    def test_fromfunction0(self):
        self.run_test("def np_fromfunction0(): from numpy import fromfunction ; s = (3,) ; return fromfunction(lambda i: i == 1, s)", np_fromfunction0=[])

    def test_fromfunction1(self):
        self.run_test("def np_fromfunction1(): from numpy import fromfunction; s = (3,3) ; return fromfunction(lambda i, j: i + j, s)", np_fromfunction1=[])

    def test_flipud0(self):
        self.run_test("def np_flipud0(): from numpy import flipud, diag ; x = diag([1.,2.,3.]) ; return flipud(x)", np_flipud0=[])

    def test_fliplr0(self):
        self.run_test("def np_fliplr0(): from numpy import fliplr, diag ; x = diag([1.,2.,3.]) ; return fliplr(x)", np_fliplr0=[])

    def test_flatten0(self):
        self.run_test("def np_flatten0(): from numpy import array; x = array([[1,2], [3,4]]) ; return x.flatten()", np_flatten0=[])

    def test_flatnonzero0(self):
        self.run_test("def np_flatnonzero0(): from numpy import arange, flatnonzero ; x = arange(-2, 3) ; return flatnonzero(x)", np_flatnonzero0=[])

    def test_fix0(self):
        self.run_test("def np_fix0(): from numpy import fix, array ; x = 3.14 ; return fix(x)", np_fix0=[])

    def test_fix1(self):
        self.run_test("def np_fix1(): from numpy import fix, array ; x = 3 ; return fix(x)", np_fix1=[])

    def test_fix2(self):
        self.run_test("def np_fix2(): from numpy import fix, array ; x = [2.1, 2.9, -2.1, -2.9] ; return fix(x)", np_fix2=[])

    def test_fix3(self):
        self.run_test("def np_fix3(): from numpy import fix, array ; x = array([2.1, 2.9, -2.1, -2.9]) ; return fix(x)", np_fix3=[])

    def test_fix4(self):
        self.run_test("def np_fix4(): from numpy import fix, array ; x = array([2.1, 2.9, -2.1, -2.9]) ; return fix(x+x)", np_fix4=[])

    def test_finfo0(self):
        self.run_test("def np_finfo0(): from numpy import finfo, float64 ; x = finfo(float64) ; return x.eps", np_finfo0=[])

    def test_fill0(self):
        self.run_test("def np_fill0(): from numpy import ones ; x = ones((2,3)) ; x.fill(5) ; return x", np_fill0=[])

    def test_eye0(self):
        self.run_test("def np_eye0(): from numpy import eye ; x = 2 ; return eye(x)", np_eye0=[])

    def test_eye1(self):
        self.run_test("def np_eye1(): from numpy import eye ; x = 2 ; return eye(x, x+1)", np_eye1=[])

    def test_eye1b(self):
        self.run_test("def np_eye1b(): from numpy import eye ; x = 3 ; return eye(x, x-1)", np_eye1b=[])

    def test_eye2(self):
        self.run_test("def np_eye2(): from numpy import eye ; x = 2 ; return eye(x, x, 1)", np_eye2=[])

    def test_eye3(self):
        self.run_test("def np_eye3(): from numpy import eye, int32 ; x = 2 ; return eye(x, x, 1, int32)", np_eye3=[])

    def test_ediff1d0(self):
        self.run_test("def np_ediff1d0(): from numpy import array, ediff1d ; x = [1,2,4,7,0] ; return ediff1d(x)", np_ediff1d0=[])

    def test_ediff1d1(self):
        self.run_test("def np_ediff1d1(): from numpy import array, ediff1d ; x = [[1,2,4],[1,6,24]] ; return ediff1d(x)", np_ediff1d1=[])

    def test_dot0(self):
        self.run_test("def np_dot0(): from numpy import array, dot ; x, y = 2, 3 ; return dot(x,y)", np_dot0=[])

    def test_dot1(self):
        self.run_test("def np_dot1(): from numpy import array, dot ; x, y = [2, 3], [2, 3] ; return dot(x,y)", np_dot1=[])

    def test_dot2(self):
        self.run_test("def np_dot2(): from numpy import array, dot ; x, y = [2j, 3j], [2j, 3j] ; return dot(x,y)", np_dot2=[])

    def test_dot3(self):
        self.run_test("def np_dot3(): from numpy import array, dot ; x, y = array([2, 3]), array([2, 3]) ; return dot(x+x,y)", np_dot3=[])

    def test_dot4(self):
        self.run_test("def np_dot4(): from numpy import array, dot ; x, y = array([2, 3]), [2, 3] ; return dot(x,y)", np_dot4=[])

    def test_digitize0(self):
        self.run_test("def np_digitize0(): from numpy import array, digitize; x = array([0.2, 6.4, 3.0, 1.6]) ; bins = array([0.0, 1.0, 2.5, 4.0, 10.0]) ; return digitize(x, bins)", np_digitize0=[])

    def test_digitize1(self):
        self.run_test("def np_digitize1(): from numpy import array, digitize; x = array([0.2, 6.4, 3.0, 1.6]) ; bins = array([ 10.0, 4.0, 2.5, 1.0, 0.0]) ; return digitize(x, bins)", np_digitize1=[])

    def test_diff0(self):
        self.run_test("def np_diff0(): from numpy import array, diff ; x = array([1, 2, 4, 7, 0]) ; return diff(x)", np_diff0=[])

    def test_diff1(self):
        self.run_test("def np_diff1(): from numpy import array, diff ; x = array([1, 2, 4, 7, 0]) ; return diff(x,2)", np_diff1=[])

    def test_diff2(self):
        self.run_test("def np_diff2(): from numpy import array, diff ; x = array([[1, 3, 6, 10], [0, 5, 6, 8]]) ; return diff(x)", np_diff2=[])

    def test_diff3(self):
        self.run_test("def np_diff3(): from numpy import array, diff ; x = array([[1, 3, 6, 10], [0, 5, 6, 8]]) ; return diff(x,2)", np_diff3=[])

    def test_diff4(self):
        self.run_test("def np_diff4(): from numpy import array, diff ; x = array([1, 2, 4, 7, 0]) ; return diff(x + x)", np_diff4=[])

    def test_trace0(self):
        self.run_test("def np_trace0(): from numpy import arange, trace; x = arange(9).reshape(3,3); return trace(x)", np_trace0=[])

    def test_trace1(self):
        self.run_test("def np_trace1(): from numpy import arange, trace; x = arange(12).reshape(3,4); return trace(x, 1)", np_trace1=[])

    def test_trace2(self):
        self.run_test("def np_trace2(): from numpy import arange, trace; x = arange(12).reshape(3,4); return trace(x, 1)", np_trace2=[])

    def test_tri0(self):
        self.run_test("def np_tri0(): from numpy import tri; return tri(3)", np_tri0=[])

    def test_tri1(self):
        self.run_test("def np_tri1(): from numpy import tri; return tri(3, 4)", np_tri1=[])

    def test_tri2(self):
        self.run_test("def np_tri2(): from numpy import tri; return tri(4, 3, -1)", np_tri2=[])

    def test_tri3(self):
        self.run_test("def np_tri3(): from numpy import tri, int64; return tri(3, 5, 1, int64)", np_tri3=[])

    def test_trim_zeros0(self):
        self.run_test("""
def np_trim_zeros0():
    from numpy import array, trim_zeros
    x = array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0))
    return trim_zeros(x)""", np_trim_zeros0=[])

    def test_trim_zeros1(self):
        self.run_test("""
def np_trim_zeros1():
    from numpy import array, trim_zeros
    x = array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0))
    return trim_zeros(x, "f")""", np_trim_zeros1=[])

    def test_trim_zeros2(self):
        self.run_test("""
def np_trim_zeros2():
    from numpy import array, trim_zeros
    x = array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0))
    return trim_zeros(x, "b")""", np_trim_zeros2=[])

    def test_triu0(self):
        self.run_test("def np_triu0(): from numpy import arange, triu; x = arange(12).reshape(3,4); return triu(x)", np_triu0=[])

    def test_triu1(self):
        self.run_test("def np_triu1(): from numpy import arange, triu; x = arange(12).reshape(3,4); return triu(x, 1)", np_triu1=[])

    def test_triu2(self):
        self.run_test("def np_triu2(): from numpy import arange, triu; x = arange(12).reshape(3,4); return triu(x, -1)", np_triu2=[])

    def test_tril0(self):
        self.run_test("def np_tril0(): from numpy import arange, tril; x = arange(12).reshape(3,4); return tril(x)", np_tril0=[])

    def test_tril1(self):
        self.run_test("def np_tril1(): from numpy import arange, tril; x = arange(12).reshape(3,4); return tril(x, 1)", np_tril1=[])

    def test_tril2(self):
        self.run_test("def np_tril2(): from numpy import arange, tril; x = arange(12).reshape(3,4); return tril(x, -1)", np_tril2=[])

    def test_union1d(self):
        self.run_test("def np_union1d(): from numpy import arange, union1d ; x = arange(-1,2) ; y = arange(1,4); return union1d(x, y)", np_union1d=[])

    def test_unique0(self):
        self.run_test("def np_unique0(): from numpy import array, unique ; x = array([1,1,2,2,2,1,5]) ; return unique(x)", np_unique0=[])

    def test_unique1(self):
        self.run_test("def np_unique1(): from numpy import array, unique ; x = array([[1,2,2],[2,1,5]]) ; return unique(x)", np_unique1=[])

    def test_unique2(self):
        self.run_test("def np_unique2(): from numpy import array, unique ; x = array([1,1,2,2,2,1,5]) ; return unique(x, True)", np_unique2=[])

    def test_unique3(self):
        self.run_test("def np_unique3(): from numpy import array, unique ; x = array([1,1,2,2,2,1,5]) ; return unique(x, True, True)", np_unique3=[])

    def test_unwrap0(self):
        self.run_test("def np_unwrap0(): from numpy import arange, unwrap, pi ; x = arange(6) ; x[:3] += 2*pi; return unwrap(x)", np_unwrap0=[])

    def test_unwrap1(self):
        self.run_test("def np_unwrap1(): from numpy import arange, unwrap, pi ; x = arange(6) ; x[:3] += 2*pi; return unwrap(x, 4)", np_unwrap1=[])

    def test_unwrap2(self):
        self.run_test("def np_unwrap2(): from numpy import arange, unwrap, pi ; x = arange(6) ; x[:3] -= 2*pi; return unwrap(x, 4)", np_unwrap2=[])

    def test_nonzero0(self):
        self.run_test("def np_nonzero0(): from numpy import arange, nonzero ; x = arange(6) ; return nonzero(x)", np_nonzero0=[])

    def test_nonzero1(self):
        self.run_test("def np_nonzero1(): from numpy import arange, nonzero ; x = arange(6) ; return nonzero(x>8)", np_nonzero1=[])

    def test_nonzero2(self):
        self.run_test("def np_nonzero2(): from numpy import arange, nonzero ; x = arange(6).reshape(2,3) ; return nonzero(x>0)", np_nonzero2=[])

    def test_diagflat3(self):
        self.run_test("def np_diagflat3(): from numpy import diagflat, arange; a = arange(2) ; return diagflat(a)", np_diagflat3=[])

    def test_diagflat4(self):
        self.run_test("def np_diagflat4(): from numpy import diagflat, arange; a = arange(3) ; return diagflat(a,1)", np_diagflat4=[])

    def test_diagflat5(self):
        self.run_test("def np_diagflat5(): from numpy import diagflat, arange; a = arange(4) ; return diagflat(a,-2)", np_diagflat5=[])

    def test_diagonal0(self):
        self.run_test("def np_diagonal0(): from numpy import diagonal, arange; a = arange(10).reshape(2,5) ; return diagonal(a)", np_diagonal0=[])

    def test_diagonal1(self):
        self.run_test("def np_diagonal1(): from numpy import diagonal, arange; a = arange(9).reshape(3,3) ; return diagonal(a,1)", np_diagonal1=[])

    def test_diagonal2(self):
        self.run_test("def np_diagonal2(): from numpy import diagonal, arange; a = arange(9).reshape(3,3) ; return diagonal(a,-2)", np_diagonal2=[])

    def test_diag0(self):
        self.run_test("def np_diag0(): from numpy import diag, arange; a = arange(10).reshape(2,5) ; return diag(a)", np_diag0=[])

    def test_diag1(self):
        self.run_test("def np_diag1(): from numpy import diag, arange; a = arange(9).reshape(3,3) ; return diag(a,1)", np_diag1=[])

    def test_diag2(self):
        self.run_test("def np_diag2(): from numpy import diag, arange; a = arange(9).reshape(3,3) ; return diag(a,-2)", np_diag2=[])

    def test_diag2b(self):
        self.run_test("def np_diag2b(): from numpy import diag, arange; a = arange(12).reshape(4,3) ; return diag(a,-2)", np_diag2b=[])

    def test_diag3(self):
        self.run_test("def np_diag3(): from numpy import diag, arange; a = arange(2) ; return diag(a)", np_diag3=[])

    def test_diag4(self):
        self.run_test("def np_diag4(): from numpy import diag, arange; a = arange(3) ; return diag(a,1)", np_diag4=[])

    def test_diag5(self):
        self.run_test("def np_diag5(): from numpy import diag, arange; a = arange(4) ; return diag(a,-2)", np_diag5=[])

    def test_delete0(self):
        self.run_test("def np_delete0(): from numpy import array, delete ; a = array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]) ; return delete(a, 1)", np_delete0=[])

    def test_delete1(self):
        self.run_test("def np_delete1(): from numpy import array, delete ; a = array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]) ; return delete(a, [1,3,5])", np_delete1=[])

    def test_where0(self):
        self.run_test("""def np_where0():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    b = arange(5, 17).reshape(3,4)
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(c , a, b)""", np_where0=[])

    def test_where1(self):
        self.run_test("""def np_where1():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, c)""", np_where1=[])

    def test_where2(self):
        self.run_test("""def np_where2():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, c)""", np_where2=[])

    def test_where3(self):
        self.run_test("""def np_where3():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, 5)""", np_where3=[])

    def test_where4(self):
        self.run_test("""def np_where4():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, 6)""", np_where4=[])

    def test_where5(self):
        self.run_test("""def np_where5():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    b = arange(5, 17).reshape(3,4)
    return where(a>5 , a, b)""", np_where5=[])

    def test_where6(self):
        self.run_test("""def np_where6():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    return where(a>5 , 1, 2)""", np_where6=[])

    def test_where7(self):
        self.run_test("""def np_where7():
    from numpy import arange, where
    a = arange(12).reshape(3,4)
    return where(a>5)""", np_where7=[])

    def test_cumprod_(self):
        self.run_test("def np_cumprod_():\n from numpy import arange,cumprod\n return arange(10).cumprod()", np_cumprod_=[])

    def test_cumprod2_(self):
        self.run_test("def np_cumprod2_():\n from numpy import arange,cumprod\n return arange(10).reshape(2,5).cumprod()", np_cumprod2_=[])

    def test_cumprod3_(self):
        self.run_test("def np_cumprod3_():\n from numpy import arange,cumprod\n return arange(10).reshape(2,5).cumprod(1)", np_cumprod3_=[])

    def test_cumprod4_(self):
        self.run_test("def np_cumprod4_():\n from numpy import arange,cumprod\n return arange(10).reshape(2,5).cumprod(0)", np_cumprod4_=[])

    def test_cumprod5_(self):
        self.run_test("def np_cumprod5_():\n from numpy import arange,cumprod\n return arange(10).cumprod(0)", np_cumprod5_=[])

    def test_copy0(self):
        code= '''
def test_copy0():
    import numpy as np
    x = np.array([1, 2, 3])
    y = x
    z = np.copy(x)
    x[0] = 10
    return x[0], y[0], z[0]'''
        self.run_test(code, test_copy0=[])

    def test_clip0(self):
        self.run_test("def np_clip0(): from numpy import arange, array, clip ; a = arange(10) ; return clip(a,1,8)", np_clip0=[])

    def test_clip1(self):
        self.run_test("def np_clip1(): from numpy import arange, array, clip ; a = arange(10) ; return clip(a,3,6)", np_clip1=[])

    def test_concatenate0(self):
        self.run_test("def np_concatenate0(): from numpy import array, concatenate ; a = array([[1, 2], [3, 4]]) ; b = array([[5, 6]]) ; return concatenate((a,b))", np_concatenate0=[])

    def test_bincount0(self):
        self.run_test("def np_bincount0(): from numpy import arange, bincount ; a = arange(5) ; return bincount(a)", np_bincount0=[])

    def test_bincount1(self):
        self.run_test("def np_bincount1(): from numpy import bincount,array ; a = array([0, 1, 1, 2, 2, 2]) ; w = array([0.3, 0.5, 0.2, 0.7, 1., -0.6]) ; return bincount(a,w)", np_bincount1=[])

    def test_binary_repr0(self):
        self.run_test("def np_binary_repr0(): from numpy import binary_repr ; a = 3 ; return binary_repr(a)", np_binary_repr0=[])

    def test_binary_repr1(self):
        self.run_test("def np_binary_repr1(): from numpy import binary_repr ; a = -3 ; return binary_repr(a)", np_binary_repr1=[])

    def test_binary_repr2(self):
        self.run_test("def np_binary_repr2(): from numpy import binary_repr ; a = 3 ; return binary_repr(a,4)", np_binary_repr2=[])

    def test_binary_repr3(self):
        self.run_test("def np_binary_repr3(): from numpy import binary_repr ; a = -3 ; return binary_repr(a,4)", np_binary_repr3=[])

    def test_base_repr0(self):
        self.run_test("def np_base_repr0(): from numpy import base_repr ; a = 5 ; return base_repr(a)", np_base_repr0=[])

    def test_base_repr1(self):
        self.run_test("def np_base_repr1(): from numpy import base_repr ; a = 6 ; return base_repr(a,5)", np_base_repr1=[])

    def test_base_repr2(self):
        self.run_test("def np_base_repr2(): from numpy import base_repr ; a = 7 ; return base_repr(a,5,3)", np_base_repr2=[])

    def test_base_repr3(self):
        self.run_test("def np_base_repr3(): from numpy import base_repr ; a = 10 ; return base_repr(a, 16)", np_base_repr3=[])

    def test_base_repr4(self):
        self.run_test("def np_base_repr4(): from numpy import base_repr ; a = 32 ; return base_repr(a, 16)", np_base_repr4=[])

    def test_average0(self):
        self.run_test("def np_average0(): from numpy import average, arange ; a = arange(10) ; return average(a)", np_average0=[])

    def test_average1(self):
        self.run_test("def np_average1(): from numpy import average, arange ; a = arange(10).reshape(2,5) ; return average(a,1)", np_average1=[])

    def test_average2(self):
        self.run_test("def np_average2(): from numpy import average, arange ; a = arange(10) ; return average(a,None, range(10))", np_average2=[])

    def test_average3(self):
        self.run_test("def np_average3(): from numpy import average, arange ; a = arange(10).reshape(2,5) ; return average(a,None, arange(10).reshape(2,5))", np_average3=[])

    def test_atleast_1d0(self):
        self.run_test("def np_atleast_1d0(): from numpy import arange, atleast_1d ; a = 1 ; return atleast_1d(a)", np_atleast_1d0=[])

    def test_atleast_1d1(self):
        self.run_test("def np_atleast_1d1(): from numpy import arange, atleast_1d ; a = arange(2) ; r = atleast_1d(a) ; return r is a", np_atleast_1d1=[])

    def test_atleast_2d0(self):
        self.run_test("def np_atleast_2d0(): from numpy import arange, atleast_2d ; a = 1 ; return atleast_2d(a)", np_atleast_2d0=[])

    def test_atleast_2d1(self):
        self.run_test("def np_atleast_2d1(): from numpy import arange, atleast_2d ; a = arange(2).reshape(1,2) ; r = atleast_2d(a) ; return r is a", np_atleast_2d1=[])

    def test_atleast_2d2(self):
        self.run_test("def np_atleast_2d2(): from numpy import arange, atleast_2d ; a = arange(2) ; r = atleast_2d(a) ; return r", np_atleast_2d2=[])

    def test_atleast_3d0(self):
        self.run_test("def np_atleast_3d0(): from numpy import arange, atleast_3d ; a = 1 ; return atleast_3d(a)", np_atleast_3d0=[])

    def test_atleast_3d1(self):
        self.run_test("def np_atleast_3d1(): from numpy import arange, atleast_3d ; a = arange(8).reshape(2,2,2) ; r = atleast_3d(a) ; return r is a", np_atleast_3d1=[])

    def test_atleast_3d2(self):
        self.run_test("def np_atleast_3d2(): from numpy import arange, atleast_3d ; a = arange(8).reshape(2,4) ; r = atleast_3d(a) ; return r", np_atleast_3d2=[])

    def test_atleast_3d3(self):
        self.run_test("def np_atleast_3d3(): from numpy import arange, atleast_3d ; a = arange(8) ; r = atleast_3d(a) ; return r", np_atleast_3d3=[])

    def test_asscalar0(self):
        self.run_test("def np_asscalar0(): from numpy import array, asscalar, int32; a = array([1], int32) ; return asscalar(a)", np_asscalar0=[])

    def test_asscalar1(self):
        self.run_test("def np_asscalar1(): from numpy import array, asscalar, int64; a = array([[1]], int64) ; return asscalar(a)", np_asscalar1=[])

    def test_ascontiguousarray0(self):
        self.run_test("def np_ascontiguousarray0():\n from numpy import ascontiguousarray\n return ascontiguousarray((1,2,3))", np_ascontiguousarray0=[])

    def test_asarray_chkfinite0(self):
        self.run_test("def np_asarray_chkfinite0():\n from numpy import asarray_chkfinite\n return asarray_chkfinite((1,2,3))", np_asarray_chkfinite0=[])
       
    def test_asarray_chkfinite1(self):
        self.run_test("def np_asarray_chkfinite1():\n from numpy import asarray_chkfinite, nan\n try: return asarray_chkfinite([[1,2],[nan,4]])\n except ValueError: return asarray_chkfinite([[1.,2.],[3.,4.]])", np_asarray_chkfinite1=[])

    def test_asarray0(self):
        self.run_test("def np_asarray0():\n from numpy import asarray\n return asarray((1,2,3))", np_asarray0=[])
       
    def test_asarray1(self):
        self.run_test("def np_asarray1():\n from numpy import asarray\n return asarray([(1,2),(3,4)])", np_asarray1=[])

    def test_asarray2(self):
        self.run_test("def np_asarray2():\n from numpy import asarray, int8\n return asarray([1.,2.,3.], int8)", np_asarray2=[])

    def test_asarray3(self):
        self.run_test("def np_asarray3():\n from numpy import arange, asarray; a = arange(3) ; b = asarray(a) ; return a is b", np_asarray3=[])

    def test_array_str0(self):
        self.run_test("def np_array_str0(): from numpy import arange, array_str ; x = arange(3) ; return array_str(x)", np_array_str0=[])

    def test_array_split0(self):
        self.run_test("def np_array_split0(): from numpy import arange, array_split,array2string ; a = arange(12) ; return map(array2string,array_split(a, 3))", np_array_split0=[])

    def test_array_split1(self):
        self.run_test("def np_array_split1(): from numpy import arange, array_split, array2string ; a = arange(12); return map(array2string,array_split(a, 5))", np_array_split1=[])

    def test_array_split2(self):
        self.run_test("def np_array_split2(): from numpy import arange, array_split, array2string ; a = arange(12).reshape(6,2); return map(array2string,array_split(a, 4))", np_array_split2=[])

    def test_array_split3(self):
        self.run_test("def np_array_split3(): from numpy import arange, array_split, array2string ; a = arange(12).reshape(6,2); return map(array2string,array_split(a, [0,1,5]))", np_array_split3=[])

    def test_array_equiv0(self):
        self.run_test("def np_array_equiv0(): from numpy import array_equiv ;  a,b = [1,2], [1,2] ; return array_equiv(a,b)", np_array_equiv0=[])

    def test_array_equiv1(self):
        self.run_test("def np_array_equiv1(): from numpy import array_equiv ;  a,b = [1,2], [1,3] ; return array_equiv(a,b)", np_array_equiv1=[])

    def test_array_equiv2(self):
        self.run_test("def np_array_equiv2(): from numpy import array_equiv ;  a,b = [1,2], [[1,2],[1,2]] ; return array_equiv(a,b)", np_array_equiv2=[])

    def test_array_equiv3(self):
        self.run_test("def np_array_equiv3(): from numpy import array_equiv ;  a,b = [1,2], [[1,2],[1,3]] ; return array_equiv(a,b)", np_array_equiv3=[])

    def test_array_equal0(self):
        self.run_test("def np_array_equal0(): from numpy import array_equal ;  a,b = [1,2], [1,2] ; return array_equal(a,b)", np_array_equal0=[])

    def test_array_equal1(self):
        self.run_test("def np_array_equal1(): from numpy import array, array_equal ;  a,b = array([1,2]), array([1,2]) ; return array_equal(a,b)", np_array_equal1=[])

    def test_array_equal2(self):
        self.run_test("def np_array_equal2(): from numpy import array, array_equal ;  a,b = array([[1,2],[3,5]]), array([[1,2],[3,5]]) ; return array_equal(a,b)", np_array_equal2=[])

    def test_array_equal3(self):
        self.run_test("def np_array_equal3(): from numpy import array, array_equal ;  a,b = array([[1,2],[3,5]]), array([[1,2],[4,5]]) ; return array_equal(a,b)", np_array_equal3=[])

    def test_array_equal4(self):
        self.run_test("def np_array_equal4(): from numpy import array, array_equal ;  a,b = array([1,2]), array([1,2,3]) ; return array_equal(a,b)", np_array_equal4=[])


    def test_array2string0(self):
        self.run_test("def np_array2string0(): from numpy import arange, array2string ; x = arange(3) ; return array2string(x)", np_array2string0=[])

    def test_argwhere0(self):
        self.run_test("def np_argwhere0(): from numpy import arange, argwhere ; x = arange(6) ; return argwhere(x)", np_argwhere0=[])

    def test_argwhere1(self):
        self.run_test("def np_argwhere1(): from numpy import arange, argwhere ; x = arange(6) ; return argwhere(x>8)", np_argwhere1=[])

    def test_argwhere2(self):
        self.run_test("def np_argwhere2(): from numpy import arange, argwhere ; x = arange(6).reshape(2,3) ; return argwhere(x>0)", np_argwhere2=[])

    def test_around0(self):
        self.run_test("def np_around0(): from numpy import array, around ; x = [0.37, 1.64] ; return around(x)", np_around0=[])

    def test_around1(self):
        self.run_test("def np_around1(): from numpy import array, around ; x = [0.37, 1.64] ; return around(x, 1)", np_around1=[])

    def test_around2(self):
        self.run_test("def np_around2(): from numpy import array, around ; x = [0.37, 1.64] ; return around(x, -1)", np_around2=[])

    def test_around3(self):
        self.run_test("def np_around3(): from numpy import array, around ; x = [.5, 1.5, 2.5, 3.5, 4.5] ; return around(x)", np_around3=[])

    def test_around4(self):
        self.run_test("def np_around4(): from numpy import array, around ; x = [1,2,3,11] ; return around(x,1)", np_around4=[])

    def test_around5(self):
        self.run_test("def np_around5(): from numpy import array, around ; x = [1,2,3,11] ; return around(x,-1)", np_around5=[])

    def test_argsort0(self):
        self.run_test("def np_argsort0(): from numpy import argsort, array ; x = array([3, 1, 2]) ; return argsort(x)", np_argsort0=[])

    def test_argsort1(self):
        self.run_test("def np_argsort1(): from numpy import argsort, array ; x = array([[3, 1, 2], [1 , 2, 3]]) ; return argsort(x)", np_argsort1=[])

    def test_argmax0(self):
        self.run_test("def np_argmax0(): from numpy import argmax, arange ; a = arange(6).reshape(2,3) ; return argmax(a)", np_argmax0=[])

    def test_argmax1(self):
        self.run_test("def np_argmax1(): from numpy import argmax, arange ; a = arange(6).reshape(2,3) ; return argmax(a+a)", np_argmax1=[])

    def test_argmin0(self):
        self.run_test("def np_argmin0(): from numpy import argmin, arange ; a = arange(6).reshape(2,3) ; return argmin(a)", np_argmin0=[])

    def test_argmin1(self):
        self.run_test("def np_argmin1(): from numpy import argmin, arange ; a =[1,2,3] ; return argmin(a)", np_argmin1=[])

    def test_append0(self):
        self.run_test("def np_append0(): from numpy import append ; a,b = [1, 2, 3], [[4, 5, 6], [7, 8, 9]] ; return append(a,b)", np_append0=[])

    def test_append1(self):
        self.run_test("def np_append1(): from numpy import append,array ; a,b = [1, 2, 3], array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", np_append1=[])

    def test_append2(self):
        self.run_test("def np_append2(): from numpy import append,array ; a,b = array([1, 2, 3]), array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", np_append2=[])

    def test_angle0(self):
        self.run_test("def np_angle0(): from numpy import angle, array ; a = [1.0, 1.0j, 1+1j] ; return angle(a)", np_angle0=[])

    def test_angle1(self):
        self.run_test("def np_angle1(): from numpy import angle, array ; a = array([1.0, 1.0j, 1+1j]) ; return angle(a)", np_angle1=[])

    def test_angle2(self):
        self.run_test("def np_angle2(): from numpy import angle, array ; a = 1 + 1j ; return angle(a,True)", np_angle2=[])

    def test_angle3(self):
        self.run_test("def np_angle3(): from numpy import angle, array ; a = 1  ; return angle(a,True)", np_angle3=[])

    def test_any0(self):
        self.run_test("def np_any0(): from numpy import any, array ; a = array([[True, False], [True, True]]) ; return any(a)", np_any0=[])

    def test_any1(self):
        self.run_test("def np_any1(): from numpy import any, array ; a = array([[True, False], [False, False]]) ; return any(a, 0)", np_any1=[])

    def test_any2(self):
        self.run_test("def np_any2(): from numpy import any ; a = [-1, 0, 5] ; return any(a)", np_any2=[])

    def test_array1D_(self):
        self.run_test("def np_array1D_():\n from numpy import array\n return array([1,2,3])", np_array1D_=[])

    def test_array2D_(self):
        self.run_test("def np_array2D_():\n from numpy import array\n return array([[1,2],[3,4]])", np_array2D_=[])

    def test_array_typed(self):
        self.run_test("def np_array_typed():\n from numpy import array, int64\n return array([1.,2.,3.], int64)", np_array_typed=[])

    def test_zeros_(self):
        self.run_test("def np_zeros_():\n from numpy import zeros\n return zeros((10,5))", np_zeros_=[])

    def test_ones_(self):
        self.run_test("def np_ones_():\n from numpy import ones\n return ones((10,5))", np_ones_=[])

    def test_flat_zeros_(self):
        self.run_test("def np_flat_zeros_():\n from numpy import zeros\n return zeros(10)", np_flat_zeros_=[])

    def test_flat_ones_(self):
        self.run_test("def np_flat_ones_():\n from numpy import ones\n return ones(5)", np_flat_ones_=[])

    def test_acces1D_(self):
        self.run_test("def np_acces1D_():\n from numpy import array\n a =array([1,2,3])\n return a[1]", np_acces1D_=[])

    def test_accesSimple_(self):
        self.run_test("def np_accesSimple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1]", np_accesSimple_=[])

    def test_accesMultiple_(self):
        self.run_test("def np_accesMultiple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1,0]", np_accesMultiple_=[])

    def test_accesMultipleND_(self):
        self.run_test("def np_accesMultipleND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1,0]", np_accesMultipleND_=[])

    def test_accesMultipleNDSplit_(self):
        self.run_test("def np_accesMultipleNDSplit_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1][0]", np_accesMultipleNDSplit_=[])

    def test_shape_(self):
        self.run_test("def np_shape_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.shape", np_shape_=[])

    def test_input_array_(self):
        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", runas="import numpy; input_array_(numpy.array([[1,2],[3,4]]))", input_array_=[numpy.array([[int]])])

    def test_change_array1D_(self):
        self.run_test("def np_change_array1D_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0,0] = 36\n return a", np_change_array1D_=[])

    def test_change_arrayND_(self):
        self.run_test("def np_change_arrayND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0] = array([99,99])\n return a", np_change_arrayND_=[])

    def test_ndim_(self):
        self.run_test("def np_ndim_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.ndim", np_ndim_=[])

    def test_stride_(self):
        self.run_test("def np_stride_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.strides", np_stride_=[])

    def test_size_(self):
        self.run_test("def np_size_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.size", np_size_=[])

    def test_itemsize_(self):
        self.run_test("def np_itemsize_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.itemsize", np_itemsize_=[])

    def test_nbytes_(self):
        self.run_test("def np_nbytes_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.nbytes", np_nbytes_=[])

    def test_flat_(self):
        self.run_test("def np_flat_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return [i for i in a.flat]", np_flat_=[])

    def test_str_(self):
        self.run_test("def np_str_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return str(a)", np_str_=[])

    def test_len_(self):
        self.run_test("def np_len_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return len(a)", np_len_=[])

    def test_empty_(self):
        self.run_test("def np_empty_():\n from numpy import empty\n a = empty((3,2))\n return a.strides, len(a)", np_empty_=[])

    def test_arange(self):
        self.run_test("def np_arange_():\n from numpy import arange\n return arange(10)", np_arange_=[])

    def test_arange1(self):
        self.run_test("def np_arange1_():\n from numpy import arange\n return arange(1, 10)", np_arange1_=[])

    def test_arange2(self):
        self.run_test("def np_arange2_():\n from numpy import arange\n return arange(0.5, 10)", np_arange2_=[])

    def test_arange3(self):
        self.run_test("def np_arange3_():\n from numpy import arange\n return arange(0.5, 9.5)", np_arange3_=[])

    def test_arange4(self):
        self.run_test("def np_arange4_():\n from numpy import arange\n return arange(0.2, 9.3, 1)", np_arange4_=[])

    def test_arange5(self):
        self.run_test("def np_arange5_():\n from numpy import arange\n return arange(1, 2, 0.3)", np_arange5_=[])

    def test_arange6(self):
        self.run_test("def np_arange6_():\n from numpy import arange\n return arange(0.2, 3.3, 0.5)", np_arange6_=[])

    def test_arange7(self):
        self.run_test("def np_arange7_():\n from numpy import arange\n return arange(1, 4.5, -0.2)", np_arange7_=[])

    def test_arange8(self):
        self.run_test("def np_arange8_():\n from numpy import arange\n return arange(4.5, 1, -0.1)", np_arange8_=[])

    def test_arange9(self):
        self.run_test("def np_arange9_():\n from numpy import arange\n return arange(4.5, -12, -3.2)", np_arange9_=[])

    def test_arange10(self):
        self.run_test("def np_arange10_():\n from numpy import arange\n return arange(-5, -5.5, -0.1)", np_arange10_=[])

    def test_arange11(self):
        self.run_test("def np_arange11_():\n from numpy import arange, uint8\n return arange(0, 255, 1, uint8)", np_arange11_=[])

    def test_arange12(self):
        self.run_test("def np_arange12_():\n from numpy import arange, float32\n return arange(0, 25, 1., float32)", np_arange12_=[])

    def test_linspace(self):
        self.run_test("def np_linspace_():\n from numpy import linspace\n return linspace(1,4,32)", np_linspace_=[])

    def test_linspace1(self):
        self.run_test("def np_linspace1_():\n from numpy import linspace\n return linspace(0.4,32.5,2)", np_linspace1_=[])

    def test_linspace2(self):
        self.run_test("def np_linspace2_():\n from numpy import linspace\n return linspace(0.4,32.5,32, False)", np_linspace2_=[])

    def test_linspace3(self):
        self.run_test("def np_linspace3_():\n from numpy import linspace\n return linspace(1,4)", np_linspace3_=[])

    def test_sin(self):
        self.run_test("def np_sin_():\n from numpy import sin, linspace\n return sin(linspace(0,6))", np_sin_=[])

    def test_pi(self):
        self.run_test("def np_pi_():\n from numpy import pi\n return pi", np_pi_=[])

    def test_e(self):
        self.run_test("def np_e_():\n from numpy import e\n return e", np_e_=[])

    def test_ones_like_(self):
        self.run_test("def np_ones_like_():\n from numpy import ones_like, array\n return ones_like(array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)]))", np_ones_like_=[])

    def test_zeros_like_(self):
        self.run_test("def np_zeros_like_():\n from numpy import zeros_like, array\n return zeros_like(array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)]))", np_zeros_like_=[])

    def test_empty_like_(self):
        self.run_test("def np_empty_like_():\n from numpy import empty_like, array\n return empty_like(array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])).shape", np_empty_like_=[])

    def test_reshape_(self):
        self.run_test("def np_reshape_():\n from numpy import arange,reshape\n return arange(10).reshape(2,5)", np_reshape_=[])

    def test_reshape_expr(self):
        self.run_test("def np_reshape_expr():\n from numpy import ones,reshape\n return (ones(10) + ones(10)).reshape(2,5)", np_reshape_expr=[])

    def test_cumsum_(self):
        self.run_test("def np_cumsum_():\n from numpy import arange,cumsum\n return arange(10).cumsum()", np_cumsum_=[])

    def test_cumsum2_(self):
        self.run_test("def np_cumsum2_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum()", np_cumsum2_=[])

    def test_cumsum3_(self):
        self.run_test("def np_cumsum3_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum(1)", np_cumsum3_=[])

    def test_cumsum4_(self):
        self.run_test("def np_cumsum4_():\n from numpy import arange,cumsum\n return arange(10).reshape(2,5).cumsum(0)", np_cumsum4_=[])

    def test_cumsum5_(self):
        self.run_test("def np_cumsum5_():\n from numpy import arange,cumsum\n return arange(10).cumsum(0)", np_cumsum5_=[])

    def test_sum_(self):
        self.run_test("def np_sum_():\n from numpy import arange,sum\n return arange(10).sum()", np_sum_=[])

    def test_sum_expr(self):
        self.run_test("def np_sum_expr():\n from numpy import arange, ones, sum\n return (arange(10)+ones(10)).sum()", np_sum_expr=[])

    def test_sum2_(self):
        self.run_test("def np_sum2_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum()", np_sum2_=[])

    def test_sum3_(self):
        self.run_test("def np_sum3_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum(1)", np_sum3_=[])

    def test_sum4_(self):
        self.run_test("def np_sum4_():\n from numpy import arange,sum\n return arange(10).reshape(2,5).sum(0)", np_sum4_=[])

    def test_sum5_(self):
        self.run_test("def np_sum5_():\n from numpy import arange,sum\n return arange(10).sum(0)", np_sum5_=[])

    def test_amin_amax(self):
        self.run_test("def np_amin_amax():\n from numpy import arange,amin,amax\n return amin(arange(10)), amax(arange(10))", np_amin_amax=[])

    def test_min_(self):
        self.run_test("def np_min_():\n from numpy import arange,min\n return arange(10).min()", np_min_=[])

    def test_min2_(self):
        self.run_test("def np_min2_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min()", np_min2_=[])

    def test_min3_(self):
        self.run_test("def np_min3_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min(1)", np_min3_=[])

    def test_min4_(self):
        self.run_test("def np_min4_():\n from numpy import arange,min\n return arange(10).reshape(2,5).min(0)", np_min4_=[])

    def test_min5_(self):
        self.run_test("def np_min5_():\n from numpy import arange,min\n return arange(10).min(0)", np_min5_=[])

    def test_max_(self):
        self.run_test("def np_max_():\n from numpy import arange,max\n return arange(10).max()", np_max_=[])

    def test_max2_(self):
        self.run_test("def np_max2_():\n from numpy import arange,max\n return arange(10).reshape(2,5).max()", np_max2_=[])

    def test_max3_(self):
        self.run_test("def np_max3_():\n from numpy import arange,max\n return arange(10).reshape(2,5).max(1)", np_max3_=[])

    def test_max4_(self):
        self.run_test("def np_max4_():\n from numpy import arange,max\n return arange(10).reshape(2,5).max(0)", np_max4_=[])

    def test_max5_(self):
        self.run_test("def np_max5_():\n from numpy import arange,max\n return arange(10).max(0)", np_max5_=[])

    def test_all_(self):
        self.run_test("def np_all_():\n from numpy import arange,all\n return arange(10).all()", np_all_=[])

    def test_all2_(self):
        self.run_test("def np_all2_():\n from numpy import ones,all\n return ones(10).reshape(2,5).all()", np_all2_=[])

    def test_all3_(self):
        self.run_test("def np_all3_():\n from numpy import arange,all\n return arange(10).reshape(2,5).all(1)", np_all3_=[])

    def test_all4_(self):
        self.run_test("def np_all4_():\n from numpy import ones,all\n return ones(10).reshape(2,5).all(0)", np_all4_=[])

    def test_all5_(self):
        self.run_test("def np_all5_():\n from numpy import arange,all\n return arange(10).all(0)", np_all5_=[])

    def test_transpose_(self):
        self.run_test("def np_transpose_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose()", np_transpose_=[])

    def test_transpose_expr(self):
        self.run_test("def np_transpose_expr():\n from numpy import arange,ones,transpose\n return (ones(24).reshape(2,3,4) + ones(24).reshape(2,3,4)).transpose()", np_transpose_expr=[])

    def test_transpose2_(self):
        self.run_test("def np_transpose2_():\n from numpy import arange,transpose\n return arange(24).reshape(2,3,4).transpose((2,0,1))", np_transpose2_=[])

    def test_add0(self):
        self.run_test("def np_add0(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b", np_add0=[])

    def test_add1(self):
        self.run_test("def np_add1(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b + a", np_add1=[])

    def test_add2(self):
        self.run_test("def np_add2(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b + 1", np_add2=[])

    def test_add3(self):
        self.run_test("def np_add3(): from numpy import ones ; a, b = ones(10), ones(10) ; return 1. + a + b + 1.", np_add3=[])

    def test_add4(self):
        self.run_test("def np_add4(): from numpy import ones ; a, b = ones(10), ones(10) ; return ( a + b ) + ( a + b )", np_add4=[])

    def test_add5(self):
        self.run_test("def np_add5(): from numpy import ones ; a, b = ones(10), ones(10) ; return (-a) + (-b)", np_add5=[])

    def test_sub0(self):
        self.run_test("def np_sub0(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b", np_sub0=[])

    def test_sub1(self):
        self.run_test("def np_sub1(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b - a", np_sub1=[])

    def test_sub2(self):
        self.run_test("def np_sub2(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b - 1", np_sub2=[])

    def test_sub3(self):
        self.run_test("def np_sub3(): from numpy import ones ; a, b = ones(10), ones(10) ; return 1. - a - b - 1.", np_sub3=[])

    def test_sub4(self):
        self.run_test("def np_sub4(): from numpy import ones ; a, b = ones(10), ones(10) ; return ( a - b ) - ( a - b )", np_sub4=[])

    def test_addsub0(self):
        self.run_test("def np_addsub0(): from numpy import ones ; a, b = ones(10), ones(10) ; return a - b + a", np_addsub0=[])

    def test_addsub1(self):
        self.run_test("def np_addsub1(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b - a", np_addsub1=[])

    def test_addsub2(self):
        self.run_test("def np_addsub2(): from numpy import ones ; a, b = ones(10), ones(10) ; return a + b - 1", np_addsub2=[])

    def test_addsub3(self):
        self.run_test("def np_addsub3(): from numpy import ones ; a, b = ones(10), ones(10) ; return 1. + a - b + 1.", np_addsub3=[])

    def test_addsub4(self):
        self.run_test("def np_addsub4(): from numpy import ones ; a, b = ones(10), ones(10) ; return ( a - b ) + ( a + b )", np_addsub4=[])

    def test_addcossub0(self):
        self.run_test("def np_addcossub0(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return a - b + cos(a)", np_addcossub0=[])

    def test_addcossub1(self):
        self.run_test("def np_addcossub1(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return a + cos(b - a)", np_addcossub1=[])

    def test_addcossub2(self):
        self.run_test("def np_addcossub2(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return a + cos(b - 1)", np_addcossub2=[])

    def test_addcossub3(self):
        self.run_test("def np_addcossub3(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return cos(1. + a - b + cos(1.))", np_addcossub3=[])

    def test_addcossub4(self):
        self.run_test("def np_addcossub4(): from numpy import ones, cos ; a, b = ones(10), ones(10) ; return cos( a - b ) + ( a + b )", np_addcossub4=[])

    def test_sin0(self):
        self.run_test("def np_sin0(): from numpy import ones, sin ; a, b = ones(10), ones(10) ; return sin(a) + b", np_sin0=[])

    def test_tan0(self):
        self.run_test("def np_tan0(): from numpy import ones, tan ; a, b = ones(10), ones(10) ; return tan(a - b)", np_tan0=[])

    def test_arccos0(self):
        self.run_test("def np_arccos0(): from numpy import ones, arccos ; a, b = ones(10), ones(10) ; return arccos(a - b) + 1", np_arccos0=[])

    def test_arcsin0(self):
        self.run_test("def np_arcsin0(): from numpy import ones, arcsin ; a, b = ones(10), ones(10) ; return arcsin(a + b - a + -b) + 1.", np_arcsin0=[])

    def test_arctan0(self):
        self.run_test("def np_arctan0(): from numpy import ones, arctan ; a, b = ones(10), ones(10) ; return arctan(a -0.5) + a", np_arctan0=[])

    def test_arctan20(self):
        self.run_test("def np_arctan20(): from numpy import ones, arctan2 ; a, b = ones(10), ones(10) ; return b - arctan2(a , b)", np_arctan20=[])

    def test_cos1(self):
        self.run_test("def np_cos1(): from numpy import cos ; a = 5 ; return cos(a)", np_cos1=[])

    def test_sin1(self):
        self.run_test("def np_sin1(): from numpy import sin ; a = 0.5 ; return sin(a)", np_sin1=[])

    def test_tan1(self):
        self.run_test("def np_tan1(): from numpy import tan ; a = 0.5 ; return tan(a)", np_tan1=[])

    def test_arccos1(self):
        self.run_test("def np_arccos1(): from numpy import arccos ; a= 1 ; return arccos(a)", np_arccos1=[])

    def test_arcsin1(self):
        self.run_test("def np_arcsin1(): from numpy import arcsin ; a= 1 ; return arcsin(a)", np_arcsin1=[])

    def test_arctan1(self):
        self.run_test("def np_arctan1(): from numpy import arctan ; a = 0.5 ; return arctan(a)", np_arctan1=[])

    def test_arctan21(self):
        self.run_test("def np_arctan21(): from numpy import arctan2 ; a, b = 1., .5 ; return arctan2(a , b)", np_arctan21=[])

    def test_sliced0(self):
        self.run_test("def np_sliced0(): from numpy import ones ; a = ones(20) ; return a[2:12]", np_sliced0=[])

    def test_sliced1(self):
        self.run_test("def np_sliced1(): from numpy import ones ; a = ones(20) ; return a[2:12:3]", np_sliced1=[])

    def test_sliced2(self):
        self.run_test("def np_sliced2(): from numpy import ones ; a = ones(20) ; return -a[2:12:3]", np_sliced2=[])

    def test_sliced3(self):
        self.run_test("def np_sliced3(): from numpy import ones ; a = ones(20) ; return a[1:11:3] -a[2:12:3]", np_sliced3=[])

    def test_sliced4(self):
        self.run_test("def np_sliced4(): from numpy import ones ; a = ones(20) ; return a[1:11] -a[2:12]", np_sliced4=[])

    def test_sliced5(self):
        self.run_test("def np_sliced5(): from numpy import ones ; a = ones(20) ; return (-a[1:11]) + 3*a[2:12]", np_sliced5=[])

    def test_sliced6(self):
        self.run_test("def np_sliced6(): from numpy import arange ; a = arange(12).reshape(6,2) ; return a[3:4]", np_sliced6=[])

    def test_sliced7(self):
        self.run_test("def np_sliced7(): from numpy import arange ; a = arange(12).reshape(6,2) ; a[3:4] = 1 ; return a", np_sliced7=[])

    def test_sliced8(self):
        self.run_test("def np_sliced8(): from numpy import arange ; a = arange(12).reshape(3,2,2) ; a[1:2] = 1 ; return a", np_sliced8=[])

    def test_sliced9(self):
        self.run_test("def np_sliced9(): from numpy import arange ; a = arange(12).reshape(3,2,2) ; a[1:2] = arange(4).reshape(1,2,2) ; return a", np_sliced9=[])

    def test_alen0(self):
        self.run_test("def np_alen0(): from numpy import ones, alen ; return alen(ones((5,6)))", np_alen0=[])

    def test_alen1(self):
        self.run_test("def np_alen1(): from numpy import ones, alen ; return alen(-ones((5,6)))", np_alen1=[])

    def test_allclose0(self):
        self.run_test("def np_allclose0(): from numpy import allclose ; return allclose([1e10,1e-7], [1.00001e10,1e-8])", np_allclose0=[])

    def test_allclose1(self):
        self.run_test("def np_allclose1(): from numpy import allclose,array ; return allclose([1e10,1e-8], +array([1.00001e10,1e-9]))", np_allclose1=[])

    def test_allclose2(self):
        self.run_test("def np_allclose2(): from numpy import allclose,array ; return allclose(array([1e10,1e-8]), [1.0001e10,1e-9])", np_allclose2=[])

    def test_allclose3(self):
        self.run_test("def np_allclose3(): from numpy import allclose,nan ; return allclose([1.0, nan], [1.0, nan])", np_allclose3=[])

    def test_alltrue0(self):
        self.run_test("def np_alltrue0(): from numpy import array, alltrue ; b = array([True, False, True, True]) ; return alltrue(b)", np_alltrue0=[])

    def test_alltrue1(self):
        self.run_test("def np_alltrue1(): from numpy import array, alltrue ; a = array([1, 5, 2, 7]) ; return alltrue(a >= 5)", np_alltrue1=[])


# automatic generation of basic test cases for ufunc
binary_ufunc = (
        'add','arctan2',
        'bitwise_and', 'bitwise_or', 'bitwise_xor',
        'copysign',
        'divide',
        'equal',
        'floor_divide', 'fmax', 'fmin', 'fmod',
        'greater', 'greater_equal',
        'hypot',
        'ldexp', 'left_shift', 'less', 'less_equal', 'logaddexp', 'logaddexp2', "logical_and", "logical_or", "logical_xor",
        'maximum', 'minimum', 'mod','multiply',
        'nextafter','not_equal',
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
        'isinf', 'isneginf', 'isposinf', 'isnan', 'invert', 'isfinite',
        'log', 'log10', 'log1p', 'log2', 'logical_not',
        'negative',
        'rad2deg', 'radians','reciprocal', 'rint', 'round', 'round_',
        'sign', 'signbit',
         'sin', 'sinh', 'spacing', 'sqrt', 'square',
        'tan', 'tanh','trunc',
        )

for f in unary_ufunc:
    if 'bitwise_' in f or 'invert' in f:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 1 ; return {0}(a)', np_{0}_scalar=[])".format(f)))
    else:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 0.5 ; return {0}(a+0.5)', np_{0}_scalar=[])".format(f)))

for f in binary_ufunc:
    if 'bitwise_' in f or 'ldexp' in f or '_shift' in f :
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, int32, {0} ; a = ones(10, int32) ; return {0}(a,a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 1 ; return {0}(a, a-1)', np_{0}_scalar=[])".format(f)))
    else:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(): from numpy import ones, {0} ; a = ones(10) ; return {0}(a,a)', np_{0}=[])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(): from numpy import {0} ; a = 0.5 ; return {0}(a+0.5, a+0.5)', np_{0}_scalar=[])".format(f)))

import unittest
from test_env import TestEnv
import numpy

class TestNumpy(TestEnv):
    def test_numpy_augassign0(self):
        self.run_test('def numpy_augassign0(a): a+=1; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign0=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign1(self):
        self.run_test('def numpy_augassign1(a): a*=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign1=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign2(self):
        self.run_test('def numpy_augassign2(a): a-=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign2=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign3(self):
        self.run_test('def numpy_augassign3(a): a/=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign3=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign4(self):
        self.run_test('def numpy_augassign4(a): a|=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign4=[numpy.array([numpy.array([int])])])

    def test_numpy_augassign5(self):
        self.run_test('def numpy_augassign5(a): a&=2; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_augassign5=[numpy.array([numpy.array([int])])])


    def test_numpy_faugassign0(self):
        self.run_test('def numpy_faugassign0(a): a[a>5]+=1; return a',
                      numpy.arange(100),
                      numpy_faugassign0=[numpy.array([int])])

    def test_numpy_faugassign1(self):
        self.run_test('def numpy_faugassign1(a): a[a>3]*=2; return a',
                      numpy.arange(100),
                      numpy_faugassign1=[numpy.array([int])])

    def test_numpy_faugassign2(self):
        self.run_test('def numpy_faugassign2(a): a[a>30]-=2; return a',
                      numpy.arange(100),
                      numpy_faugassign2=[numpy.array([int])])

    def test_numpy_faugassign3(self):
        self.run_test('def numpy_faugassign3(a): a[a<40]/=2; return a',
                      numpy.arange(100),
                      numpy_faugassign3=[numpy.array([int])])

    def test_numpy_faugassign4(self):
        self.run_test('def numpy_faugassign4(a): a[a<4]|=2; return a',
                      numpy.arange(100),
                      numpy_faugassign4=[numpy.array([int])])

    def test_numpy_faugassign5(self):
        self.run_test('def numpy_faugassign5(a): a[a>8]&=2; return a',
                      numpy.arange(100),
                      numpy_faugassign5=[numpy.array([int])])

    def test_broadcast0(self):
        self.run_test('def numpy_broadcast0(a): a[0] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast0=[numpy.array([numpy.array([int])])])

    def test_broadcast1(self):
        self.run_test('def numpy_broadcast1(a): a[1:-1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast1=[numpy.array([numpy.array([int])])])

    def test_broadcast2(self):
        self.run_test('def numpy_broadcast2(a): a[1:-1,1:-1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast2=[numpy.array([numpy.array([int])])])

    def test_broadcast3(self):
        self.run_test('def numpy_broadcast3(a): a[1:-1,1] = 1 ; return a',
                      numpy.arange(100).reshape((10, 10)),
                      numpy_broadcast3=[numpy.array([numpy.array([int])])])

    def test_broadcast4(self):
        self.run_test('def numpy_broadcast4(a): a[:,1,1] = 1 ; return a',
                      numpy.arange(100).reshape((5,5,4)),
                      numpy_broadcast4=[numpy.array([[[int]]])])

    def test_broadcast5(self):
        self.run_test('def numpy_broadcast5(a): import numpy as np ; return a + np.array([1,2,3,4])',
                      numpy.arange(20).reshape((5,4)),
                      numpy_broadcast5=[numpy.array([[int]])])

    def test_extended_slicing0(self):
        self.run_test("def numpy_extended_slicing0(a): return a[2,1:-1]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing0=[numpy.array([numpy.array([int])])])

    def test_extended_slicing1(self):
        self.run_test("def numpy_extended_slicing1(a): return a[1:-1,2]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing1=[numpy.array([numpy.array([int])])])

    def test_extended_slicing2(self):
        self.run_test("def numpy_extended_slicing2(a): return a[2,1:-1]",
                      numpy.arange(30).reshape((3,5,2)),
                      numpy_extended_slicing2=[numpy.array([numpy.array([numpy.array([int])])])])

    def test_extended_slicing3(self):
        self.run_test("def numpy_extended_slicing3(a): return a[1:-1,2]",
                      numpy.arange(30).reshape((3,5,2)),
                      numpy_extended_slicing3=[numpy.array([[[int]]])])

    def test_extended_slicing4(self):
        self.run_test("def numpy_extended_slicing4(a): return a[1:-1,2:-2]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing4=[numpy.array([numpy.array([int])])])

    def test_extended_slicing5(self):
        self.run_test("def numpy_extended_slicing5(a): return a[1:-1]",
                      numpy.arange(100).reshape((10, 10)),
                      numpy_extended_slicing5=[numpy.array([numpy.array([int])])])

    def test_extended_slicing6(self):
        self.run_test("def numpy_extended_slicing6(a): return a[1:-1,2:-2, 3:-3]",
                      numpy.arange(60).reshape((3,5,4)),
                      numpy_extended_slicing6=[numpy.array([numpy.array([numpy.array([int])])])])

    def test_extended_slicing7(self):
        self.run_test("def numpy_extended_slicing7(a): return a[1:-1, 2, 1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing7=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_slicing8(self):
        self.run_test("def numpy_extended_slicing8(a): return a[1:-1,2:-2, 1:2]",
                      numpy.arange(60).reshape((3,5,4)),
                      numpy_extended_slicing8=[numpy.array([numpy.array([numpy.array([int])])])])

    def test_extended_slicing9(self):
        self.run_test("def numpy_extended_slicing9(a): return a[1:-1, 2, 1, 1:2]",
                      numpy.arange(120).reshape((3,5,2,4)),
                      numpy_extended_slicing9=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_slicing10(self):
        self.run_test("def numpy_extended_slicing10(a): return a[1, 2, 1:-1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing10=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_slicing11(self):
        self.run_test("def numpy_extended_slicing11(a): return a[1, 2, 1:-1, 1]",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_slicing11=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_sum0(self):
        self.run_test("def numpy_extended_sum0(a): import numpy ; return numpy.sum(a)",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum0=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_sum1(self):
        self.run_test("def numpy_extended_sum1(a): import numpy ; return numpy.sum(a[1])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum1=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_sum2(self):
        self.run_test("def numpy_extended_sum2(a): import numpy ; return numpy.sum(a[1,0])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum2=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_sum3(self):
        self.run_test("def numpy_extended_sum3(a): import numpy ; return numpy.sum(a[1:-1])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum3=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_sum4(self):
        self.run_test("def numpy_extended_sum4(a): import numpy ; return numpy.sum(a[1:-1,0])",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum4=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_extended_sum5(self):
        self.run_test("def numpy_extended_sum5(a): import numpy ; return numpy.sum(a)",
                      numpy.arange(120).reshape((3,5,4,2)),
                      numpy_extended_sum5=[numpy.array([numpy.array([numpy.array([numpy.array([int])])])])])

    def test_numpy_shape_as_function(self):
         self.run_test("def numpy_shape_as_function(a): import numpy ; return numpy.shape(a)",
                       numpy.ones(3, numpy.int16),
                       numpy_shape_as_function=[numpy.array([numpy.int16])])

    def test_numpy_size_as_function(self):
         self.run_test("def numpy_size_as_function(a): import numpy ; return numpy.size(a)",
                       numpy.ones(3, numpy.int16),
                       numpy_size_as_function=[numpy.array([numpy.int16])])

    def test_numpy_ndim_as_function(self):
         self.run_test("def numpy_ndim_as_function(a): import numpy ; return numpy.ndim(a)",
                       numpy.ones(3, numpy.int16),
                       numpy_ndim_as_function=[numpy.array([numpy.int16])])

    def test_numpy_bool(self):
        self.run_test("def numpy_bool(n): import numpy ; return numpy.ones(n, bool)",
                      5,
                      numpy_bool=[int])

    def test_numpy_int(self):
        self.run_test("def numpy_int(n): import numpy ; return numpy.ones(n, int)",
                      5,
                      numpy_int=[int])

    def test_numpy_float(self):
        self.run_test("def numpy_float(n): import numpy ; return numpy.ones(n, float)",
                      5,
                      numpy_float=[int])

    def test_numpy_int16(self):
        self.run_test("def numpy_int16(n): import numpy ; return numpy.ones(n, numpy.int16)",
                      5,
                      numpy_int16=[int])

    def test_numpy_uint16(self):
        self.run_test("def numpy_uint16(n): import numpy ; return numpy.ones(n, numpy.uint16)",
                      5,
                      numpy_uint16=[int])

    def test_numpy_uint64(self):
        self.run_test("def numpy_uint64(n): import numpy ; return numpy.ones(n, numpy.uint64)",
                      5,
                      numpy_uint64=[int])

    def test_numpy_float(self):
        self.run_test("def numpy_float(n): import numpy ; return numpy.ones(n, numpy.float)",
                      5,
                      numpy_float=[int])

    def test_numpy_complex(self):
        self.run_test("def numpy_complex(n): import numpy ; return numpy.ones(n, numpy.complex)",
                      5,
                      numpy_complex=[int])

    def test_numpy_complex64(self):
        self.run_test("def numpy_complex64(n): import numpy ; return numpy.ones(n, numpy.complex64)",
                      5,
                      numpy_complex64=[int])

    def test_numpy_double(self):
        self.run_test("def numpy_double(n): import numpy ; return numpy.ones(n, numpy.double)",
                      5,
                      numpy_double=[int])

    def test_numpy_complex_export(self):
        self.run_test("def numpy_complex_export(a): import numpy ; return numpy.sum(a)",
                      numpy.array([1+1j]),
                      numpy_complex_export=[numpy.array([complex])])

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
        self.run_test('def filter_array_0(n): import numpy ; a = numpy.zeros(n) ; return a[a>1]',
                      10,
                      filter_array_0=[int])

    def test_filter_array_1(self):
        self.run_test('def filter_array_1(n): import numpy ; a = numpy.arange(n) ; return a[a>4]',
                      10,
                      filter_array_1=[int])

    def test_filter_array_2(self):
        self.run_test('def filter_array_2(n): import numpy ; a = numpy.arange(n) ; return (a+a)[a>4]',
                      10,
                      filter_array_2=[int])

    def test_filter_array_3(self):
        self.run_test('def filter_array_3(n): import numpy ; a = numpy.arange(n) ; return (-a)[a>4]',
                      10,
                      filter_array_3=[int])

    @unittest.skip("filtering a slice")
    def test_filter_array_4(self):
        self.run_test('def filter_array_4(n): import numpy ; a = numpy.arange(n) ; return a[1:-1][a[1:-1]>4]',
                      10,
                      filter_array_4=[int])

    @unittest.skip("filtering a slice")
    def test_filter_array_5(self):
        self.run_test('def filter_array_5(n): import numpy ; a = numpy.arange(n) ; return (a[1:-1])[a[1:-1]>4]',
                      10,
                      filter_array_5=[int])

    def test_assign_ndarray(self):
        code = """
def assign_ndarray(t):
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
    return c;"""
        self.run_test(code,
                      1,
                      assign_ndarray=[int])

    def test_bitwise_nan_bool(self):
        self.run_test("def np_bitwise_nan_bool(a): import numpy as np ; return ~(a<5)", numpy.arange(10), np_bitwise_nan_bool=[numpy.array([int])])

    def test_frexp0(self):
        self.run_test("def np_frexp0(a): import numpy as np ; return np.frexp(a)", 1.5, np_frexp0=[float])

    def test_frexp1(self):
        self.run_test("def np_frexp1(a): import numpy as np ; return np.frexp(a)", numpy.array([1.1,2.2,3.3]), np_frexp1=[numpy.array([float])])

    def test_frexp2(self):
        self.run_test("def np_frexp2(a): import numpy as np ; return np.frexp(a+a)", numpy.array([1.1,2.2,3.3]), np_frexp2=[numpy.array([float])])

    def test_gslice0(self):
        self.run_test("def np_gslice0(a): import numpy as np; return a[1:9,5:7]", numpy.array(range(10*9)).reshape((10,9)), np_gslice0=[numpy.array([[int]])])

    def test_gslice1(self):
        self.run_test("def np_gslice1(a): import numpy as np ; return a[1:9,0:1, 3:6]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice1=[numpy.array([[[int]]])])

    def test_gslice2(self):
        self.run_test("def np_gslice2(a): import numpy as np ; return a[:,0:1, 3:6]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice2=[numpy.array([[[int]]])])

    def test_gslice3(self):
        self.run_test("def np_gslice3(a): import numpy as np ; return a[:-1,0:-1, -3:7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice3=[numpy.array([[[int]]])])

    def test_gslice4(self):
        self.run_test("def np_gslice4(a): import numpy as np ; return a[1,0:-1, -3:7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice4=[numpy.array([[[int]]])])

    def test_gslice5(self):
        self.run_test("def np_gslice5(a): import numpy as np ; return a[1,0:-1, 7]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice5=[numpy.array([[[int]]])])

    def test_gslice6(self):
        self.run_test("def np_gslice6(a): import numpy as np ; return a[:-1, :][1:,:]", numpy.array(range(10*9*8)).reshape((10,9,8)), np_gslice6=[numpy.array([[[int]]])])

    def test_iexpr0(self):
        self.run_test("def np_iexpr0(a,i): return a[i][0,0]", numpy.array(range(10*9*8)).reshape(10,9,8), 0, np_iexpr0=[numpy.array([[[int]]]), int])

    def test_iexpr1(self):
        self.run_test("def np_iexpr1(a,i): return a[i,0][0]", numpy.array(range(10*9*8)).reshape(10,9,8), 0, np_iexpr1=[numpy.array([[[int]]]), int])

    def test_ndindex0(self):
        self.run_test("def np_ndindex0(): import numpy as np ; return [x for x in np.ndindex(5,6)]",
                      np_ndindex0=[])

    def test_ndindex1(self):
        self.run_test("def np_ndindex1(a): import numpy as np ; return [x for x in np.ndindex(a)]", 3, np_ndindex1=[int])

    def test_ndindex2(self):
        self.run_test("def np_ndindex2(n): import numpy as np ; return [x for x in np.ndindex((n,n))]", 3, np_ndindex2=[int])

    def test_ndenumerate0(self):
        self.run_test("def np_ndenumerate0(a): import numpy as np ; return [x for x in np.ndenumerate(a)]", numpy.array([[1, 2], [3, 4]]), np_ndenumerate0=[numpy.array([[int]])])

    def test_ndenumerate1(self):
        self.run_test("def np_ndenumerate1(a): import numpy as np ; return [x for x in np.ndenumerate(a)]", numpy.array([1, 2, 3, 4]), np_ndenumerate1=[numpy.array([int])])

    def test_nansum0(self):
        self.run_test("def np_nansum0(a): import numpy as np  ; return np.nansum(a)" , numpy.array([[1, 2], [3, numpy.nan]]), np_nansum0=[numpy.array([[float]])])

    def test_nansum1(self):
        self.run_test("def np_nansum1(a): import numpy as np ; return np.nansum(a)" , numpy.array([[1, 2], [numpy.NINF, numpy.nan]]), np_nansum1=[numpy.array([[float]])])

    def test_nansum2(self):
        self.run_test("def np_nansum2(a): import numpy as np ; return np.nansum(a)", [1, numpy.nan], np_nansum2=[[float]])

    def test_nanmin0(self):
        self.run_test("def np_nanmin0(a): import numpy as np ; return np.nanmin(a)" , numpy.array([[1, 2], [3, numpy.nan]]), np_nanmin0=[numpy.array([[float]])])

    def test_nanmin1(self):
        self.run_test("def np_nanmin1(a): import numpy as np ; return np.nanmin(a)" , numpy.array([[1, 2], [numpy.NINF, numpy.nan]]), np_nanmin1=[numpy.array([[float]])])

    def test_nanmax0(self):
        self.run_test("def np_nanmax0(a): import numpy as np ; return np.nanmax(a)" , numpy.array([[1, 2], [3, numpy.nan]]),  np_nanmax0=[numpy.array([[float]])])

    def test_nanmax1(self):
        self.run_test("def np_nanmax1(a): import numpy as np ; return np.nanmax(a)" , numpy.array([[1, 2], [numpy.inf, numpy.nan]]) , np_nanmax1=[numpy.array([[float]])])

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
        self.run_test("def np_nanargmax0(a): from numpy import nanargmax; return nanargmax(a)", numpy.array([[numpy.nan, 4], [2, 3]]),  np_nanargmax0=[numpy.array([[float]])])

    def test_nanargmin0(self):
        self.run_test("def np_nanargmin0(a): from numpy import nanargmin ; return nanargmin(a)", numpy.array([[numpy.nan, 4], [2, 3]]), np_nanargmin0=[numpy.array([[float]])])

    def test_nan_to_num0(self):
        self.run_test("def np_nan_to_num0(a): import numpy as np ; return np.nan_to_num(a)", numpy.array([numpy.inf, -numpy.inf, numpy.nan, -128, 128]), np_nan_to_num0=[numpy.array([float])])

    def test_median0(self):
        self.run_test("def np_median0(a): from numpy import median ; return median(a)", numpy.array([[1, 2], [3, 4]]), np_median0=[numpy.array([[int]])])

    def test_median1(self):
        self.run_test("def np_median1(a): from numpy import median ; return median(a)", numpy.array([1, 2, 3, 4,5]), np_median1=[numpy.array([int])])

    def test_mean0(self):
        self.run_test("def np_mean0(a): from numpy import mean ; return mean(a)", numpy.array([[1, 2], [3, 4]]), np_mean0=[numpy.array([[int]])])

    def test_mean1(self):
        self.run_test("def np_mean1(a): from numpy import mean ; return mean(a, 1)", numpy.array([[1, 2], [3, 4.]]), np_mean1=[numpy.array([[float]])])

    def test_mean2(self):
        self.run_test("def np_mean2(a): from numpy import mean ; return mean(a)", numpy.array([[[1, 2], [3, 4.]]]), np_mean2=[numpy.array([[[float]]])])

    def test_mean3(self):
        self.run_test("def np_mean3(a): from numpy import mean ; return mean(a, 0)", numpy.array([[[1, 2], [3, 4.]]]), np_mean3=[numpy.array([[[float]]])])

    def test_mean4(self):
        self.run_test("def np_mean4(a): from numpy import mean ; return mean(a, 1)", numpy.array([[[1, 2], [3, 4.]]]), np_mean4=[numpy.array([[[float]]])])

    def test_mean5(self):
        self.run_test("def np_mean5(a): from numpy import mean ; return mean(a, 2)", numpy.array([[[1, 2], [3, 4.]]]), np_mean5=[numpy.array([[[float]]])])


    def test_var0(self):
        self.run_test("def np_var0(a): from numpy import var ; return var(a)", numpy.array([[1, 2], [3, 4]], dtype=float), np_var0=[numpy.array([[float]])])

    def test_var1(self):
        self.run_test("def np_var1(a): from numpy import var ; return var(a, 1)", numpy.array([[1, 2], [3, 4.]]), np_var1=[numpy.array([[float]])])

    def test_var2(self):
        self.run_test("def np_var2(a): from numpy import var ; return var(a)", numpy.array([[[1, 2], [3, 4.]]]), np_var2=[numpy.array([[[float]]])])

    def test_var3(self):
        self.run_test("def np_var3(a): from numpy import var ; return var(a, 0)", numpy.array([[[1, 2], [3, 4.]]]), np_var3=[numpy.array([[[float]]])])

    def test_var4(self):
        self.run_test("def np_var4(a): from numpy import var ; return var(a, 1)", numpy.array([[[1, 2], [3, 4.]]]), np_var4=[numpy.array([[[float]]])])

    def test_var5(self):
        self.run_test("def np_var5(a): from numpy import var ; return var(a, 2)", numpy.array([[[1, 2], [3, 4.]]]), np_var5=[numpy.array([[[float]]])])

    def test_logspace0(self):
        self.run_test("def np_logspace0(start, stop): from numpy import logspace ; start, stop = 3., 4. ; return logspace(start, stop, 4)", 3., 4., np_logspace0=[float, float])

    def test_logspace1(self):
        self.run_test("def np_logspace1(start, stop): from numpy import logspace ; return logspace(start, stop, 4, False)", 3., 4., np_logspace1=[float, float])

    def test_logspace2(self):
        self.run_test("def np_logspace2(start, stop): from numpy import logspace ; return logspace(start, stop, 4, True, 2.0)", 3., 4., np_logspace2=[float, float])

    def test_lexsort0(self):
        self.run_test("def np_lexsort0(surnames): from numpy import lexsort ; first_names = ('Heinrich', 'Galileo', 'Gustav') ; return lexsort((first_names, surnames))", ('Hertz',    'Galilei', 'Hertz'), np_lexsort0=[(str, str, str)])

    def test_lexsort1(self):
        self.run_test("def np_lexsort1(a): from numpy import lexsort ; b = [9,4,0,4,0,2,1] ; return lexsort((a,b))", [1,5,1,4,3,4,4], np_lexsort1=[[int]])

    def test_item0(self):
        self.run_test("def np_item0(a): return a.item(3)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item0=[numpy.array([[int]])])

    def test_item1(self):
        self.run_test("def np_item1(a): return a.item(7)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item1=[numpy.array([[int]])])

    def test_item2(self):
        self.run_test("def np_item2(a): return a.item((0,1))",numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]),  np_item2=[numpy.array([[int]])])

    def test_item3(self):
        self.run_test("def np_item3(a): return a.item((2,2))", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item3=[numpy.array([[int]])])

    def test_item4(self):
        self.run_test("def np_item4(a): return a.item(-2)", numpy.array([[3, 1, 7],[2, 8, 3],[8, 5, 3]]), np_item4=[numpy.array([[int]])])

    def test_issctype0(self):
        self.run_test("def np_issctype0(): from numpy import issctype, int32 ; a = int32 ; return issctype(a)", np_issctype0=[])

    def test_issctype1(self):
        self.run_test("def np_issctype1(): from numpy import issctype ; a = list ; return issctype(a)", np_issctype1=[])

    def test_issctype2(self):
        self.run_test("def np_issctype2(a): from numpy import issctype ; return issctype(a)", 3.1, np_issctype2=[float])

    def test_isscalar0(self):
        self.run_test("def np_isscalar0(a): from numpy import isscalar ; return isscalar(a)", 3.1, np_isscalar0=[float])

    def test_isscalar1(self):
        self.run_test("def np_isscalar1(a): from numpy import isscalar ; return isscalar(a)", [3.1], np_isscalar1=[[float]])

    def test_isscalar2(self):
        self.run_test("def np_isscalar2(a): from numpy import isscalar ; return isscalar(a)", '3.1', np_isscalar2=[str])

    def test_isrealobj0(self):
        self.run_test("def np_isrealobj0(a): from numpy import isrealobj ; return isrealobj(a)", numpy.array([1,2,3.]), np_isrealobj0=[numpy.array([float])])

    def test_isrealobj1(self):
        self.run_test("def np_isrealobj1(a): from numpy import isrealobj ; return isrealobj(a)", numpy.array([1,2,3.,4 + 1j]).reshape((2,2)), np_isrealobj1=[numpy.array([[complex]])])

    def test_isreal0(self):
        self.run_test("def np_isreal0(a): from numpy import isreal ; return isreal(a)", numpy.array([1,2,3.]), np_isreal0=[numpy.array([float])])

    def test_isreal1(self):
        self.run_test("def np_isreal1(a): from numpy import isreal ; return isreal(a)", numpy.array([1,2,3.,4 + 1j]).reshape((2,2)), np_isreal1=[numpy.array([[complex]])])

    def test_iscomplex0(self):
        self.run_test("def np_iscomplex0(a): from numpy import iscomplex ; return iscomplex(a)", numpy.array([1, 2, 3.]), np_iscomplex0=[numpy.array([float])])

    def test_iscomplex1(self):
        self.run_test("def np_iscomplex1(a): from numpy import iscomplex ; return iscomplex(a)", numpy.array([1,2,3.,4 + 1j]).reshape((2,2)), np_iscomplex1=[numpy.array([[complex]])])

    def test_intersect1d0(self):
        self.run_test("def np_intersect1d0(a): from numpy import intersect1d ; b = [3, 1, 2, 1] ; return intersect1d(a,b)", [1, 3, 4, 3], np_intersect1d0=[[int]])

    def test_insert0(self):
        self.run_test("def np_insert0(a): from numpy import insert ; return insert(a, 1, 5)", numpy.array([[1, 1], [2, 2], [3, 3]]), np_insert0=[numpy.array([[int]])])

    def test_insert1(self):
        self.run_test("def np_insert1(a): from numpy import insert ; return insert(a, [1,2], [5,6])", numpy.array([[1, 1], [2, 2], [3, 3]]), np_insert1=[numpy.array([[int]])])

    def test_insert2(self):
        self.run_test("def np_insert2(a): from numpy import insert ; return insert(a, [1,1], [5.2,6,7])", numpy.array([[1, 1], [2, 2], [3, 3]]), np_insert2=[numpy.array([[int]])])

    def test_inner0(self):
        self.run_test("def np_inner0(x): from numpy import inner ; y = 3 ; return inner(x,y)", 2, np_inner0=[int])

    def test_inner1(self):
        self.run_test("def np_inner1(x): from numpy import inner ; y = [2, 3] ; return inner(x,y)", [2, 3], np_inner1=[[int]])

    def test_indices0(self):
        self.run_test("def np_indices0(s): from numpy import indices ; return indices(s)", (2, 3), np_indices0=[(int, int)])

    def test_identity0(self):
        self.run_test("def np_identity0(a): from numpy import identity ; return identity(a)", 3, np_identity0=[int])

    def test_identity1(self):
        self.run_test("def np_identity1(a): from numpy import identity ;return identity(a)", 4, np_identity1=[int])

    def test_fromstring0(self):
        self.run_test("def np_fromstring0(a): from numpy import fromstring, uint8 ; return fromstring(a, uint8)", '\x01\x02', np_fromstring0=[str])

    def test_fromstring1(self):
        self.run_test("def np_fromstring1(a): from numpy import fromstring, uint8 ; a = '\x01\x02\x03\x04' ; return fromstring(a, uint8,3)", '\x01\x02\x03\x04', np_fromstring1=[str])

    def test_fromstring2(self):
        self.run_test("def np_fromstring2(a): from numpy import fromstring, uint32 ; return fromstring(a, uint32,-1, ' ')", '1 2 3 4', np_fromstring2=[str])

    def test_fromstring3(self):
        self.run_test("def np_fromstring3(a): from numpy import fromstring, uint32 ; return fromstring(a, uint32,2, ',')", '1,2, 3, 4', np_fromstring3=[str])

    def test_outer0(self):
        self.run_test("def np_outer0(x): from numpy import outer ; return outer(x, x+2)", numpy.arange(6).reshape(2,3), np_outer0=[numpy.array([[int]])])

    def test_outer1(self):
        self.run_test("def np_outer1(x): from numpy import outer; return outer(x, range(6))", numpy.arange(6).reshape((2,3)), np_outer1=[numpy.array([[int]])])

    def test_place0(self):
        self.run_test("def np_place0(x): from numpy import place, ravel ; place(x, x>1, ravel(x**2)); return x", numpy.arange(6).reshape((2,3)), np_place0=[numpy.array([[int]])])

    def test_place1(self):
        self.run_test("def np_place1(x): from numpy import place ; place(x, x>1, [57, 58]); return x", numpy.arange(6).reshape((2,3)), np_place1=[numpy.array([[int]])])

    def test_product(self):
        self.run_test("def np_product(x):\n from numpy import product\n return product(x)", numpy.arange(1, 10), np_product=[numpy.array([int])])

    def test_prod_(self):
        self.run_test("def np_prod_(x):\n from numpy import prod\n return x.prod()", numpy.arange(1, 10), np_prod_=[numpy.array([int])])

    def test_prod_expr(self):
        self.run_test("def np_prod_expr(x):\n from numpy import ones, prod\n return (x + ones(10)).prod()", numpy.arange(10), np_prod_expr=[numpy.array([int])])

    def test_prod2_(self):
        self.run_test("def np_prod2_(x):\n from numpy import prod\n return x.prod()", numpy.arange(1, 11).reshape((2,5)), np_prod2_=[numpy.array([[int]])])

    def test_prod3_(self):
        self.run_test("def np_prod3_(x):\n from numpy import prod\n return x.prod(1)", numpy.arange(1, 11).reshape((2,5)), np_prod3_=[numpy.array([[int]])])

    def test_prod4_(self):
        self.run_test("def np_prod4_(x):\n from numpy import prod\n return x.prod(0)", numpy.arange(1, 11).reshape((2,5)), np_prod4_=[numpy.array([[int]])])

    def test_prod5_(self):
        self.run_test("def np_prod5_(x):\n from numpy import prod\n return x.prod(0)", numpy.arange(1, 11), np_prod5_=[numpy.array([int])])

    def test_ptp0(self):
        self.run_test("def np_ptp0(x): from numpy import ptp ; return ptp(x)", numpy.arange(4).reshape((2,2)), np_ptp0=[numpy.array([[int]])])

    def test_ptp1(self):
        self.run_test("def np_ptp1(x): from numpy import ptp ; return ptp(x,0)", numpy.arange(4).reshape((2,2)), np_ptp1=[numpy.array([[int]])])

    def test_ptp2(self):
        self.run_test("def np_ptp2(x): from numpy import ptp ; return ptp(x,1)", numpy.arange(4).reshape((2,2)), np_ptp2=[numpy.array([[int]])])

    def test_put0(self):
        self.run_test("def np_put0(x): from numpy import put ; put(x, [0,2], [-44, -55]); return x", numpy.arange(5), np_put0=[numpy.array([int])])

    def test_put1(self):
        self.run_test("def np_put1(x): from numpy import put ; put(x, [0,2,3], [57, 58]); return x", numpy.arange(6).reshape((2, 3)), np_put1=[numpy.array([[int]])])

    def test_put2(self):
        self.run_test("def np_put2(x): from numpy import put ; put(x, 2, 57); return x", numpy.arange(6).reshape((2,3)), np_put2=[numpy.array([[int]])])

    def test_putmask0(self):
        self.run_test("def np_putmask0(x): from numpy import putmask ; putmask(x, x>1, x**2); return x", numpy.arange(6).reshape((2,3)), np_putmask0=[numpy.array([[int]])])

    def test_putmask1(self):
        self.run_test("def np_putmask1(x): from numpy import putmask; putmask(x, x>1, [57, 58]); return x", numpy.arange(6).reshape((2,3)), np_putmask1=[numpy.array([[int]])])

    def test_ravel(self):
        self.run_test("def np_ravel(x): from numpy import ravel ; return ravel(x)", numpy.arange(6).reshape((2,3)), np_ravel=[numpy.array([[int]])])

    def test_repeat0(self):
        self.run_test("def np_repeat0(x): from numpy import repeat; return repeat(x, 3)", numpy.arange(3), np_repeat0=[numpy.array([int])])

    def test_repeat1(self):
        self.run_test("def np_repeat1(x): from numpy import repeat; return repeat(x, 3)", numpy.arange(6).reshape(2,3), np_repeat1=[numpy.array([[int]])])

    def test_resize4(self):
        self.run_test("def np_resize4(x): from numpy import resize ; return resize(x, (6,7))", numpy.arange(24).reshape((2,3,4)), np_resize4=[numpy.array([[[int]]])])

    def test_resize3(self):
        self.run_test("def np_resize3(x): from numpy import resize; return resize(x, (6,6))", numpy.arange(24).reshape((2,3,4)), np_resize3=[numpy.array([[[int]]])])

    def test_resize2(self):
        self.run_test("def np_resize2(x): from numpy import resize; return resize(x, (3,3))", numpy.arange(24).reshape((2,3,4)), np_resize2=[numpy.array([[[int]]])])

    def test_resize1(self):
        self.run_test("def np_resize1(x): from numpy import resize; return resize(x, 32)", numpy.arange(24), np_resize1=[numpy.array([int])])

    def test_resize0(self):
        self.run_test("def np_resize0(x): from numpy import resize; return resize(x, 12)", numpy.arange(24), np_resize0=[numpy.array([int])])

    def test_rollaxis2(self):
        self.run_test("def np_rollaxis2(x): from numpy import rollaxis; return rollaxis(x, 2)", numpy.arange(24).reshape((2,3,4)), np_rollaxis2=[numpy.array([[[int]]])])

    def test_rollaxis1(self):
        self.run_test("def np_rollaxis1(x): from numpy import rollaxis; return rollaxis(x, 1, 2)", numpy.arange(24).reshape(2,3,4), np_rollaxis1=[numpy.array([[[int]]])])

    def test_rollaxis0(self):
        self.run_test("def np_rollaxis0(x): from numpy import rollaxis; return rollaxis(x, 1)", numpy.arange(24).reshape(2,3,4), np_rollaxis0=[numpy.array([[[int]]])])

    def test_roll6(self):
        self.run_test("def np_roll6(x): from numpy import roll; return roll(x[:,:,:-1], -1, 2)", numpy.arange(24).reshape(2,3,4), np_roll6=[numpy.array([[[int]]])])

    def test_roll5(self):
        self.run_test("def np_roll5(x): from numpy import roll; return roll(x, -1, 2)", numpy.arange(24).reshape(2,3,4), np_roll5=[numpy.array([[[int]]])])

    def test_roll4(self):
        self.run_test("def np_roll4(x): from numpy import roll; return roll(x, 1, 1)", numpy.arange(24).reshape(2,3,4), np_roll4=[numpy.array([[[int]]])])

    def test_roll3(self):
        self.run_test("def np_roll3(x): from numpy import roll; return roll(x, -1, 0)", numpy.arange(24).reshape(2,3,4), np_roll3=[numpy.array([[[int]]])])

    def test_roll2(self):
        self.run_test("def np_roll2(x): from numpy import roll; return roll(x, -1)", numpy.arange(24).reshape(2,3,4), np_roll2=[numpy.array([[[int]]])])

    def test_roll1(self):
        self.run_test("def np_roll1(x): from numpy import roll; return roll(x, 10)", numpy.arange(24).reshape(2,3,4), np_roll1=[numpy.array([[[int]]])])

    def test_roll0(self):
        self.run_test("def np_roll0(x): from numpy import roll; return roll(x, 3)", numpy.arange(24).reshape(2,3,4), np_roll0=[numpy.array([[[int]]])])

    def test_searchsorted3(self):
        self.run_test("def np_searchsorted3(x): from numpy import searchsorted; return searchsorted(x, [[3,4],[1,87]])", numpy.arange(6), np_searchsorted3=[numpy.array([int])])

    def test_searchsorted2(self):
        self.run_test("def np_searchsorted2(x): from numpy import searchsorted; return searchsorted(x, [[3,4],[1,87]], 'right')", numpy.arange(6), np_searchsorted2=[numpy.array([int])])

    def test_searchsorted1(self):
        self.run_test("def np_searchsorted1(x): from numpy import searchsorted; return searchsorted(x, 3)", numpy.arange(6), np_searchsorted1=[numpy.array([int])])

    def test_searchsorted0(self):
        self.run_test("def np_searchsorted0(x): from numpy import searchsorted; return searchsorted(x, 3, 'right')", numpy.arange(6), np_searchsorted0=[numpy.array([int])])

    def test_rank1(self):
        self.run_test("def np_rank1(x): from numpy import rank; return rank(x)", numpy.arange(24).reshape(2,3,4), np_rank1=[numpy.array([[[int]]])])

    def test_rank0(self):
        self.run_test("def np_rank0(x): from numpy import rank; return rank(x)", numpy.arange(6), np_rank0=[numpy.array([int])])

    def test_rot904(self):
        self.run_test("def np_rot904(x): from numpy import rot90; return rot90(x, 4)", numpy.arange(24).reshape(2,3,4), np_rot904=[numpy.array([[[int]]])])

    def test_rot903(self):
        self.run_test("def np_rot903(x): from numpy import rot90; return rot90(x, 2)", numpy.arange(24).reshape(2,3,4), np_rot903=[numpy.array([[[int]]])])

    def test_rot902(self):
        self.run_test("def np_rot902(x): from numpy import rot90; return rot90(x, 3)", numpy.arange(24).reshape(2,3,4), np_rot902=[numpy.array([[[int]]])])

    def test_rot900(self):
        self.run_test("def np_rot900(x): from numpy import rot90; return rot90(x)", numpy.arange(24).reshape(2,3,4), np_rot900=[numpy.array([[[int]]])])

    def test_rot901(self):
        self.run_test("def np_rot901(x): from numpy import rot90; return rot90(x)", numpy.arange(4).reshape(2,2), np_rot901=[numpy.array([[int]])])

    def test_select2(self):
        self.run_test("def np_select2(x): from numpy import select; condlist = [x<3, x>5]; choicelist = [x, x**2]; return select(condlist, choicelist)", numpy.arange(10).reshape(2,5), np_select2=[numpy.array([[int]])])

    def test_select1(self):
        self.run_test("def np_select1(x): from numpy import select; condlist = [x<3, x>5]; choicelist = [x+3, x**2]; return select(condlist, choicelist)", numpy.arange(10), np_select1=[numpy.array([int])])

    def test_select0(self):
        self.run_test("def np_select0(x): from numpy import select; condlist = [x<3, x>5]; choicelist = [x, x**2]; return select(condlist, choicelist)", numpy.arange(10), np_select0=[numpy.array([int])])

    def test_sometrue0(self):
        self.run_test("def np_sometrue0(a): from numpy import sometrue ; return sometrue(a)", numpy.array([[True, False], [True, True]]), np_sometrue0=[numpy.array([[bool]])])

    def test_sometrue1(self):
        self.run_test("def np_sometrue1(a): from numpy import sometrue ; return sometrue(a, 0)", numpy.array([[True, False], [False, False]]), np_sometrue1=[numpy.array([[bool]])])

    def test_sometrue2(self):
        self.run_test("def np_sometrue2(a): from numpy import sometrue ; return sometrue(a)", [-1, 0, 5], np_sometrue2=[[int]])

    def test_sort0(self):
        self.run_test("def np_sort0(a): from numpy import sort ; return sort(a)", numpy.array([[1,6],[7,5]]), np_sort0=[numpy.array([[int]])])

    def test_sort1(self):
        self.run_test("def np_sort1(a): from numpy import sort ; return sort(a)", numpy.array([2, 1, 6, 3, 5]), np_sort1=[numpy.array([int])])

    def test_sort2(self):
        self.run_test("def np_sort2(a): from numpy import sort ; return sort(a)", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort2=[numpy.array([[[int]]])])

    def test_sort3(self):
        self.run_test("def np_sort3(a): from numpy import sort ; return sort(a, 0)", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort3=[numpy.array([[[int]]])])

    def test_sort4(self):
        self.run_test("def np_sort4(a): from numpy import sort ; return sort(a, 1)", numpy.arange(2*3*4, 0, -1).reshape(2,3,4), np_sort4=[numpy.array([[[int]]])])

    def test_sort_complex0(self):
        self.run_test("def np_sort_complex0(a): from numpy import sort_complex ; return sort_complex(a)", numpy.array([[1,6],[7,5]]), np_sort_complex0=[numpy.array([[int]])])

    def test_sort_complex1(self):
        self.run_test("def np_sort_complex1(a): from numpy import sort_complex ; return sort_complex(a)", numpy.array([1 + 2j, 2 - 1j, 3 - 2j, 3 - 3j, 3 + 5j]), np_sort_complex1=[numpy.array([complex])])

    def test_split0(self):
        self.run_test("def np_split0(a): from numpy import split,array2string ; return map(array2string,split(a, 3))", numpy.arange(12), np_split0=[numpy.array([int])])

    def test_split1(self):
        self.run_test("def np_split1(a):\n from numpy import split\n try:\n  print split(a, 5)\n  return False\n except ValueError:\n  return True", numpy.arange(12), np_split1=[numpy.array([int])])

    def test_split2(self):
        self.run_test("def np_split2(a): from numpy import split, array2string; return map(array2string,split(a, [0,1,5]))", numpy.arange(12).reshape(6,2), np_split2=[numpy.array([[int]])])

    def test_take0(self):
        self.run_test("def np_take0(a):\n from numpy import take\n return take(a, [0,1])", numpy.arange(24).reshape(2,3,4), np_take0=[numpy.array([[[int]]])])

    def test_take1(self):
        self.run_test("def np_take1(a):\n from numpy import take\n return take(a, [[0,0,2,2],[1,0,1,2]])", numpy.arange(24).reshape(2,3,4), np_take1=[numpy.array([[[int]]])])

    def test_swapaxes_(self):
        self.run_test("def np_swapaxes_(a):\n from numpy import swapaxes\n return swapaxes(a, 1, 2)", numpy.arange(24).reshape(2,3,4), np_swapaxes_=[numpy.array([[[int]]])])

    def test_tile0(self):
        self.run_test("def np_tile0(a): from numpy import tile ; return tile(a, 3)", numpy.arange(4), np_tile0=[numpy.array([int])])

    def test_tile1(self):
        self.run_test("def np_tile1(a): from numpy import tile ; return tile(a, (3, 2))", numpy.arange(4), np_tile1=[numpy.array([int])])

    def test_tolist0(self):
        self.run_test("def np_tolist0(a): return a.tolist()", numpy.arange(12), np_tolist0=[numpy.array([int])])

    def test_tolist1(self):
        self.run_test("def np_tolist1(a): return a.tolist()", numpy.arange(12).reshape(3,4), np_tolist1=[numpy.array([[int]])])

    def test_tolist2(self):
        self.run_test("def np_tolist2(a): return a.tolist()", numpy.arange(2*3*4*5).reshape(2,3,4,5), np_tolist2=[numpy.array([[[[int]]]])])

    def test_tostring0(self):
        self.run_test("def np_tostring0(a): return a.tostring()", numpy.arange(80, 100), np_tostring0=[numpy.array([int])])

    def test_tostring1(self):
        self.run_test("def np_tostring1(a): return a.tostring()", numpy.arange(500, 600), np_tostring1=[numpy.array([int])])

    def test_fromiter0(self):
        self.run_test("def g(): yield 1 ; yield 2\ndef np_fromiter0(): from numpy import fromiter, float32 ; iterable = g() ; return fromiter(iterable, float32)", np_fromiter0=[])

    def test_fromiter1(self):
        self.run_test("def np_fromiter1(): from numpy import fromiter, float32 ; iterable = (x*x for x in range(5)) ; return fromiter(iterable, float32, 5)", np_fromiter1=[])

    def test_fromfunction0(self):
        self.run_test("def np_fromfunction0(s): from numpy import fromfunction ; return fromfunction(lambda i: i == 1, s)", (3,), np_fromfunction0=[(int,)])

    def test_fromfunction1(self):
        self.run_test("def np_fromfunction1(s): from numpy import fromfunction; return fromfunction(lambda i, j: i + j, s)", (3, 3), np_fromfunction1=[(int, int)])

    def test_flipud0(self):
        self.run_test("def np_flipud0(x): from numpy import flipud ; return flipud(x)", numpy.arange(9).reshape(3,3), np_flipud0=[numpy.array([[int]])])

    def test_fliplr0(self):
        self.run_test("def np_fliplr0(x): from numpy import fliplr ; return fliplr(x)", numpy.arange(9).reshape(3,3), np_fliplr0=[numpy.array([[int]])])

    def test_flatten0(self):
        self.run_test("def np_flatten0(x): return x.flatten()", numpy.array([[1,2], [3,4]]), np_flatten0=[numpy.array([[int]])])

    def test_flatnonzero0(self):
        self.run_test("def np_flatnonzero0(x): from numpy import flatnonzero ; return flatnonzero(x)", numpy.arange(-2, 3), np_flatnonzero0=[numpy.array([int])])

    def test_flatnonzero1(self):
        self.run_test("def np_flatnonzero1(x): from numpy import flatnonzero ;  return flatnonzero(x[1:-1])", numpy.arange(-2, 3), np_flatnonzero1=[numpy.array([int])])

    def test_fix0(self):
        self.run_test("def np_fix0(x): from numpy import fix ; return fix(x)", 3.14, np_fix0=[float])

    def test_fix1(self):
        self.run_test("def np_fix1(x): from numpy import fix ; return fix(x)", 3, np_fix1=[int])

    def test_fix2(self):
        self.run_test("def np_fix2(x): from numpy import fix ; return fix(x)", numpy.array([2.1, 2.9, -2.1, -2.9]), np_fix2=[numpy.array([float])])

    def test_fix3(self):
        self.run_test("def np_fix3(x): from numpy import fix ; return fix(x)", numpy.array([2.1, 2.9, -2.1, -2.9]), np_fix3=[numpy.array([float])])

    def test_fix4(self):
        self.run_test("def np_fix4(x): from numpy import fix ; return fix(x+x)", numpy.array([2.1, 2.9, -2.1, -2.9]), np_fix4=[numpy.array([float])])

    def test_finfo0(self):
        self.run_test("def np_finfo0(): from numpy import finfo, float64 ; x = finfo(float64) ; return x.eps", np_finfo0=[])

    def test_fill0(self):
        self.run_test("def np_fill0(x): x.fill(5) ; return x", numpy.ones((2, 3)), np_fill0=[numpy.array([[float]])])

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

    def test_ediff1d0(self):
        self.run_test("def np_ediff1d0(x): from numpy import ediff1d ; return ediff1d(x)", [1,2,4,7,0], np_ediff1d0=[[int]])

    def test_ediff1d1(self):
        self.run_test("def np_ediff1d1(x): from numpy import ediff1d ; return ediff1d(x)", [[1,2,4],[1,6,24]], np_ediff1d1=[[[int]]])

    def test_dot0(self):
        self.run_test("def np_dot0(x, y): from numpy import dot ; return dot(x,y)", 2, 3, np_dot0=[int, int])

    def test_dot1(self):
        self.run_test("def np_dot1(x): from numpy import dot ; y = [2, 3] ; return dot(x,y)", [2, 3], np_dot1=[[int]])

    def test_dot2(self):
        self.run_test("def np_dot2(x): from numpy import dot ; y = [2j, 3j] ; return dot(x,y)", [2j, 3j], np_dot2=[[complex]])

    def test_dot3(self):
        self.run_test("def np_dot3(x): from numpy import array, dot ; y = array([2, 3]) ; return dot(x+x,y)", numpy.array([2, 3]), np_dot3=[numpy.array([int])])

    def test_dot4(self):
        self.run_test("def np_dot4(x): from numpy import dot ; y = [2, 3] ; return dot(x,y)", numpy.array([2, 3]), np_dot4=[numpy.array([int])])

    def test_digitize0(self):
        self.run_test("def np_digitize0(x): from numpy import array, digitize ; bins = array([0.0, 1.0, 2.5, 4.0, 10.0]) ; return digitize(x, bins)", numpy.array([0.2, 6.4, 3.0, 1.6]), np_digitize0=[numpy.array([float])])

    def test_digitize1(self):
        self.run_test("def np_digitize1(x): from numpy import array, digitize ; bins = array([ 10.0, 4.0, 2.5, 1.0, 0.0]) ; return digitize(x, bins)", numpy.array([0.2, 6.4, 3.0, 1.6]), np_digitize1=[numpy.array([float])])

    def test_diff0(self):
        self.run_test("def np_diff0(x): from numpy import diff; return diff(x)", numpy.array([1, 2, 4, 7, 0]), np_diff0=[numpy.array([int])])

    def test_diff1(self):
        self.run_test("def np_diff1(x): from numpy import diff; return diff(x,2)", numpy.array([1, 2, 4, 7, 0]), np_diff1=[numpy.array([int])])

    def test_diff2(self):
        self.run_test("def np_diff2(x): from numpy import diff; return diff(x)", numpy.array([[1, 3, 6, 10], [0, 5, 6, 8]]), np_diff2=[numpy.array([[int]])])

    def test_diff3(self):
        self.run_test("def np_diff3(x): from numpy import diff; return diff(x,2)", numpy.array([[1, 3, 6, 10], [0, 5, 6, 8]]), np_diff3=[numpy.array([[int]])])

    def test_diff4(self):
        self.run_test("def np_diff4(x): from numpy import diff; return diff(x + x)", numpy.array([1, 2, 4, 7, 0]), np_diff4=[numpy.array([int])])

    def test_trace0(self):
        self.run_test("def np_trace0(x): from numpy import trace; return trace(x)", numpy.arange(9).reshape(3,3), np_trace0=[numpy.array([[int]])])

    def test_trace1(self):
        self.run_test("def np_trace1(x): from numpy import trace; return trace(x, 1)", numpy.arange(12).reshape(3,4), np_trace1=[numpy.array([[int]])])

    def test_trace2(self):
        self.run_test("def np_trace2(x): from numpy import trace; return trace(x, 1)", numpy.arange(12).reshape(3,4), np_trace2=[numpy.array([[int]])])

    def test_tri0(self):
        self.run_test("def np_tri0(a): from numpy import tri; return tri(a)", 3, np_tri0=[int])

    def test_tri1(self):
        self.run_test("def np_tri1(a): from numpy import tri; return tri(a, 4)", 3, np_tri1=[int])

    def test_tri2(self):
        self.run_test("def np_tri2(a): from numpy import tri; return tri(a, 3, -1)", 4, np_tri2=[int])

    def test_tri3(self):
        self.run_test("def np_tri3(a): from numpy import tri, int64; return tri(a, 5, 1, int64)", 3, np_tri3=[int])

    def test_trim_zeros0(self):
        self.run_test("""
def np_trim_zeros0(x):
    from numpy import array, trim_zeros
    return trim_zeros(x)""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros0=[numpy.array([int])])

    def test_trim_zeros1(self):
        self.run_test("""
def np_trim_zeros1(x):
    from numpy import array, trim_zeros
    return trim_zeros(x, "f")""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros1=[numpy.array([int])])

    def test_trim_zeros2(self):
        self.run_test("""
def np_trim_zeros2(x):
    from numpy import trim_zeros
    return trim_zeros(x, "b")""", numpy.array((0, 0, 0, 1, 2, 3, 0, 2, 1, 0)), np_trim_zeros2=[numpy.array([int])])

    def test_triu0(self):
        self.run_test("def np_triu0(x): from numpy import triu; return triu(x)", numpy.arange(12).reshape(3,4), np_triu0=[numpy.array([[int]])])

    def test_triu1(self):
        self.run_test("def np_triu1(x): from numpy import triu; return triu(x, 1)", numpy.arange(12).reshape(3,4), np_triu1=[numpy.array([[int]])])

    def test_triu2(self):
        self.run_test("def np_triu2(x): from numpy import triu; return triu(x, -1)", numpy.arange(12).reshape(3,4), np_triu2=[numpy.array([[int]])])

    def test_tril0(self):
        self.run_test("def np_tril0(x): from numpy import tril; return tril(x)", numpy.arange(12).reshape(3,4), np_tril0=[numpy.array([[int]])])

    def test_tril1(self):
        self.run_test("def np_tril1(x): from numpy import tril; return tril(x, 1)", numpy.arange(12).reshape(3,4), np_tril1=[numpy.array([[int]])])

    def test_tril2(self):
        self.run_test("def np_tril2(x): from numpy import tril; return tril(x, -1)", numpy.arange(12).reshape(3,4), np_tril2=[numpy.array([[int]])])

    def test_union1d(self):
        self.run_test("def np_union1d(x): from numpy import arange, union1d ; y = arange(1,4); return union1d(x, y)", numpy.arange(-1,2), np_union1d=[numpy.array([int])])

    def test_unique0(self):
        self.run_test("def np_unique0(x): from numpy import unique ; return unique(x)", numpy.array([1,1,2,2,2,1,5]), np_unique0=[numpy.array([int])])

    def test_unique1(self):
        self.run_test("def np_unique1(x): from numpy import unique ; return unique(x)", numpy.array([[1,2,2],[2,1,5]]), np_unique1=[numpy.array([[int]])])

    def test_unique2(self):
        self.run_test("def np_unique2(x): from numpy import unique ; return unique(x, True)", numpy.array([1,1,2,2,2,1,5]), np_unique2=[numpy.array([int])])

    def test_unique3(self):
        self.run_test("def np_unique3(x): from numpy import unique ; return unique(x, True, True)", numpy.array([1,1,2,2,2,1,5]), np_unique3=[numpy.array([int])])

    def test_unwrap0(self):
        self.run_test("def np_unwrap0(x): from numpy import unwrap, pi ; x[:3] += 2*pi; return unwrap(x)", numpy.arange(6), np_unwrap0=[numpy.array([int])])

    def test_unwrap1(self):
        self.run_test("def np_unwrap1(x): from numpy import unwrap, pi ; x[:3] += 2*pi; return unwrap(x, 4)", numpy.arange(6), np_unwrap1=[numpy.array([int])])

    def test_unwrap2(self):
        self.run_test("def np_unwrap2(x): from numpy import unwrap, pi ; x[:3] -= 2*pi; return unwrap(x, 4)", numpy.arange(6), np_unwrap2=[numpy.array([int])])

    def test_nonzero0(self):
        self.run_test("def np_nonzero0(x): from numpy import nonzero ; return nonzero(x)", numpy.arange(6), np_nonzero0=[numpy.array([int])])

    def test_nonzero1(self):
        self.run_test("def np_nonzero1(x): from numpy import nonzero ; return nonzero(x>8)", numpy.arange(6), np_nonzero1=[numpy.array([int])])

    def test_nonzero2(self):
        self.run_test("def np_nonzero2(x): from numpy import nonzero ; return nonzero(x>0)", numpy.arange(6).reshape(2,3), np_nonzero2=[numpy.array([[int]])])

    def test_diagflat3(self):
        self.run_test("def np_diagflat3(a): from numpy import diagflat ; return diagflat(a)", numpy.arange(2), np_diagflat3=[numpy.array([int])])

    def test_diagflat4(self):
        self.run_test("def np_diagflat4(a): from numpy import diagflat ; return diagflat(a,1)", numpy.arange(3), np_diagflat4=[numpy.array([int])])

    def test_diagflat5(self):
        self.run_test("def np_diagflat5(a): from numpy import diagflat ; return diagflat(a,-2)", numpy.arange(4), np_diagflat5=[numpy.array([int])])

    def test_diagonal0(self):
        self.run_test("def np_diagonal0(a): from numpy import diagonal ; return diagonal(a)", numpy.arange(10).reshape(2,5), np_diagonal0=[numpy.array([[int]])])

    def test_diagonal1(self):
        self.run_test("def np_diagonal1(a): from numpy import diagonal ; return diagonal(a,1)", numpy.arange(9).reshape(3,3), np_diagonal1=[numpy.array([[int]])])

    def test_diagonal2(self):
        self.run_test("def np_diagonal2(a): from numpy import diagonal ; return diagonal(a,-2)", numpy.arange(9).reshape(3,3), np_diagonal2=[numpy.array([[int]])])

    def test_diag0(self):
        self.run_test("def np_diag0(a): from numpy import diag ; return diag(a)", numpy.arange(10).reshape(2,5), np_diag0=[numpy.array([[int]])])

    def test_diag1(self):
        self.run_test("def np_diag1(a): from numpy import diag ; return diag(a,1)", numpy.arange(9).reshape(3,3), np_diag1=[numpy.array([[int]])])

    def test_diag2(self):
        self.run_test("def np_diag2(a): from numpy import diag ; return diag(a,-2)", numpy.arange(9).reshape(3,3), np_diag2=[numpy.array([[int]])])

    def test_diag2b(self):
        self.run_test("def np_diag2b(a): from numpy import diag ; return diag(a,-2)", numpy.arange(12).reshape(4,3), np_diag2b=[numpy.array([[int]])])

    def test_diag3(self):
        self.run_test("def np_diag3(a): from numpy import diag ; return diag(a)", numpy.arange(2), np_diag3=[numpy.array([int])])

    def test_diag4(self):
        self.run_test("def np_diag4(a): from numpy import diag ; return diag(a,1)", numpy.arange(3), np_diag4=[numpy.array([int])])

    def test_diag5(self):
        self.run_test("def np_diag5(a): from numpy import diag; return diag(a,-2)", numpy.arange(4), np_diag5=[numpy.array([int])])

    def test_delete0(self):
        self.run_test("def np_delete0(a): from numpy import delete ; return delete(a, 1)", numpy.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]), np_delete0=[numpy.array([[int]])])

    def test_delete1(self):
        self.run_test("def np_delete1(a): from numpy import delete ; return delete(a, [1,3,5])", numpy.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]), np_delete1=[numpy.array([[int]])])

    def test_where0(self):
        self.run_test("""def np_where0(a):
    from numpy import arange, where
    b = arange(5, 17).reshape((3,4))
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(c , a, b)""", numpy.arange(12).reshape(3,4), np_where0=[numpy.array([[int]])])

    def test_where1(self):
        self.run_test("""def np_where1(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, c)""", numpy.arange(12).reshape(3,4), np_where1=[numpy.array([[int]])])

    def test_where2(self):
        self.run_test("""def np_where2(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, c)""", numpy.arange(12).reshape(3,4), np_where2=[numpy.array([[int]])])

    def test_where3(self):
        self.run_test("""def np_where3(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, 5)""", numpy.arange(12).reshape(3,4), np_where3=[numpy.array([[int]])])

    def test_where4(self):
        self.run_test("""def np_where4(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, 6)""", numpy.arange(12).reshape(3,4), np_where4=[numpy.array([[int]])])

    def test_where5(self):
        self.run_test("""def np_where5(a):
    from numpy import arange, where
    b = arange(5, 17).reshape((3,4))
    return where(a>5 , a, b)""", numpy.arange(12).reshape(3,4), np_where5=[numpy.array([[int]])])

    def test_where6(self):
        self.run_test("""def np_where6(a):
    from numpy import arange, where
    return where(a>5 , 1, 2)""", numpy.arange(12).reshape(3,4), np_where6=[numpy.array([[int]])])

    def test_where7(self):
        self.run_test("""def np_where7(a):
    from numpy import arange, where
    return where(a>5)""", numpy.arange(12).reshape(3,4), np_where7=[numpy.array([[int]])])

    def test_cumprod_(self):
        self.run_test("def np_cumprod_(a):\n from numpy import cumprod\n return a.cumprod()", numpy.arange(10), np_cumprod_=[numpy.array([int])])

    def test_cumprod2_(self):
        self.run_test("def np_cumprod2_(a):\n from numpy import cumprod\n return a.cumprod()", numpy.arange(10).reshape(2,5), np_cumprod2_=[numpy.array([[int]])])

    def test_cumprod3_(self):
        self.run_test("def np_cumprod3_(a):\n from numpy import cumprod\n return a.cumprod(1)", numpy.arange(10).reshape(2,5), np_cumprod3_=[numpy.array([[int]])])

    def test_cumprod4_(self):
        self.run_test("def np_cumprod4_(a):\n from numpy import cumprod\n return a.cumprod(0)", numpy.arange(10).reshape(2,5), np_cumprod4_=[numpy.array([[int]])])

    def test_cumprod5_(self):
        self.run_test("def np_cumprod5_(a):\n from numpy import cumprod\n return a.cumprod(0)", numpy.arange(10), np_cumprod5_=[numpy.array([int])])

    def test_copy0(self):
        code= '''
def test_copy0(x):
    import numpy as np
    y = x
    z = np.copy(x)
    x[0] = 10
    return x[0], y[0], z[0]'''
        self.run_test(code, numpy.array([1, 2, 3]), test_copy0=[numpy.array([int])])

    def test_clip0(self):
        self.run_test("def np_clip0(a): from numpy import clip ; return clip(a,1,8)", numpy.arange(10), np_clip0=[numpy.array([int])])

    def test_clip1(self):
        self.run_test("def np_clip1(a): from numpy import  clip ; return clip(a,3,6)", numpy.arange(10), np_clip1=[numpy.array([int])])

    def test_concatenate0(self):
        self.run_test("def np_concatenate0(a): from numpy import array, concatenate ; b = array([[5, 6]]) ; return concatenate((a,b))", numpy.array([[1, 2], [3, 4]]), np_concatenate0=[numpy.array([[int]])])

    def test_bincount0(self):
        self.run_test("def np_bincount0(a): from numpy import bincount ; return bincount(a)", numpy.arange(5), np_bincount0=[numpy.array([int])])

    def test_bincount1(self):
        self.run_test("def np_bincount1(a, w): from numpy import bincount; return bincount(a,w)", numpy.array([0, 1, 1, 2, 2, 2]), numpy.array([0.3, 0.5, 0.2, 0.7, 1., -0.6]), np_bincount1=[numpy.array([int]), numpy.array([float])])

    def test_binary_repr0(self):
        self.run_test("def np_binary_repr0(a): from numpy import binary_repr ; return binary_repr(a)", 3, np_binary_repr0=[int])

    def test_binary_repr1(self):
        self.run_test("def np_binary_repr1(a): from numpy import binary_repr ; return binary_repr(a)", -3, np_binary_repr1=[int])

    def test_binary_repr2(self):
        self.run_test("def np_binary_repr2(a): from numpy import binary_repr ; return binary_repr(a,4)", 3, np_binary_repr2=[int])

    def test_binary_repr3(self):
        self.run_test("def np_binary_repr3(a): from numpy import binary_repr ; return binary_repr(a,4)", -3, np_binary_repr3=[int])

    def test_base_repr0(self):
        self.run_test("def np_base_repr0(a): from numpy import base_repr ; return base_repr(a)", 5, np_base_repr0=[int])

    def test_base_repr1(self):
        self.run_test("def np_base_repr1(a): from numpy import base_repr ; return base_repr(a,5)", 6, np_base_repr1=[int])

    def test_base_repr2(self):
        self.run_test("def np_base_repr2(a): from numpy import base_repr ; return base_repr(a,5,3)", 7, np_base_repr2=[int])

    def test_base_repr3(self):
        self.run_test("def np_base_repr3(a): from numpy import base_repr ; return base_repr(a, 16)", 10, np_base_repr3=[int])

    def test_base_repr4(self):
        self.run_test("def np_base_repr4(a): from numpy import base_repr ; return base_repr(a, 16)", 32, np_base_repr4=[int])

    def test_average0(self):
        self.run_test("def np_average0(a): from numpy import average ; return average(a)", numpy.arange(10), np_average0=[numpy.array([int])])

    def test_average1(self):
        self.run_test("def np_average1(a): from numpy import average ; return average(a,1)", numpy.arange(10).reshape(2,5), np_average1=[numpy.array([[int]])])

    def test_average2(self):
        self.run_test("def np_average2(a): from numpy import average ; return average(a,None, range(10))", numpy.arange(10), np_average2=[numpy.array([int])])

    def test_average3(self):
        self.run_test("def np_average3(a): from numpy import average ; return average(a,None, a)", numpy.arange(10).reshape(2,5), np_average3=[numpy.array([[int]])])

    def test_atleast_1d0(self):
        self.run_test("def np_atleast_1d0(a): from numpy import atleast_1d ; return atleast_1d(a)", 1, np_atleast_1d0=[int])

    def test_atleast_1d1(self):
        self.run_test("def np_atleast_1d1(a): from numpy import atleast_1d ; r = atleast_1d(a) ; return r is a", numpy.arange(2), np_atleast_1d1=[numpy.array([int])])

    def test_atleast_2d0(self):
        self.run_test("def np_atleast_2d0(a): from numpy import atleast_2d ; return atleast_2d(a)", 1, np_atleast_2d0=[int])

    def test_atleast_2d1(self):
        self.run_test("def np_atleast_2d1(a): from numpy import atleast_2d ; r = atleast_2d(a) ; return r is a", numpy.arange(2).reshape(1,2), np_atleast_2d1=[numpy.array([[int]])])

    def test_atleast_2d2(self):
        self.run_test("def np_atleast_2d2(a): from numpy import atleast_2d ; r = atleast_2d(a) ; return r", numpy.arange(2), np_atleast_2d2=[numpy.array([int])])

    def test_atleast_3d0(self):
        self.run_test("def np_atleast_3d0(a): from numpy import atleast_3d ; return atleast_3d(a)", 1, np_atleast_3d0=[int])

    def test_atleast_3d1(self):
        self.run_test("def np_atleast_3d1(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r is a", numpy.arange(8).reshape(2,2,2), np_atleast_3d1=[numpy.array([[[int]]])])

    def test_atleast_3d2(self):
        self.run_test("def np_atleast_3d2(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r", numpy.arange(8).reshape(2,4), np_atleast_3d2=[numpy.array([[int]])])

    def test_atleast_3d3(self):
        self.run_test("def np_atleast_3d3(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r", numpy.arange(8), np_atleast_3d3=[numpy.array([int])])

    def test_asscalar0(self):
        self.run_test("def np_asscalar0(a): from numpy import asscalar; return asscalar(a)", numpy.array([1], numpy.int32), np_asscalar0=[numpy.array([numpy.int32])])

    def test_asscalar1(self):
        self.run_test("def np_asscalar1(a): from numpy import asscalar; return asscalar(a)", numpy.array([[1]], numpy.int64), np_asscalar1=[numpy.array([numpy.int64])])

    def test_ascontiguousarray0(self):
        self.run_test("def np_ascontiguousarray0(a):\n from numpy import ascontiguousarray\n return ascontiguousarray(a)", (1,2,3), np_ascontiguousarray0=[(int, int, int)])

    def test_asarray_chkfinite0(self):
        self.run_test("def np_asarray_chkfinite0(a):\n from numpy import asarray_chkfinite\n return asarray_chkfinite(a)", (1,2,3), np_asarray_chkfinite0=[(int, int, int)])

    def test_asarray_chkfinite1(self):
        self.run_test("def np_asarray_chkfinite1(a, x):\n from numpy import asarray_chkfinite\n try: return asarray_chkfinite(a)\n except ValueError: return asarray_chkfinite(x)", [[1,2],[numpy.nan,4]], [[1.,2.],[3.,4.]], np_asarray_chkfinite1=[[[float]], [[float]]])

    def test_asarray0(self):
        self.run_test("def np_asarray0(a):\n from numpy import asarray\n return asarray(a)", (1,2,3), np_asarray0=[(int, int, int)])

    def test_asarray1(self):
        self.run_test("def np_asarray1(a):\n from numpy import asarray\n return asarray(a)", [(1,2),(3,4)], np_asarray1=[[(int, int)]])

    def test_asarray2(self):
        self.run_test("def np_asarray2(a):\n from numpy import asarray, int8\n return asarray(a, int8)", [1., 2., 3.], np_asarray2=[[float]])

    def test_asarray3(self):
        self.run_test("def np_asarray3(a):\n from numpy import asarray; b = asarray(a) ; return a is b", numpy.arange(3), np_asarray3=[numpy.array([int])])

    def test_array_str0(self):
        self.run_test("def np_array_str0(x): from numpy import array_str ; return array_str(x)", numpy.arange(3), np_array_str0=[numpy.array([int])])

    def test_array_split0(self):
        self.run_test("def np_array_split0(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, 3))", numpy.arange(12), np_array_split0=[numpy.array([int])])

    def test_array_split1(self):
        self.run_test("def np_array_split1(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, 5))", numpy.arange(12), np_array_split1=[numpy.array([int])])

    def test_array_split2(self):
        self.run_test("def np_array_split2(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, 4))", numpy.arange(12).reshape(6,2), np_array_split2=[numpy.array([[int]])])

    def test_array_split3(self):
        self.run_test("def np_array_split3(a): from numpy import array_split, array2string ; return map(array2string,array_split(a, [0,1,5]))", numpy.arange(12).reshape(6,2), np_array_split3=[numpy.array([[int]])])

    def test_array_equiv0(self):
        self.run_test("def np_array_equiv0(a): from numpy import array_equiv ;  b = [1,2] ; return array_equiv(a,b)", [1, 2], np_array_equiv0=[[int]])

    def test_array_equiv1(self):
        self.run_test("def np_array_equiv1(a): from numpy import array_equiv ;  b = [1,3] ; return array_equiv(a,b)", [1, 2], np_array_equiv1=[[int]])

    def test_array_equiv2(self):
        self.run_test("def np_array_equiv2(a): from numpy import array_equiv ;  b = [[1,2],[1,2]] ; return array_equiv(a,b)", [1, 2], np_array_equiv2=[[int]])

    def test_array_equiv3(self):
        self.run_test("def np_array_equiv3(a): from numpy import array_equiv ;  b = [[1,2],[1,3]] ; return array_equiv(a,b)", [1, 2], np_array_equiv3=[[int]])

    def test_array_equal0(self):
        self.run_test("def np_array_equal0(a): from numpy import array_equal ;  b = [1,2] ; return array_equal(a,b)", [1, 2], np_array_equal0=[[int]])

    def test_array_equal1(self):
        self.run_test("def np_array_equal1(a): from numpy import array, array_equal ;  b = array([1,2]) ; return array_equal(a,b)", numpy.array([1,2]), np_array_equal1=[numpy.array([int])])

    def test_array_equal2(self):
        self.run_test("def np_array_equal2(a): from numpy import array, array_equal ;  b = array([[1,2],[3,5]]) ; return array_equal(a,b)", numpy.array([[1,2],[3,5]]), np_array_equal2=[numpy.array([[int]])])

    def test_array_equal3(self):
        self.run_test("def np_array_equal3(a): from numpy import array, array_equal ;  b = array([[1,2],[4,5]]) ; return array_equal(a,b)", numpy.array([[1,2],[3,5]]), np_array_equal3=[numpy.array([[int]])])

    def test_array_equal4(self):
        self.run_test("def np_array_equal4(a): from numpy import array, array_equal ;  b = array([1,2,3]) ; return array_equal(a,b)", numpy. array([1,2]), np_array_equal4=[numpy.array([int])])

    def test_array2string0(self):
        self.run_test("def np_array2string0(x): from numpy import array2string ; return array2string(x)", numpy.arange(3), np_array2string0=[numpy.array([int])])

    def test_argwhere0(self):
        self.run_test("def np_argwhere0(x): from numpy import argwhere ; return argwhere(x)", numpy.arange(6), np_argwhere0=[numpy.array([int])])

    def test_argwhere1(self):
        self.run_test("def np_argwhere1(x): from numpy import argwhere ; return argwhere(x>8)", numpy.arange(6), np_argwhere1=[numpy.array([int])])

    def test_argwhere2(self):
        self.run_test("def np_argwhere2(x): from numpy import argwhere ; return argwhere(x>0)", numpy.arange(6).reshape(2,3), np_argwhere2=[numpy.array([[int]])])

    def test_around0(self):
        self.run_test("def np_around0(x): from numpy import around ; return around(x)", [0.37, 1.64], np_around0=[[float]])

    def test_around1(self):
        self.run_test("def np_around1(x): from numpy import around ; return around(x, 1)", [0.37, 1.64], np_around1=[[float]])

    def test_around2(self):
        self.run_test("def np_around2(x): from numpy import  around ; return around(x, -1)", [0.37, 1.64], np_around2=[[float]])

    def test_around3(self):
        self.run_test("def np_around3(x): from numpy import around ; return around(x)", [.5, 1.5, 2.5, 3.5, 4.5], np_around3=[[float]])

    def test_around4(self):
        self.run_test("def np_around4(x): from numpy import around ; return around(x,1)", [1,2,3,11], np_around4=[[int]])

    def test_around5(self):
        self.run_test("def np_around5(x): from numpy import around ; return around(x,-1)", [1,2,3,11], np_around5=[[int]])

    def test_argsort0(self):
        self.run_test("def np_argsort0(x): from numpy import argsort ; return argsort(x)", numpy.array([3, 1, 2]), np_argsort0=[numpy.array([int])])

    def test_argsort1(self):
        self.run_test("def np_argsort1(x): from numpy import argsort ; return argsort(x)", numpy.array([[3, 1, 2], [1 , 2, 3]]), np_argsort1=[numpy.array([[int]])])

    def test_argmax0(self):
        self.run_test("def np_argmax0(a): from numpy import argmax ; return argmax(a)", numpy.arange(6).reshape(2,3), np_argmax0=[numpy.array([[int]])])

    def test_argmax1(self):
        self.run_test("def np_argmax1(a): from numpy import argmax ; return argmax(a+a)", numpy.arange(6).reshape(2,3), np_argmax1=[numpy.array([[int]])])

    def test_argmin0(self):
        self.run_test("def np_argmin0(a): from numpy import argmin ; return argmin(a)", numpy.arange(6).reshape(2,3), np_argmin0=[numpy.array([[int]])])

    def test_argmin1(self):
        self.run_test("def np_argmin1(a): from numpy import argmin ; return argmin(a)", [1,2,3], np_argmin1=[[int]])

    def test_append0(self):
        self.run_test("def np_append0(a): from numpy import append ; b = [[4, 5, 6], [7, 8, 9]] ; return append(a,b)", [1, 2, 3], np_append0=[[int]])

    def test_append1(self):
        self.run_test("def np_append1(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", [1, 2, 3], np_append1=[[int]])

    def test_append2(self):
        self.run_test("def np_append2(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", numpy.array([1, 2, 3]), np_append2=[numpy.array([int])])

    def test_angle0(self):
        self.run_test("def np_angle0(a): from numpy import angle ; return angle(a)", [1.0, 1.0j, 1+1j], np_angle0=[[complex]])

    def test_angle1(self):
        self.run_test("def np_angle1(a): from numpy import angle ; return angle(a)", numpy.array([1.0, 1.0j, 1+1j]), np_angle1=[numpy.array([complex])])

    def test_angle2(self):
        self.run_test("def np_angle2(a): from numpy import angle ; return angle(a,True)", 1 + 1j, np_angle2=[complex])

    def test_angle3(self):
        self.run_test("def np_angle3(a): from numpy import angle ; return angle(a,True)", 1, np_angle3=[int])

    def test_any0(self):
        self.run_test("def np_any0(a): from numpy import any ; return any(a)", numpy.array([[True, False], [True, True]]), np_any0=[numpy.array([[bool]])])

    def test_any1(self):
        self.run_test("def np_any1(a): from numpy import any ;  return any(a, 0)", numpy.array([[True, False], [False, False]]), np_any1=[numpy.array([[bool]])])

    def test_any2(self):
        self.run_test("def np_any2(a): from numpy import any ; return any(a)", [-1, 0, 5], np_any2=[[int]])

    def test_array1D_(self):
        self.run_test("def np_array1D_(a):\n from numpy import array\n return array(a)", [1,2,3], np_array1D_=[[int]])

    def test_array2D_(self):
        self.run_test("def np_array2D_(a):\n from numpy import array\n return array(a)", [[1,2],[3,4]], np_array2D_=[[[int]]])

    def test_array_typed(self):
        self.run_test("def np_array_typed(a):\n from numpy import array, int64\n return array(a, int64)", [1.,2.,3.], np_array_typed=[[float]])

    def test_zeros_(self):
        self.run_test("def np_zeros_(a): from numpy import zeros; return zeros(a)", (10, 5), np_zeros_=[(int, int)])

    def test_ones_(self):
        self.run_test("def np_ones_(a): from numpy import ones; return ones(a)", (10, 5), np_ones_=[(int, int)])

    def test_flat_zeros_(self):
        self.run_test("def np_flat_zeros_(a): from numpy import zeros; return zeros(a)", 10, np_flat_zeros_=[int])

    def test_flat_ones_(self):
        self.run_test("def np_flat_ones_(a): from numpy import ones; return ones(a)", 5, np_flat_ones_=[int])

    def test_acces1D_(self):
        self.run_test("def np_acces1D_(a): return a[1]", numpy.array([1,2,3]), np_acces1D_=[numpy.array([int])])

    def test_accesSimple_(self):
        self.run_test("def np_accesSimple_(a): return a[1]", numpy.array([[1,2],[3,4]]), np_accesSimple_=[numpy.array([[int]])])

    def test_accesMultiple_(self):
        self.run_test("def np_accesMultiple_(a): return a[1,0]", numpy.array([[1,2],[3,4]]), np_accesMultiple_=[numpy.array([[int]])])

    def test_accesMultipleND_(self):
        self.run_test("def np_accesMultipleND_(a): return a[1,0]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_accesMultipleND_=[numpy.array([[[int]]])])

    def test_accesMultipleNDSplit_(self):
        self.run_test("def np_accesMultipleNDSplit_(a): return a[1][0]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_accesMultipleNDSplit_=[numpy.array([[[int]]])])

    def test_shape_(self):
        self.run_test("def np_shape_(a): return a.shape", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_shape_=[numpy.array([[[int]]])])

    def test_input_array_(self):
        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", runas="import numpy; input_array_(numpy.array([[1,2],[3,4]]))", input_array_=[numpy.array([[int]])])

    def test_change_array1D_(self):
        self.run_test("def np_change_array1D_(a):\n a[0,0,0] = 36\n return a", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_change_array1D_=[numpy.array([[[int]]])])

    def test_change_arrayND_(self):
        self.run_test("def np_change_arrayND_(a):\n from numpy import array\n a[0,0] = array([99,99])\n return a", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_change_arrayND_=[numpy.array([[[int]]])])

    def test_ndim_(self):
        self.run_test("def np_ndim_(a): return a.ndim", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_ndim_=[numpy.array([[[int]]])])

    def test_stride_(self):
        self.run_test("def np_stride_(a): return a.strides", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_stride_=[numpy.array([[[int]]])])

    def test_size_(self):
        self.run_test("def np_size_(a): return a.size", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_size_=[numpy.array([[[int]]])])

    def test_itemsize_(self):
        self.run_test("def np_itemsize_(a): return a.itemsize", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_itemsize_=[numpy.array([[[int]]])])

    def test_nbytes_(self):
        self.run_test("def np_nbytes_(a): return a.nbytes", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_nbytes_=[numpy.array([[[int]]])])

    def test_flat_(self):
        self.run_test("def np_flat_(a): return [i for i in a.flat]", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_flat_=[numpy.array([[[int]]])])

    def test_str_(self):
        self.run_test("def np_str_(a): return str(a)", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_str_=[numpy.array([[[int]]])])

    def test_len_(self):
        self.run_test("def np_len_(a): return len(a)", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_len_=[numpy.array([[[int]]])])

    def test_empty_(self):
        self.run_test("def np_empty_(a):\n from numpy import empty\n a = empty(a)\n return a.strides, len(a)", (3, 2), np_empty_=[(int, int)])

    def test_arange(self):
        self.run_test("def np_arange_(a):\n from numpy import arange\n return arange(a)", 10, np_arange_=[int])

    def test_arange1(self):
        self.run_test("def np_arange1_(a):\n from numpy import arange\n return arange(a, 10)", 1, np_arange1_=[int])

    def test_arange2(self):
        self.run_test("def np_arange2_(a):\n from numpy import arange\n return arange(a, 10)", 0.5, np_arange2_=[float])

    def test_arange3(self):
        self.run_test("def np_arange3_(a):\n from numpy import arange\n return arange(a, 9.5)", 0.5, np_arange3_=[float])

    def test_arange4(self):
        self.run_test("def np_arange4_(a):\n from numpy import arange\n return arange(a, 9.3, 1)", 0.2, np_arange4_=[float])

    def test_arange5(self):
        self.run_test("def np_arange5_(a):\n from numpy import arange\n return arange(a, 2, 0.3)", 1, np_arange5_=[int])

    def test_arange6(self):
        self.run_test("def np_arange6_(a):\n from numpy import arange\n return arange(a, 3.3, 0.5)", 0.2, np_arange6_=[float])

    def test_arange7(self):
        self.run_test("def np_arange7_(a):\n from numpy import arange\n return arange(a, 4.5, -0.2)", 1, np_arange7_=[int])

    def test_arange8(self):
        self.run_test("def np_arange8_(a):\n from numpy import arange\n return arange(a, 1, -0.1)", 4.5, np_arange8_=[float])

    def test_arange9(self):
        self.run_test("def np_arange9_(a):\n from numpy import arange\n return arange(a, -12, -3.2)", 4.5, np_arange9_=[float])

    def test_arange10(self):
        self.run_test("def np_arange10_(a):\n from numpy import arange\n return arange(a, -5.5, -0.1)", -5, np_arange10_=[int])

    def test_arange11(self):
        self.run_test("def np_arange11_(a):\n from numpy import arange, uint8\n return arange(a, 255, 1, uint8)", 0, np_arange11_=[int])

    def test_arange12(self):
        self.run_test("def np_arange12_(a):\n from numpy import arange, float32\n return arange(a, 25, 1., float32)", 0, np_arange12_=[int])

    def test_linspace(self):
        self.run_test("def np_linspace_(a):\n from numpy import linspace\n return linspace(a,4,32)", 1, np_linspace_=[int])

    def test_linspace1(self):
        self.run_test("def np_linspace1_(a):\n from numpy import linspace\n return linspace(a,32.5,2)", 0.4, np_linspace1_=[float])

    def test_linspace2(self):
        self.run_test("def np_linspace2_(a):\n from numpy import linspace\n return linspace(a,32.5,32, False)", 0.4, np_linspace2_=[float])

    def test_linspace3(self):
        self.run_test("def np_linspace3_(a):\n from numpy import linspace\n return linspace(1,a)", 4, np_linspace3_=[int])

    def test_sin(self):
        self.run_test("def np_sin_(a):\n from numpy import sin\n return sin(a)", numpy.linspace(0,6), np_sin_=[numpy.array([float])])

    def test_pi(self):
        self.run_test("def np_pi_():\n from numpy import pi\n return pi", np_pi_=[])

    def test_e(self):
        self.run_test("def np_e_():\n from numpy import e\n return e", np_e_=[])

    def test_ones_like_(self):
        self.run_test("def np_ones_like_(a):\n from numpy import ones_like, array\n return ones_like(array(a))", [[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)], np_ones_like_=[[[int]]])

    def test_zeros_like_(self):
        self.run_test("def np_zeros_like_(a):\n from numpy import zeros_like, array\n return zeros_like(array(a))", [[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)], np_zeros_like_=[[[int]]])

    def test_empty_like_(self):
        self.run_test("def np_empty_like_(a):\n from numpy import empty_like, array\n return empty_like(array(a)).shape", [[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)], np_empty_like_=[[[int]]])

    def test_reshape0(self):
        self.run_test("def np_reshape0(a): return a.reshape((2,5))", numpy.arange(10), np_reshape0=[numpy.array([int])], check_refcount=True)

    def test_reshape1(self):
        self.run_test("def np_reshape1(a): return a.reshape((2,-1))", numpy.arange(10), np_reshape1=[numpy.array([int])], check_refcount=True)

    def test_duplicate(self):
        self.run_test("def np_duplicate(a): return a, a", numpy.arange(10), np_duplicate=[numpy.array([int])], check_refcount=True)

    def test_broadcast(self):
        self.run_test("def np_broadcast(): import numpy; a = numpy.arange(3); return a, a", np_broadcast=[], check_refcount=True)

    def test_broadcast_dup(self):
        self.run_test("def np_broadcast_dup(): import numpy; a = numpy.arange(10); return a, a.reshape((2,5))", np_broadcast_dup=[], check_refcount=True)

    def test_reshape_expr(self):
        self.run_test("def np_reshape_expr(a): return (a + a).reshape((2,5))", numpy.ones(10), np_reshape_expr=[numpy.array([float])])

    def test_cumsum_(self):
        self.run_test("def np_cumsum_(a): return a.cumsum()", numpy.arange(10), np_cumsum_=[numpy.array([int])])

    def test_cumsum2_(self):
        self.run_test("def np_cumsum2_(a): return a.cumsum()", numpy.arange(10).reshape(2,5), np_cumsum2_=[numpy.array([[int]])])

    def test_cumsum3_(self):
        self.run_test("def np_cumsum3_(a): return a.cumsum(1)", numpy.arange(10).reshape(2,5), np_cumsum3_=[numpy.array([[int]])])

    def test_cumsum4_(self):
        self.run_test("def np_cumsum4_(a): return a.cumsum(0)", numpy.arange(10).reshape(2,5), np_cumsum4_=[numpy.array([[int]])])

    def test_cumsum5_(self):
        self.run_test("def np_cumsum5_(a): return a.cumsum(0)", numpy.arange(10), np_cumsum5_=[numpy.array([int])])

    def test_sum_(self):
        self.run_test("def np_sum_(a): return a.sum()", numpy.arange(10), np_sum_=[numpy.array([int])])

    def test_sum_bool(self):
        self.run_test("def np_sum_bool(a): return (a > 2).sum()", numpy.arange(10), np_sum_bool=[numpy.array([int])])

    def test_sum_bool2(self):
        self.run_test("def np_sum_bool2(a): return a.sum()", numpy.ones(10,dtype=bool).reshape(2,5), np_sum_bool2=[numpy.array([[bool]])])

    def test_sum_expr(self):
        self.run_test("def np_sum_expr(a):\n from numpy import ones\n return (a + ones(10)).sum()", numpy.arange(10), np_sum_expr=[numpy.array([int])])

    def test_sum2_(self):
        self.run_test("def np_sum2_(a): return a.sum()", numpy.arange(10).reshape(2,5), np_sum2_=[numpy.array([[int]])])

    def test_sum3_(self):
        self.run_test("def np_sum3_(a): return a.sum(1)", numpy.arange(10).reshape(2,5), np_sum3_=[numpy.array([[int]])])

    def test_sum4_(self):
        self.run_test("def np_sum4_(a): return a.sum(0)", numpy.arange(10).reshape(2,5), np_sum4_=[numpy.array([[int]])])

    def test_sum5_(self):
        self.run_test("def np_sum5_(a): return a.sum(0)", numpy.arange(10), np_sum5_=[numpy.array([int])])

    def test_sum6_(self):
        self.run_test("def np_sum6_(a): return a.sum(0)", numpy.arange(12).reshape(2,3,2), np_sum6_=[numpy.array([[[int]]])])

    def test_sum7_(self):
        self.run_test("def np_sum7_(a): return a.sum(1)", numpy.arange(12).reshape(2,3,2), np_sum7_=[numpy.array([[[int]]])])

    def test_sum8_(self):
        self.run_test("def np_sum8_(a): return a.sum(2)", numpy.arange(12).reshape(2,3,2), np_sum8_=[numpy.array([[[int]]])])

    def test_sum9_(self):
        self.run_test("def np_sum9_(a): import numpy as np ; return np.sum(a*a,0)", numpy.arange(12).reshape(2,3,2), np_sum9_=[numpy.array([[[int]]])])

    def test_sum10_(self):
        self.run_test("def np_sum10_(a): import numpy as np ; return np.sum(a-a,1)", numpy.arange(12).reshape(2,3,2), np_sum10_=[numpy.array([[[int]]])])

    def test_sum11_(self):
        self.run_test("def np_sum11_(a): import numpy as np ; return np.sum(a+a,2)", numpy.arange(12).reshape(2,3,2), np_sum11_=[numpy.array([[[int]]])])

    def test_prod_(self):
        self.run_test("def np_prod_(a): return a.prod()", numpy.arange(10), np_prod_=[numpy.array([int])])

    def test_prod_bool(self):
        self.run_test("def np_prod_bool(a): return (a > 2).prod()", numpy.arange(10), np_prod_bool=[numpy.array([int])])

    def test_prod_bool2(self):
        self.run_test("def np_prod_bool2(a): return a.prod()", numpy.ones(10,dtype=bool).reshape(2,5), np_prod_bool2=[numpy.array([[bool]])])

    def test_prod_expr(self):
        self.run_test("def np_prod_expr(a):\n from numpy import ones\n return (a + ones(10)).prod()", numpy.arange(10), np_prod_expr=[numpy.array([int])])

    def test_prod2_(self):
        self.run_test("def np_prod2_(a): return a.prod()", numpy.arange(10).reshape(2,5), np_prod2_=[numpy.array([[int]])])

    def test_prod3_(self):
        self.run_test("def np_prod3_(a): return a.prod(1)", numpy.arange(10).reshape(2,5), np_prod3_=[numpy.array([[int]])])

    def test_prod4_(self):
        self.run_test("def np_prod4_(a): return a.prod(0)", numpy.arange(10).reshape(2,5), np_prod4_=[numpy.array([[int]])])

    def test_prod5_(self):
        self.run_test("def np_prod5_(a): return a.prod(0)", numpy.arange(10), np_prod5_=[numpy.array([int])])

    def test_prod6_(self):
        self.run_test("def np_prod6_(a): return a.prod(0)", numpy.arange(12).reshape(2,3,2), np_prod6_=[numpy.array([[[int]]])])

    def test_prod7_(self):
        self.run_test("def np_prod7_(a): return a.prod(1)", numpy.arange(12).reshape(2,3,2), np_prod7_=[numpy.array([[[int]]])])

    def test_prod8_(self):
        self.run_test("def np_prod8_(a): return a.prod(2)", numpy.arange(12).reshape(2,3,2), np_prod8_=[numpy.array([[[int]]])])

    def test_prod9_(self):
        self.run_test("def np_prod9_(a): import numpy as np ; return np.prod(a*a,0)", numpy.arange(12).reshape(2,3,2), np_prod9_=[numpy.array([[[int]]])])

    def test_prod10_(self):
        self.run_test("def np_prod10_(a): import numpy as np ; return np.prod(a-a,1)", numpy.arange(12).reshape(2,3,2), np_prod10_=[numpy.array([[[int]]])])

    def test_prod11_(self):
        self.run_test("def np_prod11_(a): import numpy as np ; return np.prod(a+a,2)", numpy.arange(12).reshape(2,3,2), np_prod11_=[numpy.array([[[int]]])])

    def test_prod_(self):
        self.run_test("def np_prod_(a): return a.prod()", numpy.arange(10), np_prod_=[numpy.array([int])])

    def test_prod_bool(self):
        self.run_test("def np_prod_bool(a): return (a > 2).prod()", numpy.arange(10), np_prod_bool=[numpy.array([int])])

    def test_prod_bool2(self):
        self.run_test("def np_prod_bool2(a): return a.prod()", numpy.ones(10,dtype=bool).reshape(2,5), np_prod_bool2=[numpy.array([[bool]])])

    def test_prod_expr(self):
        self.run_test("def np_prod_expr(a):\n from numpy import ones\n return (a + ones(10)).prod()", numpy.arange(10), np_prod_expr=[numpy.array([int])])

    def test_prod2_(self):
        self.run_test("def np_prod2_(a): return a.prod()", numpy.arange(10).reshape(2,5), np_prod2_=[numpy.array([[int]])])

    def test_prod3_(self):
        self.run_test("def np_prod3_(a): return a.prod(1)", numpy.arange(10).reshape(2,5), np_prod3_=[numpy.array([[int]])])

    def test_prod4_(self):
        self.run_test("def np_prod4_(a): return a.prod(0)", numpy.arange(10).reshape(2,5), np_prod4_=[numpy.array([[int]])])

    def test_prod5_(self):
        self.run_test("def np_prod5_(a): return a.prod(0)", numpy.arange(10), np_prod5_=[numpy.array([int])])

    def test_prod6_(self):
        self.run_test("def np_prod6_(a): return a.prod(0)", numpy.arange(12).reshape(2,3,2), np_prod6_=[numpy.array([[[int]]])])

    def test_prod7_(self):
        self.run_test("def np_prod7_(a): return a.prod(1)", numpy.arange(12).reshape(2,3,2), np_prod7_=[numpy.array([[[int]]])])

    def test_prod8_(self):
        self.run_test("def np_prod8_(a): return a.prod(2)", numpy.arange(12).reshape(2,3,2), np_prod8_=[numpy.array([[[int]]])])

    def test_prod9_(self):
        self.run_test("def np_prod9_(a): import numpy as np ; return np.prod(a*a,0)", numpy.arange(12).reshape(2,3,2), np_prod9_=[numpy.array([[[int]]])])

    def test_prod10_(self):
        self.run_test("def np_prod10_(a): import numpy as np ; return np.prod(a-a,1)", numpy.arange(12).reshape(2,3,2), np_prod10_=[numpy.array([[[int]]])])

    def test_prod11_(self):
        self.run_test("def np_prod11_(a): import numpy as np ; return np.prod(a+a,2)", numpy.arange(12).reshape(2,3,2), np_prod11_=[numpy.array([[[int]]])])

    def test_amin_amax(self):
        self.run_test("def np_amin_amax(a):\n from numpy import amin,amax\n return amin(a), amax(a)",numpy.arange(10),  np_amin_amax=[numpy.array([int])])

    def test_min_(self):
        self.run_test("def np_min_(a): return a.min()", numpy.arange(10), np_min_=[numpy.array([int])])

    def test_min1_(self):
        self.run_test("def np_min1_(a): return (a+a).min()", numpy.arange(10), np_min1_=[numpy.array([int])])

    def test_min2_(self):
        self.run_test("def np_min2_(a): return a.min()", numpy.arange(10).reshape(2,5), np_min2_=[numpy.array([[int]])])

    def test_min3_(self):
        self.run_test("def np_min3_(a): return a.min(1)", numpy.arange(10).reshape(2,5), np_min3_=[numpy.array([[int]])])

    def test_min4_(self):
        self.run_test("def np_min4_(a): return a.min(0)", numpy.arange(10).reshape(2,5), np_min4_=[numpy.array([[int]])])

    def test_min5_(self):
        self.run_test("def np_min5_(a): return a.min(0)", numpy.arange(10), np_min5_=[numpy.array([int])])

    def test_min6_(self):
        self.run_test("def np_min6_(a): return a.min(1)", numpy.arange(30).reshape(2,5,3), np_min6_=[numpy.array([[[int]]])])

    def test_min7_(self):
        self.run_test("def np_min7_(a): return (a+a).min(1)", numpy.arange(30).reshape(2,5,3), np_min7_=[numpy.array([[[int]]])])

    def test_max_(self):
        self.run_test("def np_max_(a): return a.max()", numpy.arange(10), np_max_=[numpy.array([int])])

    def test_max1_(self):
        self.run_test("def np_max1_(a): return (a+a).max()", numpy.arange(10), np_max1_=[numpy.array([int])])

    def test_max2_(self):
        self.run_test("def np_max2_(a): return a.max()", numpy.arange(10).reshape(2,5), np_max2_=[numpy.array([[int]])])

    def test_max3_(self):
        self.run_test("def np_max3_(a): return a.max(1)", numpy.arange(10).reshape(2,5), np_max3_=[numpy.array([[int]])])

    def test_max4_(self):
        self.run_test("def np_max4_(a): return a.max(0)", numpy.arange(10).reshape(2,5), np_max4_=[numpy.array([[int]])])

    def test_max5_(self):
        self.run_test("def np_max5_(a): return a.max(0)", numpy.arange(10), np_max5_=[numpy.array([int])])

    def test_max6_(self):
        self.run_test("def np_max6_(a): return a.max(1)", numpy.arange(30).reshape(2,5,3), np_max6_=[numpy.array([[[int]]])])

    def test_max7_(self):
        self.run_test("def np_max7_(a): return (a+a).max(1)", numpy.arange(30).reshape(2,5,3), np_max7_=[numpy.array([[[int]]])])

    def test_all_(self):
        self.run_test("def np_all_(a): return a.all()", numpy.arange(10), np_all_=[numpy.array([int])])

    def test_all2_(self):
        self.run_test("def np_all2_(a): return a.all()", numpy.ones(10).reshape(2,5), np_all2_=[numpy.array([[float]])])

    def test_all3_(self):
        self.run_test("def np_all3_(a): return a.all(1)", numpy.arange(10).reshape(2,5), np_all3_=[numpy.array([[int]])])

    def test_all4_(self):
        self.run_test("def np_all4_(a): return a.all(0)", numpy.ones(10).reshape(2,5), np_all4_=[numpy.array([[float]])])

    def test_all5_(self):
        self.run_test("def np_all5_(a): return a.all(0)", numpy.arange(10), np_all5_=[numpy.array([int])])

    def test_transpose_(self):
        self.run_test("def np_transpose_(a): return a.transpose()", numpy.arange(24).reshape(2,3,4), np_transpose_=[numpy.array([[[int]]])])

    def test_transpose_expr(self):
        self.run_test("def np_transpose_expr(a): return (a + a).transpose()", numpy.ones(24).reshape(2,3,4), np_transpose_expr=[numpy.array([[[float]]])])

    def test_transpose2_(self):
        self.run_test("def np_transpose2_(a): return a.transpose((2,0,1))", numpy.arange(24).reshape(2,3,4), np_transpose2_=[numpy.array([[[int]]])])

    def test_add0(self):
        self.run_test("def np_add0(a, b): return a + b", numpy.ones(10), numpy.ones(10), np_add0=[numpy.array([float]), numpy.array([float])])

    def test_add1(self):
        self.run_test("def np_add1(a, b): return a + b + a", numpy.ones(10), numpy.ones(10), np_add1=[numpy.array([float]), numpy.array([float])])

    def test_add2(self):
        self.run_test("def np_add2(a, b): return a + b + 1", numpy.ones(10), numpy.ones(10), np_add2=[numpy.array([float]), numpy.array([float])])

    def test_add3(self):
        self.run_test("def np_add3(a, b): return 1. + a + b + 1.", numpy.ones(10), numpy.ones(10), np_add3=[numpy.array([float]), numpy.array([float])])

    def test_add4(self):
        self.run_test("def np_add4(a, b): return ( a + b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_add4=[numpy.array([float]), numpy.array([float])])

    def test_add5(self):
        self.run_test("def np_add5(a, b): return (-a) + (-b)", numpy.ones(10), numpy.ones(10), np_add5=[numpy.array([float]), numpy.array([float])])

    def test_sub0(self):
        self.run_test("def np_sub0(a, b): return a - b", numpy.ones(10), numpy.ones(10), np_sub0=[numpy.array([float]), numpy.array([float])])

    def test_sub1(self):
        self.run_test("def np_sub1(a, b): return a - b - a", numpy.ones(10), numpy.ones(10), np_sub1=[numpy.array([float]), numpy.array([float])])

    def test_sub2(self):
        self.run_test("def np_sub2(a, b): return a - b - 1", numpy.ones(10), numpy.ones(10), np_sub2=[numpy.array([float]), numpy.array([float])])

    def test_sub3(self):
        self.run_test("def np_sub3(a, b): return 1. - a - b - 1.", numpy.ones(10), numpy.ones(10), np_sub3=[numpy.array([float]), numpy.array([float])])

    def test_sub4(self):
        self.run_test("def np_sub4(a, b): return ( a - b ) - ( a - b )", numpy.ones(10), numpy.ones(10), np_sub4=[numpy.array([float]), numpy.array([float])])

    def test_addsub0(self):
        self.run_test("def np_addsub0(a, b): return a - b + a", numpy.ones(10), numpy.ones(10), np_addsub0=[numpy.array([float]), numpy.array([float])])

    def test_addsub1(self):
        self.run_test("def np_addsub1(a, b): return a + b - a", numpy.ones(10), numpy.ones(10), np_addsub1=[numpy.array([float]), numpy.array([float])])

    def test_addsub2(self):
        self.run_test("def np_addsub2(a, b): return a + b - 1", numpy.ones(10), numpy.ones(10), np_addsub2=[numpy.array([float]), numpy.array([float])])

    def test_addsub3(self):
        self.run_test("def np_addsub3(a, b): return 1. + a - b + 1.", numpy.ones(10), numpy.ones(10), np_addsub3=[numpy.array([float]), numpy.array([float])])

    def test_addsub4(self):
        self.run_test("def np_addsub4(a, b): return ( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addsub4=[numpy.array([float]), numpy.array([float])])

    def test_addcossub0(self):
        self.run_test("def np_addcossub0(a, b): from numpy import cos ; return a - b + cos(a)", numpy.ones(10), numpy.ones(10), np_addcossub0=[numpy.array([float]), numpy.array([float])])

    def test_addcossub1(self):
        self.run_test("def np_addcossub1(a, b): from numpy import cos ; return a + cos(b - a)", numpy.ones(10), numpy.ones(10), np_addcossub1=[numpy.array([float]), numpy.array([float])])

    def test_addcossub2(self):
        self.run_test("def np_addcossub2(a, b): from numpy import cos ; return a + cos(b - 1)", numpy.ones(10), numpy.ones(10), np_addcossub2=[numpy.array([float]), numpy.array([float])])

    def test_addcossub3(self):
        self.run_test("def np_addcossub3(a, b): from numpy import cos ; return cos(1. + a - b + cos(1.))", numpy.ones(10), numpy.ones(10), np_addcossub3=[numpy.array([float]), numpy.array([float])])

    def test_addcossub4(self):
        self.run_test("def np_addcossub4(a, b): from numpy import cos ; return cos( a - b ) + ( a + b )", numpy.ones(10), numpy.ones(10), np_addcossub4=[numpy.array([float]), numpy.array([float])])

    def test_sin0(self):
        self.run_test("def np_sin0(a, b): from numpy import sin ; return sin(a) + b", numpy.ones(10), numpy.ones(10), np_sin0=[numpy.array([float]), numpy.array([float])])

    def test_tan0(self):
        self.run_test("def np_tan0(a, b): from numpy import tan ; return tan(a - b)", numpy.ones(10), numpy.ones(10), np_tan0=[numpy.array([float]), numpy.array([float])])

    def test_arccos0(self):
        self.run_test("def np_arccos0(a, b): from numpy import arccos ; return arccos(a - b) + 1", numpy.ones(10), numpy.ones(10), np_arccos0=[numpy.array([float]), numpy.array([float])])

    def test_arcsin0(self):
        self.run_test("def np_arcsin0(a, b): from numpy import arcsin ; return arcsin(a + b - a + -b) + 1.", numpy.ones(10), numpy.ones(10), np_arcsin0=[numpy.array([float]), numpy.array([float])])

    def test_arctan0(self):
        self.run_test("def np_arctan0(a, b): from numpy import arctan ; return arctan(a -0.5) + a", numpy.ones(10), numpy.ones(10), np_arctan0=[numpy.array([float]), numpy.array([float])])

    def test_arctan20(self):
        self.run_test("def np_arctan20(a, b): from numpy import arctan2 ; return b - arctan2(a , b)", numpy.ones(10), numpy.ones(10), np_arctan20=[numpy.array([float]), numpy.array([float])])

    def test_cos1(self):
        self.run_test("def np_cos1(a): from numpy import cos; return cos(a)", 5, np_cos1=[int])

    def test_sin1(self):
        self.run_test("def np_sin1(a): from numpy import sin; return sin(a)", 0.5, np_sin1=[float])

    def test_tan1(self):
        self.run_test("def np_tan1(a): from numpy import tan; return tan(a)", 0.5, np_tan1=[float])

    def test_arccos1(self):
        self.run_test("def np_arccos1(a): from numpy import arccos ; return arccos(a)", 1, np_arccos1=[int])

    def test_arcsin1(self):
        self.run_test("def np_arcsin1(a): from numpy import arcsin ; return arcsin(a)", 1, np_arcsin1=[int])

    def test_arctan1(self):
        self.run_test("def np_arctan1(a): from numpy import arctan ; return arctan(a)", 0.5, np_arctan1=[float])

    def test_arctan21(self):
        self.run_test("def np_arctan21(a): from numpy import arctan2 ; b = .5 ; return arctan2(a , b)", 1., np_arctan21=[float])

    def test_sliced0(self):
        self.run_test("def np_sliced0(a): return a[2:12]", numpy.ones(20), np_sliced0=[numpy.array([float])])

    def test_sliced1(self):
        self.run_test("def np_sliced1(a): return a[2:12:3]", numpy.ones(20), np_sliced1=[numpy.array([float])])

    def test_sliced2(self):
        self.run_test("def np_sliced2(a): return -a[2:12:3]", numpy.ones(20), np_sliced2=[numpy.array([float])])

    def test_sliced3(self):
        self.run_test("def np_sliced3(a): return a[1:11:3] -a[2:12:3]", numpy.ones(20), np_sliced3=[numpy.array([float])])

    def test_sliced4(self):
        self.run_test("def np_sliced4(a): return a[1:11] -a[2:12]", numpy.ones(20), np_sliced4=[numpy.array([float])])

    def test_sliced5(self):
        self.run_test("def np_sliced5(a): return (-a[1:11]) + 3*a[2:12]", numpy.ones(20), np_sliced5=[numpy.array([float])])

    def test_sliced6(self):
        self.run_test("def np_sliced6(a): return a[3:4]", numpy.arange(12).reshape(6,2), np_sliced6=[numpy.array([[int]])])

    def test_sliced7(self):
        self.run_test("def np_sliced7(a): a[3:4] = 1 ; return a", numpy.arange(12).reshape(6,2), np_sliced7=[numpy.array([[int]])])

    def test_sliced8(self):
        self.run_test("def np_sliced8(a): a[1:2] = 1 ; return a", numpy.arange(12).reshape(3,2,2), np_sliced8=[numpy.array([[[int]]])])

    def test_sliced9(self):
        self.run_test("def np_sliced9(a): from numpy import arange ; a[1:2] = arange(4).reshape((1,2,2)) ; return a", numpy.arange(12).reshape(3,2,2), np_sliced9=[numpy.array([[[int]]])])

    def test_sliced10(self):
        self.run_test("def np_sliced10(a): from numpy import arange ; a[1:-1:2] = arange(4).reshape((1,2,2)) ; return a", numpy.arange(12).reshape(3,2,2), np_sliced10=[numpy.array([[[int]]])])

    def test_sliced11(self):
        self.run_test("def np_sliced11(a): return a[1::-2]", numpy.arange(12).reshape(3,2,2), np_sliced11=[numpy.array([[[int]]])])

    def test_sliced12(self):
        self.run_test("def np_sliced12(a): return a[1::-2]", numpy.arange(12), np_sliced12=[numpy.array([int])])

    def test_sliced13(self):
        self.run_test("def np_sliced13(a): return a[3::-3]", numpy.arange(11), np_sliced13=[numpy.array([int])])

    def test_alen0(self):
        self.run_test("def np_alen0(a): from numpy import alen ; return alen(a)", numpy.ones((5,6)), np_alen0=[numpy.array([[float]])])

    def test_alen1(self):
        self.run_test("def np_alen1(a): from numpy import alen ; return alen(-a)", numpy.ones((5,6)), np_alen1=[numpy.array([[float]])])

    def test_allclose0(self):
        self.run_test("def np_allclose0(a): from numpy import allclose ; return allclose([1e10,1e-7], a)", [1.00001e10,1e-8], np_allclose0=[[float]])

    def test_allclose1(self):
        self.run_test("def np_allclose1(a): from numpy import allclose; return allclose([1e10,1e-8], +a)", numpy.array([1.00001e10,1e-9]), np_allclose1=[numpy.array([float])])

    def test_allclose2(self):
        self.run_test("def np_allclose2(a): from numpy import array, allclose; return allclose(array([1e10,1e-8]), a)", numpy.array([1.00001e10,1e-9]), np_allclose2=[numpy.array([float])])

    def test_allclose3(self):
        self.run_test("def np_allclose3(a): from numpy import allclose; return allclose(a, a)", [1.0, numpy.nan], np_allclose3=[[float]])

    def test_alltrue0(self):
        self.run_test("def np_alltrue0(b): from numpy import alltrue ; return alltrue(b)", numpy.array([True, False, True, True]), np_alltrue0=[numpy.array([bool])])

    def test_alltrue1(self):
        self.run_test("def np_alltrue1(a): from numpy import alltrue ; return alltrue(a >= 5)", numpy.array([1, 5, 2, 7]), np_alltrue1=[numpy.array([int])])

    def test_negative_mod(self):
        self.run_test("def np_negative_mod(a): return a % 5", numpy.array([-1, -5, -2, 7]), np_negative_mod=[numpy.array([int])])

    def test_count_nonzero0(self):
        self.run_test("def np_count_nonzero(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([[-1, -5, -2, 7], [9, 3, 0, -0]]), np_count_nonzero=[numpy.array([[int]])])

    def test_count_nonzero1(self):
        self.run_test("def np_count_nonzero(a): from numpy import count_nonzero; return count_nonzero(a)",
                       numpy.array([-1, 5, -2, 0]), np_count_nonzero=[numpy.array([int])])

    def test_count_nonzero2(self):
        self.run_test("def np_count_nonzero(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([-1., 0., -2., -1e-20]), np_count_nonzero=[numpy.array([float])])

    def test_count_nonzero3(self):
        self.run_test("def np_count_nonzero(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([[0, 2, 0., 4 + 1j], [0.+0.j, 0.+4j, 1.+0j, 1j]]), np_count_nonzero=[numpy.array([[complex]])])

    def test_count_nonzero4(self):
        self.run_test("def np_count_nonzero(a): from numpy import count_nonzero; return count_nonzero(a)",
                      numpy.array([[True, False], [False, False]]), np_count_nonzero=[numpy.array([[bool]])])

    def test_count_nonzero5(self):
        self.run_test("def np_count_nonzero(a): from numpy import count_nonzero; return count_nonzero(a*2)",
                      numpy.array([[-1, -5, -2, 7], [9, 3, 0, -0]]), np_count_nonzero=[numpy.array([[int]])])

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
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from numpy import {0} ; return {0}(a)', numpy.ones(10, numpy.int32), np_{0}=[numpy.array([numpy.int32])])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from numpy import {0} ; return {0}(a)', 1, np_{0}_scalar=[int])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from numpy import {0} ; return {0}(a)', numpy.ones((5,2), numpy.int32), np_{0}_matrix=[numpy.array([numpy.array([numpy.int32])])])".format(f)))
    else:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from numpy import {0} ; return {0}(a)', numpy.ones(10), np_{0}=[numpy.array([float])])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from numpy import {0} ; return {0}(a+0.5)', 0.5, np_{0}_scalar=[float])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from numpy import {0} ; return {0}(a)', numpy.ones((2,5)), np_{0}_matrix=[numpy.array([numpy.array([float])])])".format(f)))

for f in binary_ufunc:
    if 'bitwise_' in f or 'ldexp' in f or '_shift' in f :
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from numpy import {0} ; return {0}(a,a)', numpy.ones(10, numpy.int32), np_{0}=[numpy.array([numpy.int32])])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from numpy import {0} ; return {0}(a, a-1)', 1, np_{0}_scalar=[int])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from numpy import {0} ; return {0}(a,a)', numpy.ones((2,5), numpy.int32), np_{0}_matrix=[numpy.array([numpy.array([numpy.int32])])])".format(f)))
    else:
        setattr(TestNumpy, 'test_' + f, eval("lambda self: self.run_test('def np_{0}(a): from numpy import {0} ; return {0}(a,a)', numpy.ones(10), np_{0}=[numpy.array([float])])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_scalar', eval("lambda self: self.run_test('def np_{0}_scalar(a): from numpy import {0} ; return {0}(a+0.5, a+0.5)', 0.5, np_{0}_scalar=[float])".format(f)))
        setattr(TestNumpy, 'test_' + f + '_matrix', eval("lambda self: self.run_test('def np_{0}_matrix(a): from numpy import {0} ; return {0}(a,a)', numpy.ones((2,5)) - 0.2 , np_{0}_matrix=[numpy.array([numpy.array([float])])])".format(f)))

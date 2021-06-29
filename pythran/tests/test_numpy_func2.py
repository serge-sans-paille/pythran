import unittest
from pythran.tests import TestEnv
import numpy

from pythran.typing import NDArray, List, Tuple


@TestEnv.module
class TestNumpyFunc2(TestEnv):

    def test_nonzero0(self):
        self.run_test("def np_nonzero0(x): return x.nonzero()", numpy.arange(6), np_nonzero0=[NDArray[int,:]])

    def test_nonzero1(self):
        self.run_test("def np_nonzero1(x): from numpy import nonzero ; return nonzero(x>8)", numpy.arange(6), np_nonzero1=[NDArray[int,:]])

    def test_nonzero2(self):
        self.run_test("def np_nonzero2(x): from numpy import nonzero ; return nonzero(x>0)", numpy.arange(6).reshape(2,3), np_nonzero2=[NDArray[int,:,:]])

    def test_diagflat3(self):
        self.run_test("def np_diagflat3(a): from numpy import diagflat ; return diagflat(a)", numpy.arange(2), np_diagflat3=[NDArray[int,:]])

    def test_diagflat4(self):
        self.run_test("def np_diagflat4(a): from numpy import diagflat ; return diagflat(a,1)", numpy.arange(3), np_diagflat4=[NDArray[int,:]])

    def test_diagflat5(self):
        self.run_test("def np_diagflat5(a): from numpy import diagflat ; return diagflat(a,-2)", numpy.arange(4), np_diagflat5=[NDArray[int,:]])

    def test_diagonal0(self):
        self.run_test("def np_diagonal0(a): return a.diagonal()", numpy.arange(10).reshape(2,5), np_diagonal0=[NDArray[int,:,:]])

    def test_diagonal1(self):
        self.run_test("def np_diagonal1(a): from numpy import diagonal ; return diagonal(a,1)", numpy.arange(9).reshape(3,3), np_diagonal1=[NDArray[int,:,:]])

    def test_diagonal2(self):
        self.run_test("def np_diagonal2(a): from numpy import diagonal ; return diagonal(a,-2)", numpy.arange(9).reshape(3,3), np_diagonal2=[NDArray[int,:,:]])

    def test_diag0(self):
        self.run_test("def np_diag0(a): from numpy import diag ; return diag(a)", numpy.arange(10).reshape(2,5), np_diag0=[NDArray[int,:,:]])

    def test_diag1(self):
        self.run_test("def np_diag1(a): from numpy import diag ; return diag(a,1)", numpy.arange(9).reshape(3,3), np_diag1=[NDArray[int,:,:]])

    def test_diag2(self):
        self.run_test("def np_diag2(a): from numpy import diag ; return diag(a,-2)", numpy.arange(9).reshape(3,3), np_diag2=[NDArray[int,:,:]])

    def test_diag2b(self):
        self.run_test("def np_diag2b(a): from numpy import diag ; return diag(a,-2)", numpy.arange(12).reshape(4,3), np_diag2b=[NDArray[int,:,:]])

    def test_diag3(self):
        self.run_test("def np_diag3(a): from numpy import diag ; return diag(a)", numpy.arange(2), np_diag3=[NDArray[int,:]])

    def test_diag4(self):
        self.run_test("def np_diag4(a): from numpy import diag ; return diag(a,1)", numpy.arange(3), np_diag4=[NDArray[int,:]])

    def test_diag5(self):
        self.run_test("def np_diag5(a): from numpy import diag; return diag(a,-2)", numpy.arange(4), np_diag5=[NDArray[int,:]])

    def test_delete0(self):
        self.run_test("def np_delete0(a): from numpy import delete ; return delete(a, 1)", numpy.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]), np_delete0=[NDArray[int,:,:]])

    def test_delete1(self):
        self.run_test("def np_delete1(a): from numpy import delete ; return delete(a, [1,3,5])", numpy.array([[1,2,3,4], [5,6,7,8], [9,10,11,12]]), np_delete1=[NDArray[int,:,:]])

    def test_where0(self):
        self.run_test("""def np_where0(a):
    from numpy import arange, where
    b = arange(5, 17).reshape((3,4))
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(c , a, b)""", numpy.arange(12).reshape(3,4), np_where0=[NDArray[int,:,:]])

    def test_where1(self):
        self.run_test("""def np_where1(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, c)""", numpy.arange(12).reshape(3,4), np_where1=[NDArray[int,:,:]])

    def test_where2(self):
        self.run_test("""def np_where2(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, c)""", numpy.arange(12).reshape(3,4), np_where2=[NDArray[int,:,:]])

    def test_where3(self):
        self.run_test("""def np_where3(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(True , a, 5)""", numpy.arange(12).reshape(3,4), np_where3=[NDArray[int,:,:]])

    def test_where4(self):
        self.run_test("""def np_where4(a):
    from numpy import arange, where
    c = [[0, 1, 1, 1], [0, 0, 1, 1], [1, 0, 0, 0]]
    return where(False , a, 6)""", numpy.arange(12).reshape(3,4), np_where4=[NDArray[int,:,:]])

    def test_where5(self):
        self.run_test("""def np_where5(a):
    from numpy import arange, where
    b = arange(5, 17).reshape((3,4))
    return where(a>5 , a, b)""", numpy.arange(12).reshape(3,4), np_where5=[NDArray[int,:,:]])

    def test_where6(self):
        self.run_test("""def np_where6(a):
    from numpy import arange, where
    return where(a>5 , 1, 2)""", numpy.arange(12).reshape(3,4), np_where6=[NDArray[int,:,:]])

    def test_where7(self):
        self.run_test("""def np_where7(a):
    from numpy import arange, where
    return where(a>5)""", numpy.arange(12).reshape(3,4), np_where7=[NDArray[int,:,:]])

    def test_cumprod_(self):
        self.run_test("def np_cumprod_(a):\n return a.cumprod()", numpy.arange(10), np_cumprod_=[NDArray[int,:]])

    def test_cumprod2_(self):
        self.run_test("def np_cumprod2_(a):\n from numpy import cumprod\n return a.cumprod()", numpy.arange(10).reshape(2,5), np_cumprod2_=[NDArray[int,:,:]])

    def test_cumprod3_(self):
        self.run_test("def np_cumprod3_(a):\n from numpy import cumprod\n return a.cumprod(1)", numpy.arange(10).reshape(2,5), np_cumprod3_=[NDArray[int,:,:]])

    def test_cumprod4_(self):
        self.run_test("def np_cumprod4_(a):\n from numpy import cumprod\n return a.cumprod(0)", numpy.arange(10).reshape(2,5), np_cumprod4_=[NDArray[int,:,:]])

    def test_cumprod5_(self):
        self.run_test("def np_cumprod5_(a):\n from numpy import cumprod\n return a.cumprod(0)", numpy.arange(10), np_cumprod5_=[NDArray[int,:]])

    def test_correlate_1(self):
        self.run_test("def np_correlate_1(a,b):\n from numpy import correlate\n return correlate(a,b)",
                      numpy.arange(10,dtype=float),
                      numpy.arange(12,dtype=float),
                      np_correlate_1=[NDArray[float,:],NDArray[float,:]])
    def test_correlate_2(self):
        self.run_test("def np_correlate_2(a,b):\n from numpy import correlate\n return correlate(a,b)",
                  numpy.arange(12,dtype=float),
                  numpy.arange(10,dtype=float),
                  np_correlate_2=[NDArray[float,:],NDArray[float,:]])

    def test_correlate_3(self):
        self.run_test("def np_correlate_3(a,b):\n from numpy import correlate\n return correlate(a,b,'valid')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(10,dtype=float),
                  np_correlate_3=[NDArray[float,:],NDArray[float,:]])

    def test_correlate_4(self):
        self.run_test("def np_correlate_4(a,b):\n from numpy import correlate\n return correlate(a,b,'same')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(10,dtype=float),
                  np_correlate_4=[NDArray[float,:],NDArray[float,:]])

    def test_correlate_5(self):
        self.run_test("def np_correlate_5(a,b):\n from numpy import correlate\n return correlate(a,b,'same')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(7,dtype=float),
                  np_correlate_5=[NDArray[float,:],NDArray[float,:]])

    def test_correlate_6(self):
        self.run_test("def np_correlate_6(a,b):\n from numpy import correlate\n return correlate(a,b,'full')",
                  numpy.arange(12) + 1j*numpy.arange(12.),
                  numpy.arange(7.) + 1j* numpy.arange(7.),
                  np_correlate_6=[NDArray[complex,:],NDArray[complex,:]])

    def test_correlate_7(self):
        dtype = numpy.float32
        self.run_test("def np_correlate_7(a,b):\n from numpy import correlate\n return correlate(a,b,'full')",
                  numpy.arange(12).astype(dtype) + 1j*numpy.arange(12).astype(dtype),
                  numpy.arange(7).astype(dtype) + 1j* numpy.arange(7).astype(dtype),
                  np_correlate_7=[NDArray[numpy.complex64,:],NDArray[numpy.complex64,:]])

    def test_correlate_8(self):
        dtype = numpy.float32
        self.run_test("def np_correlate_8(a,b):\n from numpy import correlate\n return correlate(a,b,'full')",
                  numpy.arange(7).astype(dtype) +  1j*numpy.arange(7).astype(dtype),
                  numpy.arange(12).astype(dtype) + 1j*numpy.arange(12).astype(dtype),
                  np_correlate_8=[NDArray[numpy.complex64,:],NDArray[numpy.complex64,:]])

    def test_correlate_9(self):
        dtype = numpy.float
        self.run_test("def np_correlate_9(a,b):\n from numpy import correlate\n return correlate(a,b,'full')",
                  numpy.arange(7).astype(dtype)  + 1j*numpy.arange(7).astype(dtype),
                  numpy.arange(12).astype(dtype) + 1j*numpy.arange(12).astype(dtype),
                  np_correlate_9=[NDArray[numpy.complex128,:],NDArray[numpy.complex128,:]])

    def test_correlate_10(self):
        self.run_test("def np_correlate_10(a,b):\n from numpy import correlate\n return correlate(a,b,'same')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(7,dtype=numpy.float32),
                  np_correlate_10=[NDArray[float,:],NDArray[numpy.float32,:]])

    def test_correlate_11(self):
        self.run_test("def np_correlate_11(a,b):\n from numpy import correlate\n return correlate(a,b,'same')",
                  numpy.arange(12,dtype=numpy.float32),
                  numpy.arange(7,dtype=float),
                  np_correlate_11=[NDArray[numpy.float32,:],NDArray[float,:]])

    def test_convolve_1(self):
        self.run_test("def np_convolve_1(a,b):\n from numpy import convolve\n return convolve(a,b)",
                      numpy.arange(10,dtype=float),
                      numpy.arange(12,dtype=float),
                      np_convolve_1=[NDArray[float,:],NDArray[float,:]])
    def test_convolve_2(self):
        self.run_test("def np_convolve_2(a,b):\n from numpy import convolve\n return convolve(a,b)",
                  numpy.arange(12,dtype=float),
                  numpy.arange(10,dtype=float),
                  np_convolve_2=[NDArray[float,:],NDArray[float,:]])

    def test_convolve_3(self):
        self.run_test("def np_convolve_3(a,b):\n from numpy import convolve\n return convolve(a,b,'valid')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(10,dtype=float),
                  np_convolve_3=[NDArray[float,:],NDArray[float,:]])

    def test_convolve_4(self):
        self.run_test("def np_convolve_4(a,b):\n from numpy import convolve\n return convolve(a,b,'same')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(10,dtype=float),
                  np_convolve_4=[NDArray[float,:],NDArray[float,:]])

    def test_convolve_5(self):
        self.run_test("def np_convolve_5(a,b):\n from numpy import convolve\n return convolve(a,b,'same')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(7,dtype=float),
                  np_convolve_5=[NDArray[float,:],NDArray[float,:]])

    def test_convolve_6(self):
        self.run_test("def np_convolve_6(a,b):\n from numpy import convolve\n return convolve(a,b,'full')",
                  numpy.arange(12.) + 1j*numpy.arange(12.),
                  numpy.arange(7.) + 1j* numpy.arange(7.),
                  np_convolve_6=[NDArray[complex,:],NDArray[complex,:]])

    def test_convolve_7(self):
        dtype = numpy.float32
        self.run_test("def np_convolve_7(a,b):\n from numpy import convolve\n return convolve(a,b,'full')",
                  numpy.arange(12).astype(dtype) + 1j*numpy.arange(12).astype(dtype),
                  numpy.arange(7).astype(dtype) +  1j*numpy.arange(7).astype(dtype),
                  np_convolve_7=[NDArray[numpy.complex64,:],NDArray[numpy.complex64,:]])

    def test_convolve_8(self):
        dtype = numpy.float32
        self.run_test("def np_convolve_8(a,b):\n from numpy import convolve\n return convolve(a,b,'full')",
                  numpy.arange(7).astype(dtype) + 1j*numpy.arange(7).astype(dtype),
                  numpy.arange(12).astype(dtype) +1j*numpy.arange(12).astype(dtype),
                  np_convolve_8=[NDArray[numpy.complex64,:],NDArray[numpy.complex64,:]])

    def test_convolve_9(self):
        dtype = numpy.float
        self.run_test("def np_convolve_9(a,b):\n from numpy import convolve\n return convolve(a,b,'full')",
                  numpy.arange(7).astype(dtype) + 1j*  numpy.arange(7).astype(dtype),
                  numpy.arange(12).astype(dtype) + 1j* numpy.arange(12).astype(dtype),
                  np_convolve_9=[NDArray[numpy.complex128,:],NDArray[numpy.complex128,:]])

    def test_convolve_10(self):
        self.run_test("def np_convolve_10(a,b):\n from numpy import convolve\n return convolve(a,b,'same')",
                  numpy.arange(12,dtype=float),
                  numpy.arange(7,dtype=numpy.float32),
                  np_convolve_10=[NDArray[float,:],NDArray[numpy.float32,:]])

    def test_convolve_11(self):
        self.run_test("def np_convolve_11(a,b):\n from numpy import convolve\n return convolve(a,b,'same')",
                  numpy.arange(12,dtype=numpy.float32),
                  numpy.arange(7,dtype=float),
                  np_convolve_11=[NDArray[numpy.float32,:],NDArray[float,:]])
        
    def test_copy0(self):
        code= '''
def test_copy0(x):
    import numpy as np
    y = x
    z = np.copy(x)
    x[0] = 10
    return x[0], y[0], z[0]'''
        self.run_test(code, numpy.array([1, 2, 3]), test_copy0=[NDArray[int,:]])

    def test_copy1(self):
        code="def test_copy1(n): import numpy as np ; r = np.ones((n,n)); g = np.copy(r); return g"
        self.run_test(code, 10, test_copy1=[int])

    def test_copy2(self):
        code="def test_copy2(n): import numpy as np ; r = np.ones((n,n)); g0 = np.copy(r); g1 = np.copy(r); g0[0] = 1 ; g1[0] = 2 ; return g0, g1"
        self.run_test(code, 10, test_copy2=[int])

    def test_copy3(self):
        code="def test_copy3(n): import numpy as np ; r = [[1]*n for _ in range(n)]; g = np.copy(r) ; return g"
        self.run_test(code, 10, test_copy3=[int])

    def test_copy4(self):
        code="def test_copy4(n): import numpy as np ; r = n; g = np.copy(r) ; return g"
        self.run_test(code, 10, test_copy4=[int])

    def test_copy5(self):
        code="def test_copy5(n): return n[:-1].copy()"
        self.run_test(code, numpy.array([1,2,3]), test_copy5=[NDArray[int,:]])

    def test_copy6(self):
        code="def test_copy6(n): return n[-1].copy()"
        self.run_test(code, numpy.array([[1],[2],]), test_copy6=[NDArray[int,:,:]])

    def test_clip0(self):
        self.run_test("def np_clip0(a): return a.clip(1,8)", numpy.arange(10), np_clip0=[NDArray[int,:]])

    def test_clip1(self):
        self.run_test("def np_clip1(a): from numpy import  clip ; return clip(a,3,6)", numpy.arange(10), np_clip1=[NDArray[int,:]])

    def test_concatenate0(self):
        self.run_test("def np_concatenate0(a): from numpy import array, concatenate ; b = array([[5, 6]]) ; return concatenate((a,b))", numpy.array([[1, 2], [3, 4]]), np_concatenate0=[NDArray[int,:,:]])

    def test_concatenate1(self):
        self.run_test("def np_concatenate1(a): from numpy import array, concatenate ; return concatenate([a,a])", numpy.array([[1, 2], [3, 4]]), np_concatenate1=[NDArray[int,:,:]])

    def test_concatenate2(self):
        self.run_test(
            "def np_concatenate2(a): from numpy import array, concatenate ; b = array([[5, 6]]).T ; return concatenate((a,b, b), axis=1)",
            numpy.array([[1, 2], [3, 4]]),
            np_concatenate2=[NDArray[int,:,:]])

    def test_concatenate3(self):
        self.run_test("def np_concatenate3(a): from numpy import array, concatenate ; return concatenate([[1],a + a])", numpy.array([1, 2]), np_concatenate3=[NDArray[int,:]])

    def test_hstack_empty(self):
        code = 'def np_test_stack_empty(a): import numpy as np;return np.stack(a)'
        with self.assertRaises(ValueError):
            self.run_test(code, [], np_test_stack_empty=[List[NDArray[float,:]]])

    def test_hstack0(self):
        self.run_test("def np_hstack0(a,b): import numpy as np; return np.hstack((a,b))",
                      numpy.array((1,2,3)),
                      numpy.array((2,3,4)),
                      np_hstack0=[NDArray[int,:],NDArray[int,:]])

    def test_hstack1(self):
        self.run_test("def np_hstack1(a,b): import numpy as np; return np.hstack((a+1,b))",
                      numpy.array(([1],[2],[3])),
                      numpy.array(([2],[3],[4])),
                      np_hstack1=[NDArray[int,:,:],NDArray[int,:,:]])

    def test_vstack0(self):
        self.run_test("def np_vstack0(a,b): import numpy as np; return np.vstack((a,b))",
                      numpy.array((1,2,3)),
                      numpy.array((2,3,4)),
                      np_vstack0=[NDArray[int,:],NDArray[int,:]])

    def test_vstack1(self):
        self.run_test("def np_vstack1(a,b): import numpy as np; return np.vstack((a,b+b))",
                      numpy.array(([1],[2],[3])),
                      numpy.array(([2],[3],[4])),
                      np_vstack1=[NDArray[int,:,:],NDArray[int,:,:]])

    def test_stack0(self):
        self.run_test("def np_stack0(A): import numpy as np; return np.stack(A,axis=0)",
                      [numpy.ones((2,2)), 2*numpy.ones((2,2))],
                      np_stack0=[List[NDArray[float,:,:],NDArray[float,:,:]]])

    def test_stack1(self):
        self.run_test("def np_stack1(A): import numpy as np; return np.stack(A,axis=1)",
                      [numpy.ones((2,2,2)), 2*numpy.ones((2,2,2))],
                      np_stack1=[List[NDArray[float,:,:,:],NDArray[float,:,:,:]]])

    def test_stack2(self):
        self.run_test("def np_stack2(a,b): import numpy as np; return np.stack([a,b],axis=0)",
                      numpy.ones((2,2)), 
                      2*numpy.ones((2,2)),
                      np_stack2=[NDArray[float,:,:],NDArray[float,:,:]])

    def test_stack3(self):
        self.run_test("def np_stack3(a,b): import numpy as np; return np.stack((a,b),axis=0)",
                      numpy.ones((2,2)), 
                      2*numpy.ones((2,2)),
                      np_stack3=[NDArray[float,:,:],NDArray[float,:,:]])

    def test_stack4(self):
        self.run_test("def np_stack4(a,b): import numpy as np; return np.stack((2 * a,b),axis=0)",
                      numpy.ones((4,2,3)), 
                      2*numpy.ones((4,2,3)),
                      np_stack4=[NDArray[float,:,:,:],NDArray[float,:,:,:]])

    def test_stack5(self):
        self.run_test("def np_stack5(a): import numpy as np; return np.stack((a[:,1:],a[:,1:]),axis=1)",
                      numpy.ones((4,3,3)),
                      np_stack5=[NDArray[float,:,:,:]])

    def test_bincount0(self):
        self.run_test("def np_bincount0(a): from numpy import bincount ; return bincount(a)", numpy.arange(5), np_bincount0=[NDArray[int,:]])

    def test_bincount1(self):
        self.run_test("def np_bincount1(a, w): from numpy import bincount; return bincount(a,w)", numpy.array([0, 1, 1, 2, 2, 2]), numpy.array([0.3, 0.5, 0.2, 0.7, 1., -0.6]), np_bincount1=[NDArray[int,:], NDArray[float,:]])
    def test_bincount2(self):
        self.run_test("def np_bincount2(a, w): from numpy import bincount; return bincount(a + 1,w)", numpy.array([0, 1, 1, 2, 2, 2]), numpy.array([0.3, 0.5, 0.2, 0.7, 1., -0.6]), np_bincount2=[NDArray[int,:], NDArray[float,:]])

    def test_bincount3(self):
        self.run_test("def np_bincount3(a): from numpy import bincount,ones; x=ones((a.shape[0]+2), dtype=int); return bincount(a, x[:-2])", numpy.array([0, 1, 1, 2, 2, 2]), np_bincount3=[NDArray[int,:]])

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

    def test_base_repr5(self):
        self.run_test("def np_base_repr5(a): from numpy import base_repr ; return base_repr(a)", -5, np_base_repr5=[int])

    def test_base_repr6(self):
        self.run_test("def np_base_repr6(a): from numpy import base_repr ; return base_repr(a)", 0, np_base_repr6=[int])

    def test_base_repr7(self):
        self.run_test("def np_base_repr7(a): from numpy import base_repr ; return base_repr(a,5)", 0, np_base_repr7=[int])

    def test_average0(self):
        self.run_test("def np_average0(a): from numpy import average ; return average(a)", numpy.arange(10), np_average0=[NDArray[int,:]])

    def test_average1(self):
        self.run_test("def np_average1(a): from numpy import average ; return average(a,1)", numpy.arange(10).reshape(2,5), np_average1=[NDArray[int,:,:]])

    def test_average2(self):
        self.run_test("def np_average2(a): from numpy import average ; return average(a,None, range(10))", numpy.arange(10), np_average2=[NDArray[int,:]])

    def test_average3(self):
        self.run_test("def np_average3(a): from numpy import average ; return average(a,None, a)", numpy.arange(10).reshape(2,5), np_average3=[NDArray[int,:,:]])

    def test_atleast_1d0(self):
        self.run_test("def np_atleast_1d0(a): from numpy import atleast_1d ; return atleast_1d(a)", 1, np_atleast_1d0=[int])

    def test_atleast_1d1(self):
        self.run_test("def np_atleast_1d1(a): from numpy import atleast_1d ; r = atleast_1d(a) ; return r is a", numpy.arange(2), np_atleast_1d1=[NDArray[int,:]])

    def test_atleast_2d0(self):
        self.run_test("def np_atleast_2d0(a): from numpy import atleast_2d ; return atleast_2d(a)", 1, np_atleast_2d0=[int])

    def test_atleast_2d1(self):
        self.run_test("def np_atleast_2d1(a): from numpy import atleast_2d ; r = atleast_2d(a) ; return r is a", numpy.arange(2).reshape(1,2), np_atleast_2d1=[NDArray[int,:,:]])

    def test_atleast_2d2(self):
        self.run_test("def np_atleast_2d2(a): from numpy import atleast_2d ; r = atleast_2d(a) ; return r", numpy.arange(2), np_atleast_2d2=[NDArray[int,:]])

    def test_atleast_3d0(self):
        self.run_test("def np_atleast_3d0(a): from numpy import atleast_3d ; return atleast_3d(a)", 1, np_atleast_3d0=[int])

    def test_atleast_3d1(self):
        self.run_test("def np_atleast_3d1(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r is a", numpy.arange(8).reshape(2,2,2), np_atleast_3d1=[NDArray[int,:,:,:]])

    def test_atleast_3d2(self):
        self.run_test("def np_atleast_3d2(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r", numpy.arange(8).reshape(2,4), np_atleast_3d2=[NDArray[int,:,:]])

    def test_atleast_3d3(self):
        self.run_test("def np_atleast_3d3(a): from numpy import atleast_3d ; r = atleast_3d(a) ; return r", numpy.arange(8), np_atleast_3d3=[NDArray[int,:]])

    def test_asscalar0(self):
        self.run_test("def np_asscalar0(a): from numpy import asscalar; return asscalar(a)", numpy.array([1], numpy.int32), np_asscalar0=[NDArray[numpy.int32,:]])

    def test_asscalar1(self):
        self.run_test("def np_asscalar1(a): from numpy import asscalar; return asscalar(a)", numpy.array([[1]], numpy.int64), np_asscalar1=[NDArray[numpy.int64,:,:]])

    def test_ascontiguousarray0(self):
        self.run_test("def np_ascontiguousarray0(a):\n from numpy import ascontiguousarray\n return ascontiguousarray(a)", (1,2,3), np_ascontiguousarray0=[Tuple[int, int, int]])

    def test_asarray_chkfinite0(self):
        self.run_test("def np_asarray_chkfinite0(a):\n from numpy import asarray_chkfinite\n return asarray_chkfinite(a)", (1,2,3), np_asarray_chkfinite0=[Tuple[int, int, int]])

    def test_asarray_chkfinite1(self):
        self.run_test("def np_asarray_chkfinite1(a, x):\n from numpy import asarray_chkfinite\n try: return asarray_chkfinite(a)\n except ValueError: return asarray_chkfinite(x)", [[1.,2.],[numpy.nan,4.]], [[1.,2.],[3.,4.]], np_asarray_chkfinite1=[List[List[float]], List[List[float]]])

    def test_asarray0(self):
        self.run_test("def np_asarray0(a):\n from numpy import asarray\n return asarray(a)", (1,2,3), np_asarray0=[Tuple[int, int, int]])

    def test_asarray1(self):
        self.run_test("def np_asarray1(a):\n from numpy import asarray\n return asarray(a)", [(1,2),(3,4)], np_asarray1=[List[Tuple[int, int]]])

    def test_asarray2(self):
        self.run_test("def np_asarray2(a):\n from numpy import asarray, int8\n return asarray(a, int8)", [1., 2., 3.], np_asarray2=[List[float]])

    def test_asarray3(self):
        self.run_test("def np_asarray3(a):\n from numpy import asarray; b = asarray(a) ; return a is b", numpy.arange(3), np_asarray3=[NDArray[int,:]])

    def test_asarray4(self):
        self.run_test("def np_asarray4(a):\n from numpy import asarray\n return asarray(a[1:])", [(1,2),(3,4)], np_asarray4=[List[Tuple[int, int]]])

    def test_asarray5(self):
        self.run_test("def np_asarray5(a):\n from numpy import asarray\n return asarray(a)", 1., np_asarray5=[float])

    def test_asarray6(self):
        self.run_test("def np_asarray6(a):\n from numpy import asarray\n return asarray(a, dtype=int)", 1.5, np_asarray6=[float])

    def test_asfarray0(self):
        self.run_test("def np_asfarray0(a):\n from numpy import asfarray; b = asfarray(a) ; return a is b", numpy.arange(3.), np_asfarray0=[NDArray[float,:]])

    def test_asfarray1(self):
        self.run_test("def np_asfarray1(a):\n from numpy import asfarray; b = asfarray(a) ; return a is not b", numpy.arange(3), np_asfarray1=[NDArray[int,:]])

    def test_astype0(self):
        self.run_test("def np_astype0(a):\n return a.astype(float)", numpy.arange(3), np_astype0=[NDArray[int,:]])

    def test_astype1(self):
        self.run_test("def np_astype1(a):\n import numpy as jumpy; return a.astype(jumpy.uint8)", numpy.arange(257), np_astype1=[NDArray[int,:]])

    def test_array_str0(self):
        self.run_test("def np_array_str0(x): from numpy import array_str ; return array_str(x)", numpy.arange(3), np_array_str0=[NDArray[int,:]])

    def test_array_split0(self):
        self.run_test("def np_array_split0(a): from numpy import array_split, array2string ; return list(map(array2string,array_split(a, 3)))", numpy.arange(12), np_array_split0=[NDArray[int,:]])

    def test_array_split1(self):
        self.run_test("def np_array_split1(a): from numpy import array_split, array2string ; return list(map(array2string,array_split(a, 5)))", numpy.arange(12), np_array_split1=[NDArray[int,:]])

    def test_array_split2(self):
        self.run_test("def np_array_split2(a): from numpy import array_split, array2string ; return list(map(array2string,array_split(a, 4)))", numpy.arange(12).reshape(6,2), np_array_split2=[NDArray[int,:,:]])

    def test_array_split3(self):
        self.run_test("def np_array_split3(a): from numpy import array_split, array2string ; return list(map(array2string,array_split(a, [0,1,5])))", numpy.arange(12).reshape(6,2), np_array_split3=[NDArray[int,:,:]])

    def test_array_equiv0(self):
        self.run_test("def np_array_equiv0(a): from numpy import array_equiv ;  b = [1,2] ; return array_equiv(a,b)", [1, 2], np_array_equiv0=[List[int]])

    def test_array_equiv1(self):
        self.run_test("def np_array_equiv1(a): from numpy import array_equiv ;  b = [1,3] ; return array_equiv(a,b)", [1, 2], np_array_equiv1=[List[int]])

    def test_array_equiv2(self):
        self.run_test("def np_array_equiv2(a): from numpy import array_equiv ;  b = [[1,2],[1,2]] ; return array_equiv(a,b)", [1, 2], np_array_equiv2=[List[int]])

    def test_array_equiv3(self):
        self.run_test("def np_array_equiv3(a): from numpy import array_equiv ;  b = [[1,2],[1,3]] ; return array_equiv(a,b)", [1, 2], np_array_equiv3=[List[int]])

    def test_array_equal0(self):
        self.run_test("def np_array_equal0(a): from numpy import array_equal ;  b = [1,2] ; return array_equal(a,b)", [1, 2], np_array_equal0=[List[int]])

    def test_array_equal1(self):
        self.run_test("def np_array_equal1(a): from numpy import array, array_equal ;  b = array([1,2], dtype=int) ; return array_equal(a,b)", numpy.array([1,2]), np_array_equal1=[NDArray[int,:]])

    def test_array_equal2(self):
        self.run_test("def np_array_equal2(a): from numpy import array, array_equal ;  b = array([[1,2],[3,5]]) ; return array_equal(a,b)", numpy.array([[1,2],[3,5]]), np_array_equal2=[NDArray[int,:,:]])

    def test_array_equal3(self):
        self.run_test("def np_array_equal3(a): from numpy import array, array_equal ;  b = array([[1,2],[4,5]]) ; return array_equal(a,b)", numpy.array([[1,2],[3,5]]), np_array_equal3=[NDArray[int,:,:]])

    def test_array_equal4(self):
        self.run_test("def np_array_equal4(a): from numpy import array, array_equal ;  b = array([1,2,3]) ; return array_equal(a,b)", numpy. array([1,2]), np_array_equal4=[NDArray[int,:]])

    def test_array2string0(self):
        self.run_test("def np_array2string0(x): from numpy import array2string ; return array2string(x)", numpy.arange(3), np_array2string0=[NDArray[int,:]])

    def test_argwhere0(self):
        self.run_test("def np_argwhere0(x): from numpy import argwhere ; return argwhere(x)", numpy.arange(6), np_argwhere0=[NDArray[int,:]])

    def test_argwhere1(self):
        self.run_test("def np_argwhere1(x): from numpy import argwhere ; return argwhere(x>8)", numpy.arange(6), np_argwhere1=[NDArray[int,:]])

    def test_argwhere2(self):
        self.run_test("def np_argwhere2(x): from numpy import argwhere ; return argwhere(x>0)", numpy.arange(6).reshape(2,3), np_argwhere2=[NDArray[int,:,:]])

    def test_around0(self):
        self.run_test("def np_around0(x): from numpy import around ; return around(x)", [0.37, 1.64], np_around0=[List[float]])

    def test_around1(self):
        self.run_test("def np_around1(x): from numpy import around ; return around(x, 1)", [0.37, 1.64], np_around1=[List[float]])

    def test_around2(self):
        """ Check rounding on the left side of comma. """
        self.run_test("""
            def np_around2(x):
                from numpy import around
                return around(x, -1)""", [37.4, 164.65], np_around2=[List[float]])

    def test_around3(self):
        self.run_test("def np_around3(x): from numpy import around ; return around(x)", [.5, 1.5, 2.5, 3.5, 4.5], np_around3=[List[float]])

    def test_around4(self):
        self.run_test("def np_around4(x): from numpy import around ; return around(x,1)", [1,2,3,11], np_around4=[List[int]])

    def test_around5(self):
        self.run_test("def np_around5(x): from numpy import around ; return around(x,-1)", [1,2,3,11], np_around5=[List[int]])

    def test_argsort0(self):
        self.run_test("def np_argsort0(x): from numpy import argsort ; return argsort(x)", numpy.array([3, 1, 2]), np_argsort0=[NDArray[int,:]])

    def test_argsort1(self):
        self.run_test("def np_argsort1(x): return x.argsort()", numpy.array([[3, 1, 2], [1 , 2, 3]]), np_argsort1=[NDArray[int,:,:]])

    def test_argmax0(self):
        self.run_test("def np_argmax0(a): return a.argmax()", numpy.arange(6).reshape(2,3), np_argmax0=[NDArray[int,:,:]])

    def test_argmax1(self):
        self.run_test("def np_argmax1(a): from numpy import argmax ; return argmax(a+a)", numpy.arange(6).reshape(2,3), np_argmax1=[NDArray[int,:,:]])

    def test_argmax2(self):
        self.run_test("def np_argmax2(a): from numpy import argmax ; return argmax(a, 0)", numpy.arange(30).reshape(2,3,5), np_argmax2=[NDArray[int,:,:,:]])

    def test_argmin0(self):
        self.run_test("def np_argmin0(a): return a.argmin()", numpy.arange(6).reshape(2,3), np_argmin0=[NDArray[int,:,:]])

    def test_argmin1(self):
        self.run_test("def np_argmin1(a): from numpy import argmin ; return argmin(a)", [1,2,3], np_argmin1=[List[int]])

    def test_argmin2(self):
        self.run_test("def np_argmin2(a): from numpy import argmin ; return argmin(a, 0)", numpy.arange(30).reshape(2,3,5), np_argmin2=[NDArray[int,:,:,:]])

    def test_argmin3(self):
        self.run_test("def np_argmin3(a): from numpy import argmin ; return argmin(a, 1)", numpy.arange(30).reshape(2,3,5), np_argmin3=[NDArray[int,:,:,:]])

    def test_argmin4(self):
        self.run_test("def np_argmin4(a): from numpy import argmin ; return argmin(a, 2)", numpy.arange(30).reshape(2,3,5), np_argmin4=[NDArray[int,:,:,:]])

    def test_argmin5(self):
        self.run_test("def np_argmin5(a): from numpy import argmin ; return argmin(a[None, :] + a[:, None], 0)", numpy.arange(30), np_argmin5=[NDArray[int,:]])

    def test_argmin6(self):
        self.run_test("def np_argmin6(a): from numpy import argmin ; return argmin(a[None, :] + a[:, None], 1)", numpy.arange(30), np_argmin6=[NDArray[int,:]])

    def test_append0(self):
        self.run_test("def np_append0(a): from numpy import append ; b = [[4, 5, 6], [7, 8, 9]] ; return append(a,b)", [1, 2, 3], np_append0=[List[int]])

    def test_append1(self):
        self.run_test("def np_append1(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", [1, 2, 3], np_append1=[List[int]])

    def test_append2(self):
        self.run_test("def np_append2(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a,b)", numpy.array([1, 2, 3]), np_append2=[NDArray[int,:]])

    def test_append3(self):
        self.run_test("def np_append3(a): from numpy import append,array ; return append(a, 1)", numpy.array([1, 2, 3]), np_append3=[NDArray[int,:]])

    def test_append4(self):
        self.run_test("def np_append4(a): from numpy import append ; b = 4 ; return append(a,b)", [1, 2, 3], np_append4=[List[int]])

    def test_append5(self):
        self.run_test("def np_append5(a): from numpy import append,array ; return append(a, 1)", numpy.array([[1], [2], [3]]), np_append5=[NDArray[int,:, :]])

    def test_append6(self):
        self.run_test("def np_append6(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a.T, b)", numpy.array([[1], [2], [3]]), np_append6=[NDArray[int,:, :]])

    def test_append7(self):
        self.run_test("def np_append7(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a[0], b)", numpy.array([[1], [2], [3]]), np_append7=[NDArray[int,:, :]])

    def test_append8(self):
        self.run_test("def np_append8(a): from numpy import append,array ; b = array([[4, 5, 6], [7, 8, 9]]) ; return append(a[:], b)", numpy.array([[1], [2], [3]]), np_append8=[NDArray[int,:, :]])

    def test_angle0(self):
        self.run_test("def np_angle0(a): from numpy import angle ; return angle(a)", [1.0+0j, 1.0j, 1+1j, -1.0+0j, -1.0j, -1-1j], np_angle0=[List[complex]])

    def test_angle1(self):
                      self.run_test("def np_angle1(a): from numpy import angle ; return angle(a)", numpy.array([1.0+0j, 1.0j, 1+1j, -1.0+0j, -1.0j, -1-1j]), np_angle1=[NDArray[complex,:]])

    def test_angle2(self):
        self.run_test("def np_angle2(a): from numpy import angle ; return angle(a,True)", 1 + 1j, np_angle2=[complex])

    def test_angle3(self):
        self.run_test("def np_angle3(a): from numpy import angle ; return angle(a,True)", 1, np_angle3=[int])

    def test_any0(self):
        self.run_test("def np_any0(a): from numpy import any ; return any(a)", numpy.array([[True, False], [True, True]]), np_any0=[NDArray[bool,:,:]])

    def test_any1(self):
        self.run_test("def np_any1(a): from numpy import any ;  return any(a, 0)", numpy.array([[True, False], [False, False]]), np_any1=[NDArray[bool,:,:]])

    def test_any2(self):
        self.run_test("def np_any2(a): from numpy import any ; return any(a)", [-1, 0, 5], np_any2=[List[int]])

    def test_any3(self):
        self.run_test("def np_any3(a): from numpy import any ; return any(a).any(0)", [-1, 0, 5], np_any3=[List[int]])

    def test_any4(self):
        self.run_test("def np_any4(a): from numpy import any ; return any(a > 10)", numpy.array([-1, 0, 5]), np_any4=[NDArray[int, :]])

    def test_any5(self):
        self.run_test("def np_any5(a): from numpy import any ; return any(a > 10.0)", numpy.array([-1.0, 0.0, 5.0]), np_any5=[NDArray[float,:]])

    def test_any6(self):
        self.run_test("def np_any6(a): from numpy import any ; return any(a > 10.0)", numpy.array([[-1.0, 0.0], [5.0, 3.0]]), np_any6=[NDArray[float,:,:]])

    def test_any7(self):
        self.run_test("def np_any7(a): from numpy import any ; return any(a)", numpy.array([[False, False], [False, False]]), np_any7=[NDArray[bool,:,:]])

    def test_array1D_(self):
        self.run_test("def np_array1D_(a):\n from numpy import array\n return array(a)", [1,2,3], np_array1D_=[List[int]])

    def test_array2D_(self):
        self.run_test("def np_array2D_(a):\n from numpy import array\n return array(a)", [[1,2],[3,4]], np_array2D_=[List[List[int]]])

    def test_array_typed(self):
        self.run_test("def np_array_typed(a):\n from numpy import array, int64\n return array(a, int64)", [1.,2.,3.], np_array_typed=[List[float]])

    def test_zeros_(self):
        self.run_test("def np_zeros_(a): from numpy import zeros; return zeros(a)", (10, 5), np_zeros_=[Tuple[int, int]])

    def test_ones_(self):
        self.run_test("def np_ones_(a): from numpy import ones; return ones(a)", (10, 5), np_ones_=[Tuple[int, int]])

    def test_full_0(self):
        self.run_test("def np_full_0(a): from numpy import full; return full(a, 1.5)", (10, 5), np_full_0=[Tuple[int, int]])

    def test_full_1(self):
        self.run_test("def np_full_1(a): from numpy import full; return full(a, 1.5, dtype=int)", (10, 5), np_full_1=[Tuple[int, int]])

    def test_full_2(self):
        self.run_test("def np_full_2(a): from numpy import full; return full(a, 1.5)", 10, np_full_2=[int])

    def test_full_3(self):
        self.run_test("def np_full_3(a): from numpy import full; return full(a, 1.5, dtype=int)", 10, np_full_3=[int])

    def test_flat_zeros_(self):
        self.run_test("def np_flat_zeros_(a): from numpy import zeros; return zeros(a)", 10, np_flat_zeros_=[int])

    def test_flat_ones_(self):
        self.run_test("def np_flat_ones_(a): from numpy import ones; return ones(a)", 5, np_flat_ones_=[int])

    def test_input_array_(self):
        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", numpy.array([[1,2],[3,4]]), input_array_=[NDArray[int,:,:]])

    def test_change_array1D_(self):
        """ Assign to lowest dimension of an array. """
        self.run_test("""
            def np_change_array1D_(a):
                a[0, 0, 0] = 36
                return a""",
                      numpy.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]]),
                      np_change_array1D_=[NDArray[int,:,:,:]])

    def test_str_(self):
        self.run_test("def np_str_(a): return str(a)", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_str_=[NDArray[int,:,:,:]])

    def test_len_(self):
        self.run_test("def np_len_(a): return len(a)", numpy.array([[[1,2],[3,4]],[[5,6],[7,8]]]), np_len_=[NDArray[int,:,:,:]])

    def test_empty_(self):
        self.run_test("def np_empty_(a):\n from numpy import empty\n a = empty(a)\n return a.strides, len(a)", (3, 2), np_empty_=[Tuple[int, int]])

    def test_empty_uint_shape(self):
        self.run_test("def np_empty_uint_shape(a):\n from numpy import empty, uint8\n a = empty((uint8(a), uint8(a)))\n return a.strides, len(a)", 3, np_empty_uint_shape=[int])

    def test_empty_integral_shape(self):
        self.run_test("def np_empty_integral_shape(n):\n from numpy import empty, uint8\n a = empty(5)\n return a.strides, len(a), n", 3, np_empty_integral_shape=[int])

    def test_ones_uint_shape(self):
        self.run_test("def np_ones_uint_shape(a):\n from numpy import ones, uint32\n a = ones((uint32(a), uint32(a)))\n return a.strides, len(a)", 3, np_ones_uint_shape=[int])

    def test_ones_integral_shape(self):
        self.run_test("def np_ones_integral_shape(n):\n from numpy import ones, uint8\n a = ones(5)\n return a.strides, len(a), n", 3, np_ones_integral_shape=[int])

    def test_zeros_uint_shape(self):
        self.run_test("def np_zeros_uint_shape(a):\n from numpy import zeros, int32\n a = zeros((int32(a), int32(a)))\n return a.strides, len(a)", 3, np_zeros_uint_shape=[int])

    def test_zeros_integral_shape(self):
        self.run_test("def np_zeros_integral_shape(n):\n from numpy import zeros, uint8\n a = zeros(5)\n return a.strides, len(a), n", 3, np_zeros_integral_shape=[int])

    def test_empty_kwargs(self):
        self.run_test("def np_empty_kwargs(a):\n from numpy import empty\n a = empty(a, dtype=int)\n return a.strides, len(a)", (3, 2), np_empty_kwargs=[Tuple[int, int]])

    def test_empty_kwargs2(self):
        self.run_test("def np_empty_kwargs2(a):\n from numpy import empty \n a = empty(a, dtype=float)\n return a.strides, a.shape", 3, np_empty_kwargs2=[int])

    def test_arange(self):
        self.run_test("def np_arange_(a):\n from numpy import arange\n return arange(a, dtype=float)", 10, np_arange_=[int])

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

    def test_arange13(self):
        self.run_test("def np_arange12_(a):\n from numpy import arange, float32\n return arange(a, 25, dtype=float32)", 0, np_arange12_=[int])

    def test_arange14(self):
        self.run_test("def np_arange14_(a):\n from numpy import arange, float32\n return 50000 * arange(a, 25, dtype=float32)", 0, np_arange14_=[int])

    def test_arange15(self):
        self.run_test("def np_arange15_(a):\n from numpy import arange\n return arange(-4 * a, 1, 4)", 1, np_arange15_=[int])

    def test_arange16(self):
        self.run_test("def np_arange16_(a):\n from numpy import arange\n return arange(4 * a, -1, -4)", 1, np_arange16_=[int])

    def test_arange17(self):
        self.run_test("def np_arange17_(a):\n from numpy import arange\n return arange(4 * a, -1, -4)[:,None]", 1, np_arange17_=[int])

    def test_linspace(self):
        self.run_test("def np_linspace_(a):\n from numpy import linspace\n return linspace(a,4,32)", 1, np_linspace_=[int])

    def test_linspace1(self):
        self.run_test("def np_linspace1_(a):\n from numpy import linspace\n return linspace(a,32.5,2)", 0.4, np_linspace1_=[float])

    def test_linspace2(self):
        self.run_test("def np_linspace2_(a):\n from numpy import linspace\n return linspace(a,32.5,32, False)", 0.4, np_linspace2_=[float])

    def test_linspace3(self):
        self.run_test("def np_linspace3_(a):\n from numpy import linspace\n return linspace(1,a)", 4, np_linspace3_=[int])

    def test_linspace4(self):
        self.run_test("def np_linspace4_(a):\n from numpy import linspace\n return linspace(1,a,dtype=int)", 4, np_linspace4_=[int])

    def test_sin(self):
        self.run_test("def np_sin_(a):\n from numpy import sin\n return sin(a)", numpy.linspace(0,6), np_sin_=[NDArray[float,:]])

    def test_pi(self):
        self.run_test("def np_pi_():\n from numpy import pi\n return pi", np_pi_=[])

    def test_e(self):
        self.run_test("def np_e_():\n from numpy import e\n return e", np_e_=[])

    def test_ones_like_(self):
        self.run_test("def np_ones_like_(a):\n from numpy import ones_like, array\n return ones_like(array(a))", [[i,j,k,l] for i in range(5) for j in range(4) for k in range(6) for l in range(8)], np_ones_like_=[List[List[int]]])

    def test_full_like_0(self):
        self.run_test("def np_full_like_0(a):\n from numpy import full_like, array\n return full_like(array(a), fill_value=12.5)", [[i,j,k,l] for i in range(5) for j in range(4) for k in range(6) for l in range(8)], np_full_like_0=[List[List[int]]])

    def test_full_like_1(self):
        self.run_test("def np_full_like_1(a):\n from numpy import full_like, array\n return full_like(array(a), fill_value=12.5, dtype=float)", [[i,j,k,l] for i in range(5) for j in range(4) for k in range(6) for l in range(8)], np_full_like_1=[List[List[int]]])

    def test_zeros_like_(self):
        self.run_test("def np_zeros_like_(a):\n from numpy import zeros_like, array\n return zeros_like(array(a))", [[i,j,k,l] for i in range(5) for j in range(4) for k in range(6) for l in range(8)], np_zeros_like_=[List[List[int]]])

    def test_empty_like_1(self):
        """ Check empty_like numpy function without specified dtype. """
        code = """
            def np_empty_like_1(a):
                from numpy import empty_like
                b = empty_like(a)
                for i in range(2):
                    for j in range(3):
                        for k in range(4):
                            b[i, j, k] = i + j + k
                return b"""
        self.run_test(code,
                      numpy.arange(2 * 3 * 4).reshape(2, 3, 4),
                      np_empty_like_1=[NDArray[int,:,:,:]])

    def test_empty_like_2(self):
        """ Check empty_like numpy function with specific dtype argument. """
        code = """
            def np_empty_like_2(a):
                from numpy import empty_like
                b = empty_like(a, dtype=float)
                for i in range(2):
                    for j in range(3):
                        for k in range(4):
                            b[i, j, k] = i + j + k
                return b"""
        self.run_test(code,
                      numpy.arange(2 * 3 * 4).reshape(2, 3, 4),
                      np_empty_like_2=[NDArray[int,:,:,:]])

    def test_reshape0(self):
        self.run_test("def np_reshape0(a): return a.reshape((2,5))", numpy.arange(10), np_reshape0=[NDArray[int,:]])

    def test_reshape1(self):
        """Check reshaping with -1 argument."""
        code = """
def np_reshape1(a):
    return a.reshape((2,-1))"""
        self.run_test(code, numpy.arange(10), np_reshape1=[NDArray[int,:]])

    def test_reshape2(self):
        self.run_test("def np_reshape2(a): return a.reshape(5, 2)", numpy.arange(10), np_reshape2=[NDArray[int,:]])

    def test_reshape3(self):
        self.run_test("def np_reshape3(a): return (1 + a.reshape(1, a.size)), (1 + a[None])", numpy.arange(10), np_reshape3=[NDArray[int,:]])
        
    def test_reshape4(self):
        self.run_test("def np_reshape4(a): return (1 + a.reshape(5, -1)), (1 + a[None])", numpy.arange(10), np_reshape4=[NDArray[int,:]])
        
    def test_reshape5(self):
        self.run_test("def np_reshape5(a): return a.reshape(-1)", numpy.random.random((10,2)), np_reshape5=[NDArray[float,:,:]])
        
    def test_reshape6(self):
        code = "def test_reshape6(a): return a.reshape((-1,-1))"
        with self.assertRaises(ValueError):
            self.run_test(code, numpy.random.random((10,2)), test_reshape6=[NDArray[float,:,:]])

    def test_reshape7(self):
        self.run_test("def np_reshape7(a): return a.reshape(-10)", numpy.random.random((10,2)), np_reshape7=[NDArray[float,:,:]])

    def test_expand_dims1(self):
        code = """
import numpy
def np_expand_dims1(a,axis):
    return numpy.expand_dims(a,axis)"""
        self.run_test(code, numpy.arange(10,dtype=float),0, np_expand_dims1=[NDArray[float,:],int])
        self.run_test(code, numpy.arange(10,dtype=float),1, np_expand_dims1=[NDArray[float,:],int])
        
    def test_expand_dims2(self):
        code = """
import numpy
def np_expand_dims2(a,axis):
    return numpy.expand_dims(a,axis)"""
        self.run_test(code, numpy.random.randn(10,20),0, np_expand_dims2=[NDArray[float,:,:],int])
        self.run_test(code, numpy.random.randn(10,20),1, np_expand_dims2=[NDArray[float,:,:],int])
        self.run_test(code, numpy.random.randn(10,20),2, np_expand_dims2=[NDArray[float,:,:],int])
        
    def test_expand_dims3(self):
        code = """
import numpy
def np_expand_dims3(a,axis):
    return numpy.expand_dims(a,axis)"""
        self.run_test(code, numpy.random.randn(10,20,30),0, np_expand_dims3=[NDArray[float,:,:,:],int])
        self.run_test(code, numpy.random.randn(10,20,30),1, np_expand_dims3=[NDArray[float,:,:,:],int])
        self.run_test(code, numpy.random.randn(10,20,30),2, np_expand_dims3=[NDArray[float,:,:,:],int])
        self.run_test(code, numpy.random.randn(10,20,30),3, np_expand_dims3=[NDArray[float,:,:,:],int])
        

    def test_expand_dims4(self):
        code = '''

import numpy as np

def test1(x):
    y = np.expand_dims(x, -1)
    return y

def expand_dims4(x):
    A = np.array([-1.11312199, -0.99629629])
    return test1(x - A)'''
        self.run_test(code, numpy.random.randn(4,3,2), expand_dims4=[NDArray[float,:,:,:]])

    def test_duplicate(self):
        """Check array forwarded twice doesn't double free. """
        code = """
def np_duplicate(a):
    return a, a"""
        self.run_test(code, numpy.arange(10), np_duplicate=[NDArray[int,:]])

    def test_broadcast(self):
        """Check that ndarray returned twice doesn't double free. """
        code = """
def np_broadcast():
    import numpy
    a = numpy.arange(3)
    return a, a"""
        self.run_test(code, np_broadcast=[])

    def test_broadcast_slice(self):
        """Check that slicing an expression involving a broadcast works."""
        code = """
            def np_broadcast_slice(n):
                import numpy
                a = numpy.arange(n).reshape(2, n//2)
                return (a + 1)[:,1:]"""
        self.run_test(code, 20, np_broadcast_slice=[int])

    def test_broadcast_slice_again(self):
        """Check that slicing an expression involving a broadcast works."""
        code = """
            def np_broadcast_slice_again(n):
                import numpy
                a = numpy.arange(n).reshape(2, n//2)
                b = numpy.arange(n//2)
                return (a + b)[:,1:]"""
        self.run_test(code, 20, np_broadcast_slice_again=[int])

    def test_broadcast_dup(self):
        """Check that ndarray returned twice doesn't double free (reshaping)."""
        code = """
def np_broadcast_dup():
    import numpy
    a = numpy.arange(10)
    return a, a.reshape((2,5))"""
        self.run_test(code, np_broadcast_dup=[])

    def test_reshape_expr(self):
        self.run_test("def np_reshape_expr(a): return (a + a).reshape((2,5))", numpy.ones(10), np_reshape_expr=[NDArray[float,:]])

    def test_cumsum_(self):
        self.run_test("def np_cumsum_(a): return a.cumsum()", numpy.arange(10), np_cumsum_=[NDArray[int,:]])

    def test_cumsum2_(self):
        self.run_test("def np_cumsum2_(a): return a.cumsum()", numpy.arange(10).reshape(2,5), np_cumsum2_=[NDArray[int,:,:]])

    def test_cumsum3_(self):
        self.run_test("def np_cumsum3_(a): return a.cumsum(1)", numpy.arange(10).reshape(2,5), np_cumsum3_=[NDArray[int,:,:]])

    def test_cumsum4_(self):
        self.run_test("def np_cumsum4_(a): return a.cumsum(0)", numpy.arange(10).reshape(2,5), np_cumsum4_=[NDArray[int,:,:]])

    def test_cumsum5_(self):
        self.run_test("def np_cumsum5_(a): return a.cumsum(0)", numpy.arange(10), np_cumsum5_=[NDArray[int,:]])

    def test_sum_(self):
        self.run_test("def np_sum_(a): return a.sum()", numpy.arange(10), np_sum_=[NDArray[int,:]])

    def test_sum_of_bool(self):
        self.run_test("def np_sum_of_bool(a): return (a > 2).sum()", numpy.arange(10), np_sum_of_bool=[NDArray[int,:]])

    def test_sum_of_bool2(self):
        self.run_test("def np_sum_of_bool2(a): return (a > 2).sum(axis=1)", numpy.arange(10).reshape(5,2), np_sum_of_bool2=[NDArray[int,:,:]])

    def test_sum_scalar0(self):
        self.run_test("def np_sum_scalar0(a): return a.sum().sum()", numpy.arange(10), np_sum_scalar0=[NDArray[int,:]])

    def test_sum_scalar1(self):
        self.run_test("def np_sum_scalar1(a): return a.sum().sum(0)", numpy.arange(10), np_sum_scalar1=[NDArray[int,:]])

    def test_sum_neg_shape(self):
        self.run_test("def np_sum_neg_shape(a): return a.sum(axis=-1)", numpy.arange(10).reshape(5,2), np_sum_neg_shape=[NDArray[int,:,:]])

    def test_matrix_power0(self):
        self.run_test(
            "def np_matrix_power0(a): from numpy.linalg import matrix_power; return matrix_power(a, 0)",
            numpy.ones((10,10)),
            np_matrix_power0=[NDArray[float,:,:]]
        )

    def test_matrix_power1(self):
        self.run_test(
            "def np_matrix_power1(a): from numpy.linalg import matrix_power; return matrix_power(a, 1)",
            numpy.ones((10,10)),
            np_matrix_power1=[NDArray[float,:,:]]
        )

    def test_matrix_power2(self):
        self.run_test(
            "def np_matrix_power2(a): from numpy.linalg import matrix_power; return matrix_power(a, 5)",
            numpy.ones((10,10)),
            np_matrix_power2=[NDArray[float,:,:]]
        )


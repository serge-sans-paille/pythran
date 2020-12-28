import unittest
from pythran.tests import TestEnv
import numpy
from pythran.typing import NDArray


@TestEnv.module
class TestNumpyRFFT(TestEnv):

    # Basic test
    def test_rfft_0(self):
        self.run_test("def test_rfft(x): from numpy.fft import rfft ; return rfft(x)", numpy.arange(0,8.), test_rfft=[NDArray[float,:]])
    # Test various values of n, even, odd, greater and smaller than array size
    def test_rfft_1(self):
        self.run_test("def test_rfft_1(x,n): from numpy.fft import rfft ; return rfft(x,n)", numpy.arange(0,8.),8, test_rfft_1=[NDArray[float,:],int])
    def test_rfft_2(self):
        self.run_test("def test_rfft_2(x,n): from numpy.fft import rfft ; return rfft(x,n)", numpy.arange(0,8.),9, test_rfft_2=[NDArray[float,:],int])
    def test_rfft_3(self):
        self.run_test("def test_rfft_3(x,n): from numpy.fft import rfft ; return rfft(x,n)", numpy.arange(0,8.),7, test_rfft_3=[NDArray[float,:],int])
    def test_rfft_4(self):
        self.run_test("def test_rfft_4(x,n): from numpy.fft import rfft ; return rfft(x,n)", numpy.arange(0,8.),6, test_rfft_4=[NDArray[float,:],int])
    def test_rfft_5(self):
        self.run_test("def test_rfft_5(x,n): from numpy.fft import rfft ; return rfft(x,n)", numpy.arange(0,8.),10, test_rfft_5=[NDArray[float,:],int])

    # Two dimensional array
    def test_rfft_6(self):
        self.run_test("def test_rfft_6(x): from numpy.fft import rfft ; return rfft(x)", numpy.random.random((4,128)), test_rfft_6=[NDArray[float,:,:]])
    # Test axes
    def test_rfft_7(self):
        self.run_test("def test_rfft_7(x,n,a): from numpy.fft import rfft ; return rfft(x,n,a)", numpy.random.random((4,128)),128,1, test_rfft_7=[NDArray[float,:,:],int,int])
    def test_rfft_8(self):
        self.run_test("def test_rfft_8(x,n,a): from numpy.fft import rfft ; return rfft(x,n,a)", numpy.random.random((4,128)),128,0, test_rfft_8=[NDArray[float,:,:],int,int])
    # Test renorm
    def test_rfft_9(self):
        self.run_test("def test_rfft_9(x,n,a,r): from numpy.fft import rfft ; return rfft(x,n,a,r)", numpy.random.random((4,128)),128,1,'ortho', test_rfft_9=[NDArray[float,:,:],int,int,str])

    # Test float32
    def test_rfft_10(self):
        self.run_test("def test_rfft_10(x): from numpy.fft import rfft ; return rfft(x)", numpy.arange(0,8.).astype(numpy.float32), test_rfft_10=[NDArray[numpy.float32,:]])
    def test_rfft_11(self):
        self.run_test("def test_rfft_11(x,n): from numpy.fft import rfft ; return rfft(x,n)", numpy.arange(0,8.).astype(numpy.float32),16,test_rfft_11=[NDArray[numpy.float32,:],int])

    # Test parallel:
    def test_rfft_12(self):
        self.run_test('''
import numpy as np
def test_rfft_12(x):
    out = out = [np.empty_like(x, dtype=complex) for i in range(20)] 
    #omp parallel for
    for ii in range(20):
        out[ii] = np.fft.rfft(x)
    return np.concatenate(out)
''',numpy.random.random((4,128)), test_rfft_12=[NDArray[float,:,:]])

    ############# IRFFT
    # Basic test
    def test_irfft_0(self):
        self.run_test("def test_irfft_0(x): from numpy.fft import irfft ; return irfft(x)", numpy.exp(1j*numpy.random.random(8)), test_irfft_0=[NDArray[numpy.complex,:]])
    # Test various values of n, even, odd, greater and smaller than array size
    def test_irfft_1(self):
        self.run_test("def test_irfft_1(x,n): from numpy.fft import irfft ; return irfft(x,n)", numpy.exp(1j*numpy.random.random(8)),8, test_irfft_1=[NDArray[numpy.complex,:],int])
    def test_irfft_2(self):
        self.run_test("def test_irfft_2(x,n): from numpy.fft import irfft ; return irfft(x,n)", numpy.exp(1j*numpy.random.random(8)),9, test_irfft_2=[NDArray[numpy.complex,:],int])
    def test_irfft_3(self):
        self.run_test("def test_irfft_3(x,n): from numpy.fft import irfft ; return irfft(x,n)", numpy.exp(1j*numpy.random.random(8)),7, test_irfft_3=[NDArray[numpy.complex,:],int])
    def test_irfft_4(self):
        self.run_test("def test_irfft_4(x,n): from numpy.fft import irfft ; return irfft(x,n)", numpy.exp(1j*numpy.random.random(8)),6, test_irfft_4=[NDArray[numpy.complex,:],int])
    def test_irfft_5(self):
        self.run_test("def test_irfft_5(x,n): from numpy.fft import irfft ; return irfft(x,n)", numpy.exp(1j*numpy.random.random(8)),10, test_irfft_5=[NDArray[numpy.complex,:],int])

    # Two dimensional array
    def test_irfft_6(self):
        self.run_test("def test_irfft_6(x): from numpy.fft import irfft ; return irfft(x)", numpy.exp(1j*numpy.random.random((4,128))), test_irfft_6=[NDArray[numpy.complex,:,:]])
    # Test axes
    def test_irfft_7(self):
        self.run_test("def test_irfft_7(x,n,a): from numpy.fft import irfft ; return irfft(x,n,a)", numpy.exp(1j*numpy.random.random((4,128))),128,1, test_irfft_7=[NDArray[numpy.complex,:,:],int,int])
    def test_irfft_8(self):
        self.run_test("def test_irfft_8(x,n,a): from numpy.fft import irfft ; return irfft(x,n,a)", numpy.exp(1j*numpy.random.random((4,128))),128,0, test_irfft_8=[NDArray[numpy.complex,:,:],int,int])
    # Test renorm
    def test_irfft_9(self):
        self.run_test("def test_irfft_9(x,n,a,r): from numpy.fft import irfft ; return irfft(x,n,a,r)", numpy.exp(1j*numpy.random.random((4,128))),128,1,'ortho', test_irfft_9=[NDArray[numpy.complex,:,:],int,int,str])

    # Test complex64
    def test_irfft_10(self):
        self.run_test("def test_irfft_10(x): from numpy.fft import irfft ; return irfft(x)", numpy.exp(1j*numpy.random.random(8)).astype(numpy.complex64), test_irfft_10=[NDArray[numpy.complex64,:]])
    def test_irfft_11(self):
        self.run_test("def test_irfft_11(x,n): from numpy.fft import irfft ; return irfft(x,n)", numpy.exp(1j*numpy.random.random(8)).astype(numpy.complex64),16,test_irfft_11=[NDArray[numpy.complex64,:],int])

    # Test parallel:
    def test_irfft_12(self):
        self.run_test('''
import numpy as np
def test_irfft_12(x):
    out = [np.empty_like(x, dtype=float) for i in range(20)] 
    #omp parallel for
    for ii in range(20):
        out[ii] = np.fft.irfft(x)
    return np.concatenate(out)
''',numpy.exp(1j*numpy.random.random((4,128))).astype(numpy.complex64), test_irfft_12=[NDArray[numpy.complex64,:,:]])
        
@TestEnv.module
class TestNumpyFFT(TestEnv):
    def test_fft_1d_1(self):
        self.run_test("def test_fft_1d_1(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10)+1j*numpy.random.randn(10), test_fft_1d_1=[NDArray[numpy.complex128, :]])

    def test_fft_1d_2(self):
        self.run_test("def test_fft_1d_2(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(2**16)+1j*numpy.random.randn(2**16), test_fft_1d_2=[NDArray[numpy.complex128, :]])
        
    def test_fft_1d_c64_1(self):
        self.run_test("def test_fft_1d_c64_1(x): from numpy.fft import fft ; return fft(x)", (numpy.random.randn(10)+1j*numpy.random.randn(10)).astype(numpy.complex64), test_fft_1d_c64_1=[NDArray[numpy.complex64, :]])

    # currently this fails because the python result returns complex128
    def test_fft_1d_c64_2(self):
        self.run_test("def test_fft_1d_c64_2(x): from numpy.fft import fft ; return fft(x)", (numpy.random.randn(2**16)+1j*numpy.random.randn(2**16)).astype(numpy.complex64), test_fft_1d_c64_2=[NDArray[numpy.complex64, :]])
    
    def test_fft_1d_normNorm(self):
        self.run_test("def test_fft_1d_norm(x): from numpy.fft import fft ; return fft(x, norm=None)", numpy.random.randn(10)+1j*numpy.random.randn(10), test_fft_1d_norm=[NDArray[numpy.complex128, :]])

    def test_fft_1d_norm(self):
        self.run_test("def test_fft_1d_norm(x, norm): from numpy.fft import fft ; return fft(x, norm=norm)", numpy.random.randn(10)+1j*numpy.random.randn(10), "ortho", test_fft_1d_norm=[NDArray[numpy.complex128, :], str])

    def test_fft_1d_n(self):
        nl = [8, 10, 14]
        for n in nl:
            with self.subTest():
                self.run_test("def test_fft_1d_n(x, n): from numpy.fft import fft; return fft(x, n=n)", numpy.random.randn(10)+1j*numpy.random.randn(10), n, test_fft_1d_n=[NDArray[numpy.complex, :], int])

    # This fails currently
    def test_fft_1d_nNone(self):
        self.run_test("def test_fft_1d_n(x): from numpy.fft import fft; return fft(x, n=None)", numpy.random.randn(10)+1j*numpy.random.randn(10),  test_fft_1d_n=[NDArray[numpy.complex, :]])

    def test_fft_1d_n_norm(self):
        nl = [8, 10, 14, None]
        norm = ["ortho", None]
        for n in nl:
            for nr in norm:
                with self.subTest():
                    self.run_test("def test_fft_1d_n(x, n, norm): from numpy.fft import fft; return fft(x, n=n, norm=norm)", numpy.random.randn(10)+1j*numpy.random.randn(10), n, nr, test_fft_1d_n=[NDArray[numpy.complex, :], int, str])

    def test_fft_2d(self):
        szs  = [3, 5]
        for sz in szs:
            with self.subTest():
                self.run_test("def test_fft_2d_2(x): from numpy.fft import fft ; return fft(x)", (numpy.random.randn(30)+1j*numpy.random.randn(30)).reshape(sz, -1), test_fft_2d_2=[NDArray[numpy.complex128, :, :]])

    def test_fft_2d_axis(self):
        al = [0, 1, -1]
        szs = [3, 5]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_fft_2d_axis_1(x, a): from numpy.fft import fft ; return fft(x, axis=a)", (numpy.random.randn(30)+1j*numpy.random.randn(30)).reshape(sz, -1), a, test_fft_2d_axis_1=[NDArray[numpy.complex128, :, :], int])

    def test_fft_2d_axis_n(self):
        al = [0, 1, -1]
        nl = [3, 4, 5, 6]
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_fft_2d_axis_lengthened_3(x, a, n): from numpy.fft import fft ; return fft(x, n=n, axis=a)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, n, test_fft_2d_axis_lengthened_3=[NDArray[numpy.complex128, :, :], int, int])

    def test_fft_2d_axis_nNone(self):
        al = [0, 1, -1]
        for a in al:
            with self.subTest():
                self.run_test("def test_fft_2d_axis_lengthened_3(x, a): from numpy.fft import fft ; return fft(x, n=None, axis=a)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, test_fft_2d_axis_lengthened_3=[NDArray[numpy.complex128, :, :], int])
                
    def test_fft_2d_axis_n_orth(self):
        al = [0, 1, -1]
        nl = [3, 4, 5, 6, None]
        norms = [None, "ortho"]
        for a in al:
            for n in nl:
                for nr in norms:
                    with self.subTest():
                        if nr is None:
                            if n is None:
                                self.run_test("def test_fft_2d_axis_n_orth11(x, a): from numpy.fft import fft ; return fft(x, n=None, axis=a, norm=None)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, test_fft_2d_axis_n_orth11=[NDArray[numpy.complex128, :, :], int])
                            else:
                                self.run_test("def test_fft_2d_axis_n_orth1(x, a, n): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=None)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, n, test_fft_2d_axis_n_orth1=[NDArray[numpy.complex128, :, :], int, int])
                        elif n is None:
                            self.run_test("def test_fft_2d_axis_n_orth2(x, a, norm): from numpy.fft import fft ; return fft(x, n=None, axis=a, norm=norm)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, nr, test_fft_2d_axis_n_orth2=[NDArray[numpy.complex128, :, :], int, str])
                        else:
                            self.run_test("def test_fft_2d_axis_n_orth3(x, a, n, norm): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=norm)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, n, nr, test_fft_2d_axis_n_orth3=[NDArray[numpy.complex128, :, :], int, int, str])

    def test_fft_3d(self):
        szs  = [(5, 4, -1), (4, 5, -1)]
        for sz in szs:
            with self.subTest():
                self.run_test("def test_fft_3d(x): from numpy.fft import fft ; return fft(x)", (numpy.random.randn(200)+1j*numpy.random.randn(200)).reshape(sz), test_fft_3d=[NDArray[numpy.complex128, :, :, :]])

    def test_fft_3d_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_fft_3d_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", (numpy.random.randn(200)+1j*numpy.random.randn(200)).reshape(sz), a, test_fft_3d_axis=[NDArray[numpy.complex128, :, :, :], int])

    def test_fft_3d_axis_n(self):
        al = [0, 1, 2, -1]
        nl = [3, 4, 5, 6]
        sz = (4,4,4)
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_fft_3d_axis_n(x, a, n): from numpy.fft import fft ; return fft(x, n=n, axis=a)", (numpy.random.randn(64)+1j*numpy.random.randn(64)).reshape(sz), a, n, test_fft_3d_axis_n=[NDArray[numpy.complex128, :, :, :], int, int])

    # fails currently
    def test_fft_3d_axis_nNone(self):
        al = [0, 1, 2, -1]
        sz = (4,4,4)
        for a in al:
            with self.subTest():
                self.run_test("def test_fft_3d_axis_nNone(x, a): from numpy.fft import fft ; return fft(x, n=None, axis=a)", (numpy.random.randn(64)+1j*numpy.random.randn(64)).reshape(sz), a, test_fft_3d_axis_nNone=[NDArray[numpy.complex128, :, :, :], int])
                
    def test_fft_3d_axis_n_orth(self):
        al = [0, 1, -1]
        nl = [3, 4, 5, 6, None]
        sz = (4,4,4)
        norms = [None, "ortho"]
        for a in al:
            for n in nl:
                for nr in norms:
                    with self.subTest():
                        if nr is None:
                            if n is None:
                                self.run_test("def test_fft_3d_axis_n_orth1(x, a): from numpy.fft import fft ; return fft(x, n=None, axis=a, norm=None)", (numpy.random.randn(64)+1j*numpy.random.rand(64)).reshape(sz), a, test_fft_3d_axis_n_orth1=[NDArray[numpy.complex128, :, :, :], int])
                            else:
                                self.run_test("def test_fft_3d_axis_n_orth1(x, a, n): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=None)", (numpy.random.randn(64)+1j*numpy.random.randn(64)).reshape(sz), a, n, test_fft_3d_axis_n_orth1=[NDArray[numpy.complex128, :, :, :], int, int])
                        elif n is None:
                            self.run_test("def test_fft_3d_axis_n_orth2(x, a, norm): from numpy.fft import fft ; return fft(x, n=None, axis=a, norm=norm)", (numpy.random.randn(64)+1j*numpy.random.randn(64)).reshape(sz), a, nr, test_fft_3d_axis_n_orth2=[NDArray[numpy.complex128, :, :, :], int, str])
                        else:
                            self.run_test("def test_fft_3d_axis_n_orth3(x, a, n, norm): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=norm)", (numpy.random.randn(64)+1j*numpy.random.randn(64)).reshape(sz), a, n, nr, test_fft_3d_axis_n_orth3=[NDArray[numpy.complex128, :, :, :], int, int, str])

    # fails to build for me weirdly enough
    def test_fft_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_fft_paralle(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)+1j*numpy.random.randn(512)).reshape((4,128)), test_fft_parallel=[NDArray[numpy.complex128, :, :]])

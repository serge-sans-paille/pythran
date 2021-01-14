import unittest
from pythran.tests import TestEnv
import numpy
from pythran.typing import NDArray
import unittest


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

    # Test with arguments
    def test_rfft_13(self):
        self.run_test("def test_rfft_13(x): from numpy.fft import rfft ; return rfft(x,axis=1)", numpy.random.random((2,128)), test_rfft_13=[NDArray[float,:,:]])

    def test_rfft_14(self):
        self.run_test("def test_rfft_14(x): from numpy.fft import rfft ; return rfft(x,n=128,axis=0)", numpy.random.random((2,128)), test_rfft_14=[NDArray[float,:,:]])

    @unittest.skip("Mismatch because numpy converts to double before fft (See comment in header file)")
    def test_rfft_f32(self):
        self.run_test("def test_rfft_f32(x): from numpy.fft import rfft ; return rfft(x)", numpy.random.random(128).astype(numpy.float32), test_rfft_f32=[NDArray[numpy.float32,:]])

    def test_rfft_int64(self):
        self.run_test("def test_rfft_int64(x): from numpy.fft import rfft ; return rfft(x)", (100*numpy.random.random(128)).astype(numpy.int64), test_rfft_int64=[NDArray[numpy.int64,:]])

    def test_rfft_byte(self):
        self.run_test("def test_rfft_byte(x): from numpy.fft import rfft ; return rfft(x)", (100*numpy.random.random(128)).astype(numpy.byte), test_rfft_byte=[NDArray[numpy.byte,:]])


@TestEnv.module
class TestNumpyIRFFT(TestEnv):
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

    # Test with arguments
    def test_irfft_13(self):
        self.run_test("def test_irfft_13(x): from numpy.fft import irfft ; return irfft(x,axis=1)", numpy.exp(1j*numpy.random.random((2,128))), test_irfft_13=[NDArray[numpy.complex,:,:]])

    def test_irfft_14(self):
        self.run_test("def test_irfft_14(x): from numpy.fft import irfft ; return irfft(x,n=128,axis=0)", numpy.exp(1j*numpy.random.random((2,128))), test_irfft_14=[NDArray[numpy.complex,:,:]])
        
    def test_irfft_c64(self):
        self.run_test("def test_irfft_c64(x): from numpy.fft import irfft ; return irfft(x)", numpy.exp(1j*numpy.random.random((2,128))).astype(numpy.complex64), test_irfft_c64=[NDArray[numpy.complex64,:,:]])
        
    def test_irfft_f64(self):
        self.run_test("def test_irfft_f64(x): from numpy.fft import irfft ; return irfft(x)", numpy.random.random(128), test_irfft_f64=[NDArray[numpy.float64,:]])
        
    def test_irfft_f32(self):
        self.run_test("def test_irfft_f32(x): from numpy.fft import irfft ; return irfft(x)", numpy.random.random(128).astype(numpy.float32), test_irfft_f32=[NDArray[numpy.float32,:]])
        
    def test_irfft_int64(self):
        self.run_test("def test_irfft_int64(x): from numpy.fft import irfft ; return irfft(x)", (100*numpy.random.random(128)).astype(numpy.int64), test_irfft_int64=[NDArray[numpy.int64,:]])

    def test_irfft_byte(self):
        self.run_test("def test_irfft_byte(x): from numpy.fft import irfft ; return irfft(x)", (100*numpy.random.random(128)).astype(numpy.byte), test_irfft_byte=[NDArray[numpy.byte,:]])


@TestEnv.module
class TestNumpyFFT(TestEnv):
    # complex inputs
    def test_fft_1d_1(self):
        self.run_test("def test_fft_1d_1(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10)+1j*numpy.random.randn(10), test_fft_1d_1=[NDArray[numpy.complex128, :]])
    # check axis arg
    def test_fft_1d_axis(self):
        axs = [0, -1]
        for ax in axs:
            with self.subTest():
                self.run_test("def test_fft_1d_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", numpy.random.randn(10)+1j*numpy.random.randn(10), ax, test_fft_1d_axis=[NDArray[numpy.complex128, :], int])
    # check n arg set to None explicitely
    def test_fft_1d_n_None(self):
        self.run_test("def test_fft_1d_n_None(x): from numpy.fft import fft ; return fft(x, n=None)", numpy.random.randn(10)+1j*numpy.random.randn(10), test_fft_1d_n_None=[NDArray[numpy.complex128, :]])
    # check n set smaller, same and larger than axis
    def test_fft_1d_n(self):
        ns = [8, 10, 12]
        for n in ns:
            with self.subTest():
                self.run_test("def test_fft_1d_n(x, n): from numpy.fft import fft ; return fft(x, n)", numpy.random.randn(10)+1j*numpy.random.randn(10), n, test_fft_1d_n=[NDArray[numpy.complex128, :], int])
    # check norm arg
    def test_fft_1d_norm(self):
        self.run_test("def test_fft_1d_norm(x, norm): from numpy.fft import fft ; return fft(x, norm=norm)", numpy.random.randn(10)+1j*numpy.random.randn(10), "ortho", test_fft_1d_norm=[NDArray[numpy.complex128, :], str])

    ## do the same checks for real inputs
    def test_fft_1d_f64_1(self):
        self.run_test("def test_fft_1d_f64_1(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10), test_fft_1d_f64_1=[NDArray[numpy.float64, :]])

    def test_fft_1d_real_f32(self):
        self.run_test("def test_fft_1d_real_f32(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10).astype(numpy.float32), test_fft_1d_real_f32=[NDArray[numpy.float32, :]])

    def test_fft_1d_f64_axis(self):
        axs = [0, -1]
        for ax in axs:
            with self.subTest():
                self.run_test("def test_fft_1d_f64_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", numpy.random.randn(10), ax, test_fft_1d_f64_axis=[NDArray[numpy.float64, :], int])

    def test_fft_1d_f64_n_None(self):
        self.run_test("def test_fft_1d_f64_n_None(x): from numpy.fft import fft ; return fft(x, n=None)", numpy.random.randn(10), test_fft_1d_f64_n_None=[NDArray[numpy.float64, :]])

    # check n set smaller, same and larger than axis
    def test_fft_1d_f64_n(self):
        ns = [8, 10, 12]
        for n in ns:
            with self.subTest():
                self.run_test("def test_fft_1d_f64_n(x, n): from numpy.fft import fft ; return fft(x, n)", numpy.random.randn(10), n, test_fft_1d_f64_n=[NDArray[numpy.float64, :], int])

    def test_fft_1d_f64_norm(self):
        self.run_test("def test_fft_1d_f64_norm(x, n): from numpy.fft import fft ; return fft(x, norm=n)", numpy.random.randn(10), "ortho", test_fft_1d_f64_norm=[NDArray[numpy.float64, :], str])

    def test_fft_1d_f64_norm_None(self):
        self.run_test("def test_fft_1d_norm_None(x): from numpy.fft import fft ; return fft(x, norm=None)", numpy.random.randn(10), test_fft_1d_norm_None=[NDArray[numpy.float64, :]])
    # check for integer intputs
    def test_fft_1d_int64(self):
        self.run_test("def test_fft_1d_int64(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10).astype(numpy.int64), test_fft_1d_int64=[NDArray[numpy.int64, :]])

    def test_fft_1d_int32(self):
        self.run_test("def test_fft_1d_int32(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10).astype(numpy.int32), test_fft_1d_int32=[NDArray[numpy.int32, :]])

    def test_fft_1d_int8(self):
        self.run_test("def test_fft_1d_int8(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10).astype(numpy.int8), test_fft_1d_int8=[NDArray[numpy.int8, :]])

    def test_fft_1d_byte(self):
        self.run_test("def test_fft_1d_byte(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(10).astype(numpy.int8), test_fft_1d_byte=[NDArray[numpy.byte, :]])

    def test_fft_1d_int64_axis(self):
        axs = [0, -1]
        for ax in axs:
            with self.subTest():
                self.run_test("def test_fft_1d_int64_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", numpy.random.randn(10).astype(numpy.int64), ax, test_fft_1d_int64_axis=[NDArray[numpy.int64, :], int])

    def test_fft_1d_int64_n_None(self):
        self.run_test("def test_fft_1d_int64_n_None(x): from numpy.fft import fft ; return fft(x, n=None)", numpy.random.randn(10).astype(numpy.int64), test_fft_1d_int64_n_None=[NDArray[numpy.int64, :]])

    # check n set smaller, same and larger than axis
    def test_fft_1d_int64_n(self):
        ns = [8, 10, 12]
        for n in ns:
            with self.subTest():
                self.run_test("def test_fft_1d_int64_n(x, n): from numpy.fft import fft ; return fft(x, n)", numpy.random.randn(10).astype(numpy.int64), n, test_fft_1d_int64_n=[NDArray[numpy.int64, :], int])

    def test_fft_1d_int64_axis(self):
        self.run_test("def test_fft_1d_int64_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", numpy.random.randn(10).astype(numpy.int64), 0, test_fft_1d_int64_axis=[NDArray[numpy.int64, :], int])

    def test_fft_1d_int64_norm(self):
        self.run_test("def test_fft_1d_int64_norm(x, n): from numpy.fft import fft ; return fft(x, norm=n)", numpy.random.randn(10).astype(numpy.int64), "ortho", test_fft_1d_int64_norm=[NDArray[numpy.int64, :], str])

    def test_fft_1d_int64_norm_None(self):
        self.run_test("def test_fft_1d_int64_norm_None(x): from numpy.fft import fft ; return fft(x, norm=None)", numpy.random.randn(10).astype(numpy.int64), test_fft_1d_int64_norm_None=[NDArray[numpy.int64, :]])

    def test_fft_1d_2(self):
        self.run_test("def test_fft_1d_2(x): from numpy.fft import fft ; return fft(x)", numpy.random.randn(2**16)+1j*numpy.random.randn(2**16), test_fft_1d_2=[NDArray[numpy.complex128, :]])

    def test_fft_2d(self):
        szs  = [3, 5]
        for sz in szs:
            with self.subTest():
                self.run_test("def test_fft_2d_2(x): from numpy.fft import fft ; return fft(x)", (numpy.random.randn(30)+1j*numpy.random.randn(30)).reshape(sz, -1), test_fft_2d_2=[NDArray[numpy.complex128, :, :]])

    def test_fft_2d_axis_n_norm(self):
        al = [0, 1, -1]
        nl = [3, 4, 5]
        norm = "ortho"
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_fft_2d_axis_n_norm(x, a, n, norm): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=norm)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, n, norm, test_fft_2d_axis_n_norm=[NDArray[numpy.complex128, :, :], int, int, str])

    def test_fft_2d_f64_axis_n_norm(self):
        al = [0, 1, -1]
        nl = [3, 4, 5]
        norm = "ortho"
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_fft_2d_f64_axis_n_norm(x, a, n, norm): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=norm)", numpy.random.randn(20).reshape(5, -1).copy(), a, n, norm, test_fft_2d_f64_axis_n_norm=[NDArray[numpy.float64, :, :], int, int, str])

    def test_fft_2d_int64_axis_n_norm(self):
        al = [0, 1, -1]
        nl = [3, 4, 5]
        norm = "ortho"
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_fft_2d_int64_axis_n_norm(x, a, n, norm): from numpy.fft import fft ; return fft(x, n=n, axis=a, norm=norm)", (numpy.random.randn(20)).astype(numpy.int64).reshape(5, -1).copy(), a, n, norm, test_fft_2d_int64_axis_n_norm=[NDArray[numpy.int64, :, :], int, int, str])
    # 3D
    def test_fft_3d(self):
        szs  = [(5, 4, -1), (4, 5, -1)]
        for sz in szs:
            with self.subTest():
                self.run_test("def test_fft_3d(x): from numpy.fft import fft ; return fft(x)", (numpy.random.randn(200)+1j*numpy.random.randn(200)).reshape(sz).copy(), test_fft_3d=[NDArray[numpy.complex128, :, :, :]])

    def test_fft_3d_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_fft_3d_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", (numpy.random.randn(200)+1j*numpy.random.randn(200)).reshape(sz), a, test_fft_3d_axis=[NDArray[numpy.complex128, :, :, :], int])

    def test_fft_3d_f64_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_fft_3d_f64_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", (numpy.random.randn(200)).reshape(sz), a, test_fft_3d_f64_axis=[NDArray[numpy.float64, :, :, :], int])

    def test_fft_3d_int64_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_fft_3d_int64_axis(x, a): from numpy.fft import fft ; return fft(x, axis=a)", (numpy.random.randn(200)).reshape(sz).astype(numpy.int64), a, test_fft_3d_int64_axis=[NDArray[numpy.int64, :, :, :], int])

    def test_fft_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_fft_parallel(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)+1j*numpy.random.randn(512)).reshape((4,128)), test_fft_parallel=[NDArray[numpy.complex128, :, :]])

    def test_fft_f64_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_fft_f64_parallel(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)).reshape((4,128)), test_fft_f64_parallel=[NDArray[numpy.float64, :, :]])

    def test_fft_int64_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_fft_int64_parallel(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)).reshape((4,128)).astype(numpy.int64), test_fft_int64_parallel=[NDArray[numpy.int64, :, :]])

@TestEnv.module
class TestNumpyIFFT(TestEnv):
    # complex inputs
    def test_ifft_1d_1(self):
        self.run_test("def test_ifft_1d_1(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10)+1j*numpy.random.randn(10), test_ifft_1d_1=[NDArray[numpy.complex128, :]])
    # check axis arg
    def test_ifft_1d_axis(self):
        axs = [0, -1]
        for ax in axs:
            with self.subTest():
                self.run_test("def test_ifft_1d_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", numpy.random.randn(10)+1j*numpy.random.randn(10), ax, test_ifft_1d_axis=[NDArray[numpy.complex128, :], int])
    # check n arg set to None explicitely
    def test_ifft_1d_n_None(self):
        self.run_test("def test_ifft_1d_n_None(x): from numpy.fft import ifft ; return ifft(x, n=None)", numpy.random.randn(10)+1j*numpy.random.randn(10), test_ifft_1d_n_None=[NDArray[numpy.complex128, :]])
    # check n set smaller, same and larger than axis
    def test_ifft_1d_n(self):
        ns = [8, 10, 12]
        for n in ns:
            with self.subTest():
                self.run_test("def test_ifft_1d_n(x, n): from numpy.fft import ifft ; return ifft(x, n)", numpy.random.randn(10)+1j*numpy.random.randn(10), n, test_ifft_1d_n=[NDArray[numpy.complex128, :], int])
    # check norm arg
    def test_ifft_1d_norm(self):
        self.run_test("def test_ifft_1d_norm(x, norm): from numpy.fft import ifft ; return ifft(x, norm=norm)", numpy.random.randn(10)+1j*numpy.random.randn(10), "ortho", test_ifft_1d_norm=[NDArray[numpy.complex128, :], str])

    ## do the same checks for real inputs
    def test_ifft_1d_f64_1(self):
        self.run_test("def test_ifft_1d_f64_1(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10), test_ifft_1d_f64_1=[NDArray[numpy.float64, :]])

    def test_ifft_1d_real_f32(self):
        self.run_test("def test_ifft_1d_real_f32(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10).astype(numpy.float32), test_ifft_1d_real_f32=[NDArray[numpy.float32, :]])

    def test_ifft_1d_f64_axis(self):
        axs = [0, -1]
        for ax in axs:
            with self.subTest():
                self.run_test("def test_ifft_1d_f64_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", numpy.random.randn(10), ax, test_ifft_1d_f64_axis=[NDArray[numpy.float64, :], int])

    def test_ifft_1d_f64_n_None(self):
        self.run_test("def test_ifft_1d_f64_n_None(x): from numpy.fft import ifft ; return ifft(x, n=None)", numpy.random.randn(10), test_ifft_1d_f64_n_None=[NDArray[numpy.float64, :]])

    # check n set smaller, same and larger than axis
    def test_ifft_1d_f64_n(self):
        ns = [8, 10, 12]
        for n in ns:
            with self.subTest():
                self.run_test("def test_ifft_1d_f64_n(x, n): from numpy.fft import ifft ; return ifft(x, n)", numpy.random.randn(10), n, test_ifft_1d_f64_n=[NDArray[numpy.float64, :], int])

    def test_ifft_1d_f64_norm(self):
        self.run_test("def test_ifft_1d_f64_norm(x, n): from numpy.fft import ifft ; return ifft(x, norm=n)", numpy.random.randn(10), "ortho", test_ifft_1d_f64_norm=[NDArray[numpy.float64, :], str])

    def test_ifft_1d_f64_norm_None(self):
        self.run_test("def test_ifft_1d_norm_None(x): from numpy.fft import ifft ; return ifft(x, norm=None)", numpy.random.randn(10), test_ifft_1d_norm_None=[NDArray[numpy.float64, :]])
    # check for integer intputs
    def test_ifft_1d_int64(self):
        self.run_test("def test_ifft_1d_int64(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10).astype(numpy.int64), test_ifft_1d_int64=[NDArray[numpy.int64, :]])

    def test_ifft_1d_int32(self):
        self.run_test("def test_ifft_1d_int32(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10).astype(numpy.int32), test_ifft_1d_int32=[NDArray[numpy.int32, :]])

    def test_ifft_1d_int8(self):
        self.run_test("def test_ifft_1d_int8(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10).astype(numpy.int8), test_ifft_1d_int8=[NDArray[numpy.int8, :]])

    def test_ifft_1d_byte(self):
        self.run_test("def test_ifft_1d_byte(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(10).astype(numpy.int8), test_ifft_1d_byte=[NDArray[numpy.byte, :]])
        
    def test_ifft_1d_int64_axis(self):
        axs = [0, -1]
        for ax in axs:
            with self.subTest():
                self.run_test("def test_ifft_1d_int64_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", numpy.random.randn(10).astype(numpy.int64), ax, test_ifft_1d_int64_axis=[NDArray[numpy.int64, :], int])

    def test_ifft_1d_int64_n_None(self):
        self.run_test("def test_ifft_1d_int64_n_None(x): from numpy.fft import ifft ; return ifft(x, n=None)", numpy.random.randn(10).astype(numpy.int64), test_ifft_1d_int64_n_None=[NDArray[numpy.int64, :]])

    # check n set smaller, same and larger than axis
    def test_ifft_1d_int64_n(self):
        ns = [8, 10, 12]
        for n in ns:
            with self.subTest():
                self.run_test("def test_ifft_1d_int64_n(x, n): from numpy.fft import ifft ; return ifft(x, n)", numpy.random.randn(10).astype(numpy.int64), n, test_ifft_1d_int64_n=[NDArray[numpy.int64, :], int])

    def test_ifft_1d_int64_axis(self):
        self.run_test("def test_ifft_1d_int64_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", numpy.random.randn(10).astype(numpy.int64), 0, test_ifft_1d_int64_axis=[NDArray[numpy.int64, :], int])
        
    def test_ifft_1d_int64_norm(self):
        self.run_test("def test_ifft_1d_int64_norm(x, n): from numpy.fft import ifft ; return ifft(x, norm=n)", numpy.random.randn(10).astype(numpy.int64), "ortho", test_ifft_1d_int64_norm=[NDArray[numpy.int64, :], str])

    def test_ifft_1d_int64_norm_None(self):
        self.run_test("def test_ifft_1d_int64_norm_None(x): from numpy.fft import ifft ; return ifft(x, norm=None)", numpy.random.randn(10).astype(numpy.int64), test_ifft_1d_int64_norm_None=[NDArray[numpy.int64, :]])

    def test_ifft_1d_2(self):
        self.run_test("def test_ifft_1d_2(x): from numpy.fft import ifft ; return ifft(x)", numpy.random.randn(2**16)+1j*numpy.random.randn(2**16), test_ifft_1d_2=[NDArray[numpy.complex128, :]])

    def test_ifft_2d(self):
        szs  = [3, 5]
        for sz in szs:
            with self.subTest():
                self.run_test("def test_ifft_2d_2(x): from numpy.fft import ifft ; return ifft(x)", (numpy.random.randn(30)+1j*numpy.random.randn(30)).reshape(sz, -1), test_ifft_2d_2=[NDArray[numpy.complex128, :, :]])

    def test_ifft_2d_axis_n_norm(self):
        al = [0, 1, -1]
        nl = [3, 4, 5]
        norm = "ortho"
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_ifft_2d_axis_n_norm(x, a, n, norm): from numpy.fft import ifft ; return ifft(x, n=n, axis=a, norm=norm)", (numpy.random.randn(20)+1j*numpy.random.randn(20)).reshape(5, -1), a, n, norm, test_ifft_2d_axis_n_norm=[NDArray[numpy.complex128, :, :], int, int, str])

    def test_ifft_2d_f64_axis_n_norm(self):
        al = [0, 1, -1]
        nl = [3, 4, 5]
        norm = "ortho"
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_ifft_2d_f64_axis_n_norm(x, a, n, norm): from numpy.fft import ifft ; return ifft(x, n=n, axis=a, norm=norm)", numpy.random.randn(20).reshape(5, -1).copy(), a, n, norm, test_ifft_2d_f64_axis_n_norm=[NDArray[numpy.float64, :, :], int, int, str])

    def test_ifft_2d_int64_axis_n_norm(self):
        al = [0, 1, -1]
        nl = [3, 4, 5]
        norm = "ortho"
        for a in al:
            for n in nl:
                with self.subTest():
                    self.run_test("def test_ifft_2d_int64_axis_n_norm(x, a, n, norm): from numpy.fft import ifft ; return ifft(x, n=n, axis=a, norm=norm)", (numpy.random.randn(20)).astype(numpy.int64).reshape(5, -1).copy(), a, n, norm, test_ifft_2d_int64_axis_n_norm=[NDArray[numpy.int64, :, :], int, int, str])
    # 3D
    def test_ifft_3d(self):
        szs  = [(5, 4, -1), (4, 5, -1)]
        for sz in szs:
            with self.subTest():
                self.run_test("def test_ifft_3d(x): from numpy.fft import ifft ; return ifft(x)", (numpy.random.randn(200)+1j*numpy.random.randn(200)).reshape(sz).copy(), test_ifft_3d=[NDArray[numpy.complex128, :, :, :]])
                
    def test_ifft_3d_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_ifft_3d_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", (numpy.random.randn(200)+1j*numpy.random.randn(200)).reshape(sz), a, test_ifft_3d_axis=[NDArray[numpy.complex128, :, :, :], int])

    def test_ifft_3d_f64_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_ifft_3d_f64_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", (numpy.random.randn(200)).reshape(sz), a, test_ifft_3d_f64_axis=[NDArray[numpy.float64, :, :, :], int])

    def test_ifft_3d_int64_axis(self):
        al = [0, 1, 2, -1]
        szs  = [(5, 4, -1), (4, 5, -1)]
        for a in al:
            for sz in szs:
                with self.subTest():
                    self.run_test("def test_ifft_3d_int64_axis(x, a): from numpy.fft import ifft ; return ifft(x, axis=a)", (numpy.random.randn(200)).reshape(sz).astype(numpy.int64), a, test_ifft_3d_int64_axis=[NDArray[numpy.int64, :, :, :], int])

    def test_ifft_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_ifft_parallel(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)+1j*numpy.random.randn(512)).reshape((4,128)), test_ifft_parallel=[NDArray[numpy.complex128, :, :]])
        
    def test_ifft_f64_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_ifft_f64_parallel(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)).reshape((4,128)), test_ifft_f64_parallel=[NDArray[numpy.float64, :, :]])

    def test_ifft_int64_parallel(self):
        import numpy
        self.run_test("""
        import numpy as np
        def test_ifft_int64_parallel(x):
            out = [np.empty_like(x) for i in range(20)]
            #omp parallel for
            for ii in range(20):
                out[ii] = np.fft.fft(x)
            return np.concatenate(out)
        """, (numpy.random.randn(512)).reshape((4,128)).astype(numpy.int64), test_ifft_int64_parallel=[NDArray[numpy.int64, :, :]])

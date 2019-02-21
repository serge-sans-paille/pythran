import unittest
from pythran.tests import TestEnv
import numpy
from pythran.typing import NDArray


@TestEnv.module
class TestNumpyFFT(TestEnv):

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

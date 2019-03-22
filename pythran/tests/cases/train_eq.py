import numpy as np
#runas import numpy as np; np.random.seed(0); s=np.array([1+1j, -1+1j, -1-1j, 1-1j]); e=np.random.choice(s, (1, 100)); ee=e/np.sqrt(np.mean(abs(e)**2)); eee=ee+0.02*(np.random.randn(*ee.shape)+1j*np.random.randn(*ee.shape)); r=(np.sqrt(2)/2+0j);wx=np.zeros((1,10), dtype=eee.dtype); wx[:,4]=1; train_eq(eee.astype(np.complex64), eee.shape[1]-15, 1, np.float32(1e-3), wx.astype(np.complex64), (np.complex64(r),s.astype(np.complex64)), False)

#runas import numpy as np; np.random.seed(0); s=np.array([1+1j, -1+1j, -1-1j, 1-1j]); e=np.random.choice(s, (1, 100)); ee=e/np.sqrt(np.mean(abs(e)**2)); eee=ee+0.02*(np.random.randn(*ee.shape)+1j*np.random.randn(*ee.shape)); r=(np.sqrt(2)/2+0j);wx=np.zeros((1,10), dtype=eee.dtype); wx[:,4]=1; train_eq2(eee.astype(np.complex64), eee.shape[1]-15, 1, np.float32(1e-3), wx.astype(np.complex64), (np.complex64(r),s.astype(np.complex64)), False)

#pythran export train_eq(complex64[][], int, int, float32,
        # complex64[][],
        # (complex64, complex64[]), bool)
#pythran export train_eq2(complex64[][], int, int, float32,
        # complex64[][],
        # (complex64, complex64[]), bool)
def train_eq(E, TrSyms, os, mu, wx,  errfctprs, adapt):
    Ntaps = wx.shape[1]
    pols = wx.shape[0]
    R, symbs = errfctprs
    err = np.zeros(TrSyms, dtype=E.dtype)
    for i in range(TrSyms):
        X = E[:, i * os:i * os + Ntaps]
        Xest = np.sum(np.conj(wx) * X)
        err[i] = (R.real - abs(Xest)**2)*Xest
        wx += mu*np.conj(err[i])*X
        if adapt and i>0:
            if err[i].real*err[i-1].real > 0 and err[i].imag*err[i-1].imag > 0:
                mu = mu
            else:
                mu = np.float32(mu/(1+mu*(err[i].real*err[i].real + err[i].imag*err[i].imag)))
    return err, wx, mu

def train_eq2(E, TrSyms, os, mu, wx,  errfctprs, adapt):
    Ntaps = wx.shape[1]
    pols = wx.shape[0]
    R, symbs = errfctprs
    err = np.zeros(TrSyms, dtype=E.dtype)
    for i in range(TrSyms):
        X = E[:, i * os:i * os + Ntaps]
        Xest = np.sum(np.conj(wx) * X)
        err[i] = (R.real - abs(Xest)**2)*Xest
        wx += mu*np.conj(err[i])*X
        if adapt and i>0:
            if err[i].real*err[i-1].real > 0 and err[i].imag*err[i-1].imag > 0:
                mu = mu
            else:
                mu = np.float32(mu/(1+mu*(err[i].real*err[i].real + err[i].imag*err[i].imag)))
    return err, wx, mu

def cma_error(Xest, R, symbs):
    return (R.real - abs(Xest)**2)*Xest

def mcma_error(Xest, R, symbs):
    return symbs.dtype.type((R.real - Xest.real**2)*Xest.real + (R.imag - Xest.imag**2)*Xest.imag*1j)

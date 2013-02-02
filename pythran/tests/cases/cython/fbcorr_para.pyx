import numpy as np
cimport numpy as np
cimport cython
from cython.parallel import parallel, prange

DTYPE = np.float
ctypedef np.float_t DTYPE_t

@cython.boundscheck(False)
def fbcorr_para(np.ndarray[DTYPE_t, ndim=4, negative_indices=False] imgs,np.ndarray[DTYPE_t, ndim=4, negative_indices=False] filters):
    cdef int n_imgs = imgs.shape[0], n_rows = imgs.shape[1], n_cols = imgs.shape[2], n_channels = imgs.shape[3]
    cdef int n_filters = filters.shape[0], height = filters.shape[1], width = filters.shape[2], n_ch2 = filters.shape[3]
    cdef int ii, rr, cc, hh, ww, jj, ff
    cdef float imgval, filterval, tmp
    cdef np.ndarray[DTYPE_t, ndim=4, negative_indices=False] output = np.zeros((n_imgs, n_filters, n_rows - height + 1, n_cols - width + 1))
    with nogil, parallel():
        for ii in prange(n_imgs):
            for rr in xrange(n_rows - height + 1):
                for cc in xrange(n_cols - width + 1):
                    for ff in xrange(n_filters):
                        for hh in xrange(height):
                            for ww in xrange(width):
                                for jj in xrange(n_channels):
                                    imgval = imgs[ii,rr + hh,cc + ww,jj]
                                    filterval = filters[ff,hh,ww,jj]
                                    output[ii,ff,rr,cc] = output[ii,ff,rr,cc] + imgval * filterval

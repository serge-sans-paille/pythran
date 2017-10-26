# from https://github.com/numba/numba/blob/master/examples/fbcorr.py
#pythran export fbcorr(float [] [] [] [], float [] [] [] [])
#runas from random import random ; imgs = [ [ [ [ random() for i in xrange(3) ] for j in xrange(32) ] for j in xrange(32) ] for k in xrange(32) ] ; filt = [ [ [ [ random() for i in xrange(3) ] for j in xrange(5) ] for j in xrange(5) ] for k in xrange(6) ] ; import numpy as np ; imgs = np.array(imgs) ; filt = np.array(filt) ; fbcorr(imgs, filt)

import numpy
def fbcorr(imgs, filters):
    n_imgs, n_rows, n_cols, n_channels = imgs.shape
    n_filters, height, width, n_ch2 = filters.shape
    output = numpy.zeros((n_imgs, n_filters, (n_rows - height + 1),(n_cols - width + 1)))
    "omp parallel for private(rr,cc,hh,ww,jj,ff,imgval, filterval)"
    for ii in xrange(n_imgs):
        for rr in xrange(n_rows - height + 1):
            for cc in xrange(n_cols - width + 1):
                for hh in xrange(height):
                    for ww in xrange(width):
                        for jj in xrange(n_channels):
                            for ff in xrange(n_filters):
                                imgval = imgs[ii,rr + hh,cc + ww,jj]
                                filterval = filters[ff,hh,ww,jj]
                                output[ii,ff,rr,cc] += imgval * filterval
    return output

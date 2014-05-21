"""
This file demonstrates a filterbank correlation loop.
"""

#pythran export fbcorr(float[][][][], float[][][][], float[][][][])
#bench import numpy; in_ = numpy.arange(10*20*30*7.).reshape(10,20,30,7); filter = numpy.arange(2*3*4*7.).reshape(2,3,4,7); out = numpy.empty((10,2,18,27), dtype=numpy.float); fbcorr(in_, filter, out)
def fbcorr(imgs, filters, output):
    n_imgs, n_rows, n_cols, n_channels = imgs.shape
    n_filters, height, width, n_ch2 = filters.shape

    "omp parallel for"
    for ii in range(n_imgs):
        for rr in range(n_rows - height + 1):
            for cc in range(n_cols - width + 1):
                for hh in xrange(height):
                    for ww in xrange(width):
                        for jj in range(n_channels):
                            for ff in range(n_filters):
                                imgval = imgs[ii, rr + hh, cc + ww, jj]
                                filterval = filters[ff, hh, ww, jj]
                                output[ii, ff, rr, cc] += imgval * filterval


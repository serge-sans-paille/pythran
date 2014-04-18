# from https://github.com/numba/numba/blob/master/examples/fbcorr.py
#pythran export fbcorr(float list list list list, float list list list list)
#runas imgs = [ [ [ [ i+j+k for i in xrange(3) ] for j in xrange(16) ] for j in xrange(16) ] for k in xrange(16) ]; filters = [ [ [ [ i+2*j-k for i in xrange(3) ] for j in xrange(5) ] for j in xrange(5) ] for k in xrange(6) ] ; fbcorr(imgs, filters)
#bench imgs = [ [ [ [ i+j+k for i in xrange(11) ] for j in xrange(16) ] for j in xrange(16) ] for k in xrange(16) ]; filters = [ [ [ [ i+2*j-k for i in xrange(11) ] for j in xrange(5) ] for j in xrange(5) ] for k in xrange(6) ] ; fbcorr(imgs, filters)

def fbcorr(imgs, filters):
    n_imgs, n_rows, n_cols, n_channels = (len(imgs), len(imgs[0]), len(imgs[0][0]), len(imgs[0][0][0]))
    n_filters, height, width, n_ch2 = (len(filters), len(filters[0]), len(filters[0][0]), len(filters[0][0][0]))
    output = [ [ [ [ 0 for i in xrange(n_cols - width + 1) ] for j in xrange(n_rows - height + 1) ] for k in xrange(n_filters) ] for l in xrange(n_imgs) ]
    for ii in xrange(n_imgs):
        for rr in xrange(n_rows - height + 1):
            for cc in xrange(n_cols - width + 1):
                for hh in xrange(height):
                    for ww in xrange(width):
                        for jj in xrange(n_channels):
                            for ff in xrange(n_filters):
                                imgval = imgs[ii][rr + hh][cc + ww][jj]
                                filterval = filters[ff][hh][ww][jj]
                                output[ii][ff][rr][cc] += imgval * filterval
    return output

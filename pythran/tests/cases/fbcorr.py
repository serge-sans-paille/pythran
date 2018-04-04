# from https://github.com/numba/numba/blob/master/examples/fbcorr.py
#pythran export fbcorr(float list list list list, float list list list list)
#pythran export fbcorr(int list list list list, int list list list list)
#runas imgs = [ [ [ [ i+j+k for i in range(3) ] for j in range(16) ] for j in range(16) ] for k in range(16) ]; filters = [ [ [ [ i+2*j-k for i in range(3) ] for j in range(5) ] for j in range(5) ] for k in range(6) ] ; fbcorr(imgs, filters)
#bench imgs = [ [ [ [ i+j+k for i in range(11) ] for j in range(16) ] for j in range(16) ] for k in range(16) ]; filters = [ [ [ [ i+2*j-k for i in range(11) ] for j in range(5) ] for j in range(5) ] for k in range(6) ] ; fbcorr(imgs, filters)

def fbcorr(imgs, filters):
    n_imgs, n_rows, n_cols, n_channels = (len(imgs), len(imgs[0]), len(imgs[0][0]), len(imgs[0][0][0]))
    n_filters, height, width, n_ch2 = (len(filters), len(filters[0]), len(filters[0][0]), len(filters[0][0][0]))
    output = [ [ [ [ 0 for i in range(n_cols - width + 1) ] for j in range(n_rows - height + 1) ] for k in range(n_filters) ] for l in range(n_imgs) ]
    for ii in range(n_imgs):
        for rr in range(n_rows - height + 1):
            for cc in range(n_cols - width + 1):
                for hh in range(height):
                    for ww in range(width):
                        for jj in range(n_channels):
                            for ff in range(n_filters):
                                imgval = imgs[ii][rr + hh][cc + ww][jj]
                                filterval = filters[ff][hh][ww][jj]
                                output[ii][ff][rr][cc] += imgval * filterval
    return output

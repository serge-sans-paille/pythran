#runas: import numpy as np ; N = 500 ; X = np.random.randn(N,N,3); laplacien(X)
#pythran export laplacien(float64[][][3])

import numpy as np
def laplacien(image):
    out_image = np.abs(4*image[1:-1,1:-1] -
                                   image[0:-2,1:-1] - image[2:,1:-1] -
                                   image[1:-1,0:-2] - image[1:-1,2:])
    valmax = np.max(out_image)
    valmax = max(1.,valmax)+1.E-9
    out_image /= valmax
    return out_image

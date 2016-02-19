#runas import numpy as np; n = 20; a = np.arange(n*n*n).reshape((n,n,n)).astype(np.uint8); b = 2. ; goodExpoMeasure(a, b)
#pythran export goodExpoMeasure(uint8[][][], float)
import numpy
def goodExpoMeasure(inRGB, sigma):
    '''
    Compute the good exposition image quality measure on 1 input image.
    '''
    R = inRGB[0,:,:].astype(numpy.float)
    G = inRGB[1,:,:].astype(numpy.float)
    B = inRGB[2,:,:].astype(numpy.float)
    goodExpoR = numpy.exp(- ((R - 128)**2) / sigma)
    goodExpoG = numpy.exp(- ((G - 128)**2) / sigma)
    goodExpoB = numpy.exp(- ((B - 128)**2) / sigma)
    goodExpo  = goodExpoR * goodExpoG * goodExpoB
    goodExpo  = (numpy.round(goodExpo, 2) * (2**8-1)).astype(numpy.uint8)

    return goodExpo

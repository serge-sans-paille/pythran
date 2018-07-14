"""Color Mixer

NumPy does not do overflow checking when adding or multiplying
integers, so currently the only way to clip results efficiently
(without making copies of the data) is with an extension such as this
one.

"""

import numpy as np

# pythran export add(uint8[:,:,:], uint8[:,:,:], int, int)
# pythran export multiply(uint8[:,:,:], uint8[:,:,:], int, float)
# pythran export brightness(uint8[:,:,:], uint8[:,:,:], float, int)
# pythran export sigmoid_gamma(uint8[:,:,:], uint8[:,:,:], float, float)
# pythran export gamma(uint8[:,:,:], uint8[:,:,:], float)
# pythran export py_hsv_2_rgb(float, float, float)
# pythran export py_rgb_2_hsv(int, int, int)
# pythran export hsv_add (uint8[:,:,:], uint8[:,:,:], float, float, float)


def add(img, stateimg, channel, amount):
    """Add a given amount to a color channel of `stateimg`, and
    store the result in `img`.  Overflow is clipped.

    Parameters
    ----------
    img : (M, N, 3) ndarray of uint8
        Output image.
    stateimg : (M, N, 3) ndarray of uint8
        Input image.
    channel : int
        Channel (0 for "red", 1 for "green", 2 for "blue").
    amount : int
        Value to add.

    """
    height, width, _ = img.shape
    k = channel
    n = amount

    lut = [np.uint8()] * 256

    for l in range(256):
        op_result = l + n
        if op_result > 255:
            op_result = 255
        elif op_result < 0:
            op_result = 0

        lut[l] = np.uint8(op_result)

    for i in range(height):
        for j in range(width):
            img[i, j, k] = lut[stateimg[i, j, k]]


def multiply(img, stateimg, channel, amount):
    """Multiply a color channel of `stateimg` by a certain amount, and
    store the result in `img`.  Overflow is clipped.

    Parameters
    ----------
    img : (M, N, 3) ndarray of uint8
        Output image.
    stateimg : (M, N, 3) ndarray of uint8
        Input image.
    channel : int
        Channel (0 for "red", 1 for "green", 2 for "blue").
    amount : float
        Multiplication factor.

    """
    height, width, _ = img.shape
    k = channel
    n = amount

    lut = [np.uint8()] * 256

    for l in range(256):
        op_result = l * n
        if op_result > 255:
            op_result = 255
        elif op_result < 0:
            op_result = 0

        lut[l] = np.uint8(op_result)

    for i in range(height):
        for j in range(width):
            img[i, j, k] = lut[stateimg[i, j, k]]


def brightness(img, stateimg, factor, offset):
    """Modify the brightness of an image.
    'factor' is multiplied to all channels, which are
    then added by 'amount'. Overflow is clipped.

    Parameters
    ----------
    img : (M, N, 3) ndarray of uint8
        Output image.
    stateimg : (M, N, 3) ndarray of uint8
        Input image.
    factor : float
        Multiplication factor.
    offset : int
        Ammount to add to each channel.

    """

    height, width, _ = img.shape

    lut = [np.uint8()] * 256

    for k in range(256):
        op_result = k * factor + offset
        if op_result > 255:
            op_result = 255
        elif op_result < 0:
            op_result = 0

        lut[k] = np.uint8(op_result)

    for i in range(height):
        for j in range(width):
            img[i, j, 0] = lut[stateimg[i, j, 0]]
            img[i, j, 1] = lut[stateimg[i, j, 1]]
            img[i, j, 2] = lut[stateimg[i, j, 2]]


def sigmoid_gamma(img,
                  stateimg,
                  alpha, beta):

    height, width, _ = img.shape

    c1 = 1 / (1 + np.exp(beta))
    c2 = 1 / (1 + np.exp(beta - alpha)) - c1

    lut = [np.uint8()] * 256

    # compute the lut
    for k in range(256):
        lut[k] = np.uint8(((1 / (1 + np.exp(beta - (k / 255.) * alpha)))
                           - c1) * 255 / c2)
    for i in range(height):
        for j in range(width):
            img[i, j, 0] = lut[stateimg[i, j, 0]]
            img[i, j, 1] = lut[stateimg[i, j, 1]]
            img[i, j, 2] = lut[stateimg[i, j, 2]]


def gamma(img,
          stateimg,
          gamma):

    height, width, _ = img.shape

    lut = [np.uint8()] * 256

    if gamma == 0:
        gamma = 0.00000000000000000001
    gamma = 1./gamma

    # compute the lut
    for k in range(256):
        lut[k] = np.uint8((pow((k / 255.), gamma) * 255))

    for i in range(height):
        for j in range(width):
            img[i, j, 0] = lut[stateimg[i, j, 0]]
            img[i, j, 1] = lut[stateimg[i, j, 1]]
            img[i, j, 2] = lut[stateimg[i, j, 2]]


def rgb_2_hsv(RGB, HSV):
    R, G, B = RGB

    if R > 255:
        R = 255
    elif R < 0:
        R = 0

    if G > 255:
        G = 255
    elif G < 0:
        G = 0

    if B > 255:
        B = 255
    elif B < 0:
        B = 0

    if R < G:
        MIN = R
        MAX = G
    else:
        MIN = G
        MAX = R

    if B < MIN:
        MIN = B
    elif B > MAX:
        MAX = B
    else:
        pass

    V = MAX / 255.

    if MAX == MIN:
        H = 0.
    elif MAX == R:
        H = (60 * (G - B) / (MAX - MIN) + 360) % 360
    elif MAX == G:
        H = 60 * (B - R) / (MAX - MIN) + 120
    else:
        H = 60 * (R - G) / (MAX - MIN) + 240

    if MAX == 0:
        S = 0
    else:
        S = 1 - MIN / MAX

    HSV[0] = H
    HSV[1] = S
    HSV[2] = V


def hsv_2_rgb(HSV, RGB):

    H, S, V = HSV

    if H > 360:
        H = H % 360
    elif H < 0:
        H = 360 - ((-1 * H) % 360)
    else:
        pass

    if S > 1:
        S = 1
    elif S < 0:
        S = 0
    else:
        pass

    if V > 1:
        V = 1
    elif V < 0:
        V = 0
    else:
        pass

    hi = int(H / 60.) % 6
    f = (H / 60.) - int(H / 60.)
    p = V * (1 - S)
    q = V * (1 - f * S)
    t = V * (1 - (1 - f) * S)

    if hi == 0:
        r = V
        g = t
        b = p
    elif hi == 1:
        r = q
        g = V
        b = p
    elif hi == 2:
        r = p
        g = V
        b = t
    elif hi == 3:
        r = p
        g = q
        b = V
    elif hi == 4:
        r = t
        g = p
        b = V
    else:
        r = V
        g = p
        b = q

    RGB[0] = r
    RGB[1] = g
    RGB[2] = b


def py_hsv_2_rgb(H, S, V):
    '''Convert an HSV value to RGB.

    Automatic clipping.

    Parameters
    ----------
    H : float
        From 0. - 360.
    S : float
        From 0. - 1.
    V : float
        From 0. - 1.

    Returns
    -------
    out : (R, G, B) ints
        Each from 0 - 255

    conversion convention from here:
    http://en.wikipedia.org/wiki/HSL_and_HSV

    '''

    HSV = [H, S, V]
    RGB = [0] * 3

    hsv_2_rgb(HSV, RGB)

    R = int(RGB[0] * 255)
    G = int(RGB[1] * 255)
    B = int(RGB[2] * 255)

    return R, G, B


def py_rgb_2_hsv(R, G, B):
    '''Convert an HSV value to RGB.

    Automatic clipping.

    Parameters
    ----------
    R : int
        From 0. - 255.
    G : int
        From 0. - 255.
    B : int
        From 0. - 255.

    Returns
    -------
    out : (H, S, V) floats
        Ranges (0...360), (0...1), (0...1)

    conversion convention from here:
    http://en.wikipedia.org/wiki/HSL_and_HSV

    '''
    RGB = [float(R), float(G), float(B)]
    HSV = [0.] * 3

    rgb_2_hsv(RGB, HSV)

    return HSV


def hsv_add(img, stateimg, h_amt, s_amt, v_amt):
    """Modify the image color by specifying additive HSV Values.

    Since the underlying images are RGB, all three values HSV
    must be specified at the same time.

    The RGB triplet in the image is converted to HSV, the operation
    is applied, and then the HSV triplet is converted back to RGB

    HSV values are scaled to H(0. - 360.), S(0. - 1.), V(0. - 1.)
    then the operation is performed and any overflow is clipped, then the
    reverse transform is performed. Those are the ranges to keep in mind,
    when passing in values.

    Parameters
    ----------
    img : (M, N, 3) ndarray of uint8
        Output image.
    stateimg : (M, N, 3) ndarray of uint8
        Input image.
    h_amt : float
        Ammount to add to H channel.
    s_amt : float
        Ammount to add to S channel.
    v_amt : float
        Ammount to add to V channel.


    """

    height, width, _ = img.shape

    HSV = [0.] * 3
    RGB = [0.] * 3

    for i in range(height):
        for j in range(width):
            RGB[0] = stateimg[i, j, 0]
            RGB[1] = stateimg[i, j, 1]
            RGB[2] = stateimg[i, j, 2]

            rgb_2_hsv(RGB, HSV)

            # Add operation
            HSV[0] += h_amt
            HSV[1] += s_amt
            HSV[2] += v_amt

            hsv_2_rgb(HSV, RGB)

            RGB[0] *= 255
            RGB[1] *= 255
            RGB[2] *= 255

            img[i, j, 0] = RGB[0]
            img[i, j, 1] = RGB[1]
            img[i, j, 2] = RGB[2]


# pythran export hsv_multiply(uint8[:,:,:], uint8[:,:,:], float, float, float)
def hsv_multiply(img,
                 stateimg,
                 h_amt, s_amt, v_amt):
    """Modify the image color by specifying multiplicative HSV Values.

    Since the underlying images are RGB, all three values HSV
    must be specified at the same time.

    The RGB triplet in the image is converted to HSV, the operation
    is applied, and then the HSV triplet is converted back to RGB

    HSV values are scaled to H(0. - 360.), S(0. - 1.), V(0. - 1.)
    then the operation is performed and any overflow is clipped, then the
    reverse transform is performed. Those are the ranges to keep in mind,
    when passing in values.

    Note that since hue is in degrees, it makes no sense to multiply
    that channel, thus an add operation is performed on the hue. And the
    values given for h_amt, should be the same as for hsv_add

    Parameters
    ----------
    img : (M, N, 3) ndarray of uint8
        Output image.
    stateimg : (M, N, 3) ndarray of uint8
        Input image.
    h_amt : float
        Ammount to add to H channel.
    s_amt : float
        Ammount by which to multiply S channel.
    v_amt : float
        Ammount by which to multiply V channel.


    """

    height, width, _ = img.shape

    HSV = [0.] * 3
    RGB = [0.] * 3

    for i in range(height):
        for j in range(width):
            RGB[0] = stateimg[i, j, 0]
            RGB[1] = stateimg[i, j, 1]
            RGB[2] = stateimg[i, j, 2]

            rgb_2_hsv(RGB, HSV)

            # Multiply operation
            HSV[0] += h_amt
            HSV[1] *= s_amt
            HSV[2] *= v_amt

            hsv_2_rgb(HSV, RGB)

            RGB[0] *= 255
            RGB[1] *= 255
            RGB[2] *= 255

            img[i, j, 0] = RGB[0]
            img[i, j, 1] = RGB[1]
            img[i, j, 2] = RGB[2]

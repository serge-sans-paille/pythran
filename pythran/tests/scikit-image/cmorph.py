import numpy as np

# pythran export _dilate(uint8[:, :], uint8[:, :], uint8[:, :], int8, int8)
# pythran export _dilate(uint8[:, :], uint8[:, :], uint8[:, :], int8)
# pythran export _dilate(uint8[:, :], uint8[:, :], uint8[:, :])
# pythran export _dilate(uint8[:, :], uint8[:, :])


def _dilate(image, selem, out=None, shift_x=0, shift_y=0):
    """Return greyscale morphological dilation of an image.

    Morphological dilation sets a pixel at (i,j) to the maximum over all pixels
    in the neighborhood centered at (i,j). Dilation enlarges bright regions
    and shrinks dark regions.

    Parameters
    ----------

    image : ndarray
        Image array.
    selem : ndarray
        The neighborhood expressed as a 2-D array of 1's and 0's.
    out : ndarray
        The array to store the result of the morphology. If None, is
        passed, a new array will be allocated.
    shift_x, shift_y : bool
        shift structuring element about center point. This only affects
        eccentric structuring elements (i.e. selem with even numbered sides).

    Returns
    -------
    dilated : uint8 array
        The result of the morphological dilation.
    """

    rows = image.shape[0]
    cols = image.shape[1]
    srows = selem.shape[0]
    scols = selem.shape[1]

    centre_r = int(selem.shape[0] / 2) - shift_y
    centre_c = int(selem.shape[1] / 2) - shift_x

    image = np.ascontiguousarray(image)
    if out is None:
        out = np.zeros((rows, cols), dtype=np.uint8)

    selem_num = np.sum(np.asarray(selem) != 0)
    sr = np.empty(selem_num, dtype=np.intp)
    sc = np.empty(selem_num, dtype=np.intp)

    s = 0
    for r in range(srows):
        for c in range(scols):
            if selem[r, c] != 0:
                sr[s] = r - centre_r
                sc[s] = c - centre_c
                s += 1

    for r in range(rows):
        for c in range(cols):
            local_max = 0
            for s in range(selem_num):
                rr = r + sr[s]
                cc = c + sc[s]
                if 0 <= rr < rows and 0 <= cc < cols:
                    value = image[rr, cc]
                    if value > local_max:
                        local_max = value

            out[r, c] = local_max

    return np.asarray(out)


# pythran export _erode(uint8[:, :], uint8[:, :], uint8[:, :], int8, int8)
# pythran export _erode(uint8[:, :], uint8[:, :], uint8[:, :], int8)
# pythran export _erode(uint8[:, :], uint8[:, :], uint8[:, :])
# pythran export _erode(uint8[:, :], uint8[:, :])


def _erode(image, selem, out=None, shift_x=0, shift_y=0):
    """Return greyscale morphological erosion of an image.

    Morphological erosion sets a pixel at (i,j) to the minimum over all pixels
    in the neighborhood centered at (i,j). Erosion shrinks bright regions and
    enlarges dark regions.

    Parameters
    ----------
    image : ndarray
        Image array.
    selem : ndarray
        The neighborhood expressed as a 2-D array of 1's and 0's.
    out : ndarray
        The array to store the result of the morphology. If None is
        passed, a new array will be allocated.
    shift_x, shift_y : bool
        shift structuring element about center point. This only affects
        eccentric structuring elements (i.e. selem with even numbered sides).

    Returns
    -------
    eroded : uint8 array
        The result of the morphological erosion.
    """

    rows = image.shape[0]
    cols = image.shape[1]
    srows = selem.shape[0]
    scols = selem.shape[1]

    centre_r = int(selem.shape[0] / 2) - shift_y
    centre_c = int(selem.shape[1] / 2) - shift_x

    image = np.ascontiguousarray(image)
    if out is None:
        out = np.zeros((rows, cols), dtype=np.uint8)

    selem_num = np.sum(np.asarray(selem) != 0)
    sr = np.empty(selem_num, dtype=np.intp)
    sc = np.empty(selem_num, dtype=np.intp)

    s = 0
    for r in range(srows):
        for c in range(scols):
            if selem[r, c] != 0:
                sr[s] = r - centre_r
                sc[s] = c - centre_c
                s += 1

    for r in range(rows):
        for c in range(cols):
            local_min = 255
            for s in range(selem_num):
                rr = r + sr[s]
                cc = c + sc[s]
                if 0 <= rr < rows and 0 <= cc < cols:
                    value = image[rr, cc]
                    if value < local_min:
                        local_min = value

            out[r, c] = local_min

    return np.asarray(out)

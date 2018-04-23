#pythran export match_arrays (float32[], float32[])
#pythran export match_arrays (int16[], int16[])
#runas import numpy as np; x = np.array([1,2,3], dtype=np.int16); y = np.array([3,4,5], dtype=np.int16); match_arrays(x, y)
import numpy as np
def match_arrays(a, b):    # pragma: no cover
    """
    Finds all indexes into a and b such that a[i] = b[j]. The outputs are sorted
    in lexographical order.

    Parameters
    ----------
    a, b : np.ndarray
        The input 1-D arrays to match. If matching of multiple fields is
        needed, use np.recarrays. These two arrays must be sorted.

    Returns
    -------
    a_idx, b_idx : np.ndarray
        The output indices of every possible pair of matching elements.
    """
    if len(a) == 0 or len(b) == 0:
        return np.empty(0, dtype=np.uintp), np.empty(0, dtype=np.uintp)

    a_ind, b_ind = [], []
    nb = len(b)
    ib = 0
    match = 0

    for ia, j in enumerate(a):
        if j == b[match]:
            ib = match

        while ib < nb and j >= b[ib]:
            if j == b[ib]:
                a_ind.append(ia)
                b_ind.append(ib)

                if b[match] < b[ib]:
                    match = ib

            ib += 1

    return np.array(a_ind, dtype=np.uintp), np.array(b_ind, dtype=np.uintp)

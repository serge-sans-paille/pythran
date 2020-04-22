#pythran export _integ(uint8[:,:], int, int, int, int)
import numpy as np

def _clip(x, low, high):
    assert 0 <= low <= high
    if x > high:
        return high
    if x < low:
        return low
    return x

def _integ(img, r, c, rl, cl):
    r = _clip(r, 0, img.shape[0] - 1)
    c = _clip(c, 0, img.shape[1] - 1)

    r2 = _clip(r + rl, 0, img.shape[0] - 1)
    c2 = _clip(c + cl, 0, img.shape[1] - 1)

    ans = img[r, c] + img[r2, c2] - img[r, c2] - img[r2, c]
    return max(0, ans)


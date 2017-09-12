import numpy as np
#runas import numpy as np; x = np.ones(10) * 80000 ; tax(x)
#pythran export tax(float[])
def tax(d):
    tax_seg1 = d[(d > 256303)] * 0.45 - 16164.53
    tax_seg2 = d[(d > 54057) & (d <= 256303)] * 0.42 - 8475.44
    seg3 = d[(d > 13769) & (d <= 54057)] - 13769
    seg4 = d[(d > 8820) & (d <= 13769)] - 8820
    prog_seg3 = seg3 * 0.0000022376 + 0.2397
    prog_seg4 = seg4 * 0.0000100727 + 0.14
    return (
        np.sum(tax_seg1) +
        np.sum(tax_seg2) +
        np.sum(seg3 * prog_seg3 + 939.57) +
        np.sum(seg4 * prog_seg4)
    ) / np.sum(d)

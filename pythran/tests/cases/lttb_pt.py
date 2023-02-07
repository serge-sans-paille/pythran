"""Downsample data using the Largest-Triangle-Three-Buckets algorithm.

Translated for Pythran from https://git.sr.ht/~javiljoen/lttb-numpy
which is Copyright (c) 2020, JA Viljoen, MIT license.

Reference
---------
Sveinn Steinarsson. 2013. Downsampling Time Series for Visual
Representation. MSc thesis. University of Iceland.
"""

#runas import numpy as np; tseries = np.arange(200.).reshape(100, 2); downsample(tseries, 8)

import numpy as np

def _areas_of_triangles(a, bs, c):
    bs_minus_a = bs - a
    a_minus_bs = a - bs
    return 0.5 * abs(
        (a[0] - c[0]) * (bs_minus_a[:, 1]) - (a_minus_bs[:, 0]) * (c[1] - a[1])
    )


#pythran export downsample(float[:, :] order(C), int)
def downsample(data, n_out):
    if n_out > data.shape[0]:
        raise ValueError("n_out must be <= number of rows in data")

    if n_out == data.shape[0]:
        return data

    if n_out < 3:
        raise ValueError("Can only downsample to a minimum of 3 points")

    # Split data into bins
    n_bins = n_out - 2
    data_bins = np.array_split(data[1 : len(data) - 1], n_bins)

    # Prepare output array
    # First and last points are the same as in the input.
    out = np.zeros((n_out, 2))
    out[0] = data[0]
    out[len(out) - 1] = data[len(data) - 1]

    # Largest Triangle Three Buckets (LTTB):
    # In each bin, find the point that makes the largest triangle
    # with the point saved in the previous bin
    # and the centroid of the points in the next bin.
    for i in range(len(data_bins)):
        this_bin = data_bins[i]

        if i < n_bins - 1:
            next_bin = data_bins[i + 1]
        else:
            next_bin = data[len(data) - 1 :]

        a = out[i]
        bs = this_bin
        c = next_bin.mean(axis=0)

        areas = _areas_of_triangles(a, bs, c)
        out[i + 1] = bs[np.argmax(areas)]

    return out

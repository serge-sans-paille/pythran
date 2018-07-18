#pythran export histogram_neq_edges_weights(int32[][], int32[], int32[][])
#runas import numpy as np; d = np.arange(10, dtype=np.int32).reshape(5,2); w = np.ones_like(d, dtype=np.int32); b = np.arange(4,  dtype=np.int32); histogram_neq_edges_weights(d, b, w)

import numpy as np



def _histogram_neq_edges_weights(data, bin_edges, weights):
    _BLOCK = 65536

    bin_edges_length = (len(bin_edges) - 1)

    hist = np.zeros(len(bin_edges), weights.dtype)

    # omp parallel for private(j, tmp_hist, i, value, bin_idx)
    for j in range(0, len(data), _BLOCK):
        tmp_hist = np.zeros(len(bin_edges), weights.dtype)
        tmp_data = data[j:j + _BLOCK]
        tmp_weights = weights[j:j + _BLOCK]

        for i in range(0, len(tmp_data)):
            value = tmp_data[i]

            # Ignore data if NaN or not within range
            if np.isnan(value) or not (bin_edges[0] <= value <= bin_edges[-1]):
                continue

            # Search for index
            bin_idx = 0
            while bin_idx < bin_edges_length and bin_edges[bin_idx + 1] <= value:
                bin_idx += 1

            tmp_hist[bin_idx] += tmp_weights[i]

        # omp critical
        hist += tmp_hist

    # Last bin element is inclusive
    hist[-2] += hist[-1]

    # Remove the redundant extra bin
    return hist[:-1], bin_edges



def histogram_neq_edges_weights(data, bin_edges, weights):
    if weights.shape != data.shape:
        raise ValueError('weights should have the same shape as data.')
    weights = weights.ravel()

    data = data.ravel()
    return _histogram_neq_edges_weights(data, bin_edges, weights)



#pythran export weights(uint8[:,:],float?)
#runas import numpy as np; x = np.arange(10, dtype=np.uint8).reshape(5,2); weights(x)

import numpy as np
def weights(input_data, threshold=0.3):
    n_seq, length = input_data.shape
    weights = np.zeros(n_seq, dtype=np.float32)

    for i in range(n_seq):
        vector = input_data[i, None, :]
        count_matches = np.sum(vector == input_data, axis=1)
        over_threshold = count_matches > (threshold * length)
        total = np.sum(over_threshold)
        weights[i] = 1 / total

    return weights

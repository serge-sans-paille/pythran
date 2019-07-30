#pythran export next_pythagorean_triples(int64[:,:])
#runas import numpy as np; next_pythagorean_triples(np.array([[3, 4, 5]], dtype=np.int64))
import numpy as np
def next_pythagorean_triples(previous):
    matrices = np.array(
        [[-1, 2, 2],
         [-2, 1, 2],
         [-2, 2, 3],
         [1, 2, 2],
         [2, 1, 2],
         [2, 2, 3],
         [1, -2, 2],
         [2, -1, 2],
         [2, -2, 3]])

    next_triples = np.transpose(np.dot(matrices, np.transpose(previous)))
    next_triples = next_triples.reshape((3 * previous.shape[0], previous.shape[1]))
    return next_triples

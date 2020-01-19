#pythran export matrix_class_distance(float64[:,:], int[], float64[:,:], int)
#from https://stackoverflow.com/questions/59601987
#runas import numpy as np; n = 200;d = 10;iterations = 20;np.random.seed(42);dat = np.random.random((n, d));dat_filter = np.random.randint(0, n, size=n); dat_points = np.random.random((n, d)); matrix_class_distance(dat, dat_filter, dat_points, iterations)
import numpy as np
def matrix_class_distance(dat, dat_filter, dat_points, iterations):
    aggregation = 0
    for i in range(iterations):
        aggregation += np.sum(np.linalg.norm(dat[dat_filter==i] - dat_points[i], axis=1))
    return aggregation

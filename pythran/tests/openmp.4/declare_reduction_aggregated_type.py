import numpy as np
  
#pythran export declare_reduction_aggregated_type()
def declare_reduction_aggregated_type():
    return run(1000)

#omp declare reduction(+ : float[], int[] : omp_out += omp_in) initializer(omp_priv(np.empty_like(omp_orig)))

def run(n_bins):

    """
    Example of using openmp reduction to accelerate
    for loop
    """

    arr = np.zeros(n_bins)

    #omp parallel for reduction(+:arr)
    for i in range(10):
        for j in range(10):

            ij = i * 10 + j
            arr[int(ij % n_bins)] += 1

    return arr

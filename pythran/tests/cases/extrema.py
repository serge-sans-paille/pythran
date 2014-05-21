#runas run_extrema(10,[1.2,3.4,5.6,7.8,9.0,2.1,4.3,5.4,6.5,7.8])
#bench import random; n=3000000; a = [random.random() for i in xrange(n)]; run_extrema(n, a)
#pythran export run_extrema(int, float list)
def extrema_op(a, b):
    a_min_idx, a_min_val, a_max_idx, a_max_val = a
    b_min_idx, b_min_val, b_max_idx, b_max_val = b
    if a_min_val < b_min_val:
        if a_max_val > b_max_val:
            return a
        else:
            return a_min_idx, a_min_val, b_max_idx, b_max_val
    else:
        if a_max_val > b_max_val:
            return b_min_idx, b_min_val, a_max_idx, a_max_val
        else:
            return b

def extrema_id(x):
    return -1, 1., 1, 0.

def indices(A):
    return xrange(len(A))

def extrema(x, x_id):
    return reduce(extrema_op, zip(indices(x), x, indices(x), x), x_id)

def run_extrema(n,a):
    #import random
    #a = [random.random() for i in xrange(n)]

    a_id = extrema_id(0.)
    return extrema(a, a_id)

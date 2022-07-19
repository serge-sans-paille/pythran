# pythran export compute_increments_dim1(float64[:, :], int)

def compute_increments_dim1(var, irx):
    'Compute the increments of var over the dim 1.'
    n1 = var.shape[1]
    n1new = (n1 - irx)
    inc_var = (var[:, irx:n1] - var[:, 0:n1new])
    return inc_var


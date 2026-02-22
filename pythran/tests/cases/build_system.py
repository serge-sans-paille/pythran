#bench q = 100; n = 90; p = 110 ; r = 80; import numpy as np; x = 2 * np.ones((q,n)); y = 3 * np.ones((p,n)); powers = np.ones((r, n), dtype=int); build_system(x, y, powers, np)
#runas q = 100; n = 90; p = 110 ; r = 80; import numpy as np; x = 2 * np.ones((q,n)); y = 3 * np.ones((p,n)); powers = np.ones((r, n), dtype=int); build_system(x, y, powers, np)
import numpy as np

def thin_plate_spline(r, xp):
    return xp.where(r == 0, 0, r**2 * xp.log(r))


def _kernel_matrix_impl(x, y, kernel_func, xp):
    """Evaluate RBFs, with centerx at `y`, at `x`."""
    return kernel_func(
        xp.linalg.norm(x[None, :, :] - y[:, None, :], axis=-1), xp
    )

# pythran export build_system(float[:, :],
#                       float[:, :],
#                       int[:, :],
#                       numpy pkg)
def build_system(x, y, powers, xp):
    """Construct the coefficients needed to evaluate
    the RBF.

    Parameters
    ----------
    x : (Q, N) float ndarray
        Evaluation point coordinates.
    y : (P, N) float ndarray
        Data point coordinates.
    powers : (R, N) int ndarray
        The exponents for each monomial in the polynomial.
    xp

    Returns
    -------
    (Q, P + R) float ndarray

    """
    kernel_func = thin_plate_spline

    vec = xp.concatenate(
        [
            _kernel_matrix_impl(y, x, kernel_func, xp),
            xp.prod(x[:, None, :] ** powers, axis=-1)
        ], axis=-1
    )

    return vec

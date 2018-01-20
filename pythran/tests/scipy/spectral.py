# Author: Pim Schellart
# 2010 - 2011

"""Tools for spectral analysis of unequally sampled signals."""

import numpy as np
#pythran export lombscargle(float64[], float64[], float64[])
#runas import numpy; x = numpy.arange(2., 12.); y = numpy.arange(1., 11.); z = numpy.arange(3., 13.); lombscargle(x, y, z)

def lombscargle(x, y, freqs):
    """
    _lombscargle(x, y, freqs)

    Computes the Lomb-Scargle periodogram.
    
    Parameters
    ----------
    x : array_like
        Sample times.
    y : array_like
        Measurement values (must be registered so the mean is zero).
    freqs : array_like
        Angular frequencies for output periodogram.

    Returns
    -------
    pgram : array_like
        Lomb-Scargle periodogram.

    Raises
    ------
    ValueError
        If the input arrays `x` and `y` do not have the same shape.

    See also
    --------
    lombscargle

    """

    # Check input sizes
    if x.shape != y.shape:
        raise ValueError("Input arrays do not have the same size.")

    # Local variables
    c = np.cos(freqs[:, None] * x)
    s = np.sin(freqs[:, None] * x)
    xc = np.sum(y * c, axis=1)
    xs = np.sum(y * s, axis=1)
    cc = np.sum(c ** 2, axis=1)
    ss = np.sum(s * s, axis=1)
    cs = np.sum(c * s, axis=1)
    tau = np.arctan2(2 * cs, cc - ss) / (2 * freqs)
    c_tau = np.cos(freqs * tau)
    s_tau = np.sin(freqs * tau)
    c_tau2 = c_tau * c_tau
    s_tau2 = s_tau * s_tau
    cs_tau = 2 * c_tau * s_tau

    pgram = 0.5 * (((c_tau * xc + s_tau * xs)**2 / \
        (c_tau2 * cc + cs_tau * cs + s_tau2 * ss)) + \
        ((c_tau * xs - s_tau * xc)**2 / \
        (c_tau2 * ss - cs_tau * cs + s_tau2 * cc)))



    return pgram


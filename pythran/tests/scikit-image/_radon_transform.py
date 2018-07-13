import numpy as np
from numpy import cos, sin, floor, ceil, sqrt


def bilinear_ray_sum(image, theta, ray_position):
    """
    Compute the projection of an image along a ray.

    Parameters
    ----------
    image : 2D array, dtype=float
        Image to project.
    theta : float
        Angle of the projection
    ray_position : float
        Position of the ray within the projection

    Returns
    -------
    projected_value : float
        Ray sum along the projection
    norm_of_weights :
        A measure of how long the ray's path through the reconstruction
        circle was
    """
    theta = theta / 180. * np.pi
    radius = image.shape[0] // 2 - 1
    projection_center = image.shape[0] // 2
    rotation_center = image.shape[0] // 2
    # (s, t) is the (x, y) system rotated by theta
    t = ray_position - projection_center
    # s0 is the half-length of the ray's path in the reconstruction circle
    s0 = sqrt(radius * radius - t * t) if radius*radius >= t*t else 0.
    Ns = 2 * int(ceil(2 * s0))  # number of steps along the ray
    ray_sum = 0.
    weight_norm = 0.

    if Ns > 0:
        # step length between samples
        ds = 2 * s0 / Ns
        dx = -ds * cos(theta)
        dy = -ds * sin(theta)
        # point of entry of the ray into the reconstruction circle
        x0 = s0 * cos(theta) - t * sin(theta)
        y0 = s0 * sin(theta) + t * cos(theta)
        for k in range(Ns + 1):
            x = x0 + k * dx
            y = y0 + k * dy
            index_i = x + rotation_center
            index_j = y + rotation_center
            i = int(floor(index_i))
            j = int(floor(index_j))
            di = index_i - floor(index_i)
            dj = index_j - floor(index_j)
            # Use linear interpolation between values
            # Where values fall outside the array, assume zero
            if i > 0 and j > 0:
                weight = (1. - di) * (1. - dj) * ds
                ray_sum += weight * image[i, j]
                weight_norm += weight * weight
            if i > 0 and j < image.shape[1] - 1:
                weight = (1. - di) * dj * ds
                ray_sum += weight * image[i, j+1]
                weight_norm += weight * weight
            if i < image.shape[0] - 1 and j > 0:
                weight = di * (1 - dj) * ds
                ray_sum += weight * image[i+1, j]
                weight_norm += weight * weight
            if i < image.shape[0] - 1 and j < image.shape[1] - 1:
                weight = di * dj * ds
                ray_sum += weight * image[i+1, j+1]
                weight_norm += weight * weight

    return ray_sum, weight_norm


def bilinear_ray_update(image, image_update, theta, ray_position,
                        projected_value):
    """Compute the update along a ray using bilinear interpolation.

    Parameters
    ----------
    image : 2D array, dtype=float
        Current reconstruction estimate.
    image_update : 2D array, dtype=float
        Array of same shape as ``image``. Updates will be added to this array.
    theta : float
        Angle of the projection.
    ray_position : float
        Position of the ray within the projection.
    projected_value : float
        Projected value (from the sinogram).

    Returns
    -------
    deviation :
        Deviation before updating the image.
    """
    ray_sum, weight_norm = bilinear_ray_sum(image, theta, ray_position)
    if weight_norm > 0.:
        deviation = -(ray_sum - projected_value) / weight_norm
    else:
        deviation = 0.
    theta = theta / 180. * np.pi
    radius = image.shape[0] // 2 - 1
    projection_center = image.shape[0] // 2
    rotation_center = image.shape[0] // 2
    # (s, t) is the (x, y) system rotated by theta
    t = ray_position - projection_center
    # s0 is the half-length of the ray's path in the reconstruction circle
    s0 = sqrt(radius*radius - t*t) if radius*radius >= t*t else 0.
    Ns = 2 * int(ceil(2 * s0))
    # beta for equiripple Hamming window
    hamming_beta = 0.46164

    if Ns > 0:
        # Step length between samples
        ds = 2 * s0 / Ns
        dx = -ds * cos(theta)
        dy = -ds * sin(theta)
        # Point of entry of the ray into the reconstruction circle
        x0 = s0 * cos(theta) - t * sin(theta)
        y0 = s0 * sin(theta) + t * cos(theta)
        for k in range(Ns + 1):
            x = x0 + k * dx
            y = y0 + k * dy
            index_i = x + rotation_center
            index_j = y + rotation_center
            i = int(floor(index_i))
            j = int(floor(index_j))
            di = index_i - floor(index_i)
            dj = index_j - floor(index_j)
            hamming_window = ((1 - hamming_beta)
                              - hamming_beta * cos(2 * np.pi * k / (Ns - 1)))
            if i > 0 and j > 0:
                image_update[i, j] += (deviation * (1. - di) * (1. - dj)
                                       * ds * hamming_window)
            if i > 0 and j < image.shape[1] - 1:
                image_update[i, j+1] += (deviation * (1. - di) * dj
                                         * ds * hamming_window)
            if i < image.shape[0] - 1 and j > 0:
                image_update[i+1, j] += (deviation * di * (1 - dj)
                                         * ds * hamming_window)
            if i < image.shape[0] - 1 and j < image.shape[1] - 1:
                image_update[i+1, j+1] += (deviation * di * dj
                                           * ds * hamming_window)

    return deviation

# pythran export sart_projection_update(float64[:,:], float64, float64[:],
#                                       float64)
#
# pythran export sart_projection_update(float64[:,:], float64, float64[:])


def sart_projection_update(image,
                           theta,
                           projection,
                           projection_shift=0.):
    """
    Compute update to a reconstruction estimate from a single projection
    using bilinear interpolation.

    Parameters
    ----------
    image : 2D array, dtype=float
        Current reconstruction estimate
    theta : float
        Angle of the projection
    projection : 1D array, dtype=float
        Projected values, taken from the sinogram
    projection_shift : float
        Shift the position of the projection by this many pixels before
        using it to compute an update to the reconstruction estimate

    Returns
    -------
    image_update : 2D array, dtype=float
        Array of same shape as ``image`` containing updates that should be
        added to ``image`` to improve the reconstruction estimate
    """
    image_update = np.zeros_like(image)
    for i in range(projection.shape[0]):
        ray_position = i + projection_shift
        bilinear_ray_update(image, image_update, theta, ray_position,
                            projection[i])
    return image_update

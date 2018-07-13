from numpy import pi

# pythran export unwrap_1d(float64[:], float64[:])


def unwrap_1d(image, unwrapped_image):
    '''Phase unwrapping using the naive approach.'''
    unwrapped_image[0] = image[0]
    periods = 0
    for i in range(1, image.shape[0]):
        difference = image[i] - image[i - 1]
        if difference > pi:
            periods -= 1
        elif difference < -pi:
            periods += 1
        unwrapped_image[i] = image[i] + 2 * pi * periods

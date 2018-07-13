import numpy as np

# pythran export possible_hull(uint8[:,:])


def possible_hull(img):
    """Return positions of pixels that possibly belong to the convex hull.

    Parameters
    ----------
    img : ndarray of bool
        Binary input image.

    Returns
    -------
    coords : ndarray (cols, 2)
       The ``(row, column)`` coordinates of all pixels that possibly belong to
       the convex hull.

    """
    rows, cols = img.shape

    # Output: rows storage slots for left boundary pixels
    #         cols storage slots for top boundary pixels
    #         rows storage slots for right boundary pixels
    #         cols storage slots for bottom boundary pixels
    coords = np.ones((2 * (rows + cols), 2), dtype=np.intp)
    coords *= -1

    rows_cols = rows + cols
    rows_2_cols = 2 * rows + cols

    for r in range(rows):

        rows_cols_r = rows_cols + r

        for c in range(cols):

            if img[r, c] != 0:

                rows_c = rows + c
                rows_2_cols_c = rows_2_cols + c

                # Left check
                if coords[r, 1] == -1:
                    coords[r, 0] = r
                    coords[r, 1] = c

                # Right check
                elif coords[rows_cols_r, 1] < c:
                    coords[rows_cols_r] = r, c

                # Top check
                if coords[rows_c, 1] == -1:
                    coords[rows_c] = r, c

                # Bottom check
                elif coords[rows_2_cols_c, 0] < r:
                    coords[rows_2_cols_c] = r, c

    return coords[coords[:, 0] != -1]

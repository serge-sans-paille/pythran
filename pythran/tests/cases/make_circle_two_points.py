import math

#pythran export _cross_product (float, float, float, float, float, float)
def _cross_product(x0, y0, x1, y1, x2, y2):
        return (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0)

#pythran export make_circumcircle ((float, float), (float, float), (float, float))
def make_circumcircle(a, b, c):
    # Mathematical algorithm from Wikipedia: Circumscribed circle
        ox = (min(a[0], b[0], c[0]) + max(a[0], b[0], c[0])) / 2.0
        oy = (min(a[1], b[1], c[1]) + max(a[1], b[1], c[1])) / 2.0
        ax = a[0] - ox;  ay = a[1] - oy
        bx = b[0] - ox;  by = b[1] - oy
        cx = c[0] - ox;  cy = c[1] - oy
        d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2.0
        if d == 0.0:
            return None
        x = ox + ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + (cx*cx + cy*cy) * (ay - by)) / d
        y = oy + ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + (cx*cx + cy*cy) * (bx - ax)) / d
        ra = math.hypot(x - a[0], y - a[1])
        rb = math.hypot(x - b[0], y - b[1])
        rc = math.hypot(x - c[0], y - c[1])
        return (x, y, max(ra, rb, rc))

#pythran export make_diameter ((float, float), (float, float))    
def make_diameter(a, b):
    cx = (a[0] + b[0]) / 2.0
    cy = (a[1] + b[1]) / 2.0
    r0 = math.hypot(cx - a[0], cy - a[1])
    r1 = math.hypot(cx - b[0], cy - b[1])
    return (cx, cy, max(r0, r1))

#pythran export is_in_circle((float, float, float), (float, float))
def is_in_circle(c, p):
    return math.hypot(p[0] - c[0], p[1] - c[1]) <= c[2] * (1 + 1e-14)

#pythran export _make_circle_one_point((float,float) list, (float, float))
def _make_circle_one_point(points, p):
        c = (p[0], p[1], 0.0)
        for (i, q) in enumerate(points):
                if not is_in_circle(c, q):
                        if c[2] == 0.0:
                                c = make_diameter(p, q)
                        else:
                                c = make_circle_two_points(points[ : i + 1], p, q)
        return c

#pythran export make_circle_two_points((float,float) list, (float, float), (float, float))
#runas make_circle_two_points([(1.,4.), (0., 8.)], (3., 4.), (5., 6.))
def make_circle_two_points(points, p, q):
    circ = make_diameter(p, q)
    left  = None
    right = None
    px, py = p
    qx, qy = q
    
    # For each point not in the two-point circle
    for r in points:
        if is_in_circle(circ, r):
            continue

        # Form a circumcircle and classify it on left or right side
        cross = _cross_product(px, py, qx, qy, r[0], r[1])
        c = make_circumcircle(p, q, r)
        if c is None:
            continue
        elif cross > 0.0 and (left is None or _cross_product(px, py, qx, qy, c[0], c[1]) > _cross_product(px, py, qx, qy, left[0], left[1])):
            left = c
        elif cross < 0.0 and (right is None or _cross_product(px, py, qx, qy, c[0], c[1]) < _cross_product(px, py, qx, qy, right[0], right[1])):
            right = c
    # Select which circle to return
    if left is None and right is None:
            return circ
    elif left is None:
            return right
    elif right is None:
            return left
    else:
            return left if (left[2] <= right[2]) else right


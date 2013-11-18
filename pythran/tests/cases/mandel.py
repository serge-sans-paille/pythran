#runas mandel(20,0,0, 8)
#pythran export mandel(int, float, float, int)
def mandel(size, x_center, y_center, max_iteration):
    out= [ [ 0 for i in xrange(size) ] for j in xrange(size) ]
    for i in xrange(size):
        "omp parallel for"
        for j in xrange(size):
            x,y = ( x_center + 4.0*float(i-size/2)/size,
                      y_center + 4.0*float(j-size/2)/size
                    )

            a,b = (0.0, 0.0)
            iteration = 0

            while (a**2 + b**2 <= 4.0 and iteration < max_iteration):
                a,b = a**2 - b**2 + x, 2*a*b + y
                iteration += 1
            if iteration == max_iteration:
                color_value = 255
            else:
                color_value = iteration*10 % 255
            out[i][j]=color_value
    return out

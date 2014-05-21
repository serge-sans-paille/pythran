#skip.runas import Image; im = Image.open("Scribus.gif"); image_list = list(im.getdata()); cols, rows = im.size; res = range(len(image_list)); sobelFilter(image_list, res, cols, rows)
#runas cols = 100; rows = 100 ;image_list=[x%10+y%20 for x in xrange(cols) for y in xrange(rows)]; sobelFilter(image_list, cols, rows)
#bench cols = 1000; rows = 500 ;image_list=[x%10+y%20 for x in xrange(cols) for y in xrange(rows)]; sobelFilter(image_list, cols, rows)
#pythran export sobelFilter(int list, int, int)
def sobelFilter(original_image, cols, rows):
    edge_image = range(len(original_image))
    for i in xrange(rows):
        edge_image[i * cols] = 255
        edge_image[((i + 1) * cols) - 1] = 255

    for i in xrange(1, cols - 1):
        edge_image[i] = 255
        edge_image[i + ((rows - 1) * cols)] = 255

    for iy in xrange(1, rows - 1):
        for ix in xrange(1, cols - 1):
            sum_x = 0
            sum_y = 0
            sum = 0
            #x gradient approximation
            sum_x += original_image[ix - 1 + (iy - 1) * cols] * -1
            sum_x += original_image[ix + (iy - 1) * cols] * -2
            sum_x += original_image[ix + 1 + (iy - 1) * cols] * -1
            sum_x += original_image[ix - 1 + (iy + 1) * cols] * 1
            sum_x += original_image[ix + (iy + 1) * cols] * 2
            sum_x += original_image[ix + 1 + (iy + 1) * cols] * 1
            sum_x = min(255, max(0, sum_x))
            #y gradient approximatio
            sum_y += original_image[ix - 1 + (iy - 1) * cols] * 1
            sum_y += original_image[ix + 1 + (iy - 1) * cols] * -1
            sum_y += original_image[ix - 1 + (iy) * cols] * 2
            sum_y += original_image[ix + 1 + (iy) * cols] * -2
            sum_y += original_image[ix - 1 + (iy + 1) * cols] * 1
            sum_y += original_image[ix + 1 + (iy + 1) * cols] * -1
            sum_y = min(255, max(0, sum_y))

            #GRADIENT MAGNITUDE APPROXIMATION
            sum = abs(sum_x) + abs(sum_y)

            #make edges black and background white
            edge_image[ix + iy * cols] = 255 - (255 & sum)
    return edge_image

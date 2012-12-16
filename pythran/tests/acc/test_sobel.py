import Image
import sobel_filter

im = Image.open("cx.gif")
image_list = list(im.getdata())
cols, rows = im.size
res = sobel_filter.sobelFilter(image_list, cols, rows)
im.show()
im.putdata(res)
im.show()

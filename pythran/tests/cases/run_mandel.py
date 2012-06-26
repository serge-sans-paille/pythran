from PIL import Image
from mandel import mandel

max_iteration = 1000
x_center = -1.0
y_center =  0.0
size = 300

im = Image.new("RGB", (size,size))
cvs=mandel(size, x_center, y_center, max_iteration)
[ im.putpixel( (i,j), (cvs[i][j], cvs[i][j], cvs[i][j])) for i in xrange(size) for j in xrange(size) ]
im.save("mandelbrot.png", "PNG")

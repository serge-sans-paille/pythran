#!/usr/bin/env python
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import math
from matplotlib.backends.backend_pdf import PdfPages

x = np.array([[44.2, 1410, 1310, 260, 9.44, 6.21],[29.2, 744, 704, 143, 5.13, 5.12], [994, 0, 1320, 888, 14.1, 5.59],[118, 0, 711, 481, 8.21, 5.83]])

y = np.zeros(x.shape)

for i,j in enumerate(x):
    y[i] = j/x[2]

for i in xrange(y.shape[0]):
    for j in xrange(x.shape[1]):
        if math.isinf(y[i][j]):
            y[i][j] = x[i][j]/x[0][j]
        if math.isnan(y[i][j]):
            y[i][j] = 0
    

color_ = ["red", "blue", "orange", "purple"]
p = range(4)
for i,j in enumerate(y):
    p[i] = plt.bar(range(i,y.size+len(y)+1, len(y) +1),j, color=color_[i])

#plt.xlabel('Comparison between cython and pythran')
plt.xticks(range(2,y.size+len(y)+1, len(y) +1), ('fbcorr', 'pi_buffon', 'matmul', 'mandel', 'pairwise', 'convolution') )
plt.ylabel('execution time')
#plt.title(r'$comparaison between cython and pythran with/without parallelism$')
plt.grid(True)
plt.legend( (p[0][0], p[1][0], p[2][0], p[3][0]), ('Pythran', 'Pythran + OMP', 'Cython', 'Cython + OMP') , bbox_to_anchor=(0., 1.02, 1., .102), loc=2, ncol=2, mode="expand", borderaxespad=0.)
pp = PdfPages('cython.pdf')
plt.savefig(pp,format='pdf')
pp.close()



#pythran export brownian_bridge(int, int, float, float, int)
#runas brownian_bridge(1,5,1.35,2.65,4)
#bench brownian_bridge(1,5,0.35,4.65,100000)

import random
from math import sqrt

def linspace(begin, end, nbsteps):
    assert begin < end
    return [ begin + i*(end-begin)/nbsteps for i in xrange(nbsteps) ]

def zeros(n): return [0.]*n

# should be "from random import gauss as norm", but not reproducible...
def norm(m,u):
    return ((m*u+0.15)%1)



# moyenne du pont en t entre les points (t1,b1) et (t2,b2):
def moy(t1,t2,b1,b2,t): return (1.*(t2*b1-t1*b2)+t*(b2-b1))/(t2-t1)
def p(t): t=1
# variance du pont en t entre les points (t1,b1) et (t2,b2):
def var(t1,t2,b1,b2,t): return (1.*t-t1)*(t2-t)/(t2-t1)

def brownian_bridge(ti, tf, bi, bf, n):
    """
    simulation d'un pont brownien sur [ti,tf],
    avec les valeurs extremes bi et bf
    et n points par unite de temps
    sortie :
    - T   : positions temporelles des echantillons
    - B   : valeurs des echantillons
    """

    n        = int(n*(tf-ti))     # nombre de points
    T        = linspace(ti,tf,n)  # points d'echantillonnage
    pas      = (tf-ti)/(n-1.)     # pas d'echantillonnage
    B        = zeros(n)           # initialisation du brownien
    B[0]     = bi                 # valeur initiale
    B[n-1]   = bf                 # valeur finale
    t1       = ti
    for k in range(1,n-1):               # construction du pont en ti+k*pas
        m = moy(t1,tf,B[k-1],bf,t1+pas)  # sur les intervalle [ti+(k-1)*pas,tf]
        v = var(t1,tf,B[k-1],bf,t1+pas)  # avec les valeurs limites B[k-1],et bf
        B[k] = m+sqrt(v)*norm(0,1)
        t1  += pas
    return T, B

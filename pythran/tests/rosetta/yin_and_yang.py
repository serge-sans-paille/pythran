# from http://rosettacode.org/wiki/Yin_and_yang#Python
#pythran export yinyang(int)
#runas yinyang(4)

import math
def yinyang(n=3):
        radii   = [i * n for i in [1, 3, 6]]
        ranges  = [list(range(-r, r+1)) for r in radii]
        squares = [[ (x,y) for x in rnge for y in rnge]
                   for rnge in ranges]
        circles = [[ (x,y) for x,y in sqrpoints
                     if math.hypot(x,y) <= radius ]
                   for sqrpoints, radius in zip(squares, radii)]
        m = {(x,y):' ' for x,y in squares[-1]}
        for x,y in circles[-1]:
                m[x,y] = '*'
        for x,y in circles[-1]:
                if x>0: m[(x,y)] = '.'
        for x,y in circles[-2]:
                m[(x,y+3*n)] = '*'
                m[(x,y-3*n)] = '.'
        for x,y in circles[-3]:
                m[(x,y+3*n)] = '.'
                m[(x,y-3*n)] = '*'
        return '\n'.join(''.join(m[(x,y)] for x in reversed(ranges[-1])) for y in ranges[-1])

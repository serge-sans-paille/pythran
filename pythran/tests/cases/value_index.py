import numpy as np


#import parameters as p
#pythran export tri(int [][],int [][])
#runas import numpy as np; a = np.arange(100, 0, -1).reshape(10, 10); tri(a, a)

def tri(score,score_t):
    score_t[0,0]=score[0,0]
    score_t=score[np.argsort(score[:,1])]
    return score_t

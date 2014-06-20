#from: http://stackoverflow.com/questions/4651683/numpy-grouping-using-itertools-groupby-performance
#runas import numpy as np ; values = np.array([1,3,5,2,4],dtype="u4") ; values.sort() ; grouping(values)
#bench import numpy as np ; N = 350000 ; values = np.array(np.random.randint(0,3298,size=N),dtype="u4") ; values.sort() ; grouping(values)

#pythran export grouping(uint32 [])

def grouping(values):
    import numpy as np
    diff = np.concatenate(([1], np.diff(values)))
    idx = np.concatenate((np.where(diff)[0], [len(values)]))
    return values[idx[:-1]], np.diff(idx)

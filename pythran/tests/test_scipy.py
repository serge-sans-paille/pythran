from test_env import TestEnv
# from http://www.scipy.org/Download , weave/example directory

class TestScipy(TestEnv):

    def test_laplace(self):
        code="""
def laplace(u,dx, dy):
    nx, ny=len(u), len(u[0])
    for i in range(1, nx-1):
        for j in range(1, ny-1):
            u[i][j] = ((u[i-1][j] + u[i+1][j])*dy**2 +
                      (u[i][j-1] + u[i][j+1])*dx**2)/(2.0*(dx**2 + dy**2))
"""
        self.run_test(code, [[0.1,0.2,0.3],[0.1,0.2,0.3],[0.1,0.2,0.3]], 0.01, 0.02, laplace=[[[float]], float, float])

    def test_recursive_fibonnaci(self):
        code="""
def recursive_fibonnaci(a):
    if a <= 2:
        return 1
    else:
        return recursive_fibonnaci(a-2) + recursive_fibonnaci(a-1)
        """
        self.run_test(code, 5, recursive_fibonnaci=[int])

    def test_iterative_fibonnaci(self):
        code="""
def iterative_fibonnaci(a):
    if a <= 2:
        return 1
    last = next_to_last = 1
    i = 2
    while i < a:
        result = last + next_to_last
        next_to_last = last
        last = result
        i+=1
    return result;
"""
        self.run_test(code, 5, iterative_fibonnaci=[int])

    def test_binary_search(self):
        code="""
def binary_search(seq, t):
    min = 0; max = len(seq) - 1
    while 1:
        if max < min:
            return -1
        m = (min + max) // 2
        if seq[m] < t:
            min = m + 1
        elif seq[m] > t:
            max = m - 1
        else:
            return m
"""
        self.run_test(code,[1,2,3,4,5,6,7,8,9], 4, binary_search=[[int], int])

    def test_ramp(self):
        code="""
def ramp(result, start, end):
    size=len(result)
    assert size > 1
    step = (end-start)//(size-1)
    for i in xrange(size):
        result[i] = start + step*i
"""
        self.run_test(code,[0 for x in xrange(10)], 1.5, 9.5, ramp=[[float], float, float])

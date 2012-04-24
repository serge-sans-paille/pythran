from test_env import TestEnv

class TestScipy(TestEnv):
#
#    def test_laplace(self):
#        code="""
#def laplace(u,dx, dy):
#    nx, ny=len(u), len(u[0])
#    for i in range(1, nx-1):
#        for j in range(1, ny-1):
#            u[i][j] = ((u[i-1][j] + u[i+1][j])*dy**2 +
#                      (u[i][j-1] + u[i][j+1])*dx**2)/(2.0*(dx**2 + dy**2))
#"""
#        self.run_test(code, [[0.1,0.2,0.3],[0.1,0.2,0.3],[0.1,0.2,0.3]], 0.01, 0.02, laplace=("float list list", "float", "float"))
#
#    def test_recursive_fibonnaci(self):
#        code="""
#def recursive_fibonnaci(a):
#    if a <= 2:
#        return 1
#    else:
#        return recursive_fibonnaci(a-2) + recursive_fibonnaci(a-1)
#        """
#        self.run_test(code, 5, recursive_fibonnaci=('int'))
#
    def test_iterative_fibonnaci(self):
        code="""
def iterative_fibonnaci(a):
    if a <= 2:
        return 1
    last = next_to_last = 1
    for i in range(2,a):
        result = last + next_to_last
        next_to_last = last
        last = result
    return result;
"""
        self.run_test(code, 5, iterative_fibonnaci=('int'))


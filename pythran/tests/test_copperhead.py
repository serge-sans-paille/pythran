from test_env import TestEnv

class TestCopperhead(TestEnv):

# from copperhead test suite
# https://github.com/copperhead

    def test_saxpy(self):
        self.run_test("def saxpy(a, x, y): return map(lambda xi, yi: a * xi + yi, x, y)", 1.5, [1,2,3], [0.,2.,4.], saxpy=[float,[int], [float]])

    def test_saxpy2(self):
        self.run_test("def saxpy2(a, x, y): return [a*xi+yi for xi,yi in zip(x,y)]", 1.5, [1,2,3], [0.,2.,4.], saxpy2=[float,[int], [float]])

    def test_saxpy3(self):
        code="""
def saxpy3(a, x, y):
    def triad(xi, yi): return a * xi + yi
    return map(triad, x, y)
"""
        self.run_test(code,  1.5, [1,2,3], [0.,2.,4.], saxpy3=[float,[int], [float]])

    def test_saxpy4(self):
        code="""
def saxpy4(a, x, y):
    return manual(y,x,a)
def manual(y,x,a):
    __list=list()
    for __tuple in zip(y,x):
        __list.append(__tuple[0]*a+__tuple[1])
    return __list
"""
        self.run_test(code,  1.5, [1,2,3], [0.,2.,4.], saxpy4=[float,[int], [float]])

    def test_sxpy(self):
        code="""
def sxpy(x, y):
    def duad(xi, yi): return xi + yi
    return map(duad, x, y)
"""
        self.run_test(code,  [1,2,3], [0.,2.,4.], sxpy=[[int], [float]])

    def test_incr(self):
        self.run_test("def incr(x): return map(lambda xi: xi + 1, x)", [0., 0., 0.], incr=[[float]])

    def test_as_ones(self):
        self.run_test("def as_ones(x): return map(lambda xi: 1, x)", [0., 0., 0.], as_ones=[[float]])

    def test_idm(self):
        self.run_test("def idm(x): return map(lambda b: b, x)", [1, 2, 3], idm=[[int]])

    def test_incr_list(self):
        self.run_test("def incr_list(x): return [xi + 1 for xi in x]", [1., 2., 3.], incr_list=[[float]])


    def test_idx(self):
        code="""
def idx(x):
    def id(xi): return xi
    return map(id, x)"""
        self.run_test(code, [1,2,3], idx=[[int]])

    def test_rbf(self):
        code="""
from math import exp
def norm2_diff(x, y):
   def el(xi, yi):
       diff = xi - yi
       return diff * diff
   return sum(map(el, x, y))

def rbf(ngamma, x, y):
   return exp(ngamma * norm2_diff(x,y))"""
        self.run_test(code, 2.3, [1,2,3], [1.1,1.2,1.3], rbf=[float,[float], [float]])

# from copperhead-new/copperhead/prelude.py
    def test_indices(self):
        self.run_test("def indices(A):return range(len(A))",[1,2], indices=[[int]])

    def test_gather(self):
        self.run_test("def gather(x, indices): return [x[i] for i in indices]", [1,2,3,4,5],[0,2,4], gather=[[int], [int]])

    def test_scatter(self):
        code="""
def indices(x): return xrange(len(x))
def scatter(src, indices_, dst):
    assert len(src)==len(indices_)
    result = list(dst)
    for i in xrange(len(src)):
        result[indices_[i]] = src[i]
    return result
"""
        self.run_test(code, [0.0,1.0,2.,3,4,5,6,7,8,9],[5,6,7,8,9,0,1,2,3,4],[0,0,0,0,0,0,0,0,0,0,18], scatter=[[float], [int], [float]])

    def test_scan(self):
        code="""
def prefix(A): return scan(lambda x,y:x+y, A)
def scan(f, A):
    B = list(A)
    for i in xrange(1, len(B)):
        B[i] = f(B[i-1], B[i])
    return B
"""
        self.run_test(code, [1,2,3], prefix=[[float]])



# from Copperhead: Compiling an Embedded Data Parallel Language
# by Bryan Catanzaro, Michael Garland and Kurt Keutzer
# http://www.eecs.berkeley.edu/Pubs/TechRpts/2010/EECS-2010-124.html

    def test_spvv_csr(self):
        code="""
def spvv_csr(x, cols, y):
    def gather(x, indices): return [x[i] for i in indices]
    z = gather(y, cols)
    return sum(map(lambda a, b: a * b, x, z))
"""
        self.run_test(code, [1,2,3],[0,1,2],[5.5,6.6,7.7], spvv_csr=[[int], [int], [float]])

    def test_spmv_csr(self):
        code="""
def spvv_csr(x, cols, y):
    def gather(x, indices): return [x[i] for i in indices]
    z = gather(y, cols)
    return sum(map(lambda a, b: a * b, x, z))
def spmv_csr(Ax, Aj, x):
    return map(lambda y, cols: spvv_csr(y, cols, x), Ax, Aj)
"""
        self.run_test(code, [[0,1,2],[0,1,2],[0,1,2]],[[0,1,2],[0,1,2],[0,1,2]],[0,1,2], spmv_csr=[[[int]], [[int]], [int]])

    def test_spmv_ell(self):
        code="""
def indices(x): return xrange(len(x))
def spmv_ell(data, idx, x):
    def kernel(i):
        return sum(map(lambda Aj, J: Aj[i] * x[J[i]], data, idx))
    return map(kernel, indices(x))
"""
        self.run_test(code, [[0,1,2],[0,1,2],[0,1,2]],[[0,1,2],[0,1,2],[0,1,2]],[0,1,2], spmv_ell=[[[int]], [[int]], [int]])

    def test_vadd(self):
        self.run_test("def vadd(x, y): return map(lambda a, b: a + b, x, y)", [0.,1.,2.],[5.,6.,7.], vadd=[[float], [float]])

    def test_vmul(self):
        self.run_test("def vmul(x, y): return map(lambda a, b: a * b, x, y)", [0.,1.,2.],[5.,6.,7.], vmul=[[float], [float]])

    def test_form_preconditioner(self):
        code="""
def vadd(x, y): return map(lambda a, b: a + b, x, y)
def vmul(x, y): return map(lambda a, b: a * b, x, y)
def form_preconditioner(a, b, c):
    def det_inverse(ai, bi, ci):
        return 1.0/(ai * ci - bi * bi)
    indets = map(det_inverse, a, b, c)
    p_a = vmul(indets, c)
    p_b = map(lambda a, b: -a * b, indets, b)
    p_c = vmul(indets, a)
    return p_a, p_b, p_c
"""
        self.run_test(code, [1,2,3],[0,1,2],[5.5,6.6,7.7],form_preconditioner=[[int], [int], [float]])

    def test_precondition(self):
        code="""
def precondition(u, v, p_a, p_b, p_c):
    def vadd(x, y): return map(lambda a, b: a + b, x, y)
    def vmul(x, y): return map(lambda a, b: a * b, x, y)
    e = vadd(vmul(p_a, u), vmul(p_b, v))
    f = vadd(vmul(p_b, u), vmul(p_c, v))
    return e, f
"""
        self.run_test(code, [1,2,3], [5.5,6.6,7.7],[1,2,3], [5.5,6.6,7.7],[8.8,9.9,10.10], precondition=[[int], [float], [int], [float], [float]])


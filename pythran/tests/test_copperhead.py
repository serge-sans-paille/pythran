from pythran import python_interface
import unittest

class TestBase(unittest.TestCase):

    def run_test(self, code, *params, **interface):
        for name in sorted(interface.keys()):
            mod = python_interface("test_"+name, code, **interface)
            res = getattr(mod,name)(*params)
            print res

# from copperhead test suite
# https://github.com/copperhead
    def test_saxpy(self):
        self.run_test("def saxpy(a, x, y): return map(lambda xi, yi: a * xi + yi, x, y)", 1.5, [1,2,3], [0.,2.,4.], saxpy=("float","int list", "float list"))
    
#    def test_saxpy2(self):
#        self.run_test("def saxpy2(a, x, y): return [a*xi+yi for xi,yi in zip(x,y)]", 1.5, [1,2,3], [0.,2.,4.], saxpy2=("float","int list", "float list"))
#
#    
#    def saxpy3(a, x, y):
#        def triad(xi, yi):
#                return a * xi + yi
#                    return map(triad, x, y)
#    
#    def sxpy(x, y):
#        def duad(xi, yi):
#                return xi + yi
#                    return map(duad, x, y)
#    
#    def incr(x):
#        return map(lambda xi: xi + 1, x)
#    
#    def as_ones(x):
#        return map(lambda xi: 1, x)
#    
#    def idm(x):
#        return map(lambda b: b, x)
#    
#    def idx(x):
#        def id(xi):
#                return xi
#                    return map(id, x)
#    
#    def incr_list(x):
#        return [xi + 1 for xi in x]
#
#    def norm2_diff(x, y):
#       def el(xi, yi):
#           diff = xi - yi
#           return diff * diff
#       return sum(map(el, x, y))
#
#    def rbf(ngamma, x, y):
#       return exp(ngamma * norm2_diff(x,y))


# from Copperhead: Compiling an Embedded Data Parallel Language
# by Bryan Catanzaro, Michael Garland and Kurt Keutzer
# http://www.eecs.berkeley.edu/Pubs/TechRpts/2010/EECS-2010-124.html
#    def spmv_csr(A_values, A_columns, x):
#       def spvv(Ai, j):
#           z = gather(x, j)
#       return sum(map(lambda Aij, xj: Aij*xj, Ai, z))
#    @cu
#    def vadd(x, y):
#    return map(lambda a, b: return a + b, x, y)
#    @cu
#    def vmul(x, y):
#    return map(lambda a, b: return a * b, x, y)
#    @cu
#    def form_preconditioner(a, b, c):
#    def det_inverse(ai, bi, ci):
#    return 1.0/(ai * ci - bi * bi)
#    indets = map(det_inverse, a, b, c)
#    p_a = vmul(indets, c)
#    p_b = map(lambda a, b: -a * b, indets, b)
#    p_c = vmul(indets, a)
#    return p_a, p_b, p_c
#    @cu
#    def precondition(u, v, p_a, p_b, p_c):
#    e = vadd(vmul(p_a, u), vmul(p_b, v))
#    f = vadd(vmul(p_b, u), vmul(p_c, v))
#    return e, f


        

if __name__ == '__main__':
        unittest.main()

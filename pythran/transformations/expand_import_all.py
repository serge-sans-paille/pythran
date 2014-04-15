"""
ExpandImportAll replaces import * by all their modules
"""
import ast
from pythran.passmanager import Transformation
from pythran.tables import modules


class ExpandImportAll(Transformation):
    '''
    Expands all import when '*' detected

    >>> import ast, passmanager, backend
    >>> node = ast.parse("from math import *")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ExpandImportAll, node)
    >>> print pm.dump(backend.Python, node)
    from math import asinh, atan2, fmod, atan, isnan, factorial, pow, \
copysign, cos, cosh, ldexp, hypot, isinf, floor, sinh, acosh, tan, ceil, exp, \
trunc, asin, expm1, e, log, fabs, tanh, log10, atanh, radians, sqrt, frexp, \
lgamma, erf, erfc, modf, degrees, acos, pi, log1p, sin, gamma
    '''

    def visit_ImportFrom(self, node):
        for alias in node.names:
            if alias.name == '*':
                node.names.pop()
                node.names.extend(ast.alias(fname, None)
                                  for fname in modules[node.module])
        return node

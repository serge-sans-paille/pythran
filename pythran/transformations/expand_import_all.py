""" ExpandImportAll replaces import * by all their modules. """

from pythran.passmanager import Transformation
from pythran.tables import MODULES

import ast


class ExpandImportAll(Transformation):
    '''
    Expands all import when '*' detected

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("from math import *")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ExpandImportAll, node)
    >>> print pm.dump(backend.Python, node)
    from math import asinh, atan2, fmod, atan, isnan, factorial, pow, \
copysign, cos, cosh, ldexp, hypot, isinf, floor, sinh, acosh, tan, ceil, exp, \
trunc, asin, expm1, e, log, fabs, tanh, log10, atanh, radians, sqrt, frexp, \
lgamma, erf, erfc, modf, degrees, acos, pi, log1p, sin, gamma
    '''

    def visit_ImportFrom(self, node):
        for alias in node.names:
            if alias.name == '*':
                self.update = True
                node.names.pop()
                node.names.extend(ast.alias(fname, None)
                                  for fname in MODULES[node.module])
        return node

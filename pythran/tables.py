'''This modules provides the translation tables from python to c++'''
import ast

builtin_constants = { "True":"bool", "False":"bool", "None":"none_type"}

operator_to_lambda = {
        # boolop
        ast.And     : lambda l,r: "({0} and {1})".format(l,r),
        ast.Or      : lambda l,r: "({0} or {1})".format(l,r),
        # operator
        ast.Add     : lambda l,r: l+"+"+r,
        ast.Sub     : lambda l,r: l+"-"+r,
        ast.Mult    : lambda l,r: l+"*"+r,
        ast.Div     : lambda l,r: l+"/"+r,
        ast.Mod     : lambda l,r: l+"%"+r,
        ast.Pow     : lambda l,r: "pow({0},{1})".format(l,r),
        ast.LShift  : lambda l,r: l+"<<"+r,
        ast.RShift  : lambda l,r: l+">>"+r,
        ast.BitOr   : lambda l,r: l+"|"+r,
        ast.BitXor  : lambda l,r: "({0}^{1})".format(l,r),
        ast.BitAnd  : lambda l,r: "({0}&{1})".format(l,r),
        ast.FloorDiv: lambda l,r: "floor({0}/{1})".format(l,r), # assume from __future__ import division
        # unaryop
        ast.Invert  : lambda o:"~"+o,
        ast.Not     : lambda o:"not "+o,
        ast.UAdd    : lambda o: "+"+o,
        ast.USub    : lambda o: "-"+o,
        # cmpop
        ast.Eq      : lambda l,r: l+"=="+r,
        ast.NotEq   : lambda l,r: l+"!="+r,
        ast.Lt      : lambda l,r: l+"<"+r,
        ast.LtE     : lambda l,r: l+"<="+r,
        ast.Gt      : lambda l,r: l+">"+r,
        ast.GtE     : lambda l,r: l+">="+r,
        ast.Is      : lambda l,r: "id({0})==id({1})".format(l,r),
        ast.IsNot   : lambda l,r: "id({0})!=id({1})".format(l,r),
        ast.In      : lambda l,r: "in({1},{0})".format(l,r),
        ast.NotIn   : lambda l,r: "not in({1},{0})".format(l,r),
        }

type_to_str = {
        int     : "long",
        float   : "double",
        }

# the value, if not None, means that decltype must be used
modules = {
        "__builtins__": {
            "bind0":None,
            "bind1":None,
            "bind2":None,
            "bind3":None,
            "id":None,
            "list":None,
            "len":None,
            "zip":None,
            "reduce":None,
            "max":None,
            "min":None,
            "sum":None,
            "map": None,
            "range":None,
            "xrange":None,
            # pythran extensions
            "pmap": None,
            },
        "math" : {
            "cos" : None,
            "exp" : None,
            "sqrt" : None,
            "log10" : None,
            "isnan" : None,
            "pi" : "something",
            "e" : "yeah",
            },
        }

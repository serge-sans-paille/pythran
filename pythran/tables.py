import ast

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

# the value, if not None, is used to deduce the return type of the builtins if the default behavior is not satisfying 
modules = {
        "__builtins__": {
            "id":None,
            "list":None,
            "len":None,
            "zip":None,
            "reduce": lambda self, node: self.add_typedef(node, "decltype(std::declval<{0}>()({1}))".format(
                self.typedefs[node.args[0]][1],
                ", ".join(["std::declval<typename {0}::value_type>()".format(self.typedefs[node.args[1]][1])]*2))),
            "max":None,
            "min":None,
            "sum":None,
            "map": lambda self, node: self.add_typedef(node, "sequence< decltype(std::declval<{0}>()({1})) >".format(
                self.typedefs[node.args[0]][1],
                ", ".join("std::declval<typename {0}::value_type>()".format(self.typedefs[n][1]) for n in node.args[1:]))
                ),
            "range":None,
            "xrange":None,
            },
        "math" : {
            "exp" : None,
            },
        }

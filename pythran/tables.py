import ast

operator_to_lambda = {
        ast.Add     : lambda l,r: l+"+"+r,
        ast.Sub     : lambda l,r: l+"-"+r,
        ast.Mult    : lambda l,r: l+"*"+r,
        ast.Div     : lambda l,r: l+"/"+r,
        ast.Lt      : lambda l,r: l+"<"+r,
        ast.Gt      : lambda l,r: l+">"+r,
        ast.Eq      : lambda l,r: l+"=="+r,
        }

type_to_str = {
        int     : "long",
        float   : "double",
        }

# the value, if not None, is used to deduce the return type of the builtins if the default behavior is not satisfying 
modules = {
        "__builtins__": {
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

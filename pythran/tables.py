'''This modules provides the translation tables from python to c++'''
import ast
import cxxtypes
from intrinsic import MethodIntr, MethodWithSideEffectIntr, AttributeIntr, ScalarIntr

namespace = "pythonic"

builtin_constants = { "True":"bool", "False":"bool", "None":"none_type"}

builtin_constructors = {'int':'long', 'float':'double', 'bool':'bool', 'long':'long long'  }

cxx_keywords = {'and', 'and_eq', 'asm', 'auto', 'bitand', 'bitor',
        'break', 'case', 'catch', 'char', 'class',
        'compl', 'const', 'const_cast', 'continue', 'default', 'delete',
        'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit',
        'export', 'extern', 'false', 'for', 'friend', 
        'goto', 'if', 'inline', 'mutable',
        'namespace', 'new', 'not', 'not_eq', 'operator', 'or',
        'or_eq', 'private', 'protected', 'public', 'register', 'reinterpret_cast',
        'return', 'short', 'signed', 'sizeof', 'static', 'static_cast',
        'struct', 'switch', 'template', 'this', 'throw', 'true',
        'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned',
        'using', 'virtual', 'void', 'volatile', 'wchar_t', 'while',
        'xor', 'xor_eq',
        # C++11 additions
        'constexpr', 'decltype', 'noexcept', 'nullptr', 'static_assert', 
        # the following keywords are used as intrinsics in python and are thus allowed
        # 'bool', 'float', 'long', 'int', 
        }

operator_to_lambda = {
        # boolop
        ast.And     : lambda l,r: "({0} and {1})".format(l,r),
        ast.Or      : lambda l,r: "({0} or {1})".format(l,r),
        # operator
        ast.Add     : lambda l,r: "({0}+{1})".format(l,r),
        ast.Sub     : lambda l,r: "({0}-{1})".format(l,r),
        ast.Mult    : lambda l,r: "({0}*{1})".format(l,r),
        ast.Div     : lambda l,r: "({0}/{1})".format(l,r),
        ast.Mod     : lambda l,r: "({0}%{1})".format(l,r),
        ast.Pow     : lambda l,r: "pow({0},{1})".format(l,r),
        ast.LShift  : lambda l,r: "({0}<<{1})".format(l,r),
        ast.RShift  : lambda l,r: "({0}>>{1})".format(l,r),
        ast.BitOr   : lambda l,r: "({0}|{1})".format(l,r),
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
        long    : "long long",
        float   : "double",
        }

type_to_suffix = {
        int     : "L",
        long    : "LL",
        }

# each module consist in a module_name <> set of symbols with optional attributes
# the attributes can be
#   scalar when the symbol is *not* a function
#   attribute when the symbol is a *method*
#   combiner when the symbol has some side effects, in which case the side effect is described using a function
#
modules = {
        "__builtins__": {
            "abs": MethodIntr(),
            "all": MethodIntr(),
            "any": MethodIntr(),
            "bin": MethodIntr(),
            "chr": MethodIntr(),
            "cmp": MethodIntr(),
            "complex": MethodIntr(),
            "divmod": MethodIntr(),
            "enumerate": MethodIntr(),
            "filter": MethodIntr(),
            "hex": MethodIntr(),
            "id": MethodIntr(),
            "len": MethodIntr(),
            "list": MethodIntr(),
            "map": MethodIntr(),
            "max": MethodIntr(),
            "min": MethodIntr(),
            "oct": MethodIntr(),
            "pow": MethodIntr(),
            "range": MethodIntr(),
            "reduce": MethodIntr(),
            "reversed": MethodIntr(),
            "round": MethodIntr(),
            "set": MethodIntr(),
            "sorted": MethodIntr(),
            "str": MethodIntr(),
            "sum": MethodIntr(),
            "tuple": MethodIntr(),
            "xrange": MethodIntr(),
            "zip": MethodIntr(),
            # pythran extensions
            "bind0": MethodIntr(),
            "bind1": MethodIntr(),
            "bind2": MethodIntr(),
            "bind3": MethodIntr(),
            "pmap":  MethodIntr(),
            },
        "math" : {
            "isinf" : MethodIntr(),
            "modf" : MethodIntr(),
            "frexp" : MethodIntr(),
            "factorial" : MethodIntr(),
            "gamma" : MethodIntr(),
            "lgamma" : MethodIntr(),
            "trunc" : MethodIntr(),
            "erf" : MethodIntr(),
            "erfc" : MethodIntr(),
            "asinh" : MethodIntr(),
            "atanh" : MethodIntr(),
            "acosh" : MethodIntr(),
            "radians" : MethodIntr(),
            "degrees" : MethodIntr(),
            "hypot" : MethodIntr(),
            "tanh" : MethodIntr(),
            "cosh" : MethodIntr(),
            "sinh" : MethodIntr(),
            "atan" : MethodIntr(),
            "atan2" : MethodIntr(),
            "asin" : MethodIntr(),
            "tan" : MethodIntr(),
            "log" : MethodIntr(),
       	    "log1p" : MethodIntr(),
            "expm1" : MethodIntr(),
            "ldexp" : MethodIntr(),
            "fmod" : MethodIntr(),
            "fabs" : MethodIntr(),
            "copysign" : MethodIntr(),
            "acos" : MethodIntr(),
            "cos" : MethodIntr(),
            "sin" : MethodIntr(),
            "exp" : MethodIntr(),
            "sqrt" : MethodIntr(),
            "log10" : MethodIntr(),
            "isnan" : MethodIntr(),
            "ceil" : MethodIntr(),
            "floor" : MethodIntr(),
            "pi" : ScalarIntr(),
            "e" : ScalarIntr(),
            },
        "cmath" : {
            "cos" : MethodIntr(),
            "sin" : MethodIntr(),
            "exp" : MethodIntr(),
            "sqrt" : MethodIntr(),
            "log10" : MethodIntr(),
            "isnan" : MethodIntr(),
            "pi" : ScalarIntr(),
            "e" : ScalarIntr(),
            },
        "random" : {
                "seed": MethodIntr(),
                "random" :MethodIntr(),
                "gauss": MethodIntr()
                },
        "__list__" : {
            "append" : MethodWithSideEffectIntr([lambda self, node: self.combine(node.args[0], node.args[1], unary_op=lambda f: cxxtypes.ListType(f), register=True)]),
            "extend" : MethodWithSideEffectIntr([lambda self, node: self.combine(node.args[0], node.args[1], register=True)]),
            "remove" : MethodWithSideEffectIntr(),
            "index" : MethodWithSideEffectIntr(),
            "pop" : MethodWithSideEffectIntr(),
            "reverse" : MethodWithSideEffectIntr(),
            "sort" : MethodWithSideEffectIntr(),
            "count" : MethodWithSideEffectIntr(),
            "insert" : MethodWithSideEffectIntr([lambda self, node: self.combine(node.args[0], node.args[2], unary_op=lambda f: cxxtypes.ListType(f), register=True)]),
            },
        "__set__" : {
            "add" : MethodWithSideEffectIntr([lambda self, node: self.combine(node.args[0], node.args[1], unary_op=lambda f: cxxtypes.SetType(f), register=True)]),
            },
        "_complex_" : {
                "real": AttributeIntr(0),
                "imag": AttributeIntr(1),
                "conjugate" : MethodWithSideEffectIntr(),
                },
        "__iterator__" : {
            "next": MethodWithSideEffectIntr(),
            },
        "__user__" : {},
        }

# a method name to module binding
methods ={}
for module, elems in modules.iteritems():
    for elem, signature in elems.iteritems():
        if signature.ismethodwithsideeffect():
            assert elem not in methods # we need unicity
            methods[elem]= ( module, signature )

# a attribute name to module binding
attributes={}
for module, elems in modules.iteritems():
    for elem, signature in elems.iteritems():
        if signature.isattribute():
            assert elem not in attributes # we need unicity
            attributes[elem]= ( module, signature )

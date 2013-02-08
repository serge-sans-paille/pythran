'''
This modules provides the translation tables from python to c++.
'''

import ast
import cxxtypes

from intrinsic import ConstFunctionIntr, FunctionIntr
from intrinsic import ConstMethodIntr, MethodIntr, AttributeIntr, ScalarIntr

namespace = "pythonic"

pytype_to_ctype_table = {
        complex: 'std::complex<double>',
        bool: 'bool',
        int: 'long',
        long: 'pythran_long_def',
        float: 'double',
        str: 'core::string',
        None: 'void',
        }

type_to_suffix = {
        int: "L",
        long: "LL",
        }

builtin_constants = {
    "True": "bool",
    "False": "bool",
    "None": "none_type"
    }

builtin_constructors = {
        'int': pytype_to_ctype_table[int],
        'float': pytype_to_ctype_table[float],
        'bool': pytype_to_ctype_table[bool],
        'long': pytype_to_ctype_table[long],
        }

cxx_keywords = {
        'and', 'and_eq', 'asm', 'auto', 'bitand', 'bitor',
        'break', 'case', 'catch', 'char', 'class',
        'compl', 'const', 'const_cast', 'continue', 'default', 'delete',
        'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit',
        'export', 'extern', 'false', 'for', 'friend',
        'goto', 'if', 'inline', 'mutable', 'namespace', 'new', 'not',
        'not_eq', 'operator', 'or', 'or_eq', 'private', 'protected', 'public',
        'register', 'reinterpret_cast', 'return', 'short', 'signed', 'sizeof',
        'static', 'static_cast',
        'struct', 'switch', 'template', 'this', 'throw', 'true',
        'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned',
        'using', 'virtual', 'void', 'volatile', 'wchar_t', 'while',
        'xor', 'xor_eq',
        # C++11 additions
        'constexpr', 'decltype', 'noexcept', 'nullptr', 'static_assert',
        # reserved namespaces
        'std',
        }

operator_to_lambda = {
        # boolop
        ast.And: lambda l, r: "(({0})?({1}):({0}))".format(l, r),
        ast.Or: lambda l, r: "(({0})?({0}):({1}))".format(l, r),
        # operator
        ast.Add: lambda l, r: "({0} + {1})".format(l, r),
        ast.Sub: lambda l, r: "({0} - {1})".format(l, r),
        ast.Mult: lambda l, r: "({0} * {1})".format(l, r),
        ast.Div: lambda l, r: "({0} / {1})".format(l, r),
        ast.Mod: lambda l, r: "({0} % {1})".format(l, r),
        ast.Pow: lambda l, r: "(pow({0}, {1}))".format(l, r),
        ast.LShift: lambda l, r: "({0} << {1})".format(l, r),
        ast.RShift: lambda l, r: "({0} >> {1})".format(l, r),
        ast.BitOr: lambda l, r: "({0} | {1})".format(l, r),
        ast.BitXor: lambda l, r: "({0} ^ {1})".format(l, r),
        ast.BitAnd: lambda l, r: "({0} & {1})".format(l, r),
        #** assume from __future__ import division
        ast.FloorDiv: lambda l, r: "(floordiv({0}, {1}))".format(l, r),
        # unaryop
        ast.Invert: lambda o: "(~{0})".format(o),
        ast.Not: lambda o: "(not {0})".format(o),
        ast.UAdd: lambda o: "(+{0})".format(o),
        ast.USub: lambda o: "(-{0})".format(o),
        # cmpop
        ast.Eq: lambda l, r: "({0} == {1})".format(l, r),
        ast.NotEq: lambda l, r: "({0} != {1})".format(l, r),
        ast.Lt: lambda l, r: "({0} < {1})".format(l, r),
        ast.LtE: lambda l, r: "({0} <= {1})".format(l, r),
        ast.Gt: lambda l, r: "({0} > {1})".format(l, r),
        ast.GtE: lambda l, r: "({0} >= {1})".format(l, r),
        ast.Is: lambda l, r: "(id({0}) == id({1}))".format(l, r),
        ast.IsNot: lambda l, r: "(id({0}) != id({1}))".format(l, r),
        ast.In: lambda l, r: "(in({1}, {0}))".format(l, r),
        ast.NotIn: lambda l, r: "(not in({1}, {0}))".format(l, r),
        }

# each module consist in a module_name <> set of symbols
modules = {
        "__builtins__": {
            "abs": ConstFunctionIntr(),
            "BaseException": ConstFunctionIntr(),
            "SystemExit": ConstFunctionIntr(),
            "KeyboardInterrupt": ConstFunctionIntr(),
            "GeneratorExit": ConstFunctionIntr(),
            "Exception": ConstFunctionIntr(),
            "StopIteration": ConstFunctionIntr(),
            "StandardError": ConstFunctionIntr(),
            "Warning": ConstFunctionIntr(),
            "BytesWarning": ConstFunctionIntr(),
            "UnicodeWarning": ConstFunctionIntr(),
            "ImportWarning": ConstFunctionIntr(),
            "FutureWarning": ConstFunctionIntr(),
            "UserWarning": ConstFunctionIntr(),
            "SyntaxWarning": ConstFunctionIntr(),
            "RuntimeWarning": ConstFunctionIntr(),
            "PendingDeprecationWarning": ConstFunctionIntr(),
            "DeprecationWarning": ConstFunctionIntr(),
            "BufferError": ConstFunctionIntr(),
            "ArithmeticError": ConstFunctionIntr(),
            "AssertionError": ConstFunctionIntr(),
            "AttributeError": ConstFunctionIntr(),
            "EnvironmentError": ConstFunctionIntr(),
            "EOFError": ConstFunctionIntr(),
            "ImportError": ConstFunctionIntr(),
            "LookupError": ConstFunctionIntr(),
            "MemoryError": ConstFunctionIntr(),
            "NameError": ConstFunctionIntr(),
            "ReferenceError": ConstFunctionIntr(),
            "RuntimeError": ConstFunctionIntr(),
            "SyntaxError": ConstFunctionIntr(),
            "SystemError": ConstFunctionIntr(),
            "TypeError": ConstFunctionIntr(),
            "ValueError": ConstFunctionIntr(),
            "FloatingPointError": ConstFunctionIntr(),
            "OverflowError": ConstFunctionIntr(),
            "ZeroDivisionError": ConstFunctionIntr(),
            "IOError": ConstFunctionIntr(),
            "OSError": ConstFunctionIntr(),
            "WindowsError": ConstFunctionIntr(),
            "VMSError": ConstFunctionIntr(),
            "IndexError": ConstFunctionIntr(),
            "KeyError": ConstFunctionIntr(),
            "UnboundLocalError": ConstFunctionIntr(),
            "NotImplementedError": ConstFunctionIntr(),
            "IndentationError": ConstFunctionIntr(),
            "TabError": ConstFunctionIntr(),
            "UnicodeError": ConstFunctionIntr(),
            #  "UnicodeDecodeError": ConstFunctionIntr(),
            #  "UnicodeEncodeError": ConstFunctionIntr(),
            #  "UnicodeTranslateError": ConstFunctionIntr(),
            "all": ConstFunctionIntr(),
            "any": ConstFunctionIntr(),
            "bin": ConstFunctionIntr(),
            "chr": ConstFunctionIntr(),
            "cmp": ConstFunctionIntr(),
            "complex": ConstFunctionIntr(),
            "dict": ConstFunctionIntr(),
            "divmod": ConstFunctionIntr(),
            "enumerate": ConstFunctionIntr(),
            "filter": ConstFunctionIntr(),
            "hex": ConstFunctionIntr(),
            "id": ConstFunctionIntr(),
            "len": ConstFunctionIntr(),
            "list": ConstFunctionIntr(),
            "map": ConstFunctionIntr(),
            "max": ConstFunctionIntr(),
            "min": ConstFunctionIntr(),
            "oct": ConstFunctionIntr(),
            "pow": ConstFunctionIntr(),
            "range": ConstFunctionIntr(),
            "reduce": ConstFunctionIntr(),
            "reversed": ConstFunctionIntr(),
            "round": ConstFunctionIntr(),
            "set": ConstFunctionIntr(),
            "sorted": ConstFunctionIntr(),
            "str": ConstFunctionIntr(),
            "sum": ConstFunctionIntr(),
            "tuple": ConstFunctionIntr(),
            "xrange": ConstFunctionIntr(),
            "zip": ConstFunctionIntr(),
            # pythran extensions
            "bind0": FunctionIntr(),
            "bind1": FunctionIntr(),
            "bind2": FunctionIntr(),
            "bind3": FunctionIntr(),
            "pmap":  ConstFunctionIntr(),
            },
        "time": {
                "sleep": ConstFunctionIntr(),
            },
        "math": {
                "isinf": ConstFunctionIntr(),
                "modf": ConstFunctionIntr(),
                "frexp": ConstFunctionIntr(),
                "factorial": ConstFunctionIntr(),
                "gamma": ConstFunctionIntr(),
                "lgamma": ConstFunctionIntr(),
                "trunc": ConstFunctionIntr(),
                "erf": ConstFunctionIntr(),
                "erfc": ConstFunctionIntr(),
                "asinh": ConstFunctionIntr(),
                "atanh": ConstFunctionIntr(),
                "acosh": ConstFunctionIntr(),
                "radians": ConstFunctionIntr(),
                "degrees": ConstFunctionIntr(),
                "hypot": ConstFunctionIntr(),
                "tanh": ConstFunctionIntr(),
                "cosh": ConstFunctionIntr(),
                "sinh": ConstFunctionIntr(),
                "atan": ConstFunctionIntr(),
                "atan2": ConstFunctionIntr(),
                "asin": ConstFunctionIntr(),
                "tan": ConstFunctionIntr(),
                "log": ConstFunctionIntr(),
                "log1p": ConstFunctionIntr(),
                "expm1": ConstFunctionIntr(),
                "ldexp": ConstFunctionIntr(),
                "fmod": ConstFunctionIntr(),
                "fabs": ConstFunctionIntr(),
                "copysign": ConstFunctionIntr(),
                "acos": ConstFunctionIntr(),
                "cos": ConstFunctionIntr(),
                "sin": ConstFunctionIntr(),
                "exp": ConstFunctionIntr(),
                "sqrt": ConstFunctionIntr(),
                "log10": ConstFunctionIntr(),
                "isnan": ConstFunctionIntr(),
                "ceil": ConstFunctionIntr(),
                "floor": ConstFunctionIntr(),
                "pow": ConstFunctionIntr(),
                "pi": ScalarIntr(),
                "e": ScalarIntr(),
                },
        "cmath": {
                "cos": FunctionIntr(),
                "sin": FunctionIntr(),
                "exp": FunctionIntr(),
                "sqrt": FunctionIntr(),
                "log10": FunctionIntr(),
                "isnan": FunctionIntr(),
                "pi": ScalarIntr(),
                "e": ScalarIntr(),
                },
        "random": {
                "seed": FunctionIntr(global_effects=True),
                "random": FunctionIntr(global_effects=True),
                "gauss": FunctionIntr(global_effects=True),
                "uniform": FunctionIntr(global_effects=True),
                "expovariate": FunctionIntr(global_effects=True),
                "sample": FunctionIntr(global_effects=True)
                },
        "omp": {
                "set_num_threads": FunctionIntr(global_effects=True),
                "get_num_threads": FunctionIntr(global_effects=True),
                "get_max_threads": FunctionIntr(global_effects=True),
                "get_thread_num": FunctionIntr(global_effects=True),
                "get_num_procs": FunctionIntr(global_effects=True),
                "in_parallel": FunctionIntr(global_effects=True),
                "set_dynamic": FunctionIntr(global_effects=True),
                "get_dynamic": FunctionIntr(global_effects=True),
                "set_nested": FunctionIntr(global_effects=True),
                "get_nested": FunctionIntr(global_effects=True),
                "init_lock": FunctionIntr(global_effects=True),
                "destroy_lock": FunctionIntr(global_effects=True),
                "set_lock": FunctionIntr(global_effects=True),
                "unset_lock": FunctionIntr(global_effects=True),
                "test_lock": FunctionIntr(global_effects=True),
                "init_nest_lock": FunctionIntr(global_effects=True),
                "destroy_nest_lock": FunctionIntr(global_effects=True),
                "set_nest_lock": FunctionIntr(global_effects=True),
                "unset_nest_lock": FunctionIntr(global_effects=True),
                "test_nest_lock": FunctionIntr(global_effects=True),
                "get_wtime": FunctionIntr(global_effects=True),
                "get_wtick": FunctionIntr(global_effects=True),
                "set_schedule": FunctionIntr(global_effects=True),
                "get_schedule": FunctionIntr(global_effects=True),
                "get_thread_limit": FunctionIntr(global_effects=True),
                "set_max_active_levels": FunctionIntr(global_effects=True),
                "get_max_active_levels": FunctionIntr(global_effects=True),
                "get_level": FunctionIntr(global_effects=True),
                "get_ancestor_thread_num": FunctionIntr(global_effects=True),
                "get_team_size": FunctionIntr(global_effects=True),
                "get_active_level": FunctionIntr(global_effects=True),
                "in_final": FunctionIntr(global_effects=True),
                },
        "__list__": {
                "append": MethodIntr(
                    lambda self, node:
                    self.combine(
                        node.args[0],
                        node.args[1],
                        unary_op=lambda f: cxxtypes.ListType(f),
                        register=True)
                    ),
                "extend": MethodIntr(
                    lambda self, node:
                    self.combine(
                        node.args[0],
                        node.args[1],
                        register=True)
                    ),
                "index": ConstMethodIntr(),
                #"pop": MethodIntr(), forwarded
                "reverse": MethodIntr(),
                "sort": MethodIntr(),
                "count": ConstMethodIntr(),
                "insert": MethodIntr(
                    lambda self, node:
                    self.combine(
                        node.args[0],
                        node.args[2],
                        unary_op=lambda f: cxxtypes.ListType(f),
                        register=True)
                    ),
                },
        "__string__": {
                "find": ConstMethodIntr(),
                "join": ConstMethodIntr(),
                "capitalize": ConstMethodIntr(),
                "split": ConstMethodIntr(),
                "endswith": ConstMethodIntr(),
                },
        "__set__": {
                "add": MethodIntr(
                    lambda self, node:
                    self.combine(
                        node.args[0],
                        node.args[1],
                        unary_op=lambda f: cxxtypes.SetType(f),
                        register=True)
                    ),
                "discard": MethodIntr(),
                "isdisjoint": ConstMethodIntr(),
                "union_": ConstMethodIntr(lambda self, node:
                    [
                        self.combine(
                            node.args[0],
                            node_args_k,
                            unary_op=lambda f: cxxtypes.SetType(
                                cxxtypes.ContentType(f)),
                            register=True)
                        for node_args_k in node.args[1:]
                        ]
                    ),
                "intersection": ConstMethodIntr(lambda self, node:
                    [
                        self.combine(
                            node.args[0],
                            node_args_k,
                            unary_op=lambda f: cxxtypes.SetType(
                                cxxtypes.ContentType(f)),
                            register=True)
                        for node_args_k in node.args[1:]
                        ]
                    ),
                "intersection_update": MethodIntr(
                    lambda self, node:
                    [
                        self.combine(
                            node.args[0],
                            node_args_k,
                            unary_op=lambda f: cxxtypes.SetType(
                                cxxtypes.ContentType(f)),
                            register=True)
                        for node_args_k in node.args[1:]
                        ]
                    ),
                "difference": ConstMethodIntr(
                    lambda self, node:
                    [
                        self.combine(
                            node.args[0],
                            node_args_k,
                            unary_op=lambda f: cxxtypes.SetType(
                                cxxtypes.ContentType(f)),
                            register=True)
                        for node_args_k in node.args[1:]
                        ]
                    ),
                "difference_update": MethodIntr(
                    lambda self, node:
                    [
                        self.combine(
                            node.args[0],
                            node_args_k,
                            unary_op=lambda f: cxxtypes.SetType(
                                cxxtypes.ContentType(f)),
                            register=True)
                        for node_args_k in node.args[1:]
                        ]
                    ),
                "symmetric_difference": ConstMethodIntr(
                        lambda self, node:
                        [
                            self.combine(
                                node.args[0],
                                node_args_k,
                                unary_op=lambda f: cxxtypes.SetType(
                                    cxxtypes.ContentType(f)),
                                register=True)
                            for node_args_k in node.args[1:]
                            ]
                        ),
                "symmetric_difference_update": MethodIntr(
                        lambda self, node:
                        [
                            self.combine(
                                node.args[0],
                                node_args_k,
                                unary_op=lambda f: cxxtypes.SetType(
                                    cxxtypes.ContentType(f)),
                                register=True)
                            for node_args_k in node.args[1:]
                            ]
                        ),
                "issuperset": ConstMethodIntr(),
                "issubset": ConstMethodIntr(),
                },
        "__exception__": {
                "args": AttributeIntr(0),
                "errno": AttributeIntr(1),
                "strerror": AttributeIntr(2),
                "filename": AttributeIntr(3),
                },
        "__complex___": {
                "real": AttributeIntr(0),
                "imag": AttributeIntr(1),
                "conjugate": MethodIntr(),
                },
        "__dict__":  {
                "fromkeys": ConstFunctionIntr(),
                "get": ConstMethodIntr(),
                "has_key": ConstMethodIntr(),
                "items": MethodIntr(),
                "iteritems": MethodIntr(),
                "iterkeys": MethodIntr(),
                "itervalues": MethodIntr(),
                "keys": MethodIntr(),
                #"pop": MethodIntr(), forwarded
                "popitem": MethodIntr(),
                "setdefault": MethodIntr(
                    lambda self, node:
                    len(node.args) == 3 and
                    self.combine(
                        node.args[0],
                        node.args[1],
                        unary_op=lambda x: cxxtypes.DictType(
                            x,
                            self.result[node.args[2]]),
                        register=True),
                    return_alias=lambda node: {
                        ast.Subscript(node.args[0],
                            ast.Index(node.args[1]),
                            ast.Load())
                        }
                    ),
                "values": MethodIntr(),
                "viewitems": MethodIntr(),
                "viewkeys": MethodIntr(),
                "viewvalues": MethodIntr(),
                },
        "__iterator__": {
                "next": MethodIntr(),
                },
        # conflicting method names must be listed here
        "__dispatch__": {
                "clear": MethodIntr(),
                "copy": ConstMethodIntr(),
                "pop": MethodIntr(),
                "remove": MethodIntr(),
                "update": MethodIntr(
                    lambda self, node:
                    [
                        self.combine(
                            node.args[0],
                            node_args_k,
                            register=True)
                        for node_args_k in node.args[1:]
                        ]
                    ),
                },
        "__user__": {},
        }

# a method name to module binding
methods = {}
for module, elems in modules.iteritems():
    for elem, signature in elems.iteritems():
        if signature.ismethod():
            assert elem not in methods  # we need unicity
            methods[elem] = (module, signature)

# a function name to module binding
functions = {}
for module, elems in modules.iteritems():
    for elem, signature in elems.iteritems():
        if signature.isstaticfunction():
            functions.setdefault(elem, []).append((module, signature,))

# a attribute name to module binding
attributes = {}
for module, elems in modules.iteritems():
    for elem, signature in elems.iteritems():
        if signature.isattribute():
            assert elem not in attributes  # we need unicity
            attributes[elem] = (module, signature,)

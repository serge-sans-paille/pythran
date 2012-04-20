import ast
import sys, os.path
from cgen import *
from codepy.bpl import BoostPythonModule
import re
from subprocess import check_call, check_output

from passes import referenced_ids, forward_declarations, type_substitution, normalize_tuples
from tables import type_to_str, operator_to_lambda

# the value, if not None, is used to deduce the return type of the intrinsics if the default behavior is not satisfying (i.e. if lambdas are involved)
intrinsics = {
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
    }

templatize = lambda node, types: Template([ "typename " + t for t in types ], node ) if types else node 


class CgenVisitor(ast.NodeVisitor):
    """Generate Cgen tree from an ast tree"""

    return_type="return_type"

    def __init__(self, name, forward_declarations=set()):
        self.name=name
        self.typedefs=dict()
        self.typedeps=dict()
        self.counter=0
        self.declarations=set()
        self.gdeclarations=forward_declarations
        self.structures=list()

    def add_typedef(self, k, v, *deps):
        typename = "expression_type{0}".format(self.counter)
        existing = [ value for value in self.typedefs.itervalues() if value if value[0] == v ]
        if existing:
            self.typedefs[k]=( v, existing[0][1] )
        else:
            self.typedefs[k]=( v, typename)
            self.typedeps[typename]=set(deps)
            for d in deps:
                self.typedeps[typename].update(self.typedeps.get(d,set()))
            self.counter+=1

    def visit_Module(self, node):
        mod = BoostPythonModule()
        mod.use_private_namespace=False
        headers= [ "pythran/pythran.h", "utility", "boost/python/module.hpp", "boost/python/tuple.hpp", "boost/python/def.hpp" ]
        mod.add_to_preamble([Include(h) for h in headers])
        functions = [ self.visit(n) for n in node.body ]
        mod.add_to_module( self.structures + functions ) 
        header_name = self.name+".h"
        with file(header_name,"w") as module_header:
            m = mod.generate()
            m.contents.pop() # remove the boost part
            m.contents.pop() # remove the boost part
            m.contents.insert(1+len(headers), Statement("namespace {0} {{".format(self.name)))
            print >> module_header, m
            print >> module_header, '}'
        return header_name

    def visit_Interactive(self, node):
        raise NotImplementedError

    def visit_Expression(self, node):
        raise NotImplementedError

    def visit_Suite(self, node):
        raise NotImplementedError

    def visit_Delete(self, node):
        return Statement("")

    def visit_Break(self, node):
        return Statement("break")

    def visit_Assert(self, node):
        params = [ self.visit(node.msg) if node.msg else None, self.visit(node.test) ]
        return Statement("assert(({0}))".format(", ".join(p for p in params if p)))

    def visit_Continue(self, node):
        return Statement("continue")

    def visit_FunctionDef(self, node):
        fargs = node.args.args
        nargs = [ arg.id for arg in fargs ]

        cgv = CgenVisitor("<anonymous>", self.gdeclarations)
        cgv.name = node.name

        generic_types= [ "argument_type"+str(i) for i in xrange(len(fargs)) ]

        cgv.typedefs = { k:(k,v) for (k,v) in zip(nargs, generic_types ) }
        cgv.typedefs.update({ k:None for k in self.gdeclarations })
        cgv.typedeps = { k:set() for k in generic_types }
        cgv.declarations=set(nargs)

        cgv.typer = "type{0}::".format("<" + ", ".join(generic_types) +">" if generic_types else "")
        body = [ cgv.visit(n) for n in node.body ]

        if CgenVisitor.return_type not in cgv.typedefs:
            cgv.typedefs[CgenVisitor.return_type]= ("void",  CgenVisitor.return_type)

        convert = lambda text: int(text) if text.isdigit() else text 
        alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key[1]) ] 
        valid_typedefs = [ v for k,v in cgv.typedefs.iteritems() if not isinstance(k,str) or k == CgenVisitor.return_type if v if v[0] not in nargs]
        unique_typedefs = { k:v for k,v in valid_typedefs }.items()
        typedefs= sorted( unique_typedefs, key=alphanum_key)

        fscope = "type{0}::".format(
                "<{0}>".format(", ".join(generic_types)) if generic_types else ""
                )



        struct = Struct("type", [Typedef(Value(n,t)) for n,t in typedefs] )
        fdeclaration =  FunctionDeclaration( Value("typename "+fscope+CgenVisitor.return_type, "operator()"), 
                                    [ Value( t, "" ) for t in generic_types ] )

        topstruct = Struct(cgv.name, [ templatize(struct, generic_types), templatize(fdeclaration, generic_types), Statement("") ] )

        self.structures+= cgv.structures
        self.structures.append( topstruct )

        ffscope = cgv.name + "::" + fscope
        fdeclaration =  FunctionDeclaration(
                Value("typename "+ffscope+CgenVisitor.return_type, cgv.name+"::operator()"),
                [ Value( t, n ) for t,n in zip(generic_types, [ arg.id for arg in fargs ] ) ] )
        declarations = [ Statement("typename {0}{1} {2}".format(ffscope, cgv.typedefs[k][1], k)) for k in cgv.declarations if k not in nargs if k not in self.declarations]
        operator = FunctionBody(
                Template([ "typename " + t for t in generic_types ], fdeclaration ) if generic_types else fdeclaration,
                Block( declarations + body)
                )
        return operator 


    def visit_Pass(self, node):
        return Statement("")

    def visit_Expr(self, node):
        return Statement(self.visit(node.value))

    def visit_Return(self, node):
        if node.value:
            ret = self.visit(node.value)
            return_type = ( self.typedefs[node.value][1], CgenVisitor.return_type)
            self.typedefs[CgenVisitor.return_type] = return_type
            return Statement("return " + ret)
        else:
            self.typedefs[CgenVisitor.return_type] = ("void", CgenVisitor.return_type)
            return Statement("return")

    def visit_Print(self, node):
        if node.dest: raise NotImplementedError
        values = [ self.visit(n) for n in node.values]
        return Statement("print{0}({1})".format(
                "" if node.nl else "_nonl",
                ", ".join(values))
                )

    def visit_If(self, node):
        test = self.visit(node.test)
        body = [ self.visit(n) for n in node.body ]
        orelse = [ self.visit(n) for n in node.orelse ]
        return If(test, Block(body), Block(orelse) if orelse else None )

    def visit_While(self, node):
        test = self.visit(node.test)
        body = [ self.visit(n) for n in node.body ]
        orelse = [ self.visit(n) for n in node.orelse ]
        stmt = While(test, Block(body))
        return If(test, Block( body + [stmt]), Block(orelse)) if orelse else stmt 

    def visit_For(self, node):
        if not isinstance(node.target, ast.Name): raise NotImplementedError
        iter = self.visit(node.iter)
        self.add_typedef(node.target.id, "typename {0}::value_type".format(self.typedefs[node.iter][1]), self.typedefs[node.iter][1])
        target = self.visit(node.target)
        body = [ self.visit(n) for n in node.body ]
        orelse = [ self.visit(n) for n in node.orelse ]
        stmt = Statement("for(auto& {0}: {1}) {2}".format(target, iter, "".join([l for l in Block(body).generate()])))
        return If(iter, stmt, Block(orelse)) if orelse else stmt

    def visit_Assign(self, node):
        if len(node.targets) != 1: raise NotImplementedError
        if not isinstance(node.targets[0], ast.Name): raise NotImplementedError
        value = self.visit(node.value)
        if node.targets[0].id not in self.declarations:
            self.add_typedef(node.targets[0].id, self.typedefs[node.value][1], self.typedefs[node.value][1])
            self.declarations.add(node.targets[0].id)
        targets=[self.visit(n) for n in node.targets]
        return Statement("{0} = {1}".format(targets[0], value))

    def visit_AugAssign(self, node):
        value = self.visit(node.value)
        if not isinstance(node.target, ast.Name): raise NotImplementedError
        if node.target.id not in self.declarations:
            self.add_typedef(node.target.id, self.typedefs[node.value][1], self.typedefs[node.value][1])
            self.declarations.add(node.target.id)
        target=self.visit(node.target)
        op = operator_to_lambda[type(node.op)](target, value)
        return Statement("{0} = {1}".format(target, op))

    def visit_Name(self, node):
        if node.id in self.typedefs:
            self.typedefs[node] = self.typedefs[node.id]
        elif node.id == self.name:
            if CgenVisitor.return_type in self.typedefs:
                self.add_typedef(node, self.typedefs[CgenVisitor.return_type], self.typedefs[CgenVisitor.return_type][1])
            else:
                self.typedefs[node]=None
        elif node.id in intrinsics:
            pass #should be ok, as intrinsics are handled differently
        elif node.id in ["True", "False"]:
            self.add_typedef(node.id,"bool")
        else:
            print self.name, ":", node.id, self.typedefs
            raise NotImplementedError
        return node.id

    def visit_Lambda(self, node):
        lambda_name = "lambda{0}".format(len(self.structures))

        parameter_arguments = referenced_ids(node)
        [ parameter_arguments.difference_update( referenced_ids(n) ) for n in node.args.args  ]
        parameter_arguments = sorted(parameter_arguments)

        formal_arguments = [n.id for n in node.args.args]
        formal_types =  [ "argument_type{0}".format(n) for n in xrange(len(formal_arguments)) ]
        parameter_types = [ "parameter_type{0}".format(n) for n in xrange(len(parameter_arguments)) ]

        cgv = CgenVisitor("<lambda>", self.declarations)
        cgv.name = lambda_name
        cgv.typedefs = { k:(k,v) for (k,v) in zip(formal_arguments + parameter_arguments, formal_types + parameter_types) }
        body = cgv.visit(node.body)
        holder = templatize(
                Struct(lambda_name,
                    [ Statement( "{0} {1}".format(n, t) ) for n, t in zip(parameter_types, parameter_arguments) ] +
                    [ FunctionBody(
                        FunctionDeclaration(
                            Value("", lambda_name),
                            [Value("{0} const &".format(t), n)  for t,n in zip(parameter_types, parameter_arguments)]
                            ),
                        Block([Statement("this->{0} = {0}".format(n)) for n in parameter_arguments ])
                        ) ] +
                    [ FunctionBody(
                        templatize(
                            AutoFunctionDeclaration(
                                Value("auto", "operator()"),
                                [ Value("{0} const &".format(t), n)  for t,n in zip(formal_types, formal_arguments) ],
                                body
                                ),
                            formal_types),
                        Block([Statement("return {0}".format(body))])
                        ) ]
                    ),
                parameter_types)
        self.structures.append(holder)

        fully_qualified_lambda_name = "{0}{1}".format(lambda_name,
                "<"+", ".join(self.typedefs[p][1] for p in parameter_arguments)+">" if parameter_arguments else "")
        self.add_typedef(node, fully_qualified_lambda_name, *[self.typedefs[a] for a in parameter_arguments])

        return "{0}({1})".format(fully_qualified_lambda_name,
                ", ".join(parameter_arguments))

    def visit_Call(self, node):
        args = [ self.visit(n) for n in node.args[::-1] ][::-1] # reverse order to handle lambda calls
        func = self.visit(node.func)
        if func == self.name:
            if CgenVisitor.return_type in self.typedefs:
                self.add_typedef(node, self.typedefs[CgenVisitor.return_type], self.typedefs[CgenVisitor.return_type][1])
            else:
                self.typedefs[node]=None
        elif func in intrinsics and intrinsics[func]:
            intrinsics[func](self, node)
        else:
             self.add_typedef(node, "decltype({0}{1}({2}))".format(
                 "std::declval<{0}>()".format(self.typedefs[func][1]) if func in self.declarations else func,
                 "" if func in intrinsics or func in self.declarations else "()",
                 ", ".join([ "std::declval<{0}>()".format(self.typedefs[n][1]) for n in node.args] )), *[self.typedefs[n][1] for n in node.args])
        return "{0}{1}({2})".format(func, "" if func in intrinsics or func in self.declarations else "()", ", ".join(args))

    def visit_Compare(self, node):
        left = self.visit(node.left)
        ops = [ operator_to_lambda[type(n)] for n in node.ops ]
        comparators = [ self.visit(n) for n in node.comparators ]
        self.add_typedef(node, "bool")
        return reduce(lambda v,o: o[0](v,o[1]), zip( ops, comparators ), left)

    def visit_IfExp(self, node):
        test = self.visit(node.test)
        body = self.visit(node.body)
        orelse = self.visit(node.orelse)
        if self.typedefs[node.body] and self.typedefs[node.body][1] not in self.typedeps[ self.typedefs[node.body][1] ] :
            self.add_typedef( node, self.typedefs[node.body][1], self.typedefs[node.body][1] )
        elif self.typedefs[node.orelse] and self.typedefs[node.orelse][1] not in self.typedeps[ self.typedefs[node.orelse][1] ] :
            self.add_typedef( node, self.typedefs[node.orelse][1], self.typedefs[node.orelse][1] )
        else:
            raise RuntimeError
        return "{0} ? {1} : {2}".format(test, body, orelse)

    def visit_Str(self, node):
        self.add_typedef(node, "std::string")
        return '"{0}"'.format(node.s)

    def visit_Num(self, node):
        self.add_typedef(node, type_to_str[type(node.n)])
        return str(node.n)

    def visit_Index(self, node):
        value = self.visit(node.value)
        self.add_typedef(node, self.typedefs[node.value][1], self.typedefs[node.value][1])
        return value

    def visit_Slice(self, node):
        raise NotImplementedError


    def visit_Subscript(self, node):
        value = self.visit(node.value)
        slice = self.visit(node.slice)
        is_constant_expression = lambda s: re.sub(r'[a-zA-Z_ \t]','',s)
        if is_constant_expression(slice):
            self.add_typedef(node, "typename std::tuple_element<{0}, {1}>::type".format(slice, self.typedefs[node.value][1]), self.typedefs[node.value][1])
            return "std::get<{0}>({1})".format(slice, value)
        else:
            self.add_typedef(node, "typename {1}::value_type".format(self.typedefs[node.value][1]), self.typedefs[node.value][1])
            return "{1}[{0}]".format(slice, value)


    def visit_BinOp(self, node):
        left = self.visit(node.left)
        right= self.visit(node.right)
        op = operator_to_lambda[type(node.op)]
        if not self.typedefs[node.left] or not self.typedefs[node.right]:
            self.typedefs[node]=None
        else:
            self.add_typedef(node, "decltype({0})".format(op("std::declval<{0}>()".format(self.typedefs[node.left][1]) , "std::declval<{0}>()".format(self.typedefs[node.right][1]))), *[self.typedefs[node.left][1], self.typedefs[node.right][1]] )
        return op(left,right)

    def visit_comprehension(self, node):
        #(expr target, expr iter, expr* ifs)
        ifs = [ self.visit(n) for n in node.ifs ]
        if ifs : raise NotImplementedError
        iter = self.visit(node.iter)
        if isinstance(node.target, ast.Name):
            self.add_typedef(node.target.id, "typename {0}::value_type".format(self.typedefs[node.iter][1]), self.typedefs[node.iter][1])
        else: raise NotImplementedError
        target = self.visit(node.target)
        return ast.comprehension(target, iter, ifs )

    def visit_ListComp(self, node):
        generators = [ self.visit(n) for n in node.generators ]
        elt = self.visit(node.elt)
        self.add_typedef(node, "sequence<{0}>".format( self.typedefs[node.elt][1] ), self.typedefs[node.elt][1])
        lambda_expr = "[&] ( {0} ) {{ return {1} ; }}".format( ", ".join( [ "typename "+self.typer+self.typedefs[g.target][1] + " const & " + g.target for g in generators ] ), elt)
        return "map({0}, {1})".format(lambda_expr, ", ".join(g.iter for g in generators))
pytype_to_ctype_table = {
        'bool'          : 'bool',
        'int'           : 'long',
        'float'         : 'double',
        'string'        : 'std::string',
        'None'          : 'void',
        }

def pytype_to_ctype(t):
    if t in pytype_to_ctype_table: return pytype_to_ctype_table[t]
    else:
        tokens = t.split()
        if tokens[-1] == "list":
            return 'sequence<{0}>'.format(pytype_to_ctype(" ".join(tokens[:-1])))
        elif tokens[-1] == "tuple":
            return 'std::tuple<{0}>'.format(", ".join(pytype_to_ctype(t) for t in tokens[:-1])) # fragile
        else:
            raise NotImplementedError

######

def python_interface(module_name, code, **specializations):

    from codepy.jit import guess_toolchain
    tc = guess_toolchain()
    tc.include_dirs.append(".")
    tc.cflags.append("-std=c++0x")
    tc.include_dirs+=[ p for p in sys.path if os.path.exists(os.path.join(p,"pythran.h")) ]

    check_call(["pkg-config", "pythonic++", "--exists"])
    cflags = check_output(["pkg-config", "pythonic++", "--cflags"]).strip()
    tc.cflags.append(cflags)

    ir=ast.parse(code)
    normalize_tuples(ir)
    fwd_decl =  forward_declarations(ir)
    CgenVisitor(module_name, fwd_decl).visit(ir)


    mod=BoostPythonModule()
    header = module_name + ".h"
    mod.use_private_namespace=False
    mod.add_to_preamble([Include(header)])
    for k,v in specializations.iteritems():
        vl = v if isinstance(v, tuple) else [v,]
        arguments_types = [pytype_to_ctype(t) for t in vl ]
        arguments = ["a"+str(i) for i in xrange(len(arguments_types))]
        boost_arguments_types = [ "boost::python::list" if at.startswith("sequence<") else 
                "boost::python::tuple" if at .startswith("std::tuple<") else at
                for at in arguments_types ]
        boost_arguments = [ "to_sequence<{0}>({1})".format(at,a) if at.startswith("sequence<") else 
            "to_tuple<{0}>({1})".format(at,a) if at.startswith("std::tuple<") else a
            for (a,at) in zip(arguments, arguments_types) ]
        specialized_fname = "{0}::{1}::type{2}".format(module_name, 
                k,
                ("<"+", ".join(arguments_types)+">") if arguments_types else ""
                )
        return_type = "typename fwd<typename {0}::return_type>::type".format(specialized_fname)
        mod.add_function(
                FunctionBody(
                    FunctionDeclaration( Value(return_type, k), [ Value( t, "a"+str(i) ) for i,t in enumerate(boost_arguments_types) ]),
                    Block([ Statement("return Fwd< {0}, typename {1}::return_type>()({2})".format(
                        module_name+"::"+k,
                        specialized_fname,
                        ', '.join(boost_arguments) ) ) ] )
                    )
                )

    #print mod.generate()

    pymod = mod.compile(tc, wait_on_error=True)
    return pymod

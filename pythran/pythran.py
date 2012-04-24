import ast
import sys, os.path
from cgen import *
from codepy.bpl import BoostPythonModule
import re
from subprocess import check_call, check_output

from passes import imported_ids, forward_declarations, normalize_tuples
from tables import type_to_str, operator_to_lambda, modules

templatize = lambda node, types: Template([ "typename " + t for t in types ], node ) if types else node 


class CgenVisitor(ast.NodeVisitor):
    """Generate Cgen tree from an ast tree"""

    return_type="return_type"

    def __init__(self, name, external_symbols, structure_declarations, structure_definitions):
        self.name=name
        self.external_symbols= external_symbols
        self.typedefs = { k:None for k in external_symbols }
        self.typedeps=dict()
        self.counter=0
        self.declarations=set()
        self.structure_declarations=structure_declarations
        self.structure_definitions=structure_definitions
        self.renamings=dict()

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
        body = [ self.visit(n) for n in node.body ]
        mod.add_to_module( body + self.structure_declarations + self.structure_definitions ) 
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

    def visit_ImportFrom(self, node):
        if node.level != 0: raise NotImplementedError
        if not node.module: raise NotImplementedError
        module = node.module
        if module not in modules: raise NotImplementedError

        names = node.names
        if [ alias for alias in names if alias.asname ]: raise NotImplementedError

        for alias in names:
            self.typedefs[alias.name]=(alias.name, None)

        return Statement("; ".join(["using {0}::proxy::{1} ".format(module, alias.name) for alias in names]))

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

        cgv = CgenVisitor("<anonymous>", self.external_symbols.union({ k for k,v in self.typedefs.iteritems() if not v or not v[1] }),
                self.structure_declarations, self.structure_definitions)
        cgv.name = node.name

        generic_types= [ "argument_type"+str(i) for i in xrange(len(fargs)) ]

        cgv.typedefs.update({ k:(k,v) for (k,v) in zip(nargs, generic_types ) })
        cgv.typedeps = { k:set() for k in generic_types }
        cgv.declarations=set(nargs)

        imported_args = sorted(imported_ids(node, cgv.external_symbols))
        imported_types = [ "imported_type{0}".format(i) for i in xrange(len(imported_args)) ]
        cgv.typedefs.update( { k:(k,v) for (k,v) in zip(imported_args, imported_types ) } )


        cgv.typer = "type{0}::".format("<" + ", ".join(generic_types) +">" if generic_types else "")
        body = [ cgv.visit(n) for n in node.body ] 

        if CgenVisitor.return_type not in cgv.typedefs:
            cgv.typedefs[CgenVisitor.return_type]= ("void",  CgenVisitor.return_type)

        convert = lambda text: int(text) if text.isdigit() else text 
        alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key[1]) ] 
        valid_typedefs = [ v for k,v in cgv.typedefs.iteritems() if not isinstance(k,str) or k == CgenVisitor.return_type if v if v[0] not in nargs and v[0] not in imported_args]
        unique_typedefs = { k:v for k,v in valid_typedefs }.items()
        typedefs= sorted( unique_typedefs, key=alphanum_key)

        fscope = "type{0}::".format(
                "<{0}>".format(", ".join(generic_types)) if generic_types else ""
                )



        struct = Struct("type", [Typedef(Value(n,t)) for n,t in typedefs] )
        inner_fdeclaration =  templatize(FunctionDeclaration( Value("typename "+fscope+CgenVisitor.return_type, "operator()"), 
                                    [ Value( t, n ) for t,n in zip(generic_types, nargs) ] ), generic_types)



        declarations = [ Statement("typename {0}{1} {2}".format(fscope, cgv.typedefs[k][1], k)) for k in cgv.declarations if k not in nargs if k not in self.declarations]
        fully_qualified_name = "{0}<{1}>".format(cgv.name, ", ".join(self.typedefs[k][1] for k in imported_args)) if imported_args else cgv.name
        fully_qualified_inner_name = "{0}<{1}>".format(cgv.name, ", ".join(imported_types)) if imported_types else cgv.name
        ffscope = fully_qualified_inner_name + "::{0}".format("template " if imported_types else "") + fscope
        declarations = [ Statement("typename {0}{1} {2}".format(ffscope, cgv.typedefs[k][1], k)) for k in cgv.declarations if k not in nargs if k not in self.declarations]

        inner_members = [ Statement( "{0} const & {1}".format(n, t) ) for n, t in zip(imported_types, imported_args) ] + (
                [ FunctionBody(
                    ConstructorDeclaration(
                        Value("", cgv.name),
                        [Value("{0} const &".format(t), n)  for t,n in zip(imported_types, imported_args)],
                        ["{0}({0})".format(n) for n in imported_args ]
                        ),
                    Block([])
                    ) ] if imported_types else list() )


        fdeclaration =  FunctionDeclaration(
                Value("typename "+ffscope+CgenVisitor.return_type, "{0}{1}::operator()".format(cgv.name,"<{0}>".format(", ".join(imported_types)) if imported_types else "")),
                [ Value( t, n ) for t,n in zip(generic_types, nargs ) ] )
        fdeclaration = templatize(templatize(fdeclaration, generic_types), imported_types)
        definition = FunctionBody(
                fdeclaration,
                Block( declarations + body)
                )
        self.structure_definitions.append(definition)
        if imported_args:
            self.add_typedef(cgv.name, fully_qualified_name, *[self.typedefs[k][1] for k in imported_args])
        else:
            self.add_typedef(cgv.name,  cgv.name)

        topstruct = templatize(Struct(cgv.name, inner_members + [ templatize(struct, generic_types), inner_fdeclaration, Statement("") ] ), imported_types)
        self.structure_declarations.append(topstruct)

        if imported_types: # create a maker facility, in the spirit of make_tuple
            make_name = "make_{0}".format(cgv.name)
            make_body = "{0}<{1}>({2})".format(cgv.name, ", ".join(imported_types), ", ".join(imported_args))
            make_declaration = FunctionBody(
                    Template(["typename {0}".format(t) for t in imported_types], 
                        AutoFunctionDeclaration(
                                Value("auto", make_name),
                                [ Value("{0} const &".format(t), n)  for t,n in zip(imported_types, imported_args) ],
                                make_body)),
                        Block([Statement("return "+make_body)]))
            self.structure_declarations.append(make_declaration)
            self.renamings[cgv.name]=(make_name, imported_args)
        else:
            self.renamings[cgv.name]=(cgv.name, [])

        return Statement("") # no inner function declaration, not much compatible with templates


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
        if not isinstance(node.targets[0], ast.Name) and not isinstance(node.targets[0], ast.Subscript): raise NotImplementedError
        value = self.visit(node.value)
        if isinstance(node.targets[0], ast.Name):
            if node.targets[0].id not in self.declarations:
                self.declarations.add(node.targets[0].id)
                self.add_typedef(node.targets[0].id, self.typedefs[node.value][1], self.typedefs[node.value][1])
            else:
                self.add_typedef(node.targets[0].id, "decltype(std::declval<{0}>() + std::declval<{1}>())".format(self.typedefs[node.value][1], self.typedefs[node.targets[0].id][1]), *[self.typedefs[node.value][1], self.typedefs[node.targets[0].id][1]])
        targets=[self.visit(n) for n in node.targets]
        return Statement("{0} = {1}".format(targets[0], value))

    def visit_AugAssign(self, node):
        value = self.visit(node.value)
        if not isinstance(node.target, ast.Name): raise NotImplementedError
        if node.target.id not in self.declarations:
            self.declarations.add(node.target.id)
        self.add_typedef(node.target.id, self.typedefs[node.value][1], self.typedefs[node.value][1])
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
        elif node.id in modules["__builtins__"]:
            pass #should be ok, as builtins are handled differently
        elif node.id in ["True", "False"]:
            self.add_typedef(node.id,"bool")
        else:
            print self.name, ":", node.id, self.typedefs
            raise NotImplementedError
        if node.id in self.renamings:
            return "{0}({1})".format(self.renamings[node.id][0], ", ".join(self.renamings[node.id][1]))
        elif node.id in self.typedefs and ( not self.typedefs[node.id] or not self.typedefs[node.id][1] ):
            return node.id+"()"
        else:
            return node.id

    def visit_Lambda(self, node):
        lambda_name = "lambda{0}".format(len(self.structure_definitions))
        self.structure_definitions.append(Statement("")) # *** ugly

        parameter_arguments = sorted(imported_ids(node, { k for k,v in self.typedefs.iteritems() if not v or not v[1]}))

        formal_arguments = [n.id for n in node.args.args]
        formal_types =  [ "argument_type{0}".format(n) for n in xrange(len(formal_arguments)) ]
        parameter_types = [ "parameter_type{0}".format(n) for n in xrange(len(parameter_arguments)) ]

        cgv = CgenVisitor("<lambda>", self.declarations, self.structure_declarations, self.structure_definitions)
        cgv.name = lambda_name
        cgv.typedefs = { k:(k,v) for (k,v) in zip(formal_arguments + parameter_arguments, formal_types + parameter_types) }
        body = cgv.visit(node.body)
        holder = templatize(
                Struct(lambda_name,
                    [ Statement( "{0} const & {1}".format(n, t) ) for n, t in zip(parameter_types, parameter_arguments) ] +
                    [ FunctionBody(
                        ConstructorDeclaration(
                            Value("", lambda_name),
                            [Value("{0} const &".format(t), n)  for t,n in zip(parameter_types, parameter_arguments)],
                            ["{0}({0})".format(n) for n in parameter_arguments ]
                            ),
                        Block([])
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
        self.structure_declarations.append(holder)

        fully_qualified_lambda_name = "{0}{1}".format(lambda_name,
                "<"+", ".join(self.typedefs[p][1] for p in parameter_arguments)+">" if parameter_arguments else "")
        self.add_typedef(node, fully_qualified_lambda_name, *[self.typedefs[a] for a in parameter_arguments])

        return "{0}({1})".format(fully_qualified_lambda_name,
                ", ".join(parameter_arguments))

    def visit_Call(self, node):
        args = [ self.visit(n) for n in node.args ]
        func = self.visit(node.func)
        if func == "{0}()".format(self.name): # *** recursive call
            if CgenVisitor.return_type in self.typedefs:
                self.add_typedef(node, self.typedefs[CgenVisitor.return_type], self.typedefs[CgenVisitor.return_type][1])
            else:
                self.typedefs[node]=None
            func = "(*this)"
        elif func in modules["__builtins__"] and modules["__builtins__"][func]:
            modules["__builtins__"][func](self, node)
        else:
            self.add_typedef(node, "decltype({0}({1}))".format(
                 "std::declval<{0}>()".format(self.typedefs[func][1]) if func in self.declarations else func,
                 ", ".join([ "std::declval<{0}>()".format(self.typedefs[n][1]) for n in node.args] )), *[self.typedefs[n][1] for n in node.args])
        return "{0}({1})".format(func, ", ".join(args))

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
        is_constant_expression = lambda s: not re.sub(r'[+*/\-0-9]','',s)
        if is_constant_expression(slice):
            self.add_typedef(node, "typename std::tuple_element<{0}, {1}>::type".format(slice, self.typedefs[node.value][1]), self.typedefs[node.value][1])
            return "std::get<{0}>({1})".format(slice, value)
        else:
            self.add_typedef(node, "typename {0}::value_type".format(self.typedefs[node.value][1]), self.typedefs[node.value][1])
            return "{1}[{0}]".format(slice, value)

    def visit_Tuple(self, node):
        if not node.elts: # empty tuple
            self.add_typedef(node,"decltype(std::make_tuple())")
            return "std::make_tuple()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            self.add_typedef(node, "std::tuple<{0}>".format(", ".join( self.typedefs[n][1] for n in node.elts )), *[self.typedefs[n][1] for n in node.elts])
            return "std::make_tuple({0})".format(", ".join(elts))

    def visit_List(self, node):
        if not node.elts: # empty list
            self.add_typedef(node, "decltype(list())")
            return "list()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            self.add_typedef(node, "sequence<decltype({0})>".format(" + ".join("std::declval<{0}>()".format(self.typedefs[n][1]) for n in node.elts)), *[self.typedefs[n][1] for n in node.elts])
            return "sequence< decltype({0})>({{ {1} }})".format(" + ".join(elts), ", ".join(elts))

    def visit_UnaryOp(self, node):
        operand = self.visit(node.operand)
        op = operator_to_lambda[type(node.op)]
        if not self.typedefs[node.operand]:
            self.typedefs[node]=None
        else:
            self.add_typedef(node, "decltype({0})".format(op("std::declval<{0}>()".format(self.typedefs[node.operand][1]))), self.typedefs[node.operand][1])
        return op(operand)


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
    CgenVisitor(module_name, fwd_decl, list(), list()).visit(ir)


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
        boost_arguments = [ "from_python<{0}>()({1})".format(at,a) if at.startswith("sequence<") or at.startswith("std::tuple<") else a
            for (a,at) in zip(arguments, arguments_types) ]
        specialized_fname = "{0}::{1}::type{2}".format(module_name, 
                k,
                ("<"+", ".join(arguments_types)+">") if arguments_types else ""
                )
        return_type = "typename to_python<typename {0}::return_type>::type".format(specialized_fname)
        mod.add_function(
                FunctionBody(
                    FunctionDeclaration( Value(return_type, k), [ Value( t, "a"+str(i) ) for i,t in enumerate(boost_arguments_types) ]),
                    Block([ Statement("return ToPython< {0}, typename {1}::return_type>()({2})".format(
                        module_name+"::"+k,
                        specialized_fname,
                        ', '.join(boost_arguments) ) ) ] )
                    )
                )

    #print mod.generate()

    pymod = mod.compile(tc, wait_on_error=True)
    return pymod

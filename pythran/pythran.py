import ast
from cgen import *
import re

from passes import imported_ids
from tables import type_to_str, operator_to_lambda, modules

templatize = lambda node, types: Template([ "typename " + t for t in types ], node ) if types else node 
is_constant_expression = lambda s: not re.sub(r'[+*/\-0-9]','',s)

class PythranSyntaxError(SyntaxError):
    def __init__(self, msg, node):
        SyntaxError.__init__(self,msg)
        self.lineno=node.lineno
        self.offset=node.col_offset


class CgenVisitor(ast.NodeVisitor):
    """Generate Cgen tree from an ast tree"""

    return_type="return_type"

    def __init__(self, name, parent):
        self.name=name
        self.external_symbols= parent.external_symbols
        self.typedefs = { k:None for k in parent.external_symbols }
        self.typedefs.update({k:None for k in { n for n,v in parent.typedefs.iteritems() if not v or not v[1] } })
        self.counter=0
        self.declarations=set()
        self.structure_declarations=parent.structure_declarations
        self.structure_definitions=parent.structure_definitions
        self.renamings=dict()

    def add_typedef(self, k, v):
        typename = "expression_type{0}".format(self.counter)
        assert not isinstance(k,tuple)
        assert not isinstance(v,tuple)
        self.typedefs[k]=( v, typename)
        self.counter+=1

    def visit_Module(self, node):
        headers= [ Include(h) for h in [ "pythran/pythran.h", "utility", "boost/python/module.hpp", "boost/python/tuple.hpp", "boost/python/def.hpp" ] ]
        body = [ self.visit(n) for n in node.body ]
        return headers +  [Namespace(self.name, body + self.structure_declarations + self.structure_definitions) ]

    def visit_Interactive(self, node):
        raise PythranSyntaxError("Interactive session are not supported", node)

    def visit_Expression(self, node):
        raise PythranSyntaxError("Top-Level expressions are not supported", node)

    def visit_Suite(self, node):
        raise PythranSyntaxError("Suite are specific to Jython and not supported", node)

    def visit_Delete(self, node):
        return EmptyStatement()

    def visit_ImportFrom(self, node):
        if node.level != 0: raise PythranSyntaxError("Specifying a level in an import", node)
        if not node.module: raise PythranSyntaxError("The import from syntax without module", node)
        module = node.module
        if module not in modules: raise PythranSyntaxError("Module '{0}'".format(module), node)

        names = node.names
        if [ alias for alias in names if alias.asname ]: raise PythranSyntaxError("Renaming using the 'as' keyword in an import", node)

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

        cgv = CgenVisitor("<anonymous>", self)
        cgv.name = node.name

        generic_types= [ "argument_type"+str(i) for i in xrange(len(fargs)) ]

        cgv.typedefs.update({ k:(k,v) for (k,v) in zip(nargs, generic_types ) })
        cgv.declarations=set(nargs)

        imported_args = sorted(imported_ids(node, { k for k,v in cgv.typedefs.iteritems() if not v}))#cgv.external_symbols))
        imported_types = [ "imported_type{0}".format(i) for i in xrange(len(imported_args)) ]
        cgv.typedefs.update( { k:(k,v) for (k,v) in zip(imported_args, imported_types ) } )


        cgv.typer = "type{0}::".format("<" + ", ".join(generic_types) +">" if generic_types else "")
        body = [ cgv.visit(n) for n in node.body ] 

        if CgenVisitor.return_type not in cgv.typedefs:
            cgv.typedefs[CgenVisitor.return_type]= ("void",  CgenVisitor.return_type)

        local_declarations = [ k for k in cgv.declarations if k not in nargs if k not in self.declarations ]

        convert = lambda text: int(text) if text.isdigit() else text 
        alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key[1]) ] 
        valid_typedefs = [ v for k,v in cgv.typedefs.iteritems() if v and v[1] and v[1].startswith("expression_type") ]
        valid_typedefs.append(cgv.typedefs[CgenVisitor.return_type])
        unique_typedefs = [ (k,v) for v,k in { v:k for (k,v) in valid_typedefs }.iteritems() ] # we want unique keys, not unique values ...
        typedefs= sorted( unique_typedefs, key=alphanum_key)

        fscope = "type{0}::".format(
                "<{0}>".format(", ".join(generic_types)) if generic_types else ""
                )



        struct = Struct("type", [Typedef(Value(n,t)) for n,t in typedefs] )
        inner_fdeclaration =  templatize(FunctionDeclaration( Value("typename "+fscope+CgenVisitor.return_type, "operator()"), 
                                    [ Value( t, n ) for t,n in zip(generic_types, nargs) ] ), generic_types)



        declarations = [ Statement("typename {0}{1} {2}".format(fscope, cgv.typedefs[k][1], k)) for k in local_declarations]
        fully_qualified_name = "{0}<{1}>".format(cgv.name, ", ".join(self.typedefs[k][1] for k in imported_args)) if imported_args else cgv.name
        fully_qualified_inner_name = "{0}<{1}>".format(cgv.name, ", ".join(imported_types)) if imported_types else cgv.name
        ffscope = fully_qualified_inner_name + "::{0}".format("template " if imported_types else "") + fscope
        declarations = [ Statement("typename {0}{1} {2}".format(ffscope, cgv.typedefs[k][1], k)) for k in local_declarations]

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
            self.add_typedef(cgv.name, fully_qualified_name)
        else:
            self.add_typedef(cgv.name,  cgv.name)

        topstruct = templatize(Struct(cgv.name, inner_members + [ templatize(struct, generic_types), inner_fdeclaration, EmptyStatement() ] ), imported_types)
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

        return EmptyStatement() # no inner function declaration, not much compatible with templates


    def visit_Pass(self, node):
        return EmptyStatement()

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
        if node.dest: raise PythranSyntaxError("Printing to a specific stream", node.dest)
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
        if not isinstance(node.target, ast.Name):
            raise PythranSyntaxError("Using something other than an identifier as loop target", node.target)
        iter = self.visit(node.iter)
        self.add_typedef(node.target.id, "typename {0}::value_type".format(self.typedefs[node.iter][1]))
        target = self.visit(node.target)
        body = [ self.visit(n) for n in node.body ]
        orelse = [ self.visit(n) for n in node.orelse ]
        stmt = AutoFor(target, iter, Block(body))
        return If(iter, stmt, Block(orelse)) if orelse else stmt

    def visit_Assign(self, node):
        if not all([isinstance(n, ast.Name) or isinstance(n, ast.Subscript) for n in node.targets]) :
            raise PythranSyntaxError("Assigning to something other than an identifier or a subscript", node)
        value = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                if t.id not in self.declarations:
                    self.declarations.add(t.id)
                    self.add_typedef(t.id, self.typedefs[node.value][1])
                else:
                    self.add_typedef(t.id, "decltype(std::declval<{0}>() + std::declval<{1}>())".format(self.typedefs[node.value][1], self.typedefs[t.id][1]))

        targets=[self.visit(t) for t in node.targets]
        return Statement("{0} = {1}".format("= ".join(targets), value))

    def visit_AugAssign(self, node):
        value = self.visit(node.value)
        if not isinstance(node.target, ast.Name):
            raise PythranSyntaxError("Assigning to something other than an identifier", node)
        if node.target.id not in self.declarations:
            self.declarations.add(node.target.id)
        self.add_typedef(node.target.id, self.typedefs[node.value][1])
        target=self.visit(node.target)
        op = operator_to_lambda[type(node.op)](target, value)
        return Statement("{0} = {1}".format(target, op))

    def visit_Name(self, node):
        if node.id in self.external_symbols:
            self.add_typedef(node, node.id)
        elif node.id in self.typedefs:
            self.typedefs[node] = self.typedefs[node.id]
        elif node.id in modules["__builtins__"]:
            self.add_typedef(node, "proxy::{0}".format(node.id))
            return "proxy::"+node.id+"()"
        elif node.id in ["True", "False"]:
            self.add_typedef(node.id,"bool")
        else:
            raise RuntimeError("I did not manage to construct a type for identifier {0}".format(node.id))
        if node.id in self.renamings:
            return "{0}({1})".format(self.renamings[node.id][0], ", ".join(self.renamings[node.id][1]))
        elif node.id in self.typedefs and ( not self.typedefs[node.id] or not self.typedefs[node.id][1] ):
            return node.id+"()"
        else:
            return node.id

    def visit_Lambda(self, node):
        lambda_name = "lambda{0}".format(len(self.structure_definitions))
        self.structure_definitions.append(EmptyStatement()) # *** ugly

        parameter_arguments = sorted(imported_ids(node, { k for k,v in self.typedefs.iteritems() if not v or not v[1]}))

        formal_arguments = [n.id for n in node.args.args]
        formal_types =  [ "argument_type{0}".format(n) for n in xrange(len(formal_arguments)) ]
        parameter_types = [ "parameter_type{0}".format(n) for n in xrange(len(parameter_arguments)) ]

        cgv = CgenVisitor("<lambda>", self)
        cgv.name = lambda_name
        cgv.typedefs.update({ k:(k,v) for (k,v) in zip(formal_arguments + parameter_arguments, formal_types + parameter_types) })
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
        self.add_typedef(node, fully_qualified_lambda_name)

        return "{0}({1})".format(fully_qualified_lambda_name,
                ", ".join(parameter_arguments))

    def visit_Call(self, node):
        args = [ self.visit(n) for n in node.args ]
        if isinstance(node.func,ast.Name) and node.func.id not in self.declarations and node.func.id in modules["__builtins__"]:
            func = node.func.id
        else:
            func = self.visit(node.func)
        self.add_typedef(node, "decltype({0}({1}))".format(
            "std::declval<{0}>()".format(self.typedefs[func][1]) if func in self.declarations else func,
            ", ".join([ "std::declval<{0}>()".format(self.typedefs[n][1]) for n in node.args] )))
        return "{0}({1})".format(func, ", ".join(args))

    def visit_Compare(self, node):
        left = self.visit(node.left)
        ops = [ operator_to_lambda[type(n)] for n in node.ops ]
        comparators = [ self.visit(n) for n in node.comparators ]
        self.add_typedef(node, "bool")
        all_compare = zip( [left]+comparators[:-1], ops, comparators )
        return " and ".join(op(l,r) for l,op,r in all_compare)

    def visit_IfExp(self, node):
        test = self.visit(node.test)
        body = self.visit(node.body)
        orelse = self.visit(node.orelse)
        self.add_typedef( node, "decltype(std::declval<{0}>()+std::declval<{1}>())",self.typedefs[node.body][1], self.typedefs[node.orelse])
        return "{0} ? {1} : {2}".format(test, body, orelse)

    def visit_Str(self, node):
        self.add_typedef(node, "std::string")
        return '"{0}"'.format(node.s)

    def visit_Num(self, node):
        self.add_typedef(node, type_to_str[type(node.n)])
        return str(node.n)

    def visit_Index(self, node):
        value = self.visit(node.value)
        self.add_typedef(node, self.typedefs[node.value][1])
        return value

    def visit_Slice(self, node):
        lower = self.visit(node.lower) if node.lower else None
        upper = self.visit(node.upper) if node.upper else None
        step = self.visit(node.step) if node.step else None
        if not upper and not lower and step: # special case
            raise NotImplementedError
        if step:
            if not upper: upper = "std::numeric_limits<long>::max()"
        if upper:
            if not lower: lower = "0"
        self.add_typedef(node, "slice")
        return "slice({0})".format(", ".join( l for l in [ lower, upper, step ] if l ))

    def visit_Subscript(self, node):
        value = self.visit(node.value)
        slice = self.visit(node.slice)
        if is_constant_expression(slice):
            self.add_typedef(node, "typename std::tuple_element<{0}, {1}>::type".format(slice, self.typedefs[node.value][1]))
            return "std::get<{0}>({1})".format(slice, value)
        else:
            self.add_typedef(node, "typename {0}::value_type".format(self.typedefs[node.value][1]))
            return "{1}[{0}]".format(slice, value)

    def visit_Tuple(self, node):
        if not node.elts: # empty tuple
            self.add_typedef(node,"decltype(std::make_tuple())")
            return "std::make_tuple()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            self.add_typedef(node, "std::tuple<{0}>".format(", ".join( self.typedefs[n][1] for n in node.elts )))
            return "std::make_tuple({0})".format(", ".join(elts))

    def visit_List(self, node):
        if not node.elts: # empty list
            self.add_typedef(node, "decltype(list())")
            return "list()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            self.add_typedef(node, "sequence<decltype({0})>".format(" + ".join("std::declval<{0}>()".format(self.typedefs[n][1]) for n in node.elts)))
            return "sequence< decltype({0})>({{ {1} }})".format(" + ".join(elts), ", ".join(elts))

    def visit_UnaryOp(self, node):
        operand = self.visit(node.operand)
        op = operator_to_lambda[type(node.op)]
        self.add_typedef(node, "decltype({0})".format(op("std::declval<{0}>()".format(self.typedefs[node.operand][1]))))
        return op(operand)

    def visit_BoolOp(self, node):
        assert len(node.values) == 2
        fake_node = ast.BinOp(node.values[0], node.op, node.values[1])
        r = self.visit_BinOp(fake_node)
        self.typedefs[node]=self.typedefs[fake_node]
        return r

    def visit_BinOp(self, node):
        left = self.visit(node.left)
        right= self.visit(node.right)
        op = operator_to_lambda[type(node.op)]
        self.add_typedef(node, "decltype({0})".format(op("std::declval<{0}>()".format(self.typedefs[node.left][1]) , "std::declval<{0}>()".format(self.typedefs[node.right][1]))))
        return op(left,right)

    def visit_comprehension(self, node):
        iter = self.visit(node.iter)
        if isinstance(node.target, ast.Name):
            self.add_typedef(node.target.id, "typename {0}::value_type".format(self.typedefs[node.iter][1]))
        else:
            raise PythranSyntaxError("Using something other than an identifier as list comprehension target", node)
        target = self.visit(node.target)
        ifs = [ self.visit(n) for n in node.ifs ]
        return ast.comprehension(target, iter, ifs )

    def visit_ListComp(self, node):

        list_comp_name = "list_comp{0}".format(len(self.structure_definitions))
        self.structure_definitions.append(EmptyStatement()) # *** ugly

        effective_arguments = [g.iter for g in [ self.visit(n) for n in node.generators ] ]
        formal_arguments = [ "argument{0}".format(n) for n in xrange(len(effective_arguments)) ]
        formal_types =  [ "argument_type{0}".format(n) for n in xrange(len(formal_arguments)) ]

        parameter_arguments = sorted( n for n in imported_ids(node, { k for k,v in self.typedefs.iteritems() if not v or not v[1]}) if n not in formal_arguments )
        parameter_types = [ "parameter_type{0}".format(n) for n in xrange(len(parameter_arguments)) ]

        cgv = CgenVisitor("<list_comp>", self)
        cgv.name = list_comp_name
        cgv.typedefs.update({ k:(k,v) for (k,v) in zip(formal_arguments + parameter_arguments, formal_types + parameter_types) })
        generators = [ cgv.visit(n) for n in node.generators ]

        elt = cgv.visit(node.elt)

        cgv.typedefs[CgenVisitor.return_type]= ("sequence<{0}>".format(cgv.typedefs[node.elt][1]),  CgenVisitor.return_type)

        convert = lambda text: int(text) if text.isdigit() else text 
        alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key[1]) ] 
        valid_typedefs = [ v for k,v in cgv.typedefs.iteritems() if v and v[1] and v[1].startswith("expression_type") ]
        valid_typedefs.append(cgv.typedefs[CgenVisitor.return_type])
        unique_typedefs = [ (k,v) for v,k in { v:k for (k,v) in valid_typedefs }.iteritems() ] # we want unique keys, not unique values ...
        typedefs= sorted( unique_typedefs, key=alphanum_key)

        struct = templatize(Struct("type", [Typedef(Value(n,t)) for n,t in typedefs] ), formal_types)

        fscope = "typename type{0}::".format(
                "<{0}>".format(", ".join(formal_types)) if formal_types else ""
                )

        def wrap_in_ifs(node, ifs):
            return reduce(lambda n,if_: If(if_,n,None), ifs, node)

        seq_name = "__s"
        holder = templatize(
                Struct(list_comp_name,
                    [ Statement( "{0} const & {1}".format(n, t) ) for n, t in zip(parameter_types, parameter_arguments) ] +
                    [ struct ] +
                    [ FunctionBody(
                        ConstructorDeclaration(
                            Value("", list_comp_name),
                            [Value("{0} const &".format(t), n)  for t,n in zip(parameter_types, parameter_arguments)],
                            ["{0}({0})".format(n) for n in parameter_arguments ]
                            ),
                        Block([])
                        ) ] +
                    [ FunctionBody(
                        templatize(
                            FunctionDeclaration(
                                Value(fscope+CgenVisitor.return_type, "operator()"),
                                [ Value("{0} const &".format(t), n)  for t,n in zip(formal_types, formal_arguments) ]
                                ),
                            formal_types),
                        Block([
                            Statement("{0} {1}".format(fscope+CgenVisitor.return_type, seq_name)),
                            reduce(lambda x,g:AutoFor(g.target, g.iter, wrap_in_ifs(x, g.ifs)), generators, Statement("{0}.push_back({1})".format(seq_name, elt))),
                            Statement("return {0}".format(seq_name))
                            ])
                        ) ]
                    ),
                parameter_types)
        self.structure_declarations.append(holder)

        fully_qualified_list_comp_name = "{0}{1}".format(list_comp_name,
                "<"+", ".join(self.typedefs[p][1] for p in parameter_arguments)+">" if parameter_arguments else "")
        self.add_typedef(node, "decltype(std::declval<{0}>()({1}))".format(
            fully_qualified_list_comp_name,
            ", ".join( "std::declval<{0}>()".format(self.typedefs[g.iter][1]) for g in node.generators)
            ))

        return "{0}({1})({2})".format(fully_qualified_list_comp_name, ", ".join(parameter_arguments), ", ".join(effective_arguments))





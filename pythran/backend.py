'''This module turns a pythran AST into C++ code
    *  cxx_backend generates a string holding the c++ code
'''
import ast
from cxxgen import *

from analysis import local_declarations, global_declarations, constant_value, yields

from tables import operator_to_lambda, modules, type_to_suffix
from typing import type_all
from syntax import PythranSyntaxError
import metadata

def templatize(node, types, default_types=None):
    if not default_types:
        default_types=[None]*len(types)
    return Template([ "typename " + t + ("= const {0}".format(d) if d else "") for t,d in zip(types, default_types) ], node ) if types else node

class CxxBackend(ast.NodeVisitor):

    generator_state_holder = "__generator_state" # used to recover previous generator state
    generator_state_value = "__generator_value" # used to recover previous generator state
    final_statement = "that_is_all_folks" # flags the last statement

    def __init__(self, name):
        modules['__user__']=dict()
        self.name=name
        self.types=None
        self.declarations=list()
        self.definitions=list()
        self.break_handler=list()

    # mod
    def visit_Module(self, node):
        # build all types
        self.global_declarations = global_declarations(node)
        self.local_functions=set()
        self.local_declarations=list()
        self.types=type_all(node)
        headers= [ Include(h) for h in [ "pythran/pythran.h" ] ]
        body = [ self.visit(n) for n in node.body if not isinstance(n, ast.Expr)] # remove top-level strings

        assert not self.local_declarations
        return headers +  [ Namespace("__{0}".format(self.name), body + self.declarations + self.definitions) ]

    # openmp processing
    def process_openmp_attachements(self, node):
        l = metadata.get(node, metadata.OpenMPDirective)
        return l


    # stmt
    def visit_FunctionDef(self, node):
        class CachedTypeVisitor:
            class CachedType:
                def __init__(self,s):self.s=s
                def generate(self,ctx): return self.s
            def __init__(self):
                self.cache=dict()
                self.mapping=dict()
            def __call__(self, node):
                if node not in self.mapping:
                    t=node.generate(self)
                    self.mapping[node]=len(self.mapping)
                    self.cache[node]=t
                return CachedTypeVisitor.CachedType("__type{0}".format(self.mapping[node]))
            def typedefs(self):
                l=sorted(self.mapping.items(),key=lambda x:x[1])
                L=list()
                for k,v in l:
                    #print "__type{0}".format(v), "->", k, ":", self.cache[k]
                    L.append( Typedef(Value(self.cache[k],"__type{0}".format(v))) )
                return L

        # prepare context and visit function body
        fargs = node.args.args

        local_functions={k for k in self.local_functions}

        formal_args = [ arg.id for arg in fargs ]
        formal_types= [ "argument_type"+str(i) for i in xrange(len(formal_args)) ]

        ldecls={ sym.id:sym for sym in local_declarations(node) }

        self.local_declarations.append(set(ldecls.iterkeys()))
        self.local_declarations[-1].update(formal_args)
        self.extra_declarations={}

        ldecls= set(ldecls.itervalues())

        self.yields = { k:(1+v,"yield_point{0}".format(1+v)) for (v,k) in enumerate(yields(node)) } # 0 is used as initial_state, thus the +1

        operator_body = [ self.visit(n) for n in node.body ] 
        default_arg_values = [None]*(len(node.args.args) - len(node.args.defaults)) + [ self.visit(n) for n in node.args.defaults ]
        default_arg_types  = [None]*(len(node.args.args) - len(node.args.defaults)) + [ self.types[n] for n in node.args.defaults ]

        self.local_declarations.pop()

        # add preprocessor line information
        #if hasattr(node,"lineno"):
        #    operator_body.insert(0,Line('#line {0} "{1}.py"'.format(node.lineno, self.name)))

        return_type = self.types[node][0]

        def make_function_declaration(rtype, name, ftypes, fargs, defaults):
            return FunctionDeclaration( Value(rtype, name), [ Value( t, "{0}{1}".format(a,"= {0}".format(d) if d else "") ) for t,a,d in zip(ftypes, fargs, defaults) ])

        if self.yields: # generator case
            # a generator has a call operator that returns the generator itself, that then behave like a regular iterator

            next_name = "__generator__"+node.name
            instanciated_next_name = "{0}{1}".format(next_name, "<{0}>".format(", ".join(formal_types)) if formal_types else "")

            operator_body.append(Statement("{0}: return return_type();".format(CxxBackend.final_statement )))

            next_declaration = [FunctionDeclaration( Value("return_type", "next"),
                [] ) , EmptyStatement()] #*** empty statement to force a comma ...
            next_constructors = [
                    FunctionBody(
                        FunctionDeclaration( Value("", next_name), []), Block([])
                        ),
                    FunctionBody(
                        make_function_declaration("",next_name, formal_types, formal_args, default_arg_values),
                        Line("{0} {{ }}".format( ": {0}".format(", ".join(["{0}({0})".format(fa) for fa in formal_args]+["{0}(0)".format(CxxBackend.generator_state_holder)]))))
                        )
                    ]
            next_iterator = [
                    FunctionBody(
                        FunctionDeclaration( Value("void", "operator++"), []), Block([Statement("next()")])),
                    FunctionBody(
                        FunctionDeclaration( Value("typename {0}::return_type".format(instanciated_next_name), "operator*"), []), Block([Statement("return {0}".format(CxxBackend.generator_state_value))])),
                    FunctionBody(
                        FunctionDeclaration( Value("pythonic::generator_iterator<{0}>".format(next_name), "begin"), []),
                        Block([Statement("next() ; return generator_iterator<{0}>(this)".format(next_name))])),
                    FunctionBody(
                        FunctionDeclaration( Value("pythonic::generator_iterator<{0}>".format(next_name), "end"), []),
                        Block([Statement("return generator_iterator<{0}>()".format(next_name))])),
                    FunctionBody(
                        FunctionDeclaration( Value("bool", "operator!="), [Value("{0} const &".format(next_name),"other")]), Block([Statement("return {0}!=other.{0}".format(CxxBackend.generator_state_holder))]))
                    ]
            next_signature = templatize(FunctionDeclaration(
                Value("typename {0}::return_type".format(instanciated_next_name), "{0}::next".format(instanciated_next_name)), [] ), formal_types)

            next_body = operator_body
            next_body.insert(0,Statement("switch({0}) {{ {1} }}".format( # the dispatch table at the entry point
                CxxBackend.generator_state_holder,
                " ".join("case {0}: goto {1};".format(num, where) for (num,where) in sorted(self.yields.itervalues(),key=lambda x:x[0])))))

            ctx=CachedTypeVisitor()
            next_members = [ Statement("{0} {1}".format(ft, fa)) for (ft,fa) in zip(formal_types, formal_args) ]\
                         + [ Statement("{0} {1}".format(self.types[k].generate(ctx), k.id)) for k in ldecls ]\
                         + [ Statement("{0} {1}".format(v,k)) for k,v in self.extra_declarations.iteritems() ]\
                         + [Statement("{0} {1}".format("long", CxxBackend.generator_state_holder))]\
                         + [Statement("typename {0}::return_type {1}".format(instanciated_next_name, CxxBackend.generator_state_value))]
            next_members = next_members

            extern_typedefs = [Typedef(Value(t.generate(ctx), t.name)) for t in self.types[node][1] if not t.isweak()]
            iterator_typedef= [Typedef(Value("pythonic::generator_iterator<{0}>".format("{0}<{1}>".format(next_name, ", ".join(str(t) for t in formal_types) ) if formal_types else next_name), "iterator")), Typedef(Value(return_type.generate(ctx), "value_type"))]
            return_typedef  = [Typedef(Value(return_type.generate(ctx), "return_type"))]
            extra_typedefs  =  ctx.typedefs() + extern_typedefs + iterator_typedef + return_typedef

            next_struct = templatize(Struct(next_name, extra_typedefs + next_members + next_constructors + next_iterator + next_declaration), formal_types)
            next_definition = FunctionBody(next_signature, Block( next_body ))

            operator_declaration = [templatize(make_function_declaration(instanciated_next_name, "operator()", formal_types, formal_args, default_arg_values) , formal_types, default_arg_types), EmptyStatement()] #*** empty statement to force a comma ...
            operator_signature = FunctionDeclaration(
                    Value(instanciated_next_name, "{0}::operator()".format(node.name)),
                    [ Value( t, a ) for t,a in zip(formal_types, formal_args ) ] )
            operator_definition = FunctionBody(
                    templatize(operator_signature, formal_types),
                    Block( [ Statement("return {0}({1})".format(instanciated_next_name, ", ".join(formal_args))) ])
                    )

            topstruct_type = templatize(Struct("type", extra_typedefs), formal_types)
            topstruct = Struct(node.name, [topstruct_type] + operator_declaration)

            self.declarations.append(next_struct)
            self.definitions.append(next_definition)


        else: # regular function case
            # a function has a call operator to be called, and a default constructor to create instances
            fscope = "type{0}::".format( "<{0}>".format(", ".join(formal_types)) if formal_types else ""  )
            ffscope = "{0}::{1}".format(node.name, fscope)

            operator_declaration = [templatize(
                make_function_declaration("typename "+fscope+"return_type", "operator()",
                    formal_types, formal_args, default_arg_values) , formal_types, default_arg_types), EmptyStatement()] #*** empty statement to force a comma ...
            operator_signature = FunctionDeclaration(
                    Value("typename {0}return_type".format(ffscope), "{0}::operator()".format(node.name)),
                    [ Value( t, a ) for t,a in zip(formal_types, formal_args ) ] )
            ctx=CachedTypeVisitor()
            operator_local_declarations = [ Statement("{0} {1}".format(self.types[k].generate(ctx), k.id)) for k in ldecls ]\
                    + [ Statement("{0} {1}".format(v,k)) for k,v in self.extra_declarations.iteritems() ]
            dependent_typedefs = ctx.typedefs()
            operator_definition = FunctionBody(
                    templatize(operator_signature, formal_types),
                    Block( dependent_typedefs + operator_local_declarations + operator_body )
                    )

            ctx=CachedTypeVisitor()
            extra_typedefs = [Typedef(Value(t.generate(ctx), t.name)) for t in self.types[node][1] if not t.isweak()]\
                           + [Typedef(Value(return_type.generate(ctx), "return_type"))]
            extra_typedefs = ctx.typedefs() + extra_typedefs
            return_declaration = [templatize(Struct("type",extra_typedefs), formal_types)]
            topstruct = Struct(node.name, return_declaration + operator_declaration)

        self.declarations.append(topstruct)
        self.definitions.append(operator_definition)

        self.local_functions=local_functions
        return EmptyStatement()

    def visit_Return(self, node):
        if self.yields: return Block([Statement("{0} = -1".format(CxxBackend.generator_state_holder)), Statement("goto "+CxxBackend.final_statement)])
        else: return ReturnStatement(self.visit(node.value))

    def visit_Delete(self, node):
        return EmptyStatement()

    def visit_Yield(self, node):
        num, label = self.yields[node]
        return "".join(n for n in Block([
            Statement("{0} = {1}".format(CxxBackend.generator_state_holder,num)),
            ReturnStatement("{0} = {1}".format(CxxBackend.generator_state_value,self.visit(node.value))),
            Statement("{0}:".format(label))
            ]).generate())

    def visit_Assign(self, node):
        if not all([isinstance(n, ast.Name) or isinstance(n, ast.Subscript) for n in node.targets]) :
            raise PythranSyntaxError("Assigning to something other than an identifier or a subscript", node)
        value = self.visit(node.value)
        targets=[self.visit(t) for t in node.targets]
        alltargets="= ".join(targets)
        return Statement("{0} = {1}".format(alltargets, value))

    def visit_AugAssign(self, node):
        value = self.visit(node.value)
        target=self.visit(node.target)
        return Statement(operator_to_lambda[type(node.op)](target, "="+value))

    def visit_Print(self, node):
        values = [ self.visit(n) for n in node.values]
        return Statement("print{0}({1})".format(
                "" if node.nl else "_nonl",
                ", ".join(values))
                )

    def visit_For(self, node):
        if not isinstance(node.target, ast.Name):
            raise PythranSyntaxError("Using something other than an identifier as loop target", node.target)
        directives = self.process_openmp_attachements(node)
        iter = self.visit(node.iter)
        target = self.visit(node.target)

        if node.orelse:
            break_handler="__no_breaking{0}".format(len(self.break_handler))
        else:
            break_handler=None
        self.break_handler.append(break_handler)

        local_iter= "__iter{0}".format(len(self.break_handler))
        local_target= "__target{0}".format(len(self.break_handler))

        local_iter_decl="decltype({0})".format(iter)
        local_target_decl="decltype({0}.begin())".format(iter)
        if self.yields:
            self.extra_declarations[local_iter]=local_iter_decl
            self.extra_declarations[local_target]=local_target_decl
            local_target_decl=""
            local_iter_decl=""

        body = [ self.visit(n) for n in node.body ]

        self.break_handler.pop()


        stmts=[
                Statement("{0} {1} = {2}".format(local_iter_decl, local_iter, iter)),
                For("{0} {1} = {2}.begin()".format(local_target_decl, local_target, local_iter),
                    "{0} < {1}.end()".format(local_target, local_iter),
                    "++{0}".format(local_target),
                    Block([Statement("{0} = *{1}".format(target, local_target))] + body ) )           
                ]

        for directive in reversed(directives):
            stmts.insert(1, Line("#pragma {0}".format(directive) ))

        for comp in metadata.get(node, metadata.Comprehension):# in that case when can proceed to a reserve
            stmts.insert(1, Statement("pythonic::reserve({0},{1})".format(comp.target, local_iter)))

        if break_handler:
            stmts.append(Block([ self.visit(n) for n in node.orelse ] + [ Statement("{0}:".format(break_handler))]))

        return Block(stmts)

    def visit_While(self, node):
        test = self.visit(node.test)
        self.break_handler.append(Block([self.visit(n) for n in node.orelse]) if node.orelse else None)
        body = [ self.visit(n) for n in node.body ]
        self.break_handler.pop()
        return While(test, Block(body))

    def visit_If(self, node):
        test = self.visit(node.test)
        body = [ self.visit(n) for n in node.body ]
        orelse = [ self.visit(n) for n in node.orelse ]
        return If(test, Block(body), Block(orelse) if orelse else None )

    def visit_Raise(self, node):
        type=self.visit(node.type)
        inst=self.visit(node.inst) if node.inst else None
        if inst: return Statement("throw {0}({1})".format(type, inst))
        else: return Statement("throw {0}".format(type))
            

    def visit_Assert(self, node):
        params = [ self.visit(node.msg) if node.msg else None, self.visit(node.test) ]
        return Statement("assert(({0}))".format(", ".join(p for p in params if p)))

    def visit_Import(self, node):
        return EmptyStatement() # everything is already #included

    def visit_ImportFrom(self, node):
        assert False, "this case should be filtered out by the expand_import pass"

    def visit_Expr(self, node):
        return Statement(self.visit(node.value))

    def visit_Pass(self, node):
        return EmptyStatement()

    def visit_Break(self, node):
        if self.break_handler[-1]:
            return Statement("goto {0}".format(self.break_handler[-1]))
        else:
             return Statement("break")

    def visit_Continue(self, node):
        return Statement("continue")


    # expr
    def visit_BoolOp(self, node):
        values = [ self.visit(value) for value in node.values ]
        return reduce(operator_to_lambda[type(node.op)], values)

    def visit_BinOp(self, node):
        left = self.visit(node.left)
        right= self.visit(node.right)
        return operator_to_lambda[type(node.op)](left,right)

    def visit_UnaryOp(self, node):
        operand = self.visit(node.operand)
        return operator_to_lambda[type(node.op)](operand)

    def visit_IfExp(self, node):
        test = self.visit(node.test)
        body = self.visit(node.body)
        orelse = self.visit(node.orelse)
        return "({0} ? {1} : {2})".format(test, body, orelse)

    def visit_List(self, node):
        if not node.elts: # empty list
            return "list()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            return "core::list< decltype({0})>({{ {1} }})".format(" + ".join(elts), ", ".join(elts))

    def visit_Set(self, node):
        if not node.elts: # empty set
            return "set()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            return "core::set< decltype({0})>({{ {1} }})".format(" + ".join(elts), ", ".join(elts))

    def visit_Dict(self, node):
        if not node.keys: # empty dict
            return "dict()"
        else:
            keys = [ self.visit(n) for n in node.keys ]
            values = [ self.visit(n) for n in node.values ]
            return "core::dict< decltype({0}),  decltype({1})>({{ {2} }})".format(" + ".join(keys), " + ".join(values),  ", ".join("{{ {0}, {1} }}".format(k,v) for k,v in zip(keys,values)))

    def visit_Tuple(self, node):
        if not node.elts: # empty tuple
            return "std::make_tuple()"
        else:
            elts = [ self.visit(n) for n in node.elts ]
            return "std::make_tuple({0})".format(", ".join(elts))

    def visit_Compare(self, node):
        left = self.visit(node.left)
        ops = [ operator_to_lambda[type(n)] for n in node.ops ]
        comparators = [ self.visit(n) for n in node.comparators ]
        all_compare = zip( ops, comparators )
        return " and ".join(op(left,r) for op,r in all_compare)

    def visit_Call(self, node):
        args = [ self.visit(n) for n in node.args ]
        func = self.visit(node.func)
        return "{0}({1})".format(func, ", ".join(args))

    def visit_Num(self, node):
        return str(node.n) + type_to_suffix.get(type(node.n),"")

    def visit_Str(self, node):
        return 'core::string("{0}")'.format(node.s.replace("\n",'\\n"\n"'))

    def visit_Attribute(self, node):
        value, attr = (node.value, node.attr)
        if isinstance(value, ast.Name) and value.id in modules and attr in modules[value.id]:
            if modules[value.id][attr]: return "{0}::{1}".format(value.id, attr)
            else: return "{0}::proxy::{1}()".format(value.id, attr)
        raise PythranSyntaxError("Attributes are only supported for namespaces", node)

    def visit_Subscript(self, node):
        value = self.visit(node.value)
        slice = self.visit(node.slice)
        try:
            v = constant_value(node.slice)
            if isinstance(v,int) or isinstance(v,long) or isinstance(v,bool):
                return "std::get<{0}>({1})".format(v, value)
            else:
                raise RuntimeError()
        except:
            if isinstance(node.slice, ast.Slice) and (
                    isinstance(node.ctx, ast.Store) or not metadata.get(node, metadata.NotTemporary)):
                return "{1}({0})".format(slice, value)
            else:
                return "{1}[{0}]".format(slice, value)

    def visit_Name(self, node):
        if node.id in self.local_declarations[-1]:
            return node.id
        elif node.id in modules["__builtins__"]:
            return "proxy::{0}()".format(node.id)
        elif node.id in self.global_declarations or node.id in self.local_functions:
            return "{0}()".format(node.id)
        else:
            return node.id


    # other

    def visit_Slice(self, node):
        lower = self.visit(node.lower) if node.lower else None
        upper = self.visit(node.upper) if node.upper else None
        step = self.visit(node.step) if node.step else None
        cv=None
        if not upper and not lower and step: # special case
            try: cv=constant_value(node.step)
            except: raise NotImplementedError("non constant step with undefined upper and lower bound in slice")
        if step:
            if not upper: upper = "std::numeric_limits<long>::max()"
        if upper:
            if not lower: lower = "0"
        if cv and cv <0: upper,lower=lower,upper

        return "core::slice({0})".format(", ".join( l for l in [ lower, upper, step ] if l ))

    def visit_Index(self, node):
        value = self.visit(node.value)
        return value

def cxx_backend(module_name,node):
    return CxxBackend(module_name).visit(node)

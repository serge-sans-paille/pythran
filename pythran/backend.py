'''
This module contains all pythran backends.
    * Cxx dumps the AST into C++ code
    * Python dumps the AST into Python code
'''

import ast
from cxxgen import *
from cxxtypes import *

from analysis import LocalDeclarations, GlobalDeclarations, Scope
from analysis import YieldPoints, BoundedExpressions, ArgumentEffects
from passmanager import Backend

from tables import operator_to_lambda, modules, type_to_suffix
from tables import pytype_to_ctype_table
from tables import pythran_ward
from typing import Types
from syntax import PythranSyntaxError

from openmp import OMPDirective

from math import isnan

import cStringIO
import unparse
import metadata


class Python(Backend):
    '''
    Produces a Python representation of the AST.

    >>> import ast, passmanager
    >>> node = ast.parse("print 'hello world'")
    >>> pm = passmanager.PassManager('test')
    >>> print pm.dump(Python, node)
    print 'hello world'
    '''

    def __init__(self):
        self.result = ''
        super(Python, self).__init__()

    def visit(self, node):
        output = cStringIO.StringIO()
        unparse.Unparser(node, output)
        self.result = output.getvalue()


def templatize(node, types, default_types=None):
    if not default_types:
        default_types = [None] * len(types)
    if types:
        return Template(
                ["typename {0} {1}".format(
                    t, "= {0}".format(d) if d else "")
                    for t, d in zip(types, default_types)],
                node)
    else:
        return node


def strip_exp(s):
    if s.startswith('(') and s.endswith(')'):
        return s[1:-1]
    else:
        return s


class Cxx(Backend):
    '''
    Produces a C++ representation of the AST.

    >>> import ast, passmanager
    >>> node = ast.parse("print 'hello world'")
    >>> pm = passmanager.PassManager('test')
    >>> r = pm.dump(Cxx, node)
    >>> print r
    #include <pythran/pythran.h>
    namespace __pythran_test
    {
      print(core::string("hello world"));
    }
    '''

    # recover previous generator state
    generator_state_holder = "__generator_state"
    generator_state_value = "__generator_value"
    # flags the last statement of a generator
    final_statement = "that_is_all_folks"

    def __init__(self):
        self.declarations = list()
        self.definitions = list()
        self.break_handlers = list()
        self.result = None
        super(Cxx, self).__init__(
                GlobalDeclarations, BoundedExpressions, Types, ArgumentEffects,
                Scope)

    # mod
    def visit_Module(self, node):
        # build all types
        header = Include("pythran/pythran.h")

        # remove top-level strings
        fbody = (n for n in node.body if not isinstance(n, ast.Expr))
        body = map(self.visit, fbody)

        nsbody = body + self.declarations + self.definitions
        ns = Namespace(pythran_ward + self.passmanager.module_name, nsbody)
        self.result = CompilationUnit([header, ns])

    # local declaration processing
    def process_locals(self, node, node_visited, *skipped):
        locals = self.scope[node].difference(skipped)
        if not locals or self.yields:
            return node_visited  # no processing

        locals_visited = []
        for varname in locals:
            vartype = self.local_types[varname]
            decl = Statement("{} {}".format(vartype, varname))
            locals_visited.append(decl)
        self.ldecls = [ld for ld in self.ldecls if ld.id not in locals]
        return Block(locals_visited + [node_visited])

    # openmp processing
    def process_omp_attachements(self, node, stmt, index=None):
        l = metadata.get(node, OMPDirective)
        if l:
            directives = list()
            for directive in reversed(l):
                # special hook for default for index scope
                if isinstance(node, ast.For):
                    target = node.target
                    hasfor = 'for' in directive.s
                    nodefault = 'default' not in directive.s
                    noindexref = all(x.id != target.id for x in directive.deps)
                    if hasfor and nodefault and noindexref:
                        directive.s += ' private({})'
                        directive.deps.append(ast.Name(target.id, ast.Param()))
                directives.append(directive)
            if index is None:
                stmt = AnnotatedStatement(stmt, directives)
            else:
                stmt[index] = AnnotatedStatement(stmt[index], directives)
        return stmt

    # stmt
    def visit_FunctionDef(self, node):
        class CachedTypeVisitor:
            class CachedType:
                def __init__(self, s):
                    self.s = s

                def generate(self, ctx):
                    return self.s

            def __init__(self, other=None):
                if other:
                    self.cache = other.cache.copy()
                    self.rcache = other.rcache.copy()
                    self.mapping = other.mapping.copy()
                else:
                    self.cache = dict()
                    self.rcache = dict()
                    self.mapping = dict()

            def __call__(self, node):
                if node not in self.mapping:
                    t = node.generate(self)
                    if t in self.rcache:
                        self.mapping[node] = self.mapping[self.rcache[t]]
                        self.cache[node] = self.cache[self.rcache[t]]
                    else:
                        self.rcache[t] = node
                        self.mapping[node] = len(self.mapping)
                        self.cache[node] = t
                return CachedTypeVisitor.CachedType(
                        "__type{0}".format(self.mapping[node]))

            def typedefs(self):
                l = sorted(self.mapping.items(), key=lambda x: x[1])
                L = list()
                visited = set()  # the same value must not be typedefed twice
                for k, v in l:
                    if v not in visited:
                        typename = "__type" + str(v)
                        L.append(Typedef(Value(self.cache[k], typename)))
                        visited.add(v)
                return L

        # prepare context and visit function body
        fargs = node.args.args

        formal_args = [arg.id for arg in fargs]
        formal_types = ["argument_type" + str(i) for i in xrange(len(fargs))]

        self.ldecls = self.passmanager.gather(LocalDeclarations, node)

        self.local_names = {sym.id for sym in self.ldecls}.union(formal_args)
        self.extra_declarations = []

        lctx = CachedTypeVisitor()
        self.local_types = {n: self.types[n].generate(lctx)
                            for n in self.ldecls}
        self.local_types.update((n.id, t) for n, t in self.local_types.items())

        # choose one node among all the ones with the same name for each name
        self.ldecls = {n for _, n in
                       {n.id: n for n in self.ldecls}.iteritems()}

        # 0 is used as initial_state, thus the +1
        self.yields = {k: (1 + v, "yield_point{0}".format(1 + v))
                for (v, k) in
                enumerate(self.passmanager.gather(YieldPoints, node))}

        # gather body dump
        operator_body = map(self.visit, node.body)

        # compute arg dump
        default_arg_values = (
                [None] * (len(node.args.args) - len(node.args.defaults))
                + [self.visit(n) for n in node.args.defaults])
        default_arg_types = (
                [None] * (len(node.args.args) - len(node.args.defaults))
                + [self.types[n] for n in node.args.defaults])

        # compute type dump
        result_type = self.types[node][0]

        callable_type = Typedef(Value("void", "callable"))

        def make_function_declaration(rtype, name, ftypes, fargs,
            defaults=None, attributes=[]):
            if defaults is None:
                defaults = [None] * len(ftypes)
            arguments = list()
            for i, (t, a, d) in enumerate(zip(ftypes, fargs, defaults)):
                if self.yields:
                    rvalue_ref = ""
                elif self.argument_effects[node][i]:
                    rvalue_ref = "&&"
                else:
                    rvalue_ref = " const &"
                argument = Value(t + rvalue_ref,
                    "{0}{1}".format(a, "= {0}".format(d) if d else ""))
                arguments.append(argument)
            return FunctionDeclaration(Value(rtype, name), arguments,
                *attributes)

        def make_const_function_declaration(rtype, name, ftypes, fargs,
            defaults=None):
            return make_function_declaration(rtype, name, ftypes, fargs,
                defaults, ["const"])

        if self.yields:  # generator case
            # a generator has a call operator that returns the iterator

            next_name = "__generator__{0}".format(node.name)
            instanciated_next_name = "{0}{1}".format(
                next_name,
                "<{0}>".format(
                    ", ".join(formal_types)) if formal_types else "")

            operator_body.append(
                Statement("{0}: return result_type();".format(
                    Cxx.final_statement)))

            next_declaration = [
                FunctionDeclaration(Value("result_type", "next"), []),
                EmptyStatement()]  # empty statement to force a comma ...

            # the constructors
            next_constructors = [
                    FunctionBody(
                        FunctionDeclaration(Value("", next_name), []),
                        Line(': {}(0) {{}}'.format(Cxx.generator_state_holder))
                        )]
            if formal_types:
                #if all parameters have a default value, we don't need default
                # constructor
                if default_arg_values and all(default_arg_values):
                    next_constructors = list()
                next_constructors.append(FunctionBody(
                    make_function_declaration("",
                        next_name, formal_types, formal_args,
                        default_arg_values),
                    Line("{0} {{ }}".format(
                        ": {0}".format(
                            ", ".join(
                                ["{0}({0})".format(fa) for fa in formal_args]
                                +
                                ["{0}(0)".format(
                                    Cxx.generator_state_holder)]))))
                    ))

            next_iterator = [
                    FunctionBody(
                        FunctionDeclaration(Value("void", "operator++"), []),
                        Block([Statement("next()")])),

                    FunctionBody(
                        FunctionDeclaration(
                            Value("typename {0}::result_type".format(
                                instanciated_next_name),
                                "operator*"),
                            [], "const"),
                        Block([
                            ReturnStatement(
                                Cxx.generator_state_value)])),
                    FunctionBody(
                        FunctionDeclaration(
                            Value("pythonic::generator_iterator<{0}>".format(
                                next_name),
                                "begin"),
                            []),
                        Block([Statement("next()"),
                            ReturnStatement(
                                "generator_iterator<{0}>(*this)".format(
                                    next_name))])),
                    FunctionBody(
                        FunctionDeclaration(
                            Value("pythonic::generator_iterator<{0}>".format(
                                next_name),
                                "end"),
                            []),
                        Block([ReturnStatement(
                            "generator_iterator<{0}>()".format(next_name))])),
                    FunctionBody(
                        FunctionDeclaration(
                            Value("bool", "operator!="),
                            [Value("{0} const &".format(next_name), "other")],
                            "const"),
                        Block([ReturnStatement(
                            "{0}!=other.{0}".format(
                                Cxx.generator_state_holder))])),
                    FunctionBody(
                        FunctionDeclaration(
                            Value("bool", "operator=="),
                            [Value("{0} const &".format(next_name), "other")],
                            "const"),
                        Block([ReturnStatement(
                            "{0}==other.{0}".format(
                                Cxx.generator_state_holder))])),
                    ]
            next_signature = templatize(
                    FunctionDeclaration(
                        Value(
                            "typename {0}::result_type".format(
                                instanciated_next_name),
                            "{0}::next".format(instanciated_next_name)),
                        []),
                    formal_types)

            next_body = operator_body
            # the dispatch table at the entry point
            next_body.insert(0,
                    Statement("switch({0}) {{ {1} }}".format(
                        Cxx.generator_state_holder,
                        " ".join("case {0}: goto {1};".format(num, where)
                            for (num, where) in sorted(
                                self.yields.itervalues(),
                                key=lambda x: x[0])))))

            ctx = CachedTypeVisitor(lctx)
            next_members = (
                    [Statement("{0} {1}".format(ft, fa))
                        for (ft, fa) in zip(formal_types, formal_args)]
                    + [Statement("{0} {1}".format(
                        self.types[k].generate(ctx),
                        k.id))
                        for k in self.ldecls]
                    + [Statement("{0} {1}".format(v, k))
                        for k, v in self.extra_declarations]
                    + [Statement("{0} {1}".format("long",
                        Cxx.generator_state_holder))]
                    + [Statement("typename {0}::result_type {1}".format(
                        instanciated_next_name,
                        Cxx.generator_state_value))]
                    )

            extern_typedefs = [Typedef(Value(t.generate(ctx), t.name))
                    for t in self.types[node][1] if not t.isweak()]
            iterator_typedef = [
                    Typedef(Value(
                        "pythonic::generator_iterator<{0}>".format(
                            "{0}<{1}>".format(
                                next_name,
                                ", ".join(t for t in formal_types))
                            if formal_types
                            else next_name),
                        "iterator")),
                    Typedef(Value(
                        result_type.generate(ctx),
                        "value_type"))]
            result_typedef = [
                    Typedef(Value(result_type.generate(ctx), "result_type"))]
            extra_typedefs = (ctx.typedefs()
                    + extern_typedefs
                    + iterator_typedef
                    + result_typedef)

            next_struct = templatize(
                    Struct(
                        next_name,
                        extra_typedefs
                        + next_members
                        + next_constructors
                        + next_iterator
                        + next_declaration),
                    formal_types)
            next_definition = FunctionBody(next_signature, Block(next_body))

            operator_declaration = [
                    templatize(
                        make_const_function_declaration(
                            instanciated_next_name,
                            "operator()",
                            formal_types,
                            formal_args,
                            default_arg_values),
                        formal_types,
                        default_arg_types),
                    EmptyStatement()]
            operator_signature = make_const_function_declaration(
                    instanciated_next_name,
                    "{0}::operator()".format(node.name),
                    formal_types,
                    formal_args)
            operator_definition = FunctionBody(
                    templatize(operator_signature, formal_types),
                    Block([ReturnStatement("{0}({1})".format(
                        instanciated_next_name,
                        ", ".join(formal_args)))])
                    )

            topstruct_type = templatize(
                    Struct("type", extra_typedefs),
                    formal_types)
            topstruct = Struct(
                    node.name,
                    [topstruct_type, callable_type]
                    + operator_declaration)

            self.declarations.append(next_struct)
            self.definitions.append(next_definition)

        else:  # regular function case
            # a function has a call operator to be called
            # and a default constructor to create instances
            fscope = "type{0}::".format(
                    "<{0}>".format(
                        ", ".join(formal_types))
                    if formal_types
                    else "")
            ffscope = "{0}::{1}".format(node.name, fscope)

            operator_declaration = [
                    templatize(
                        make_const_function_declaration(
                            "typename {0}result_type".format(fscope),
                            "operator()",
                            formal_types,
                            formal_args,
                            default_arg_values),
                        formal_types,
                        default_arg_types),
                    EmptyStatement()
                    ]
            operator_signature = make_const_function_declaration(
                    "typename {0}result_type".format(ffscope),
                    "{0}::operator()".format(node.name),
                    formal_types,
                    formal_args)
            ctx = CachedTypeVisitor(lctx)
            operator_local_declarations = (
                    [Statement("{0} {1}".format(
                     self.types[k].generate(ctx), k.id)) for k in self.ldecls]
                    + [Statement("{0} {1}".format(v, k))
                       for k, v in self.extra_declarations]
                    )
            dependent_typedefs = ctx.typedefs()
            operator_definition = FunctionBody(
                    templatize(operator_signature, formal_types),
                    Block(dependent_typedefs
                        + operator_local_declarations
                        + operator_body)
                    )

            ctx = CachedTypeVisitor()
            extra_typedefs = (
                    [Typedef(Value(t.generate(ctx), t.name))
                        for t in self.types[node][1] if not t.isweak()]
                    + [Typedef(Value(
                        result_type.generate(ctx),
                        "result_type"))]
                    )
            extra_typedefs = ctx.typedefs() + extra_typedefs
            return_declaration = [
                    templatize(
                        Struct("type", extra_typedefs),
                        formal_types,
                        default_arg_types
                        )
                    ]
            topstruct = Struct(
                    node.name,
                    [callable_type]
                    + return_declaration
                    + operator_declaration)

        self.declarations.append(topstruct)
        self.definitions.append(operator_definition)

        return EmptyStatement()

    def visit_Return(self, node):
        if self.yields:
            return Block([
                Statement("{0} = -1".format(
                    Cxx.generator_state_holder)),
                Statement("goto {0}".format(
                    Cxx.final_statement))
                ])
        else:
            stmt = ReturnStatement(self.visit(node.value))
            return self.process_omp_attachements(node, stmt)

    def visit_Delete(self, node):
        return EmptyStatement()

    def visit_Yield(self, node):
        num, label = self.yields[node]
        return "".join(n for n in Block([
            Assign(Cxx.generator_state_holder, num),
            ReturnStatement("{0} = {1}".format(
                Cxx.generator_state_value,
                self.visit(node.value))),
            Statement("{0}:".format(label))
            ]).generate())

    def visit_Assign(self, node):
        if not all(isinstance(n, ast.Name) or isinstance(n, ast.Subscript)
                for n in node.targets):
            raise PythranSyntaxError(
                    "Must assign to an identifier or a subscript",
                    node)
        value = self.visit(node.value)
        targets = [self.visit(t) for t in node.targets]
        alltargets = "= ".join(targets)
        islocal = any(metadata.get(t, metadata.LocalVariable)
                      for t in node.targets)
        if len(targets) == 1 and isinstance(node.targets[0], ast.Name):
            islocal |= node.targets[0].id in self.scope[node]
        if islocal and not self.yields:
            # remove this decl from local decls
            tdecls = {t.id for t in node.targets}
            self.ldecls = {d for d in self.ldecls if d.id not in tdecls}
            # add a local declaration
            alltargets = '{} {}'.format(self.local_types[node.targets[0]],
                                        alltargets)
        stmt = Assign(alltargets, value)
        return self.process_omp_attachements(node, stmt)

    def visit_AugAssign(self, node):
        value = self.visit(node.value)
        target = self.visit(node.target)
        l = operator_to_lambda[type(node.op)]
        if type(node.op) in (ast.FloorDiv,):
            stmt = Assign(target, l(target, value))
        else:
            stmt = Statement(l(target, '')[1:-2] + '= {0}'.format(value))
        return self.process_omp_attachements(node, stmt)

    def visit_Print(self, node):
        values = [self.visit(n) for n in node.values]
        stmt = Statement("print{0}({1})".format(
                "" if node.nl else "_nonl",
                ", ".join(values))
                )
        return self.process_omp_attachements(node, stmt)

    def visit_For(self, node):
        if not isinstance(node.target, ast.Name):
            raise PythranSyntaxError(
                    "Using something other than an identifier as loop target",
                    node.target)
        iter = self.visit(node.iter)
        target = self.visit(node.target)

        if node.orelse:
            break_handler = "__no_breaking{0}".format(len(self.break_handlers))
        else:
            break_handler = None
        self.break_handlers.append(break_handler)

        local_iter = "__iter{0}".format(len(self.break_handlers))
        local_target = "__target{0}".format(len(self.break_handlers))

        local_iter_decl = Assignable(DeclType(iter))
        local_target_decl = NamedType("{0}::iterator".format(local_iter_decl))
        if self.yields:
            self.extra_declarations.append((local_iter, local_iter_decl,))
            self.extra_declarations.append((local_target, local_target_decl,))
            local_target_decl = ""
            local_iter_decl = ""

        loop_body = Block(map(self.visit, node.body))

        self.break_handlers.pop()

        # eventually add local_iter in a shared clause
        omp = metadata.get(node, OMPDirective)
        if omp:
            for directive in omp:
                if 'parallel' in directive.s:
                    directive.s += ' shared({})'
                    directive.deps.append(ast.Name(local_iter, ast.Param()))

        prelude = Statement("{0} {1} = {2}".format(
            local_iter_decl, local_iter, iter)
            )

        auto_for = bool(metadata.get(node.target, metadata.LocalVariable))
        auto_for |= (type(node.target) is ast.Name
                      and node.target.id in self.scope[node])
        auto_for &= not self.yields and not omp

        loop_body = self.process_locals(node, loop_body, node.target.id)

        if auto_for:
            self.ldecls = {d for d in self.ldecls if d.id != node.target.id}
            loop = AutoFor(
                    target,
                    local_iter,
                    loop_body
                    )
        else:
            if (metadata.get(node.target, metadata.LocalVariable) and
                    not self.yields):
                local_type = "typename decltype({})::reference ".format(
                                local_target)
            else:
                local_type = ""
            loop_body_prelude = Statement(
                    "{} {}= *{}".format(
                        local_type,
                        target,
                        local_target)
                    )
            loop = For(
                    "{0} {1} = {2}.begin()".format(
                        local_target_decl,
                        local_target,
                        local_iter),
                    "{0} < {1}.end()".format(
                        local_target,
                        local_iter),
                    "++{0}".format(local_target),
                    Block([loop_body_prelude, loop_body])
                    )
        stmts = [prelude, loop]

        # in that case when can proceed to a reserve
        for comp in metadata.get(node, metadata.Comprehension):
            stmts.insert(1,
                    Statement("pythonic::reserve({0},{1})".format(
                        comp.target,
                        local_iter)))

        if break_handler:
            orelse = map(self.visit, node.orelse)
            orelse_label = Statement("{0}:".format(break_handler))
            stmts.append(Block(orelse + [orelse_label]))

        return Block(self.process_omp_attachements(node, stmts, 1))

    def visit_While(self, node):
        test = self.visit(node.test)

        if node.orelse:
            break_handler = "__no_breaking{0}".format(len(self.break_handlers))
        else:
            break_handler = None
        self.break_handlers.append(break_handler)

        body = [self.visit(n) for n in node.body]

        self.break_handlers.pop()

        while_ = While(test, Block(body))

        if break_handler:
            orelse = map(self.visit, node.orelse)
            orelse_label = Statement("{0}:".format(break_handler))
            return Block([while_] + orelse + [orelse_label])
        else:
            return while_

    def visit_TryExcept(self, node):
        body = [self.visit(n) for n in node.body]
        except_ = list()
        [except_.extend(self.visit(n)) for n in node.handlers]
        return TryExcept(Block(body), except_, None)

    def visit_ExceptHandler(self, node):
        name = self.visit(node.name) if node.name else None
        body = [self.visit(m) for m in node.body]
        if not isinstance(node.type, ast.Tuple):
            return [ExceptHandler(
                node.type and node.type.attr,
                Block(body),
                name)]
        else:
            elts = [p.attr for p in node.type.elts]
            return [ExceptHandler(o, Block(body), name) for o in elts]

    def visit_If(self, node):
        test = self.visit(node.test)
        body = [self.visit(n) for n in node.body]
        orelse = [self.visit(n) for n in node.orelse]
        if isinstance(node.test, ast.Num) and node.test.n == 1:
            stmt = Block(body)
        else:
            stmt = If(test, Block(body), Block(orelse) if orelse else None)
        return self.process_locals(node,
                                   self.process_omp_attachements(node, stmt))

    def visit_Raise(self, node):
        type = node.type and self.visit(node.type)
        if node.inst:
            if isinstance(node.inst, ast.Tuple):
                inst = ['"{0}"'.format(e.s) for e in node.inst.elts]
            else:
                inst = [node.inst.s]
        else:
            inst = None
        if inst:
            return Statement("throw {0}({1})".format(type, ", ".join(inst)))
        else:
            return Statement("throw {0}".format(type or ""))

    def visit_Assert(self, node):
        params = [self.visit(node.test), node.msg and self.visit(node.msg)]
        sparams = ", ".join(map(strip_exp, filter(None, params)))
        return Statement("pythran_assert({0})".format(sparams))

    def visit_Import(self, node):
        return EmptyStatement()  # everything is already #included

    def visit_ImportFrom(self, node):
        assert False, "should be filtered out by the expand_import pass"

    def visit_Expr(self, node):
        # turn docstring into comments
        if type(node.value) is ast.Str:
            stmt = Line("//" + node.value.s.replace('\n', '\n//'))
        # other expressions are processed normally
        else:
            stmt = Statement(self.visit(node.value))
        return self.process_locals(node,
                                   self.process_omp_attachements(node, stmt))

    def visit_Pass(self, node):
        stmt = EmptyStatement()
        return self.process_omp_attachements(node, stmt)

    def visit_Break(self, node):
        if self.break_handlers[-1]:
            return Statement("goto {0}".format(self.break_handlers[-1]))
        else:
            return Statement("break")

    def visit_Continue(self, node):
        return Statement("continue")

    # expr
    def visit_BoolOp(self, node):
        values = [self.visit(value) for value in node.values]
        if node in self.bounded_expressions:
            op = operator_to_lambda[type(node.op)]
        elif isinstance(node.op, ast.And):
            op = lambda l, r: '({0} and {1})'.format(l, r)
        elif isinstance(node.op, ast.Or):
            op = lambda l, r: '({0} or {1})'.format(l, r)
        return reduce(op, values)

    def visit_BinOp(self, node):
        left = self.visit(node.left)
        right = self.visit(node.right)
        return operator_to_lambda[type(node.op)](left, right)

    def visit_UnaryOp(self, node):
        operand = self.visit(node.operand)
        return operator_to_lambda[type(node.op)](operand)

    def visit_IfExp(self, node):
        test = self.visit(node.test)
        body = self.visit(node.body)
        orelse = self.visit(node.orelse)
        return "({0} ? {1} : {2})".format(test, body, orelse)

    def visit_List(self, node):
        if not node.elts:  # empty list
            return "__builtin__::list()"
        else:
            elts = [self.visit(n) for n in node.elts]
            # constructor disambiguation, clang++ workaround
            if len(elts) == 1:
                elts.append('core::single_value()')
                return "{0}({{ {1} }})".format(
                        Assignable(self.types[node]),
                        ", ".join(elts))
            else:
                return "{0}({{ {1} }})".format(
                        Assignable(self.types[node]),
                        ", ".join(elts))

    def visit_Set(self, node):
        if not node.elts:  # empty set
            return "__builtin__::set()"
        else:
            elts = [self.visit(n) for n in node.elts]
            return "{0}({{ {1} }})".format(
                    Assignable(self.types[node]),
                    ", ".join(elts))

    def visit_Dict(self, node):
        if not node.keys:  # empty dict
            return "__builtin__::dict()"
        else:
            keys = [self.visit(n) for n in node.keys]
            values = [self.visit(n) for n in node.values]
            return "{0}({{ {1} }})".format(
                    Assignable(self.types[node]),
                    ", ".join("{{ {0}, {1} }}".format(k, v)
                        for k, v in zip(keys, values)))

    def visit_Tuple(self, node):
        elts = map(self.visit, node.elts or ())
        return "core::make_tuple({0})".format(", ".join(elts))

    def visit_Compare(self, node):
        left = self.visit(node.left)
        ops = [operator_to_lambda[type(n)] for n in node.ops]
        comparators = [self.visit(n) for n in node.comparators]
        all_compare = zip(ops, comparators)
        op, right = all_compare[0]
        output = [op(left, right)]
        left = right
        for op, right in all_compare[1:]:
            output.append(op(left, right))
            left = right
        return " and ".join(output)

    def visit_Call(self, node):
        args = [self.visit(n) for n in node.args]
        func = self.visit(node.func)
        return "{0}({1})".format(func, ", ".join(args))

    def visit_Num(self, node):
        if type(node.n) == complex:
            return "{0}({1}, {2})".format(
                    pytype_to_ctype_table[complex],
                    repr(node.n.real),
                    repr(node.n.imag))
        elif type(node.n) == long:
            return 'pythran_long({0})'.format(node.n)
        elif isnan(node.n):
            return 'pythonic::nan'
        else:
            return repr(node.n) + type_to_suffix.get(type(node.n), "")

    def visit_Str(self, node):
        quoted = node.s.replace('"', '\\"').replace('\n', '\\n"\n"')
        return 'core::string("{0}")'.format(quoted)

    def visit_Attribute(self, node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return w[n.id], (n.id,)
            elif isinstance(n, ast.Attribute):
                r = rec(w, n.value)
                return r[0][n.attr], r[1] + (n.attr,)
        obj, path = rec(modules, node)
        return ('::'.join(path) if obj.isliteral()
                else ('::'.join(path[:-1]) + '::proxy::' + path[-1] + '{}'))

    def visit_Subscript(self, node):
        value = self.visit(node.value)
        # attribute case
        if metadata.get(node, metadata.Attribute):
            return "getattr<{0}>({1})".format(node.slice.value.n, value)
        # positive static index case
        elif (isinstance(node.slice, ast.Index)
                and isinstance(node.slice.value, ast.Num)
                and (node.slice.value.n >= 0)
                and any(isinstance(node.slice.value.n, t)
                    for t in (int, long))):
            return "std::get<{0}>({1})".format(node.slice.value.n, value)
        # slice optimization case
        elif (isinstance(node.slice, ast.Slice)
                and (isinstance(node.ctx, ast.Store)
                    or node not in self.bounded_expressions)):
            slice = self.visit(node.slice)
            return "{1}({0})".format(slice, value)
        # extended slice case
        elif isinstance(node.slice, ast.ExtSlice):
            slice = self.visit(node.slice)
            return "{1}({0})".format(','.join(slice), value)
        # standard case
        else:
            slice = self.visit(node.slice)
            return "{1}[{0}]".format(slice, value)

    def visit_Name(self, node):
        if node.id in self.local_names:
            return node.id
        elif node.id in self.global_declarations:
            return "{0}()".format(node.id)
        else:
            return node.id

    # other
    def visit_ExtSlice(self, node):
        return map(self.visit, node.dims)

    def visit_Slice(self, node):
        args = []
        for field in ('lower', 'upper', 'step'):
            nfield = getattr(node, field)
            arg = self.visit(nfield) if nfield else '__builtin__::None'
            args.append(arg)
        return "core::slice({},{},{})".format(*args)

    def visit_Index(self, node):
        return self.visit(node.value)

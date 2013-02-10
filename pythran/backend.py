'''
This module contains all pythran backends.
    * Cxx dumps the AST into C++ code
    * Python dumps the AST into Python code
'''

import ast
from cxxgen import *
from cxxtypes import *

from analysis import LocalDeclarations, GlobalDeclarations
from analysis import YieldPoints, BoundedExpressions, ArgumentEffects
from passmanager import Backend

from tables import operator_to_lambda, modules, type_to_suffix
from tables import builtin_constructors, pytype_to_ctype_table
from typing import Types
from syntax import PythranSyntaxError

from openmp import OMPDirective

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
    <BLANKLINE>
    print 'hello world'
    '''

    def __init__(self):
        self.result = ''
        Backend.__init__(self)

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
                    t, "= const {0}".format(d) if d else "")
                    for t, d in zip(types, default_types)],
                node)
    else:
        return node


class Cxx(Backend):
    '''
    Produces a C++ representation of the AST.

    >>> import ast, passmanager
    >>> node = ast.parse("print 'hello world'")
    >>> pm = passmanager.PassManager('test')
    >>> r = pm.dump(Cxx, node)
    >>> for l in r: print l
    #include <pythran/pythran.h>
    #include <pythran/pythran_gmp.h>
    namespace __test
    {
      print(core::string("hello world"));
    }
    <BLANKLINE>
    '''

    # recover previous generator state
    generator_state_holder = "__generator_state"
    generator_state_value = "__generator_value"
    # flags the last statement of a generator
    final_statement = "that_is_all_folks"

    def __init__(self):
        self.declarations = list()
        self.definitions = list()
        self.break_handler = list()
        self.result = list()
        Backend.__init__(self,
                GlobalDeclarations, BoundedExpressions, Types, ArgumentEffects)

    # mod
    def visit_Module(self, node):
        # build all types
        self.local_functions = set()
        self.local_declarations = list()
        headers = [Include(h)
                for h in ("pythran/pythran.h", "pythran/pythran_gmp.h")]
        # remove top-level strings
        body = [self.visit(n)
                for n in node.body if not isinstance(n, ast.Expr)]

        assert not self.local_declarations
        self.result = headers + [
                Namespace("__{0}".format(self.passmanager.module_name),
                    body
                    + self.declarations
                    + self.definitions)]

    # openmp processing
    def process_omp_attachements(self, node, stmt, index=None):
        l = metadata.get(node, OMPDirective)
        if l:
            directives = list()
            for directive in reversed(l):
                # special hook for default for index scope
                if isinstance(node, ast.For):
                    target = node.target
                    if ('for' in directive.s
                            and 'default' not in directive.s
                            and all(x.id != target.id for x in directive.deps)
                            ):
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

            def __init__(self):
                self.cache = dict()
                self.mapping = dict()

            def __call__(self, node):
                if node not in self.mapping:
                    t = node.generate(self)
                    self.mapping[node] = len(self.mapping)
                    self.cache[node] = t
                return CachedTypeVisitor.CachedType(
                        "__type{0}".format(self.mapping[node]))

            def typedefs(self):
                l = sorted(self.mapping.items(),
                        key=lambda x: x[1])
                L = list()
                for k, v in l:
                    L.append(Typedef(
                        Value(self.cache[k], "__type{0}".format(v))))
                return L

        # prepare context and visit function body
        fargs = node.args.args

        local_functions = {k for k in self.local_functions}

        formal_args = [arg.id for arg in fargs]
        formal_types = ["argument_type{0}".format(i)
                for i in xrange(len(formal_args))]

        ldecls = {sym.id: sym
                for sym in self.passmanager.gather(LocalDeclarations, node)}

        self.local_declarations.append(set(ldecls.iterkeys()))
        self.local_declarations[-1].update(formal_args)
        self.extra_declarations = []

        ldecls = set(ldecls.itervalues())

        # 0 is used as initial_state, thus the +1
        self.yields = {k: (1 + v, "yield_point{0}".format(1 + v))
                for (v, k) in
                enumerate(self.passmanager.gather(YieldPoints, node))}

        operator_body = [self.visit(n) for n in node.body]
        default_arg_values = (
                [None] * (len(node.args.args) - len(node.args.defaults))
                + [self.visit(n) for n in node.args.defaults])
        default_arg_types = (
                [None] * (len(node.args.args) - len(node.args.defaults))
                + [self.types[n] for n in node.args.defaults])

        self.local_declarations.pop()

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
                        Block([]))]
            if formal_types:
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
                            []),
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
                                "generator_iterator<{0}>(this)".format(
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

            ctx = CachedTypeVisitor()
            next_members = (
                    [Statement("{0} {1}".format(ft, fa))
                        for (ft, fa) in zip(formal_types, formal_args)]
                    + [Statement("{0} {1}".format(
                        self.types[k].generate(ctx),
                        k.id))
                        for k in ldecls]
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
                        make_function_declaration(
                            instanciated_next_name,
                            "operator()",
                            formal_types,
                            formal_args,
                            default_arg_values),
                        formal_types,
                        default_arg_types),
                    EmptyStatement()]
            operator_signature = make_function_declaration(
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
            ctx = CachedTypeVisitor()
            operator_local_declarations = (
                    [Statement("{0} {1}".format(
                        self.types[k].generate(ctx), k.id)) for k in ldecls]
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
            return_declaration = [templatize(
                Struct("type", extra_typedefs),
                formal_types)]
            topstruct = Struct(
                    node.name,
                    [callable_type]
                    + return_declaration
                    + operator_declaration)

        self.declarations.append(topstruct)
        self.definitions.append(operator_definition)

        self.local_functions = local_functions
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
        if any(metadata.get(t, metadata.LocalVariable) for t in node.targets):
            alltargets = "auto {0}".format(alltargets)
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
        return Statement("print{0}({1})".format(
                "" if node.nl else "_nonl",
                ", ".join(values))
                )

    def visit_For(self, node):
        if not isinstance(node.target, ast.Name):
            raise PythranSyntaxError(
                    "Using something other than an identifier as loop target",
                    node.target)
        iter = self.visit(node.iter)
        target = self.visit(node.target)

        if node.orelse:
            break_handler = "__no_breaking{0}".format(len(self.break_handler))
        else:
            break_handler = None
        self.break_handler.append(break_handler)

        local_iter = "__iter{0}".format(len(self.break_handler))
        local_target = "__target{0}".format(len(self.break_handler))

        local_iter_decl = Assignable(DeclType(Val(iter)))
        local_target_decl = NamedType("{0}::iterator".format(local_iter_decl))
        if self.yields:
            self.extra_declarations.append((local_iter, local_iter_decl,))
            self.extra_declarations.append((local_target, local_target_decl,))
            local_target_decl = ""
            local_iter_decl = ""
        target_decl = ("auto"
                if metadata.get(node.target, metadata.LocalVariable)
                else "")

        body = [self.visit(n) for n in node.body]

        self.break_handler.pop()

        # eventually add local_iter in a shared clause
        omp = metadata.get(node, OMPDirective)
        if omp:
            for directive in omp:
                if 'parallel' in directive.s:
                    directive.s += ' shared({})'
                    directive.deps.append(ast.Name(local_iter, ast.Param()))

        stmts = [
                Statement("{0} {1} = {2}".format(
                    local_iter_decl,
                    local_iter, iter)
                    ),
                For("{0} {1} = {2}.begin()".format(
                    local_target_decl,
                    local_target,
                    local_iter),
                    "{0} < {1}.end()".format(
                        local_target,
                        local_iter),
                    "++{0}".format(local_target),
                    Block(
                        [Statement("{0} {1}= *{2}".format(
                            target_decl,
                            target,
                            local_target))]
                        + body))
                ]

        # in that case when can proceed to a reserve
        for comp in metadata.get(node, metadata.Comprehension):
            stmts.insert(1,
                    Statement("pythonic::reserve({0},{1})".format(
                        comp.target,
                        local_iter)))

        if break_handler:
            stmts.append(Block(
                [self.visit(n) for n in node.orelse]
                + [Statement("{0}:".format(break_handler))]))

        return Block(self.process_omp_attachements(node, stmts, 1))

    def visit_While(self, node):
        test = self.visit(node.test)
        self.break_handler.append(
                Block([self.visit(n) for n in node.orelse])
                if node.orelse
                else None)
        body = [self.visit(n) for n in node.body]
        self.break_handler.pop()
        return While(test, Block(body))

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
                node.type.id if node.type else None,
                Block(body),
                name)]
        else:
            elts = [p.id for p in node.type.elts]
            return [ExceptHandler(o, Block(body), name) for o in elts]

    def visit_If(self, node):
        test = self.visit(node.test)
        body = [self.visit(n) for n in node.body]
        orelse = [self.visit(n) for n in node.orelse]
        if isinstance(node.test, ast.Num) and node.test.n == 1:
            stmt = Block(body)
        else:
            stmt = If(test, Block(body), Block(orelse) if orelse else None)
        return self.process_omp_attachements(node, stmt)

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
        params = [node.msg and self.visit(node.msg), self.visit(node.test)]
        return Statement("assert(({0}))".format(
            ", ".join(p for p in params if p)))

    def visit_Import(self, node):
        return EmptyStatement()  # everything is already #included

    def visit_ImportFrom(self, node):
        assert False, "should be filtered out by the expand_import pass"

    def visit_Expr(self, node):
        stmt = Statement(self.visit(node.value))
        return self.process_omp_attachements(node, stmt)

    def visit_Pass(self, node):
        stmt = EmptyStatement()
        return self.process_omp_attachements(node, stmt)

    def visit_Break(self, node):
        if self.break_handler[-1]:
            return Statement("goto {0}".format(self.break_handler[-1]))
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
            return "list()"
        else:
            elts = [self.visit(n) for n in node.elts]
            return "{0}({{ {1} }})".format(
                    Assignable(self.types[node]),
                    ", ".join(elts))

    def visit_Set(self, node):
        if not node.elts:  # empty set
            return "set()"
        else:
            elts = [self.visit(n) for n in node.elts]
            return "{0}({{ {1} }})".format(
                    Assignable(self.types[node]),
                    ", ".join(elts))

    def visit_Dict(self, node):
        if not node.keys:  # empty dict
            return "dict()"
        else:
            keys = [self.visit(n) for n in node.keys]
            values = [self.visit(n) for n in node.values]
            return "{0}({{ {1} }})".format(
                    Assignable(self.types[node]),
                    ", ".join("{{ {0}, {1} }}".format(k, v)
                        for k, v in zip(keys, values)))

    def visit_Tuple(self, node):
        if not node.elts:  # empty tuple
            return "std::tuple<>()"
        else:
            elts = [self.visit(n) for n in node.elts]
            return "std::make_tuple({0})".format(", ".join(elts))

    def visit_Compare(self, node):
        left = self.visit(node.left)
        ops = [operator_to_lambda[type(n)] for n in node.ops]
        comparators = [self.visit(n) for n in node.comparators]
        all_compare = zip(ops, comparators)
        return " and ".join(op(left, r) for op, r in all_compare)

    def visit_Call(self, node):
        args = [self.visit(n) for n in node.args]
        func = self.visit(node.func)
        return "{0}({1})".format(func, ", ".join(args))

    def visit_Num(self, node):
        if type(node.n) == complex:
            return "{0}({1}, {2})".format(
                    pytype_to_ctype_table[type(node.n)],
                    repr(node.n.real),
                    repr(node.n.imag))
        elif type(node.n) == long:
            return 'pythran_long({0})'.format(node.n)
        else:
            return repr(node.n) + type_to_suffix.get(type(node.n), "")

    def visit_Str(self, node):
        return 'core::string("{0}")'.format(node.s.replace('\n', '\\n"\n"'))

    def visit_Attribute(self, node):
        value, attr = (node.value, node.attr)
        if (isinstance(value, ast.Name)
                and value.id in modules
                and attr in modules[value.id]):
            if modules[value.id][attr]:
                return "{0}::{1}".format(value.id, attr)
            else:
                return "{0}::proxy::{1}()".format(value.id, attr)
        else:
            raise PythranSyntaxError(
                    "Attributes are only supported for namespaces",
                    node)

    def visit_Subscript(self, node):
        value = self.visit(node.value)
        # attribute case
        if metadata.get(node, metadata.Attribute):
            return "getattr<{0}>({1})".format(node.slice.value.n, value)
        # static index case
        elif (isinstance(node.slice, ast.Index)
                and isinstance(node.slice.value, ast.Num)
                and any(isinstance(node.slice.value.n, t)
                    for t in (int, long))):
            return "std::get<{0}>({1})".format(node.slice.value.n, value)
        # slice optimization case
        elif (isinstance(node.slice, ast.Slice)
                and (isinstance(node.ctx, ast.Store)
                    or node not in self.bounded_expressions)):
            slice = self.visit(node.slice)
            return "{1}({0})".format(slice, value)
        # standard case
        else:
            slice = self.visit(node.slice)
            return "{1}[{0}]".format(slice, value)

    def visit_Name(self, node):
        if node.id in self.local_declarations[-1]:
            return node.id
        elif node.id in modules["__builtins__"]:
            return "proxy::{0}()".format(node.id)
        elif (node.id in self.global_declarations
                or node.id in self.local_functions):
            return "{0}()".format(node.id)
        elif node.id in builtin_constructors:
            return "pythonic::constructor<{0}>()".format(
                    builtin_constructors[node.id])
        else:
            return node.id

    # other
    def visit_Slice(self, node):
        lower = node.lower and self.visit(node.lower)
        upper = node.upper and self.visit(node.upper)
        step = node.step and self.visit(node.step)
        cv = None
        if step == 'None':
            step = None  # happens when a[-4::]
        if not upper and not lower and step:  # special case
            if isinstance(node.step, ast.Num):
                cv = node.step.n
            else:
                print ast.dump(node.step)
                raise NotImplementedError(
                        "non constant step with undefined upper/lower bound")
        if step and not upper:
            upper = "std::numeric_limits<long>::max()"
        if upper and not lower:
            lower = "0"
        if cv and cv < 0:
            upper, lower = lower, upper
        return "core::slice({0})".format(", ".join(l
            for l in (lower, upper, step) if l))

    def visit_Index(self, node):
        return self.visit(node.value)

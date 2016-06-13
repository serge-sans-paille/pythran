'''
This module contains all pythran backends.
    * Cxx dumps the AST into C++ code
    * Python dumps the AST into Python code
'''
from __future__ import print_function

from pythran.analyses import ArgumentEffects, BoundExpressions, Dependencies
from pythran.analyses import LocalNodeDeclarations, GlobalDeclarations, Scope
from pythran.analyses import YieldPoints, IsAssigned, ASTMatcher, AST_any
from pythran.analyses import RangeValues, PureExpressions
from pythran.cxxgen import Template, Include, Namespace, CompilationUnit
from pythran.cxxgen import Statement, Block, AnnotatedStatement, Typedef
from pythran.cxxgen import Value, FunctionDeclaration, EmptyStatement, Static
from pythran.cxxgen import FunctionBody, Line, ReturnStatement, Struct, Assign
from pythran.cxxgen import For, While, TryExcept, ExceptHandler, If, AutoFor
from pythran.cxxtypes import (Assignable, DeclType, NamedType,
                              ListType, CombinedTypes, Lazy)
from pythran.openmp import OMPDirective
from pythran.passmanager import Backend
from pythran.syntax import PythranSyntaxError
from pythran.tables import operator_to_lambda, MODULES, pythran_ward
from pythran.types.conversion import PYTYPE_TO_CTYPE_TABLE, TYPE_TO_SUFFIX
from pythran.types.types import Types
from pythran.utils import attr_to_path
from pythran import metadata, unparse

from math import isnan, isinf
import ast
import os
import sys
if sys.version_info[0] < 3:
    import cStringIO
else:
    from io import StringIO as cStringIO


class Python(Backend):
    '''
    Produces a Python representation of the AST.

    >>> import ast, passmanager
    >>> node = ast.parse("print('hello world')")
    >>> pm = passmanager.PassManager('test')
    >>> print(pm.dump(Python, node))
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
            ["typename {0} {1}".format(t, "= {0}".format(d) if d else "")
             for t, d in zip(types, default_types)],
            node)
    else:
        return node


def strip_exp(s):
    if s.startswith('(') and s.endswith(')'):
        return s[1:-1]
    else:
        return s


def cxx_loop(fun):
    """
    Decorator for loop node (For and While) to handle "else" branching.

    Decorated node will save flags for a goto statement used instead of usual
    break and add this flag at the end of the else statements.

    Examples
    --------
    >> for i in xrange(12):
    >>     if i == 5:
    >>         break
    >> else:
    >>     ... some code ...

    Becomes

    >> for(type i : xrange(12))
    >>     if(i==5)
    >>         goto __no_breaking0;
    >> ... some code ...
    >> __no_breaking0;
    """
    def loop_visitor(self, node):
        """
        New decorate function.

        It push the breaking flag, run the visitor and add "else" statements.
        """
        if node.orelse:
            break_handler = "__no_breaking{0}".format(len(self.break_handlers))
        else:
            break_handler = None
        self.break_handlers.append(break_handler)

        res = fun(self, node)

        self.break_handlers.pop()

        # handle the body of the for loop
        if break_handler:
            orelse = map(self.visit, node.orelse)
            orelse_label = Statement("{0}:".format(break_handler))
            return Block([res] + orelse + [orelse_label])
        else:
            return res
    return loop_visitor


class Cxx(Backend):

    """
    Produces a C++ representation of the AST.

    Attributes
    ----------
    ldecls : {ast.Name}
        set of local declarations.
    break_handler : [str]
        It contains flags for goto statements to jump on break in case of
        orelse statement in loop. None means there are no orelse statement so
        no jump are requiered.
        (else in loop means : don't execute if loop is terminated with a break)

    >>> import ast, passmanager, os
    >>> node = ast.parse("def foo(): print('hello world')")
    >>> pm = passmanager.PassManager('test')
    >>> r = pm.dump(Cxx, node)
    >>> print(str(r).replace(os.sep, '/'))
    #include <pythonic/include/__builtin__/print.hpp>
    #include <pythonic/include/__builtin__/str.hpp>
    #include <pythonic/__builtin__/print.hpp>
    #include <pythonic/__builtin__/str.hpp>
    namespace __pythran_test
    {
      ;
      struct foo
      {
        typedef void callable;
        ;
        struct type
        {
          typedef typename pythonic::returnable<\
pythonic::types::none_type>::type result_type;
        }  ;
        typename type::result_type operator()() const;
        ;
      }  ;
      typename foo::type::result_type foo::operator()() const
      {
        pythonic::__builtin__::print("hello world");
      }
    }
    """

    # recover previous generator state
    generator_state_holder = "__generator_state"
    generator_state_value = "__generator_value"
    # flags the last statement of a generator
    final_statement = "that_is_all_folks"

    def __init__(self):
        """ Basic initialiser gathering analysis informations. """
        self.declarations = list()
        self.definitions = list()
        self.break_handlers = list()
        self.result = None
        self.ldecls = set()
        super(Cxx, self).__init__(Dependencies, GlobalDeclarations,
                                  BoundExpressions, Types, ArgumentEffects,
                                  Scope, RangeValues, PureExpressions)

    # mod
    def visit_Module(self, node):
        """ Build a compilation unit. """
        # build all types
        headers = [Include(os.path.join("pythonic", "include",  *t) + ".hpp")
                   for t in self.dependencies]
        headers += [Include(os.path.join("pythonic", *t) + ".hpp")
                    for t in self.dependencies]

        body = map(self.visit, node.body)

        nsbody = body + self.declarations + self.definitions
        ns = Namespace(pythran_ward + self.passmanager.module_name, nsbody)
        self.result = CompilationUnit(headers + [ns])

    # local declaration processing
    def process_locals(self, node, node_visited, *skipped):
        """
        Declare variable local to node and insert declaration before.

        Not possible for function yielding values.
        """
        local_vars = self.scope[node].difference(skipped)
        if not local_vars or self.yields:
            return node_visited  # no processing

        locals_visited = []
        for varname in local_vars:
            vartype = self.typeof(varname)
            decl = Statement("{} {}".format(vartype, varname))
            locals_visited.append(decl)
        self.ldecls = {ld for ld in self.ldecls if ld.id not in local_vars}
        return Block(locals_visited + [node_visited])

    def process_omp_attachements(self, node, stmt, index=None):
        """
        Add OpenMP pragma on the correct stmt in the correct order.

        stmt may be a list. On this case, index have to be specify to add
        OpenMP on the correct statement.
        """
        omp_directives = metadata.get(node, OMPDirective)
        if omp_directives:
            directives = list()
            for directive in reversed(omp_directives):
                directive.deps = map(self.visit, directive.deps)
                directives.append(directive)
            if index is None:
                stmt = AnnotatedStatement(stmt, directives)
            else:
                stmt[index] = AnnotatedStatement(stmt[index], directives)
        return stmt

    def typeof(self, node):
        if isinstance(node, str):
            return self.typeof(self.local_names[node])
        else:
            return self.types[node].generate(self.lctx)

    # stmt
    def visit_FunctionDef(self, node):
        class CachedTypeVisitor:
            class CachedType:
                def __init__(self, s):
                    self.s = s

                def generate(self, _):
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

        self.fname = node.name

        # prepare context and visit function body
        fargs = node.args.args

        formal_args = [arg.id for arg in fargs]
        formal_types = ["argument_type" + str(i) for i in xrange(len(fargs))]

        self.ldecls = set(self.passmanager.gather(LocalNodeDeclarations, node))

        self.local_names = {sym.id: sym for sym in self.ldecls}
        self.local_names.update({arg.id: arg for arg in fargs})
        self.extra_declarations = []

        self.lctx = CachedTypeVisitor()

        # choose one node among all the ones with the same name for each name
        self.ldecls = set({n.id: n for n in self.ldecls}.itervalues())

        # 0 is used as initial_state, thus the +1
        self.yields = {k: (1 + v, "yield_point{0}".format(1 + v)) for (v, k) in
                       enumerate(self.passmanager.gather(YieldPoints, node))}

        # gather body dump
        operator_body = map(self.visit, node.body)

        # compute arg dump
        default_arg_values = (
            [None] * (len(node.args.args) - len(node.args.defaults)) +
            [self.visit(n) for n in node.args.defaults])
        default_arg_types = (
            [None] * (len(node.args.args) - len(node.args.defaults)) +
            [self.types[n] for n in node.args.defaults])

        # compute type dump
        result_type = self.types[node][0]

        callable_type = Typedef(Value("void", "callable"))
        pure_type = (Typedef(Value("void", "pure"))
                     if node in self.pure_expressions else EmptyStatement())

        def make_function_declaration(rtype, name, ftypes, fargs,
                                      defaults=None, attributes=None):
            if defaults is None:
                defaults = [None] * len(ftypes)
            if attributes is None:
                attributes = []
            arguments = list()
            for i, (t, a, d) in enumerate(zip(ftypes, fargs, defaults)):
                if self.yields:
                    rvalue_ref = ""
                elif self.argument_effects[node][i]:
                    rvalue_ref = "&&"
                else:
                    rvalue_ref = " const &"
                argument = Value(
                    t + rvalue_ref,
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
                    Line(': pythonic::yielder() {}')
                    )]
            if formal_types:
                # If all parameters have a default value, we don't need default
                # constructor
                if default_arg_values and all(default_arg_values):
                    next_constructors = list()
                next_constructors.append(FunctionBody(
                    make_function_declaration("", next_name, formal_types,
                                              formal_args, default_arg_values),
                    Line(": {0} {{ }}".format(
                        ", ".join(["pythonic::yielder()"] +
                                  map("{0}({0})".format, formal_args))))
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
                        Value("pythonic::types::generator_iterator<{0}>"
                              .format(next_name),
                              "begin"),
                        []),
                    Block([Statement("next()"),
                           ReturnStatement(
                               "pythonic::types::generator_iterator<{0}>"
                               "(*this)".format(next_name))])),
                FunctionBody(
                    FunctionDeclaration(
                        Value("pythonic::types::generator_iterator<{0}>"
                              .format(next_name),
                              "end"),
                        []),
                    Block([ReturnStatement(
                        "pythonic::types::generator_iterator<{0}>()"
                        .format(next_name))]))
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
            next_body.insert(0, Statement("switch({0}) {{ {1} }}".format(
                Cxx.generator_state_holder,
                " ".join("case {0}: goto {1};".format(num, where)
                         for (num, where) in sorted(
                             self.yields.itervalues(),
                             key=lambda x: x[0])))))

            ctx = CachedTypeVisitor(self.lctx)
            next_members = ([Statement("{0} {1}".format(ft, fa))
                             for (ft, fa) in zip(formal_types, formal_args)] +
                            [Statement(
                                "{0} {1}".format(self.types[k].generate(ctx),
                                                 k.id))
                                for k in self.ldecls] +
                            [Statement("{0} {1}".format(v, k))
                             for k, v in self.extra_declarations] +
                            [Statement(
                                "typename {0}::result_type {1}".format(
                                    instanciated_next_name,
                                    Cxx.generator_state_value))])

            extern_typedefs = [Typedef(Value(t.generate(ctx), t.name))
                               for t in self.types[node][1] if not t.isweak()]
            iterator_typedef = [
                Typedef(
                    Value("pythonic::types::generator_iterator<{0}>".format(
                        "{0}<{1}>".format(next_name, ", ".join(formal_types))
                        if formal_types else next_name),
                        "iterator")),
                Typedef(Value(result_type.generate(ctx),
                              "value_type"))]
            result_typedef = [
                Typedef(Value(result_type.generate(ctx), "result_type"))]
            extra_typedefs = (ctx.typedefs() +
                              extern_typedefs +
                              iterator_typedef +
                              result_typedef)

            next_struct = templatize(
                Struct(next_name,
                       extra_typedefs +
                       next_members +
                       next_constructors +
                       next_iterator +
                       next_declaration, "pythonic::yielder"),
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
                [topstruct_type, callable_type, pure_type] +
                operator_declaration)

            self.declarations.append(next_struct)
            self.definitions.append(next_definition)

        else:  # regular function case
            # a function has a call operator to be called
            # and a default constructor to create instances
            fscope = "type{0}::".format("<{0}>".format(", ".join(formal_types))
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
            ctx = CachedTypeVisitor(self.lctx)
            operator_local_declarations = (
                [Statement("{0} {1}".format(
                    self.types[k].generate(ctx), k.id)) for k in self.ldecls] +
                [Statement("{0} {1}".format(v, k))
                 for k, v in self.extra_declarations]
            )
            dependent_typedefs = ctx.typedefs()
            operator_definition = FunctionBody(
                templatize(operator_signature, formal_types),
                Block(dependent_typedefs +
                      operator_local_declarations +
                      operator_body)
                )

            ctx = CachedTypeVisitor()
            extra_typedefs = (
                [Typedef(Value(t.generate(ctx), t.name))
                 for t in self.types[node][1] if not t.isweak()] +
                [Typedef(Value(
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
            topstruct = Struct(node.name,
                               [callable_type, pure_type] +
                               return_declaration +
                               operator_declaration)

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
            value = self.visit(node.value)
            if metadata.get(node, metadata.StaticReturn):
                # don't rely on auto because we want to make sure there's no
                # conversion each time we return
                # this happens for variant because the variant param
                # order may differ from the init order (because of the way we
                # do type inference
                rtype = "typename {}::type::result_type".format(self.fname)
                stmt = Block([Assign("static %s tmp_global" % rtype, value),
                              ReturnStatement("tmp_global")])
            else:
                stmt = ReturnStatement(value)
            return self.process_omp_attachements(node, stmt)

    def visit_Delete(self, _):
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
        """
        Create Assign node for final Cxx representation.

        It tries to handle multi assignment like:

        >> a = b = c = 2

        If only one local variable is assigned, typing is added:

        >> int a = 2;

        TODO: Handle case of multi-assignement for some local variables.

        Finally, process OpenMP clause like #pragma omp atomic
        """
        if not all(isinstance(n, (ast.Name, ast.Subscript))
                   for n in node.targets):
            raise PythranSyntaxError(
                "Must assign to an identifier or a subscript",
                node)
        value = self.visit(node.value)
        targets = [self.visit(t) for t in node.targets]
        alltargets = "= ".join(targets)
        islocal = (len(targets) == 1 and
                   isinstance(node.targets[0], ast.Name) and
                   node.targets[0].id in self.scope[node])
        if islocal and not self.yields:
            # remove this decl from local decls
            tdecls = {t.id for t in node.targets}
            self.ldecls = {d for d in self.ldecls if d.id not in tdecls}
            # add a local declaration
            if self.types[node.targets[0]].iscombined():
                alltargets = '{} {}'.format(self.typeof(node.targets[0]),
                                            alltargets)
            elif isinstance(self.types[node.targets[0]], Assignable):
                alltargets = '{} {}'.format(
                    Assignable(NamedType('decltype({})'.format(value))),
                    alltargets)
            else:
                assert isinstance(self.types[node.targets[0]], Lazy)
                alltargets = '{} {}'.format(
                    Lazy(NamedType('decltype({})'.format(value))),
                    alltargets)
        stmt = Assign(alltargets, value)
        return self.process_omp_attachements(node, stmt)

    def visit_AugAssign(self, node):
        value = self.visit(node.value)
        target = self.visit(node.target)
        l = operator_to_lambda[type(node.op)]
        if isinstance(node.op, (ast.FloorDiv, ast.Mod, ast.Pow)):
            stmt = Assign(target, l(target, value))
        else:
            stmt = Statement(l(target, '')[1:-2] + '= {0}'.format(value))
        return self.process_omp_attachements(node, stmt)

    def visit_Print(self, node):
        values = [self.visit(n) for n in node.values]
        stmt = Statement("pythonic::__builtin__::print{0}({1})".format(
            "" if node.nl else "_nonl",
            ", ".join(values))
            )
        return self.process_omp_attachements(node, stmt)

    def gen_for(self, node, target, local_iter, loop_body):
        """
        Create For representation on iterator for Cxx generation.

        Examples
        --------
        >> "omp parallel for"
        >> for i in xrange(10):
        >>     ... do things ...

        Becomes

        >> "omp parallel for shared(__iterX)"
        >> for(decltype(__iterX)::iterator __targetX = __iterX.begin();
               __targetX < __iterX.end(); ++__targetX)
        >>         auto&& i = *__targetX;
        >>     ... do things ...

        It the case of not local variable, typing for `i` disappear and typing
        is removed for iterator in case of yields statement in function.
        """
        # Choose target variable for iterator (which is iterator type)
        local_target = "__target{0}".format(len(self.break_handlers))
        local_target_decl = NamedType("typename decltype({0})::iterator".
                                      format(local_iter))

        # For yield function, all variables are globals.
        if self.yields:
            self.extra_declarations.append((local_target, local_target_decl,))
            local_target_decl = ""

        # If variable is local to the for body it's a ref to the iterator value
        # type
        if node.target.id in self.scope[node] and not self.yields:
            self.ldecls = {d for d in self.ldecls
                           if d.id != node.target.id}
            local_type = "auto&& ".format(
                local_target)
        else:
            local_type = ""

        # Assign iterable value
        loop_body_prelude = Statement("{} {}= *{}".format(local_type,
                                                          target,
                                                          local_target))

        # Create the loop
        loop = For("{0} {1} = {2}.begin()".format(local_target_decl,
                                                  local_target,
                                                  local_iter),
                   "{0} < {1}.end()".format(local_target, local_iter),
                   "++{0}".format(local_target),
                   Block([loop_body_prelude, loop_body]))
        return [self.process_omp_attachements(node, loop)]

    def handle_real_loop_comparison(self, args, stmts, target, upper_bound,
                                    step):
        """
        Handle comparison for real loops.

        Add the correct comparison operator if possible or set a runtime __cmp
        comparison.
        """
        # order is 1 for increasing loop, -1 for decreasing loop and 0 if it is
        # not known at compile time
        if len(args) <= 2:
            order = 1
        elif isinstance(args[2], ast.Num):
            order = -1 + 2 * (int(args[2].n) > 0)
        elif isinstance(args[1], ast.Num) and isinstance(args[0], ast.Num):
            order = -1 + 2 * (int(args[1].n) > int(args[0].n))
        else:
            order = 0

        if order:
            comparison = "{} < {}" if order == 1 else "{} > {}"
            comparison = comparison.format(target, upper_bound)
            for_pos = 0
        else:
            cmp_type = "std::function<bool(long, long)> "
            cmp_op = "__cmp{}".format(len(self.break_handlers))

            # For yield function, all variables are globals.
            if self.yields:
                self.extra_declarations.append((cmp_op, cmp_type))
                cmp_type = ""

            stmts.insert(0, Statement("{} {} = std::less<long>()".format(
                cmp_type, cmp_op)))
            stmts.insert(1, If("{} < 0L".format(step),
                               Statement("{} = std::greater<long>()".format(
                                   cmp_op))))
            for_pos = 2
            comparison = "{0}({1}, {2})".format(cmp_op, target, upper_bound)
        return comparison, for_pos

    def gen_c_for(self, node, local_iter, loop_body):
        """
        Create C For representation for Cxx generation.

        Examples
        --------
        >> for i in xrange(10):
        >>     ... do things ...

        Becomes

        >> for(long i = 0, __targetX = 10; i < __targetX; i += 1)
        >>     ... do things ...

        Or

        >> for i in xrange(10, 0, -1):
        >>     ... do things ...

        Becomes

        >> for(long i = 10, __targetX = 0; i > __targetX; i += -1)
        >>     ... do things ...

        Or

        >> for i in xrange(a, b, c):
        >>     ... do things ...

        Becomes

        >> std::function<bool(int, int)> __cmpX = std::less<long>();
        >> if(c < 0)
        >>     __cmpX = std::greater<long>();
        >> for(long i = a, __targetX = b; __cmpX(i, __targetX); i += c)
        >>     ... do things ...

        It the case of not local variable, typing for `i` disappear
        """
        args = node.iter.args
        step = "1L" if len(args) <= 2 else self.visit(args[2])
        if len(args) == 1:
            lower_bound = "0L"
            upper_value = self.visit(args[0])
        else:
            lower_bound = self.visit(args[0])
            upper_value = self.visit(args[1])

        upper_bound = "__target{0}".format(len(self.break_handlers))

        upper_type = iter_type = "long "

        # If variable is local to the for body keep it local...
        if node.target.id in self.scope[node] and not self.yields:
            self.ldecls = {d for d in self.ldecls if d.id != node.target.id}
            loop = list()
        else:
            # For yield function, upper_bound is globals.
            if self.yields:
                self.extra_declarations.append((upper_bound, upper_type))
                upper_type = ""
            iter_type = ""
            # Back one step to keep Python behavior (except for break)
            loop = [If("{} == {}".format(local_iter, upper_bound),
                    Statement("{} -= {}".format(local_iter, step)))]

        comparison, for_pos = self.handle_real_loop_comparison(args, loop,
                                                               local_iter,
                                                               upper_bound,
                                                               step)

        forloop = For("{0} {1} = {2}".format(iter_type, local_iter,
                                             lower_bound),
                      comparison,
                      "{0} += {1}".format(local_iter, step),
                      loop_body)

        loop.insert(for_pos, self.process_omp_attachements(node, forloop))

        # Store upper bound value
        header = [Statement("{0} {1} = {2}".format(upper_type, upper_bound,
                                                   upper_value))]
        return header, loop

    def handle_omp_for(self, node, local_iter):
        """
        Fix OpenMP directives on For loops.

        Add the target as private variable as a new variable may have been
        introduce to handle cxx iterator.

        Also, add the iterator as shared variable as all 'parallel for chunck'
        have to use the same iterator.
        """
        for directive in metadata.get(node, OMPDirective):
            if any(key in directive.s for key in (' parallel ', ' task ')):
                # Eventually add local_iter in a shared clause as iterable is
                # shared in the for loop (for every clause with datasharing)
                directive.s += ' shared({})'
                directive.deps.append(ast.Name(local_iter, ast.Load()))

            target = node.target
            assert isinstance(target, ast.Name)
            hasfor = 'for' in directive.s
            nodefault = 'default' not in directive.s
            noindexref = all(isinstance(x, ast.Name) and
                             x.id != target.id for x in directive.deps)
            if (hasfor and nodefault and noindexref and
                    target.id not in self.scope[node]):
                # Target is private by default in omp but iterator use may
                # introduce an extra variable
                directive.s += ' private({})'
                directive.deps.append(ast.Name(target.id, ast.Load()))

    def can_use_autofor(self, node):
        """
        Check if given for Node can use autoFor syntax.

        To use auto_for:
            - iterator should have local scope
            - yield should not be use
            - OpenMP pragma should not be use

        TODO : Yield should block only if it is use in the for loop, not in the
               whole function.
        """
        auto_for = (isinstance(node.target, ast.Name) and
                    node.target.id in self.scope[node])
        auto_for &= not self.yields
        auto_for &= not metadata.get(node, OMPDirective)
        return auto_for

    def can_use_c_for(self, node):
        """
        Check if a for loop can use classic C syntax.

        To use C syntax:
            - target should not be assign in the loop
            - xrange should be use as iterator
            - order have to be known at compile time or OpenMP should not be
              use

        """
        assert isinstance(node.target, ast.Name)
        pattern = ast.Call(func=ast.Attribute(value=ast.Name(id='__builtin__',
                                                             ctx=ast.Load()),
                                              attr='xrange', ctx=ast.Load()),
                           args=AST_any(), keywords=[], starargs=None,
                           kwargs=None)
        is_assigned = {node.target.id: False}
        [is_assigned.update(self.passmanager.gather(IsAssigned, stmt))
         for stmt in node.body]

        if (node.iter not in ASTMatcher(pattern).search(node.iter) or
                is_assigned[node.target.id]):
            return False

        args = node.iter.args
        if (len(args) > 2 and (not isinstance(args[2], ast.Num) and
                               not (isinstance(args[1], ast.Num) and
                                    isinstance(args[0], ast.Num))) and
                metadata.get(node, OMPDirective)):
            return False
        return True

    @cxx_loop
    def visit_For(self, node):
        """
        Create For representation for Cxx generation.

        Examples
        --------
        >> for i in xrange(10):
        >>     ... work ...

        Becomes

        >> typename returnable<decltype(__builtin__.xrange(10))>::type __iterX
           = __builtin__.xrange(10);
        >> ... possible container size reservation ...
        >> for (auto&& i: __iterX)
        >>     ... the work ...

        This function also handle assignment for local variables.

        We can notice that three kind of loop are possible:
        - Normal for loop on iterator
        - Autofor loop.
        - Normal for loop using integer variable iteration
        Kind of loop used depend on OpenMP, yield use and variable scope.
        """
        if not isinstance(node.target, ast.Name):
            raise PythranSyntaxError(
                "Using something other than an identifier as loop target",
                node.target)
        target = self.visit(node.target)

        # Handle the body of the for loop
        loop_body = Block(map(self.visit, node.body))

        # Declare local variables at the top of the loop body
        loop_body = self.process_locals(node, loop_body, node.target.id)
        iterable = self.visit(node.iter)

        if self.can_use_c_for(node):
            header, loop = self.gen_c_for(node, target, loop_body)
        else:

            if self.can_use_autofor(node):
                header = []
                self.ldecls = {d for d in self.ldecls
                               if d.id != node.target.id}
                autofor = AutoFor(target, iterable, loop_body)
                loop = [self.process_omp_attachements(node, autofor)]
            else:
                # Iterator declaration
                local_iter = "__iter{0}".format(len(self.break_handlers))
                local_iter_decl = Assignable(DeclType(iterable))

                self.handle_omp_for(node, local_iter)

                # For yield function, iterable is globals.
                if self.yields:
                    self.extra_declarations.append(
                        (local_iter, local_iter_decl,))
                    local_iter_decl = ""

                # Assign iterable
                # For C loop, it avoids issues
                # if the upper bound is assigned in the loop
                header = [Statement("{0} {1} = {2}".format(local_iter_decl,
                                                           local_iter,
                                                           iterable))]
                loop = self.gen_for(node, target, local_iter, loop_body)

        # For xxxComprehension, it is replaced by a for loop. In this case,
        # pre-allocate size of container.
        for comp in metadata.get(node, metadata.Comprehension):
            header.append(Statement("pythonic::utils::reserve({0},{1})".format(
                comp.target,
                iterable)))

        return Block(header + loop)

    @cxx_loop
    def visit_While(self, node):
        """
        Create While node for Cxx generation.

        It is a cxx_loop to handle else clause.
        """
        test = self.visit(node.test)
        body = [self.visit(n) for n in node.body]
        stmt = While(test, Block(body))
        return self.process_omp_attachements(node, stmt)

    def visit_TryExcept(self, node):
        body = [self.visit(n) for n in node.body]
        except_ = list()
        [except_.extend(self.visit(n)) for n in node.handlers]
        return TryExcept(Block(body), except_)

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
        type_ = node.type and self.visit(node.type)
        if node.inst:
            if isinstance(node.inst, ast.Tuple):
                inst = ['"{0}"'.format(e.s) for e in node.inst.elts]
            else:
                inst = [node.inst.s]
        else:
            inst = None
        if inst:
            return Statement("throw {0}({1})".format(type_, ", ".join(inst)))
        else:
            return Statement("throw {0}".format(type_ or ""))

    def visit_Assert(self, node):
        params = [self.visit(node.test), node.msg and self.visit(node.msg)]
        sparams = ", ".join(map(strip_exp, filter(None, params)))
        return Statement("pythonic::pythran_assert({0})".format(sparams))

    def visit_Import(self, _):
        return EmptyStatement()  # everything is already #included

    def visit_ImportFrom(self, _):
        assert False, "should be filtered out by the expand_import pass"

    def visit_Expr(self, node):
        stmt = Statement(self.visit(node.value))
        return self.process_locals(node,
                                   self.process_omp_attachements(node, stmt))

    def visit_Pass(self, node):
        stmt = EmptyStatement()
        return self.process_omp_attachements(node, stmt)

    def visit_Break(self, _):
        """
        Generate break statement in most case and goto for orelse clause.

        See Also : cxx_loop
        """
        if self.break_handlers[-1]:
            return Statement("goto {0}".format(self.break_handlers[-1]))
        else:
            return Statement("break")

    def visit_Continue(self, _):
        return Statement("continue")

    # expr
    def visit_BoolOp(self, node):
        values = [self.visit(value) for value in node.values]
        if node in self.bound_expressions:
            op = operator_to_lambda[type(node.op)]
        elif isinstance(node.op, ast.And):
            def op(l, r):
                return '({0} and {1})'.format(l, r)
        elif isinstance(node.op, ast.Or):
            def op(l, r):
                return '({0} or {1})'.format(l, r)
        return reduce(op, values)

    def visit_BinOp(self, node):
        left = self.visit(node.left)
        right = self.visit(node.right)
        if isinstance(node.left, ast.Str):
            left = "pythonic::types::str({})".format(left)
        elif isinstance(node.right, ast.Str):
            right = "pythonic::types::str({})".format(right)
        return operator_to_lambda[type(node.op)](left, right)

    def visit_UnaryOp(self, node):
        operand = self.visit(node.operand)
        return operator_to_lambda[type(node.op)](operand)

    def visit_IfExp(self, node):
        test = self.visit(node.test)
        body = self.visit(node.body)
        orelse = self.visit(node.orelse)
        return ("(pythonic::__builtin__::functor::bool_{{}}"
                "({0}) ? {1} : {2})".format(test, body, orelse))

    def visit_List(self, node):
        if not node.elts:  # empty list
            return "pythonic::__builtin__::functor::list{}()"
        else:
            elts = [self.visit(n) for n in node.elts]
            elts_type = [DeclType(elt) for elt in elts]
            if len(elts_type) == 1:
                elts_type = elts_type[0]
            else:
                elts_type = CombinedTypes(*elts_type)
            node_type = ListType(elts_type)

            # constructor disambiguation, clang++ workaround
            if len(elts) == 1:
                elts.append('pythonic::types::single_value()')

            return "{0}({{ {1} }})".format(
                Assignable(node_type),
                ", ".join(elts))

    def visit_Set(self, node):
        if not node.elts:  # empty set
            return "pythonic::__builtin__::functor::set{}()"
        else:
            elts = [self.visit(n) for n in node.elts]
            return "{0}({{ {1} }})".format(
                Assignable(self.types[node]),
                ", ".join(elts))

    def visit_Dict(self, node):
        if not node.keys:  # empty dict
            return "pythonic::__builtin__::functor::dict{}()"
        else:
            keys = [self.visit(n) for n in node.keys]
            values = [self.visit(n) for n in node.values]
            return "{0}({{ {1} }})".format(
                Assignable(self.types[node]),
                ", ".join("{{ {0}, {1} }}".format(k, v)
                          for k, v in zip(keys, values)))

    def visit_Tuple(self, node):
        elts = map(self.visit, node.elts or ())
        return "pythonic::types::make_tuple({0})".format(", ".join(elts))

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
        # special hook for getattr, as we cannot represent it in C++
        if func == 'pythonic::__builtin__::functor::getattr{}':
            return ('pythonic::__builtin__::getattr<{}>({})'
                    .format('pythonic::types::attr::' + node.args[1].s.upper(),
                            args[0]))
        else:
            return "{}({})".format(func, ", ".join(args))

    def visit_Num(self, node):
        if isinstance(node.n, complex):
            return "{0}({1}, {2})".format(
                PYTYPE_TO_CTYPE_TABLE[complex],
                repr(node.n.real),
                repr(node.n.imag))
        elif isinstance(node.n, long):
            return 'pythran_long({0})'.format(node.n)
        elif isnan(node.n):
            return 'pythonic::numpy::nan'
        elif isinf(node.n):
            return ('+' if node.n > 0 else '-') + 'pythonic::numpy::inf'
        else:
            return repr(node.n) + TYPE_TO_SUFFIX.get(type(node.n), "")

    def visit_Str(self, node):
        quoted = node.s.replace('"', '\\"').replace('\n', '\\n"\n"')
        return '"' + quoted + '"'

    def visit_Attribute(self, node):
        obj, path = attr_to_path(node)
        sattr = '::'.join(path)
        if not obj.isliteral():
            sattr += '{}'
        return sattr

    def visit_Subscript(self, node):
        value = self.visit(node.value)
        # we cannot overload the [] operator in that case
        if isinstance(node.value, ast.Str):
            value = 'pythonic::types::str({})'.format(value)
        # positive static index case
        if (isinstance(node.slice, ast.Index) and
            isinstance(node.slice.value, ast.Num) and
            (node.slice.value.n >= 0) and
            any(isinstance(node.slice.value.n, t)
                for t in (int, long))):
            return "std::get<{0}>({1})".format(node.slice.value.n, value)
        # slice optimization case
        elif (isinstance(node.slice, ast.Slice) and
              (isinstance(node.ctx, ast.Store) or
               node not in self.bound_expressions)):
            slice_ = self.visit(node.slice)
            return "{1}({0})".format(slice_, value)
        # extended slice case
        elif isinstance(node.slice, ast.ExtSlice):
            slice_ = self.visit(node.slice)
            return "{1}({0})".format(','.join(slice_), value)
        # positive indexing case
        elif (isinstance(node.slice, ast.Index) and
              isinstance(node.slice.value, ast.Name) and
              self.range_values[node.slice.value.id].low >= 0):
            slice_ = self.visit(node.slice)
            return "{1}.fast({0})".format(slice_, value)
        # standard case
        else:
            slice_ = self.visit(node.slice)
            return "{1}[{0}]".format(slice_, value)

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
            arg = (self.visit(nfield) if nfield
                   else 'pythonic::__builtin__::None')
            args.append(arg)
        if node.step is None or (isinstance(node.step, ast.Num) and
                                 node.step.n == 1):
            return "pythonic::types::contiguous_slice({},{})".format(args[0],
                                                                     args[1])
        else:
            return "pythonic::types::slice({},{},{})".format(*args)

    def visit_Index(self, node):
        return self.visit(node.value)

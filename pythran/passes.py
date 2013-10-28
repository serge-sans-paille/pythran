'''
This modules contains code transformation to turn python AST into
    pythran AST
    * NormalizeTuples removes implicit variable -> tuple conversion
    * RemoveComprehension turns list comprehension into function calls
    * RemoveNestedFunctions turns nested function into top-level functions
    * RemoveLambdas turns lambda into regular functions
    * NormalizeReturn adds return statement where relevant
    * NormalizeMethodCalls turns built in method calls into function calls
    * NormalizeCompare turns complex compare into function calls
    * NormalizeAttributes turns built in attributes into function calls
    * NormalizeIdentifiers prevents conflicts with c++ keywords
    * NormalizeException simplifies try blocks
    * UnshadowParameters prevents the shadow parameter phenomenon
    * ExpandImports replaces imports by their full paths
    * ExpandImportAll replaces import * by all their modules
    * ExpandBuiltins replaces builtins by their full paths
    * FalsePolymorphism rename variable if possible to avoid false polymorphism
'''

from analysis import ImportedIds, Identifiers, YieldPoints, Globals, Locals
from analysis import UsedDefChain, UseOMP, CFG, GlobalDeclarations
from passmanager import Transformation
from tables import methods, attributes, functions, modules
from tables import cxx_keywords, namespace
from operator import itemgetter
from copy import copy
import networkx as nx
import metadata
import ast


##
class _ConvertToTuple(ast.NodeTransformer):
    def __init__(self, tuple_id, renamings):
        self.tuple_id = tuple_id
        self.renamings = renamings

    def visit_Name(self, node):
        if node.id in self.renamings:
            nnode = reduce(
                    lambda x, y: ast.Subscript(
                        x,
                        ast.Index(ast.Num(y)),
                        ast.Load()),
                    self.renamings[node.id],
                    ast.Name(self.tuple_id, ast.Load())
                    )
            nnode.ctx = node.ctx
            return nnode
        return node


class NormalizeTuples(Transformation):
    """
    Remove implicit tuple -> variable conversion.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("a=(1,2.) ; i,j = a")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeTuples, node)
    >>> print pm.dump(backend.Python, node)
    a = (1, 2.0)
    if 1:
        __tuple10 = a
        i = __tuple10[0]
        j = __tuple10[1]
    """
    tuple_name = "__tuple"

    def __init__(self):
        self.counter = 0
        Transformation.__init__(self)

    def traverse_tuples(self, node, state, renamings):
        if isinstance(node, ast.Name):
            if state:
                renamings[node.id] = state
        elif isinstance(node, ast.Tuple) or isinstance(node, ast.List):
            [self.traverse_tuples(n, state + (i,), renamings)
                    for i, n in enumerate(node.elts)]
        elif isinstance(node, ast.Subscript):
            if state:
                renamings[node] = state
        else:
            raise NotImplementedError

    def visit_comprehension(self, node):
        renamings = dict()
        self.traverse_tuples(node.target, (), renamings)
        if renamings:
            self.counter += 1
            return (
                    "{0}{1}".format(
                        NormalizeTuples.tuple_name,
                        self.counter),
                    renamings)
        else:
            return node

    def visit_AnyComp(self, node, *fields):
        for field in fields:
            setattr(node, field, self.visit(getattr(node, field)))
        generators = map(self.visit, node.generators)
        nnode = node
        for i, g in enumerate(generators):
            if isinstance(g, tuple):
                gtarget = "{0}{1}".format(g[0], i)
                nnode.generators[i].target = ast.Name(
                        gtarget,
                        nnode.generators[i].target.ctx)
                metadata.add(
                        nnode.generators[i].target,
                        metadata.LocalVariable())
                nnode = _ConvertToTuple(gtarget, g[1]).visit(nnode)
        for field in fields:
            setattr(node, field, getattr(nnode, field))
        node.generators = nnode.generators
        return node

    def visit_ListComp(self, node):
        return self.visit_AnyComp(node, 'elt')

    def visit_SetComp(self, node):
        return self.visit_AnyComp(node, 'elt')

    def visit_DictComp(self, node):
        return self.visit_AnyComp(node, 'key', 'value')

    def visit_GeneratorExp(self, node):
        return self.visit_AnyComp(node, 'elt')

    def visit_Lambda(self, node):
        self.generic_visit(node)
        for i, arg in enumerate(node.args.args):
            renamings = dict()
            self.traverse_tuples(arg, (), renamings)
            if renamings:
                self.counter += 1
                nname = "{0}{1}".format(
                        NormalizeTuples.tuple_name,
                        self.counter)
                node.args.args[i] = ast.Name(nname, ast.Param())
                node.body = _ConvertToTuple(nname, renamings).visit(node.body)
        return node

    def visit_Assign(self, node):
        self.generic_visit(node)
        extra_assign = [node]
        for i, t in enumerate(node.targets):
            if isinstance(t, ast.Tuple) or isinstance(t, ast.List):
                renamings = dict()
                self.traverse_tuples(t, (), renamings)
                if renamings:
                    self.counter += 1
                    gtarget = "{0}{1}{2}".format(
                            NormalizeTuples.tuple_name,
                            self.counter,
                            i)
                    node.targets[i] = ast.Name(gtarget, node.targets[i].ctx)
                    metadata.add(node.targets[i], metadata.LocalVariable())
                    for rename, state in sorted(renamings.iteritems()):
                        nnode = reduce(
                                lambda x, y: ast.Subscript(
                                    x,
                                    ast.Index(ast.Num(y)),
                                    ast.Load()),
                                state,
                                ast.Name(gtarget, ast.Load()))
                        if isinstance(rename, str):
                            extra_assign.append(
                                    ast.Assign(
                                        [ast.Name(rename, ast.Store())],
                                        nnode))
                        else:
                            extra_assign.append(ast.Assign([rename], nnode))
        return (ast.If(ast.Num(1), extra_assign, [])
                if len(extra_assign) > 1
                else extra_assign)

    def visit_For(self, node):
        target = node.target
        if isinstance(target, ast.Tuple) or isinstance(target, ast.List):
            renamings = dict()
            self.traverse_tuples(target, (), renamings)
            if renamings:
                self.counter += 1
                gtarget = "{0}{1}".format(
                        NormalizeTuples.tuple_name,
                        self.counter
                        )
                node.target = ast.Name(gtarget, node.target.ctx)
                metadata.add(node.target, metadata.LocalVariable())
                for rename, state in sorted(renamings.iteritems()):
                    nnode = reduce(
                            lambda x, y: ast.Subscript(
                                x,
                                ast.Index(ast.Num(y)),
                                ast.Load()),
                            state,
                            ast.Name(gtarget, ast.Load()))
                    if isinstance(rename, str):
                        node.body.insert(0,
                                ast.Assign(
                                    [ast.Name(rename, ast.Store())],
                                    nnode)
                                )
                    else:
                        node.body.insert(0, ast.Assign([rename], nnode))

        self.generic_visit(node)
        return node


##
class RemoveComprehension(Transformation):
    """
    Turns all list comprehension from a node into new function calls.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("[x*x for x in (1,2,3)]")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(RemoveComprehension, node)
    >>> print pm.dump(backend.Python, node)
    list_comprehension0()
    def list_comprehension0():
        __target = __builtin__.list()
        for x in (1, 2, 3):
            __list__.append(__target, (x * x))
        return __target
    """

    def __init__(self):
        self.count = 0
        Transformation.__init__(self)

    def nest_reducer(self, x, g):
        def wrap_in_ifs(node, ifs):
            return reduce(lambda n, if_: ast.If(if_, [n], []), ifs, node)
        metadata.add(g.target, metadata.LocalVariable())
        return ast.For(g.target, g.iter, [wrap_in_ifs(x, g.ifs)], [])

    def visit_AnyComp(self, node, comp_type, comp_module, comp_method):
        node.elt = self.visit(node.elt)
        name = "{0}_comprehension{1}".format(comp_type, self.count)
        self.count += 1
        args = self.passmanager.gather(ImportedIds, node, self.ctx)
        self.count_iter = 0

        starget = "__target"
        body = reduce(self.nest_reducer,
                reversed(node.generators),
                ast.Expr(
                    ast.Call(
                        ast.Attribute(
                            ast.Name(comp_module, ast.Load()),
                            comp_method,
                            ast.Load()),
                        [ast.Name(starget, ast.Load()), node.elt],
                        [],
                        None,
                        None
                        )
                    )
                )
        # add extra metadata to this node
        metadata.add(body, metadata.Comprehension(starget))
        init = ast.Assign(
                [ast.Name(starget, ast.Store())],
                ast.Call(
                    ast.Attribute(
                        ast.Name('__builtin__', ast.Load()),
                        comp_type,
                        ast.Load()
                        ),
                    [], [], None, None)
                )
        result = ast.Return(ast.Name(starget, ast.Load()))
        sargs = sorted(ast.Name(arg, ast.Param()) for arg in args)
        fd = ast.FunctionDef(name,
                ast.arguments(sargs, None, None, []),
                [init, body, result],
                [])
        self.ctx.module.body.append(fd)
        return ast.Call(
                ast.Name(name, ast.Load()),
                [ast.Name(arg.id, ast.Load()) for arg in sargs],
                [],
                None,
                None
                )  # no sharing !

    def visit_ListComp(self, node):
        return self.visit_AnyComp(node, "list", "__list__", "append")

    def visit_SetComp(self, node):
        return self.visit_AnyComp(node, "set", "__set__", "add")

    def visit_DictComp(self, node):
        # this is a quickfix to match visit_AnyComp signature
        # potential source of improvement there!
        node.elt = ast.List(
                [ast.Tuple([node.key, node.value], ast.Load())],
                ast.Load()
                )
        return self.visit_AnyComp(node, "dict", "__dispatch__", "update")

    def visit_GeneratorExp(self, node):
        node.elt = self.visit(node.elt)
        name = "generator_expression{0}".format(self.count)
        self.count += 1
        args = self.passmanager.gather(ImportedIds, node, self.ctx)
        self.count_iter = 0

        body = reduce(self.nest_reducer,
                reversed(node.generators),
                ast.Expr(ast.Yield(node.elt))
                )

        sargs = sorted(ast.Name(arg, ast.Param()) for arg in args)
        fd = ast.FunctionDef(name,
                ast.arguments(sargs, None, None, []),
                [body],
                [])
        self.ctx.module.body.append(fd)
        return ast.Call(
                ast.Name(name, ast.Load()),
                [ast.Name(arg.id, ast.Load()) for arg in sargs],
                [],
                None,
                None
                )  # no sharing !


##
class _NestedFunctionRemover(Transformation):
    def __init__(self, pm, ctx):
        Transformation.__init__(self)
        self.ctx = ctx
        self.passmanager = pm
        self.global_declarations = pm.gather(GlobalDeclarations, ctx.module)

    def visit_FunctionDef(self, node):
        if modules['functools'] not in self.global_declarations.values():
            import_ = ast.Import([ast.alias('functools', None)])
            self.ctx.module.body.insert(0, import_)
            self.global_declarations['functools'] = modules['functools']

        self.ctx.module.body.append(node)

        former_name = node.name
        former_nbargs = len(node.args.args)
        new_name = "pythran_{0}".format(former_name)

        ii = self.passmanager.gather(ImportedIds, node, self.ctx)
        binded_args = [ast.Name(iin, ast.Load()) for iin in sorted(ii)]
        node.args.args = ([ast.Name(iin, ast.Param()) for iin in sorted(ii)]
                + node.args.args)

        class Renamer(ast.NodeTransformer):
            def visit_Call(self, node):
                self.generic_visit(node)
                if (isinstance(node.func, ast.Name)
                        and node.func.id == former_name):
                    node.func.id = new_name
                    node.args = (
                            [ast.Name(iin, ast.Load())
                                for iin in sorted(ii)]
                            + node.args
                            )
                return node
        Renamer().visit(node)

        node.name = new_name
        proxy_call = ast.Name(new_name, ast.Load())

        new_node = ast.Assign(
                [ast.Name(former_name, ast.Store())],
                ast.Call(
                    ast.Attribute(
                        ast.Name('functools', ast.Load()),
                        "partial",
                        ast.Load()
                        ),
                    [proxy_call] + binded_args,
                    [],
                    None,
                    None
                    )
                )

        self.generic_visit(node)
        return new_node


class RemoveNestedFunctions(Transformation):
    '''
    Replace nested function by top-level functions
    and a call to a bind intrinsic that
    generates a local function with some arguments binded.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(x):\\n def bar(y): return x+y\\n bar(12)")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(RemoveNestedFunctions, node)
    >>> print pm.dump(backend.Python, node)
    import functools
    def foo(x):
        bar = functools.partial(pythran_bar, x)
        bar(12)
    def pythran_bar(x, y):
        return (x + y)
    '''

    def visit_Module(self, node):
        map(self.visit, node.body)
        return node

    def visit_FunctionDef(self, node):
        nfr = _NestedFunctionRemover(self.passmanager, self.ctx)
        node.body = map(nfr.visit, node.body)
        return node


##
class _LambdaRemover(Transformation):

    def __init__(self, pm, name, ctx, lambda_functions, imports):
        Transformation.__init__(self)
        self.passmanager = pm
        self.ctx = ctx
        self.prefix = name
        self.lambda_functions = lambda_functions
        self.imports = imports
        self.global_declarations = pm.gather(GlobalDeclarations, ctx.module)

    def visit_Lambda(self, node):
        if modules['functools'] not in self.global_declarations.values():
            import_ = ast.Import([ast.alias('functools', None)])
            self.imports.append(import_)
            self.global_declarations['functools'] = modules['functools']

        self.generic_visit(node)
        forged_name = "{0}_lambda{1}".format(
                self.prefix,
                len(self.lambda_functions))

        ii = self.passmanager.gather(ImportedIds, node, self.ctx)
        ii.difference_update(self.lambda_functions)  # remove current lambdas

        binded_args = [ast.Name(iin, ast.Load()) for iin in sorted(ii)]
        former_nbargs = len(node.args.args)
        node.args.args = ([ast.Name(iin, ast.Param()) for iin in sorted(ii)]
                + node.args.args)
        forged_fdef = ast.FunctionDef(
                forged_name,
                copy(node.args),
                [ast.Return(node.body)],
                [])
        self.lambda_functions.append(forged_fdef)
        proxy_call = ast.Name(forged_name, ast.Load())
        if binded_args:
            return ast.Call(
                    ast.Attribute(
                        ast.Name('functools', ast.Load()),
                        "partial",
                        ast.Load()
                        ),
                    [proxy_call] + binded_args,
                    [],
                    None,
                    None)
        else:
            return proxy_call


class RemoveLambdas(Transformation):
    '''
    Turns lambda into top-level functions.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(y): lambda x:y+x")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(RemoveLambdas, node)
    >>> print pm.dump(backend.Python, node)
    import functools
    def foo(y):
        functools.partial(foo_lambda0, y)
    def foo_lambda0(y, x):
        return (y + x)
    '''

    def visit_Module(self, node):
        self.lambda_functions = list()
        self.imports = list()
        self.generic_visit(node)
        node.body = self.imports + node.body + self.lambda_functions
        return node

    def visit_FunctionDef(self, node):
        lr = _LambdaRemover(self.passmanager, node.name, self.ctx,
                            self.lambda_functions, self.imports)
        node.body = map(lr.visit, node.body)
        return node


##
class NormalizeReturn(Transformation):
    '''
    Adds Return statement when they are implicit,
    and adds the None return value when not set

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(y): print y")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeReturn, node)
    >>> print pm.dump(backend.Python, node)
    def foo(y):
        print y
        return __builtin__.None
    '''

    def __init__(self):
        super(NormalizeReturn, self).__init__(CFG)

    def visit_FunctionDef(self, node):
        self.yield_points = self.passmanager.gather(YieldPoints, node)
        map(self.visit, node.body)
        # Look for nodes that have no successors
        for n in self.cfg.predecessors(None):
            if type(n) not in (ast.Return, ast.Raise):
                if self.yield_points:
                    node.body.append(ast.Return(None))
                else:
                    none = ast.Attribute(ast.Name("__builtin__", ast.Load()),
                            'None', ast.Load())
                    node.body.append(ast.Return(none))
                break

        return node

    def visit_Return(self, node):
        if not node.value and not self.yield_points:
            none = ast.Attribute(ast.Name("__builtin__", ast.Load()),
                    'None', ast.Load())
            node.value = none
        return node


##
class NormalizeMethodCalls(Transformation):
    '''
    Turns built in method calls into function calls.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("l.append(12)")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeMethodCalls, node)
    >>> print pm.dump(backend.Python, node)
    __list__.append(l, 12)
    '''

    def __init__(self):
        Transformation.__init__(self, Globals)
        self.imports = set()

    def visit_FunctionDef(self, node):
        self.imports = self.globals.copy()
        [self.imports.discard(arg.id) for arg in node.args.args]
        self.generic_visit(node)
        return node

    def visit_Import(self, node):
        for alias in node.names:
            self.imports.add(alias.asname or alias.name)
        return node

    def visit_Assign(self, node):
        n = self.generic_visit(node)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.imports.discard(t.id)
        return n

    def visit_For(self, node):
        node.iter = self.visit(node.iter)
        if isinstance(node.target, ast.Name):
            self.imports.discard(node.target.id)
        if node.body:
            node.body = [self.visit(n) for n in node.body]
        if node.orelse:
            node.orelse = [self.visit(n) for n in node.orelse]
        return node

    def visit_Call(self, node):
        node = self.generic_visit(node)
        if isinstance(node.func, ast.Attribute):
            lhs = node.func.value
            if node.func.attr in methods:
                isname = isinstance(lhs, ast.Name)
                ispath = isname or isinstance(lhs, ast.Attribute)
                if not ispath or (isname and lhs.id not in self.imports):
                    node.args.insert(0, node.func.value)
                    node.func = ast.Attribute(
                            ast.Name(methods[node.func.attr][0], ast.Load()),
                            node.func.attr,
                            ast.Load())
            if node.func.attr in methods or node.func.attr in functions:
                def renamer(v):
                    name = '__{0}__'.format(v)
                    if name in modules:
                        return name
                    else:
                        name += '_'
                        if name in modules:
                            return name
                    return v

                def rec(n):
                    if isinstance(n, ast.Attribute):
                        n.attr = renamer(n.attr)
                        rec(n.value)
                    elif isinstance(n, ast.Name):
                        n.id = renamer(n.id)
                rec(node.func.value)

        return node


##
class NormalizeAttributes(Transformation):
    '''
    Turns built in attributes into tuple subscript.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("a.real")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeAttributes, node)
    >>> print pm.dump(backend.Python, node)
    a[0]
    '''

    def visit_Attribute(self, node):
        if node.attr in attributes:
            out = ast.Subscript(
                    node.value,
                    ast.Index(ast.Num(attributes[node.attr][1].val)),
                    node.ctx)
            metadata.add(out, metadata.Attribute())
            return out
        else:
            return node


##
class NormalizeIdentifiers(Transformation):
    '''
    Prevents naming conflict with c++ keywords by appending extra '_'
    to conflicting names.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def namespace(union):pass")
    >>> pm = passmanager.PassManager("test")
    >>> d = pm.apply(NormalizeIdentifiers, node)
    >>> print pm.dump(backend.Python, node)
    def namespace_(union_):
        pass
    '''

    def __init__(self):
        self.renamings = dict()
        Transformation.__init__(self, Identifiers)

    def rename(self, name):
        if name not in self.renamings:
            new_name = name
            while new_name in self.identifiers:
                new_name += "_"
            self.renamings[name] = new_name
        return self.renamings[name]

    def run(self, node, ctx):
        super(NormalizeIdentifiers, self).run(node, ctx)
        return self.renamings

    def visit_Name(self, node):
        if node.id in cxx_keywords:
            node.id = self.rename(node.id)
        return node

    def visit_FunctionDef(self, node):
        if node.name in cxx_keywords:
            node.name = self.rename(node.name)
        self.visit(node.args)
        [self.visit(n) for n in node.body]
        return node

    def visit_alias(self, node):
        if node.name in cxx_keywords:
            node.name = self.rename(node.name)
        if node.asname:
            if node.asname in cxx_keywords:
                node.asname = self.rename(node.asname)
        return node

    def visit_ImportFrom(self, node):
        self.generic_visit(node)
        if node.module and node.module in cxx_keywords:
            node.module = self.rename(node.module)
        return node

    def visit_Attribute(self, node):
        self.visit(node.value)
        if node.attr in cxx_keywords:
            node.attr += "_"  # cross fingers
        # Always true as long as we don't have custom classes.
        return node


##
class NormalizeException(Transformation):
    '''
    Transform else statement in try except block in nested try except.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("try:print 't'\\nexcept: print 'x'\\nelse: print 'e'")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeException, node)
    >>> print pm.dump(backend.Python, node)
    try:
        print 't'
        try:
            print 'e'
        except:
            pass
    except:
        print 'x'
    '''
    def visit_TryExcept(self, node):
        if node.orelse:
            node.body.append(
                    ast.TryExcept(
                        node.orelse,
                        [ast.ExceptHandler(None, None, [ast.Pass()])],
                        []
                        )
                    )
            node.orelse = []
        return node

    def visit_TryFinally(self, node):
        node.body.extend(node.finalbody)
        node.finalbody.append(ast.Raise(None, None, None))
        return ast.TryExcept(
                node.body,
                [ast.ExceptHandler(None, None, node.finalbody)],
                [])


##
class UnshadowParameters(Transformation):
    '''
    Prevents parameter shadowing by creating new variable.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(a): a=None")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(UnshadowParameters, node)
    >>> print pm.dump(backend.Python, node)
    def foo(a):
        a_ = a
        a_ = None
    '''

    def __init__(self):
        Transformation.__init__(self, Identifiers)

    def visit_FunctionDef(self, node):
        self.argsid = {arg.id for arg in node.args.args}
        self.renaming = {}
        [self.visit(n) for n in node.body]
        # do it twice to make sure all renaming are done
        [self.visit(n) for n in node.body]
        for k, v in self.renaming.iteritems():
            node.body.insert(
                    0,
                    ast.Assign(
                        [ast.Name(v, ast.Store())],
                        ast.Name(k, ast.Load())
                        )
                    )
        return node

    def update(self, node):
        if isinstance(node, ast.Name) and node.id in self.argsid:
            if node.id not in self.renaming:
                new_name = node.id
                while new_name in self.identifiers:
                    new_name = new_name + "_"
                self.renaming[node.id] = new_name

    def visit_Assign(self, node):
        map(self.update, node.targets)
        try:
            self.generic_visit(node)
        except AttributeError:
            pass
        return node

    def visit_AugAssign(self, node):
        self.update(node.target)
        return self.generic_visit(node)

    def visit_Name(self, node):
        if node.id in self.renaming:
            node.id = self.renaming[node.id]
        return node


##
class ExpandImports(Transformation):
    '''
    Expands all imports into full paths.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("from math import cos ; cos(2)")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ExpandImports, node)
    >>> print pm.dump(backend.Python, node)
    import math as pythonic::math
    math.cos(2)
    '''

    def __init__(self):
        Transformation.__init__(self)
        self.imports = set()
        self.symbols = dict()

    def visit_Module(self, node):
        node.body = [k for k in (self.visit(n) for n in node.body) if k]
        imports = [ast.Import([ast.alias(i, namespace + "::" + i)])
                for i in self.imports]
        node.body = imports + node.body
        ast.fix_missing_locations(node)
        return node

    def visit_Import(self, node):
        for alias in node.names:
            self.imports.add(alias.name)
            self.symbols[alias.asname or alias.name] = (alias.name,)
        return None

    def visit_ImportFrom(self, node):
        self.imports.add(node.module)
        for alias in node.names:
            self.symbols[alias.asname or alias.name] = (
                    node.module,
                    alias.name,
                    )
        return None

    def visit_FunctionDef(self, node):
        self.symbols.pop(node.name, None)
        gsymbols = self.symbols.copy()
        [self.symbols.pop(arg.id, None) for arg in node.args.args]
        node.body = [k for k in (self.visit(n) for n in node.body) if k]
        self.symbols = gsymbols
        return node

    def visit_Assign(self, node):
        new_node = self.generic_visit(node)
        [self.symbols.pop(t.id, None)
                for t in new_node.targets if isinstance(t, ast.Name)]
        return new_node

    def visit_Name(self, node):
        if node.id in self.symbols:
            new_node = reduce(
                    lambda v, o: ast.Attribute(v, o, ast.Load()),
                    self.symbols[node.id][1:],
                    ast.Name(self.symbols[node.id][0], ast.Load())
                    )
            new_node.ctx = node.ctx
            ast.copy_location(new_node, node)
            return new_node
        return node


##
class ExpandImportAll(Transformation):
    '''
    Expands all import when '*' detected

    >>> import ast, passmanager, backend
    >>> node = ast.parse("from math import *")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ExpandImportAll, node)
    >>> print pm.dump(backend.Python, node)
    from math import asinh, atan2, fmod, atan, isnan, factorial, pow, \
copysign, cos, cosh, ldexp, hypot, isinf, floor, sinh, acosh, tan, ceil, exp, \
trunc, asin, expm1, e, log, fabs, tanh, log10, atanh, radians, sqrt, frexp, \
lgamma, erf, erfc, modf, degrees, acos, pi, log1p, sin, gamma
    '''

    def visit_ImportFrom(self, node):
        for alias in node.names:
            if alias.name == '*':
                node.names.pop()
                node.names.extend(ast.alias(fname, None)
                        for fname in modules[node.module])
        return node


class ExpandBuiltins(Transformation):
    '''
    Expands all builtins into full paths.
    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(): return list()")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ExpandBuiltins, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        return __builtin__.list()
    '''

    def __init__(self):
        Transformation.__init__(self, Locals, Globals)

    def visit_Name(self, node):
        s = node.id
        if (isinstance(node.ctx, ast.Load)
                and s not in self.locals[node]
                and s not in self.globals
                and s in modules['__builtin__']):
            return ast.Attribute(
                    ast.Name('__builtin__', ast.Load()),
                    s,
                    node.ctx)
        else:
            return node


class FalsePolymorphism(Transformation):
    """
    Rename variable when possible to avoid false polymorphism.
    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(): a = 12; a = 'babar'")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(FalsePolymorphism, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        a = 12
        a_ = 'babar'
    """
    def __init__(self):
        super(FalsePolymorphism, self).__init__(UsedDefChain, UseOMP)

    def visit_FunctionDef(self, node):
        #function using openmp are ignored
        if not self.use_omp:
            self.identifiers = self.passmanager.gather(Identifiers, node,
                    self.ctx)
            for name, udgraph in self.used_def_chain.iteritems():
                group_variable = list()
                while udgraph:
                    e = udgraph.nodes_iter().next()
                    to_change = set()
                    to_analyse_pred = set([e])
                    to_analyse_succ = set()
                    while to_analyse_pred or to_analyse_succ:
                        if to_analyse_pred:
                            n = to_analyse_pred.pop()
                            to_change.add(n)
                            to_analyse_succ.update(udgraph.successors(n))
                            to_analyse_succ -= to_change
                        else:
                            n = to_analyse_succ.pop()
                            if (udgraph.node[n]['action'] == 'U' or
                                    udgraph.node[n]['action'] == 'UD'):
                                to_change.add(n)
                                to_analyse_succ.update(udgraph.successors(n))
                                to_analyse_succ -= to_change
                        if (udgraph.node[n]['action'] == 'U' or
                                udgraph.node[n]['action'] == 'UD'):
                            to_analyse_pred.update(udgraph.predecessors(n))
                            to_analyse_pred -= to_change
                    nodes_to_change = [udgraph.node[k]['name']
                                            for k in to_change]
                    group_variable.append(nodes_to_change)
                    udgraph.remove_nodes_from(to_change)
                if len(group_variable) > 1:
                    self.identifiers.remove(name)
                    for group in group_variable:
                        while name in self.identifiers:
                            name += "_"
                        for var in group:
                            var.id = name
                        self.identifiers.add(name)
        return node


class NormalizeCompare(Transformation):
    '''
    Turns multiple compare into a function with proper temporaries.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(a): return 0 < a + 1 < 3")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeCompare, node)
    >>> print pm.dump(backend.Python, node)
    def foo(a):
        return foo_compare0(0, (a + 1), 3)
    def foo_compare0($0, $1, $2):
        return ($0 < $1 < $2)
    '''

    def visit_Module(self, node):
        self.compare_functions = list()
        self.generic_visit(node)
        node.body.extend(self.compare_functions)
        return node

    def visit_FunctionDef(self, node):
        self.prefix = node.name
        self.generic_visit(node)
        return node

    def visit_Compare(self, node):
        node = self.generic_visit(node)
        if len(node.ops) > 1:
            forged_name = "{0}_compare{1}".format(
                    self.prefix,
                    len(self.compare_functions)
                    )
            binded_args = [node.left] + node.comparators
            args = ast.arguments([ast.Name('${}'.format(i), ast.Param())
                for i in range(1 + len(node.ops))],
                None, None, [])
            node.left = ast.Name('$0', ast.Load())
            node.comparators = [ast.Name('${}'.format(i), ast.Load())
                    for i in range(1, 1 + len(node.ops))]
            forged_fdef = ast.FunctionDef(
                    forged_name,
                    args,
                    [ast.Return(node)],
                    [])
            self.compare_functions.append(forged_fdef)
            return ast.Call(ast.Name(forged_name, ast.Load()),
                    binded_args, [], None, None)
        else:
            return node

""" Aliases gather aliasing informations. """

from pythran.analyses.global_declarations import GlobalDeclarations
from pythran.intrinsic import Intrinsic, Class, NewMem
from pythran.passmanager import ModuleAnalysis
from pythran.syntax import PythranSyntaxError
from pythran.tables import functions, methods, MODULES
import pythran.metadata as md

from itertools import product

import ast

IntrinsicAliases = dict()


class ContainerOf(object):
    def __init__(self, index, containee):
        self.index = index
        self.containee = containee


def save_intrinsic_alias(module):
    """ Recursively save default aliases for pythonic functions. """
    for v in module.values():
        if isinstance(v, dict):  # Submodules case
            save_intrinsic_alias(v)
        else:
            IntrinsicAliases[v] = {v}
            if isinstance(v, Class):
                save_intrinsic_alias(v.fields)

for module in MODULES.values():
    save_intrinsic_alias(module)


class CopyOnWriteAliasesMap(object):

    def __init__(self, *args, **kwargs):
        self.src = kwargs.get('src', None)
        if self.src is None:
            self.data = dict(*args)
        else:
            assert not args, "cannot use a src and positional arguments"
            self.data = self.src

    def _copy_on_write(self):
        if self.src is not None:
            # need to do a copy
            assert self.data is self.src
            self.data = self.src.copy()
            self.src = None

    def __setitem__(self, k, v):
        self._copy_on_write()
        return self.data.__setitem__(k, v)

    def update(self, *values):
        self._copy_on_write()
        return self.data.update(*values)

    def copy(self):
        return CopyOnWriteAliasesMap(src=self.data)

    def __iter__(self):
        return self.data.__iter__()

    def __getitem__(self, k):
        return self.data.__getitem__(k)

    def __getattr__(self, name):
        return getattr(self.data, name)


class Aliases(ModuleAnalysis):
    """Gather aliasing informations across nodes."""

    RetId = '@'

    class Info(object):
        def __init__(self, state, aliases):
            self.state = state
            self.aliases = aliases

    def __init__(self):
        self.result = dict()
        self.aliases = None
        super(Aliases, self).__init__(GlobalDeclarations)

    def expand_unknown(self, node):
        # should include built-ins too?
        unkowns = {NewMem()}.union(self.global_declarations.values())
        return unkowns.union(node.args)

    @staticmethod
    def access_path(node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return w.get(n.id, n.id)
            elif isinstance(n, ast.Attribute):
                return rec(w, n.value)[n.attr]
            elif isinstance(n, ast.FunctionDef):
                return node.name
            else:
                return node
        return rec(MODULES, node)

    # aliasing created by expressions
    def add(self, node, values=None):
        if not values:  # no given target for the alias
            if isinstance(node, Intrinsic):
                values = {node}  # an Intrinsic always aliases to itself
            else:
                values = set()  # otherwise aliases to nothing
        assert isinstance(values, set)
        self.result[node] = Aliases.Info(self.aliases.copy(), values)
        return values

    def visit_BoolOp(self, node):
        return self.add(node, set.union(*map(self.visit, node.values)))

    def visit_UnaryOp(self, node):
        self.generic_visit(node)
        return self.add(node)

    visit_BinOp = visit_UnaryOp
    visit_Compare = visit_UnaryOp

    def visit_IfExp(self, node):
        self.visit(node.test)
        rec = map(self.visit, [node.body, node.orelse])
        return self.add(node, set.union(*rec))

    def visit_Dict(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Set(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Return(self, node):
        if not node.value:
            return
        self.aliases.setdefault(Aliases.RetId, set()).update(
            self.visit(node.value))

    def call_return_alias(self, node):

        def interprocedural_aliases(func, args):
            arg_aliases = [self.result[arg].aliases
                           for arg in args]
            return_aliases = set()
            for args_combination in product(*arg_aliases):
                return_aliases.update(
                    func.return_alias(args_combination))
            return set(map(expand_subscript, return_aliases))

        def expand_subscript(node):
            if isinstance(node, ast.Subscript):
                if isinstance(node.value, ContainerOf):
                    return node.value.containee
            return node

        def full_args(func, call):
            args = call.args
            if isinstance(func, ast.FunctionDef):
                extra = len(func.args.args) - len(args)
                args = args + func.args.defaults[extra:]
            return args

        func = node.func
        aliases = set()

        if node.keywords:
            # too soon, we don't support keywords in interprocedural_aliases
            pass
        elif isinstance(func, ast.Attribute):
            _, signature = methods.get(func.attr,
                                       functions.get(func.attr,
                                                     [(None, None)])[0])
            if signature:
                args = full_args(signature, node)
                aliases = interprocedural_aliases(signature, args)

        elif isinstance(func, ast.Name):
            func_aliases = self.result[func].aliases
            for func_alias in func_aliases:
                if hasattr(func_alias, 'return_alias'):
                    args = full_args(func_alias, node)
                    aliases.update(interprocedural_aliases(func_alias, args))
                else:
                    pass  # better thing to do ?
        [self.add(a) for a in aliases if a not in self.result]
        return aliases or self.expand_unknown(node)

    def visit_Call(self, node):
        self.generic_visit(node)
        f = node.func
        # special handler for bind functions
        if isinstance(f, ast.Attribute) and f.attr == "partial":
            return self.add(node, {node})
        else:
            return_alias = self.call_return_alias(node)
            # expand collected aliases
            all_aliases = set()
            for value in return_alias:
                if isinstance(value, NewMem):
                    all_aliases.add(value)
                elif value in self.result:
                    all_aliases.update(self.result[value].aliases)
                else:
                    try:
                        ap = Aliases.access_path(value)
                        all_aliases.update(self.aliases.get(ap, ()))
                    except NotImplementedError:
                        # should we do something better here?
                        all_aliases.add(value)
            return self.add(node, all_aliases)

    visit_Num = visit_UnaryOp
    visit_Str = visit_UnaryOp

    def visit_Attribute(self, node):
        return self.add(node, {Aliases.access_path(node)})

    def visit_Subscript(self, node):
        if isinstance(node.slice, ast.Index):
            aliases = set()
            self.visit(node.slice)
            value_aliases = self.visit(node.value)
            for alias in value_aliases:
                if isinstance(alias, ContainerOf):
                    if isinstance(node.slice.value, ast.Slice):
                        continue
                    if isinstance(node.slice.value, ast.Num):
                        if node.slice.value.n != alias.index:
                            continue
                    # FIXME: what if the index is a slice variable...
                    aliases.add(alias.containee)
                elif isinstance(getattr(alias, 'ctx', None), ast.Param):
                    aliases.add(ast.Subscript(alias, node.slice, node.ctx))
        else:
            # could be enhanced through better handling of containers
            aliases = None
            self.generic_visit(node)
        return self.add(node, aliases)

    def visit_Name(self, node):
        if node.id not in self.aliases:
            err = ("identifier {0} unknown, either because "
                   "it is an unsupported intrinsic, "
                   "the input code is faulty, "
                   "or... pythran is buggy.")
            raise PythranSyntaxError(err.format(node.id), node)
        return self.add(node, self.aliases[node.id].copy())

    def visit_List(self, node):
        if node.elts:
            elts_aliases = set()
            for i, elt in enumerate(node.elts):
                elt_aliases = self.visit(elt)
                elts_aliases.update(ContainerOf(i, alias)
                                    for alias in elt_aliases)
        else:
            elts_aliases = None
        return self.add(node, elts_aliases)

    visit_Tuple = visit_List

    def visit_comprehension(self, node):
        self.aliases[node.target.id] = {node.target}
        self.generic_visit(node)

    def visit_ListComp(self, node):
        map(self.visit_comprehension, node.generators)
        self.visit(node.elt)
        return self.add(node)

    visit_SetComp = visit_ListComp

    visit_GeneratorExp = visit_ListComp

    def visit_DictComp(self, node):
        map(self.visit_comprehension, node.generators)
        self.visit(node.key)
        self.visit(node.value)
        return self.add(node)

    # aliasing created by statements

    def visit_FunctionDef(self, node):
        """
        Initialise aliasing default value before visiting.

        Add aliasing values for :
            - Pythonic
            - globals declarations
            - current function arguments
        """
        self.aliases = CopyOnWriteAliasesMap(IntrinsicAliases.items())

        self.aliases.update((f.name, {f})
                            for f in self.global_declarations.values())

        self.aliases.update((arg.id, {arg})
                            for arg in node.args.args)

        self.generic_visit(node)
        if Aliases.RetId in self.aliases:
            # multiple return alias not supported... yet!
            if len(self.aliases[Aliases.RetId]) == 1:
                ret_alias = next(iter(self.aliases[Aliases.RetId]))

                # parametrize the expression
                def parametrize(exp):
                    if isinstance(exp, ast.Index):
                        return lambda _: {exp}
                    elif isinstance(exp, ast.Name):
                        try:
                            w = node.args.args.index(exp)

                            def return_alias(args):
                                if w < len(args):
                                    return {args[w]}
                                else:
                                    return {node.args.defaults[w - len(args)]}
                            return return_alias
                        except ValueError:
                            return lambda _: {NewMem}
                    elif isinstance(exp, ast.Subscript):
                        values = parametrize(exp.value)
                        slices = parametrize(exp.slice)
                        return lambda args: {
                            ast.Subscript(value, slice, ast.Load())
                            for value in values(args)
                            for slice in slices(args)}
                    else:
                        return lambda _: {NewMem}

                node.return_alias = parametrize(ret_alias)

    def visit_Assign(self, node):
        md.visit(self, node)
        value_aliases = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.aliases[t.id] = value_aliases or {t}
                for alias in list(value_aliases):
                    if isinstance(alias, ast.Name):
                        self.aliases[alias.id].add(t)
                self.add(t, self.aliases[t.id].copy())
            else:
                self.visit(t)

    def visit_For(self, node):
        # FIXME: node.target.id could alias to the content of node.iter
        self.aliases[node.target.id] = {node.target}
        # Error may come from false branch evaluation so we have to try again
        try:
            self.generic_visit(node)
        except PythranSyntaxError:
            self.generic_visit(node)

    def visit_While(self, node):
        # Error may come from false branch evaluation so we have to try again
        try:
            self.generic_visit(node)
        except PythranSyntaxError:
            self.generic_visit(node)

    def visit_If(self, node):
        md.visit(self, node)
        self.visit(node.test)
        false_aliases = {k: v.copy() for k, v in self.aliases.items()}
        try:  # first try the true branch
            map(self.visit, node.body)
            true_aliases, self.aliases = self.aliases, false_aliases
        except PythranSyntaxError:  # it failed, try the false branch
            map(self.visit, node.orelse)
            raise  # but still throw the exception, maybe we are in a For
        try:  # then try the false branch
            map(self.visit, node.orelse)
        except PythranSyntaxError:  # it failed
            # we still get some info from the true branch, validate them
            self.aliases = true_aliases
            raise  # and let other visit_ handle the issue
        for k, v in true_aliases.items():
            if k in self.aliases:
                self.aliases[k].update(v)
            else:
                assert isinstance(v, set)
                self.aliases[k] = v

    def visit_ExceptHandler(self, node):
        if node.name:
            self.aliases[node.name.id] = {node.name}
        self.generic_visit(node)


class StrictAliases(Aliases):
    """
    Gather aliasing informations across nodes,
    without adding unsure aliases.
    """
    def expand_unknown(self, node):
        return {}

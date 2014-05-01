"""
Aliases gather aliasing informations
"""
import ast
from global_declarations import GlobalDeclarations
from pythran.intrinsic import Intrinsic
import pythran.metadata as md
from pythran.passmanager import ModuleAnalysis
from pythran.syntax import PythranSyntaxError
from pythran.tables import functions, methods, modules
from pythran.syntax import PythranSyntaxError


class Aliases(ModuleAnalysis):
    """Gather aliasing informations across nodes."""
    class Info(object):
        def __init__(self, state, aliases):
            self.state = state
            self.aliases = aliases

    def __init__(self):
        self.result = dict()
        self.aliases = dict()
        super(Aliases, self).__init__(GlobalDeclarations)

    def expand_unknown(self, node):
        # should include built-ins too?
        unkowns = {None}.union(self.global_declarations.values())
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
        return rec(modules, node)

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

    def call_return_alias(self, node):
        func = node.func
        aliases = set()
        if isinstance(func, ast.Attribute):
            _, signature = methods.get(func.attr,
                                       functions.get(func.attr,
                                                     [(None, None)])[0])
            if signature and signature.return_alias:
                aliases = signature.return_alias(node)
        elif isinstance(func, ast.Name):
            func_aliases = self.result[func].aliases
            for func_alias in func_aliases:
                signature = None
                if isinstance(func_alias, ast.FunctionDef):
                    _, signature = functions.get(
                        func_alias.name,
                        [(None, None)])[0]
                    if signature and signature.return_alias:
                        aliases.update(signature.return_alias(node))
                elif hasattr(func_alias, 'return_alias'):
                    aliases.update(func_alias.return_alias(node))
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
                if value is None:
                    all_aliases.add(None)
                elif value in self.result:
                    all_aliases.update(self.result[value].aliases)
                else:
                    try:
                        ap = Aliases.access_path(value)
                        all_aliases.update(self.aliases.get(ap, ()))
                    except NotImplementedError:
                        # should we do something better here?
                        all_aliases.add(value)
                        pass
            return_alias = all_aliases
            return self.add(node, return_alias)

    visit_Num = visit_UnaryOp
    visit_Str = visit_UnaryOp

    def visit_Attribute(self, node):
        return self.add(node, {Aliases.access_path(node)})

    def visit_Subscript(self, node):
        self.generic_visit(node)
        # could be enhanced through better handling of containers
        return self.add(node)

    def visit_Name(self, node):
        if node.id not in self.aliases:
            err = ("identifier {0} unknown, either because "
                   "it is an unsupported intrinsic, "
                   "the input code is faulty, "
                   "or... pythran is buggy.")
            raise PythranSyntaxError(err.format(node.id), node)
        return self.add(node, self.aliases[node.id].copy())

    def visit_List(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

    def visit_Tuple(self, node):
        self.generic_visit(node)
        return self.add(node)  # not very accurate

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
        self.aliases = dict()
        for module in modules:
            self.aliases.update((v, {v})
                                for k, v in modules[module].iteritems())
        self.aliases.update((f.name, {f})
                            for f in self.global_declarations.itervalues())
        self.aliases.update((arg.id, {arg})
                            for arg in node.args.args)
        self.generic_visit(node)

    def visit_Assign(self, node):
        md.visit(self, node)
        value_aliases = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.aliases[t.id] = value_aliases or {t}
                for alias in list(value_aliases):
                    if isinstance(alias, ast.Name):
                        self.aliases[alias.id].add(t)
            else:
                self.visit(t)

    def visit_For(self, node):
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
        false_aliases = {k: v.copy() for k, v in self.aliases.iteritems()}
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
        for k, v in true_aliases.iteritems():
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

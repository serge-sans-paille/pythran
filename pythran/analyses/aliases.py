""" Aliases gather aliasing informations. """

from pythran.analyses.global_declarations import GlobalDeclarations
from pythran.intrinsic import Intrinsic, Class, UnboundValue
from pythran.passmanager import ModuleAnalysis
from pythran.syntax import PythranSyntaxError
from pythran.tables import functions, methods, MODULES
from pythran.unparse import Unparser
import pythran.metadata as md

import ast
from itertools import product
import sys

if sys.version_info[0] < 3:
    import cStringIO
else:
    from io import StringIO as cStringIO


IntrinsicAliases = dict()


class ContainerOf(object):
    '''
    Represents a container of something

    We just know that if indexed by the integer value `index',
    we get `containee'
    '''
    UnknownIndex = float('nan')

    def __init__(self, containee, index=UnknownIndex):
        self.index = index
        self.containee = containee


def save_intrinsic_alias(module):
    """ Recursively save default aliases for pythonic functions. """
    for v in module.values():
        if isinstance(v, dict):  # Submodules case
            save_intrinsic_alias(v)
        else:
            IntrinsicAliases[v] = frozenset((v,))
            if isinstance(v, Class):
                save_intrinsic_alias(v.fields)

for module in MODULES.values():
    save_intrinsic_alias(module)


class Aliases(ModuleAnalysis):
    '''
    Gather aliasing informations across nodes

    As a result, each node from the module is associated to a set of node or
    Intrinsic to which it *may* alias to.
    '''

    RetId = '@'

    def __init__(self):
        self.result = dict()
        self.aliases = None
        super(Aliases, self).__init__(GlobalDeclarations)

    @staticmethod
    def dump(result, filter=None):
        def pp(n):
            output = cStringIO.StringIO()
            Unparser(n, output)
            return output.getvalue().strip()

        if isinstance(result, dict):
            for k, v in result.items():
                if (filter is None) or isinstance(k, filter):
                    print('{} => {}'.format(pp(k), sorted(map(pp, v))))
        elif isinstance(result, (frozenset, set)):
            print(sorted(map(pp, result)))

    def expand_unknown(self, node):
        # should include built-ins too?
        unkowns = {UnboundValue}.union(self.global_declarations.values())
        return unkowns.union(node.args)

    def get_unbound_value_set(self):
        return {UnboundValue}

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
    def add(self, node, values=set()):
        if not values:  # no given target for the alias
            if isinstance(node, Intrinsic):
                values = {node}  # an Intrinsic always aliases to itself
            else:
                values = self.get_unbound_value_set()
        assert isinstance(values, (frozenset, set))
        self.result[node] = values
        return values

    def visit_BoolOp(self, node):
        '''
        Resulting node may alias to either operands:

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return a or b')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.BoolOp)
        (a or b) => ['a', 'b']

        Note that a literal does not create any alias

        >>> module = ast.parse('def foo(a, b): return a or 0')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.BoolOp)
        (a or 0) => ['<unbound-value>', 'a']
        '''
        return self.add(node, set.union(*map(self.visit, node.values)))

    def visit_UnaryOp(self, node):
        '''
        Resulting node does not alias to anything

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a): return -a')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.UnaryOp)
        (- a) => ['<unbound-value>']
        '''
        self.generic_visit(node)
        return self.add(node)

    visit_BinOp = visit_UnaryOp
    visit_Compare = visit_UnaryOp

    def visit_IfExp(self, node):
        '''
        Resulting node alias to either branch

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b, c): return a if c else b')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.IfExp)
        (a if c else b) => ['a', 'b']
        '''
        self.visit(node.test)
        rec = map(self.visit, [node.body, node.orelse])
        return self.add(node, set.union(*rec))

    def visit_Dict(self, node):
        '''
        A dict is abstracted as an unordered container of its values

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return {0: a, 1: b}')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Dict)
        {0: a, 1: b} => ['|a|', '|b|']

        where the |id| notation means something that may contain ``id``.
        '''
        if node.keys:
            elts_aliases = set()
            for key, val in zip(node.keys, node.values):
                self.visit(key)  # res ignored, just to fill self.aliases
                elt_aliases = self.visit(val)
                elts_aliases.update(map(ContainerOf, elt_aliases))
        else:
            elts_aliases = None
        return self.add(node, elts_aliases)

    def visit_Set(self, node):
        '''
        A set is abstracted as an unordered container of its elements

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return {a, b}')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Set)
        {a, b} => ['|a|', '|b|']

        where the |id| notation means something that may contain ``id``.
        '''
        if node.elts:
            elts_aliases = set()
            for elt in node.elts:
                elt_aliases = self.visit(elt)
                elts_aliases.update(map(ContainerOf, elt_aliases))
        else:
            elts_aliases = None
        return self.add(node, elts_aliases)

    def visit_Return(self, node):
        '''
        A side effect of computing aliases on a Return is that it updates the
        ``return_alias`` field of current function

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return a')
        >>> result = pm.gather(Aliases, module)
        >>> module.body[0].return_alias # doctest: +ELLIPSIS
        <function merge_return_aliases at...>

        This field is a function that takes as many nodes as the function
        argument count as input and returns an expression based on
        these arguments if the function happens to create aliasing
        between its input and output. In our case:

        >>> f = module.body[0].return_alias
        >>> Aliases.dump(f([ast.Name('A', ast.Load()), ast.Num(1)]))
        ['A']

        This also works if the relationship between input and output
        is more complex:

        >>> module = ast.parse('def foo(a, b): return a or b[0]')
        >>> result = pm.gather(Aliases, module)
        >>> f = module.body[0].return_alias
        >>> List = ast.List([ast.Name('L0', ast.Load())], ast.Load())
        >>> Aliases.dump(f([ast.Name('B', ast.Load()), List]))
        ['B', '[L0][0]']

        Which actually means that when called with two arguments ``B`` and
        the single-element list ``[L[0]]``, ``foo`` may returns either the
        first argument, or the first element of the second argument.
        '''
        if not node.value:
            return
        ret_aliases = self.visit(node.value)
        if Aliases.RetId in self.aliases:
            ret_aliases = ret_aliases.union(self.aliases[Aliases.RetId])
        self.aliases[Aliases.RetId] = ret_aliases

    def call_return_alias(self, node):

        def interprocedural_aliases(func, args):
            arg_aliases = [self.result[arg] or {arg} for arg in args]
            return_aliases = set()
            for args_combination in product(*arg_aliases):
                return_aliases.update(
                    func.return_alias(args_combination))
            return {expand_subscript(ra) for ra in return_aliases}

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
            func_aliases = self.result[func]
            for func_alias in func_aliases:
                if hasattr(func_alias, 'return_alias'):
                    args = full_args(func_alias, node)
                    aliases.update(interprocedural_aliases(func_alias, args))
                else:
                    pass  # better thing to do ?
        [self.add(a) for a in aliases if a not in self.result]
        return aliases or self.expand_unknown(node)

    def visit_Call(self, node):
        '''
        Resulting node alias to the return_alias of called function,
        if the function is already known by Pythran (i.e. it's an Intrinsic)
        or if Pythran already computed it's ``return_alias`` behavior.

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> fun = """
        ... def f(a): return a
        ... def foo(b): c = f(b)"""
        >>> module = ast.parse(fun)

        The ``f`` function create aliasing between
        the returned value and its first argument.

        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Call)
        f(b) => ['b']

        This also works with intrinsics, e.g ``dict.setdefault`` which
        may create alias between its third argument and the return value.

        >>> fun = 'def foo(a, d): __builtin__.dict.setdefault(d, 0, a)'
        >>> module = ast.parse(fun)
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Call)
        __builtin__.dict.setdefault(d, 0, a) => ['<unbound-value>', 'a']

        Note that complex cases can arise, when one of the formal parameter
        is already known to alias to various values:

        >>> fun = """
        ... def f(a, b): return a and b
        ... def foo(A, B, C, D): return f(A or B, C or D)"""
        >>> module = ast.parse(fun)
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Call)
        f((A or B), (C or D)) => ['A', 'B', 'C', 'D']
        '''
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
                # no translation
                if isinstance(value, (ContainerOf, ast.FunctionDef,
                                      Intrinsic)):
                    all_aliases.add(value)
                elif value in self.result:
                    all_aliases.update(self.result[value])
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
        '''
        Resulting node alias stores the subscript relationship if we don't know
        anything about the subscripted node.

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a): return a[0]')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Subscript)
        a[0] => ['a[0]']

        If we know something about the container, e.g. in case of a list, we
        can use this information to get more accurate informations:

        >>> module = ast.parse('def foo(a, b, c): return [a, b][c]')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Subscript)
        [a, b][c] => ['a', 'b']

        Moreover, in case of a tuple indexed by a constant value, we can
        further refine the aliasing information:

        >>> fun = """
        ... def f(a, b): return a, b
        ... def foo(a, b): return f(a, b)[0]"""
        >>> module = ast.parse(fun)
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Subscript)
        f(a, b)[0] => ['a']

        Nothing is done for slices, even if the indices are known :-/

        >>> module = ast.parse('def foo(a, b, c): return [a, b, c][1:]')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Subscript)
        [a, b, c][1:] => ['<unbound-value>']
        '''
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

    def visit_OMPDirective(self, node):
        '''
        omp directive may introduce new variables, just register them
        '''
        for dep in node.deps:
            self.add(dep)

    def visit_Name(self, node):
        if node.id not in self.aliases:
            err = ("identifier {0} unknown, either because "
                   "it is an unsupported intrinsic, "
                   "the input code is faulty, "
                   "or... pythran is buggy.")
            raise PythranSyntaxError(err.format(node.id), node)
        return self.add(node, self.aliases[node.id])

    def visit_Tuple(self, node):
        '''
        A tuple is abstracted as an ordered container of its values

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return a, b')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Tuple)
        (a, b) => ['|[0]=a|', '|[1]=b|']

        where the |[i]=id| notation means something that
        may contain ``id`` at index ``i``.
        '''
        if node.elts:
            elts_aliases = set()
            for i, elt in enumerate(node.elts):
                elt_aliases = self.visit(elt)
                elts_aliases.update(ContainerOf(alias, i)
                                    for alias in elt_aliases)
        else:
            elts_aliases = None
        return self.add(node, elts_aliases)

    visit_List = visit_Set

    def visit_comprehension(self, node):
        self.aliases[node.target.id] = {node.target}
        self.generic_visit(node)

    def visit_ListComp(self, node):
        '''
        A comprehension is not abstracted in any way

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return [a for i in b]')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.ListComp)
        [a for i in b] => ['<unbound-value>']
        '''
        map(self.visit_comprehension, node.generators)
        self.visit(node.elt)
        return self.add(node)

    visit_SetComp = visit_ListComp

    visit_GeneratorExp = visit_ListComp

    def visit_DictComp(self, node):
        '''
        A comprehension is not abstracted in any way

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a, b): return {i: i for i in b}')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.DictComp)
        {i: i for i in b} => ['<unbound-value>']
        '''
        map(self.visit_comprehension, node.generators)
        self.visit(node.key)
        self.visit(node.value)
        return self.add(node)

    # aliasing created by statements

    def visit_FunctionDef(self, node):
        '''
        Initialise aliasing default value before visiting.

        Add aliasing values for :
            - Pythonic
            - globals declarations
            - current function arguments
        '''
        self.aliases = IntrinsicAliases.copy()

        self.aliases.update((f.name, {f})
                            for f in self.global_declarations.values())

        self.aliases.update((arg.id, {arg})
                            for arg in node.args.args)

        self.generic_visit(node)
        if Aliases.RetId in self.aliases:
            # parametrize the expression
            def parametrize(exp):
                # constant(?) or global -> no change
                if isinstance(exp, (ast.Index, Intrinsic, ast.FunctionDef)):
                    return lambda _: {exp}
                elif isinstance(exp, ContainerOf):
                    pcontainee = parametrize(exp.containee)
                    index = exp.index
                    return lambda args: {
                        ContainerOf(pc, index)
                        for pc in pcontainee(args)
                    }
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
                        return lambda _: self.get_unbound_value_set()
                elif isinstance(exp, ast.Subscript):
                    values = parametrize(exp.value)
                    slices = parametrize(exp.slice)
                    return lambda args: {
                        ast.Subscript(value, slice, ast.Load())
                        for value in values(args)
                        for slice in slices(args)}
                else:
                    return lambda _: self.get_unbound_value_set()

            # this is a little tricky: for each returned alias,
            # parametrize builds a function that, given a list of args,
            # returns the alias
            # then as we may have multiple returned alias, we compute the union
            # of these returned aliases
            return_aliases = [parametrize(ret_alias)
                              for ret_alias
                              in self.aliases[Aliases.RetId]]

            def merge_return_aliases(args):
                merged_return_aliases = set()
                for return_alias in return_aliases:
                    merged_return_aliases.update(return_alias(args))
                return merged_return_aliases

            node.return_alias = merge_return_aliases

    def visit_Assign(self, node):
        '''
        Assignment creates aliasing between lhs and rhs

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse('def foo(a): c = a ; d = e = c ; {c, d, e}')
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Set)
        {c, d, e} => ['|a|', '|a|', '|a|']

        Everyone points to the formal parameter 'a' \o/
        '''
        md.visit(self, node)
        value_aliases = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.aliases[t.id] = set(value_aliases) or {t}
                for alias in list(value_aliases):
                    if isinstance(alias, ast.Name):
                        a_id = alias.id
                        self.aliases[a_id] = self.aliases[a_id].union((t,))
                self.add(t, self.aliases[t.id])
            else:
                self.visit(t)

    def visit_For(self, node):
        '''
        For loop creates aliasing between the target
        and the content of the iterator

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> module = ast.parse("""
        ... def foo(a):
        ...     for i in a:
        ...         {i}""")
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Set)
        {i} => ['|i|']

        Not very useful, unless we know something about the iterated container

        >>> module = ast.parse("""
        ... def foo(a, b):
        ...     for i in [a, b]:
        ...         {i}""")
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Set)
        {i} => ['|a|', '|b|']
        '''

        iter_aliases = self.visit(node.iter)
        if all(isinstance(x, ContainerOf) for x in iter_aliases):
            target_aliases = set()
            for iter_alias in iter_aliases:
                target_aliases.add(iter_alias.containee)
        else:
            target_aliases = {node.target}

        self.add(node.target, target_aliases)
        self.aliases[node.target.id] = self.result[node.target]
        # Error may come from false branch evaluation so we have to try again
        try:
            self.generic_visit(node)
        except PythranSyntaxError:
            self.generic_visit(node)

    def visit_While(self, node):
        '''

        While statement evaluation is somehow equivalent to the evaluation of a
        sequence, except the fact that in some subtle cases, the first rounds
        of analyse fails because we do not follow the regular execution order

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> fun = """
        ... def foo(a):
        ...     while(a):
        ...         if a==1: print b
        ...         else: b=a"""
        >>> module = ast.parse(fun)
        >>> result = pm.gather(Aliases, module)
        '''
        # Error may come from false branch evaluation so we have to try again
        try:
            self.generic_visit(node)
        except PythranSyntaxError:
            self.generic_visit(node)
        self.generic_visit(node)

    def visit_If(self, node):
        '''
        After an if statement, the values from both branches are merged,
        potentially creating more aliasing:

        >>> from pythran import passmanager
        >>> pm = passmanager.PassManager('demo')
        >>> fun = """
        ... def foo(a, b):
        ...     if a: c=a
        ...     else: c=b
        ...     return {c}"""
        >>> module = ast.parse(fun)
        >>> result = pm.gather(Aliases, module)
        >>> Aliases.dump(result, filter=ast.Set)
        {c} => ['|a|', '|b|']
        '''

        md.visit(self, node)
        self.visit(node.test)
        false_aliases = self.aliases.copy()
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
                self.aliases[k] = self.aliases[k].union(v)
            else:
                assert isinstance(v, (frozenset, set))
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

    def get_unbound_value_set(self):
        return set()

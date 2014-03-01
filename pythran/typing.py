'''
This module performs the return type inference, according to symbolic types,
   It then reorders function declarations according to the return type deps.
    * type_all generates a node -> type binding
'''

import ast
from numpy import ndarray
import networkx as nx

from tables import pytype_to_ctype_table, operator_to_lambda
from tables import modules, methods, functions
from analysis import GlobalDeclarations, YieldPoints, LocalDeclarations
from analysis import OrderedGlobalDeclarations, ModuleAnalysis, StrictAliases
from analysis import LazynessAnalysis, DeclaredGlobals, Locals
from analysis import AssignTargets
from passes import Transformation
from syntax import PythranSyntaxError
from cxxtypes import *
from intrinsic import UserFunction, MethodIntr
import operator
from intrinsic import ConstantIntr
from config import cfg
from collections import defaultdict


# networkx backward compatibility
if not "has_path" in nx.__dict__:
    def has_path(G, source, target):
        try:
            nx.shortest_path(G, source, target)
        except nx.NetworkXNoPath:
            return False
        return True
    nx.has_path = has_path


##
def pytype_to_ctype(t):
    '''python -> c++ type binding'''
    if isinstance(t, list):
        return 'pythonic::types::list<{0}>'.format(pytype_to_ctype(t[0]))
    if isinstance(t, set):
        return 'pythonic::types::set<{0}>'.format(pytype_to_ctype(list(t)[0]))
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return 'pythonic::types::dict<{0},{1}>'.format(pytype_to_ctype(tkey),
                                                       pytype_to_ctype(tvalue))
    elif isinstance(t, tuple):
        return 'decltype(pythonic::types::make_tuple({0}))'.format(
            ", ".join('std::declval<{}>()'.format(
                pytype_to_ctype(_)) for _ in t)
            )
    elif isinstance(t, ndarray):
        return 'pythonic::types::ndarray<{0},{1}>'.format(
            pytype_to_ctype(t.flat[0]), t.ndim)
    elif t in pytype_to_ctype_table:
        return pytype_to_ctype_table[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


def pytype_to_deps(t):
    '''python -> c++ type binding'''
    if isinstance(t, list):
        return {'pythonic/types/list.hpp'}.union(pytype_to_deps(t[0]))
    if isinstance(t, set):
        return {'pythonic/types/set.hpp'}.union(pytype_to_deps(list(t)[0]))
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return {'pythonic/types/dict.hpp'}.union(pytype_to_deps(tkey),
                                                 pytype_to_deps(tvalue))
    elif isinstance(t, tuple):
        return {'pythonic/types/tuple.hpp'}.union(*map(pytype_to_deps, t))
    elif isinstance(t, ndarray):
        return {'pythonic/types/ndarray.hpp'}.union(pytype_to_deps(t[0]))
    elif t in pytype_to_ctype_table:
        return {'pythonic/types/{}.hpp'.format(t.__name__)}
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


def extract_constructed_types(t):
    if isinstance(t, list) or isinstance(t, ndarray):
        return [pytype_to_ctype(t)] + extract_constructed_types(t[0])
    elif isinstance(t, set):
        return [pytype_to_ctype(t)] + extract_constructed_types(list(t)[0])
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return ([pytype_to_ctype(t)]
                + extract_constructed_types(tkey)
                + extract_constructed_types(tvalue))
    elif isinstance(t, tuple):
        return ([pytype_to_ctype(t)]
                + sum(map(extract_constructed_types, t), []))
    elif t == long:
        return [pytype_to_ctype(t)]
    elif t == str:
        return [pytype_to_ctype(t)]
    else:
        return []


def disjoint_reduce(val1, val2):
    """
    Reduces two type of dependencies by combining them. If either set
    of dependencies can be "independent" (aka there exist a call graph
    that means it doesn't depend on any other variable/functions), then
    the resulting dependency can be independent too.
    """
    return val1[0] | val2[0], val1[1] or val2[1]


def combine_reduce(val1, val2):
    """
    Reduces two type of dependencies by combining them. If both set
    of dependencies can be "independent" (aka there exist a call graph
    that means it doesn't depend on any other variable/functions), then
    the resulting dependency can be independent too.
    """
    return val1[0] | val2[0], val1[1] and val2[1]


class TypeDependencies(ModuleAnalysis):
    """
    Similar to Aliases, for each node, gathers all the node that
    determine its type
    """

    def __init__(self, *deps):
        self.result = {}
        self.current_function = None
        #Combiners for interprocedural analysis: when a function is analyzed,
        # its effects on the dependencies of the arguments are stored there.
        self.combiners = {}
        self.in_cond = False
        #When updating the dependencies of a variable, is it a partial update,
        # or is the variable set to a completely new value?
        #If it's a partial update, the new dependencies will be the old ones
        # in addition to the new ones.
        self.partial_assign = False
        #During the first "regular" run, nothing is analyzed. That's because
        # we need to visit the functions in a particular order. So this va-
        # riable is then set to True and the functions visited in the correct
        # order (see the run() function)
        self.visiting_functions = False
        #Used only by the combine() function. When an external combiner calls
        # get_type() on the parameter object, will change this variable to add
        # the new dependency.
        self.nodes = []
        #Are we combining? The interprocedural analysis could lead to infinite
        # recursion, so this is a variable to stop that.
        self.combining = False
        #Each time a variable has its naming modified, it's stored in there.
        #It's used to know which arguments have been "changed" by the function
        # and need a combiner.
        self.modified_naming = set()
        #When in interprocedural dependency deduction, if the type of the
        # parameter depends on anything in the function, it should also
        # depend on the whole call of the function, as it will in the Types
        # analysis with the PTypes.
        #
        #self.current_call is used to store the current call in case there's
        # a combine, so as to be prepared for such a situation
        self.current_call = None
        super(TypeDependencies, self).__init__(GlobalDeclarations, Locals,
                                               DeclaredGlobals, StrictAliases,
                                               OrderedGlobalDeclarations,
                                               *deps)

    def visit_any_conditionnal(self, node):
        '''
        Set and restore the in_cond variable whenever a node
        the children of which may not be executed is visited
        '''
        in_cond = self.in_cond
        self.in_cond = True
        self.generic_visit(node)
        self.in_cond = in_cond

    def prepare(self, node, ctx):
        for mname, module in modules.iteritems():
            for fname, function in module.iteritems():
                if not isinstance(function, ConstantIntr):
                    self.combiners[function] = function

        super(TypeDependencies, self).prepare(node, ctx)

    def visit_FunctionDef(self, node):
        if not self.visiting_functions:
            return

        #print "Type dependencies - visiting " + node.name
        assert self.current_function is None
        self.current_function = node
        self.naming = dict()
        self.in_cond = False  # True when we are in a if, while or for
        #So the args point to something, and when looking up doesn't go back
        # to the global of the same name as the arg
        for arg in node.args.args:
            self.update_naming(arg.id, (set(), True))
        #Arguments aren't considered "modified" naming, especially since
        # the goal of the variable is too see which arguments were modified
        self.modified_naming = set()

        #add dependencies induced by default arguments
        if len(node.args.defaults) > 0:
            for p in range(len(node.args.args)):
                if len(node.args.defaults) - len(node.args.args) + p >= 0:
                    i = len(node.args.defaults) - len(node.args.args) + p
                    default = node.args.defaults[i]
                    self.add_function_deps(self.visit(default))

        self.generic_visit(node)
        arg_deps = UserFunction()

        for (p, arg) in enumerate(node.args.args):
            naming = self.get_naming(arg.id)

            def interprocedural_generator(p, naming):
                def interprocedural_combiner(s, n):
                    #default arguments mean a call doesn't always have all the
                    # arguments
                    if not (p < len(n.args)):
                        return
                    s.combine_(n.args[p], naming)
                return interprocedural_combiner

            if arg.id in self.modified_naming:
                arg_deps.add_combiner(interprocedural_generator(p, naming))

        self.combiners[node] = arg_deps
        self.current_function = None

    def add_function_deps(self, values):
        pass

    def is_global_variable(self, name):
        if name in self.declared_globals:
            if not Locals.is_local(self.locals, self.current_function, name):
                return True
        return False

    def update_naming(self, name, value):
        '''
        Update or renew the name <-> dependencies binding
        depending on the in_cond state
        @rtype : None
        '''
        if (self.in_cond or self.partial_assign) and name in self.naming:
            self.naming[name] = reduce(disjoint_reduce,
                                       [value, self.naming[name]])
        else:
            self.naming[name] = value

        if self.is_global_variable(name):
            self.naming[name][0].add(self.global_declarations[name])

        self.modified_naming.add(name)

    def visit_Assign(self, node):
        v = self.visit(node.value)
        targets = self.passmanager.gather(AssignTargets, node)
        for t in targets[0]:
            self.partial_assign = t not in targets[1]
            self.update_naming(t.id, v)
        self.partial_assign = False

        #If we have m[x] = 1, makes sure m depends on x
        if isinstance(node, ast.Assign):
            targets = node.targets
        else:
            assert isinstance(node, ast.AugAssign)
            targets = [node.target]

        for t in targets:
            #in a[...], gets ast.Name('a')
            target = list(self.passmanager.gather(AssignTargets, t)[0])
            assert(len(target) == 1)
            self.update_naming(target[0].id, self.visit(t))

    visit_AugAssign = visit_Assign

    def visit_For(self, node):
        self.update_naming(node.target.id, self.visit(node.iter))
        self.visit_any_conditionnal(node)

    def visit_BoolOp(self, node):
        values = [self.visit(value) for value in node.values]
        return reduce(disjoint_reduce, values)

    def visit_BinOp(self, node):
        return reduce(combine_reduce, map(self.visit, (node.left, node.right)))

    def visit_UnaryOp(self, node):
        return self.visit(node.operand)

    def visit_Lambda(self, node):
        assert False

    def visit_IfExp(self, node):
        return reduce(disjoint_reduce, map(self.visit, (node.body,
                                                        node.orelse)))

    def visit_Compare(self, node):
        #Type can depend on operands of a compare expression, for example for
        # nd arrays
        values = map(self.visit, [node.left] + node.comparators)
        return reduce(disjoint_reduce, values)

    def combine(self, node1, node2, register=False, unary_op=None):
        """
        When a function is called, like list.append, we call its combiner to
        see if it changes any types

        For example a.append(b) would change a's type based on b, so we use
        the combiner (in tables.py) of the append function which will call
        self.combine(arg0, arg1). Then with the code below we mark that the
        type of arg0 depends on the previous type of arg0 and the type of arg1
        """
        if not register:
            return

        # Don't do recursive combining
        if self.combining:
            return

        self.nodes = [node1, node2]
        if unary_op:
            unary_op(NamedType("int"))

        results = reduce(disjoint_reduce, map(self.visit, self.nodes))

        self.combine_(node1, results)

    def combine_(self, node1, result):
        if self.combining:
            return
        #We don't want infinite recursion by combining inside the current call
        self.combining = True
        results = [result, self.visit(self.current_call)]
        self.combining = False

        targets = \
            set(n.id for n in self.passmanager.gather(AssignTargets, node1)[0])
        for target in targets:
            self.update_naming(target, reduce(disjoint_reduce, results))

    def get_type(self, node):
        """
        If the combiner's unary op needs to use the get_type function,
        add a dependency to the corresponding node
        """
        self.nodes.append(node)
        return NamedType("int")

    def visit(self, node):
        if node is None:
            return set(), False
        return super(TypeDependencies, self).visit(node)

    def visit_Call(self, node):
        old_call = self.current_call
        self.current_call = node
        #in x.append(y), the type of x depends on the type of y
        for alias in self.strict_aliases[node.func].aliases:
            # this comes from a bind
            if isinstance(alias, ast.Call):
                a0 = alias.args[0]
                bounded_name = a0.id
                # by construction of the bind construct
                assert len(self.strict_aliases[a0].aliases) == 1
                bounded_function = list(self.strict_aliases[a0].aliases)[0]
                fake_name = ast.Name(bounded_name, ast.Load())
                fake_node = ast.Call(fake_name, alias.args[1:] + node.args,
                                     [], None, None)
                if bounded_function in self.combiners:
                    self.combiners[bounded_function].combiner(self, fake_node)
            # handle backward type dependencies from function calls
            else:
                if alias in self.combiners:
                    self.combiners[alias].combiner(self, node)

        args = map(self.visit, node.args)
        func = self.visit(node.func)
        params = args + [func or []]
        self.current_call = old_call
        return reduce(combine_reduce, params)

    def visit_Num(self, node):
        return set(), True

    def visit_Str(self, node):
        return set(), True

    def visit_Attribute(self, node):
        return set(), True

    def visit_Subscript(self, node):
        #returned type of a[b] is declval(a)[declval(b)], so need to go inside
        # the slice
        return reduce(combine_reduce, map(self.visit, (node.value,
                                                       node.slice)))

    def get_naming(self, id):
        if id in self.naming:
            return self.naming[id]
        elif id in self.global_declarations:
            return {self.global_declarations[id]}, False
        else:
            return set(), True

    def visit_Name(self, node):
        return self.get_naming(node.id)

    def visit_List(self, node):
        if node.elts:
            return reduce(combine_reduce, map(self.visit, node.elts))
        else:
            return set(), True

    visit_Set = visit_List

    def visit_Dict(self, node):
        if node.keys:
            items = node.keys + node.values
            return reduce(combine_reduce, map(self.visit, items))
        else:
            return set(), True

    visit_Tuple = visit_List

    def visit_Slice(self, node):
        return reduce(combine_reduce, map(self.visit, (node.lower,
                                                       node.upper)))

    def visit_ExtSlice(self, node):
        return reduce(combine_reduce, map(self.visit, node.dims))

    def visit_Index(self, node):
        return self.visit(node.value)

    visit_If = visit_any_conditionnal
    visit_While = visit_any_conditionnal

    def visit_Expr(self, node):
        return self.visit(node.value)

    def run(self, node, ctx):
        """
        We want to visit the functions in a predetermined "good" order
        so that when we try to call up a function's combiner, it already
        exists.

        Aka if function a calls function b we want b to be parsed before a.

        Because when parsing a, we may need to use b's combiner, which will
        only exist if b was already parsed.
        """
        super(TypeDependencies, self).run(node, ctx)

        self.visiting_functions = True
        self.ordered_global_declarations.reverse()
        map(self.visit, self.ordered_global_declarations)

        return self.result


class ReturnTypeDependencies(TypeDependencies):
    '''
    Gathers the aliases in each return statement, to deduce what a function's
    type is dependent on.

    Returns a DiGraph, u -> v means u depends on v
    '''

    NoDeps = "No dependencies"

    def __init__(self):
        super(ReturnTypeDependencies, self).__init__(GlobalDeclarations)
        self.result = nx.DiGraph()
        self.global_changing_functions = defaultdict(set)

    def visit_FunctionDef(self, node):
        self.result.add_node(node)
        super(ReturnTypeDependencies, self).visit_FunctionDef(node)

    def add_function_deps(self, res):
        #Only keep the aliases if they refer to something global
        gb_vals = self.global_declarations.values()
        res = {val for val in res[0] if val in gb_vals}
        for val in res:
            if val != self.current_function:
                self.result.add_edge(self.current_function, val)

    def visit_Return(self, node):
        if not node.value:
            return

        res = self.visit(node.value)

        if isinstance(node, ast.Yield):
            #For yields, pythran puts all the declared locals in the struct,
            # so there needs to be a dependency to each of them
            locs = self.passmanager.gather(LocalDeclarations,
                                           self.current_function)
            res = reduce(combine_reduce, [res] + [self.get_naming(l.id)
                                                  for l in locs])

        self.add_function_deps(res)
        #If the function can depend on nothing, say it. It will help us break
        # cyclic dependencies if any
        if res[1]:
            self.result.add_edge(self.current_function,
                                 ReturnTypeDependencies.NoDeps)

    def update_naming(self, name, value):
        '''
        Update or renew the name <-> dependencies binding
        depending on the in_cond state
        @rtype : None
        '''
        super(ReturnTypeDependencies, self).update_naming(name, value)

        if self.is_global_variable(name):
            #If a global's dependencies are modified, add the correct edges in
            # the resulting directed graph
            gb_vals = self.global_declarations.values()
            content = {y for y in value[0] if y in gb_vals}
            target = self.global_declarations[name]

            for y in content:
                if y != target and not self.result.has_edge(target, y):
                    self.result.add_edge(target, y)

            self.global_changing_functions[self.current_function].add(name)

    visit_Yield = visit_Return

    def run(self, node, ctx):
        super(ReturnTypeDependencies, self).run(node, ctx)

        # gb_decls = dict((v, k) for k, v in self.global_declarations.items())
        # gb_decls[ReturnTypeDependencies.NoDeps] = \
        # ReturnTypeDependencies.NoDeps
        # edges = self.result.edges()
        # edges = [(gb_decls[edge[0]], gb_decls[edge[1]]) for edge in edges]
        # print "edges: " + str(edges)

        gb_changing = self.global_changing_functions

        if not nx.is_directed_acyclic_graph(self.result):
            #We break the return dependency cycles.

            #For that we consider the functions that can have no dependencies,
            # and we remove what circular dependencies they have
            nodeps = ReturnTypeDependencies.NoDeps
            #Multiple uses of sorted because the order needs to be consistent
            # across all usages
            candidates = sorted(self.result.predecessors(nodeps))
            past_candidates = set(candidates)
            while len(candidates) > 0:
                new_candidates = set()
                for candidate in candidates:
                    for s in self.result.successors(candidate):
                        if nx.has_path(self.result, s, candidate):
                            while self.result.has_edge(candidate, s):
                                self.result.remove_edge(candidate, s)
                            #If candidate is a global modified by s, remove it
                            # from the list of the globals modified by s
                            if s in gb_changing:
                                for n in gb_changing[s]:
                                    gb = self.global_declarations[n]
                                    if gb == candidate:
                                        gb_changing[s].remove(n)
                                        break
                    new_candidates |= set(self.result.predecessors(candidate))
                    #needed for euler53
                    #If a function changes a global, then that global doesn't
                    # need other dependencies
                    if candidate in gb_changing:
                        for n in gb_changing[candidate]:
                            gb = self.global_declarations[n]
                            if gb in self.result:
                                new_candidates.add(gb)
                candidates = new_candidates - past_candidates
                past_candidates |= candidates
                candidates = sorted(list(candidates))
            """ There's a bad heuristic concerning globals changed by functions

            We assume that if there is a circular dependency between a function
            and a global, (aka return type of function depends on global and
            type of global depends on return type of function), that dependency
            happens inside the code of the function.

            Making it truly general would mean revisiting the Weak system."""

        # gb_decls = dict((v, k) for k, v in self.global_declarations.items())
        # gb_decls[ReturnTypeDependencies.NoDeps] = \
        #  ReturnTypeDependencies.NoDeps
        # edges = self.result.edges()
        # edges = [(gb_decls[edge[0]], gb_decls[edge[1]]) for edge in edges]
        # print "edges2: " + str(edges)

        if ReturnTypeDependencies.NoDeps in self.result:
            self.result.remove_node(ReturnTypeDependencies.NoDeps)

        return self.result


class Reorder(Transformation):
    '''
    Reorder top-level functions to prevent circular type dependencies
    '''
    def __init__(self):
        Transformation.__init__(self, TypeDependencies,
                                OrderedGlobalDeclarations)

    def prepare(self, node, ctx):
        super(Reorder, self).prepare(node, ctx)
        none_successors = self.type_dependencies.successors(
            TypeDependencies.NoDeps)
        candidates = sorted(none_successors)
        while candidates:
            new_candidates = list()
            for n in candidates:
                # remove edges that imply a circular dependency
                for p in sorted(self.type_dependencies.predecessors(n)):
                    if nx.has_path(self.type_dependencies, n, p):
                        try:
                            while True:  # may be multiple edges
                                self.type_dependencies.remove_edge(p, n)
                        except:
                            pass  # no more edges to remove
                    # nx.write_dot(self.type_dependencies,"b.dot")
                if not n in self.type_dependencies.successors(n):
                    new_candidates.extend(self.type_dependencies.successors(n))
            candidates = new_candidates

    def visit_Module(self, node):
        newbody = list()
        olddef = list()
        for stmt in node.body:
            if isinstance(stmt, ast.FunctionDef):
                olddef.append(stmt)
            else:
                newbody.append(stmt)
            try:
                newdef = nx.topological_sort(
                    self.type_dependencies,
                    self.ordered_global_declarations)
                newdef = [f for f in newdef if isinstance(f, ast.FunctionDef)]

            except nx.exception.NetworkXUnfeasible:
                raise PythranSyntaxError("Infinite function recursion",
                                         stmt)
        assert set(newdef) == set(olddef)
        node.body = newbody + newdef
        return node


class UnboundableRValue(Exception):
    pass


class Types(ModuleAnalysis):
    '''
    Infer symbolic type for all AST node
    '''

    def __init__(self):
        self.result = dict()
        self.result["bool"] = NamedType("bool")
        self.combiners = defaultdict(UserFunction)
        self.current_global_declarations = dict()
        self.max_recompute = 1  # max number of use to be lazy
        ModuleAnalysis.__init__(self, StrictAliases, LazynessAnalysis)
        self.curr_locals_declaration = None

    def prepare(self, node, ctx):
        self.passmanager.apply(Reorder, node, ctx)
        for mname, module in modules.iteritems():
            for fname, function in module.iteritems():
                tname = 'pythonic::{0}::proxy::{1}'.format(mname, fname)
                self.result[function] = NamedType(tname)
                self.combiners[function] = function
        super(Types, self).prepare(node, ctx)

    def run(self, node, ctx):
        super(Types, self).run(node, ctx)
        final_types = self.result.copy()
        for head in self.current_global_declarations.itervalues():
            if head not in final_types:
                final_types[head] = "void"
        return final_types

    def register(self, ptype):
        """register ptype as a local typedef"""
        # Too many of them leads to memory burst
        if len(self.typedefs) < cfg.getint('typing', 'max_combiner'):
            self.typedefs.append(ptype)
            return True
        return False

    def node_to_id(self, n, depth=0):
        if isinstance(n, ast.Name):
            return (n.id, depth)
        elif isinstance(n, ast.Subscript):
            if isinstance(n.slice, ast.Slice):
                return self.node_to_id(n.value, depth)
            else:
                return self.node_to_id(n.value, 1 + depth)
        # use return_alias information if any
        elif isinstance(n, ast.Call):
            func = n.func
            for alias in self.strict_aliases[func].aliases:
                # handle backward type dependencies from method calls
                signature = None
                if isinstance(alias, MethodIntr):
                    signature = alias
                #if isinstance(alias, ast.Attribute):
                #    _, signature = methods.get(
                #            func.attr,
                #            functions.get(func.attr, [(None, None)])[0]
                #            )
                #elif isinstance(alias, ast.Name):
                #    _, signature = functions.get(func.attr, [(None, None)])[0]
                if signature:
                    return_alias = (signature.return_alias
                                    and signature.return_alias(n))
                    if return_alias:  # else new location -> unboundable
                        assert len(return_alias), 'Too many return aliases'
                        return self.node_to_id(list(return_alias)[0], depth)
        raise UnboundableRValue()

    def isargument(self, node):
        """ checks whether node aliases to a parameter"""
        try:
            node_id, _ = self.node_to_id(node)
            return (node_id in self.name_to_nodes and
                    any([isinstance(n, ast.Name) and
                         isinstance(n.ctx, ast.Param)
                         for n in self.name_to_nodes[node_id]]))
        except UnboundableRValue:
                return False

    def combine(self, node, othernode, op=None, unary_op=None, register=False):
        if register and node in self.strict_aliases:
            self.combine_(node, othernode, op or operator.add,
                          unary_op or (lambda x: x), register)
            for a in self.strict_aliases[node].aliases:
                self.combine_(a, othernode, op or operator.add,
                              unary_op or (lambda x: x), register)
        else:
            self.combine_(node, othernode, op or operator.add,
                          unary_op or (lambda x: x), register)

    def combine_(self, node, othernode, op, unary_op, register):
        try:
            if register:  # this comes from an assignment,
                          # so we must check where the value is assigned
                node_id, depth = self.node_to_id(node)
                if depth > 0:
                    node = ast.Name(node_id, ast.Load())
                self.name_to_nodes.setdefault(node_id, set()).add(node)

                former_unary_op = unary_op

                # update the type to reflect container nesting
                unary_op = lambda x: reduce(lambda t, n: ContainerType(t),
                                            xrange(depth), former_unary_op(x))

            if isinstance(othernode, ast.FunctionDef):
                new_type = NamedType(othernode.name)
                if node not in self.result:
                    self.result[node] = new_type
            else:
                # only perform inter procedural combination upon stage 0
                if register and self.isargument(node) and self.stage == 0:
                    node_id, _ = self.node_to_id(node)
                    if node not in self.result:
                        self.result[node] = unary_op(self.result[othernode])
                    assert self.result[node], "found an alias with a type"

                    parametric_type = PType(self.current,
                                            self.result[othernode])
                    if self.register(parametric_type):

                        current_function = self.combiners[self.current]

                        def translator_generator(args, op, unary_op):
                            ''' capture args for translator generation'''
                            def interprocedural_type_translator(s, n):
                                translated_othernode = ast.Name(
                                    '__fake__', ast.Load())
                                s.result[translated_othernode] = (
                                    parametric_type.instanciate(
                                        s.current,
                                        [s.result[arg] for arg in n.args]))
                                # look for modified argument
                                for p, effective_arg in enumerate(n.args):
                                    formal_arg = args[p]
                                    if formal_arg.id == node_id:
                                        translated_node = effective_arg
                                        break
                                try:
                                    s.combine(translated_node,
                                              translated_othernode,
                                              op, unary_op, register=True)
                                except NotImplementedError:
                                    pass
                                    # this may fail when the effective
                                    #parameter is an expression
                                except UnboundLocalError:
                                    pass
                                    # this may fail when translated_node
                                    #is a default parameter
                            return interprocedural_type_translator
                        translator = translator_generator(
                            self.current.args.args,
                            op, unary_op)  # deferred combination
                        current_function.add_combiner(translator)
                else:
                    new_type = unary_op(self.result[othernode])
                    if node not in self.result:
                        self.result[node] = new_type
                    else:
                        self.result[node] = op(self.result[node], new_type)
        except UnboundableRValue:
            pass
        except:
            #print ast.dump(othernode)
            raise

    def visit_FunctionDef(self, node):
        self.curr_locals_declaration = self.passmanager.gather(
            LocalDeclarations,
            node)
        self.current = node
        self.typedefs = list()
        self.name_to_nodes = {arg.id: {arg} for arg in node.args.args}
        self.yield_points = self.passmanager.gather(YieldPoints, node)

        # two stages, one for inter procedural propagation
        self.stage = 0
        self.generic_visit(node)

        # and one for backward propagation
        # but this step is generally costly
        if cfg.getboolean('typing', 'enable_two_steps_typing'):
            self.stage = 1
            self.generic_visit(node)

        # propagate type information through all aliases
        for name, nodes in self.name_to_nodes.iteritems():
            final_node = ast.Name("__fake__" + name, ast.Load())
            for n in nodes:
                self.combine(final_node, n)
            for n in nodes:
                self.result[n] = self.result[final_node]
        self.current_global_declarations[node.name] = node
        # return type may be unset if the function always raises
        return_type = self.result.get(node, NamedType("void"))
        self.result[node] = (Assignable(return_type), self.typedefs)
        for k in self.passmanager.gather(LocalDeclarations, node):
            self.result[k] = self.get_qualifier(k)(self.result[k])

    def get_qualifier(self, node):
        lazy_res = self.lazyness_analysis[node.id]
        return Lazy if lazy_res <= self.max_recompute else Assignable

    def visit_Return(self, node):
        self.generic_visit(node)
        if not self.yield_points:
            if node.value:
                self.combine(self.current, node.value)
            else:
                self.result[self.current] = NamedType("none_type")

    def visit_Yield(self, node):
        self.generic_visit(node)
        self.combine(self.current, node.value)

    def visit_Assign(self, node):
        self.visit(node.value)
        for t in node.targets:
            self.combine(t, node.value, register=True)
            if t in self.curr_locals_declaration:
                self.result[t] = self.get_qualifier(t)(self.result[t])
            if isinstance(t, ast.Subscript):
                if self.visit_AssignedSubscript(t):
                    for alias in self.strict_aliases[t.value].aliases:
                        fake = ast.Subscript(alias, t.value, ast.Store())
                        self.combine(fake, node.value, register=True)

    def visit_AugAssign(self, node):
        self.visit(node.value)
        self.combine(node.target, node.value,
                     lambda x, y: x + ExpressionType(
                         operator_to_lambda[type(node.op)],
                         [x, y]), register=True)
        if isinstance(node.target, ast.Subscript):
            if self.visit_AssignedSubscript(node.target):
                for alias in self.strict_aliases[node.target.value].aliases:
                    fake = ast.Subscript(alias, node.target.value, ast.Store())
                    self.combine(fake,
                                 node.value,
                                 lambda x, y: x + ExpressionType(
                                     operator_to_lambda[type(node.op)],
                                     [x, y]),
                                 register=True)

    def visit_For(self, node):
        self.visit(node.iter)
        self.combine(node.target, node.iter,
                     unary_op=IteratorContentType, register=True)
        node.body and map(self.visit, node.body)
        node.orelse and map(self.visit, node.orelse)

    def visit_BoolOp(self, node):
        self.generic_visit(node)
        [self.combine(node, value) for value in node.values]

    def visit_BinOp(self, node):
        self.generic_visit(node)
        wl, wr = [self.result[x].isweak() for x in (node.left, node.right)]
        if (isinstance(node.op, ast.Add) and any([wl, wr])
                and not all([wl, wr])):
        # assumes the + operator always has the same operand type
        # on left and right side
            F = operator.add
        else:
            F = lambda x, y: ExpressionType(
                operator_to_lambda[type(node.op)], [x, y])

        fake_node = ast.Name("#", ast.Param())
        self.combine(fake_node, node.left, F)
        self.combine(fake_node, node.right, F)
        self.combine(node, fake_node)
        del self.result[fake_node]

    def visit_UnaryOp(self, node):
        self.generic_visit(node)
        f = lambda x: ExpressionType(operator_to_lambda[type(node.op)], [x])
        self.combine(node, node.operand, unary_op=f)

    def visit_IfExp(self, node):
        self.generic_visit(node)
        [self.combine(node, n) for n in (node.body, node.orelse)]

    def visit_Compare(self, node):
        self.generic_visit(node)
        all_compare = zip(node.ops, node.comparators)
        for op, comp in all_compare:
            self.combine(node, comp,
                         unary_op=lambda x: ExpressionType(
                             operator_to_lambda[type(op)],
                             [self.result[node.left], x])
                         )

    def visit_Call(self, node):
        self.generic_visit(node)
        for alias in self.strict_aliases[node.func].aliases:
            # this comes from a bind
            if isinstance(alias, ast.Call):
                a0 = alias.args[0]
                bounded_name = a0.id
                # by construction of the bind construct
                assert len(self.strict_aliases[a0].aliases) == 1
                bounded_function = list(self.strict_aliases[a0].aliases)[0]
                fake_name = ast.Name(bounded_name, ast.Load())
                fake_node = ast.Call(fake_name, alias.args[1:] + node.args,
                                     [], None, None)
                self.combiners[bounded_function].combiner(self, fake_node)
                # force recombination of binded call
                for n in self.name_to_nodes[node.func.id]:
                    self.result[n] = ReturnType(self.result[alias.func],
                                                [self.result[arg]
                                                 for arg in alias.args])
            # handle backward type dependencies from function calls
            else:
                self.combiners[alias].combiner(self, node)

        # recurring nightmare
        isweak = any(self.result[n].isweak() for n in node.args + [node.func])
        if self.stage == 0 and isweak:
            # maybe we can get saved if we have a hint about
            # the called function return type
            for alias in self.strict_aliases[node.func].aliases:
                if alias is self.current and alias in self.result:
                    # great we have a (partial) type information
                    self.result[node] = self.result[alias]
                    return

        # special handler for getattr: use the attr name as an enum member
        if type(node.func) is (ast.Attribute) and node.func.attr == 'getattr':
            F = lambda f: GetAttr(self.result[node.args[0]], node.args[1].s)
        # default behavior
        else:
            F = lambda f: ReturnType(f,
                                     [self.result[arg] for arg in node.args])
        # op is used to drop previous value there
        self.combine(node, node.func, op=lambda x, y: y, unary_op=F)

    def visit_Num(self, node):
        self.result[node] = NamedType(pytype_to_ctype_table[type(node.n)])

    def visit_Str(self, node):
        self.result[node] = NamedType(pytype_to_ctype_table[str])

    def visit_Attribute(self, node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return w[n.id], (n.id,)
            elif isinstance(n, ast.Attribute):
                r = rec(w, n.value)
                if len(r[1]) > 1:
                    plast, last = r[1][-2:]
                    if plast == '__builtin__' and last.startswith('__'):
                        return r[0][n.attr], r[1][:-2] + r[1][-1:] + (n.attr,)
                return r[0][n.attr], r[1] + (n.attr,)
        obj, path = rec(modules, node)
        path = ('pythonic',) + path
        if obj.isliteral():
            self.result[node] = DeclType('::'.join(path))
        else:
            self.result[node] = DeclType(
                '::'.join(path[:-1]) + '::proxy::' + path[-1] + '()')

    def visit_Slice(self, node):
        self.generic_visit(node)
        if node.step is None or (type(node.step) is ast.Num
                                 and node.step.n == 1):
            self.result[node] = NamedType('pythonic::types::contiguous_slice')
        else:
            self.result[node] = NamedType('pythonic::types::slice')

    def visit_Subscript(self, node):
        self.visit(node.value)
        if isinstance(node.slice, ast.ExtSlice):
            d = sum(int(type(dim) is ast.Index) for dim in node.slice.dims)
            f = lambda t: reduce(lambda x, y: ContentType(x), range(d), t)
        elif isinstance(node.slice, ast.Slice):
            self.visit(node.slice)
            f = lambda x:  ExpressionType(
                lambda a, b: "{0}[{1}]".format(a, b),
                [x, self.result[node.slice]]
                )
        elif isinstance(node.slice.value, ast.Num) and node.slice.value.n >= 0:
            f = lambda t: ElementType(node.slice.value.n, t)
        elif isinstance(node.slice.value, ast.Tuple):
            f = lambda t: reduce(lambda x, y: ContentType(x),
                                 node.slice.value.elts, t)
        else:
            self.visit(node.slice)
            f = lambda x: ExpressionType(
                lambda a, b: "{0}[{1}]".format(a, b),
                [x, self.result[node.slice]]
                )
        f and self.combine(node, node.value, unary_op=f)

    def visit_AssignedSubscript(self, node):
        if type(node.slice) not in (ast.Slice, ast.ExtSlice):
            self.visit(node.slice)
            self.combine(node.value, node.slice,
                         unary_op=IndexableType, register=True)
            for alias in self.strict_aliases[node.value].aliases:
                self.combine(alias, node.slice,
                             unary_op=IndexableType, register=True)
            return True
        else:
            return False

    def visit_Name(self, node):
        if node.id in self.name_to_nodes:
            for n in self.name_to_nodes[node.id]:
                self.combine(node, n)
        elif node.id in self.current_global_declarations:
            self.combine(node, self.current_global_declarations[node.id])
        else:
            self.result[node] = NamedType(node.id, {Weak})

    def visit_List(self, node):
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=ListType)
        else:
            self.result[node] = NamedType("pythonic::types::empty_list")

    def visit_Set(self, node):
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=SetType)
        else:
            self.result[node] = NamedType("pythonic::types::empty_set")

    def visit_Dict(self, node):
        self.generic_visit(node)
        if node.keys:
            for key, value in zip(node.keys, node.values):
                self.combine(node, key,
                             unary_op=lambda x: DictType(x,
                                                         self.result[value]))
        else:
            self.result[node] = NamedType("pythonic::types::empty_dict")

    def visit_ExceptHandler(self, node):
        if node.type and node.name:
            if not isinstance(node.type, ast.Tuple):
                tname = NamedType(
                    'pythonic::types::{0}'.format(node.type.attr))
                self.result[node.type] = tname
                self.combine(node.name, node.type, register=True)
        map(self.visit, node.body)

    def visit_Tuple(self, node):
        self.generic_visit(node)
        try:
            types = [self.result[elt] for elt in node.elts]
            self.result[node] = TupleType(types)
        except:
            pass  # not very harmonious with the combine method ...

    def visit_Index(self, node):
        self.generic_visit(node)
        self.combine(node, node.value)

    def visit_arguments(self, node):
        for i, arg in enumerate(node.args):
            self.result[arg] = ArgumentType(i)
        map(self.visit, node.defaults)

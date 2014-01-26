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
from analysis import LazynessAnalysis
from passes import Transformation
from syntax import PythranSyntaxError
from cxxtypes import *
from intrinsic import UserFunction, MethodIntr
import itertools
import operator
import metadata
import intrinsic
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
        return {'pythonic/types/ndarray.hpp'}
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


class TypeDependencies(ModuleAnalysis):
    '''
    Gathers the callees of each function required for type inference

    This analyse produces a directed graph with functions as nodes and edges
    between nodes when a function might call another.
    '''

    NoDeps = "None"

    def __init__(self):
        self.result = nx.DiGraph()
        self.current_function = None
        ModuleAnalysis.__init__(self, GlobalDeclarations)

    def prepare(self, node, ctx):
        super(TypeDependencies, self).prepare(node, ctx)
        for k, v in self.global_declarations.iteritems():
            self.result.add_node(v)
        self.result.add_node(TypeDependencies.NoDeps)

    def visit_any_conditionnal(self, node):
        '''
        Set and restore the in_cond variable whenever a node
        the children of which may not be executed is visited
        '''
        in_cond = self.in_cond
        self.in_cond = True
        self.generic_visit(node)
        self.in_cond = in_cond

    def visit_FunctionDef(self, node):
        assert self.current_function is None
        self.current_function = node
        self.result.add_node(node)
        self.naming = dict()
        self.in_cond = False  # True when we are in a if, while or for
        self.generic_visit(node)
        self.current_function = None

    def visit_Return(self, node):
        '''
        Gather all the function call that led to the creation of the
        returned expression and add an edge to each of this function.

        When visiting an expression, one returns a list of frozensets.  Each
        element of the list is linked to a possible path, each element of a
        frozenset is linked to a dependency.
        '''
        if node.value:
            v = self.visit(node.value)
            for dep_set in v:
                if dep_set:
                    [self.result.add_edge(dep,
                            self.current_function) for dep in dep_set]
                else:
                    self.result.add_edge(TypeDependencies.NoDeps,
                                            self.current_function)

    visit_Yield = visit_Return

    def update_naming(self, name, value):
        '''
        Update or renew the name <-> dependencies binding
        depending on the in_cond state
        '''
        if self.in_cond:
            self.naming.setdefault(name, []).extend(value)
        else:
            self.naming[name] = value

    def visit_Assign(self, node):
        v = self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.update_naming(t.id, v)

    def visit_AugAssign(self, node):
        v = self.visit(node.value)
        t = node.target
        if isinstance(t, ast.Name):
            self.update_naming(t.id, v)

    def visit_For(self, node):
        self.naming.update({node.target.id: self.visit(node.iter)})
        self.visit_any_conditionnal(node)

    def visit_BoolOp(self, node):
        return sum((self.visit(value) for value in node.values), [])

    def visit_BinOp(self, node):
        args = map(self.visit, (node.left, node.right))
        return list({frozenset.union(*x) for x in itertools.product(*args)})

    def visit_UnaryOp(self, node):
        return self.visit(node.operand)

    def visit_Lambda(self, node):
        assert False

    def visit_IfExp(self, node):
        return self.visit(node.body) + self.visit(node.orelse)

    def visit_Compare(self, node):
        return [frozenset()]

    def visit_Call(self, node):
        args = map(self.visit, node.args)
        func = self.visit(node.func)
        params = args + [func or []]
        return list({frozenset.union(*p) for p in itertools.product(*params)})

    def visit_Num(self, node):
        return [frozenset()]

    def visit_Str(self, node):
        return [frozenset()]

    def visit_Attribute(self, node):
        return [frozenset()]

    def visit_Subscript(self, node):
        return self.visit(node.value)

    def visit_Name(self, node):
        if node.id in self.naming:
            return self.naming[node.id]
        elif node.id in self.global_declarations:
            return [frozenset([self.global_declarations[node.id]])]
        else:
            return [frozenset()]

    def visit_List(self, node):
        if node.elts:
            return list(set(sum(map(self.visit, node.elts), [])))
        else:
            return [frozenset()]

    visit_Set = visit_List

    def visit_Dict(self, node):
        if node.keys:
            items = node.keys + node.values
            return list(set(sum(map(self.visit, items), [])))
        else:
            return [frozenset()]

    visit_Tuple = visit_List

    def visit_Slice(self, node):
        return [frozenset()]

    def visit_Index(self, node):
        return [frozenset()]

    visit_If = visit_any_conditionnal
    visit_While = visit_any_conditionnal


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
                else:
                    pass
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
                newdef = (f for f in nx.topological_sort(
                    self.type_dependencies,
                    self.ordered_global_declarations
                    ))
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
        final_types = {k: self.result[k]
                if k in self.result
                else v
                for k, v in self.result.iteritems()}
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

        else:
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
                                 s.current, [s.result[arg] for arg in n.args]))
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
            lazy_res = self.lazyness_analysis[k.id]
            if lazy_res <= self.max_recompute:
                self.result[k] = Lazy(self.result[k])
            else:
                self.result[k] = Assignable(self.result[k])

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
            if isinstance(t, ast.Subscript):
                if self.visit_AssignedSubscript(t):
                    for alias in self.strict_aliases[t.value].aliases:
                        fake = ast.Subscript(alias, t.value, ast.Store())
                        self.combine(fake, node.value, register=True)

    def visit_AugAssign(self, node):
        self.visit(node.value)
        self.combine(node.target, node.value,
            lambda x, y: x + ExpressionType(operator_to_lambda[type(node.op)],
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
                        [self.result[arg] for arg in alias.args])
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

        # default behavior
        F = lambda f: ReturnType(f, [self.result[arg] for arg in node.args])
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
        self.result[node] = DeclType(
                '::'.join(path) if obj.isliteral() else
                ('::'.join(path[:-1]) + '::proxy::' + path[-1] + '()')
                )

    def visit_Slice(self, node):
        self.generic_visit(node)
        self.result[node] = NamedType('pythonic::types::slice')

    def visit_Subscript(self, node):
        self.visit(node.value)
        if metadata.get(node, metadata.Attribute):
            f = lambda t: AttributeType(node.slice.value.n, t)
        elif isinstance(node.slice, ast.ExtSlice):
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
                        unary_op=lambda x: DictType(x, self.result[value]))
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

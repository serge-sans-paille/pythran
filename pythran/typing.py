'''
This module performs the return type inference, according to symbolic types,
   It then reorders function declarations according to the return type deps.
    * type_all generates a node -> type binding
'''

import ast
import networkx as nx
from tables import pytype_to_ctype_table, operator_to_lambda
from tables import modules, builtin_constants, builtin_constructors
from tables import methods, functions
from analysis import GlobalDeclarations, YieldPoints, LocalDeclarations
from analysis import OrderedGlobalDeclarations, ModuleAnalysis, StrictAliases
from passes import Transformation
from syntax import PythranSyntaxError
from cxxtypes import *
from intrinsic import UserFunction, MethodIntr
import itertools
import operator
import metadata
import intrinsic


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
def add_if_not_in(l0, l1):
    s0 = set(l0)
    l = list(l0)
    return l + [x for x in l1 if x not in s0]


class TypeDependencies(ModuleAnalysis):
    '''
    Gathers the calles of each function required for type inference
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

    def visit_FunctionDef(self, node):
        assert self.current_function is None
        modules['__user__'][node.name] = UserFunction()
        self.current_function = node
        self.result.add_node(node)
        self.naming = dict()
        self.generic_visit(node)
        self.current_function = None

    def visit_Return(self, node):
        if node.value:
            v = self.visit(node.value)
            for dep_set in v:
                if dep_set:
                    [self.result.add_edge(dep,
                            self.current_function) for dep in dep_set]
                else:
                    self.result.add_edge(TypeDependencies.NoDeps,
                                            self.current_function)

    def visit_Yield(self, node):
        self.visit_Return(node)

    def visit_Assign(self, node):
        v = self.visit(node.value)
        self.naming.update({t.id: v  # need to handle subscript too ...
            for t in node.targets if isinstance(t, ast.Name)})

    def visit_AugAssign(self, node):
        v = self.visit(node.value)
        if isinstance(node.target, ast.Name):
            self.naming.update({node.target.id: v})

    def visit_For(self, node):
        self.naming.update({node.target.id: self.visit(node.iter)})
        self.generic_visit(node)

    def visit_BoolOp(self, node):
        return sum((self.visit(value) for value in node.values), [])

    def visit_BinOp(self, node):
        return [l.union(r) for l in self.visit(node.left)
                for r in self.visit(node.right)]

    def visit_UnaryOp(self, node):
        return self.visit(node.operand)

    def visit_Lambda(self, node):
        assert False

    def visit_IfExp(self, node):
        return self.visit(node.body) + self.visit(node.orelse)

    def visit_Compare(self, node):
        return [frozenset()]

    def visit_Call(self, node):
        func = self.visit(node.func)
        for arg in node.args:
            func = [f.union(v) for f in func for v in self.visit(arg)]
        return func

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
        return reduce(add_if_not_in,
                map(self.visit, node.elts),
                [frozenset()])

    def visit_Set(self, node):
        return reduce(add_if_not_in,
                map(self.visit, node.elts),
                [frozenset()])

    def visit_Dict(self, node):
        return reduce(add_if_not_in,
                map(self.visit, node.keys) + map(self.visit, node.values),
                [frozenset()])

    def visit_Tuple(self, node):
        return reduce(add_if_not_in, map(self.visit, node.elts), [frozenset()])

    def visit_Slice(self, node):
        return [frozenset()]

    def visit_Index(self, node):
        return [frozenset()]


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
        self.current_global_declarations = dict()
        ModuleAnalysis.__init__(self, StrictAliases, LocalDeclarations)

    def prepare(self, node, ctx):
        self.passmanager.apply(Reorder, node, ctx)
        for mname, module in modules.iteritems():
            for fname, function in module.iteritems():
                tname = 'pythonic::{0}::proxy::{1}'.format(mname, fname)
                self.result[function] = NamedType(tname)
        super(Types, self).prepare(node, ctx)

    def run(self, node, ctx):
        super(Types, self).run(node, ctx)
        for k in self.local_declarations:
            self.result[k] = Assignable(self.result[k])
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
        self.typedefs.append(ptype)

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
            for a in self.strict_aliases[node].aliases:
                self.combine_(a, othernode, op or operator.add,
                        unary_op or (lambda x: x), register)
            else:
                self.combine_(node, othernode, op or operator.add,
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
                if register and self.isargument(node):
                    node_id, _ = self.node_to_id(node)
                    if node not in self.result:
                        self.result[node] = unary_op(self.result[othernode])
                    assert self.result[node], "found an alias with a type"

                    parametric_type = PType(self.current,
                                            self.result[othernode])
                    self.register(parametric_type)

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
                    user_module = modules['__user__']
                    current_function = user_module[self.current.name]
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

        for k, v in builtin_constants.iteritems():
            fake_node = ast.Name(k, ast.Load())
            self.name_to_nodes.update({k: {fake_node}})
            self.result[fake_node] = NamedType(v)

        self.generic_visit(node)

        # propagate type information through all aliases
        for name, nodes in self.name_to_nodes.iteritems():
            final_node = ast.Name("__fake__" + name, ast.Load())
            for n in nodes:
                self.combine(final_node, n)
            for n in nodes:
                self.result[n] = self.result[final_node]
        self.current_global_declarations[node.name] = node
        self.result[node] = (Assignable(self.result[node]), self.typedefs)

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
                self.visit_AssignedSubscript(t)
                for alias in self.strict_aliases[t.value].aliases:
                    fake = ast.Subscript(alias, t.value, ast.Store())
                    self.combine(fake, node.value, register=True)

    def visit_AugAssign(self, node):
        self.visit(node.value)
        self.combine(node.target, node.value,
            lambda x, y: ExpressionType(operator_to_lambda[type(node.op)],
                [x, y]), register=True)
        if isinstance(node.target, ast.Subscript):
            self.visit_AssignedSubscript(node.target)
            for alias in self.strict_aliases[node.target.value].aliases:
                fake = ast.Subscript(alias, node.target.value, ast.Store())
                self.combine(fake,
                        node.value,
                        lambda x, y: ExpressionType(
                            operator_to_lambda[type(node.op)],
                            [x, y]),
                        register=True)

    def visit_For(self, node):
        self.visit(node.iter)
        self.combine(node.target, node.iter,
            unary_op=IteratorContentType, register=True)
        node.body and [self.visit(n) for n in node.body]
        node.orelse and [self.visit(n) for n in node.orelse]

    def visit_BoolOp(self, node):
        self.generic_visit(node)
        [self.combine(node, value) for value in node.values]

    def visit_BinOp(self, node):
        self.generic_visit(node)
        wl, wr = [self.result[x].isweak() for x in (node.left, node.right)]
        if (isinstance(node.op, ast.Add) and any([wl, wr])
            and not all([wl, wr])):
        # assumes the + operator always has the same operand type
        #on left and right side
            F = operator.add
        else:
            F = lambda x, y: ExpressionType(
                operator_to_lambda[type(node.op)], [x, y])

        self.combine(node, node.left, F)
        self.combine(node, node.right, F)

    def visit_UnaryOp(self, node):
        self.generic_visit(node)
        f = lambda x: ExpressionType(operator_to_lambda[type(node.op)], [x])
        self.combine(node, node.operand, unary_op=f)

    def visit_IfExp(self, node):
        self.generic_visit(node)
        [self.combine(node, n) for n in (node.body, node.orelse)]

    def visit_Compare(self, node):
        self.generic_visit(node)
        self.result[node] = NamedType("bool")

    def visit_Call(self, node):
        self.generic_visit(node)
        user_module = modules['__user__']
        for alias in self.strict_aliases[node.func].aliases:
            # handle backward type dependencies from method calls
            if isinstance(alias, intrinsic.Intrinsic):
                if hasattr(alias, 'combiner'):
                    # also generate all possible aliasing combinations
                    combinations = [filter(
                        None,
                        self.strict_aliases[arg].aliases.union({arg}))
                        for arg in node.args]
                    for new_args in itertools.product(*combinations):
                        alias.combiner(self,
                                ast.Call(
                                    node.func,
                                    new_args,
                                    [],
                                    None,
                                    None)
                                )
            # handle backward type dependencies from user calls
            elif isinstance(alias, ast.FunctionDef):
                user_module[alias.name].combiner(self, node)
            # this comes from a bind
            elif isinstance(alias, ast.Call):
                bounded_function_name = alias.args[0].id
                bounded_function = user_module[bounded_function_name]
                fake_name = ast.Name(bounded_function_name, ast.Load())
                fake_node = ast.Call(fake_name, alias.args[1:] + node.args,
                    [], None, None)
                bounded_function.combiner(self, fake_node)
                # force recombination of binded call
                for n in self.name_to_nodes[node.func.id]:
                    self.result[n] = ReturnType(self.result[alias.func],
                        [self.result[arg] for arg in alias.args])

        F = lambda f: ReturnType(f, [self.result[arg] for arg in node.args])
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
                return r[0][n.attr], r[1] + (n.attr,)
        obj, path = rec(modules, node)
        self.result[node] = DeclType(
                '::'.join(path) if obj.isliteral() else
                ('::'.join(path[:-1]) + '::proxy::' + path[-1] + '()')
                )

    def visit_Subscript(self, node):
        self.visit(node.value)
        if metadata.get(node, metadata.Attribute):
            f = lambda t: AttributeType(node.slice.value.n, t)
        elif isinstance(node.slice, ast.Slice):
            f = lambda t: t
        elif isinstance(node.slice.value, ast.Num):
            f = lambda t: ElementType(node.slice.value.n, t)
        elif isinstance(node.slice.value, ast.Tuple):
            f = lambda t: reduce(lambda x, y: ContentType(x),
                    node.slice.value.elts, t)
        else:
            f = ContentType
        self.combine(node, node.value, unary_op=f)

    def visit_AssignedSubscript(self, node):
        if not isinstance(node.slice, ast.Slice):
            self.visit(node.slice)
            self.combine(node.value, node.slice,
                    unary_op=IndexableType, register=True)
            for alias in self.strict_aliases[node.value].aliases:
                self.combine(alias, node.slice,
                        unary_op=IndexableType, register=True)

    def visit_Name(self, node):
        if node.id in self.name_to_nodes:
            for n in self.name_to_nodes[node.id]:
                self.combine(node, n)
        elif node.id in self.current_global_declarations:
            self.combine(node, self.current_global_declarations[node.id])
        elif node.id in builtin_constants:
            self.result[node] = NamedType(builtin_constants[node.id])
        elif node.id in builtin_constructors:
            self.result[node] = NamedType("pythonic::constructor<{0}>".format(
                builtin_constructors[node.id]))
        else:
            self.result[node] = NamedType(node.id, {Weak})

    def visit_List(self, node):
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=ListType)
        else:
            self.result[node] = NamedType("core::empty_list")

    def visit_Set(self, node):
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=SetType)
        else:
            self.result[node] = NamedType("core::empty_set")

    def visit_Dict(self, node):
        self.generic_visit(node)
        if node.keys:
            for key, value in zip(node.keys, node.values):
                self.combine(node, key,
                        unary_op=lambda x: DictType(x, self.result[value]))
        else:
            self.result[node] = NamedType("core::empty_dict")

    def visit_ExceptHandler(self, node):
        if node.type and node.name:
            if not isinstance(node.type, ast.Tuple):
                tname = NamedType('core::{0}'.format(node.type.attr))
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

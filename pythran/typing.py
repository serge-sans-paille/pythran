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
import types
import itertools
import metadata


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
    l = [x for x in l0]
    return l + [x for x in l1 if x not in s0]


class TypeDependencies(ModuleAnalysis):

    NoDeps = "None"

    def __init__(self):
        self.result = nx.DiGraph()
        self.current_function = None
        ModuleAnalysis.__init__(self, GlobalDeclarations)

    def run_visit(self, node):
        for k, v in self.global_declarations.iteritems():
            self.result.add_node(v)
        self.result.add_node(TypeDependencies.NoDeps)
        return ModuleAnalysis.run_visit(self, node)

    def visit_FunctionDef(self, node):
        assert self.current_function is None
        modules['__user__'][node.name] = UserFunction()
        self.current_function = node
        self.result.add_node(node)
        self.naming = dict()
        [self.visit(n) for n in node.args.defaults]
        [self.visit(n) for n in node.body]
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
        if node.body:
            [self.visit(n) for n in node.body]
        if node.orelse:
            [self.visit(n) for n in node.orelse]

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
        return reduce(add_if_not_in,
                map(self.visit, node.elts),
                [frozenset()])

    def visit_Slice(self, node):
        return [frozenset()]

    def visit_Index(self, node):
        return [frozenset()]


class Reorder(Transformation):
    def __init__(self):
        Transformation.__init__(self, TypeDependencies,
                OrderedGlobalDeclarations)

    def run_visit(self, node):
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
        Transformation.run_visit(self, node)

    def visit_Module(self, node):
        newbody = list()
        olddef = list()
        for stmt in node.body:
            if isinstance(stmt, ast.FunctionDef):
                olddef.append(stmt)
            else:
                newbody.append(stmt)
            try:
                newdef = [f for f in nx.topological_sort(
                    self.type_dependencies,
                    self.ordered_global_declarations
                    ) if isinstance(f, ast.FunctionDef)]
            except nx.exception.NetworkXUnfeasible:
                raise PythranSyntaxError("Infinite function recursion",
                                        stmt)
        assert set(newdef) == set(olddef)
        node.body = newbody + newdef
        return node


class UnboundableRValue(Exception):
    pass


def copy_func(f, name=None):
    return types.FunctionType(f.func_code,
                            f.func_globals,
                            name or f.func_name,
                            f.func_defaults,
                            f.func_closure)


class Types(ModuleAnalysis):
    '''Infer symbolic type for all AST node.'''

    def __init__(self):
        self.result = dict()
        self.result["bool"] = NamedType("bool")
        self.current = list()
        self.current_global_declarations = dict()
        ModuleAnalysis.__init__(self, StrictAliases, LocalDeclarations)

    def run(self, node, ctx):
        self.passmanager.apply(Reorder, node, ctx)
        return ModuleAnalysis.run(self, node, ctx)

    def run_visit(self, node):
        ModuleAnalysis.run_visit(self, node)
        final_types = {k: self.result[k]
                if k in self.result
                else v
                for k, v in self.result.iteritems()}
        for k in self.local_declarations:
            self.result[k] = Assignable(self.result[k])
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
                if isinstance(alias, ast.Attribute):
                    _, signature = methods.get(
                            func.attr,
                            functions.get(func.attr, [(None, None)])[0]
                            )
                elif isinstance(alias, ast.Name):
                    _, signature = functions.get(func.attr, [(None, None)])[0]
                if signature:
                    return_alias = (signature.return_alias
                            and signature.return_alias(n))
                    if return_alias:  # else new location -> unboundable
                        return self.node_to_id(return_alias, depth)
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
        self.combine_(node, othernode, op or (lambda x, y: x + y),
                        unary_op or (lambda x: x), register)

    def combine_(self, node, othernode, op, unary_op, register):
        try:
            if register:  # this comes from an assignment,
                          # so we must check where the value is assigned
                node_id, depth = self.node_to_id(node)
                if depth > 0:
                    node = ast.Name(node_id, ast.Load())
                self.name_to_nodes.setdefault(node_id, set()).add(node)

                former_unary_op = copy_func(unary_op)

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

                    parametric_type = PType(self.current[-1],
                                            self.result[othernode])
                    self.register(parametric_type)

                    def translator_generator(args, op, unary_op):
                        ''' capture args for translator generation'''
                        def interprocedural_type_translator(s, n):
                            translated_othernode = ast.Name(
                                '__fake__', ast.Load())
                            s.result[translated_othernode] = (
                             parametric_type.instanciate(
                             s.current[-1], [s.result[arg] for arg in n.args]))
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
                        self.current[-1].args.args,
                        op, unary_op)  # deferred combination
                    user_module = modules['__user__']
                    current_function = user_module[self.current[-1].name]
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
            print ast.dump(othernode)
            raise

    def visit_Module(self, node):
        [self.visit(n) for n in node.body]

    def visit_FunctionDef(self, node):
        self.current.append(node)
        self.typedefs = list()
        self.name_to_nodes = {arg.id: {arg} for arg in node.args.args}
        self.yield_points = self.passmanager.gather(YieldPoints, node)

        for k, v in builtin_constants.iteritems():
            fake_node = ast.Name(k, ast.Load())
            self.name_to_nodes.update({k: {fake_node}})
            self.result[fake_node] = NamedType(v)
        self.visit(node.args)
        [self.visit(n) for n in node.body]
        # propagate type information through all aliases
        for name, nodes in self.name_to_nodes.iteritems():
            final_node = ast.Name("__fake__" + name, ast.Load())
            for n in nodes:
                self.combine(final_node, n)
            for n in nodes:
                self.result[n] = self.result[final_node]
        self.current_global_declarations[node.name] = node
        self.result[node] = (Assignable(self.result[node]), self.typedefs)
        self.current.pop()

    def visit_Return(self, node):
        if not self.yield_points:
            if node.value:
                self.visit(node.value)
                self.combine(self.current[-1], node.value)
            else:
                self.result[self.current[-1]] = NamedType("none_type")

    def visit_Yield(self, node):
        self.visit(node.value)
        self.combine(self.current[-1], node.value)

    def visit_TryExcept(self, node):
        [self.visit(n) for n in node.body]
        [self.visit(n) for n in node.handlers]

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
            unary_op=lambda x: IteratorContentType(x), register=True)
        self.visit(node.target)
        if node.body:
            [self.visit(n) for n in node.body]
        if node.orelse:
            [self.visit(n) for n in node.orelse]

    def visit_BoolOp(self, node):
        [self.visit(value) for value in node.values]
        [self.combine(node, value) for value in node.values]

    def visit_BinOp(self, node):
        [self.visit(value) for value in (node.left, node.right)]
        wl, wr = [self.result[x].isweak() for x in (node.left, node.right)]
        if (isinstance(node.op, ast.Add) and any([wl, wr])
            and not all([wl, wr])):
        # assumes the + operator always has the same operand type
        #on left and right side
            F = lambda x, y: x + y
        else:
            F = lambda x, y: ExpressionType(
                operator_to_lambda[type(node.op)], [x, y])

        self.combine(node, node.left, F)
        self.combine(node, node.right, F)

    def visit_UnaryOp(self, node):
        self.visit(node.operand)
        f = lambda x: ExpressionType(operator_to_lambda[type(node.op)], [x])
        self.combine(node, node.operand, unary_op=f)

    def visit_Lambda(self, node):
        assert False

    def visit_IfExp(self, node):
        [self.visit(n) for n in (node.body, node.orelse)]
        [self.combine(node, n) for n in (node.body, node.orelse)]

    def visit_Compare(self, node):
        self.generic_visit(node)
        self.result[node] = NamedType("bool")

    def visit_Call(self, node):
        self.visit(node.func)
        [self.visit(n) for n in node.args]
        user_module = modules['__user__']
        for alias in self.strict_aliases[node.func].aliases:
            # handle backward type dependencies from method calls
            if isinstance(alias, ast.Attribute):
                if isinstance(alias.value, ast.Name):
                    if (alias.value.id in modules and
                        alias.attr in modules[alias.value.id]):
                        aliased_fun = modules[alias.value.id][alias.attr]
                        if hasattr(aliased_fun, 'combiner'):
                            # aliased_fun.combiner(self, node)
                            # also generate all possible aliasing combinations
                            combinations = [filter(
                                None,
                                self.strict_aliases[arg].aliases.union({arg}))
                                for arg in node.args]
                            for new_args in itertools.product(*combinations):
                                aliased_fun.combiner(self,
                                        ast.Call(
                                            node.func,
                                            new_args,
                                            [],
                                            None,
                                            None)
                                        )
                else:
                    raise PythranSyntaxError(
                        "Unknown Attribute: `{0}'".format(alias.attr), node)
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
        value, attr = (node.value, node.attr)
        if value.id in modules and attr in modules[value.id]:
            self.result[node] = (DeclType(
                Val('{0}::{1}'.format(value.id, attr)))
                if modules[value.id][attr].isscalar()
                else DeclType(Val("{0}::proxy::{1}()".format(value.id, attr)))
                )
        else:
            raise PythranSyntaxError(
                "Unknown Attribute: `{0}'".format(node.attr), node)

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
            f = lambda t: ContentType(t)
        self.combine(node, node.value, unary_op=f)

    def visit_AssignedSubscript(self, node):
        if not isinstance(node.slice, ast.Slice):
            self.visit(node.slice)
            self.combine(node.value, node.slice,
                unary_op=lambda t: IndexableType(t), register=True)
            for alias in self.strict_aliases[node.value].aliases:
                self.combine(alias, node.slice,
                    unary_op=lambda t: IndexableType(t), register=True)

    def visit_Name(self, node):
        if node.id in self.name_to_nodes:
            for n in self.name_to_nodes[node.id]:
                self.combine(node, n)
        elif node.id in self.current_global_declarations:
            self.combine(node, self.current_global_declarations[node.id])
        elif node.id in builtin_constants:
            self.result[node] = NamedType(builtin_constants[node.id])
        elif node.id in modules["__builtins__"]:
            self.result[node] = NamedType("proxy::{0}".format(node.id))
        elif node.id in builtin_constructors:
            self.result[node] = NamedType("pythonic::constructor<{0}>".format(
                builtin_constructors[node.id]))
        else:
            self.result[node] = NamedType(node.id, {Weak})

    def visit_List(self, node):
        if node.elts:
            [self.visit(elt) for elt in node.elts]
            [self.combine(node, elt,
                unary_op=lambda x:ListType(x)) for elt in node.elts]
        else:
            self.result[node] = NamedType("core::empty_list")

    def visit_Set(self, node):
        if node.elts:
            [self.visit(elt) for elt in node.elts]
            [self.combine(node, elt,
                unary_op=lambda x:SetType(x)) for elt in node.elts]
        else:
            self.result[node] = NamedType("core::empty_set")

    def visit_Dict(self, node):
        if node.keys:
            [self.visit(elt) for elt in node.keys]
            [self.visit(elt) for elt in node.values]
            [self.combine(
                node,
                key,
                unary_op=lambda x:DictType(x, self.result[value]))
                for key, value in zip(node.keys, node.values)]
        else:
            self.result[node] = NamedType("core::empty_dict")

    def visit_ExceptHandler(self, node):
        if node.type and node.name:
            if not isinstance(node.type, ast.Tuple):
                self.result[node.type] = NamedType(
                    "core::{0}".format(node.type.id))
                self.combine(node.name, node.type, register=True)
        [self.visit(n) for n in node.body]

    def visit_Tuple(self, node):
        [self.visit(elt) for elt in node.elts]
        try:
            types = [self.result[elt] for elt in node.elts]
            self.result[node] = TupleType(types)
        except:
            pass  # not very harmonious with the combine method ...

    def visit_Index(self, node):
        self.visit(node.value)
        self.combine(node, node.value)

    def visit_arguments(self, node):
        for i, arg in enumerate(node.args):
            self.result[arg] = ArgumentType(i)
        [self.visit(n) for n in node.defaults]

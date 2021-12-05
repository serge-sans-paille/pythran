'''
This module performs the return type inference, according to symbolic types,
   It then reorders function declarations according to the return type deps.
    * type_all generates a node -> type binding
'''

from pythran.analyses import LazynessAnalysis, StrictAliases, YieldPoints
from pythran.analyses import LocalNodeDeclarations, Immediates, RangeValues
from pythran.config import cfg
from pythran.cxxtypes import TypeBuilder, ordered_set
from pythran.intrinsic import UserFunction, Class
from pythran.passmanager import ModuleAnalysis
from pythran.tables import operator_to_lambda, MODULES
from pythran.types.conversion import pytype_to_ctype
from pythran.types.reorder import Reorder
from pythran.utils import attr_to_path, cxxid, isnum, isextslice, ispowi

from collections import defaultdict
from functools import partial
import gast as ast
import operator
from functools import reduce
from copy import deepcopy
import types


class UnboundableRValue(Exception):
    pass


class Types(ModuleAnalysis):

    """ Infer symbolic type for all AST node. """

    def __init__(self):

        class TypeResult(dict):
            def __init__(self):
                self.builder = TypeBuilder()

            def copy(self):
                other = TypeResult()
                other.update(self.items())
                other.builder = self.builder
                return other

        self.result = TypeResult()
        self.builder = self.result.builder
        self.result["bool"] = self.builder.NamedType("bool")
        self.combiners = defaultdict(UserFunction)
        self.current_global_declarations = dict()
        self.max_recompute = 1  # max number of use to be lazy
        ModuleAnalysis.__init__(self, Reorder, StrictAliases, LazynessAnalysis,
                                Immediates, RangeValues)
        self.curr_locals_declaration = None

    def combined(self, *types):
        if len(types) == 1:
            return next(iter(types))
        return self.builder.CombinedTypes(*types)



    def prepare(self, node):
        """
        Initialise values to prepare typing computation.

        Reorder functions to avoid dependencies issues and prepare typing
        computation setting typing values for Pythonic functions.
        """

        def register(name, module):
            """ Recursively save function typing and combiners for Pythonic."""
            for fname, function in module.items():
                if isinstance(function, dict):
                    register(name + "::" + fname, function)
                else:
                    tname = 'pythonic::{0}::functor::{1}'.format(name, fname)
                    self.result[function] = self.builder.NamedType(tname)
                    self.combiners[function] = function
                    if isinstance(function, Class):
                        register(name + "::" + fname, function.fields)

        for mname, module in MODULES.items():
            register(mname, module)
        super(Types, self).prepare(node)

    def run(self, node):
        super(Types, self).run(node)
        for head in self.current_global_declarations.values():
            if head not in self.result:
                self.result[head] = "pythonic::types::none_type"
        return self.result

    def register(self, ptype):
        """register ptype as a local typedef"""
        # Too many of them leads to memory burst
        if len(self.typedefs) < cfg.getint('typing', 'max_combiner'):
            self.typedefs.append(ptype)
            return True
        return False

    def node_to_id(self, n, depth=()):
        if isinstance(n, ast.Name):
            return (n.id, depth)
        elif isinstance(n, ast.Subscript):
            if isinstance(n.slice, ast.Slice):
                return self.node_to_id(n.value, depth)
            else:
                index = n.slice.value if isnum(n.slice) else None
                return self.node_to_id(n.value, depth + (index,))
        # use alias information if any
        elif isinstance(n, ast.Call):
            for alias in self.strict_aliases[n]:
                if alias is n:  # no specific alias info
                    continue
                try:
                    return self.node_to_id(alias, depth)
                except UnboundableRValue:
                    continue
        raise UnboundableRValue()

    def isargument(self, node):
        """ checks whether node aliases to a parameter."""
        try:
            node_id, _ = self.node_to_id(node)
            return (node_id in self.name_to_nodes and
                    any(isinstance(n, ast.Name) and
                        isinstance(n.ctx, ast.Param)
                        for n in self.name_to_nodes[node_id]))
        except UnboundableRValue:
            return False

    def combine(self, node, othernode, op=None, unary_op=None, register=False,
                aliasing_type=False):
        """
        Change `node` typing with combination of `node` and `othernode`.

        Parameters
        ----------
        aliasing_type : bool
            All node aliasing to `node` have to be updated too.
        """
        if self.result[othernode] is self.builder.UnknownType:
            if node not in self.result:
                self.result[node] = self.builder.UnknownType
            return

        if aliasing_type:
            self.combine_(node, othernode, op or operator.add,
                          unary_op or (lambda x: x), register)
            for a in self.strict_aliases[node]:
                self.combine_(a, othernode, op or operator.add,
                              unary_op or (lambda x: x), register)
        else:
            self.combine_(node, othernode, op or operator.add,
                          unary_op or (lambda x: x), register)

    def combine_(self, node, othernode, op, unary_op, register):
        try:
            # This comes from an assignment,so we must check where the value is
            # assigned
            if register:
                try:
                    node_id, depth = self.node_to_id(node)
                    if depth:
                        node = ast.Name(node_id, ast.Load(), None, None)
                        former_unary_op = unary_op

                        # update the type to reflect container nesting
                        def merge_container_type(ty, index):
                            # integral index make it possible to correctly
                            # update tuple type
                            if isinstance(index, int):
                                kty = self.builder.NamedType(
                                        'std::integral_constant<long,{}>'
                                        .format(index))
                                return self.builder.IndexableContainerType(kty,
                                                                           ty)
                            else:
                                return self.builder.ContainerType(ty)

                        def unary_op(x):
                            return reduce(merge_container_type, depth,
                                          former_unary_op(x))

                        # patch the op, as we no longer apply op,
                        # but infer content
                        op = self.combined

                    self.name_to_nodes[node_id].append(node)
                except UnboundableRValue:
                    pass

            # only perform inter procedural combination upon stage 0
            if register and self.isargument(node) and self.stage == 0:
                node_id, _ = self.node_to_id(node)
                if node not in self.result:
                    self.result[node] = unary_op(self.result[othernode])
                assert self.result[node], "found an alias with a type"

                parametric_type = self.builder.PType(self.current,
                                                     self.result[othernode])
                if self.register(parametric_type):

                    current_function = self.combiners[self.current]

                    def translator_generator(args, op, unary_op):
                        ''' capture args for translator generation'''
                        def interprocedural_type_translator(s, n):
                            translated_othernode = ast.Name(
                                '__fake__', ast.Load(), None, None)
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
                                          op, unary_op, register=True,
                                          aliasing_type=True)
                            except NotImplementedError:
                                pass
                                # this may fail when the effective
                                # parameter is an expression
                            except UnboundLocalError:
                                pass
                                # this may fail when translated_node
                                # is a default parameter
                        return interprocedural_type_translator
                    translator = translator_generator(
                        self.current.args.args,
                        op, unary_op)  # deferred combination
                    current_function.add_combiner(translator)
            else:
                new_type = unary_op(self.result[othernode])
                UnknownType = self.builder.UnknownType
                if node not in self.result or self.result[node] is UnknownType:
                    self.result[node] = new_type
                else:
                    if isinstance(self.result[node], tuple):
                        raise UnboundableRValue
                    self.result[node] = op(self.result[node], new_type)

        except UnboundableRValue:
            pass

    def visit_FunctionDef(self, node):
        self.delayed_types = set()
        self.curr_locals_declaration = self.gather(
            LocalNodeDeclarations,
            node)
        self.current = node
        self.typedefs = list()
        self.name_to_nodes = defaultdict(ordered_set)
        for arg in node.args.args:
            self.name_to_nodes[arg.id].append(arg)

        self.yield_points = self.gather(YieldPoints, node)

        # two stages, one for inter procedural propagation
        self.stage = 0
        self.generic_visit(node)

        visited_names = {}
        for delayed_node in self.delayed_types:
            delayed_type = self.result[delayed_node]
            all_types = ordered_set(self.result[ty] for ty in
                                    self.name_to_nodes[delayed_node.id])
            final_type = self.combined(*all_types)
            delayed_type.final_type = final_type
            visited_names[delayed_node.id] = final_type

        # and one for backward propagation
        # but this step is generally costly
        if cfg.getboolean('typing', 'enable_two_steps_typing'):
            self.stage = 1
            self.generic_visit(node)

        # propagate type information through all aliases
        for name, nodes in self.name_to_nodes.items():
            all_types = ordered_set(self.result[ty] for ty in nodes)
            final_type = self.combined(*all_types)
            for n in nodes:
                if isinstance(self.result[n], self.builder.LType):
                    self.result[n].final_type = final_type
                else:
                    self.result[n] = final_type
        self.current_global_declarations[node.name] = node
        # return type may be unset if the function always raises
        return_type = self.result.get(
            node,
            self.builder.NamedType("pythonic::types::none_type"))

        self.result[node] = self.builder.Returnable(return_type), self.typedefs
        for k in self.gather(LocalNodeDeclarations, node):
            self.result[k] = self.get_qualifier(k)(self.result[k])

    def get_qualifier(self, node):
        lazy_res = self.lazyness_analysis[node.id]
        return (self.builder.Lazy
                if lazy_res <= self.max_recompute
                else self.builder.Assignable)

    def visit_Return(self, node):
        """ Compute return type and merges with others possible return type."""
        self.generic_visit(node)
        # No merge are done if the function is a generator.
        if not self.yield_points:
            assert node.value, "Values were added in each return statement."
            self.combine(self.current, node.value)

    def visit_Yield(self, node):
        """ Compute yield type and merges it with others yield type. """
        self.generic_visit(node)
        self.combine(self.current, node.value)

    def visit_Assign(self, node):
        self.visit(node.value)
        for t in node.targets:
            # We don't support subscript aliasing
            self.combine(t, node.value, register=True,
                         aliasing_type=isinstance(t, ast.Name))
            if t in self.curr_locals_declaration:
                self.result[t] = self.get_qualifier(t)(self.result[t])
            if isinstance(t, ast.Subscript):
                if self.visit_AssignedSubscript(t):
                    for alias in self.strict_aliases[t.value]:
                        fake = ast.Subscript(alias, t.slice, ast.Store())
                        self.combine(fake, node.value, register=True)

    def visit_AugAssign(self, node):
        self.visit(node.value)
        if isinstance(node.target, ast.Subscript):
            if self.visit_AssignedSubscript(node.target):
                for alias in self.strict_aliases[node.target.value]:
                    fake = ast.Subscript(alias, node.target.slice, ast.Store())
                    # We don't check more aliasing as it is a fake node.
                    self.combine(fake,
                                 node.value,
                                 lambda x, y: x + self.builder.ExpressionType(
                                     operator_to_lambda[type(node.op)],
                                     (x, y)),
                                 register=True)
        # We don't support aliasing on subscript
        self.combine(node.target, node.value,
                     lambda x, y: x + self.builder.ExpressionType(
                         operator_to_lambda[type(node.op)],
                         (x, y)),
                     register=True,
                     aliasing_type=isinstance(node.target, ast.Name))

    def visit_For(self, node):
        self.visit(node.iter)
        self.combine(node.target, node.iter,
                     unary_op=self.builder.IteratorContentType,
                     aliasing_type=True, register=True)
        for n in node.body + node.orelse:
            self.visit(n)

    def visit_BoolOp(self, node):
        """
        Merge BoolOp operand type.

        BoolOp are "and" and "or" and may return any of these results so all
        operands should have the combinable type.
        """
        # Visit subnodes
        self.generic_visit(node)
        # Merge all operands types.
        [self.combine(node, value) for value in node.values]

    def visit_BinOp(self, node):
        if ispowi(node):
            self.visit(node.op)
            self.visit(node.left)
            cty = "std::integral_constant<long, %s>" % (node.right.value)
            self.result[node.right] = self.builder.NamedType(cty)
        else:
            self.generic_visit(node)

        def F(x, y):
            return self.builder.ExpressionType(
                operator_to_lambda[type(node.op)], (x, y))

        self.combine(node, node.left, F)
        self.combine(node, node.right, F)

    def visit_UnaryOp(self, node):
        self.generic_visit(node)

        def f(x):
            return self.builder.ExpressionType(
                operator_to_lambda[type(node.op)], (x,))
        self.combine(node, node.operand, unary_op=f)

    def visit_IfExp(self, node):
        self.generic_visit(node)
        for n in (node.body, node.orelse):
            self.combine(node, n)

    def visit_Compare(self, node):
        self.generic_visit(node)
        all_compare = list(zip(node.ops, node.comparators))

        def unary_op(x, op=None):
            return self.builder.ExpressionType(
                operator_to_lambda[type(op)],
                (self.result[node.left], x))
        for op, comp in all_compare:
            self.combine(node, comp,
                         unary_op=partial(unary_op, op=op))

    def visit_Call(self, node):
        self.generic_visit(node)

        func = node.func

        for alias in self.strict_aliases[func]:
            # this comes from a bind
            if isinstance(alias, ast.Call):
                a0 = alias.args[0]
                # by construction of the bind construct
                assert len(self.strict_aliases[a0]) == 1
                bounded_function = next(iter(self.strict_aliases[a0]))
                fake_name = deepcopy(a0)
                fake_node = ast.Call(fake_name, alias.args[1:] + node.args,
                                     [])
                self.combiners[bounded_function].combiner(self, fake_node)

            # handle backward type dependencies from function calls
            else:
                self.combiners[alias].combiner(self, node)

        UnknownType = self.builder.UnknownType

        # recurring nightmare
        def last_chance():
            # maybe we can get saved if we have a hint about
            # the called function return type
            for alias in self.strict_aliases[func]:
                if alias is self.current and alias in self.result:
                    # great we have a (partial) type information
                    self.result[node] = self.result[alias]
                    return
            self.result[node] = UnknownType

        if self.result[node.func] is UnknownType:
            return last_chance()

        if any(self.result[arg] is UnknownType for arg in node.args):
            return last_chance()

        # special handler for getattr: use the attr name as an enum member
        if (isinstance(func, ast.Attribute) and func.attr == 'getattr'):
            def F(_):
                return self.builder.GetAttr(self.result[node.args[0]],
                                            node.args[1].value)
        # default behavior
        else:
            def F(f):
                return self.builder.ReturnType(
                    f, [self.result[arg] for arg in node.args])
        # op is used to drop previous value there
        self.combine(node, func, op=lambda x, y: y, unary_op=F)

    def visit_Constant(self, node):
        """ Set the pythonic constant type. """
        ty = type(node.value)
        if ty is str and len(node.value) == 1:
            sty = 'pythonic::types::chr'
        else:
            sty = pytype_to_ctype(ty)
        if node in self.immediates:
            sty = "std::integral_constant<%s, %s>" % (sty,
                                                      str(node.value).lower())
        self.result[node] = self.builder.NamedType(sty)

    def visit_Attribute(self, node):
        """ Compute typing for an attribute node. """
        obj, path = attr_to_path(node)
        # If no type is given, use a decltype
        if obj.isliteral():
            typename = pytype_to_ctype(obj.signature)
            self.result[node] = self.builder.NamedType(typename)
        else:
            path = '::'.join(map(cxxid, path)) + '{}'
            self.result[node] = self.builder.DeclType(path)

    def visit_Slice(self, node):
        """
        Set slicing type using continuous information if provided.

        Also visit subnodes as they may contains relevant typing information.
        """
        self.generic_visit(node)
        if node.step is None or (isnum(node.step) and node.step.value == 1):
            if all(self.range_values[p].low >= 0
                   for p in (node.lower, node.upper)):
                ntype = "pythonic::types::fast_contiguous_slice"
            else:
                ntype = "pythonic::types::contiguous_slice"
            self.result[node] = self.builder.NamedType(ntype)
        else:
            self.result[node] = self.builder.NamedType(
                'pythonic::types::slice')

    def visit_Subscript(self, node):
        self.visit(node.value)
        # type of a[1:2, 3, 4:1] is the type of: declval(a)(slice, long, slice)
        if isextslice(node.slice):
            self.visit(node.slice)

            def f(t):
                def et(a, *b):
                    return "{0}({1})".format(a, ", ".join(b))
                dim_types = tuple(self.result[d] for d in node.slice.elts)
                return self.builder.ExpressionType(et, (t,) + dim_types)
        elif isnum(node.slice) and node.slice.value >= 0:
            # type of a[2] is the type of an elements of a
            # this special case is to make type inference easier
            # for the back end compiler
            def f(t):
                return self.builder.ElementType(node.slice.value, t)
        else:
            # type of a[i] is the return type of the matching function
            self.visit(node.slice)

            def f(x):
                return self.builder.ExpressionType(
                    "{0}[{1}]".format,
                    (x, self.result[node.slice]))
        f and self.combine(node, node.value, unary_op=f)

    def visit_AssignedSubscript(self, node):
        if isinstance(node.slice, ast.Slice):
            return False
        elif isextslice(node.slice):
            return False
        else:
            self.visit(node.slice)
            self.combine(node.value, node.slice,
                         unary_op=self.builder.IndexableType,
                         aliasing_type=True, register=True)
            return True

    def delayed(self, node):
        fallback_type = self.combined(*[self.result[n] for n in
                                        self.name_to_nodes[node.id]])
        self.delayed_types.add(node)
        return self.builder.LType(fallback_type, node)

    def visit_Name(self, node):
        if node.id in self.name_to_nodes:
            self.result[node] = self.delayed(node)
        elif node.id in self.current_global_declarations:
            newtype = self.builder.NamedType(
                self.current_global_declarations[node.id].name)
            if node not in self.result:
                self.result[node] = newtype
        else:
            self.result[node] = self.builder.UnknownType

    def visit_List(self, node):
        """ Define list type from all elements type (or empty_list type). """
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=self.builder.ListType)
        else:
            self.result[node] = self.builder.NamedType(
                "pythonic::types::empty_list")

    def visit_Set(self, node):
        """ Define set type from all elements type (or empty_set type). """
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=self.builder.SetType)
        else:
            self.result[node] = self.builder.NamedType(
                "pythonic::types::empty_set")

    def visit_Dict(self, node):
        """ Define set type from all elements type (or empty_dict type). """
        self.generic_visit(node)
        if node.keys:
            for key, value in zip(node.keys, node.values):
                value_type = self.result[value]
                self.combine(node, key,
                             unary_op=partial(self.builder.DictType,
                                              of_val=value_type))
        else:
            self.result[node] = self.builder.NamedType(
                "pythonic::types::empty_dict")

    def visit_ExceptHandler(self, node):
        if node.type and node.name:
            if not isinstance(node.type, ast.Tuple):
                tname = self.builder.NamedType(
                    'pythonic::types::{0}'.format(node.type.attr))
                self.result[node.type] = tname
                self.combine(node.name, node.type, aliasing_type=True,
                             register=True)
        for n in node.body:
            self.visit(n)

    def visit_Tuple(self, node):
        self.generic_visit(node)
        types = [self.result[elt] for elt in node.elts]
        self.result[node] = self.builder.TupleType(types)

    def visit_arguments(self, node):
        for i, arg in enumerate(node.args):
            self.result[arg] = self.builder.ArgumentType(i)
        for n in node.defaults:
            self.visit(n)

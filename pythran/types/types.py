'''
This module performs the return type inference, according to symbolic types,
   It then reorders function declarations according to the return type deps.
    * type_all generates a node -> type binding
'''

from pythran.analyses import (LazynessAnalysis, StrictAliases, YieldPoints,
                              LocalNodeDeclarations)
from pythran.config import cfg
from pythran.cxxtypes import NamedType, ContainerType, PType, Assignable, Lazy
from pythran.cxxtypes import ExpressionType, IteratorContentType, ReturnType
from pythran.cxxtypes import GetAttr, DeclType, ElementType, IndexableType
from pythran.cxxtypes import Weak, ListType, SetType, DictType, TupleType
from pythran.cxxtypes import ArgumentType, Returnable, CombinedTypes
from pythran.intrinsic import UserFunction, MethodIntr, Class
from pythran.passmanager import ModuleAnalysis
from pythran.tables import operator_to_lambda, MODULES
from pythran.types.conversion import PYTYPE_TO_CTYPE_TABLE, pytype_to_ctype
from pythran.types.reorder import Reorder
from pythran.utils import attr_to_path
from pythran import metadata

from collections import defaultdict
from functools import partial
from numpy import ndarray
import ast
import operator


def extract_constructed_types(t):
    if isinstance(t, (list, ndarray)):
        return [pytype_to_ctype(t)] + extract_constructed_types(t[0])
    elif isinstance(t, set):
        return [pytype_to_ctype(t)] + extract_constructed_types(list(t)[0])
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return ([pytype_to_ctype(t)] +
                extract_constructed_types(tkey) +
                extract_constructed_types(tvalue))
    elif isinstance(t, tuple):
        return ([pytype_to_ctype(t)] +
                sum(map(extract_constructed_types, t), []))
    elif t == long:
        return [pytype_to_ctype(t)]
    elif t == str:
        return [pytype_to_ctype(t)]
    else:
        return []


class UnboundableRValue(Exception):
    pass


class Types(ModuleAnalysis):

    """ Infer symbolic type for all AST node. """

    def __init__(self):
        self.result = dict()
        self.result["bool"] = NamedType("bool")
        self.combiners = defaultdict(UserFunction)
        self.current_global_declarations = dict()
        self.max_recompute = 1  # max number of use to be lazy
        ModuleAnalysis.__init__(self, StrictAliases, LazynessAnalysis)
        self.curr_locals_declaration = None

    def prepare(self, node, ctx):
        """
        Initialise values to prepare typing computation.

        Reorder functions to avoid dependencies issues and prepare typing
        computation setting typing values for Pythonic functions.
        """
        self.passmanager.apply(Reorder, node, ctx)

        def register(name, module):
            """ Recursively save function typing and combiners for Pythonic."""
            for fname, function in module.iteritems():
                if isinstance(function, dict):
                    register(name + "::" + fname, function)
                else:
                    tname = 'pythonic::{0}::functor::{1}'.format(name, fname)
                    self.result[function] = NamedType(tname)
                    self.combiners[function] = function
                    if isinstance(function, Class):
                        register(name + "::" + fname, function.fields)

        for mname, module in MODULES.iteritems():
            register(mname, module)
        super(Types, self).prepare(node, ctx)

    def run(self, node, ctx):
        super(Types, self).run(node, ctx)
        final_types = self.result.copy()
        for head in self.current_global_declarations.itervalues():
            if head not in final_types:
                final_types[head] = "pythonic::types::none_type"
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
                    any([isinstance(n, ast.Name) and
                         isinstance(n.ctx, ast.Param)
                         for n in self.name_to_nodes[node_id]]))
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
            if register:    # this comes from an assignment,
                            # so we must check where the value is assigned
                node_id, depth = self.node_to_id(node)
                if depth > 0:
                    node = ast.Name(node_id, ast.Load())
                    former_unary_op = unary_op

                    # update the type to reflect container nesting
                    def unary_op(x):
                        return reduce(lambda t, n: ContainerType(t),
                                      xrange(depth), former_unary_op(x))

                    # patch the op, as we no longer apply op, but infer content
                    # but it's dangerous to combine with a weakling
                    def op(*types):
                        nonweaks = [t for t in types if not t.isweak()]
                        if len(nonweaks) == 1:
                            return nonweaks[0]
                        else:
                            return CombinedTypes(*nonweaks)

                self.name_to_nodes.setdefault(node_id, set()).add(node)

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
                    if node not in self.result:
                        self.result[node] = new_type
                    else:
                        self.result[node] = op(self.result[node], new_type)
        except UnboundableRValue:
            pass

    def visit_FunctionDef(self, node):
        self.curr_locals_declaration = self.passmanager.gather(
            LocalNodeDeclarations,
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
        return_type = self.result.get(node,
                                      NamedType("pythonic::types::none_type"))

        self.result[node] = (Returnable(return_type), self.typedefs)
        for k in self.passmanager.gather(LocalNodeDeclarations, node):
            self.result[k] = self.get_qualifier(k)(self.result[k])

    def get_qualifier(self, node):
        lazy_res = self.lazyness_analysis[node.id]
        return Lazy if lazy_res <= self.max_recompute else Assignable

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
                        fake = ast.Subscript(alias, t.value, ast.Store())
                        self.combine(fake, node.value, register=True)
            else:
                self.result[t].iscore = True

    def visit_AugAssign(self, node):
        self.visit(node.value)
        if isinstance(node.target, ast.Subscript):
            if self.visit_AssignedSubscript(node.target):
                for alias in self.strict_aliases[node.target.value]:
                    fake = ast.Subscript(alias, node.target.value, ast.Store())
                    # We don't check more aliasing as it is a fake node.
                    self.combine(fake,
                                 node.value,
                                 lambda x, y: x + ExpressionType(
                                     operator_to_lambda[type(node.op)],
                                     [x, y]),
                                 register=True)
        # We don't support aliasing on subscript
        self.combine(node.target, node.value,
                     lambda x, y: x + ExpressionType(
                         operator_to_lambda[type(node.op)],
                         [x, y]),
                     register=True,
                     aliasing_type=isinstance(node.target, ast.Name))

    def visit_For(self, node):
        self.visit(node.iter)
        self.combine(node.target, node.iter, unary_op=IteratorContentType,
                     aliasing_type=True, register=True)
        node.body and map(self.visit, node.body)
        node.orelse and map(self.visit, node.orelse)

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
        self.generic_visit(node)
        wl, wr = [self.result[x].isweak() for x in (node.left, node.right)]
        if(isinstance(node.op, ast.Add) and any([wl, wr]) and
           not all([wl, wr])):
            # assumes the + operator always has the same operand type
            # on left and right side
            F = operator.add
        else:
            def F(x, y):
                return ExpressionType(operator_to_lambda[type(node.op)],
                                      [x, y])

        fake_node = ast.Name("#", ast.Param())
        self.combine(fake_node, node.left, F)
        self.combine(fake_node, node.right, F)
        self.combine(node, fake_node)
        del self.result[fake_node]

    def visit_UnaryOp(self, node):
        self.generic_visit(node)

        def f(x):
            return ExpressionType(operator_to_lambda[type(node.op)], [x])
        self.combine(node, node.operand, unary_op=f)

    def visit_IfExp(self, node):
        self.generic_visit(node)
        [self.combine(node, n) for n in (node.body, node.orelse)]

    def visit_Compare(self, node):
        self.generic_visit(node)
        all_compare = zip(node.ops, node.comparators)

        def unary_op(x, op=None):
            return ExpressionType(
                operator_to_lambda[type(op)],
                [self.result[node.left], x])
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
                bounded_name = a0.id
                # by construction of the bind construct
                assert len(self.strict_aliases[a0]) == 1
                bounded_function = list(self.strict_aliases[a0])[0]
                fake_name = ast.Name(bounded_name, ast.Load())
                fake_node = ast.Call(fake_name, alias.args[1:] + node.args,
                                     [], None, None)
                self.combiners[bounded_function].combiner(self, fake_node)
                # force recombination of binded call
                for n in self.name_to_nodes[func.id]:
                    self.result[n] = ReturnType(self.result[alias.func],
                                                [self.result[arg]
                                                 for arg in alias.args])
            # handle backward type dependencies from function calls
            else:
                self.combiners[alias].combiner(self, node)

        # recurring nightmare
        isweak = any(self.result[n].isweak() for n in node.args + [func])
        if self.stage == 0 and isweak:
            # maybe we can get saved if we have a hint about
            # the called function return type
            for alias in self.strict_aliases[func]:
                if alias is self.current and alias in self.result:
                    # great we have a (partial) type information
                    self.result[node] = self.result[alias]
                    return

        # special handler for getattr: use the attr name as an enum member
        if (isinstance(func, ast.Attribute) and func.attr == 'getattr'):
            def F(_):
                return GetAttr(self.result[node.args[0]], node.args[1].s)
        # default behavior
        else:
            def F(f):
                return ReturnType(f, [self.result[arg] for arg in node.args])
        # op is used to drop previous value there
        self.combine(node, func, op=lambda x, y: y, unary_op=F)

    def visit_Num(self, node):
        """
        Set type for number.

        It could be int, long or float so we use the default python to pythonic
        type converter.
        """
        self.result[node] = NamedType(PYTYPE_TO_CTYPE_TABLE[type(node.n)])

    def visit_Str(self, node):
        """ Set the pythonic string type. """
        self.result[node] = NamedType(PYTYPE_TO_CTYPE_TABLE[str])

    def visit_Attribute(self, node):
        """ Compute typing for an attribute node. """
        obj, path = attr_to_path(node)
        assert not obj.isliteral() or obj.return_type, "Constants are known."
        # If no type is given, use a decltype
        if obj.return_type:
            self.result[node] = obj.return_type
        else:
            self.result[node] = DeclType('::'.join(path) + '{}')

    def visit_Slice(self, node):
        """
        Set slicing type using continuous information if provided.

        Also visit subnodes as they may contains relevant typing information.
        """
        self.generic_visit(node)
        if node.step is None or (isinstance(node.step, ast.Num) and
                                 node.step.n == 1):
            self.result[node] = NamedType('pythonic::types::contiguous_slice')
        else:
            self.result[node] = NamedType('pythonic::types::slice')

    def visit_Subscript(self, node):
        self.visit(node.value)
        # type of a[1:2, 3, 4:1] is the type of: declval(a)(slice, long, slice)
        if isinstance(node.slice, ast.ExtSlice):
            self.visit(node.slice)

            def f(t):
                def et(a, *b):
                    return "{0}({1})".format(a, ", ".join(b))
                dim_types = [self.result[d] for d in node.slice.dims]
                return ExpressionType(et, [t] + dim_types)
        elif (isinstance(node.slice, ast.Index) and
              isinstance(node.slice.value, ast.Num) and
              node.slice.value.n >= 0):
            # type of a[2] is the type of an elements of a
            # this special case is to make type inference easier
            # for the back end compiler
            def f(t):
                return ElementType(node.slice.value.n, t)
        else:
            # type of a[i] is the return type of the matching function
            self.visit(node.slice)

            def f(x):
                return ExpressionType("{0}[{1}]".format,
                                      [x, self.result[node.slice]])
        f and self.combine(node, node.value, unary_op=f)

    def visit_AssignedSubscript(self, node):
        if isinstance(node.slice, (ast.Slice, ast.ExtSlice)):
            return False
        else:
            self.visit(node.slice)
            self.combine(node.value, node.slice, unary_op=IndexableType,
                         aliasing_type=True, register=True)
            return True

    def visit_Name(self, node):
        if node.id in self.name_to_nodes:
            for n in self.name_to_nodes[node.id]:
                self.combine(node, n)
        elif node.id in self.current_global_declarations:
            self.combine(node, self.current_global_declarations[node.id])
        else:
            self.result[node] = NamedType(node.id, {Weak})

    def visit_List(self, node):
        """ Define list type from all elements type (or empty_list type). """
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=ListType)
        else:
            self.result[node] = NamedType("pythonic::types::empty_list")

    def visit_Set(self, node):
        """ Define set type from all elements type (or empty_set type). """
        self.generic_visit(node)
        if node.elts:
            for elt in node.elts:
                self.combine(node, elt, unary_op=SetType)
        else:
            self.result[node] = NamedType("pythonic::types::empty_set")

    def visit_Dict(self, node):
        """ Define set type from all elements type (or empty_dict type). """
        self.generic_visit(node)
        if node.keys:
            for key, value in zip(node.keys, node.values):
                value_type = self.result[value]
                self.combine(node, key,
                             unary_op=partial(DictType, of_value=value_type))
        else:
            self.result[node] = NamedType("pythonic::types::empty_dict")

    def visit_ExceptHandler(self, node):
        if node.type and node.name:
            if not isinstance(node.type, ast.Tuple):
                tname = NamedType(
                    'pythonic::types::{0}'.format(node.type.attr))
                self.result[node.type] = tname
                self.combine(node.name, node.type, aliasing_type=True,
                             register=True)
        map(self.visit, node.body)

    def visit_Tuple(self, node):
        self.generic_visit(node)
        types = [self.result[elt] for elt in node.elts]
        self.result[node] = TupleType(types)

    def visit_Index(self, node):
        self.generic_visit(node)
        self.combine(node, node.value)

    def visit_arguments(self, node):
        for i, arg in enumerate(node.args):
            self.result[arg] = ArgumentType(i)
        map(self.visit, node.defaults)

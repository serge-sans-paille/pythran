""" NormalizeStaticIf adds support for static guards. """

from pythran.analyses import (ImportedIds, IsAssigned, HasReturn,
                              StaticExpressions, HasStaticExpression)
from pythran.passmanager import Transformation
from pythran.syntax import PythranSyntaxError

import gast as ast
from copy import deepcopy


def outline(name, formal_parameters, out_parameters, stmts, has_return):
    args = ast.arguments(
        [ast.Name(fp, ast.Param(), None) for fp in formal_parameters],
        None, [], [], None, [])

    if isinstance(stmts, ast.expr):
        assert not out_parameters, "no out parameters with expr"
        fdef = ast.FunctionDef(name, args, [ast.Return(stmts)], [], None)
    else:
        fdef = ast.FunctionDef(name, args, stmts, [], None)

        # this is part of a huge trick that plays with delayed type inference
        # it basically computes the return type based on out parameters, and
        # the return statement is unconditionally added so if we have other
        # returns, there will be a computation of the output type based on the
        # __combined of the regular return types and this one The original
        # returns have been patched above to have a different type that
        # cunningly combines with this output tuple
        #
        # This is the only trick I found to let pythran compute both the output
        # variable type and the early return type. But hey, a dirty one :-/

        stmts.append(
            ast.Return(
                ast.Tuple(
                    [ast.Name(fp, ast.Load(), None) for fp in out_parameters],
                    ast.Load()
                )
            )
        )
        if has_return:
            pr = PatchReturn(stmts[-1])
            pr.visit(fdef)

    return fdef


class PatchReturn(ast.NodeTransformer):

    def __init__(self, guard):
        self.guard = guard

    def visit_Return(self, node):
        if node is self.guard:
            holder = "StaticIfNoReturn"
        else:
            holder = "StaticIfReturn"

        return ast.Return(
            ast.Call(
                ast.Attribute(
                    ast.Attribute(
                        ast.Name("__builtin__", ast.Load(), None),
                        "pythran",
                        ast.Load()),
                    holder,
                    ast.Load()), [node.value], []))


class NormalizeStaticIf(Transformation):

    def __init__(self):
        super(NormalizeStaticIf, self).__init__(StaticExpressions)

    def visit_Module(self, node):
        self.new_functions = []
        self.generic_visit(node)
        node.body.extend(self.new_functions)
        return node

    @staticmethod
    def make_fake(stmts):
        return ast.If(ast.Num(0), stmts, [])

    @staticmethod
    def make_dispatcher(static_expr, func_true, func_false,
                        imported_ids):
        dispatcher_args = [static_expr,
                           ast.Name(func_true.name, ast.Load(), None),
                           ast.Name(func_false.name, ast.Load(), None)]

        dispatcher = ast.Call(
            ast.Attribute(
                ast.Attribute(
                    ast.Name("__builtin__", ast.Load(), None),
                    "pythran",
                    ast.Load()),
                "static_if_",
                ast.Load()),
            dispatcher_args, [])

        actual_call = ast.Call(
            dispatcher,
            [ast.Name(ii, ast.Load(), None) for ii in imported_ids],
            [])

        return actual_call

    def true_name(self):
        return "$isstatic{}".format(len(self.new_functions) + 0)

    def false_name(self):
        return "$isstatic{}".format(len(self.new_functions) + 1)

    def visit_IfExp(self, node):
        self.generic_visit(node)

        if node.test not in self.static_expressions:
            return node

        imported_ids = sorted(self.passmanager.gather(ImportedIds,
                                                      node, self.ctx))

        func_true = outline(self.true_name(), imported_ids, [],
                            node.body, False)
        func_false = outline(self.false_name(), imported_ids, [],
                             node.orelse, False)
        self.new_functions.extend((func_true, func_false))

        actual_call = self.make_dispatcher(node.test, func_true,
                                           func_false, imported_ids)

        return actual_call

    def visit_If(self, node):
        self.generic_visit(node)
        if node.test not in self.static_expressions:
            return node

        imported_ids = self.passmanager.gather(ImportedIds, node, self.ctx)

        assigned_ids_left = set(
            self.passmanager.gather(IsAssigned, self.make_fake(node.body),
                                    self.ctx).keys())
        assigned_ids_right = set(
            self.passmanager.gather(IsAssigned, self.make_fake(node.orelse),
                                    self.ctx).keys())
        assigned_ids_both = assigned_ids_left.union(assigned_ids_right)

        imported_ids.update(i for i in assigned_ids_left
                            if i not in assigned_ids_right)
        imported_ids.update(i for i in assigned_ids_right
                            if i not in assigned_ids_left)
        imported_ids = sorted(imported_ids)

        assigned_ids = sorted(assigned_ids_both)

        true_has_return = self.passmanager.gather(HasReturn,
                                                  self.make_fake(node.body),
                                                  self.ctx)
        false_has_return = self.passmanager.gather(HasReturn,
                                                   self.make_fake(node.orelse),
                                                   self.ctx)

        has_return = true_has_return or false_has_return

        func_true = outline(self.true_name(), imported_ids, assigned_ids,
                            node.body, has_return)
        func_false = outline(self.false_name(), imported_ids, assigned_ids,
                             node.orelse, has_return)
        self.new_functions.extend((func_true, func_false))

        actual_call = self.make_dispatcher(node.test,
                                           func_true, func_false, imported_ids)

        expected_return = [ast.Name(ii, ast.Load(), None)
                           for ii in assigned_ids]

        self.update = True

        if has_return:
            n = len(self.new_functions)
            fast_return = [ast.Name("$status{}".format(n), ast.Load(), None),
                           ast.Name("$return{}".format(n), ast.Load(), None),
                           ast.Name("$cont{}".format(n), ast.Load(), None)]

            if expected_return:
                cont_ass = [ast.Assign(
                    [ast.Tuple(expected_return, ast.Store())],
                    ast.Name("$cont{}".format(n), ast.Load(), None))]
            else:
                cont_ass = []

            return [
                ast.Assign([ast.Tuple(fast_return, ast.Store())], actual_call),
                ast.If(ast.Name("$status{}".format(n), ast.Load(), None),
                       [ast.Return(
                           ast.Name("$return{}".format(n), ast.Load(), None))],
                       cont_ass)]
        elif expected_return:
            return ast.Assign([ast.Tuple(expected_return, ast.Store())],
                              actual_call)
        else:
            return ast.Expr(actual_call)


class SplitStaticExpression(Transformation):

    def __init__(self):
        super(SplitStaticExpression, self).__init__(StaticExpressions)

    def visit_Cond(self, node):
        '''
        generic expression splitting algorithm. Should work for ifexp and if
        using W(rap) and U(n)W(rap) to manage difference between expr and stmt

        The idea is to split a BinOp in three expressions:
            1. a (possibly empty) non-static expr
            2. an expr containing a static expr
            3. a (possibly empty) non-static expr
        Once split, the if body is refactored to keep the semantic,
        and then recursively split again, until all static expr are alone in a
        test condition
        '''

        NodeTy = type(node)
        if NodeTy is ast.IfExp:
            def W(x):
                return x

            def UW(x):
                return x
        else:
            def W(x):
                return [x]

            def UW(x):
                return x[0]

        has_static_expr = self.passmanager.gather(HasStaticExpression,
                                                  node.test, self.ctx)

        if not has_static_expr:
            return node

        if node.test in self.static_expressions:
            return node

        if not isinstance(node.test, ast.BinOp):
            return node

        before, static, after = [], [], []
        values = [node.test.right, node.test.left]

        def has_static_expression(n):
            return self.passmanager.gather(HasStaticExpression, n, self.ctx)

        while values and not has_static_expression(values[-1]):
            before.append(values.pop())

        while values and has_static_expression(values[-1]):
            static.append(values.pop())

        after = list(reversed(values))

        test_before = NodeTy(None, None, None)
        if before:
            test_before.test = before[0]

        test_static = NodeTy(None, None, None)
        if static:
            test_static.test = static[0]

        test_after = NodeTy(None, None, None)
        if after:
            test_after.test = after[0]

        if isinstance(node.test.op, ast.BitAnd):
            if after:
                test_after.body = deepcopy(node.body)
                test_after.orelse = deepcopy(node.orelse)
                test_after = W(test_after)
            else:
                test_after = deepcopy(node.body)

            if static:
                test_static.body = test_after
                test_static.orelse = deepcopy(node.orelse)
                test_static = W(test_static)
            else:
                test_static = test_after

            if before:
                test_before.body = test_static
                test_before.orelse = node.orelse
                node = test_before
            else:
                node = UW(test_static)

        elif isinstance(node.test.op, ast.BitOr):
            if after:
                test_after.body = deepcopy(node.body)
                test_after.orelse = deepcopy(node.orelse)
                test_after = W(test_after)
            else:
                test_after = deepcopy(node.orelse)

            if static:
                test_static.body = deepcopy(node.body)
                test_static.orelse = test_after
                test_static = W(test_static)
            else:
                test_static = test_after

            if before:
                test_before.body = deepcopy(node.body)
                test_before.orelse = test_static
                node = test_before
            else:
                node = UW(test_static)
        else:
            raise PythranSyntaxError("operator not supported in a static if",
                                     node)

        self.update = True
        return self.visit(node)

    visit_If = visit_IfExp = visit_Cond

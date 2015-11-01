""" NormalizeCompare turns complex compare into function calls. """

from pythran.analyses import ImportedIds
from pythran.passmanager import Transformation

import ast


class NormalizeCompare(Transformation):
    '''
    Turns multiple compare into a function with proper temporaries.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(a): return 0 < a + 1 < 3")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(NormalizeCompare, node)
    >>> print pm.dump(backend.Python, node)
    def foo(a):
        return foo_compare0(a)
    def foo_compare0(a):
        $0 = 0
        $1 = (a + 1)
        if ($0 < $1):
            pass
        else:
            return 0
        $2 = 3
        if ($1 < $2):
            pass
        else:
            return 0
        return 1
    '''

    def visit_Module(self, node):
        self.compare_functions = list()
        self.generic_visit(node)
        node.body.extend(self.compare_functions)
        self.update |= bool(self.compare_functions)
        return node

    def visit_FunctionDef(self, node):
        self.prefix = node.name
        self.generic_visit(node)
        return node

    def visit_Compare(self, node):
        node = self.generic_visit(node)
        if len(node.ops) > 1:
            # in case we have more than one compare operator
            # we generate an auxillary function
            # that lazily evaluates the needed parameters
            imported_ids = self.passmanager.gather(ImportedIds, node, self.ctx)
            imported_ids = sorted(imported_ids)
            binded_args = [ast.Name(i, ast.Load()) for i in imported_ids]

            # name of the new function
            forged_name = "{0}_compare{1}".format(self.prefix,
                                                  len(self.compare_functions))

            # call site
            call = ast.Call(ast.Name(forged_name, ast.Load()),
                            binded_args, [], None, None)

            # new function
            arg_names = [ast.Name(i, ast.Param()) for i in imported_ids]
            args = ast.arguments(arg_names, None, None, [])

            body = []  # iteratively fill the body (yeah, feel your body!)
            body.append(ast.Assign([ast.Name('$0', ast.Store())], node.left))
            for i, exp in enumerate(node.comparators):
                body.append(ast.Assign([ast.Name('${}'.format(i+1),
                                                 ast.Store())],
                                       exp))
                cond = ast.Compare(ast.Name('${}'.format(i), ast.Load()),
                                   [node.ops[i]],
                                   [ast.Name('${}'.format(i+1), ast.Load())])
                body.append(ast.If(cond,
                                   [ast.Pass()],
                                   [ast.Return(ast.Num(0))]))
            body.append(ast.Return(ast.Num(1)))

            forged_fdef = ast.FunctionDef(forged_name, args, body, [])
            self.compare_functions.append(forged_fdef)

            return call
        else:
            return node

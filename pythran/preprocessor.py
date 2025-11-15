'''
This modules contains various preprocessing passes before any other transformations

Those transformation are applied for any backend
'''

import beniget
import gast as ast

from pythran.tables import pythran_ward
from pythran.syntax import PythranSyntaxError

class GatherFunctionDefs(ast.NodeVisitor):
    '''
    Helper analysis to create a binding between function name and node

    >>> import gast as ast
    >>> node = ast.parse("def foo():\\n def bar(): pass\\n return bar")
    >>> gfd = GatherFunctionDefs()
    >>> gfd.visit(node)
    >>> list(gfd.defs.keys())
    ['foo', 'bar']
    '''
    def __init__(self):
        self.defs = {}
    def visit_FunctionDef(self, node):
        self.defs[node.name] = node
        self.generic_visit(node)

class MaterializePkg(ast.NodeTransformer):
    '''
    Helper transformation to fold package arguments

    It works for simple cases:

    >>> import gast as ast
    >>> mp = MaterializePkg({"foo": [(0, "numpy")]})
    >>> node = ast.parse("def foo(xp): return xp.cos(1)")
    >>> print(ast.unparse(mp.visit(node)))
    def foo(__pythran__folded_package_0):
        import numpy as xp
        return xp.cos(1)

    But it can also propagate through multiple calls, even when only materializing
    the argument of a single function:
    >>> mp = MaterializePkg({"foo": [(1, "numpy")]})
    >>> node = ast.parse("def foo(v, xp): return 1 + bar(v, 2, xp)\\ndef bar(x, y, z): return x + z.cos(y)")
    >>> print(ast.unparse(mp.visit(node)))
    def foo(v, __pythran__folded_package_1):
        return 1 + bar(v, 2, None)
    <BLANKLINE>
    def bar(x, y, __pythran__folded_package_2):
        import numpy as z
        return x + z.cos(y)
    '''

    def __init__(self, pkgs):
        self.pkgs = pkgs.copy()

    def visit_Module(self, node):
        self.duc = beniget.DefUseChains()
        self.duc.visit(node)
        self.udc = beniget.UseDefChains(self.duc)

        self.ancestors = beniget.Ancestors()
        self.ancestors.visit(node)

        gfd = GatherFunctionDefs()
        gfd.visit(node)
        self.fdefs = gfd.defs
        self.visited = set()

        return self.generic_visit(node)

    def visit_FunctionDef(self, node):
        self.visited.add(node.name)
        if node.name not in self.pkgs:
            return node

        pkg_renames = [(pkgname, node.args.args[i]) for i, pkgname in
                       self.pkgs[node.name]]

        extra_imports = []
        extra_functions_to_process = []
        for pkgname, arg in pkg_renames:
            arg_users = self.duc.chains[arg].users()
            add_import = False
            for user in arg_users:
                parents = self.ancestors.parents(user.node)
                if isinstance(parents[-1], ast.Attribute):
                    add_import =True
                elif isinstance(parents[-1], ast.Call):
                    call = parents[-1]
                    try:
                        user_index = call.args.index(user.node)
                    except IndexError:
                        raise PythranSyntaxError(
                                "Forwarding package as keyword parameter is not supported",
                                arg)
                    call.args[user_index] = ast.Constant(None, None)
                    call_defs = self.udc.chains[call.func]
                    if len(call_defs) != 1:
                        raise PythranSyntaxError(
                                "Forwarding package as argument of a dynamic call is not supported",
                                call.func)
                    call_def = call_defs[0].node
                    if not isinstance(call_def, ast.FunctionDef):
                        raise PythranSyntaxError(
                                "Forwarding package as argument of a dynamic call is not supported",
                                call.func)
                    key = user_index, pkgname
                    if call_def.name in self.pkgs:
                        # make sure the signature request is compatible with other specs
                        if key not in self.pkgs[call_def.id]:
                            raise PythranSyntaxError(
                                    f"Forwarding package as argument number {user_index + 1} of {call_def.id} is incompatible with export specification",
                                    call)
                    if call_def.name not in self.pkgs:
                        extra_functions_to_process.append(self.fdefs[call_def.name])
                        self.pkgs[call_def.name] = []
                    self.pkgs[call_def.name].append(key)
                else:
                    raise PythranSyntaxError(
                            f"Forwarding package can only be propagated through function call",
                            parents[-1])
            if add_import:
                extra_imports.append((pkgname, arg.id))

        node.body = [ast.Import([ast.alias(*extra_import)]) for extra_import in
                                extra_imports] + node.body
        for i, _ in self.pkgs[node.name]:
            node.args.args[i].id = f'{pythran_ward}_folded_package_{i}'

        # propagate package information
        for fdef in extra_functions_to_process:
            if fdef.name in self.visited:
                # we can't let the generic processing do its job there
                self.visit(fdef)

        # no recursive call, we cannot export inner functions
        return node

def materialize_pkgs(ir, pkgs):
    return MaterializePkg(pkgs).visit(ir)

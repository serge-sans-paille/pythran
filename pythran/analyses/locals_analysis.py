"""
Locals computes the value of locals()
"""

from pythran.passmanager import ModuleAnalysis
import pythran.metadata as md

import ast


class Locals(ModuleAnalysis):
    """
    Statically compute the value of locals() before each statement

    Yields a dictionary binding every node to the set of variable names defined
    *before* this node.

    Following snippet illustrates its behavior:
    >>> import ast
    >>> from pythran import passmanager
    >>> pm = passmanager.PassManager('test')
    >>> code = '''
    ... def b(n):
    ...     m = n + 1
    ...     def b(n):
    ...         return n + 1
    ...     return b(m)'''
    >>> tree = ast.parse(code)
    >>> l = pm.gather(Locals, tree)
    >>> l[tree.body[0].body[0]]
    set(['n'])
    >>> l[tree.body[0].body[1]]
    set(['b', 'm', 'n'])
    """

    def __init__(self):
        self.result = dict()
        self.locals = set()
        self.nesting = 0
        super(Locals, self).__init__()

    def generic_visit(self, node):
        super(Locals, self).generic_visit(node)
        if node not in self.result:
            self.result[node] = self.result[self.expr_parent]

    def store_and_visit(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        self.generic_visit(node)

    def visit_Module(self, node):
        self.expr_parent = node
        self.result[node] = self.locals
        map(self.visit, node.body)

    def visit_FunctionDef(self, node):
        # special case for nested functions
        if self.nesting:
            self.locals.add(node.name)
        self.nesting += 1
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        parent_locals = self.locals.copy()
        map(self.visit, node.args.defaults)
        self.locals.update(arg.id for arg in node.args.args)
        map(self.visit, node.body)
        self.locals = parent_locals
        self.nesting -= 1

    def visit_Assign(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        md.visit(self, node)
        self.visit(node.value)
        self.locals.update(t.id for t in node.targets
                           if isinstance(t, ast.Name))
        map(self.visit, node.targets)

    def visit_For(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        md.visit(self, node)
        self.visit(node.iter)
        self.locals.add(node.target.id)
        map(self.visit, node.body)
        map(self.visit, node.orelse)

    def visit_Import(self, node):
        self.result[node] = self.locals.copy()
        self.locals.update(alias.name for alias in node.names)

    def visit_ImportFrom(self, node):
        self.result[node] = self.locals.copy()
        self.locals.update(alias.name for alias in node.names)

    def visit_ExceptHandler(self, node):
        self.expr_parent = node
        self.result[node] = self.locals.copy()
        if node.name:
            self.locals.add(node.name.id)
        node.type and self.visit(node.type)
        map(self.visit, node.body)

    # statements that do not define a new variable
    visit_Return = store_and_visit
    visit_Yield = store_and_visit
    visit_TryExcept = store_and_visit
    visit_AugAssign = store_and_visit
    visit_Print = store_and_visit
    visit_While = store_and_visit
    visit_If = store_and_visit
    visit_Raise = store_and_visit
    visit_Assert = store_and_visit
    visit_Expr = store_and_visit
    visit_Pass = store_and_visit
    visit_Break = store_and_visit
    visit_Continue = store_and_visit

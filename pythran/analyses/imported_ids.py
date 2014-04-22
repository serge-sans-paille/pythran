"""
ImportedIds gathers identifiers imported by a node
"""
import ast
from globals_analysis import Globals
from locals_analysis import Locals
import pythran.metadata as md
from pythran.passmanager import NodeAnalysis


class ImportedIds(NodeAnalysis):
    """Gather ids referenced by a node and not declared locally"""
    def __init__(self):
        self.result = set()
        self.current_locals = set()
        self.is_list = False
        self.in_augassign = False
        super(ImportedIds, self).__init__(Globals, Locals)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store) and not self.in_augassign:
            self.current_locals.add(node.id)
        elif (node.id not in self.visible_globals
                and node.id not in self.current_locals):
            self.result.add(node.id)

    def visit_FunctionDef(self, node):
        self.current_locals.add(node.name)
        current_locals = self.current_locals.copy()
        self.current_locals.update(arg.id for arg in node.args.args)
        map(self.visit, node.body)
        self.current_locals = current_locals

    def visit_AnyComp(self, node):
        current_locals = self.current_locals.copy()
        map(self.visit, node.generators)
        self.visit(node.elt)
        self.current_locals = current_locals

    visit_ListComp = visit_AnyComp
    visit_SetComp = visit_AnyComp
    visit_DictComp = visit_AnyComp
    visit_GeneratorExp = visit_AnyComp

    def visit_Assign(self, node):
        #order matter as an assignation
        #is evaluted before being assigned
        md.visit(self, node)
        self.visit(node.value)
        map(self.visit, node.targets)

    def visit_AugAssign(self, node):
        self.in_augassign = True
        self.generic_visit(node)
        self.in_augassign = False

    def visit_Lambda(self, node):
        current_locals = self.current_locals.copy()
        self.current_locals.update(arg.id for arg in node.args.args)
        self.visit(node.body)
        self.current_locals = current_locals

    def visit_Import(self, node):
        self.current_locals.update(alias.name for alias in node.names)

    def visit_ImportFrom(self, node):
        self.current_locals.update(alias.name for alias in node.names)

    def visit_Attribute(self, node):
        pass

    def prepare(self, node, ctx):
        super(ImportedIds, self).prepare(node, ctx)
        if self.is_list:  # so that this pass can be called on list
            node = node.body[0]
        self.visible_globals = set(self.globals) - self.locals[node]

    def run(self, node, ctx):
        if isinstance(node, list):  # so that this pass can be called on list
            self.is_list = True
            node = ast.If(ast.Num(1), node, [])
        return super(ImportedIds, self).run(node, ctx)

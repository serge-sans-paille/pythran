'''
This module provides a few code analysis for the pythran language.
    * LocalDeclarations gathers declarations local to a node
    * GlobalDeclarations gathers top-level declarations
    * Locals computes the value of locals()
    * Globals computes the value of globals()
    * ImportedIds gathers identifiers imported by a node
    * ConstantExpressions gathers constant expression
    * Aliases gather aliasing informations
    * Identifiers gathers all identifiers used in a module
    * YieldPoints gathers all yield points from a node
    * BoundedExpressions gathers temporary objects
'''

from tables import modules, builtin_constants, builtin_constructors
import ast
import networkx as nx
import metadata
from passmanager import NodeAnalysis, FunctionAnalysis, ModuleAnalysis


##

class LocalDeclarations(NodeAnalysis):
    """Gathers all local symbols from a function"""
    def __init__(self):
        self.result=set()
        NodeAnalysis.__init__(self)

    def visit_Assign(self, node):
        for t in node.targets:
            assert isinstance(t, ast.Name) or isinstance(t, ast.Subscript)
            if isinstance(t, ast.Name) and not metadata.get(t, metadata.LocalVariable):
                self.result.add(t)

    def visit_For(self, node):
        assert isinstance(node.target, ast.Name)
        self.result.add(node.target)
        [ self.visit(n) for n in node.body ]

##
class GlobalDeclarations(ModuleAnalysis):
    """Generates a function name -> function node binding"""
    def __init__(self):
        self.result=dict()
        ModuleAnalysis.__init__(self)

    def visit_Import(self, node):
        for alias in node.names:
            self.result[alias.name]=alias

    def visit_ImportFrom(self, node):
        for alias in node.names:
            self.result[alias.asname if alias.asname else alias.name ]=alias
        return None

    def visit_FunctionDef(self, node):
        self.result[node.name]=node

##
class Locals(ModuleAnalysis):
    """Statically compute the value of locals() before each statement"""
    def __init__(self):
        self.result=dict()
        self.locals=set()
        ModuleAnalysis.__init__(self, GlobalDeclarations)
        # statements that do not define a new variable
        self.visit_Return=self.visit_Yield=self.visit_TryExcept=self.visit_AugAssign=self.visit_Print=self.visit_While=self.visit_If=self.Raise=self.Assert=self.Expr=self.Pass=self.Break=self.Continue=self.store_and_visit

    def generic_visit(self, node):
        ModuleAnalysis.generic_visit(self, node)
        if node not in self.result:
            self.result[node]=self.result[self.expr_parent]

    def store_and_visit(self, node):
        self.expr_parent=node
        self.result[node]=self.locals.copy()
        self.generic_visit(node)

    def visit_Module(self, node):
        self.expr_parent=node
        self.result[node]=self.locals
        [ self.visit(n) for n in node.body]

    def visit_FunctionDef(self, node):
        self.expr_parent=node
        self.result[node]=self.locals.copy()
        parent_locals=self.locals.copy()
        self.locals.update(arg.id for arg in node.args.args)
        [ self.visit(n) for n in node.body ]
        self.locals=parent_locals

    def visit_Assign(self, node):
        self.expr_parent=node
        self.result[node]=self.locals.copy()
        self.visit(node.value)
        self.locals.update(t.id for t in node.targets if isinstance(t, ast.Name))

    def visit_For(self, node):
        self.expr_parent=node
        self.result[node]=self.locals.copy()
        self.visit(node.iter)
        self.locals.add(node.target.id)
        [self.visit(n) for n in node.body]
        [self.visit(n) for n in node.orelse]

    def visit_Import(self, node):
        self.result[node]=self.locals.copy()
        self.locals.update(alias.name for alias in node.names)

    def visit_ImportFrom(self, node):
        self.result[node]=self.locals.copy()
        self.locals.update(alias.name for alias in node.names)

    def visit_excepthandler(self, node):
        self.expr_parent=node
        self.result[node]=self.locals.copy()
        if node.name: self.locals.add(node.name.id)
        [self.visit(n) for n in node.body]

##
class Globals(ModuleAnalysis):
    def __init__(self):
        self.result=dict()
        ModuleAnalysis.__init__(self, GlobalDeclarations)

    def visit(self, node):pass

    def run(self, node, ctx):
        ModuleAnalysis.run(self, node, ctx)
        return set(self.global_declarations.keys() + modules["__builtins__"].keys() + builtin_constants.keys() + builtin_constructors.keys())

##
class ImportedIds(NodeAnalysis):
    """Gather ids referenced by a node and not declared locally"""
    def __init__(self):
        self.result=set()
        self.current_locals=set()
        NodeAnalysis.__init__(self, Globals, Locals)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store): self.current_locals.add(node.id)
        elif node.id not in self.visible_globals and node.id not in self.current_locals: self.result.add(node.id)

    def visit_FunctionDef(self, node):
        self.current_locals.add(node.name)
        result=self.result.copy()
        current_locals=self.current_locals.copy()
        self.current_locals.update( arg.id for arg in node.args.args )
        [self.visit(n) for n in node.body]
        self.current_locals=current_locals

    def visit_AnyComp(self, node):
        current_locals=self.current_locals.copy()
        [ self.visit(n) for n in node.generators ]
        self.visit(node.elt)
        self.current_locals=current_locals

    def visit_ListComp(self, node): self.visit_AnyComp(node)
    def visit_SetComp(self, node): self.visit_AnyComp(node)
    def visit_GeneratorExp(self, node): self.visit_AnyComp(node)

    def visit_Lambda(self, node):
        current_locals=self.current_locals.copy()
        self.current_locals.update( arg.id for arg in node.args.args )
        self.visit(node.body)
        self.current_locals=current_locals

    def visit_Import(self, node):
        self.current_locals.update(alias.name for alias in node.names)

    def visit_ImportFrom(self, node):
        self.current_locals.update(alias.name for alias in node.names)

    def visit_Attribute(self, node):pass

    def run(self, node, ctx):
        if isinstance(node,list):
            node=ast.If(ast.Num(1),node,None)
        return NodeAnalysis.run(self, node, ctx)

    def run_visit(self, node):
        self.visible_globals=set(self.globals)-self.locals[node]
        NodeAnalysis.run_visit(self, node)

##
class ConstantExpressions(NodeAnalysis):
    """Identify constant expressions (dummy implementation)"""
    def __init__(self):
        self.result=set()
        NodeAnalysis.__init__(self, Globals, Locals)

    def add(self, node):
        self.result.add(node)
        return True

    def visit_BoolOp(self, node):
        return all(self.visit(n) for n in node.values) and self.add(node)

    def visit_BinOp(self, node):
        return all([self.visit(n) for n in (node.left, node.right)]) and self.add(node)

    def visit_UnaryOp(self, node):
        return self.visit(node.operand) and self.add(node)

    def visit_IfExp(self, node):
        return all([self.visit(n) for n in (node.test, node.body, node.orelse)]) and self.add(node)

    def visit_Dict(self, node):
        return all([self.visit(n) for n in (node.keys+node.values)]) and self.add(node)

    def visit_Set(self, node):
        return all([self.visit(n) for n in node.elts]) and self.add(node)

    def visit_Compare(self, node):
        return all([self.visit(n) for n in [node.left] + node.comparators]) and self.add(node)

    def visit_Call(self, node):
        return all([self.visit(n) for n in node.args + [node.func]]) and self.add(node)

    def visit_Num(self, node):
        return self.add(node)

    def visit_Str(self, node):
        return self.add(node)

    def visit_Subscript(self, node):
        return all([self.visit(n) for n in (node.value, node.slice)]) and self.add(node)

    def visit_Name(self, node):
        if node in self.locals:
            return node.id not in self.locals[node] and node.id in modules['__builtins__'] and modules['__builtins__'][node.id].isconst()
        else: # not in an expression
            return False

    def visit_Attribute(self, node):
        assert isinstance(node.value, ast.Name)
        return node.value.id in modules and modules[node.value.id][node.attr].isconst()

    def visit_List(self, node):
        return all([self.visit(n) for n in node.elts]) and self.add(node)

    def visit_Tuple(self, node):
        return all([self.visit(n) for n in node.elts]) and self.add(node)

    def visit_Slice(self, node):
        l=(self.visit(node.lower) if node.lower else True)
        u=(self.visit(node.upper) if node.upper else True )
        s=(self.visit(node.step) if node.step else True)
        return False

    def visit_Index(self, node):
        return self.visit(node.value) and self.add(node)
##
class OrderedGlobalDeclarations(ModuleAnalysis):
    '''Order all global functions according to their callgraph depth'''
    def __init__(self):
        self.result=dict()
        ModuleAnalysis.__init__(self, Aliases, GlobalDeclarations)

    def visit_FunctionDef(self,node):
        self.curr=node
        self.result[node]=set()
        self.curr_aliases=self.aliases[node]
        [ self.visit(n) for n in node.body ]

    def visit_Name(self,node):
        if node.id in self.global_declarations and isinstance(self.global_declarations[node.id], ast.FunctionDef):
            self.result[self.curr].add(self.global_declarations[node.id])
        elif node.id in self.curr_aliases:
            for alias in self.curr_aliases[node.id]:
                if alias in self.global_declarations and isinstance(alias, ast.FunctionDef):
                    self.result[self.curr].add(self.global_declarations[alias])

    def run(self, node, ctx):
        ModuleAnalysis.run(self, node, ctx)
        old_count=-1
        new_count=0
        while new_count != old_count:
            for k,v in self.result.iteritems():
                for f in list(v):
                    v.update(self.result[f])
            old_count=new_count
            new_count=reduce(lambda acc,s:acc+len(s),self.result.itervalues(),0)
        return sorted(self.result.iterkeys(), key=lambda s: len(self.result[s]), reverse=True)

##
class Aliases(ModuleAnalysis):
    """Gather aliasing informations across nodes."""
    def __init__(self):
        self.result=dict()
        ModuleAnalysis.__init__(self)
    def visit_FunctionDef(self, node):
        self.result[node]=dict()
        self.curr=self.result[node]
        for arg in node.args.args:
            self.curr[arg.id]={arg.id}
        [ self.visit(n) for n in node.body ]

    def visit_Assign(self, node):
        if isinstance(node.value, ast.Name):
            for t in node.targets:
                if isinstance(t, ast.Name):
                    if t.id not in self.curr: self.curr[t.id]=self.curr[node.value.id] if node.value.id in self.curr else {node.value.id}
                    else: self.curr[t.id].add(node.value.id)

##
class Identifiers(NodeAnalysis):
    """Gather all identifiers used throughout a node."""
    def __init__(self):
        self.result=set()
        NodeAnalysis.__init__(self)
    def visit_Name(self, node):
        self.result.add(node.id)
    def visit_FunctionDef(self, node):
        self.result.add(node.name)
        self.visit(node.args)
        [ self.visit(n) for n in node.body ]
    def visit_alias(self, node):
        if node.asname:
            self.result.add(node.asname)

##
class YieldPoints(FunctionAnalysis):
    '''Gathers all yield points of a generator, if any.'''
    def __init__(self):
        self.result=list() 
        FunctionAnalysis.__init__(self)

    def visit_Yield(self, node):
        self.result.append(node)

##
class BoundedExpressions(ModuleAnalysis):
    '''Gathers all nodes that are bound to an identifier.'''
    def __init__(self):
        self.result=set()
        ModuleAnalysis.__init__(self)

    def visit_Assign(self, node):
        self.result.add(node.value)
        if isinstance(node.value, ast.Subscript):
            self.result.add(node.value.slice)
        self.visit(node.value)
        [self.visit(n) for n in node.targets]

    def visit_Call(self, node):
        for n in node.args:
            if isinstance(n, ast.Subscript):
                self.result.add(n)

    def visit_Return(self, node):
        self.visit(node.value)
        if node.value:
            self.result.add(node.value)
            if isinstance(node.value, ast.Subscript):
                self.result.add(node.value.slice)


'''This module provides a few code analysis for the pythran language.
    * local_declarations gathers declarations local to a node
    * global_declarations gathers top-level declarations
    * imported_ids gathers identifiers imported by a node
    * purity_test computes whether functions write their parameters or not
    * constant_value evaluates a constant expression
    * type_aliasing gather aliasing informations
    * identifiers gathers all identifiers used in a module
    * yields gathers all yield points from a node
    * mark_temporaries flags temporary objects for further optimization
'''

from tables import modules, functions, builtin_constants
import ast
import networkx as nx
import metadata



class LocalDeclarations(ast.NodeVisitor):
    def __init__(self):
        self.local_symbols=set()
        self.first=True
    def visit_FunctionDef(self, node):
        if self.first:
            self.first=False
            [ self.visit(n) for n in node.body ]
            args = { arg.id for arg in node.args.args }
            self.local_symbols = { sym for sym in self.local_symbols if sym.id not in args }
        else:
            pass
    def visit_Assign(self, node):
        for t in node.targets:
            if isinstance(t, ast.Name):
                self.local_symbols.add(t)

    def visit_For(self, node):
        if isinstance(node.target, ast.Name):
            self.local_symbols.add(node.target)
        [ self.visit(n) for n in node.body ]

def local_declarations(node):
    """Gathers all local symbols from a function"""
    assert isinstance(node, ast.FunctionDef)
    ld = LocalDeclarations()
    ld.visit(node)
    return ld.local_symbols

##
class GlobalDeclarations(ast.NodeVisitor):
    def __init__(self):
        self.bindings=dict()

    def visit_Import(self, node):
        for alias in node.names:
            self.bindings[alias.name]=alias

    def visit_FunctionDef(self, node):
        self.bindings[node.name]=node

def global_declarations(node):
    """Generates a function name -> function node binding"""
    gd = GlobalDeclarations()
    gd.visit(node)
    return gd.bindings



##
class ImportedIds(ast.NodeVisitor):
    def __init__(self, global_declarations):
        self.references=set()
        self.global_declarations=set(global_declarations)
        self.skip=set()

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store):
            self.skip.add(node.id)
        elif node.id not in self.skip and node.id not in self.global_declarations:
            self.references.add(node.id)

    def visit_FunctionDef(self, node):
        local = ImportedIds(self.global_declarations)
        [local.visit(n) for n in node.body]
        local.references -= { arg.id for arg in node.args.args }
        self.global_declarations.add(node.name)
        self.references.update(local.references)

    def visit_AnyComp(self, node):
        local = ImportedIds(self.global_declarations)
        [ local.visit(n) for n in node.generators ]
        local.visit(node.elt)
        self.references.update(local.references)

    def visit_Attribute(self, node):
        assert isinstance(node.value, ast.Name)
        assert node.value.id in modules
        pass

    def visit_ListComp(self, node): self.visit_AnyComp(node)

    def visit_SetComp(self, node): self.visit_AnyComp(node)

    def visit_GeneratorExp(self, node): self.visit_AnyComp(node)

    def visit_Lambda(self, node):
        local = ImportedIds(self.global_declarations)
        local.visit(node.body)
        local.references -= { arg.id for arg in node.args.args }
        self.references.update(local.references)

    def visit_Import(self, node):
        self.global_declarations.update({ alias.name:None for alias in node.names})

    def visit_ImportFrom(self, node):
        self.global_declarations.update({ alias.name:None for alias in node.names})

def imported_ids(node, global_declarations):
    """Gather ids referenced by a node and not declared locally"""
    r = ImportedIds(global_declarations)
    if isinstance(node,list):
        node=ast.If(ast.Num(1),node,None)
    r.visit(node)
    #*** expand all modules here
    return { ref for ref in r.references } - set(modules["__builtins__"].keys()+builtin_constants.keys())

##
class WrittenAreas(ast.NodeVisitor):
    def __init__(self):
        self.written_areas=set()
        self.aliases=dict()
        self.deps=set()

    def recursievely_gather_aliases(self, id, target):
        if isinstance(target, ast.Name):
            self.aliases[ id ].add(target.id)
        elif isinstance(target, ast.Subscript):
            self.recursievely_gather_aliases(id, target.value)

    def visit_FunctionDef(self, node):
        self.aliases={ arg.id:{arg.id} for arg in node.args.args }
        [ self.visit(b) for b in node.body ]

    def visit_Assign(self, node):
        all_parameters=reduce(set.union, [ s for s in self.aliases.itervalues() ], set() )
        if isinstance(node.value, ast.Name) and node.value.id in all_parameters:
            for target in node.targets:
                self.recursievely_gather_aliases(node.value.id, target)
        else:
            [self.visit(t) for t in node.targets]
        self.visit(node.value)

    def visit_AugAssign(self, node):
        all_parameters=reduce(set.union, [ s for s in self.aliases.itervalues() ], set() )
        if isinstance(node.value, ast.Name) and node.value.id in all_parameters:
            self.recursievely_gather_aliases(node.value.id, node.target)
        else:
            self.visit(node.target)
        self.visit(node.value)

    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store):
            for aliases in self.aliases.itervalues():
                if node.id in aliases:
                    self.written_areas.update(aliases)

    def visit_Subscript(self, node):
        if isinstance(node.ctx, ast.Store):
            tmp = node.value
            while isinstance(tmp, ast.Subscript):
                tmp=tmp.value
            if not isinstance(tmp, ast.Name):
                raise NotImplementedError("assigning to a subscript whose value is not an identifier but an '{0}'".format(type(tmp)))
            for aliases in self.aliases.itervalues():
                if tmp.id in aliases:
                    self.written_areas.update(aliases)

    def visit_Call(self, node):
        def call_to_id(n):
            '''extension for imported functions'''
            if isinstance(n, ast.Name):
                return n.id
            elif isinstance(n, ast.Attribute) and isinstance(n.value, ast.Name):
                return "{0}::{1}".format(n.value.id, n.attr)
            else:
                print ast.dump(node)
                assert False
        call_id = call_to_id(node.func)
        [self.visit(arg) for arg in node.args]
        imported_areas=imported_ids(node, dict())
        imported_areas.difference_update({ call_id })
        all_parameters=reduce(set.union, [ s for s in self.aliases.itervalues() ], set() )
        if not imported_areas.isdisjoint(all_parameters):
            self.deps.add(call_id)


def written_areas(node):
    wv = WrittenAreas()
    wv.visit(node)
    return wv.written_areas, wv.deps

class PurityTest(ast.NodeVisitor):
    def __init__(self):
        self.pure=nx.DiGraph()

    def visit_Module(self, node):
        [self.visit(n) for n in node.body ]
        painted=1
        while painted:
            painted=0
            for fun in self.pure:
                for s in self.pure.successors(fun):
                    if not self.pure.node[s]["pure"] and self.pure.node[fun]["pure"]:
                        painted+=1
                        self.pure.node[fun]["pure"]=False

    def visit_Lambda(self, node):
        self.visit_FunctionDef(self,node)

    def visit_FunctionDef(self, node):
        weffects, wdeps = written_areas(node)
        imported_areas = imported_ids(node.body,dict())
        self.pure.add_node(node.name, pure=(imported_areas.isdisjoint(weffects)))
        [self.pure.add_node(wd, pure="unknown") for wd in wdeps if wd not in self.pure]
        [ self.pure.add_edge(node.name, wd) for wd in wdeps ]

def purity_test(node):
    """Returns a function_name -> Bool mapping where True means that the function does not write any of its parameter."""
    pt=PurityTest()
    pt.visit(node)
    #nx.write_dot(pt.pure,"pure.dot")
    #for p in pt.pure:
    #    print p, "is pure?", pt.pure.node[p]["pure"] 
    return { p for p in pt.pure if pt.pure.node[p]["pure"] }

##
class ConstantValue(ast.NodeVisitor):
    def visit_Num(self, node):
        return node.n
    def visit_Name(self, node):
        raise RuntimeError()
    def visit_Index(self, node):
        return self.visit(node.value)

def constant_value(node):
    """returns the numerical value of a constant expression."""
    cv= ConstantValue().visit(node)
    if cv!=None : return cv 
    else: raise RuntimeError()

##
class Callees(ast.NodeVisitor):
    def __init__(self, name_to_node):
        self.name_to_node=name_to_node
        self.callees={ n:set() for n in name_to_node.itervalues() }
        self.aliases={}

    def visit_FunctionDef(self,node):
        self.curr=node
        [ self.visit(n) for n in node.body ]

    def visit_Assign(self, node):
        if isinstance(node.value, ast.Name) and node.value.id in self.name_to_node:
            for t in node.targets: # aliasing handling is not that good :(
                if isinstance(t, ast.Name):
                    if not t.id in self.aliases: self.aliases[t.id]=set()
                    self.aliases[t.id].add(node.value.id)
        [self.visit(t) for t in node.targets]
        self.visit(node.value)

    def visit_Name(self,node):
        if node.id in self.name_to_node:
            self.callees[self.curr].add(self.name_to_node[node.id])
        elif node.id in self.aliases:
            for alias in self.aliases[node.id]:
                self.callees[self.curr].add(self.name_to_node[alias])

def ordered_global_declarations(node):
    '''order all global functions according to their callgraph depth'''
    c=Callees(global_declarations(node))
    c.visit(node)
    old_count=-1
    new_count=0
    while new_count != old_count:
        for k,v in c.callees.iteritems():
            for f in list(v):
                v.update(c.callees[f])
        old_count=new_count
        new_count=reduce(lambda acc,s:acc+len(s),c.callees.itervalues(),0)
    return sorted(c.callees.iterkeys(), key=lambda s: len(c.callees[s]), reverse=True)

##
class Aliasing(ast.NodeVisitor):
    def __init__(self):
        self.aliases=dict()
    def visit_FunctionDef(self, node):
        self.aliases[node]=dict()
        self.curr=self.aliases[node]
        for arg in node.args.args:
            self.curr[arg.id]={arg.id}
        [ self.visit(n) for n in node.body ]

    def visit_Assign(self, node):
        if isinstance(node.value, ast.Name):
            for t in node.targets:
                if isinstance(t, ast.Name):
                    if t.id not in self.curr: self.curr[t.id]=self.curr[node.value.id] if node.value.id in self.curr else {node.value.id}
                    else: self.curr[t.id].add(node.value.id)

def type_aliasing(node):
    """Gather aliasing informations across nodes"""
    a=Aliasing()
    a.visit(node)
    return a.aliases

##
class Identifiers(ast.NodeVisitor):
    def __init__(self):
        self.identifiers=set()
    def visit_Name(self, node):
        self.identifiers.add(node.id)
    def visit_FunctionDef(self, node):
        self.identifiers.add(node.name)
        self.visit(node.args)
        [ self.visit(n) for n in node.body ]
    def visit_alias(self, node):
        if node.asname:
            self.identifiers.add(node.asname)

def identifiers(node):
    """Gathers all identifiers used throughout the node."""
    ids=Identifiers()
    ids.visit(node)
    return ids.identifiers

##
class Yields(ast.NodeVisitor):
    def __init__(self):
        self.yields=list() 

    def visit_Yield(self, node):
        self.yields.append(node)

def yields(node):
    '''Gathers all yield points of a generator, if any'''
    assert isinstance(node, ast.FunctionDef)
    ylds=Yields()
    ylds.visit(node)
    return ylds.yields
##
class FlagTemporaries(ast.NodeVisitor):
    def visit_Assign(self, node):
        metadata.add(node.value, metadata.NotTemporary())
        if isinstance(node.value, ast.Subscript):
            metadata.add(node.value.slice, metadata.NotTemporary())
        self.visit(node.value)
        [self.visit(n) for n in node.targets]

    def visit_Return(self, node):
        self.visit(node.value)
        if node.value:
            metadata.add(node.value, metadata.NotTemporary())
            if isinstance(node.value, ast.Subscript):
                metadata.add(node.value.slice, metadata.NotTemporary())

def flag_temporaries(node):
    FlagTemporaries().visit(node)

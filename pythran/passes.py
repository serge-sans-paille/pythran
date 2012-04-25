from tables import operator_to_lambda, modules
import ast
import re

##
class DeclarationDependencies(ast.NodeVisitor):
    """ Gather name dependencies froma  function """
    def __init__(self, name):
        self.deps=set()
        self.name=name
    def visit_Name(self, node):
        if self.name != node.id:
            self.deps.add(node.id)

class ForwardDeclarations(ast.NodeVisitor):
    """ Gather declared function names """
    def __init__(self):
        self.declarations=dict()
    def visit_FunctionDef(self, node):
        dd=DeclarationDependencies(node.name)
        [dd.visit(n) for n in node.body]
        self.declarations[node.name]=dd.deps

class ReorderModule(ast.NodeVisitor):
    """ reorder the function declarations in a module"""
    def __init__(self, ordering):
        self.ordering= { v:k for k,v in enumerate(ordering) }

    def visit_Module(self, node):
        nbody = list()
        fdef = [ None for x in xrange(len(self.ordering)) ]
        for n in node.body:
            if not isinstance(n, ast.FunctionDef):
                nbody.append(n)
            else:
                fdef[self.ordering[n.name]]=n
        node.body = nbody + fdef

def forward_declarations(node):
    fd = ForwardDeclarations()
    fd.visit(node)
    for f,deps in fd.declarations.iteritems():
        deps.intersection_update(set(fd.declarations.iterkeys()))
    declarations = list()
    prev=len(fd.declarations)
    while fd.declarations:
        for f,deps in fd.declarations.items():
            if not deps.difference(declarations):
                declarations.append(f)
                fd.declarations.pop(f)
                break
        assert prev > len(fd.declarations)
        prev=len(fd.declarations)

    ReorderModule(declarations).visit(node)

    return set(declarations)


##
class ImportedIds(ast.NodeVisitor):
    """ Gather ids referenced by a node """
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

    def visit_ListComp(self, node):
        local = ImportedIds(self.global_declarations)
        [ local.visit(n) for n in node.generators ]
        local.visit(node.elt)
        self.references.update(local.references)

    def visit_Lambda(self, node):
        local = ImportedIds(self.global_declarations)
        local.visit(node.body)
        local.references -= { arg.id for arg in node.args.args }
        self.references.update(local.references)

def imported_ids(node, global_declarations):
    r = ImportedIds(global_declarations)
    if isinstance(node,list):
        node=ast.If(ast.Num(1),node,None)
    r.visit(node)
    #*** expand all modules here
    return r.references - set(modules["__builtins__"].keys()+[ "True", "False" ])

##
class WrittenAreas(ast.NodeVisitor):
    def __init__(self):
        self.written_areas=set()
    def visit_Name(self, node):
        if isinstance(node.ctx, ast.Store):
            self.written_areas.add(node.id)

    def visit_Subscript(self, node):
        if isinstance(node.ctx, ast.Store):
            tmp = node.value
            while isinstance(tmp, ast.Subscript):
                tmp=tmp.value
            if not isinstance(tmp, ast.Name):
                raise NotImplementedError("assigning to a subscript whose value is not an identifier but an '{0}'".format(type(tmp)))
            self.written_areas.add(tmp.id)

def written_areas(node):
    wv = WrittenAreas()
    wv.visit(node)
    return wv.written_areas

class PurityTest(ast.NodeVisitor):
    """ Gathers function purity information """
    def __init__(self):
        self.pure=dict()

    def visit_Lambda(self, node):
        self.visit_FunctionDef(self,node)

    def visit_FunctionDef(self, node):
        weffects = written_areas(node)
        imported_areas = imported_ids(node.body,dict())
        written_imported_areas= imported_areas.intersection(weffects)
        self.pure[node]=written_imported_areas


def purity_test(node):
    pt=PurityTest()
    pt.visit(node)
    return pt.pure

##
class TypeSubstitution(ast.NodeVisitor):
    """ Generate a typed expression suitable for declval call from an expression """
    def __init__(self, typedefs):
        self.typedefs=typedefs

    def visit_Name(self, node):
        assert node.id in self.typedefs
        return "std::declval< {0} >()".format(self.typedefs[node][ 0 if self.typedefs[node][1].startswith("expression_type") else 1 ])

    def visit_Index(self, node):
        return self.visit(node.value)

    def visit_Subscript(self, node):
        value = self.visit(node.value)
        slice = self.visit(node.slice)
        is_constant_expression = lambda s: not re.sub(r'[+*/\-0-9]','',s)
        if is_constant_expression(slice):
            return "std::get<{0}>({1})".format(slice, value)
        else:
            return "{1}[{0}]".format(slice, value)

    def visit_Num(self, node):
        return str(node.n)

    def visit_BinOp(self, node):
        left = self.visit(node.left)
        right= self.visit(node.right)
        op = operator_to_lambda[type(node.op)]
        return op(left,right)

def type_substitution(node, typedefs):
    return TypeSubstitution(typedefs).visit(node)

##
class ConvertToTuple(ast.NodeTransformer):
    def __init__(self, tuple_id, renamings):
        self.tuple_id=tuple_id
        self.renamings=renamings

    def visit_Name(self, node):
        if node.id in self.renamings:
            nnode=reduce(lambda x,y: ast.Subscript(x, ast.Index(ast.Num(y)), ast.Load()), self.renamings[node.id], ast.Name(self.tuple_id, ast.Load()))
            nnode.ctx=node.ctx
            return nnode
        return node

def convert_to_tuple(node, tuple_id, renamings):
    return ConvertToTuple(tuple_id, renamings).visit(node)

class NormalizeTuples(ast.NodeTransformer):
    tuple_name = "__tuple"
    def __init__(self):
        self.counter=0

    def traverse_tuples(self, node, state, renamings):
        if isinstance(node, ast.Name):
            if state: renamings[node.id] = state
        elif isinstance(node, ast.Tuple):
            [self.traverse_tuples(n, state + (i,), renamings) for i,n in enumerate(node.elts)]
        else:
            raise NotImplementedError

    """ Remove implicit tuple -> variable conversion."""
    def visit_comprehension(self, node):
        renamings=dict()
        self.traverse_tuples(node.target,(), renamings)
        if renamings:
            self.counter+=1
            return "{0}{1}".format(NormalizeTuples.tuple_name, self.counter), renamings
        else:
            return None

    def visit_ListComp(self, node):
        generators = [ self.visit(n) for n in node.generators ]
        nnode = node
        for i, g in enumerate(generators):
            if g:
                gtarget = "{0}{1}".format(g[0], i)
                nnode.generators[i].target=ast.Name(gtarget, nnode.generators[i].target.ctx)
                nnode = convert_to_tuple(nnode, gtarget, g[1])
        node.elt=nnode.elt
        node.generators=nnode.generators
        return node

    def visit_Assign(self, node):
        extra_assign = [node]
        for i,t in enumerate(node.targets):
            if isinstance(t, ast.Tuple):
                renamings=dict()
                self.traverse_tuples(t,(), renamings)
                if renamings:
                    self.counter+=1
                    gtarget = "{0}{1}{2}".format(NormalizeTuples.tuple_name, self.counter, i)
                    node.targets[i]=ast.Name(gtarget, node.targets[i].ctx)
                    for rename,state in sorted(renamings.iteritems()):
                        nnode=reduce(lambda x,y: ast.Subscript(x, ast.Index(ast.Num(y)), ast.Load()), state, ast.Name(gtarget, ast.Load()))
                        extra_assign.append(ast.Assign([ast.Name(rename,ast.Store())], nnode))
        return extra_assign

def normalize_tuples(node):
    NormalizeTuples().visit(node)

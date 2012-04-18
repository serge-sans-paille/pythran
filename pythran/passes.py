from tables import operator_to_lambda
import ast

##
class ForwardDeclarations(ast.NodeVisitor):
    """ Gather declared function names """
    def __init__(self):
        self.declarations=dict()
    def visit_FunctionDef(self, node):
        self.deps=set()
        self.name=node.name
        [self.visit(n) for n in node.body]
        self.declarations[node.name]=self.deps

    def visit_Name(self, node):
        if self.name != node.id:
            self.deps.add(node.id)

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
class ReferencedIds(ast.NodeVisitor):
    """ Gather ids referenced by a node """
    def __init__(self):
        self.references=set()

    def visit_Name(self, node):
        self.references.add(node.id)
def referenced_ids(node):
    r = ReferencedIds()
    r.visit(node)
    return r.references

##
class TypeSubstitution(ast.NodeVisitor):
    """ Generate a typed expression suitable for declval call from an expression """
    def __init__(self, typedefs):
        self.typedefs=typedefs

    def visit_Name(self, node):
        assert node.id in self.typedefs
        return "std::declval< {0} >()".format(self.typedefs[node][1])

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
            nnode=reduce(lambda x,y: ast.Subscript(x, ast.Index(ast.Num(y)), ast.Load), self.renamings[node.id], ast.Name(self.tuple_id, ast.Load))
            nnode.ctx=node.ctx
            return nnode
        return node

def convert_to_tuple(node, tuple_id, renamings):
    return ConvertToTuple(tuple_id, renamings).visit(node)

class NormalizeTuples(ast.NodeVisitor):
    """ Remove implicit tuple -> variable conversion."""
    def visit_comprehension(self, node):
        def traverse_tuples(node, state, renamings):
            if isinstance(node, ast.Name):
                if state: renamings[node.id] = state
            elif isinstance(node, ast.Tuple):
                [traverse_tuples(n, state + (i,), renamings) for i,n in enumerate(node.elts)]
            else:
                raise NotImplementedError
        renamings=dict()
        traverse_tuples(node.target,(), renamings)
        return ("__tuple", renamings ) if renamings else None

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


def normalize_tuples(node):
    NormalizeTuples().visit(node)

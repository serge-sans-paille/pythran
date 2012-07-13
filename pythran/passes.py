'''This modules contains code transformation to make your way from python code to pythran code
    * convert_to_tuple removes implicite variable -> tuple conversion
    * remove_comprehension turns list comprehension into function calls
    * remove_nested_functions turns nested function into top-level functions
    * remove_lambdas turns lambda into regular functions
    * parallelize_maps make some map calls parallel
    * normalize_return adds return statement where relevant
    * normalize_identifiers prevents conflicts with c++ keywords
    * unshadow_parameters prevents the shadow parameter phenomenon
'''

from analysis import imported_ids, purity_test, global_declarations, identifiers
from tables import methods, attributes, cxx_keywords
import metadata
import ast
import re

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
        elif isinstance(node, ast.Subscript):
            if state:
                renamings[node] = state
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
            return node

    def visit_ListComp(self, node):
        self.generic_visit(node.elt)
        generators = [ self.visit(n) for n in node.generators ]
        nnode = node
        for i, g in enumerate(generators):
            if isinstance(g,tuple):
                gtarget = "{0}{1}".format(g[0], i)
                nnode.generators[i].target=ast.Name(gtarget, nnode.generators[i].target.ctx)
                nnode = convert_to_tuple(nnode, gtarget, g[1])
        node.elt=nnode.elt
        node.generators=nnode.generators
        return node

    def visit_Lambda(self, node):
        self.generic_visit(node)
        for i,arg in enumerate(node.args.args):
            renamings=dict()
            self.traverse_tuples(arg, (), renamings)
            if renamings:
                self.counter+=1
                newname="{0}{1}".format(NormalizeTuples.tuple_name, self.counter)
                node.args.args[i]=ast.Name(newname, ast.Param())
                node.body=convert_to_tuple(node.body, newname, renamings)
        return node


    def visit_Assign(self, node):
        self.generic_visit(node)
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
                        if isinstance(rename, str):
                            extra_assign.append(ast.Assign([ast.Name(rename,ast.Store())], nnode))
                        else:
                            extra_assign.append(ast.Assign([rename], nnode))
        return extra_assign

    def visit_For(self, node):
        self.generic_visit(node)
        target = node.target
        if isinstance(target,  ast.Tuple):
                renamings=dict()
                self.traverse_tuples(target,(), renamings)
                if renamings:
                    self.counter+=1
                    newname = "{0}{1}".format(NormalizeTuples.tuple_name, self.counter)
                    node.target=ast.Name(newname, node.target.ctx)
                    node.body=[convert_to_tuple(n, newname, renamings) for n in node.body ]
        return node


def normalize_tuples(node):
    """Prune a node from implicit tuples, replacing them by real ones."""
    NormalizeTuples().visit(node)

##
class RemoveComprehension(ast.NodeTransformer):
    def __init__(self):
        self.functions=list()
        self.count=0

    def visit_Module(self, node):
        self.global_declarations = global_declarations(node)
        [ self.visit(n) for n in node.body ]
        node.body = self.functions + node.body


    def visit_ListComp(self, node):
        node.elt=self.visit(node.elt)
        name = "list_comprehension{0}".format(self.count)
        self.global_declarations.update({name:None})
        self.count+=1
        args = imported_ids(node,self.global_declarations)
        for generator in node.generators:
            args.difference_update(imported_ids(generator.target, self.global_declarations))
        def wrap_in_ifs(node, ifs):
            return reduce(lambda n,if_: ast.If(if_,[n],[]), ifs, node)
        self.count_iter=0
        def nest_reducer(x,g):
            return ast.For(g.target, g.iter, [ wrap_in_ifs(x, g.ifs) ], [])
        body = reduce( nest_reducer,
                node.generators,
                ast.Expr(ast.Call(ast.Attribute(ast.Name("__list__",ast.Load()),"append",ast.Load()),[ast.Name("__list",ast.Load()),node.elt],[], None, None))
                )
        # add extra metadata to this node
        metadata.add(body, metadata.Comprehension("__list"))
        init = ast.Assign(
                [ast.Name("__list",ast.Store())],
                ast.Call(ast.Name("list",ast.Load()), [],[], None, None )
                )
        result = ast.Return(ast.Name("__list",ast.Store()))
        sargs=sorted([ast.Name(arg, ast.Load()) for arg in args])
        fd = ast.FunctionDef(name,
                ast.arguments(sargs,None, None,[]),
                [init, body, result ],
                [])
        self.functions.append(fd)
        return ast.Call(ast.Name(name,ast.Load()),[ast.Name(arg.id, ast.Load()) for arg in sargs],[], None, None) # no sharing !

def remove_comprehension(node):
    """Turns all list comprehension from a node into new function calls."""
    RemoveComprehension().visit(node)
    return node


##
class NestedFunctionRemover(ast.NodeTransformer):
    def __init__(self, gd):
         self.nested_functions=list()
         self.global_declarations=gd

    def visit_FunctionDef(self, node):
        [self.visit(n) for n in node.body ]
        self.nested_functions.append(node)
        former_name=node.name
        former_nbargs=len(node.args.args)
        node.name="pythran_{0}".format(former_name)
        ii=imported_ids(node, self.global_declarations)
        binded_args=[ast.Name(iin,ast.Load()) for iin in sorted(ii)]
        node.args.args= [ast.Name(iin,ast.Param()) for iin in sorted(ii)] + node.args.args
        proxy_call=ast.Name(node.name,ast.Load())
        return ast.Assign([ast.Name(former_name, ast.Store())], ast.Call(ast.Name("bind{0}".format(former_nbargs),ast.Load()), [proxy_call]+binded_args, [], None, None))

class RemoveNestedFunctions(ast.NodeVisitor):

    def visit_Module(self, node):
        self.nested_functions=list()
        self.global_declarations = global_declarations(node)
        [ self.visit(n) for n in node.body ]
        node.body+=self.nested_functions

    def visit_FunctionDef(self, node):
        nfr = NestedFunctionRemover(self.global_declarations)
        node.body=[nfr.visit(n) for n in node.body]
        self.nested_functions+=nfr.nested_functions

def remove_nested_functions(node):
    '''replace nested function by top-level functions and a call to a bind intrinsic that generates a local function with some arguments binded'''
    RemoveNestedFunctions().visit(node)

##
class LambdaRemover(ast.NodeTransformer):
    def __init__(self, name, gd):
        self.prefix=name
        self.lambda_functions=list()
        self.global_declarations=gd

    def visit_Lambda(self, node):
        node.body=self.visit(node.body)
        forged_name="{0}_lambda{1}".format(self.prefix, len(self.lambda_functions))
        ii=imported_ids(node, self.global_declarations)
        binded_args=[ast.Name(iin,ast.Load()) for iin in sorted(ii)]
        former_nbargs=len(node.args.args)
        node.args.args = [ast.Name(iin,ast.Param()) for iin in sorted(ii)] + node.args.args
        forged_fdef = ast.FunctionDef(forged_name, node.args, [ ast.Return(node.body) ], [])
        self.lambda_functions.append(forged_fdef)
        proxy_call=ast.Name(forged_name, ast.Load())
        return ast.Call(ast.Name("bind{0}".format(former_nbargs),ast.Load()), [proxy_call]+binded_args, [], None, None)

class RemoveLambdas(ast.NodeVisitor):

    def visit_Module(self, node):
        self.lambda_functions=list()
        self.global_declarations = global_declarations(node)
        [ self.visit(n) for n in node.body ]
        node.body+=self.lambda_functions

    def visit_FunctionDef(self, node):
        lr = LambdaRemover(node.name, self.global_declarations)
        node.body=[lr.visit(n) for n in node.body]
        self.lambda_functions+=lr.lambda_functions

def remove_lambdas(node):
    '''turns lambda into top-level functions'''
    RemoveLambdas().visit(node)

##

class ParallelizeMaps(ast.NodeVisitor):

    def __init__(self, pure):
        self.pure=pure

    def visit_Call(self, node):
        if isinstance(node.func, ast.Name) and node.func.id == "map":
            if isinstance(node.args[0], ast.Name) and node.args[0].id in self.pure:
                node.func.id="pmap"
            elif isinstance(node.args[0], ast.Call) and re.match(r"^bind[0-9]+$",node.args[0].func.id) and node.args[0].args[0].id in self.pure:
                node.func.id="pmap"



def parallelize_maps(node):
    '''Turns map calls to p(arallel)map calls when the first argument is pure.'''
    pure=purity_test(node)
    ParallelizeMaps(pure).visit(node)

##
class NormalizeReturn(ast.NodeVisitor):
    def visit_FunctionDef(self, node):
        self.has_return=False
        [ self.visit(n) for n in node.body ]
        if not self.has_return: node.body.append(ast.Return(ast.Name("None",ast.Load())))
    def visit_Return(self, node):
        self.has_return=True
        if not node.value:
            node.value=ast.Name("None",ast.Load())

def normalize_return(node):
    '''Adds Return statement when they are implicit, and adds the None return value when not set'''
    NormalizeReturn().visit(node)

##
class NormalizeMethodCalls(ast.NodeVisitor):
    def visit_Call(self, node):
        if isinstance(node.func, ast.Attribute) and node.func.attr in methods:
            node.args.insert(0,  node.func.value)
            node.func=ast.Attribute(ast.Name(methods[node.func.attr][0],ast.Load()), node.func.attr, ast.Load())

def normalize_method_calls(node):
    '''Turns built in method calls into function calls'''
    NormalizeMethodCalls().visit(node)

##
class NormalizeAttributes(ast.NodeTransformer):
    def visit_Attribute(self, node):
        if node.attr in attributes:
            return ast.Subscript(node.value, ast.Index(ast.Num(attributes[node.attr][1]["attribute"])), node.ctx)
        else:
            return node

def normalize_attributes(node):
    '''Turns built in attributes into tuple subscript'''
    NormalizeAttributes().visit(node)

##
class NormalizeIdentifiers(ast.NodeVisitor):
    def __init__(self, identifiers,renamings):
        self.identifiers=identifiers
        self.renamings=renamings

    def rename(self, name):
        if name not in self.renamings: 
            new_name=name
            while new_name in self.identifiers:
                new_name+="_"
            self.renamings[name]=new_name
        return self.renamings[name]

    def visit_Name(self, node):
        if node.id in cxx_keywords:
            node.id=self.rename(node.id)

    def visit_FunctionDef(self, node):
        if node.name in cxx_keywords:
            node.name=self.rename(node.name)
        self.visit(node.args)
        [ self.visit(n) for n in node.body ]
    def visit_alias(self, node):
        if node.asname:
            if node.asname in cxx_keywords:
                node.asname=self.rename(node.name)

def normalize_identifiers(node):
    '''Prevents naming conflict with c++ keywords by appending extra '_' to conflicting names.'''
    ni=NormalizeIdentifiers(identifiers(node), dict())
    ni.visit(node)
    return (node, ni.renamings)

##
class UnshadowParameters(ast.NodeVisitor):
    def __init__(self, identifiers):
        self.identifiers=identifiers

    def visit_FunctionDef(self, node):
        self.argsid={ arg.id for arg in node.args.args }
        self.renaming={}
        [ self.visit(n) for n in node.body ]
        [ self.visit(n) for n in node.body ] # do it twice to make sure all renamings are done
        for k,v in self.renaming.iteritems():
            node.body.insert(0,ast.Assign([ast.Name(v,ast.Store())],ast.Name(k,ast.Load())))

    def visit_Assign(self, node):
        for t in node.targets:
            if isinstance(t, ast.Name) and t.id in self.argsid:
                if t.id not in self.renaming:
                    new_name=t.id
                    while new_name in self.identifiers:
                        new_name=new_name+"_"
                    self.renaming[t.id]=new_name
        [self.visit(t) for t in node.targets]
        self.visit(node.value)

    def visit_Name(self, node):
        if node.id in self.renaming: node.id=self.renaming[node.id]

def unshadow_parameters(node):
    '''Prevents parameter shadowing by creating new variable'''
    UnshadowParameters(identifiers(node)).visit(node)

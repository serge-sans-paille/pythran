'''This modules contains code transformation to make your way from python code to pythran code
    * NormalizeTuples removes implicite variable -> tuple conversion
    * RemoveComprehension turns list comprehension into function calls
    * RemoveNestedFunctions turns nested function into top-level functions
    * RemoveLambdas turns lambda into regular functions
    * NormalizeReturn adds return statement where relevant
    * NormalizeMethodCalls turns built in method calls into function calls
    * NormalizeAttributes turns built in attributes into function calls
    * NormalizeIdentifiers prevents conflicts with c++ keywords
    * NormalizeException turns try...finally and try...else constructs into try...except
    * UnshadowParameters prevents the shadow parameter phenomenon
    * ExpandImports replaces imports by their full paths
    * GatherOMPData turns OpenMP-like string annotations into metadata
'''

from analysis import ImportedIds, GlobalDeclarations, Identifiers, ConstantExpressions
from passmanager import gather, Transformation
from tables import methods, attributes, functions, cxx_keywords, namespace, modules
from syntax import PythranSyntaxError
import metadata
import ast

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

class NormalizeTuples(Transformation):
    """ Remove implicit tuple -> variable conversion."""
    tuple_name = "__tuple"
    def __init__(self):
        self.counter=0
        Transformation.__init__(self)

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

    def visit_comprehension(self, node):
        renamings=dict()
        self.traverse_tuples(node.target,(), renamings)
        if renamings:
            self.counter+=1
            return "{0}{1}".format(NormalizeTuples.tuple_name, self.counter), renamings
        else:
            return node

    def visit_AnyComp(self, node):
        self.generic_visit(node.elt)
        generators = [ self.visit(n) for n in node.generators ]
        nnode = node
        for i, g in enumerate(generators):
            if isinstance(g,tuple):
                gtarget = "{0}{1}".format(g[0], i)
                nnode.generators[i].target=ast.Name(gtarget, nnode.generators[i].target.ctx)
                metadata.add(nnode.generators[i].target, metadata.LocalVariable())
                nnode = ConvertToTuple(gtarget, g[1]).visit(nnode)
        node.elt=nnode.elt
        node.generators=nnode.generators
        return node

    def visit_ListComp(self, node): return self.visit_AnyComp(node)

    def visit_SetComp(self, node): return self.visit_AnyComp(node)

    def visit_Lambda(self, node):
        self.generic_visit(node)
        for i,arg in enumerate(node.args.args):
            renamings=dict()
            self.traverse_tuples(arg, (), renamings)
            if renamings:
                self.counter+=1
                newname="{0}{1}".format(NormalizeTuples.tuple_name, self.counter)
                node.args.args[i]=ast.Name(newname, ast.Param())
                node.body=ConvertToTuple(newname, renamings).visit(node.body) 
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
                    metadata.add(node.targets[i], metadata.LocalVariable())
                    for rename,state in sorted(renamings.iteritems()):
                        nnode=reduce(lambda x,y: ast.Subscript(x, ast.Index(ast.Num(y)), ast.Load()), state, ast.Name(gtarget, ast.Load()))
                        if isinstance(rename, str):
                            extra_assign.append(ast.Assign([ast.Name(rename,ast.Store())], nnode))
                        else:
                            extra_assign.append(ast.Assign([rename], nnode))
        return ast.If(ast.Num(1), extra_assign, []) if len(extra_assign) > 1 else extra_assign

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
                    node.body=[ConvertToTuple( newname, renamings).visit(n) for n in node.body ]
        return node

##
class RemoveComprehension(Transformation):
    """Turns all list comprehension from a node into new function calls."""

    def __init__(self):
        self.count=0
        Transformation.__init__(self)

    def nest_reducer(self, x,g):
        def wrap_in_ifs(node, ifs):
            return reduce(lambda n,if_: ast.If(if_,[n],[]), ifs, node)
        return ast.For(g.target, g.iter, [ wrap_in_ifs(x, g.ifs) ], [])

    def visit_AnyComp(self, node, comp_type, comp_method):
        node.elt=self.visit(node.elt)
        name = "{0}_comprehension{1}".format(comp_type, self.count)
        self.count+=1
        args=gather(ImportedIds, node, self.ctx)
        self.count_iter=0

        starget="__target"
        body = reduce( self.nest_reducer,
                node.generators,
                ast.Expr(ast.Call(ast.Attribute(ast.Name("__{0}__".format(comp_type),ast.Load()), comp_method, ast.Load()),[ast.Name(starget,ast.Load()),node.elt],[], None, None))
                )
        # add extra metadata to this node
        metadata.add(body, metadata.Comprehension(starget))
        init = ast.Assign(
                [ast.Name(starget,ast.Store())],
                ast.Call(ast.Name(comp_type, ast.Load()), [],[], None, None )
                )
        result = ast.Return(ast.Name(starget,ast.Store()))
        sargs=sorted([ast.Name(arg, ast.Load()) for arg in args])
        fd = ast.FunctionDef(name,
                ast.arguments(sargs,None, None,[]),
                [init, body, result ],
                [])
        self.ctx.module.body.append(fd)
        return ast.Call(ast.Name(name,ast.Load()),[ast.Name(arg.id, ast.Load()) for arg in sargs],[], None, None) # no sharing !

    def visit_ListComp(self, node): return self.visit_AnyComp(node, "list", "append")

    def visit_SetComp(self, node): return self.visit_AnyComp(node, "set", "add")

    def visit_GeneratorExp(self, node):
        node.elt=self.visit(node.elt)
        name = "generator_expression{0}".format(self.count)
        self.count+=1
        args = gather(ImportedIds, node, self.ctx)
        self.count_iter=0

        body = reduce( self.nest_reducer,
                node.generators,
                ast.Expr(ast.Yield(node.elt))
                )

        sargs=sorted([ast.Name(arg, ast.Load()) for arg in args])
        fd = ast.FunctionDef(name,
                ast.arguments(sargs,None, None,[]),
                [body],
                [])
        self.ctx.module.body.append(fd)
        return ast.Call(ast.Name(name,ast.Load()),[ast.Name(arg.id, ast.Load()) for arg in sargs],[], None, None) # no sharing !

##
class NestedFunctionRemover(Transformation):
    '''replace nested function by top-level functions and a call to a bind intrinsic that generates a local function with some arguments binded'''
    def __init__(self, ctx):
        Transformation.__init__(self)
        self.nested_functions=list()
        self.ctx=ctx

    def visit_FunctionDef(self, node):
        [self.visit(n) for n in node.body ]
        self.nested_functions.append(node)
        former_name=node.name
        former_nbargs=len(node.args.args)
        node.name="pythran_{0}".format(former_name)
        ii=gather(ImportedIds, node, self.ctx)
        binded_args=[ast.Name(iin,ast.Load()) for iin in sorted(ii)]
        node.args.args= [ast.Name(iin,ast.Param()) for iin in sorted(ii)] + node.args.args
        proxy_call=ast.Name(node.name,ast.Load())
        return ast.Assign([ast.Name(former_name, ast.Store())], ast.Call(ast.Name("bind{0}".format(former_nbargs),ast.Load()), [proxy_call]+binded_args, [], None, None))

class RemoveNestedFunctions(Transformation):

    def visit_Module(self, node):
        self.nested_functions=list()
        [ self.visit(n) for n in node.body ]
        node.body.extend(self.nested_functions)
        return node

    def visit_FunctionDef(self, node):
        nfr = NestedFunctionRemover(self.ctx)
        node.body=[nfr.visit(n) for n in node.body]
        self.nested_functions.extend(nfr.nested_functions)
        return node

##
class LambdaRemover(Transformation):
    '''turns lambda into top-level functions'''
    def __init__(self, name, ctx):
        Transformation.__init__(self)
        self.ctx=ctx
        self.prefix=name
        self.lambda_functions=list()

    def visit_Lambda(self, node):
        node.body=self.visit(node.body)
        forged_name="{0}_lambda{1}".format(self.prefix, len(self.lambda_functions))
        ii=gather(ImportedIds, node, self.ctx)
        binded_args=[ast.Name(iin,ast.Load()) for iin in sorted(ii)]
        former_nbargs=len(node.args.args)
        node.args.args = [ast.Name(iin,ast.Param()) for iin in sorted(ii)] + node.args.args
        forged_fdef = ast.FunctionDef(forged_name, node.args, [ ast.Return(node.body) ], [])
        self.lambda_functions.append(forged_fdef)
        proxy_call=ast.Name(forged_name, ast.Load())
        return ast.Call(ast.Name("bind{0}".format(former_nbargs),ast.Load()), [proxy_call]+binded_args, [], None, None)

class RemoveLambdas(Transformation):

    def visit_Module(self, node):
        self.lambda_functions=list()
        [ self.visit(n) for n in node.body ]
        node.body.extend(self.lambda_functions)
        return node

    def visit_FunctionDef(self, node):
        lr = LambdaRemover(node.name, self.ctx)
        node.body=[lr.visit(n) for n in node.body]
        self.lambda_functions.extend(lr.lambda_functions)
        return node

##
class NormalizeReturn(Transformation):
    '''Adds Return statement when they are implicit, and adds the None return value when not set'''
    def visit_FunctionDef(self, node):
        self.has_return=False
        [ self.visit(n) for n in node.body ]
        if not self.has_return: node.body.append(ast.Return(ast.Name("None",ast.Load())))
        return node
    def visit_Return(self, node):
        self.has_return=True
        if not node.value:
            node.value=ast.Name("None",ast.Load())
        return node
##
class NormalizeMethodCalls(Transformation):
    '''Turns built in method calls into function calls'''
    def visit_Call(self, node):
        [self.visit(n) for n in node.args ]
        if isinstance(node.func, ast.Attribute) and node.func.attr in methods:
            node.args.insert(0,  node.func.value)
            node.func=ast.Attribute(ast.Name(methods[node.func.attr][0],ast.Load()), node.func.attr, ast.Load())
        return node

##
class NormalizeAttributes(Transformation):
    '''Turns built in attributes into tuple subscript'''
    def visit_Attribute(self, node):
        if node.attr in attributes:
            return ast.Subscript(node.value, ast.Index(ast.Num(attributes[node.attr][1].val)), node.ctx)
        elif node.attr in functions:
            if len(functions[node.attr]) > 1:
                return node
            else:
                [(module,_)] = functions[node.attr]
                assert isinstance(node.value, ast.Name)
                node.value.id=module
                return node
        else:
            return node

##
class NormalizeIdentifiers(Transformation):
    '''Prevents naming conflict with c++ keywords by appending extra '_' to conflicting names.'''
    def __init__(self):
        self.renamings=dict()
        Transformation.__init__(self, Identifiers)

    def rename(self, name):
        if name not in self.renamings: 
            new_name=name
            while new_name in self.identifiers:
                new_name+="_"
            self.renamings[name]=new_name
        return self.renamings[name]

    def run_visit(self, node):
        self.visit(node)
        return self.renamings

    def visit_Name(self, node):
        if node.id in cxx_keywords:
            node.id=self.rename(node.id)
        return node

    def visit_FunctionDef(self, node):
        if node.name in cxx_keywords:
            node.name=self.rename(node.name)
        self.visit(node.args)
        [ self.visit(n) for n in node.body ]
        return node

    def visit_alias(self, node):
        if node.asname:
            if node.asname in cxx_keywords:
                node.asname=self.rename(node.name)
        return node

    def visit_Attribute(self, node):
        self.visit(node.value)
        if node.attr in cxx_keywords:
            node.attr += "_" # let us only hope the considered class does not have this attribute
        # Always true as long as we don't have custom classes.
        return node

##
class NormalizeException(Transformation):
    '''Transform else statement in try except block in nested try except'''
    def visit_TryExcept(self,node):
        if node.orelse:
            node.body.append(ast.TryExcept(node.orelse,[ast.ExceptHandler(None,None,[])],[]))
            node.orelse=None
        return node

    def visit_TryFinally(self,node):
        node.body.extend(node.finalbody)
        node.finalbody.append(ast.Raise(None,None,None))
        return ast.TryExcept(node.body,[ast.ExceptHandler(None,None,node.finalbody)],[])

##
class UnshadowParameters(Transformation):
    '''Prevents parameter shadowing by creating new variable'''
    def __init__(self):
        Transformation.__init__(self, Identifiers)

    def visit_FunctionDef(self, node):
        self.argsid={ arg.id for arg in node.args.args }
        self.renaming={}
        [ self.visit(n) for n in node.body ]
        [ self.visit(n) for n in node.body ] # do it twice to make sure all renamings are done
        for k,v in self.renaming.iteritems():
            node.body.insert(0,ast.Assign([ast.Name(v,ast.Store())],ast.Name(k,ast.Load())))
        return node

    def visit_Assign(self, node):
        for t in node.targets:
            if isinstance(t, ast.Name) and t.id in self.argsid:
                if t.id not in self.renaming:
                    new_name=t.id
                    while new_name in self.identifiers:
                        new_name=new_name+"_"
                    self.renaming[t.id]=new_name
        [self.visit(t) for t in node.targets]
        try: self.visit(node.metadata)
        except AttributeError:pass 
        self.visit(node.value)
        return node

    def visit_Name(self, node):
        if node.id in self.renaming: node.id=self.renaming[node.id]
        return node

##
class ExpandImports(Transformation):
    '''Expands all imports into full paths'''

    def __init__(self):
        Transformation.__init__(self)
        self.imports=set()
        self.symbols=dict()

    def visit_Module(self, node):
        node.body = [ k for k in ( self.visit(n) for n in node.body ) if k ]
        imports = [ ast.Import([ast.alias(i, namespace + "::" + i)]) for i in self.imports ]
        node.body = imports + node.body
        ast.fix_missing_locations(node)
        return node

    def visit_Import(self, node):
        for alias in node.names:
            self.imports.add(alias.name)
            self.symbols[alias.asname if alias.asname else alias.name]=(alias.name,)
        return None

    def visit_ImportFrom(self, node):
        self.imports.add(node.module)
        for alias in node.names:
            self.symbols[alias.asname if alias.asname else alias.name ]=(node.module,alias.name)
        return None

    def visit_FunctionDef(self, node):
        self.symbols.pop(node.name, None)
        gsymbols=self.symbols.copy()
        self.visit(node.args)
        node.body = [ k for k in ( self.visit(n) for n in node.body ) if k ]
        self.symbols=gsymbols
        return node

    def visit_Assign(self, node):
        self.visit(node.value)
        [ self.visit(n) for n in node.targets ]
        [ self.symbols.pop(t.id, None) for t in node.targets if isinstance(t, ast.Name)]
        return node

    def visit_Name(self, node):
        if node.id in self.symbols:
            new_node= reduce(lambda v,o:ast.Attribute(v,o, ast.Load()), self.symbols[node.id][1:], ast.Name(self.symbols[node.id][0], ast.Load())) 
            new_node.ctx=node.ctx
            ast.copy_location(new_node,node)
            return new_node
        return node

##
class GatherOMPData(Transformation):
    '''walks node and collect string comment looking for OpenMP directives'''
    statements= ("Call", "Return", "Delete", "Assign", "AugAssign", "Print", "For", "While", "If", "Raise", "Assert", "Pass",)
    def __init__(self):
        Transformation.__init__(self)
        for s in GatherOMPData.statements:
            setattr(self, "visit_"+s, lambda node_: self.attach_data(node_))
        self.current=list()

    def visit_Expr(self, node):
        if isinstance(node.value, ast.Str) and node.value.s.startswith("omp"):
            self.current.append(node.value.s)
            return None
        else:
            self.attach_data(node)
        return node

    def attach_data(self, node):
        if self.current:
            [metadata.add(node, metadata.OMPDirective(curr)) for curr in self.current]
            self.current=list()
        self.generic_visit(node)
        return node

##
class ConstantFolding(Transformation):
    '''Replace constant expression by their evaluation.'''
    def __init__(self):
        Transformation.__init__(self, ConstantExpressions)
        self.env= { module_name : __import__(module_name) for module_name in modules if not module_name.startswith('__') }

    def to_ast(self, value):
        if any(isinstance(value,t) for t in (int, long, bool, float)):
            return ast.Num(value)
        elif isinstance(value, str):
            return ast.Str(value)
        elif isinstance(value, list):
            return ast.List([ self.to_ast(elt) for elt in value ], ast.Load()) #SG: unsure wether it Load or something else
        elif isinstance(value, tuple):
            return ast.Tuple([ self.to_ast(elt) for elt in value ], ast.Load())
        elif isinstance(value, set):
            return ast.Set([ self.to_ast(elt) for elt in value ])
        elif isinstance(value, dict):
            return ast.Dict([self.to_ast(elt) for elt in value.iterkeys()], [self.to_ast(elt) for elt in value.itervalues()])
        else:
            return None


    def generic_visit(self, node):
        if node in self.constant_expressions:
            try:
                fake_node=ast.Expression(node.value if isinstance(node, ast.Index) else node )
                code=compile(fake_node,'<constant folding>','eval')
                value=eval(code, self.env)
                new_node = self.to_ast(value) or node
                if isinstance(node, ast.Index) and not isinstance(new_node, ast.Index):
                    new_node=ast.Index(new_node)
                return new_node
            except Exception as e:
                print ast.dump(node)
                print 'error in constant folding: ', e
                return node
        else:
            return Transformation.generic_visit(self, node)

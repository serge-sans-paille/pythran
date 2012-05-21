'''This module performs the return type inference, according to symbolic types, and reorder function declarations according to the return type dependencies.
    * type_all generates a node -> type binding
'''

import ast
import networkx as nx
import operator
import re
from tables import type_to_str, operator_to_lambda, modules, builtin_constants
from analysis import global_declarations, constant_value, ordered_global_declarations, PythranSyntaxError

# networkx backward compatibility
if not "has_path" in nx.__dict__:
	def has_path(G,source,target):
		try:
			nx.shortest_path(G, source, target)
		except nx.NetworkXNoPath:
			return False
		return True
	nx.has_path=has_path

class Reorder(ast.NodeVisitor):
    def __init__(self, typedeps):
        self.typedeps=typedeps
        none_successors = self.typedeps.successors(TypeDependencies.NoDeps)
        for n in sorted(none_successors): # remove edges that implies a circular dependency
            for p in sorted(self.typedeps.predecessors(n)):
                if nx.has_path(self.typedeps,n,p):
                    self.typedeps.remove_edge(p,n)
        #nx.write_dot(self.typedeps,"b.dot")

    def visit_Module(self, node):
        newbody=list()
        olddef=list()
        for stmt in node.body:
            if isinstance(stmt, ast.FunctionDef):
                olddef.append(stmt)
            else: newbody.append(stmt)
        newdef = [ f for f in nx.topological_sort(self.typedeps, ordered_global_declarations(node)) if isinstance(f, ast.FunctionDef) ]
        assert set(newdef) == set(olddef)
        node.body=newbody + newdef


class TypeDependencies(ast.NodeVisitor):

    NoDeps="None"

    def __init__(self, name_to_node):
        self.types=nx.DiGraph()
        for k,v in name_to_node.iteritems():
            self.types.add_node(v)
        self.types.add_node(TypeDependencies.NoDeps)
        self.name_to_node=name_to_node
        self.current_function=list()


    def visit_FunctionDef(self, node):
        modules['__user__'][node.name]=dict()
        self.current_function.append(node)
        self.types.add_node(node)
        self.naming=dict()
        [ self.visit(n) for n in node.body ]
        self.current_function.pop()

    def visit_Return(self, node):
        if node.value:
            v=self.visit(node.value)
            for dep_set in v:
                if dep_set: [self.types.add_edge(dep,self.current_function[-1]) for dep in dep_set]
                else: self.types.add_edge(TypeDependencies.NoDeps,self.current_function[-1])

    def visit_Assign(self, node):
        v=self.visit(node.value)
        self.naming.update({ t.id:v for t in node.targets if isinstance(t, ast.Name) }) # need to handle subscript too ...

    def visit_AugAssign(self, node):
        v=self.visit(node.value)
        if isinstance(node.target, ast.Name):
            self.naming.update({ node.target.id: v })

    def visit_For(self, node):
        self.naming.update( {node.target.id : self.visit(node.iter)})
        if node.body:
            [self.visit(n) for n in node.body]
        if node.orelse:
            [self.visit(n) for n in node.orelse]

    def visit_BoolOp(self, node):
        root=[set()]
        for value in node.values:
            for val in self.visit(value):
                root=[r.union(v) for r in root for v in val]
        return root

    def visit_BinOp(self, node):
        return [l.union(r) for l in self.visit(node.left) for r in self.visit(node.right)]

    def visit_UnaryOp(self, node):
        return self.visit(node.operand)

    def visit_Lambda(self, node):
        assert False

    def visit_IfExp(self, node):
        return self.visit(node.body)+self.visit(node.orelse)

    def visit_Compare(self, node):
        return [set()]

    def visit_Call(self, node):
        func = self.visit(node.func)
        for arg in node.args:
            func=[f.union(v) for f in func for v in self.visit(arg)]
        return func

    def visit_Num(self, node):
        return [set()]

    def visit_Str(self, node):
        return [set()]

    def visit_Attribute(self, node):
        return [set()]

    def visit_Subscript(self, node):
        return self.visit(node.value)

    def visit_Name(self, node):
        if node.id in self.naming: return self.naming[node.id]
        elif node.id in self.name_to_node: return [{self.name_to_node[node.id]}]
        else: return [set()]

    def visit_List(self, node):
        return reduce(operator.add, map(self.visit,node.elts), [set()])

    def visit_Tuple(self, node):
        return reduce(operator.add, map(self.visit,node.elts), [set()])

    def visit_Slice(self, node):
        return [set()]

    def visit_Index(self, node):
        return [set()]

class Typing(ast.NodeVisitor):

    def __init__(self, name_to_node):
        self.types=dict()
        self.types["bool"]="bool"
        self.current=list()
        self.global_declarations = dict()

    def combine(self, node, othernode, op=lambda x, y: "{0}+{1}".format(x,y), unary_op=lambda x:x):
        self.merge(node, othernode, op, unary_op)

    def merge(self, node, othernode, op, unary_op):
        try:
            if isinstance(othernode, ast.FunctionDef):
                new_type=othernode.name
                if node not in self.types:
                    self.types[node]=new_type
            else:
                f=lambda x: "std::declval<{0}>()".format(x)
                if isinstance(node, ast.Name) and isinstance(node.ctx, ast.Param): # defer combination for parameters
                    def translator_generator(args):
                        ''' capture args for transtor generation'''
                        def interprocedural_type_translator(s,n):
                            translated_othernode=ast.Name('__fake__', ast.Load())
                            s.types[translated_othernode]=s.types[othernode]
                            # build translated type for fake_node
                            for p,v in enumerate(args):
                                if v == node: # this one will replace `node'
                                    translated_node=n.args[p]
                                s.types[translated_othernode]=re.sub(r'argument_type{0}'.format(p),s.types[n.args[p]], s.types[translated_othernode])
                            s.combine(translated_node, translated_othernode, op, unary_op)
                        return interprocedural_type_translator
                    modules['__user__'][self.current[-1].name]['combiner']=translator_generator(self.current[-1].args.args) # deferred combination
                else:
                    new_type = unary_op( self.types[othernode] ) 
                    if node not in self.types or (isinstance(node,ast.FunctionDef) and self.types[node] in self.global_declarations):
                        self.types[node]=new_type
                    elif self.types[node] != new_type :
                        if "/*weak*/" not in new_type and "/*weak*/" not in self.types[node]:
                            self.types[node]="decltype({0})".format(op(f(self.types[node]), f(new_type)))
                        elif "/*weak*/" not in new_type:
                            self.types[node]=new_type
        except:
            print ast.dump(othernode)
            raise

    def visit_Module(self, node):
        [ self.visit(n) for n in node.body ]


    def visit_FunctionDef(self, node):
        self.current.append(node)
        self.name_to_nodes = {arg.id:{arg} for arg in node.args.args }
        for k,v in builtin_constants.iteritems():
            fake_node=ast.Name(k,ast.Load())
            self.name_to_nodes.update({ k:{fake_node}}) 
            self.types[fake_node]=v
        self.visit(node.args) ; [ self.visit(n) for n in node.body ]
        # propagate type information through all aliases
        for name,nodes in self.name_to_nodes.iteritems():
            relevant_types= [self.types[n] for n in nodes if n in self.types]
            if relevant_types:
                max_type = max(relevant_types, key=len)
                for n in nodes:
                    self.types[n]=max_type
        self.global_declarations[node.name]=node
        self.current.pop()

    def visit_Return(self, node):
        if node.value:
            self.visit(node.value)
            self.combine(self.current[-1], node.value)
        else:
            self.types[self.current[-1]]="none_type"

    def visit_Assign(self, node):
        self.visit(node.value)
        for t in node.targets:
            if isinstance(t, ast.Name):
                if not t.id in self.name_to_nodes: self.name_to_nodes[t.id]=set()
                self.name_to_nodes[t.id].add(t)
        for t in node.targets:
            self.combine(t, node.value)
            self.visit(t)

    def visit_AugAssign(self, node):
        self.visit(node.value)
        self.visit(node.target)
        self.combine(node.target, node.value, operator_to_lambda[type(node.op)])

    def visit_For(self, node):
        if isinstance(node.target, ast.Name):
            if not node.target.id in self.name_to_nodes: self.name_to_nodes[node.target.id]=set()
            self.name_to_nodes[node.target.id].add(node.target)
        self.visit(node.iter)
        self.combine(node.target, node.iter, unary_op=lambda x:"typename content_of<{0}>::type".format(x))
        self.visit(node.target)
        if node.body:
            [self.visit(n) for n in node.body]
        if node.orelse:
            [self.visit(n) for n in node.orelse]

    def visit_ImportFrom(self, node):
        for alias in node.names:
            if self.current:self.name_to_nodes[alias.name]={alias}
            else: self.global_declarations[alias.name]=alias
            self.types[alias]="decltype({0}::{1})".format(node.module,alias.name) if "scalar" in modules[node.module][alias.name] else "{0}::proxy::{1}".format(node.module, alias.name)

    def visit_BoolOp(self, node):
        [ self.visit(value) for value in node.values]
        [ self.combine(node, value,  operator_to_lambda[type(node.op)]) for value in node.values]

    def visit_BinOp(self, node):
        [ self.visit(value) for value in (node.left, node.right)]
        self.combine(node, node.left,  operator_to_lambda[type(node.op)])
        self.combine(node, node.right,  operator_to_lambda[type(node.op)])

    def visit_UnaryOp(self, node):
        self.visit(node.operand)
        f=lambda x: "decltype({0})".format(
                operator_to_lambda[type(node.op)](
                    "std::declval<{0}>()".format(x)))
        self.combine(node,node.operand, unary_op=f)

    def visit_Lambda(self, node):
        assert False
        self.visit(node.body)

    def visit_IfExp(self, node):
        [ self.visit(n) for n in (node.body, node.orelse) ]
        [ self.combine(node,n) for n in (node.body, node.orelse) ]

    def visit_Compare(self, node):
        self.types[node]="bool"

    def visit_Call(self, node):
        self.visit(node.func)
        [self.visit(n) for n in node.args]
        # handle backward type dependencies from method calls
        if isinstance(node.func, ast.Attribute):
            if isinstance(node.func.value, ast.Name):
                if node.func.value.id in modules and node.func.attr in modules[node.func.value.id]:
                    if 'combiner' in modules[node.func.value.id][node.func.attr]:
                        modules[node.func.value.id][node.func.attr]['combiner'](self, node)
            else:
                raise PythranSyntaxError("Unknown Attribute: `{0}'".format(node.func.attr), node)
        # handle backward type dependencies from user calls
        elif isinstance(node.func, ast.Name):
            if node.func.id in modules['__user__'] and 'combiner' in modules['__user__'][node.func.id]:
                modules['__user__'][node.func.id]['combiner'](self, node)
        F=lambda f: "decltype(std::declval<{0}>()({1}))".format( f, ", ".join("std::declval<{0}>()".format(self.types[arg]) for arg in node.args))
        self.combine(node, node.func, op=lambda x,y:y, unary_op=F)

    def visit_Num(self, node):
        self.types[node]=type_to_str[type(node.n)]

    def visit_Str(self, node):
        self.types[node]="std::string"

    def visit_Attribute(self, node):
        value, attr = (node.value, node.attr)
        if value.id in modules and attr in modules[value.id]:
            if modules[value.id][attr]: self.types[node]="decltype({0}::{1})".format(value.id, attr)
            else: self.types[node]="decltype({0}::proxy::{1}())".format(value.id, attr)
        else:
            raise PythranSyntaxError("Unknown Attribute: `{0}'".format(node.attr), node)

    def visit_Subscript(self, node):
        self.visit(node.value)
        try:
            v=constant_value(node.slice)
            f=lambda t: "typename std::tuple_element<{0},{1}>::type".format(v, t)
        except:
            f=lambda t: "typename content_of<{0}>::type".format(t)
        self.combine(node, node.value, unary_op=f)

    def visit_Name(self, node):
        if node.id in self.name_to_nodes:
            for nnode in self.name_to_nodes[node.id]:
                self.combine(node, nnode)
            self.name_to_nodes[node.id].add(node)
        elif node.id in self.global_declarations:
            self.combine(node, self.global_declarations[node.id])
        elif node.id in builtin_constants:
            self.types[node]=builtin_constants[node.id]
        elif node.id in modules["__builtins__"]:
            self.types[node]="proxy::{0}".format(node.id)
        else:
            self.types[node]="/*weak*/{0}".format(node.id)
        if "proxy::bind" in self.types[node] and "/*auto*/" not in self.types[node]:
            self.types[node]+="/*auto*/"
            

    def visit_List(self, node):
        if node.elts:
            [self.visit(elt) for elt in node.elts]
            [self.combine(node, elt, unary_op=lambda x:"sequence<{0}>".format(x)) for elt in node.elts]
        else:
            self.types[node]="empty_sequence"

    def visit_Tuple(self, node):
        if node.elts:
            [self.visit(elt) for elt in node.elts]
            try:
                types=[ self.types[elt] for elt in node.elts]
                self.types[node]="std::tuple<{0}>".format(",".join(types))
            except: pass # not very harmonious with the combine method ...
        else:
            self.types[node]="decltype(std::make_tuple())"

    def visit_Index(self, node):
        self.visit(node.value)
        self.combine(node, node.value)

    def visit_arguments(self, node):
        for i,arg in enumerate(node.args):
            self.types[arg]= "argument_type{0}".format(i)
        [self.visit(arg) for arg in node.args]

def type_all(node):
    gd=global_declarations(node)
    t = TypeDependencies(gd)
    t.visit(node)
    #nx.write_dot(t.types,"a.dot")

    Reorder(t.types).visit(node)

    ty = Typing(gd)
    ty.visit(node)

    final_types = { k: ty.types[k] if k in ty.types else v for k,v in ty.types.iteritems() }
    for head in gd.itervalues():
        if head not in final_types:
            final_types[head]="void"
    #for head in n2n.bindings.itervalues():
    #    print head.name, ":", final_types[head]
    return final_types


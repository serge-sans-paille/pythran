'''
This modules contains OpenMP-related stuff.
    * OMPDirective is used to represent OpenMP annotations in the AST
    * GatherOMPData turns OpenMP-like string annotations into metadata
'''

from pythran.passmanager import Transformation
import pythran.metadata as metadata

from ast import AST
import ast
import re

keywords = {
    'atomic',
    'barrier',
    'capture',
    'collapse',
    'copyin',
    'copyprivate',
    'critical',
    'default',
    'final',
    'firstprivate',
    'flush',
    'for',
    'if',
    'lastprivate',
    'master',
    'mergeable',
    'none',
    'nowait',
    'num_threads',
    'omp',
    'ordered',
    'parallel',
    'private',
    'read',
    'reduction',
    'schedule',
    'section',
    'sections',
    'shared',
    'simd',
    'single',
    'task',
    'taskwait',
    'taskyield',
    'threadprivate',
    'untied',
    'update',
    'write'
}

reserved_contex = {
    'default',
    'schedule',
}


class OMPDirective(AST):
    '''Turn a string into a context-dependent metadata.
    >>> o = OMPDirective("omp for private(a,b) shared(c)")
    >>> o.s
    'omp for private({},{}) shared({})'
    >>> [ type(dep) for dep in o.deps ]
    [<class '_ast.Name'>, <class '_ast.Name'>, <class '_ast.Name'>]
    >>> [ dep.id for dep in o.deps ]
    ['a', 'b', 'c']
    '''

    def __init__(self, *args):  # no positional argument to be deep copyable
        super(OMPDirective, self).__init__()
        if not args:
            return

        self.deps = []

        def tokenize(s):
            '''A simple contextual "parser" for an OpenMP string'''
            # not completely satisfying if there are strings in if expressions
            out = ''
            par_count = 0
            curr_index = 0
            in_reserved_context = False
            while curr_index < len(s):
                m = re.match(r'^([a-zA-Z_]\w*)', s[curr_index:])
                if m:
                    word = m.group(0)
                    curr_index += len(word)
                    if(in_reserved_context or
                       (par_count == 0 and word in keywords)):
                        out += word
                        in_reserved_context = word in reserved_contex
                    else:
                        v = '{}'
                        self.deps.append(ast.Name(word, ast.Load()))
                        out += v
                elif s[curr_index] == '(':
                    par_count += 1
                    curr_index += 1
                    out += '('
                elif s[curr_index] == ')':
                    par_count -= 1
                    curr_index += 1
                    out += ')'
                    if par_count == 0:
                        in_reserved_context = False
                else:
                    if s[curr_index] == ',':
                        in_reserved_context = False
                    out += s[curr_index]
                    curr_index += 1
            return out

        self.s = tokenize(args[0])
        self._fields = ('deps',)


##
class GatherOMPData(Transformation):
    '''Walks node and collect string comments looking for OpenMP directives.'''

    # there is a special handling for If and Expr, so not listed here
    statements = ("FunctionDef", "Return", "Delete", "Assign", "AugAssign",
                  "Print", "For", "While", "Raise", "TryExcept", "TryFinally",
                  "Assert", "Import", "ImportFrom", "Pass", "Break",)

    # these fields hold statement lists
    statement_lists = ("body", "orelse", "finalbody",)

    def __init__(self):
        Transformation.__init__(self)
        # Remap self.visit_XXXX() to self.attach_data() generic method
        for s in GatherOMPData.statements:
            setattr(self, "visit_" + s, self.attach_data)
        self.current = list()

    def isompdirective(self, node):
        return isinstance(node, ast.Str) and node.s.startswith("omp ")

    def visit_Expr(self, node):
        if self.isompdirective(node.value):
            self.current.append(node.value.s)
            return None
        else:
            self.attach_data(node)
            return node

    def visit_If(self, node):
        if self.isompdirective(node.test):
            self.visit(ast.Expr(node.test))
            return self.visit(ast.If(ast.Num(1), node.body, node.orelse))
        else:
            return self.attach_data(node)

    def attach_data(self, node):
        '''Generic method called for visit_XXXX() with XXXX in
        GatherOMPData.statements list

        '''
        if self.current:
            for curr in self.current:
                md = OMPDirective(curr)
                metadata.add(node, md)
            self.current = list()
        # add a Pass to hold some directives
        for field_name, field in ast.iter_fields(node):
            if field_name in GatherOMPData.statement_lists:
                if(field and
                   isinstance(field[-1], ast.Expr) and
                   self.isompdirective(field[-1].value)):
                    field.append(ast.Pass())
        self.generic_visit(node)

        # add an If to hold scoping OpenMP directives
        directives = metadata.get(node, OMPDirective)
        field_names = {n for n, _ in ast.iter_fields(node)}
        has_no_scope = field_names.isdisjoint(GatherOMPData.statement_lists)
        if directives and has_no_scope:
            # some directives create a scope, but the holding stmt may not
            # artificially create one here if needed
            sdirective = ''.join(d.s for d in directives)
            scoping = ('parallel', 'task', 'section')
            if any(s in sdirective for s in scoping):
                node = ast.If(ast.Num(1), [node], [])
        return node

"""
Generator for C/C++.
"""

# Serge Guelton: The licensing terms are not set in the source package, but
# pypi[1] says the software is under the MIT license, so I reproduce it here
# [1] http://pypi.python.org/pypi/cgen
#
# Copyright (C) 2008 Andreas Kloeckner
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

from __future__ import division
from textwrap import dedent
import networkx as nx
from pythran.tables import pythran_ward, functions
from pythran.intrinsic import ConstExceptionIntr
import sys

__copyright__ = "Copyright (C) 2008 Andreas Kloeckner"


class Generable(object):
    def __str__(self):
        """Return a single string (possibly containing newlines) representing
        this code construct."""
        return "\n".join(l.rstrip() for l in self.generate())

    def generate(self, with_semicolon=True):
        """Generate (i.e. yield) the lines making up this code construct."""
        raise NotImplementedError


class Declarator(Generable):
    def generate(self, with_semicolon=True):
        tp_lines, tp_decl = self.get_decl_pair()
        tp_lines = list(tp_lines)
        for line in tp_lines[:-1]:
            yield line
        sc = ";"
        if not with_semicolon:
            sc = ""
        if tp_decl is None:
            yield "%s%s" % (tp_lines[-1], sc)
        else:
            yield "%s %s%s" % (tp_lines[-1], tp_decl, sc)

    def get_decl_pair(self):
        """Return a tuple ``(type_lines, rhs)``.

        *type_lines* is a non-empty list of lines (most often just a
        single one) describing the type of this declarator. *rhs* is the right-
        hand side that actually contains the function/array/constness notation
        making up the bulk of the declarator syntax.
        """

    def inline(self):
        """Return the declarator as a single line."""
        tp_lines, tp_decl = self.get_decl_pair()
        tp_lines = " ".join(tp_lines)
        if tp_decl is None:
            return tp_lines
        else:
            return "%s %s" % (tp_lines, tp_decl)


class Value(Declarator):
    """A simple declarator: *typename* and *name* are given as strings."""

    def __init__(self, typename, name):
        self.typename = typename
        self.name = name

    def get_decl_pair(self):
        return [self.typename], self.name


class NestedDeclarator(Declarator):
    def __init__(self, subdecl):
        self.subdecl = subdecl

    @property
    def name(self):
        return self.subdecl.name

    def get_decl_pair(self):
        return self.subdecl.get_decl_pair()


class DeclSpecifier(NestedDeclarator):
    def __init__(self, subdecl, spec, sep=' '):
        NestedDeclarator.__init__(self, subdecl)
        self.spec = spec
        self.sep = sep

    def get_decl_pair(self):
        def add_spec(sub_it):
            it = iter(sub_it)
            try:
                yield "%s%s%s" % (self.spec, self.sep, it.next())
            except StopIteration:
                pass

            for line in it:
                yield line

        sub_tp, sub_decl = self.subdecl.get_decl_pair()
        return add_spec(sub_tp), sub_decl


class NamespaceQualifier(DeclSpecifier):
    def __init__(self, namespace, subdecl):
        DeclSpecifier.__init__(self, subdecl, namespace, '::')


class Typedef(DeclSpecifier):
    def __init__(self, subdecl):
        DeclSpecifier.__init__(self, subdecl, "typedef")


class Static(DeclSpecifier):
    def __init__(self, subdecl):
        DeclSpecifier.__init__(self, subdecl, "static")


class Const(NestedDeclarator):
    def get_decl_pair(self):
        sub_tp, sub_decl = self.subdecl.get_decl_pair()
        return sub_tp, ("const %s" % sub_decl)


class FunctionDeclaration(NestedDeclarator):
    def __init__(self, subdecl, arg_decls, *attributes):
        NestedDeclarator.__init__(self, subdecl)
        self.arg_decls = arg_decls
        self.attributes = attributes

    def get_decl_pair(self):
        sub_tp, sub_decl = self.subdecl.get_decl_pair()
        return sub_tp, ("%s(%s) %s" % (
            sub_decl,
            ", ".join(ad.inline() for ad in self.arg_decls),
            " ".join(self.attributes)))


class Struct(Declarator):

    """
    A structure declarator.

    Attributes
    ----------
    tpname : str
        Name of the structure. (None for unnamed struct)
    fields : [Declarator]
        Content of the structure.
    inherit : str
        Parent class of current structure.
    """

    def __init__(self, tpname, fields, inherit=None):
        """Initialize the structure declarator.  """
        self.tpname = tpname
        self.fields = fields
        self.inherit = inherit

    def get_decl_pair(self):
        """ See Declarator.get_decl_pair."""
        def get_tp():
            """ Iterator generating lines for struct definition. """
            decl = "struct "
            if self.tpname is not None:
                decl += self.tpname
                if self.inherit is not None:
                    decl += " : " + self.inherit
            yield decl
            yield "{"
            for f in self.fields:
                for f_line in f.generate():
                    yield "  " + f_line
            yield "} "
        return get_tp(), ""


# template --------------------------------------------------------------------
class Template(NestedDeclarator):
    def __init__(self, template_spec, subdecl):
        super(Template, self).__init__(subdecl)
        self.template_spec = template_spec

    def generate(self, with_semicolon=False):
        yield "template <%s>" % ", ".join(self.template_spec)
        for i in self.subdecl.generate(with_semicolon):
            yield i
        if(not isinstance(self.subdecl, FunctionDeclaration) and
           not isinstance(self.subdecl, Template)):
            yield ";"


# control flow/statement stuff ------------------------------------------------
class ExceptHandler(Generable):
    def __init__(self, name, body, alias=None):
        self.name = name
        assert isinstance(body, Generable)
        self.body = body
        self.alias = alias

    def generate(self):
        if self.name is None:
            yield "catch(...)"
        else:
            yield "catch (pythonic::types::%s const& %s)" % (self.name,
                                                             self.alias or '')
        for line in self.body.generate():
            yield line


class TryExcept(Generable):
    def __init__(self, try_, except_):
        self.try_ = try_
        assert isinstance(try_, Generable)
        self.except_ = except_

    def generate(self):
        yield "try"

        for line in self.try_.generate():
            yield line

        for exception in self.except_:
            for line in exception.generate():
                yield "  " + line


class If(Generable):
    def __init__(self, condition, then_, else_=None):
        if condition[0] == '(' and condition[-1] == ')':
            condition = condition[1:-1]

        self.condition = condition

        assert isinstance(then_, Generable)
        if else_ is not None:
            assert isinstance(else_, Generable)

        self.then_ = then_
        self.else_ = else_

    def generate(self):
        yield "if (%s)" % self.condition

        for line in self.then_.generate():
            yield line

        if self.else_ is not None:
            yield "else"
            for line in self.else_.generate():
                yield line


class Loop(Generable):
    def __init__(self, body):
        assert isinstance(body, Generable)
        self.body = body

    def generate(self):
        if self.intro_line() is not None:
            yield self.intro_line()

        for line in self.body.generate():
            yield line


class While(Loop):
    def __init__(self, condition, body):
        super(While, self).__init__(body)
        if condition[0] == '(' and condition[-1] == ')':
            condition = condition[1:-1]
        self.condition = condition

    def intro_line(self):
        return "while (%s)" % self.condition


class For(Loop):
    def __init__(self, start, condition, update, body):
        super(For, self).__init__(body)
        self.start = start
        self.condition = condition
        self.update = update

    def intro_line(self):
        return "for (%s; %s; %s)" % (self.start, self.condition, self.update)


class AutoFor(Loop):
    def __init__(self, target, iter_, body):
        super(AutoFor, self).__init__(body)
        self.target = target
        self.iter = iter_

    def intro_line(self):
        return ("for (auto&& "
                "{0}: {1})".format(self.target,
                                   self.iter))


# simple statements -----------------------------------------------------------
class Define(Generable):
    def __init__(self, symbol, value):
        self.symbol = symbol
        self.value = value

    def generate(self):
        yield "#define %s %s" % (self.symbol, self.value)


class Include(Generable):
    def __init__(self, filename, system=True):
        self.filename = filename
        self.system = system

    def generate(self):
        if self.system:
            yield "#include <%s>" % self.filename
        else:
            yield "#include \"%s\"" % self.filename


class Statement(Generable):
    def __init__(self, text):
        self.text = text

    def generate(self):
        yield self.text + ";"


class AnnotatedStatement(Generable):
    def __init__(self, stmt, annotations):
        self.stmt = stmt
        self.annotations = annotations

    def generate(self):
        for directive in self.annotations:
            pragma = "#pragma " + directive.s
            yield pragma.format(*directive.deps)
        for s in self.stmt.generate():
            yield s


class ReturnStatement(Statement):
    def generate(self):
        yield "return " + self.text + ";"


class EmptyStatement(Statement):
    def __init__(self):
        Statement.__init__(self, "")


class Assign(Generable):
    def __init__(self, lvalue, rvalue):
        self.lvalue = lvalue
        self.rvalue = rvalue

    def generate(self):
        yield "%s = %s;" % (self.lvalue, self.rvalue)


class Line(Generable):
    def __init__(self, text=""):
        self.text = text

    def generate(self):
        yield self.text


# initializers ----------------------------------------------------------------
class FunctionBody(Generable):
    def __init__(self, fdecl, body):
        """Initialize a function definition. *fdecl* is expected to be
        a :class:`FunctionDeclaration` instance, while *body* is a
        :class:`Block`.
        """
        self.fdecl = fdecl
        self.body = body

    def generate(self):
        for f_line in self.fdecl.generate(with_semicolon=False):
            yield f_line
        for b_line in self.body.generate():
            yield b_line


# block -----------------------------------------------------------------------
class Block(Generable):
    def __init__(self, contents=None):
        if contents is None:
            self.contents = []
        else:
            self.contents = contents[:]
        for item in self.contents:
            assert isinstance(item, Generable), item

    def generate(self):
        yield "{"
        for item in self.contents:
            for item_line in item.generate():
                yield "  " + item_line
        yield "}"


class Module(Block):
    def generate(self):
        for c in self.contents:
            for line in c.generate():
                yield line


class Namespace(Block):
    def __init__(self, name, contents=None):
        if contents is None:
            contents = []
        Block.__init__(self, contents)
        self.name = name

    def generate(self):
        yield "namespace " + self.name
        yield "{"
        for item in self.contents:
            for item_line in item.generate():
                yield "  " + item_line
        yield "}"


# copy-pasted from codepy.bpl, which is a real mess...
# the original code was under MIT License
# cf. http://pypi.python.org/pypi/codepy
# so I reproduce it here
#
# Copyright (C) 2008 Andreas Kloeckner
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

class PythonModule(object):
    '''
    Wraps the creation of a Pythran module wrapped a Python native Module
    '''
    def __init__(self, name, docstrings, metadata):
        '''
        Builds an empty PythonModule
        '''
        self.name = name
        self.preamble = []
        self.includes = []
        self.functions = {}
        self.global_vars = []
        self.implems = []
        self.wrappers = []
        self.docstrings = docstrings

        self.metadata = metadata
        moduledoc = self.docstring(self.docstrings.get(None, ""))
        self.metadata['moduledoc'] = moduledoc

        self._init_catches()

    def _init_catches(self):
        '''
        Initialize the catch handler used by all pythran-generated functions
        '''
        # topologically sorted exceptions based on the inheritance hierarchy.
        # needed because otherwise boost python register_exception handlers
        # do not catch exception type in the right way
        # (first valid exception is selected)
        # Inheritance has to be taken into account in the registration order.
        exceptions = nx.DiGraph()
        for function_name, v in functions.iteritems():
            for mname, symbol in v:
                if isinstance(symbol, ConstExceptionIntr):
                    exceptions.add_node(
                        getattr(sys.modules[".".join(mname)], function_name))

        # add edges based on class relationships
        for n in exceptions:
            if n.__base__ in exceptions:
                exceptions.add_edge(n.__base__, n)

        sorted_exceptions = nx.topological_sort(exceptions)

        self.catches = ['''
            #ifdef PYTHONIC_BUILTIN_{uname}_HPP
                catch(pythonic::types::{name} & e) {{
                    PyErr_SetString(PyExc_{name},
                        pythonic::__builtin__::functor::str{{}}(e.args).c_str());
                }}
            #endif
                '''.format(name=n.__name__,
                           uname=n.__name__.upper())
                        for n in sorted_exceptions]

        self.catches.append('''
            catch(...) {
                PyErr_SetString(PyExc_RuntimeError,
                    "Something happened on the way to heaven"
                );
            }''')

    def docstring(self, doc):
        return '"%s"' % (dedent(doc).replace('"', '\\"')
                                    .replace('\n', '\\n')
                                    .replace('\r', '\\r'))

    def add_to_preamble(self, *pa):
        self.preamble.extend(pa)

    def add_to_includes(self, *incl):
        self.includes.extend(incl)

    def add_meta(self, infos):
        self.infos = infos

    def add_function(self, func, name, types):
        """
        Add a function to be exposed. *func* is expected to be a
        :class:`cgen.FunctionBody`.

        Because a function can have several signatures exported,
        this method actually creates a wrapper for each specialization
        and a global wrapper that checks the argument types and
        runs the correct candidate, if any
        """
        self.implems.append(func)

        args_unboxing = []  # turns PyObject to c++ object
        args_checks = []  # check if the above conversion is valid
        wrapper_name = pythran_ward + 'wrap_' + func.fdecl.name

        for i, t in enumerate(types):
            args_unboxing.append('from_python<{}>(args_obj[{}])'.format(t, i))
            args_checks.append('is_convertible<{}>(args_obj[{}])'.format(t, i))
        if types:
            wrapper = '''
                static PyObject *
                {wname}(PyObject *self, PyObject *args)
                {{
                    PyObject* args_obj[{size}+1];
                    if(! PyArg_ParseTuple(args, "{fmt}", {objs}))
                        return nullptr;
                    if({checks})
                        return to_python({name}({args}));
                    else {{
                        return nullptr;
                    }}
                }}'''
        else:
            wrapper = '''
                static PyObject *
                {wname}(PyObject *self, PyObject *args)
                {{
                    return to_python({name}({args}));
                }}'''

        self.wrappers.append(
            wrapper.format(name=func.fdecl.name,
                           size=len(types),
                           fmt="O" * len(types),
                           objs=', '.join('&args_obj[%d]' % i
                                          for i in range(len(types))),
                           args=', '.join(args_unboxing),
                           checks=' and '.join(args_checks),
                           wname=wrapper_name,
                           )
        )

        func_descriptor = wrapper_name, types
        self.functions.setdefault(name, []).append(func_descriptor)

    def add_global_var(self, name, init):
        self.global_vars.append(name)
        self.implems.append(Assign('static PyObject* ' + name,
                                   'to_python({})'.format(init)))

    def generate(self):
        """Generate (i.e. yield) the source code of the
        module line-by-line.
        """
        themethods = []
        theextraobjects = []
        theoverloads = []
        for vname in self.global_vars:
            theextraobjects.append(
                'PyModule_AddObject(theModule, "{0}", {0});'.format(vname))

        for fname, overloads in self.functions.items():
            tryall = []
            candidates = []
            for overload, types in overloads:
                try_ = """
                    if(PyObject* obj = {name}(self, args))
                        return obj;
                    """.format(name=overload)
                tryall.append(try_)
                theargs = (t.replace("pythonic::types::", "")
                            .replace('::', '.')
                           for t in types)
                thecall = "{}({})".format(fname,
                                          ",".join(theargs))
                candidates.append(thecall)

            wrapper_name = pythran_ward + 'wrapall_' + fname

            candidate = '''
            static PyObject *
            {wname}(PyObject *self, PyObject *args)
            {{
                try {{
                {tryall}
                PyErr_SetString(PyExc_TypeError,
                  "Invalid argument type for pythranized function `{name}'.\\n"
                  "Candidates are:\\n{candidates}\\n"
                );
                return nullptr;
                }}
                {catches}
                return nullptr;
            }}
            '''.format(name=fname,
                       tryall="\n".join(tryall),
                       candidates="\\n".join("   " + c for c in candidates),
                       catches='\n'.join(self.catches),
                       wname=wrapper_name)

            fdoc = self.docstring(self.docstrings.get(fname, ''))
            themethod = '''{{
                "{name}",
                {wname},
                METH_VARARGS,
                {doc}}}'''.format(name=fname,
                                  wname=wrapper_name,
                                  doc=fdoc)
            themethods.append(themethod)
            theoverloads.append(candidate)

        methods = '''
            static PyMethodDef Methods[] = {{
                {methods}
                {{NULL, NULL, 0, NULL}}
            }};
            '''.format(methods="".join(m + "," for m in themethods))

        module = '''
            #if PY_MAJOR_VERSION >= 3
              static struct PyModuleDef moduledef = {{
                PyModuleDef_HEAD_INIT,
                "{name}",            /* m_name */
                {moduledoc},         /* m_doc */
                -1,                  /* m_size */
                Methods,             /* m_methods */
                NULL,                /* m_reload */
                NULL,                /* m_traverse */
                NULL,                /* m_clear */
                NULL,                /* m_free */
              }};
            #define PYTHRAN_RETURN return theModule
            #define PYTHRAN_MODULE_INIT(s) PyInit_##s
            #else
            #define PYTHRAN_RETURN return
            #define PYTHRAN_MODULE_INIT(s) init##s
            #endif
            PyMODINIT_FUNC
            PYTHRAN_MODULE_INIT({name})(void)
            __attribute__ ((visibility("default")))
            __attribute__ ((externally_visible));
            PyMODINIT_FUNC
            PYTHRAN_MODULE_INIT({name})(void) {{
                #ifdef PYTHONIC_TYPES_NDARRAY_HPP
                    import_array()
                #endif
                #if PY_MAJOR_VERSION >= 3
                PyObject* theModule = PyModule_Create(&moduledef);
                #else
                PyObject* theModule = Py_InitModule3("{name}",
                                                     Methods,
                                                     {moduledoc}
                );
                #endif
                if(not theModule)
                    PYTHRAN_RETURN;
                PyObject * theDoc = Py_BuildValue("(sss)",
                                                  "{version}",
                                                  "{date}",
                                                  "{hash}");
                if(not theDoc)
                    PYTHRAN_RETURN;
                PyModule_AddObject(theModule,
                                   "__pythran__",
                                   theDoc);
                {extraobjects}
                PYTHRAN_RETURN;
            }}
            '''.format(name=self.name,
                       extraobjects='\n'.join(theextraobjects),
                       **self.metadata)

        body = (self.preamble +
                self.includes +
                self.implems +
                map(Line, self.wrappers + theoverloads) +
                [Line(methods), Line(module)])

        return Module(body)

    def __str__(self):
        return str(self.generate())


class CompilationUnit(object):

    def __init__(self, body):
        self.body = body

    def __str__(self):
        return '\n'.join('\n'.join(s.generate()) for s in self.body)

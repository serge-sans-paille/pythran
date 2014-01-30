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

    def inline(self, with_semicolon=True):
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
            " ".join(self.attributes))
            )


class Struct(Declarator):
    """A structure declarator."""

    def __init__(self, tpname, fields):
        """Initialize the structure declarator.
        *tpname* is the name of the structure.
        *fields* is a list of :class:`Declarator` instances.
        """
        self.tpname = tpname
        self.fields = fields

    def get_decl_pair(self):
        def get_tp():
            if self.tpname is not None:
                yield "struct %s" % self.tpname
            else:
                yield "struct"
            yield "{"
            for f in self.fields:
                for f_line in f.generate():
                    yield "  " + f_line
            yield "} "
        return get_tp(), ""


# template --------------------------------------------------------------------
class Template(NestedDeclarator):
    def __init__(self, template_spec, subdecl):
        self.template_spec = template_spec
        self.subdecl = subdecl

    def generate(self, with_semicolon=False):
        yield "template <%s>" % ", ".join(self.template_spec)
        for i in self.subdecl.generate(with_semicolon):
            yield i
        if(not isinstance(self.subdecl, FunctionDeclaration)
                and not isinstance(self.subdecl, Template)):
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
    def __init__(self, try_, except_, else_=None):
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
        self.body = body

    def generate(self):
        if self.intro_line() is not None:
            yield self.intro_line()

        for line in self.body.generate():
            yield line


class While(Loop):
    def __init__(self, condition, body):
        self.condition = condition
        assert isinstance(body, Generable)
        self.body = body

    def intro_line(self):
        return "while (%s)" % self.condition


class For(Loop):
    def __init__(self, start, condition, update, body):
        self.start = start
        self.condition = condition
        self.update = update

        assert isinstance(body, Generable)
        self.body = body

    def intro_line(self):
        return "for (%s; %s; %s)" % (self.start, self.condition, self.update)


class AutoFor(Loop):
    def __init__(self, target, iter, body):
        self.target = target
        self.iter = iter

        assert isinstance(body, Generable)
        self.body = body

    def intro_line(self):
        return ("for (typename decltype({1})::iterator::reference "
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
        for a in self.annotations:
            yield "#pragma %s" % (a)
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
    def __init__(self, contents=[]):
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
    def __init__(self, name, contents=[]):
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

class BoostPythonModule(object):
    def __init__(self, name="module", max_arity=None):
        self.name = name
        self.preamble = []
        self.mod_body = []
        self.init_body = []

    def add_to_init(self, body):
        """Add the blocks or statements contained in the iterable *body* to the
        module initialization function.
        """
        self.init_body.extend(body)

    def add_to_preamble(self, pa):
        self.preamble.extend(pa)

    def add_function(self, func, name=None):
        """Add a function to be exposed. *func* is expected to be a
        :class:`cgen.FunctionBody`.
        """
        if not name:
            name = func.fdecl.name

        self.mod_body.append(func)
        self.init_body.append(
            Statement("boost::python::def(\"%s\", &%s)" % (name,
                                                           func.fdecl.name)))

    def generate(self):
        """Generate (i.e. yield) the source code of the
        module line-by-line.
        """
        body = (self.preamble + [Line()]
                + self.mod_body
                + [Line(), Line("BOOST_PYTHON_MODULE(%s)" % self.name)]
                + [Block(self.init_body)])

        return Module(body)

    def __str__(self):
        return str(self.generate())


class CompilationUnit(object):

    def __init__(self, body):
        self.body = body

    def __str__(self):
        return '\n'.join('\n'.join(s.generate()) for s in self.body)

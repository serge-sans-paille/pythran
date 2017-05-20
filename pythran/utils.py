""" Common function use for AST manipulation. """

import gast as ast
from pythran.tables import MODULES
from pythran.conversion import mangle, demangle
from functools import reduce
from contextlib import contextmanager


def attr_to_path(node):
    """ Compute path and final object for an attribute node """

    def get_intrinsic_path(modules, attr):
        """ Get function path and intrinsic from an ast.Attribute.  """
        if isinstance(attr, ast.Name):
            return modules[demangle(attr.id)], (demangle(attr.id),)
        elif isinstance(attr, ast.Attribute):
            module, path = get_intrinsic_path(modules, attr.value)
            return module[attr.attr], path + (attr.attr,)
    obj, path = get_intrinsic_path(MODULES, node)
    if not obj.isliteral():
        path = path[:-1] + ('functor', path[-1])
    return obj, ('pythonic', ) + path


def path_to_attr(path):
    """
    Transform path to ast.Attribute.

    >>> import gast as ast
    >>> path = ('__builtin__', 'my', 'constant')
    >>> value = path_to_attr(path)
    >>> ref = ast.Attribute(
    ...     value=ast.Attribute(value=ast.Name(id="__builtin__",
    ...                                        ctx=ast.Load(),
    ...                                        annotation=None),
    ...                         attr="my", ctx=ast.Load()),
    ...     attr="constant", ctx=ast.Load())
    >>> ast.dump(ref) == ast.dump(value)
    True
    """
    return reduce(lambda hpath, last: ast.Attribute(hpath, last, ast.Load()),
                  path[1:], ast.Name(mangle(path[0]), ast.Load(), None))


def path_to_node(path):
    """
    Retrieve a symbol in MODULES based on its path
    >>> path = ('math', 'pi')
    >>> path_to_node(path) #doctest: +ELLIPSIS
    <pythran.intrinsic.ConstantIntr object at 0x...>
    """
    if len(path) == 1:
        return MODULES[path[0]]
    else:
        return path_to_node(path[:-1])[path[-1]]


def get_variable(assignable):
    """
    Return modified variable name.

    >>> import gast as ast
    >>> ref = ast.Subscript(
    ...     value=ast.Subscript(
    ...         value=ast.Name(id='a', ctx=ast.Load(), annotation=None),
    ...         slice=ast.Index(value=ast.Name('i', ast.Load(), None)),
    ...         ctx=ast.Load()),
    ...     slice=ast.Index(value=ast.Name(id='j',
    ...                                    ctx=ast.Load(), annotation=None)),
    ...     ctx=ast.Load())
    >>> ast.dump(get_variable(ref))
    "Name(id='a', ctx=Load(), annotation=None)"
    """
    msg = "Only name and subscript can be assigned."
    assert isinstance(assignable, (ast.Name, ast.Subscript)), msg
    while isinstance(assignable, ast.Subscript):
        assignable = assignable.value
    return assignable


@contextmanager
def pushpop(l, v):
    l.append(v)
    yield
    l.pop()

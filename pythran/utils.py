""" Common function use for AST manipulation. """

import gast as ast
from pythran.tables import MODULES
from functools import reduce


def attr_to_path(node):
    """ Compute path and final object for an attribute node """

    def get_intrinsic_path(modules, attr):
        """ Get function path and intrinsic from an ast.Attribute.  """
        if isinstance(attr, ast.Name):
            return modules[attr.id], (attr.id,)
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
                  path[1:], ast.Name(path[0], ast.Load(), None))


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

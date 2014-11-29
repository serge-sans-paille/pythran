""" Common function use for AST manipulation. """

import ast


def path_to_attr(path):
    """
    Transform path to ast.Attribute.

    >>> import ast
    >>> path = ('__builtin__', 'my', 'constant')
    >>> value = path_to_attr(path)
    >>> ref = ast.Attribute(
    ...     value=ast.Attribute(value=ast.Name(id="__builtin__",
    ...                                        ctx=ast.Load()),
    ...                         attr="my", ctx=ast.Load()),
    ...     attr="constant", ctx=ast.Load())
    >>> ast.dump(ref) == ast.dump(value)
    True
    """
    return reduce(lambda hpath, last: ast.Attribute(hpath, last, ast.Load()),
                  path[1:], ast.Name(path[0], ast.Load()))


def get_variable(assignable):
    """
    Return modified variable name.

    >>> import ast
    >>> ref = ast.Subscript(
    ...     value=ast.Subscript(
    ...         value=ast.Name(id='a', ctx=ast.Load()),
    ...         slice=ast.Index(value=ast.Name(id='i', ctx=ast.Load())),
    ...         ctx=ast.Load()),
    ...     slice=ast.Index(value=ast.Name(id='j', ctx=ast.Load())),
    ...     ctx=ast.Load())
    >>> ast.dump(get_variable(ref))
    "Name(id='a', ctx=Load())"
    """
    msg = "Only name and subscript can be assigned."
    assert isinstance(assignable, (ast.Name, ast.Subscript)), msg
    while isinstance(assignable, ast.Subscript):
        assignable = assignable.value
    return assignable

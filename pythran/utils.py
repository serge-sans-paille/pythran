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

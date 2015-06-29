import sys
import ast

if sys.version_info[0] >= 3:

    # ast.arguments has different signature in Py3
    def make_arguments(args, vararg, kwarg, defaults):
        return ast.arguments(args, vararg, [], [], kwarg, defaults)

    # FunctionDef has an extra returns parameter
    def make_FunctionDef(name, args, body, decorator_list):
        return ast.FunctionDef(name, args, body, decorator_list, None)

else:
    make_arguments = ast.arguments
    make_FunctionDef = ast.FunctionDef

ast.make_arguments = make_arguments
ast.make_FunctionDef = make_FunctionDef

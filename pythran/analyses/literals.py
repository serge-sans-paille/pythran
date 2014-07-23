"""
Literals lists nodes that are only literals
"""

from pythran.passmanager import FunctionAnalysis

import ast


class Literals(FunctionAnalysis):
    """
        Store variable that save only Literals (with no construction cost)
    """
    def __init__(self):
        self.result = set()
        super(Literals, self).__init__()

    def visit_Assign(self, node):
        # list, dict, set and other are not considered as Literals as they have
        # a constructor which may be costly and they can be updated using
        # function call
        basic_type = (ast.Num, ast.Lambda, ast.Str)
        if any(isinstance(node.value, type) for type in basic_type):
            targets_id = {target.id for target in node.targets
                          if isinstance(target, ast.Name)}
            self.result.update(targets_id)

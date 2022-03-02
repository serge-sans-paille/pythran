""" Intrinsics gathers all intrinsics referenced in a module. """

from pythran.passmanager import ModuleAnalysis
from pythran.analyses.aliases import StrictAliases
import pythran.intrinsic as intrinsic


class Intrinsics(ModuleAnalysis):

    """ Gather all intrinsics used in the module
    """

    def __init__(self):
        """ Result is a set of intrinsic values. """
        self.result = set()
        super(Intrinsics, self).__init__(StrictAliases)

    def visit_Attribute(self, node):
        for alias in self.strict_aliases.get(node, ()):
            if isinstance(alias, intrinsic.Intrinsic):
                self.result.add(alias)
        self.generic_visit(node)

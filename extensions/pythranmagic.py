"""
Pythran integration into IPython.

* provides the %%pythran magic function to ipython
"""
# -----------------------------------------------------------------------------
# Copyright (C) 2010-2011, IPython Development Team.
#
# Distributed under the terms of the Modified BSD License.
#
# The full license is in the file COPYING.txt, distributed with this software.
# -----------------------------------------------------------------------------

import imp
from IPython.core.magic import Magics, magics_class, cell_magic

import pythran


@magics_class
class PythranMagics(Magics):

    """ Class to make it possible to use pythran as a magic IPython command."""

    def __init__(self, shell):
        """ Init the pythran magic stuff. """
        super(PythranMagics, self).__init__(shell)
        self._reloads = {}

    def _import_all(self, module):
        """ Import only globals modules. """
        for k, v in module.__dict__.items():
            if not k.startswith('__'):
                self.shell.push({k: v})

    @cell_magic
    def pythran(self, line, cell):
        """
        Compile and import everything from a Pythran code cell.

        %%pythran
        #pythran export foo(int)
        def foo(x):
            return x + x
        """
        module_name = "pythranized"
        module_path = pythran.compile_pythrancode(module_name, cell)
        module = imp.load_dynamic(module_name, module_path)
        self._import_all(module)


def load_ipython_extension(ipython):
    """Load the extension in IPython."""
    ipython.register_magics(PythranMagics)

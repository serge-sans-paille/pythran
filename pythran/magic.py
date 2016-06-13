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

import hashlib
import imp
from IPython.core.magic import Magics, magics_class, cell_magic
from IPython.core import magic_arguments

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

    @magic_arguments.magic_arguments()
    @magic_arguments.argument('-D', action='append', default=[])
    @magic_arguments.argument('-O', action='append', default=[])
    @magic_arguments.argument('-march', action='append', default=[])
    @magic_arguments.argument('-fopenmp', action='store_true')
    @cell_magic
    def pythran(self, line, cell):
        """
        Compile and import everything from a Pythran code cell.

        %%pythran
        #pythran export foo(int)
        def foo(x):
            return x + x
        """
        args = magic_arguments.parse_argstring(self.pythran, line)
        kwargs = {}
        if args.D:
            kwargs['define_macros'] = args.D
        if args.O:
            kwargs.setdefault('extra_compile_args', []).extend(
                '-O' + str(x) for x in args.O)
        if args.march:
            kwargs.setdefault('extra_compile_args', []).extend(
                '-march=' + str(x) for x in args.march)
        if args.fopenmp:
            kwargs.setdefault('extra_compile_args', []).append(
                '-fopenmp')
            kwargs.setdefault('extra_link_args', []).append(
                '-fopenmp')
        m = hashlib.md5()
        m.update(cell)
        module_name = "pythranized_" + m.hexdigest()
        module_path = pythran.compile_pythrancode(module_name, cell, **kwargs)
        module = imp.load_dynamic(module_name, module_path)
        self._import_all(module)


def load_ipython_extension(ipython):
    """Load the extension in IPython."""
    ipython.register_magics(PythranMagics)

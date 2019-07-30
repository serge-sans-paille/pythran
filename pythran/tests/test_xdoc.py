from __future__ import print_function

import doctest
import inspect
import os
import pytest
import sys
import unittest

import pythran
from pythran import transformations, analyses, optimizations, types, log


class TestDoctest(unittest.TestCase):

    """
    Enable automatic doctest integration to unittest.

    Every module in the pythran package is scanned for doctests
    and one test per module is created
    """

    @pytest.mark.skipif(sys.platform == "win32",
                        reason="We should create a file for windows.")
    def test_tutorial(self):
        failed, _ = doctest.testfile('../../docs/TUTORIAL.rst')
        self.assertEqual(failed, 0)

    @pytest.mark.skipif(sys.platform == "win32",
                        reason="We should create a file for windows.")
    def test_internal(self):
        tmpfile = self.adapt_rst('../../docs/INTERNAL.rst')
        failed, _ = doctest.testfile(tmpfile, False)
        self.assertEqual(failed, 0)
        os.remove(tmpfile)

    @pytest.mark.skipif(sys.platform == "win32",
                        reason="We should create a file for windows.")
    def test_cli(self):
        tmpfile = self.adapt_rst('../../docs/CLI.rst')
        failed, _ = doctest.testfile(tmpfile, False)
        self.assertEqual(failed, 0)
        os.remove(tmpfile)

    def adapt_rst(self, relative_path):
        """
        replace '$>' with '>>>' and execute theses command lines by creating a shell
        return the path of the new adapted tmp file
        """
        import re
        from tempfile import NamedTemporaryFile
        filepath = os.path.join(os.path.dirname(__file__), relative_path)
        with open(filepath) as rst_doc:
            # hidden doctest
            sp = re.sub(r'\.\.(\s+>>>)', r'\1', rst_doc.read())

        # hack to support setuptools-generated pythran / pythran-config scripts
        for tool, sub in (('pythran-config', 'python -m pythran.config'),
                          ('pythran', 'python -m pythran.run'),
                          ('python', sys.executable)):
            sp = re.sub(r'(\$>.*?[^#])\b' + tool + r'\b([^-.].*)$',
                        r'\1' + sub + r'\2',
                        sp,
                        flags=re.MULTILINE)

        # convert shell doctest into python ones
        sp = re.sub(r'\$>(.*?)$',
                    r'>>> from __future__ import print_function ; import subprocess ; res = subprocess.check_output("\1", shell=True).decode("ascii").strip() ; print(res, end="")',
                    sp,
                    flags=re.MULTILINE)
        f = NamedTemporaryFile("w", delete=False)
        f.write(sp)
        f.close()
        return f.name

def generic_test_package(self, mod):
    # disable logging during doctest
    log.logging.getLogger('pythran').setLevel(log.logging.ERROR)

    failed, _ = doctest.testmod(mod)
    self.assertEqual(failed, 0)

def add_module_doctest(base, module_name):
    module = getattr(base, module_name)
    if inspect.ismodule(module):
        setattr(TestDoctest, 'test_' + module_name,
            lambda self: generic_test_package(self, module))

# doctest does not goes through imported variables,
# so manage the tests manually here
for module in (pythran, transformations, analyses, optimizations, types):
    for submodule in dir(module):
        add_module_doctest(module, submodule)

if __name__ == '__main__':
    unittest.main()

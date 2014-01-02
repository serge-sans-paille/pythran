import unittest
import doctest
import pythran
import inspect
import os

class TestDoctest(unittest.TestCase):
    '''
    Enable automatic doctest integration to unittest

    Every module in the pythran package is scanned for doctests
    and one test per module is created
    '''
    def test_tutorial(self):
        failed, _ = doctest.testfile('../../doc/TUTORIAL.rst')
        self.assertEqual(failed, 0)

    def test_internal(self):
        tmpfile = self.adapt_rst('../../doc/INTERNAL.rst')
        failed, _ = doctest.testfile(tmpfile, False)
        self.assertEqual(failed, 0)
        os.remove(tmpfile)

    def test_cli(self):
        tmpfile = self.adapt_rst('../../doc/CLI.rst')
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
        rst_doc = file(filepath).read()
        rst_doc = re.sub(r'\.\.(\s+>>>)', r'\1', rst_doc)  # hidden doctest
        sp = re.sub(r'\$>(.*?)$',
                    r'>>> import subprocess ; print subprocess.check_output("\1", shell=True),',
                    rst_doc,
                    flags=re.MULTILINE)
        f = NamedTemporaryFile(delete=False)
        f.write(sp)
        f.close()
        return f.name

def generic_test_package(self, mod):
    failed, _ = doctest.testmod(mod)
    self.assertEqual(failed, 0)

def add_module_doctest(module_name):
    module = getattr(pythran, module_name)
    if inspect.ismodule(module):
        setattr(TestDoctest, 'test_' + module_name,
            lambda self: generic_test_package(self, module))

map(add_module_doctest, dir(pythran))

if __name__ == '__main__':
    unittest.main()

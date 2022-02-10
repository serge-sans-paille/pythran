from tempfile import mkstemp
from pythran.tests import TestEnv

import unittest

from pythran.typing import List


class TestFile(TestEnv):

    def __init__(self, *args, **kwargs):
        super(TestFile, self).__init__(*args, **kwargs)
        self.file_content = """azerty\nqwerty\n\n"""

    def tempfile(self):
        filename=mkstemp()[1]
        with open(filename,"w") as f:
            f.write(self.file_content)
        self.filename = filename
        return filename

    def reinit_file(self):
        with open(self.filename,"w") as f:
            f.write(self.file_content)
        return self.filename

    def test_filename_only_constructor(self):
        filename=mkstemp()[1]
        self.run_test("""
            def filename_only_constructor(filename):
                open(filename).close()""",
            filename, filename_only_constructor=[str])

    def test_open_write(self):
        filename=mkstemp()[1]
        self.run_test("""
            def _open_write(filename):
                f = open(filename,"w+")
                f.write("azert")
                f.close()""",
            filename, _open_write=[str])
        with open(filename) as fd:
            self.assertEqual(fd.read(), "azert")

    def test_open_append(self):
        filename=mkstemp()[1]
        self.run_test("""
            def _open_append(filename):
                f = open(filename,"a")
                f.write("azert")
                f.close()""",
            filename,
            _open_append=[str])
        with open(filename) as fd:
            # * 2 because it's opened by python then pythran
            self.assertEqual(fd.read(), "azert"*2)

    def test_writing_mode_constructor(self):
        # Expecting file to be erased.
        # But python execution of test will erase it before pythran can :s
        self.tempfile()
        self.run_test("""
            def writing_mode_constructor(filename):
                f = open(filename, "w")
                f.close()""",
            self.filename,prelude=self.reinit_file, writing_mode_constructor=[str])

        with open(self.filename) as fd:
            self.assertEqual(fd.read(), "")

    def test_write(self):
        self.filename=mkstemp()[1]
        content="""q2\naze23\n"""
        self.run_test("""def _write(filename):\n f=open(filename,'a+')\n n = f.write("""+str('str("""q2\naze23\n""")')+""")\n f.close()\n return n""", self.filename, _write=[str])

        with open(self.filename) as fd:
            self.assertEqual(fd.read(), content * 2)

    def test_writelines(self):
        self.filename=mkstemp()[1]
        content=["azerty", "qsdfgh", "12345524"]
        self.run_test("""
            def _writelines(filename,_content):
                f = open(filename,'a+')
                f.writelines(_content)
                f.close()""",
            self.filename, content, _writelines=[str, List[str]])

        with open(self.filename) as fd:
            self.assertEqual(fd.read(), str().join(content)*2)

    def test_close(self):
        filename=mkstemp()[1]
        self.run_test("""
            def file_close(filename):
                f = open(filename,'w')
                f.close()
                try:
                    f.write("q")
                except:
                    pass""",
            filename, file_close=[str])

    def test_truncate(self):
        self.tempfile()
        self.run_test("""
            def _truncate(filename):
                f = open(filename)
                f.truncate(3)
                c = f.read()
                f.close()
                return c""",
            self.filename, _truncate=[str])

    def test_read(self):
        self.tempfile()
        self.run_test("""
            def _read(filename):
                f = open(filename)
                c = f.read()
                f.close()
                return c""", self.filename, _read=[str])

    def test_read_size(self):
        self.tempfile()
        self.run_test("""
            def _read_size(filename, size):
                f = open(filename)
                c = f.read(size)
                f.close()
                return c""", self.filename, 10, _read_size=[str, int])

    def test_read_oversize(self):
        self.tempfile()
        self.run_test("""
            def _read_oversize(filename, size):
                f = open(filename)
                c =  f.read(size)
                f.close()
                return c""", self.filename, len(self.file_content)+5, _read_oversize=[str, int])

    def test_readline(self):
        self.tempfile()
        self.run_test("""
            def _readline(filename):
                f = open(filename)
                c = [f.readline(),f.readline(), f.readline(),f.readline(),f.readline()]
                f.close()
                return c""", self.filename, _readline=[str])

    def test_readline_size(self):
        self.tempfile()
        self.run_test("""
            def _readline_size(filename):
                f = open(filename)
                c = [f.readline(7),f.readline(3),f.readline(4),f.readline(),f.readline(10)]
                f.close()
                return c""", self.filename, _readline_size=[str])

    def test_readline_size_bis(self):
        self.tempfile()
        self.run_test("""
            def _readline_size_bis(filename):
                f = open(filename)
                c = [f.readline(4),f.readline(3),f.readline(10),f.readline(),f.readline(5)]
                f.close()
                return c""", self.filename, _readline_size_bis=[str])

    def test_readlines(self):
        self.tempfile()
        self.run_test("""
            def _readlines(filename):
                f = open(filename)
                c = f.readlines()
                f.close()
                return c""", self.filename, _readlines=[str])

    def test_offset_read(self):
        self.tempfile()
        self.run_test("""
            def _offset_read(filename):
                f = open(filename)
                f.seek(5)
                c = f.read()
                f.close()
                return c""", self.filename, _offset_read=[str])

    def test_offset_write(self):
        self.tempfile()
        self.run_test("""
            def _offset_write(filename):
                f = open(filename, "a")
                f.seek(5)
                f.write("aze")
                f.close()
                f = open(filename,"r")
                c = f.read()
                f.close()
                return c""", self.filename, prelude = self.reinit_file, _offset_write=[str])

    def test_next(self):
        self.tempfile()
        self.run_test("""
            def _next(filename):
                f = open(filename)
                c = [next(f), next(f)]
                f.close()
                return c
                """, self.filename, _next=[str])

    def test_iter(self):
        self.tempfile()
        self.run_test("""
            def _iter(filename):
                f = open(filename)
                c = [l for l in f]
                f.close()
                return c""", self.filename, _iter=[str])

    def test_fileno(self):
        self.tempfile()
        # Useless to check if same fileno, just checking if fct can be called
        self.run_test("""
            def _fileno(filename):
                f = open(filename)
                a = f.fileno()
                c = a!= 0
                f.close()
                return c""", self.filename, _fileno=[str])

    def test_isatty(self):
        self.tempfile()
        self.run_test("""
            def _isatty(filename):
                f = open(filename)
                c = f.isatty()
                f.close()
                return c""", self.filename, _isatty=[str])

    def test_truncate(self):
        self.tempfile()
        self.run_test("""
            def _truncate(filename):
                f = open(filename, 'a')
                f.seek(3)
                f.truncate()
                f.close()
                f = open(filename)
                c = f.read()
                f.close()
                return c""", self.filename, _truncate=[str])

    def test_truncate_size(self):
        self.tempfile()
        self.run_test("""
            def _truncate_size(filename):
                f = open(filename, 'a')
                f.truncate(4)
                f.close()
                f = open(filename)
                c = f.read()
                f.close()
                return c""", self.filename, _truncate_size=[str])

    def test_flush(self):
        self.tempfile()
        # Don't know how to check properly, just checking fct call.
        self.run_test("""
            def _flush(filename):
                f = open(filename, 'a')
                f.flush()
                f.close()""", self.filename, _flush=[str])

    def test_tell(self):
        self.tempfile()
        self.run_test("""
            def _tell(filename):
                f = open(filename)
                f.read(3)
                c = f.tell()
                f.close()
                return c""", self.filename, _tell=[str])

    def test_seek(self):
        self.tempfile()
        self.run_test("""
            def _seek(filename):
                f = open(filename, 'a')
                f.seek(3)
                c = f.tell()
                f.close()
                return c""", self.filename, _seek=[str])

    def test_attribute_closed(self):
        self.tempfile()
        self.run_test("""
            def _attribute_closed(filename):
                f = open(filename, 'a')
                c = f.closed
                f.close()
                return c""", self.filename, _attribute_closed=[str])

    def test_attribute_name(self):
        self.tempfile()
        self.run_test("""
            def _attribute_name(filename):
                f = open(filename, 'a')
                c = f.name
                f.close()
                return c""", self.filename, _attribute_name=[str])

    def test_attribute_mode(self):
        self.tempfile()
        self.run_test("""
            def _attribute_mode(filename):
                f = open(filename, 'a')
                c = f.mode
                f.close()
                return c""", self.filename, _attribute_mode=[str])

    def test_attribute_newlines(self):
        self.tempfile()
        self.run_test("""
            def _attribute_newlines(filename):
                f = open(filename, 'a')
                c = f.newlines
                f.close()
                return c""", self.filename, _attribute_newlines=[str])

    def test_map_iter(self):
        self.tempfile()
        self.run_test("""
            def _map_iter(filename):
                f = open(filename)
                c = list(map(lambda s: len(s), f))
                f.close()
                return c""", self.filename, _map_iter=[str])

    # The following tests insures the PROXY compatibility with rvalues
    # Note that it doesn't close the file which is not a good idea...
    def test_rvalue_write(self):
        self.filename=mkstemp()[1]
        self.run_test("""def _rvalue_write(filename):\n open(filename,'a+').write("aze")""", self.filename, _rvalue_write=[str])

    def test_rvalue_writelines(self):
        self.filename=mkstemp()[1]
        self.run_test("""def _rvalue_writelines(filename):\n open(filename,'a+').writelines(["azerty", "qsdfgh", "12345524"])""", self.filename, _rvalue_writelines=[str])

    def test_rvalue_close(self):
        filename=mkstemp()[1]
        self.run_test("""
            def _rvalue_close(filename):
                open(filename,'w').close()""", filename, _rvalue_close=[str])

    def test_rvalue_read(self):
        self.tempfile()
        self.run_test("def _rvalue_read(filename):\n return open(filename).read()", self.filename, _rvalue_read=[str])

    def test_rvalue_readline(self):
        self.tempfile()
        self.run_test("def _rvalue_readline(filename):\n return open(filename).readline()", self.filename, _rvalue_readline=[str])

    def test_rvalue_readlines(self):
        self.tempfile()
        self.run_test("def _rvalue_readlines(filename):\n return open(filename).readlines()", self.filename, _rvalue_readlines=[str])

    def test_rvalue_next(self):
        self.tempfile()
        self.run_test("""def _rvalue_next(filename):\n return next(open(filename))""", self.filename, _rvalue_next=[str])

    def test_rvalue_fileno(self):
        self.tempfile()
        # Useless to check if same fileno, just checking if fct can be called
        self.run_test("""def _rvalue_fileno(filename):\n open(filename).fileno()""", self.filename, _rvalue_fileno=[str])

    def test_rvalue_isatty(self):
        self.tempfile()
        self.run_test("""def _rvalue_isatty(filename):\n return open(filename).isatty()""", self.filename, _rvalue_isatty=[str])

    def test_rvalue_truncate(self):
        self.tempfile()
        self.run_test("""def _rvalue_truncate(filename):\n open(filename, 'a').truncate(3)""", self.filename, _rvalue_truncate=[str])

    def test_rvalue_flush(self):
        self.tempfile()
        self.run_test("""def _rvalue_flush(filename):\n open(filename, 'a').flush()""", self.filename, _rvalue_flush=[str])

    def test_rvalue_tell(self):
        self.tempfile()
        self.run_test("""def _rvalue_tell(filename):\n return open(filename, 'a').tell()""", self.filename, _rvalue_tell=[str])

    def test_rvalue_seek(self):
        self.tempfile()
        self.run_test("""def _rvalue_seek(filename):\n open(filename, 'a').seek(3)""", self.filename, _rvalue_seek=[str])

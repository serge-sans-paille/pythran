from test_env import TestEnv
from textwrap import dedent
import pythran

class TestImportAll(TestEnv):

    def test_import_all(self):
        self.run_test("from math import *\ndef import_all(l): return cos(l)", 3.3, import_all=[float])

    def test_import_cmath_all(self):
        self.run_test("from cmath import *\ndef import_cmath_all(l): return cos(l)", 2.2, import_cmath_all=[float])

    def test_import_all_cos(self):
        self.run_test("from math import *\nfrom math import cos\ndef import_all_cos(l): return cos(l)", 1.1, import_all_cos=[float])

    def test_import_all_twice(self):
        self.run_test("from math import *\nfrom math import *\ndef import_all_twice(l): return cos(l)", 0.1, import_all_twice=[float])

    def test_import_same_name(self):
        self.run_test("from math import *\ndef cos(l): return 100", 0.1, cos=[float])

    def test_import_collections(self):
        """
        Check correct error is returned for incorrect module import.

        Check is done for module as .py file.
        """
        code = """
            import collections
            def unsupported_module():
                return collections.Counter()"""

        with self.assertRaises(pythran.syntax.PythranSyntaxError) as ex:
            pythran.compile_pythrancode("flamby", dedent(code))

        self.assertEqual(ex.exception.message,
                         "Unpythranizable module: collections")

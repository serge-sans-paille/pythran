from pythran.tests import TestEnv

import unittest
import sys

class TestArray(TestEnv):

    @unittest.skipIf(sys.implementation.name == 'pypy', "non supported upstream")
    def test_typecodes(self):
        self.run_test("def typecodes_(i): import array; return array.typecodes[i]",
                      2, typecodes_=[int])

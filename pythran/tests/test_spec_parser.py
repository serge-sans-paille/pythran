import unittest
from pythran import SpecParser
import os.path

#pythran export a((float,(int,long),str list) list list)
#pythran export a(str)
#pythran export a( (str,str), int, long list list)

class TestSpecParser(unittest.TestCase):

    def test_parser(self):
        sp = SpecParser()
        print sp(os.path.realpath(__file__))

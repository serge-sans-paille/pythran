import numpy
import pytest
import sys
import unittest

from pythran.tests import TestEnv
from pythran.typing import *

class TestBase(TestEnv):
    def test_simple_ann_stmt(self):
        self.run_test("def simple_ann_stmt(a):\n b: int = a; return b, b",
                      1,
                      simple_ann_stmt=[int])

    def test_dead_ann_stmt(self):
        self.run_test("def dead_ann_stmt(a): b: float = 2; return a",
                      1,
                      dead_ann_stmt=[int])

    def test_fwd_ann_stmt(self):
        self.run_test("def fwd_ann_stmt(a): b: float; b = 1.; return a + b",
                      1,
                      fwd_ann_stmt=[int])

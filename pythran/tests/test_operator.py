from test_env import TestEnv

class TestOperator(TestEnv):

    def test_lt(self):
        self.run_test("def lt(a,b):\n from operator import lt\n return lt(a,b)", 1, 2, lt=[int,int])

    def test_le(self):
        self.run_test("def le(a,b):\n from operator import le\n return le(a,b)", 1, 2, le=[int,int])

    def test_eq(self):
        self.run_test("def eq(a,b):\n from operator import eq\n return eq(a,b)", 2, 2, eq=[int,int])

    def test_ne(self):
        self.run_test("def ne(a,b):\n from operator import ne\n return ne(a,b)", 2, 2, ne=[int,int])

    def test_ge(self):
        self.run_test("def ge(a,b):\n from operator import ge\n return ge(a,b)", 2, 2, ge=[int,int])

    def test_gt(self):
        self.run_test("def gt(a,b):\n from operator import gt\n return gt(a,b)", 2, 2, gt=[int,int])

    def test___lt__(self):
        self.run_test("def __lt__(a,b):\n from operator import __lt__\n return __lt__(a,b)", 2, 2, __lt__=[int,int])

    def test___le__(self):
        self.run_test("def __le__(a,b):\n from operator import __le__\n return __le__(a,b)", 2, 2, __le__=[int,int])

    def test___eq__(self):
        self.run_test("def __eq__(a,b):\n from operator import __eq__\n return __eq__(a,b)", 2, 2, __eq__=[int,int])

    def test___ne__(self):
        self.run_test("def __ne__(a,b):\n from operator import __ne__\n return __ne__(a,b)", 2, 2, __ne__=[int,int])

    def test___ge__(self):
        self.run_test("def __ge__(a,b):\n from operator import __ge__\n return __ge__(a,b)", 2, 2, __ge__=[int,int])

    def test___gt__(self):
        self.run_test("def __gt__(a,b):\n from operator import __gt__\n return __gt__(a,b)", 2, 2, __gt__=[int,int])

    def test_not_(self):
        self.run_test("def not_(a):\n from operator import not_\n return not_(a)", True, not_=[bool])

    def test___not__(self):
        self.run_test("def __not__(a):\n from operator import __not__\n return __not__(a)", True, __not__=[bool])

    def test_truth(self):
        self.run_test("def truth(a):\n from operator import truth\n return truth(a)", True, truth=[bool])

    def test_is_(self):
        self.run_test("def is_(a,b):\n from operator import is_\n return is_(a,b)", 2, 2, is_=[int,int])

    def test_is_not(self):
        self.run_test("def is_not(a,b):\n from operator import is_not\n return is_not(a,b)", 1, 2, is_not=[int,int])

    def test_abs(self):
        self.run_test("def abs(a):\n from operator import abs\n return abs(a)", -1, abs=[int])

    def test___abs__(self):
        self.run_test("def __abs__(a):\n from operator import __abs__\n return __abs__(a)", -2, __abs__=[int])

    def test__add_(self):
        self.run_test("def add(a,b):\n from operator import add\n return add(a,b)", -1, 2, add=[int,int])

    def test___add__(self):
        self.run_test("def __add__(a,b):\n from operator import __add__\n return __add__(a,b)", -1, 2, __add__=[int,int])

    def test_and_(self):
        self.run_test("def and_(a,b):\n from operator import and_\n return and_(a,b)", 0x01, 0x02, and_=[int,int])

    def test___and__(self):
        self.run_test("def __and__(a,b):\n from operator import __and__\n return __and__(a,b)", 0x01, 0x02, __and__=[int,int])

    def test_div(self):
        self.run_test("def div(a,b):\n from operator import div\n return div(a,b)", 5, 2, div=[int,int])

    def test___div__(self):
        self.run_test("def __div__(a,b):\n from operator import __div__\n return __div__(a,b)", 5, 2, __div__=[int,int])

    def test_floordiv(self):
        self.run_test("def floordiv(a,b):\n from operator import floordiv\n return floordiv(a,b)", 5, 2, floordiv=[int,int])

    def test___floordiv__(self):
        self.run_test("def __floordiv__(a,b):\n from operator import __floordiv__\n return __floordiv__(a,b)", 5, 2, __floordiv__=[int,int])

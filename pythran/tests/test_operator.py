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

    def test_inv(self):
        self.run_test("def inv(a):\n from operator import inv\n return inv(a)", 0x02, inv=[int])

    def test_invert(self):
        self.run_test("def invert(a):\n from operator import invert\n return invert(a)", 0x02, invert=[int])

    def test___inv__(self):
        self.run_test("def __inv__(a):\n from operator import __inv__\n return __inv__(a)", 0x02, __inv__=[int])

    def test___invert__(self):
        self.run_test("def __invert__(a):\n from operator import __invert__\n return __invert__(a)", 0x02, __invert__=[int])

    def test_lshift(self):
        self.run_test("def lshift(a,b):\n from operator import lshift\n return lshift(a,b)", 0x02, 1, lshift=[int,int])

    def test___lshift__(self):
        self.run_test("def __lshift__(a,b):\n from operator import __lshift__\n return __lshift__(a,b)",0x02 , 1, __lshift__=[int,int])

    def test_mod(self):
        self.run_test("def mod(a,b):\n from operator import mod\n return mod(a,b)", 5, 2, mod=[int,int])

    def test___mod__(self):
        self.run_test("def __mod__(a,b):\n from operator import __mod__\n return __mod__(a,b)", 5, 2, __mod__=[int,int])

    def test_mul(self):
        self.run_test("def mul(a,b):\n from operator import mul\n return mul(a,b)", 5, 2, mul=[int,int])

    def test___mul__(self):
        self.run_test("def __mul__(a,b):\n from operator import __mul__\n return __mul__(a,b)", 5, 2, __mul__=[int,int])

    def test_neg(self):
        self.run_test("def neg(a):\n from operator import neg\n return neg(a)", 1, neg=[int])

    def test___neg__(self):
        self.run_test("def __neg__(a):\n from operator import __neg__\n return __neg__(a)", 1, __neg__=[int])

    def test_or_(self):
        self.run_test("def or_(a,b):\n from operator import or_\n return or_(a,b)", 0x02, 0x01, or_=[int,int])

    def test___or__(self):
        self.run_test("def __or__(a,b):\n from operator import __or__\n return __or__(a,b)", 0x02, 0x01, __or__=[int,int])

    def test_pos(self):
        self.run_test("def pos(a):\n from operator import pos\n return pos(a)", 2, pos=[int])

    def test___pos__(self):
        self.run_test("def __pos__(a):\n from operator import __pos__\n return __pos__(a)", 2, __pos__=[int])

    def test_rshift(self):
        self.run_test("def rshift(a,b):\n from operator import rshift\n return rshift(a,b)", 0x02, 1, rshift=[int,int])

    def test___rshift__(self):
        self.run_test("def __rshift__(a,b):\n from operator import __rshift__\n return __rshift__(a,b)", 0x02, 1, __rshift__=[int,int])

    def test_sub(self):
        self.run_test("def sub(a,b):\n from operator import sub\n return sub(a,b)", 5, 2, sub=[int,int])

    def test___sub__(self):
        self.run_test("def __sub__(a,b):\n from operator import __sub__\n return __sub__(a,b)", 5, 2, __sub__=[int,int])

    def test_truediv(self):
        self.run_test("def truediv(a,b):\n from operator import truediv\n return truediv(a,b)", 5, 2, truediv=[int,int])

    def test___truediv__(self):
        self.run_test("def __truediv__(a,b):\n from operator import __truediv__\n return __truediv__(a,b)", 5, 2, __truediv__=[int,int])

    def test___xor__(self):
        self.run_test("def __xor__(a,b):\n from operator import __xor__\n return __xor__(a,b)", 0x02, 0x01, __xor__=[int,int])


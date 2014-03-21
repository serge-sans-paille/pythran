import unittest
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

    def test_iadd(self):
        self.run_test("def iadd(a,b):\n from operator import iadd\n return iadd(a,b)", -1, 3, iadd=[int,int])

    def test_iadd_argument_modification_not_mutable(self):
        self.run_test("def iadd2(b):\n a = -1\n from operator import iadd\n iadd(a,b)\n return a", 3, iadd2=[int])

    def test_iadd_argument_modification_mutable(self):
        self.run_test("def iadd3(b):\n a = []\n from operator import iadd\n iadd(a,b)\n return a", [3], iadd3=[[int]])

    def test_iadd_argument_modification_mutable2(self):
        self.run_test("def iadd4(b):\n from operator import iadd\n return iadd([],b)", [3], iadd4=[[int]])

    def test___iadd__(self):
        self.run_test("def __iadd__(a,b):\n from operator import __iadd__\n return __iadd__(a,b)", 1, -4, __iadd__=[int,int])

    def test___iadd___argument_modification_not_mutable(self):
        self.run_test("def __iadd2__(b):\n a = -1\n from operator import __iadd__\n __iadd__(a,b)\n return a", 3, __iadd2__=[int])

    def test___iadd___argument_modification_mutable(self):
        self.run_test("def __iadd3__(b):\n a = []\n from operator import __iadd__\n __iadd__(a,b)\n return a", [3], __iadd3__=[[int]])

    def test___iadd___argument_modification_mutable2(self):
        self.run_test("def __iadd4__(b):\n from operator import __iadd__\n return __iadd__([],b)", [3], __iadd4__=[[int]])


    def test_iand(self):
        self.run_test("def iand(a,b):\n from operator import iand\n return iand(a,b)", 0x01, 0x11, iand=[int,int])

    def test_iand2(self):
        self.run_test("def iand2(b):\n from operator import iand\n a=0x01\n return iand(a,b)", 0x11, iand2=[int])

    def test_iand3(self):
        self.run_test("def iand3(b):\n from operator import iand\n a=0x01\n iand(a,b)\n return a", 0x11, iand3=[int])

    def test___iand__(self):
        self.run_test("def __iand__(a,b):\n from operator import __iand__\n return __iand__(a,b)", 0x10, 0xFF, __iand__=[int,int])

    def test_iconcat(self):
        self.run_test("def iconcat(a,b):\n from operator import iconcat\n return iconcat(a,b)", [3], [4], iconcat=[[int],[int]])

    def test_iconcat2(self):
        self.run_test("def iconcat2(b):\n from operator import iconcat\n a=[3]\n return iconcat(a,b)", [4], iconcat2=[[int]])

    def test_iconcat3(self):
        self.run_test("def iconcat3(b):\n from operator import iconcat\n a=[3]\n iconcat(a,b)\n return a", [4], iconcat3=[[int]])

    def test_iconcat4(self):
        self.run_test("def iconcat4(b):\n from operator import iconcat\n a=[]\n iconcat(a,b)\n return a", [4], iconcat4=[[int]])

    def test_iconcat5(self):
        self.run_test("def iconcat5(b):\n from operator import iconcat\n return iconcat([],b)", [4], iconcat5=[[int]])

    def test___iconcat__(self):
        self.run_test("def __iconcat__(a,b):\n from operator import __iconcat__\n return __iconcat__(a,b)", [3], [4], __iconcat__=[[int],[int]])

    def test_idiv(self):
        self.run_test("def idiv(a,b):\n from operator import idiv\n return idiv(a,b)", 5, 2, idiv=[int,int])

    def test_idiv2(self):
        self.run_test("def idiv2(b):\n from operator import idiv\n a=5\n return idiv(a,b)", 2, idiv2=[int])

    def test_idiv3(self):
        self.run_test("def idiv3(b):\n from operator import idiv\n a=5\n idiv(a,b)\n return a", 2, idiv3=[int])

    def test___idiv__(self):
        self.run_test("def __idiv__(a,b):\n from operator import __idiv__\n return __idiv__(a,b)", 5, 2, __idiv__=[int,int])

    def test_ifloordiv(self):
        self.run_test("def ifloordiv(a,b):\n from operator import ifloordiv\n return ifloordiv(a,b)", 5, 2, ifloordiv=[int,int])

    def test___ifloordiv__(self):
        self.run_test("def __ifloordiv__(a,b):\n from operator import __ifloordiv__\n return __ifloordiv__(a,b)", 5, 2, __ifloordiv__=[int,int])

    def test_ilshift(self):
        self.run_test("def ilshift(a,b):\n from operator import ilshift\n return ilshift(a,b)", 0x02, 3, ilshift=[int,int])

    def test___ilshift__(self):
        self.run_test("def __ilshift__(a,b):\n from operator import __ilshift__\n return __ilshift__(a,b)", 0x02, 3, __ilshift__=[int,int])

    def test_imod(self):
        self.run_test("def imod(a,b):\n from operator import imod\n return imod(a,b)", 4, 2, imod=[int,int])

    def test___imod__(self):
        self.run_test("def __imod__(a,b):\n from operator import __imod__\n return __imod__(a,b)", 5, 3, __imod__=[int,int])

    def test_imul(self):
        self.run_test("def imul(a,b):\n from operator import imul\n return imul(a,b)", 5, -1, imul=[int,int])

    def test___imul__(self):
        self.run_test("def __imul__(a,b):\n from operator import __imul__\n return __imul__(a,b)", -6.1, -2, __imul__=[float,int])

    def test_ior(self):
        self.run_test("def ior(a,b):\n from operator import ior\n return ior(a,b)", 0x02, 0x01, ior=[int,int])

    def test___ior__(self):
        self.run_test("def __ior__(a,b):\n from operator import __ior__\n return __ior__(a,b)", 0x02, 0x02, __ior__=[int,int])

    def test_ipow(self):
        self.run_test("def ipow(a,b):\n from operator import ipow\n return ipow(a,b)", 5, 5, ipow=[int,int])

    def test___ipow__(self):
        self.run_test("def __ipow__(a,b):\n from operator import __ipow__\n return __ipow__(a,b)", 2, 8, __ipow__=[int,int])

    def test_irshift(self):
        self.run_test("def irshift(a,b):\n from operator import irshift\n return irshift(a,b)", 0x02, 3, irshift=[int,int])

    def test___irshift__(self):
        self.run_test("def __irshift__(a,b):\n from operator import __irshift__\n return __irshift__(a,b)", 0x02, 1, __irshift__=[int,int])

    def test_isub(self):
        self.run_test("def isub(a,b):\n from operator import isub\n return isub(a,b)", 5, -8, isub=[int,int])

    def test___isub__(self):
        self.run_test("def __isub__(a,b):\n from operator import __isub__\n return __isub__(a,b)", -8, 5, __isub__=[int,int])

    def test_itruediv(self):
        self.run_test("def itruediv(a,b):\n from operator import itruediv\n return itruediv(a,b)", 5, 2, itruediv=[int,int])

    def test_itruediv2(self):
        self.run_test("def itruediv2(b):\n from operator import itruediv\n a=5\n return itruediv(a,b)", 2, itruediv2=[int])

    def test_itruediv3(self):
        self.run_test("def itruediv3(b):\n from operator import itruediv\n a=5\n itruediv(a,b)\n return a", 2, itruediv3=[int])

    def test___itruediv__(self):
        self.run_test("def __itruediv__(a,b):\n from operator import __itruediv__\n return __itruediv__(a,b)", 5, 2, __itruediv__=[int,int])

    def test_ixor(self):
        self.run_test("def ixor(a,b):\n from operator import ixor\n return ixor(a,b)", 0x02, 0x01, ixor=[int,int])

    def test___ixor__(self):
        self.run_test("def __ixor__(a,b):\n from operator import __ixor__\n return __ixor__(a,b)", 0x02, 0x02, __ixor__=[int,int])

    def test_concat(self):
        self.run_test("def concat(a,b):\n from operator import concat\n return concat(a,b)", [3], [4], concat=[[int],[int]])

    def test___concat__(self):
        self.run_test("def __concat__(a,b):\n from operator import __concat__\n return __concat__(a,b)", [], [1], __concat__=[[int],[int]])

    def test_contains(self):
        self.run_test("def contains(a,b):\n from operator import contains\n return contains(a,b)", [1,2,3,4], 2, contains=[[int],int])

    def test___contains__(self):
        self.run_test("def __contains__(a,b):\n from operator import __contains__\n return __contains__(a,b)", [1,2,3,4], 5, __contains__=[[int],int])

    def test_countOf(self):
        self.run_test("def countOf(a,b):\n from operator import countOf\n return countOf(a,b)", [1,2,3,4,3,3,3,2,3,1], 3, countOf=[[int],int])

    def test_delitem(self):
        self.run_test("def delitem(a,b):\n from operator import delitem\n return delitem(a,b)", [1,2,3,4], 3, delitem=[[int],int])

    def test___delitem__(self):
        self.run_test("def __delitem__(a,b):\n from operator import __delitem__\n return __delitem__(a,b)", [1,2,3,4], 2, __delitem__=[[int],int])

    def test_getitem(self):
        self.run_test("def getitem(a,b):\n from operator import getitem\n return getitem(a,b)", [4,3,2,1], 1, getitem=[[int],int])

    def test___getitem__(self):
        self.run_test("def __getitem__(a,b):\n from operator import __getitem__\n return __getitem__(a,b)", [4,3,2,1], 2, __getitem__=[[int],int])

    def test_indexOf(self):
        self.run_test("def indexOf(a,b):\n from operator import indexOf\n return indexOf(a,b)", [4,3,2,1], 4, indexOf=[[int],int])
         
    def test_itemgetter(self):
        self.run_test("def itemgetter(i,a):\n from operator import itemgetter\n g = itemgetter(i)\n return g(a)", 2, [4,3,2,1], itemgetter=[int,[int]])

    def test_itemgetter2(self):
       self.run_test("def foo():\n from operator import itemgetter\n g = itemgetter(1)", foo=[])

    def test_itemgetter3(self):
        self.run_test("def itemgetter3(i,j,k,a):\n from operator import itemgetter\n g = itemgetter(i,j,k)\n return g(a)", 2, 3, 4, [4,3,2,1,0], itemgetter3=[int,int,int,[int]])

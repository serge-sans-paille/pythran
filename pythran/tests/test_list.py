from pythran.tests import TestEnv
from pythran.typing import List, NDArray
import numpy as np

class TestList(TestEnv):
    def test_contains_(self):
        self.run_test("def contains_(a):\n b=[1,2,3,8,7,4]\n return a in b",
                      8,
                      contains_=[int])

    def test_contains_slice(self):
        self.run_test("def contains_slice(a):\n b=[1,2,3,8,7,4]\n return a in b[1:a//2]",
                      8,
                      contains_slice=[int])

    def test_extend_(self):
        self.run_test("def extend_(a):\n b=[1,2,3]\n b.extend(a)\n return b", [1.2], extend_=[List[float]])

    def test_remove_(self):
        self.run_test("def remove_(a):\n b=[1,2,3]\n b.remove(a)\n return b", 2, remove_=[int])

    def test_index_(self):
        self.run_test("def index_(a):\n b=[1,2,3,8,7,4]\n return b.index(a)", 8, index_=[int])

    def test_index_tuple(self):
        self.run_test("def index_tuple(a):\n b=[1,2,3,8,7,4]\n return tuple(b).index(a)", 1, index_tuple=[int])

    def test_clear_(self):
        self.run_test("def clear_():\n b=[1,3,4,5,6,7]\n b.clear()\n return b", clear_=[])
        
    def test_pop_(self):
        self.run_test("def pop_(a):\n b=[1,3,4,5,6,7]\n return b.pop(a)", 2, pop_=[int])

    def test_popnegatif_(self):
        self.run_test("def popnegatif_(a):\n b=[1,3,4,5,6,7]\n return b.pop(a)", -2, popnegatif_=[int])

    def test_popempty_(self):
        self.run_test("def popempty_():\n b=[1,3,4,5,6,7]\n return b.pop()", popempty_=[])

    def test_count_(self):
        self.run_test("def count_(a):\n b=[1,3,4,5,3,7]\n return b.count(a)",3, count_=[int])

    def test_count_slice(self):
        self.run_test("def count_slice(a):\n b=[1,3,4,5,3,7]\n return b[:a].count(a)",3, count_slice=[int])

    def test_reverse_(self):
        self.run_test("def reverse_():\n b=[1,2,3]\n b.reverse()\n return b", reverse_=[])

    def test_sort_(self):
        self.run_test("def sort_():\n b=[1,3,5,4,2]\n b.sort()\n return b", sort_=[])

    def test_sort_key(self):
        self.run_test("def sort_key(n):\n b=[(1,3),(5,4),(2,n)]\n b.sort(key=lambda x: x[1])\n return b", 1, sort_key=[int])

    def test_insert_(self):
        self.run_test("def insert_(a,b):\n c=[1,3,5,4,2]\n c.insert(a,b)\n return c",2,5, insert_=[int,int])

    def test_mult_0(self):
        self.run_test("def mult_0(a):\n b=[1,2,3,8,7,4]\n b*=a\n return b",
                      8,
                      mult_0=[int])

    def test_mult_1(self):
        self.run_test("def mult_1(a):\n b=[1,2,3,8,7,4] * a\n return b",
                      8,
                      mult_1=[int])


    def test_insertneg_(self):
        self.run_test("def insertneg_(a,b):\n c=[1,3,5,4,2]\n c.insert(a,b)\n return c",-1,-2, insertneg_=[int,int])

    def test_subscripted_slice(self):
        self.run_test("def subscripted_slice(l): a=l[2:6:2] ; return a[1]", list(range(10)), subscripted_slice=[List[int]])

    def test_list_comparison(self):
        self.run_test("def list_comparison(l): return max(l)", [[1,2,3],[1,4,1],[1,4,8,9]], list_comparison=[List[List[int]]])

    def test_list_comparison0(self):
        self.run_test("def list_comparison0(l0, l1):"
                      " return l0 < l1, l0 == l1, l0 <= l1, l0 > l1, l0 >= l1, l0 != l1",
                      [1,2,3],
                      [1, 2],
                      list_comparison0=[List[int], List[int]])

    def test_list_comparison1(self):
        self.run_test("def list_comparison1(l0, l1):"
                      " return l0 < l1, l0 == l1, l0 <= l1, l0 > l1, l0 >= l1, l0 != l1",
                      [3],
                      [1],
                      list_comparison1=[List[int], List[int]])

    def test_list_comparison2(self):
        self.run_test("def list_comparison2(l0, l1):"
                      " return l0 < l1, l0 == l1, l0 <= l1, l0 > l1, l0 >= l1, l0 != l1",
                      [3],
                      [1, 2],
                      list_comparison2=[List[int], List[int]])

    def test_list_comparison3(self):
        self.run_test("def list_comparison3(l0, l1):"
                      " return l0 < l1, l0 == l1, l0 <= l1, l0 > l1, l0 >= l1, l0 != l1",
                      [1,2,3],
                      [1,2,4],
                      list_comparison3=[List[int], List[int]])

    def test_list_equal_comparison_true(self):
        self.run_test("def list_comparison_true(l1,l2):  return l1==l2",
                      [1,2,3],[1,4,1], list_comparison_true=[List[int],List[int]])

    def test_list_equal_comparison_false(self):
        self.run_test("def list_comparison_false(l1,l2): return l1==l2",
                      [1,4,1],[1,4,1], list_comparison_false=[List[int],List[int]])

    def test_list_equal_comparison_different_sizes(self):
        self.run_test("def list_comparison_different_sizes(l1,l2): return l1==l2",
                      [1,4,1],[1,4,1,5], list_comparison_different_sizes=[List[int],List[int]])

    def test_list_unequal_comparison_false(self):
        self.run_test("def list_comparison_unequal_false(l1,l2):  return l1!=l2",
                      [1,2,3],[1,4,1], list_comparison_unequal_false=[List[int],List[int]])

    def test_list_unequal_comparison_true(self):
        self.run_test("def list_comparison_unequal_true(l1,l2): return l1!=l2",
                      [1,4,1],[1,4,1], list_comparison_unequal_true=[List[int],List[int]])

    def test_list_unequal_comparison_different_sizes(self):
        self.run_test("def list_unequal_comparison_different_sizes(l1,l2): return l1!=l2",
                      [1,4,1],[1,4,1,5], list_unequal_comparison_different_sizes=[List[int],List[int]])

    def test_assigned_slice(self):
        self.run_test("def assigned_slice(l): l[0]=l[2][1:3] ; return l",
                      [[1,2,3],[1,4,1],[1,4,8,9]],
                      assigned_slice=[List[List[int]]])

    def test_assigned_self_slice0(self):
        self.run_test("def assigned_self_slice0(t): l = [t,-1,-1]; l[2] = 0;  l[:2]=l[1:] ; return l",
                      -5,
                      assigned_self_slice0=[int])

    def test_assigned_self_slice1(self):
        self.run_test("def assigned_self_slice1(t): l = [t,-1,-1]; l[2] = 0;  l[1:]=l[:2] ; return l",
                      -5,
                      assigned_self_slice1=[int])

    def test_add_list_of_arrays(self):
        self.run_test("def add_list_of_arrays(x, y): return x + y",
                      [np.array([1,2])],
                      [np.array([3,4])],
                      add_list_of_arrays=[List[NDArray[int, :]], List[NDArray[int, :]]])

    def test_slice_get_item_assign(self):
        self.run_test('def slice_get_item_assign(x): y = x[:]; y.remove(0); return x, y',
                      [0, 1,2,3],
                      slice_get_item_assign=[List[int]])

    def test_init_array_empty_list(self):
        code = '''
def init_array_empty_list(X,f):
    A = []
    for i in range(int(f)):
        if i==0: A = f*X[:,i]
        else: A+=f*X[:,i]
    return A'''
        self.run_test(
            code,
            np.array([[2,3],[4,5]]), 1.,
            init_array_empty_list=[NDArray[int, :,:], float])

    def test_pop_while_iterating(self):
        code = '''
            def pop_while_iterating(n):
                AA=[[n,2,3],[n,2,3],[1,2,3],[1,2,3],[1,2,3],[1,n,3]]
                for ii in range(len(AA)):
                    AA.pop()
                return AA'''
        self.run_test(code,
                      0,
                      pop_while_iterating=[int])

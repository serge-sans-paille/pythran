from test_env import TestEnv

class TestList(TestEnv):

    def test_extend_(self):
        self.run_test("def extend_(a):\n b=[1,2,3]\n b.extend(a)\n return b", [1.2], extend_=[[float]])

    def test_remove_(self):
        self.run_test("def remove_(a):\n b=[1,2,3]\n b.remove(a)\n return b", 2, remove_=[int])

    def test_index_(self):
        self.run_test("def index_(a):\n b=[1,2,3,8,7,4]\n return b.index(a)", 8, index_=[int])

    def test_pop_(self):
        self.run_test("def pop_(a):\n b=[1,3,4,5,6,7]\n return b.pop(a)", 2, pop_=[int])

    def test_popnegatif_(self):
        self.run_test("def popnegatif_(a):\n b=[1,3,4,5,6,7]\n return b.pop(a)", -2, popnegatif_=[int])

    def test_popempty_(self):
        self.run_test("def popempty_():\n b=[1,3,4,5,6,7]\n return b.pop()", popempty_=[])

    def test_count_(self):
        self.run_test("def count_(a):\n b=[1,3,4,5,3,7]\n return b.count(a)",3, count_=[int])

    def test_reverse_(self):
        self.run_test("def reverse_():\n b=[1,2,3]\n b.reverse()\n return b", reverse_=[])

    def test_sort_(self):
        self.run_test("def sort_():\n b=[1,3,5,4,2]\n b.sort()\n return b", sort_=[])

    def test_insert_(self):
        self.run_test("def insert_(a,b):\n c=[1,3,5,4,2]\n c.insert(a,b)\n return c",2,5, insert_=[int,int])

    def test_insertneg_(self):
        self.run_test("def insertneg_(a,b):\n c=[1,3,5,4,2]\n c.insert(a,b)\n return c",-1,-2, insertneg_=[int,int])

    def test_subscripted_slice(self):
        self.run_test("def subscripted_slice(l): a=l[2:6:2] ; return a[1]", range(10), subscripted_slice=[[int]])

    def test_list_comparison(self):
        self.run_test("def list_comparison(l): return max(l)", [[1,2,3],[1,4,1],[1,4,8,9]], list_comparison=[[[int]]])

    def test_list_equal_comparison_true(self):
        self.run_test("def list_comparison_true(l1,l2):  return l1==l2",
                      [1,2,3],[1,4,1], list_comparison_true=[[int],[int]])

    def test_list_equal_comparison_false(self):
        self.run_test("def list_comparison_false(l1,l2): return l1==l2",
                      [1,4,1],[1,4,1], list_comparison_false=[[int],[int]])

    def test_list_equal_comparison_different_sizes(self):
        self.run_test("def list_comparison_different_sizes(l1,l2): return l1==l2",
                      [1,4,1],[1,4,1,5], list_comparison_different_sizes=[[int],[int]])

    def test_list_unequal_comparison_false(self):
        self.run_test("def list_comparison_unequal_false(l1,l2):  return l1!=l2",
                      [1,2,3],[1,4,1], list_comparison_unequal_false=[[int],[int]])

    def test_list_unequal_comparison_true(self):
        self.run_test("def list_comparison_unequal_true(l1,l2): return l1!=l2",
                      [1,4,1],[1,4,1], list_comparison_unequal_true=[[int],[int]])

    def test_list_unequal_comparison_different_sizes(self):
        self.run_test("def list_unequal_comparison_different_sizes(l1,l2): return l1!=l2",
                      [1,4,1],[1,4,1,5], list_unequal_comparison_different_sizes=[[int],[int]])

    def test_assigned_slice(self):
        self.run_test("def assigned_slice(l): l[0]=l[2][1:3] ; return l",
                      [[1,2,3],[1,4,1],[1,4,8,9]], assigned_slice=[[[int]]])


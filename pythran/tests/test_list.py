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

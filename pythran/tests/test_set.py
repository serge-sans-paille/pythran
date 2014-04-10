import unittest
from test_env import TestEnv

class TestSet(TestEnv):

    def test_cpy_constructor(self):
        code="""
def are_equal(s1):
    s2 = set(s1)
    return s2 == s1
"""
        self.run_test(code, {'jack', 'sjoerd'}, are_equal=[{str}])
    def test_in(self):
        self.run_test("def _in(a,b):\n return b in a", {'aze', 'qsd'},'qsd', _in=[{str},str])

    def test_empty_in(self):
        self.run_test("def empty_in(b):\n return b in set()",'qsd', empty_in=[str])

    def test_len(self):
        self.run_test("def _len(a):\n return len(a)", {'aze', 'qsd', 'azeqsd'}, _len=[{str}])

    def test_disjoint(self):
        self.run_test("def _isdisjoint(a,b):\n return a.isdisjoint(b)", {1,3,2}, {7,2,5}, _isdisjoint=[{int},{float}])

    def test_operator_le(self):
        self.run_test("def _le(a,b):\n return a <= b", {1.,5.}, {1,2,5}, _le=[{float},{int}])

    def test_issubset(self):
        self.run_test("def _issubset(a,b):\n return a.issubset(b)", {1.,5.}, {1,2,5}, _issubset=[{float},{int}])

    def test_operator_lt(self):
        self.run_test("def _lt(a,b):\n return a < b", {1.,5.}, {1,2,5}, _lt=[{float},{int}])

    def test_operator_ge(self):
        self.run_test("def _ge(a,b):\n return a >= b", {1.,5.}, {1,2,5}, _ge=[{float},{int}])

    def test_issuperset(self):
        self.run_test("def _issuperset(a,b):\n return a.issuperset(b)", {1.,5.}, {1,2,5}, _issuperset=[{float},{int}])

    def test_operator_gt(self):
        self.run_test("def _gt(a,b):\n return a > b", {1.,5.}, {1,2,5}, _gt=[{float},{int}])

    def test_clear(self):
        self.run_test("def _clear(a):\n a.clear()\n return a", {1.,5.}, _clear=[{float}])

    def test_pop(self):
        self.run_test("def _pop(a):\n a.pop()\n return a", {1.,5.}, _pop=[{float}])

    def test_remove(self):
        self.run_test("def _remove(a,b):\n a.remove(b)\n return a", {1,3}, 1., _remove=[{int}, float])

    def test_remove_strict(self):
        self.run_test("def _remove_strict(a,b):\n a.remove(b)\n return a <= {3} and a >= {3}", {1,3}, 1., _remove_strict=[{int}, float])

    def test_discard(self):
        self.run_test("def _discard(a ,b):\n a.discard(b)\n return a", {1,3}, 1., _discard=[{int},float])

    def test_copy(self):
        self.run_test("def _copy(a):\n b=a.copy()\n return a <= {3} and a >= {3} and not a is b", {1,3}, _copy=[{int}])

    def test_fct_union(self):
        self.run_test("def _fct_union(b, c):\n a={1.}\n return a.union(b, c)", {1,3}, {1.,3.,4.,5.,6.} , _fct_union=[{int},{float}])

    def test_fct_union_empty_set(self):
        self.run_test("def _fct_union_empty_set(b, c):\n a=set()\n return a.union(b, c)", {1,3}, {1.,3.,4.,5.,6.} , _fct_union_empty_set=[{int},{float}])

    def test_fct_union_empty_set_list(self):
        self.run_test("def _fct_union_empty_set_list(b, c):\n a=set()\n return a.union(b, c)", {1,3}, [1.,3.,4.,5.,6.] , _fct_union_empty_set_list=[{int},[float]])

    def test_fct_union_list(self):
        self.run_test("def _fct_union_list(b, c):\n a={1.}\n return a.union(b, c)", [1,3], {1.,3.,4.,5.,6.} , _fct_union_list=[[int],{float}])

    def test_fct_union_1arg(self):
        self.run_test("def _fct_union_1arg(b):\n a={1.}\n return a.union(b)", {1,3,4,5,6}, _fct_union_1arg=[{int}])

    def test_operator_union(self):
        self.run_test("def _operator_union(b, c):\n a={1.}\n return (a | b | c)", {1,3,4,5,6}, {1.,2.,4.}, _operator_union=[{int},{float}])

    def test_update(self):
        self.run_test("def _update(b, c):\n a={1.}\n a.update(b, c)\n return a", {1,3}, {1.,3.,4.,5.,6.} , _update=[{int},{float}])

    def test_update_list(self):
        self.run_test("def _update_list(b, c):\n a={1.}; a.update(b, c); return a", {1,3}, [1.,3.,4.,5.,6.] , _update_list=[{int},[float]])

    def test_update_empty_set_list(self):
        self.run_test("def _update_empty_set_list(b, c):\n a=set()\n a.update(b, c)\n return a", {1,3}, [1.,3.,4.,5.,6.] , _update_empty_set_list=[{int},[float]])

    def test_operator_update(self):
        self.run_test("def _operator_update(b, c):\n a={1.,10.}\n a |= b | c\n return a", {1,3,4,5,6}, {1.,2.,4.}, _operator_update=[{int},{float}])

    def test_fct_intersection(self):
        self.run_test("def _fct_intersection(b, c):\n a={1.}\n return a.intersection(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_intersection=[{int},{float}])

    def test_fct_intersection_empty_set(self):
        self.run_test("def _fct_intersection_empty_set(b, c):\n a=set()\n return a.intersection(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_intersection_empty_set=[{int},{float}])

    def test_fct_intersection_list(self):
        self.run_test("def _fct_intersection_list(b, c):\n a={1.}\n return a.intersection(b,c)", {1,3,4,5,6}, [1.,2.,4.], _fct_intersection_list=[{int},[float]])

    def test_operator_intersection(self):
        self.run_test("def _operator_intersection(b, c):\n a={1.}\n return (a & b & c)", {1,3,4,5,6}, {1.,2.,4.}, _operator_intersection=[{int},{float}])

    def test_fct_intersection_update(self):
        self.run_test("def _fct_intersection_update(b, c):\n a={1.,10.}\n return a.intersection_update(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_intersection_update=[{int},{float}])

    def test_fct_intersection_update_empty_set(self):
        self.run_test("def _fct_intersection_update_empty_set(b, c):\n a=set()\n return a.intersection_update(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_intersection_update_empty_set=[{int},{float}])

    def test_fct_intersection_empty_set_update(self):
        self.run_test("def _fct_intersection_empty_set_update(c):\n a={1}\n b=set()\n return a.intersection_update(b,c)", {1.,2.,4.}, _fct_intersection_empty_set_update=[{float}])

    def test_fct_intersection_update_list(self):
        self.run_test("def _fct_intersection_update_list(b, c):\n a={1.,10.}\n return a.intersection_update(b,c)", [1,3,4,5,6], {1.,2.,4.}, _fct_intersection_update_list=[[int],{float}])

    def test_operator_intersection_update(self):
        self.run_test("def _operator_intersection_update(b, c):\n a={1.}\n a &= b & c\n return a", {1,3,4,5,6}, {1.,2.,4.}, _operator_intersection_update=[{int},{float}])

    @unittest.skip("pythran -E + pythran success")
    def test_operator_intersection_update_empty_set(self):
        self.run_test("def _operator_intersection_update_empty_set(b, c):\n a=set()\n a &= b & c\n return a", {1,3,4,5,6}, {1.,2.,4.}, _operator_intersection_update_empty_set=[{int},{float}])

    def test_fct_difference(self):
        self.run_test("def _fct_difference(b, c):\n a={1.,5.,10.}\n return a.difference(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_difference=[{int},{float}])

    def test_fct_difference_empty_set(self):
        self.run_test("def _fct_difference_empty_set(b, c):\n a=set()\n return a.difference(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_difference_empty_set=[{int},{float}])

    def test_fct_difference_list(self):
        self.run_test("def _fct_difference_list(b, c):\n a={1.,5.,10.}\n return a.difference(b,c)", [1,3,4,5,6], {1.,2.,4.}, _fct_difference_list=[[int],{float}])

    def test_operator_difference(self):
        self.run_test("def _operator_difference(b, c):\n a={1.}\n return (a - b - c)", {1,3,4,5,6}, {1.,2.,4.}, _operator_difference=[{int},{float}])

    def test_operator_difference_1arg(self):
        self.run_test("def _operator_difference_1arg(b):\n a={1.,2.,5.}\n return (b - a)", {1,3,4,5,6}, _operator_difference_1arg=[{int}])

    def test_fct_difference_update(self):
        self.run_test("def _fct_difference_update(b, c):\n a={1.,5.,10.}\n return a.difference_update(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_difference_update=[{int},{float}])

    def test_fct_difference_update_empty_set(self):
        self.run_test("def _fct_difference_update_empty_set(b, c):\n a=set()\n return a.difference_update(b,c)", {1,3,4,5,6}, {1.,2.,4.}, _fct_difference_update_empty_set=[{int},{float}])

    def test_fct_difference_update_list(self):
        self.run_test("def _fct_difference_update_list(b, c):\n a={1.,5.,10.}\n return a.difference_update(b,c)", {1,3,4,5,6}, [1.,2.,4.], _fct_difference_update_list=[{int},[float]])

    def test_operator_difference_update(self):
        self.run_test("def _operator_difference_update(b, c):\n a={1.}\n a -= b - c\n return a", {1,3,4,5,6}, {1.,2.,4.}, _operator_difference_update=[{int},{float}])

    def test_fct_symmetric_difference(self):
        self.run_test("def _fct_symmetric_difference(b, c):\n return (b.symmetric_difference(c))", {1,3,6}, {1.,2.,5.}, _fct_symmetric_difference=[{int},{float}])

    def test_fct_symmetric_difference_empty_set(self):
        self.run_test("def _fct_symmetric_difference_empty_set(c):\n b=set()\n return (b.symmetric_difference(c))", {1.,2.,5.}, _fct_symmetric_difference_empty_set=[{float}])

    def test_fct_symmetric_difference_list(self):
        self.run_test("def _fct_symmetric_difference_list(b, c):\n return (b.symmetric_difference(c))", {1,3,6}, [1.,2.,5.], _fct_symmetric_difference_list=[{int},[float]])

    def test_operator_symmetric_difference(self):
        self.run_test("def _operator_symmetric_difference(b, c):\n return (b ^ c)", {1,3,6}, {1.,2.,5.}, _operator_symmetric_difference=[{int},{float}])

    def test_fct_symmetric_difference_update(self):
        self.run_test("def _fct_symmetric_difference_update(b, c):\n return (c.symmetric_difference_update(b))", {1,3,6}, {1.,2.,5.}, _fct_symmetric_difference_update=[{int},{float}])

    def test_fct_symmetric_difference_update_empty_set(self):
        self.run_test("def _fct_symmetric_difference_update_empty_set(b):\n c=set()\n return (c.symmetric_difference_update(b))", {1.,2.,5.}, _fct_symmetric_difference_update_empty_set=[{float}])

    def test_fct_symmetric_difference_update2(self):
        self.run_test("def _fct_symmetric_difference_update2(b, c):\n return (b.symmetric_difference_update(c))", {1,3,6}, {1.,2.,5.}, _fct_symmetric_difference_update2=[{int},{float}])

    def test_fct_symmetric_difference_update_list(self):
        self.run_test("def _fct_symmetric_difference_update_list(b, c):\n return (b.symmetric_difference_update(c))", {1,3,6}, [1.,2.,5.], _fct_symmetric_difference_update_list=[{int},[float]])

    def test_operator_symmetric_difference_update(self):
        self.run_test("def _operator_symmetric_difference_update(b, c):\n b ^= c\n return b", {1,3,6}, {1.,2.,5.}, _operator_symmetric_difference_update=[{int},{float}])

    def test_operator_symmetric_difference_update2(self):
        self.run_test("def _operator_symmetric_difference_update2(b, c):\n c ^= b\n return c", {1,3,6}, {1.,2.,5.}, _operator_symmetric_difference_update2=[{int},{float}])

    # Check if conflict between set.pop() & list.pop()
    def test_conflict_pop(self):
        self.run_test("def _conflict_pop(a,b):\n a.pop()\n b.pop()\n return len(a)+len(b)", {1.,5.}, [1,2], _conflict_pop=[{float},[int]])

    def test_set_to_bool_conversion(self):
        self.run_test("def set_to_bool_conversion(s, t): return (1 if s else 0), (t if t else set())",
                      set(), {1, 2},set_to_bool_conversion=[{int}, {int}])

    def test_print_set(self):
        self.run_test("def print_set(s): return str(s)", {1, 2}, print_set=[{int}])

    def test_print_empty_set(self):
        self.run_test("def print_empty_set(s): return str(s)", set(), print_empty_set=[{int}])


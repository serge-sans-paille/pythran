from pythran.typing import List
from pythran.tests import TestFromDir, TestEnv
from pythran.config import cfg

import os
import numpy as np
import platform

try:
    import sortedcontainers

    class TestSortedContainersSortedList(TestEnv):

        def test_create_sortedlist_from_list(self):
            code = '''
            def sortedlist_from_list(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return list(sl)'''
            self.run_test(code, [3, 1, 2], sortedlist_from_list=[List[int]])

        def test_create_sortedlist_from_staticlist(self):
            code = '''
            def sortedlist_from_staticlist(e):
                from sortedcontainers import SortedList
                sl = SortedList([e, 5, 3])
                return list(sl)'''
            self.run_test(code, 8, sortedlist_from_staticlist=[int])

        def test_sortedlist_mul(self):
            code = '''
            def sortedlist_mul(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return list(sl * 3)'''
            self.run_test(code, [3, 1, 2], sortedlist_mul=[List[int]])

        def test_sortedlist_imul(self):
            code = '''
            def sortedlist_imul(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl *= 3
                return list(sl)'''
            self.run_test(code, [3, 1, 2], sortedlist_imul=[List[int]])

        def test_sortedlist_add(self):
            code = '''
            def sortedlist_add(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl.add(8)
                return list(sl)'''
            self.run_test(code, [3, 1, 2], sortedlist_add=[List[int]])

        def test_sortedlist_update(self):
            code = '''
            def sortedlist_update(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl.update([8, 1, 4])
                sl.update(SortedList([8, 1, 4]))
                return list(sl)'''
            self.run_test(code, [3, 1, 2], sortedlist_update=[List[int]])

        def test_sortedlist_add_op(self):
            code = '''
            def sortedlist_add_op(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return list(sl + [3])'''
            self.run_test(code, [3, 1, 2], sortedlist_add_op=[List[int]])

        def test_sortedlist_iadd(self):
            code = '''
            def sortedlist_iadd(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl += [3,4]
                return list(sl)'''
            self.run_test(code, [3, 1, 2], sortedlist_iadd=[List[int]])

        def test_sortedlist_clear(self):
            code = '''
            def sortedlist_clear(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl.clear()
                return list(sl)'''
            self.run_test(code, [3, 1, 2], sortedlist_clear=[List[int]])

        def test_sortedlist_discard(self):
            code = '''
            def sortedlist_discard(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl.discard(1)
                return list(sl)'''
            self.run_test(code, [3, 1, 2, 1], sortedlist_discard=[List[int]])

        def test_sortedlist_remove(self):
            code = '''
            def sortedlist_remove(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                sl.remove(1)
                sl.remove(1)
                try:
                    sl.remove(1)
                except ValueError:
                    pass
                return list(sl)'''
            self.run_test(code, [3, 1, 2, 1], sortedlist_remove=[List[int]])

        def test_sortedlist_pop(self):
            code = '''
            def sortedlist_pop(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                v1 = sl.pop(1)
                vl = sl.pop()
                vn = sl.pop(-2)
                try:
                    sl.pop(10)
                except IndexError:
                    pass
                return list(sl), v1, vl, vn'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0], sortedlist_pop=[List[int]])

        def test_sortedlist_bisect_left(self):
            code = '''
            def sortedlist_bisect_left(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return sl.bisect_left(1), sl.bisect_left(-4), sl.bisect_left(18), sl.bisect_left(9)'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0], sortedlist_bisect_left=[List[int]])

        def test_sortedlist_bisect_right(self):
            code = '''
            def sortedlist_bisect_right(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return sl.bisect_right(1), sl.bisect_right(-4), sl.bisect_right(18), sl.bisect_right(9)'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_bisect_right=[List[int]])

        def test_sortedlist_count(self):
            code = '''
            def sortedlist_count(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return sl.count(1), sl.count(-4), SortedList.count(sl, 18), sl.count(9)'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_count=[List[int]])

        def test_sortedlist_index(self):
            code = '''
            def sortedlist_index(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                s1 = sl.index(1)
                sn = sl.index(4, 3)
                sL = sl.index(4, 3, 12)
                try: so = sl.index(18)
                except ValueError: so = None
                return s1, sn, so, SortedList.index(sl, 9)'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_index=[List[int]])

        def test_sortedlist_contains(self):
            code = '''
            def sortedlist_contains(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return 1 in sl, 12 in sl'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_contains=[List[int]])

        def test_sortedlist_getitem(self):
            code = '''
            def sortedlist_getitem(l, i):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return sl[1], sl[-1], sl[1:3], sl[i]'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0], 4,
                          sortedlist_getitem=[List[int], int])

        def test_sortedlist_iter(self):
            code = '''
            def sortedlist_iter(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return [i**2 for i in sl]'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_iter=[List[int]])

        def test_sortedlist_reversed(self):
            code = '''
            def sortedlist_reversed(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return list(reversed(sl))'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_reversed=[List[int]])

        def test_sortedlist_len(self):
            code = '''
            def sortedlist_len(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                return len(sl)'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_len=[List[int]])

        def test_sortedlist_copy(self):
            code = '''
            def sortedlist_copy(l):
                from sortedcontainers import SortedList
                sl = SortedList(l)
                slc = sl.copy()
                sl.pop()
                slp = SortedList.copy(sl)
                return list(sl), list(slc), list(slp)'''
            self.run_test(code, [3, 1, 2, 1, 4, 5, 9, 0],
                          sortedlist_copy=[List[int]])

except ImportError:
    pass

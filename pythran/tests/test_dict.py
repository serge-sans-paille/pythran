from pythran.tests import TestEnv
from pythran.typing import Dict, List

class TestDict(TestEnv):

    def test_dict_(self):
        self.run_test("def dict_(): a=dict()", dict_=[])

    def test_assigned_dict(self):
        self.run_test("def assigned_dict(k):\n a=dict() ; a[k]=18", "yeah", assigned_dict=[str])

    def test_print_empty_dict(self):
        self.run_test("def print_empty_dict():\n print(dict())", print_empty_dict=[])

    def test_print_dict(self):
        self.run_test("def print_dict(k):\n a= dict() ; a[k]='youpi'\n print(a)", 5, print_dict=[int])

    def test_empty_dict(self):
        self.run_test("def empty_dict(): return {}", empty_dict=[])

    def test_initialized_dict(self):
        self.run_test("def initialized_dict(): return {1:'e', 5.2:'f'}", initialized_dict=[])

    def test_dict_contains(self):
        self.run_test("def dict_contains(v): return v in { 'a':1, 'e': 2 }", "e", dict_contains=[str])

    def test_emptydict_contains(self):
        self.run_test("def emptydict_contains(v): return v in dict()", "e", emptydict_contains=[str])

    def test_dict_get_item(self):
        self.run_test("def dict_get_item(a): return a['e']", {'e':1, 'f':2}, dict_get_item=[Dict[str, int]])

    def test_dict_get_missingitem(self):
        self.run_test("""
        def dict_get_missingitem(a):
            try:
                return a['g']
            except:
                return 12""",
                      {'e':1, 'f':2}, dict_get_missingitem=[Dict[str, int]])

    def test_dict_update_missingitem(self):
        self.run_test("""
        def dict_update_missingitem(a):
            try:
                a['g'] += 1
                return 1
            except KeyError:
                return 2""",
                     {'e':1, 'f':2}, dict_update_missingitem=[Dict[str, int]])

    def test_dict_len(self):
        self.run_test("def dict_len(d): return len(d)", {1:'e', 2:'f'}, dict_len=[Dict[int, str]])
    def test_dict_set_item(self):
        self.run_test("def dict_set_item():\n a= dict() ; a[1.5]='s'\n return a", dict_set_item=[])
    def test_dict_set_item_bis(self):
        self.run_test("def dict_set_item_bis():\n a= dict() ; a[1]='s'\n return a", dict_set_item_bis=[])
    def test_dict_clear(self):
        self.run_test("def dict_clear(a):\n a.clear()\n return a", {'e':'E' }, dict_clear=[Dict[str, str]])
    def test_dict_copy(self):
        code="""
def dict_copy(a):
    b = a.copy()
    c = a
    a.clear()
    return c,b"""
        self.run_test(code,  {1:2 }, dict_copy=[Dict[int, int]])

    def test_dict_from_keys(self):
        return self.run_test("def dict_from_keys(a): return dict.fromkeys(a), dict.fromkeys(a,1)", [1.5,2.5,3.5], dict_from_keys=[List[float]])

    def test_dict_get(self):
        return self.run_test("def dict_get(a): return a.get(1.5), a.get(2, 18) + 1", {1.5:2 }, dict_get=[Dict[float, int]])

    def test_dict_get_none(self):
        return self.run_test("def dict_get_none(a): return a.get(1)", {1.5:2 }, dict_get_none=[Dict[float, int]])

    def test_dict_items(self):
        return self.run_test("def dict_items(a): return sorted(a.items())", { 'a':1, 'e': 2 }, dict_items=[Dict[str, int]])

    def test_dict_for(self):
        return self.run_test("def dict_for(a): return sorted([x for x in a])", { 'a':1, 'e': 2 }, dict_for=[Dict[str, int]])

    def test_dict_keys(self):
        return self.run_test("def dict_keys(a): return sorted([ x*2 for x in a.keys()])", { 1:'a', 2:'b' }, dict_keys=[Dict[int, str]])

    def test_dict_values(self):
        return self.run_test("def dict_values(a): return sorted([ x*2 for x in a.values()])", { 1:'a', 2:'b' }, dict_values=[Dict[int, str]])

    def test_dict_pop(self):
        return self.run_test("def dict_pop(a): return a.pop(1), a.pop(3,'e'), a", { 1:'a', 2:'b' }, dict_pop=[Dict[int, str]])

    def test_dict_popitem0(self):
        return self.run_test(
            "def dict_popitem0(a): return a.popitem(), a",
            {1:'a' },
            dict_popitem0=[Dict[int, str]])

    def test_dict_popitem1(self):
        return self.run_test(
            "def dict_popitem1(a): return a.popitem(), a",
            { 1: 2 },
            dict_popitem1=[Dict[int, int]])

    def test_dict_setdefault(self):
        return self.run_test("def dict_setdefault():\n a={1.5:2 }\n return a.setdefault(1.5) + a.setdefault(2, 18)", dict_setdefault=[])

    def test_dict_update(self):
        return self.run_test("def dict_update(a):\n a.update([(1,'e')])\n a.update({2:'c'})\n return a", { 1:'a', 2:'b' }, dict_update=[Dict[int, str]])

    def test_dict_items_contains(self):
        return self.run_test("def dict_viewitems_contains(a):\n d=a.items()\n return (1,'a') in d, (2,'e') in d", { 1:'a', 2:'b' }, dict_viewitems_contains=[Dict[int, str]])

    def test_dict_keys_contains(self):
        return self.run_test("def dict_viewkeys_contains(a):\n d=a.keys()\n return 1 in d, 3 in d", { 1:'a', 2:'b' }, dict_viewkeys_contains=[Dict[int, str]])

    def test_dict_values_contains(self):
        return self.run_test("def dict_viewvalues_contains(a):\n d=a.values()\n return 'a' in d, 'e' in d", { 1:'a', 2:'b' }, dict_viewvalues_contains=[Dict[int, str]])

    def test_dict_update_combiner(self):
        return self.run_test("def dict_update_combiner():\n a=dict()\n a.update({1:'e'})\n return a", dict_update_combiner=[])

    def test_dict_setdefault_combiner(self):
        return self.run_test("def dict_setdefault_combiner():\n a=dict()\n a.setdefault(1,'e')\n return a", dict_setdefault_combiner=[])

    def test_dict_iterate_item(self):
        return self.run_test(
            """def dict_iterate_item(d):
                s = 0
                for kv in d.items():
                 for e in kv:
                  s += e
                return s""",
            {1:2,3:4},
            dict_iterate_item=[Dict[int, int]])

    def test_dict_return_complex_item(self):
        return self.run_test(
            """def dict_return_complex_item(d):
                for k, v in d.items():
                 return v""",
            {1:2j},
            dict_return_complex_item=[Dict[int, complex]])

    def test_dict_indexed_by_none(self):
        return self.run_test(
                """
                def dict_indexed_by_none(l):
                    x = {}
                    x[None] = l
                    y = x
                    x[None] += 1
                    equal = y == x
                    x.clear()
                    y.update({None: l + len(x)})
                    x.pop(None)
                    empty = bool(x)
                    y.setdefault(None, l + 2)
                    x[None] += 1
                    acc = 0
                    for j in x:
                        acc += bool(j) or 1
                    for j in x.items():
                        acc += j[1]
                    for j in x.keys():
                        acc += bool(j) or 1
                    for j in x.values():
                        acc += j

                    return x, y, equal, empty, acc""",
                1,
                dict_indexed_by_none=[int])


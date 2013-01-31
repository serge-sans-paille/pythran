from test_env import TestEnv

class TestTyping(TestEnv):

    def test_list_of_set(self):
        code = '''
def list_of_set():
    l=[set()]
    l[0].add("12")
    return l'''
        self.run_test(code, list_of_set=[])

    def test_dict_of_set(self):
        code = '''
def dict_of_set():
    l={0:set()}
    l[0].add("12")
    return l'''
        self.run_test(code, dict_of_set=[])

    def test_typing_aliasing_and_indices(self):
        self.run_test('def typing_aliasing_and_indices(): d={};e={}; f = e or d; f[1]="e"; return d,e,f', typing_aliasing_and_indices=[])

    def test_typing_aliasing_and_combiner(self):
        self.run_test('def typing_aliasing_and_combiner(): d=set();e=set(); f = e or d; f.add("e"); return d,e,f', typing_aliasing_and_combiner=[])

    def test_typing_aliasing_and_combiner_back(self):
        self.run_test('def typing_aliasing_and_combiner_back(): d=set();e=set(); f = e or d; e.add("e"); return d,e,f', typing_aliasing_and_combiner_back=[])

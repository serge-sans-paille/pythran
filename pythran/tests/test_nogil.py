from pythran.tests import TestEnv
from pythran.typing import List, Set, Dict, NDArray
import numpy as np

class TestNoGil(TestEnv):

    def test_list_param(self):
        code="""
        def list_param(l):
            return l, sum(i*j for i in l for j in l)
        """
        self.run_test(code, list(range(30)), list_param=[List[int]],
                      thread_count=4)

    def test_set_param(self):
        code="""
        def set_param(l):
            return {sum(l), sum(i*j for i in l for j in l)}, l
        """
        self.run_test(code, set(range(30)), set_param=[Set[int]],
                      thread_count=4)

    def test_dict_param(self):
        code="""
        def dict_param(l):
            return {sum(i-j for i in l.keys() for j in l.values()): l}, l
        """
        self.run_test(code, dict(zip(range(30), range(30))),
                      dict_param=[Dict[int, int]],
                      thread_count=4)

    def test_ndarray_param(self):
        code="""
        import numpy as np
        def ndarray_param(l):
            return np.array([i*j for i in l for j in l]), l
        """
        self.run_test(code, np.ones(100, dtype=int),
                      ndarray_param=[NDArray[int, :]],
                      thread_count=4)


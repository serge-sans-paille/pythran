import os
import unittest

class TestCython(unittest.TestCase):
    pass

def add_test(name, runner, target):
    setattr(TestCython, "test_" + name, lambda s: runner(s, target))

try:
    import Cython
    import glob
    import sys
    targets = glob.glob(os.path.join(os.path.dirname(__file__), "cython", "setup_*.py"))
    sys.path.append(os.path.join(os.path.dirname(__file__), "cython"))

    for target in targets:
        def runner(self, target):
            cwd = os.getcwd()
            try:
                os.chdir(os.path.dirname(target))
                exec(open(os.path.basename(target)).read())
            except:
                raise
            finally:
                os.chdir(cwd)
        name, _ = os.path.splitext(os.path.basename(target))
        add_test(name, runner, target)


except ImportError:
    pass


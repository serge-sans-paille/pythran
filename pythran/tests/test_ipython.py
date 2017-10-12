import subprocess
from unittest import TestCase

class TestIpythonMagic(TestCase):

    def test_loadext_and_run(self):
        subprocess.check_call(['ipython', 'ipython_script.ipy'])

    def test_loadext_and_run_timeit_twice(self):
        subprocess.check_call(['ipython', 'ipython_script_timeit.ipy'])

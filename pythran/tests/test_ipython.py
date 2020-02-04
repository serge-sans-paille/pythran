import os
import subprocess
from unittest import TestCase

class TestIpythonMagic(TestCase):

    def test_loadext_and_run(self):
        subprocess.check_call(['ipython',
                               os.path.join(os.path.dirname(__file__),
                                            'ipython_script.ipy')])

    def test_loadext_and_run_timeit_twice(self):
        subprocess.check_call(['ipython',
                               os.path.join(os.path.dirname(__file__),
                                            'ipython_script_timeit.ipy')])

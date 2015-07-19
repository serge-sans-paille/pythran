""" Tests for the time module. """

import pytest
import sys

from test_env import TestEnv


@TestEnv.module
class TestTime(TestEnv):

    """ Tests for the time module. """

    @pytest.mark.skipif(sys.platform == "win32",
                        reason="not supported by winpython for now")
    def test_time_and_sleep(self):
        """ Check time and sleep have the "same" behavior ~0.05 sec. """
        self.run_test("""
            def time_and_sleep():
                import time
                begin = time.time()
                time.sleep(2)
                end = time.time()
                return (end - begin) < 2.05 and (end - begin) > 1.95""",
                      time_and_sleep=[])

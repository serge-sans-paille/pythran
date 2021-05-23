import re

import pythran
from pythran.tests import TestEnv


class TestVersion(TestEnv):
    def test_version_check_cython(self):
        # Cython actually does this check (variable is named
        # `pythran_is_pre_0_9_6`). Make sure it doesn't break.
        v = pythran.__version__
        pre_096 = tuple(map(int, v.split('.')[0:3])) < (0, 9, 6)
        self.assertFalse(pre_096)

    def test_valid_version_string(self):
        # Verify that the pythran version is a valid one (note: excludes
        # .post suffix, and complies to PEP 440. Test taken from NumPy
        version_pattern = r"^[0-9]+\.[0-9]+\.[0-9]+(|a[0-9]|b[0-9]|rc[0-9])"
        dev_suffix = r"\.dev0\+[0-9]*\.g[0-9a-f]+"

        # For released versions:
        res1 = re.match(version_pattern, pythran.__version__)
        # For dev versions:
        res2 = re.match(version_pattern + dev_suffix, pythran.__version__)

        self.assertTrue(res1 is not None or res2 is not None,
                        pythran.__version__)


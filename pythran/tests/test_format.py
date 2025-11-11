"""Module to check coding style."""
import glob
import os
import subprocess
import unittest


class FormatTest(unittest.TestCase):
    excluded_files = ['pdqsort.hpp']
    clang_format = 'clang-format-20'

    def setUp(self):
        try:
            subprocess.check_call([FormatTest.clang_format, '--version'])
        except Exception:
            self.skipTest(FormatTest.clang_format + " not available")


    def test_clang_format(self):
        """Check coding style for cpp files."""
        pythran_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
        for root, _, _ in os.walk(os.path.join(pythran_dir, "pythonic")):
            for file_ in glob.glob(os.path.join(root, "*.hpp")):
                if os.path.basename(file_) in FormatTest.excluded_files:
                    continue
                cmd = "{cmd} {file} | diff -u {file} -".format(
                    cmd=FormatTest.clang_format,
                    file=os.path.join(root, file_))
                process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, universal_newlines=True)
                assert not process.wait(), process.stdout.read()

""" Module to check coding style. """
import glob
import os
import subprocess
import unittest


def test_clang_format():
    """ Check coding style for cpp files. """
    clang_format = 'clang-format-3.6'
    try:
        subprocess.check_call([clang_format, '--version'])
    except OSError:
        raise unittest.SkipTest(clang_format + " not available")

    pythran_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
    for root, _, _ in os.walk(os.path.join(pythran_dir, "pythonic")):
        for file_ in glob.glob(os.path.join(root, "*.hpp")):
            cmd = "{cmd} {file} | diff -u {file} -".format(
                cmd=clang_format,
                file=os.path.join(root, file_))
            process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            assert not process.wait(), process.stdout.read()

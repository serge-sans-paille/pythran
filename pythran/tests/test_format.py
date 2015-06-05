""" Module to check coding style. """
import glob
import os
import subprocess


def test_clang_format():
    """ Check coding style for cpp files. """
    pythran_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
    for root, _, _ in os.walk(os.path.join(pythran_dir, "pythonic")):
        for file_ in glob.glob(os.path.join(root, "*.hpp")):
            cmd = "clang-format-3.6 {file} | diff -u {file} -".format(
                file=os.path.join(root, file_))
            process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            assert not process.wait(), process.stdout.read()

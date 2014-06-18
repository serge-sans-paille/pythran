import unittest
import os.path
from subprocess import check_call
import shutil

cwd = os.path.dirname(__file__)

class TestDistutils(unittest.TestCase):

    def test_setup_build(self):
        check_call(['python', 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        check_call(['python', 'setup.py', 'install', '--prefix=demo_install'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        check_call(['python', '-c', 'import demo'],
                   cwd=os.path.join(cwd, 'test_distutils', 'demo_install',
                                    'lib', 'python2.7', 'site-packages'))
        check_call(['python', 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'demo_install'))


    def test_setup_sdist_install(self):
        check_call(['python', 'setup.py', 'sdist'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        check_call(['tar', 'xzf', 'demo-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils', 'dist'))
        check_call(['python', 'setup.py', 'install', '--prefix=demo_install'],
                   cwd=os.path.join(cwd, 'test_distutils', 'dist', 'demo-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'dist',
                                   'demo-1.0', 'demo_install'))

    def test_setup_bdist_install(self):
        check_call(['python', 'setup.py', 'bdist'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        check_call(['tar', 'xzf', 'demo-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils', 'dist'))
        check_call(['python', 'setup.py', 'install', '--prefix=demo_install'],
                   cwd=os.path.join(cwd, 'test_distutils', 'dist', 'demo-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'dist',
                                   'demo-1.0', 'demo_install'))


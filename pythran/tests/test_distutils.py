import unittest
import os
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
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'build'))


    def test_setup_sdist_install(self):
        check_call(['python', 'setup.py', 'sdist', "--dist-dir=sdist"],
                   cwd=os.path.join(cwd, 'test_distutils'))
        check_call(['tar', 'xzf', 'demo-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils', 'sdist'))
        check_call(['python', 'setup.py', 'install', '--prefix=demo_install'],
                   cwd=os.path.join(cwd, 'test_distutils', 'sdist', 'demo-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'sdist'))

    def test_setup_bdist_install(self):
        check_call(['python', 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils'))
        dist_path = os.path.join(cwd, 'test_distutils', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        check_call(['tar', 'xzf', tgz], cwd=dist_path)

        def find(name, path):
            for root, dirs, files in os.walk(path):
                if name in files:
                    return os.path.join(root, name)
        demo_so = find("demo.so", dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

    def test_setup_build2(self):
        check_call(['python', 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        check_call(['python', 'setup.py', 'install', '--prefix=demo_install2'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        check_call(['python', '-c', 'import demo2.a'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'demo_install2',
                                    'lib', 'python2.7', 'site-packages'))
        check_call(['python', 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'demo_install2'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'build'))


    def test_setup_sdist_install2(self):
        check_call(['python', 'setup.py', 'sdist', "--dist-dir=sdist2"],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        check_call(['tar', 'xzf', 'demo2-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'sdist2'))
        check_call(['python', 'setup.py', 'install', '--prefix=demo_install2'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'sdist2', 'demo2-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'sdist2'))

    def test_setup_bdist_install2(self):
        check_call(['python', 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        dist_path = os.path.join(cwd, 'test_distutils_packaged', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        check_call(['tar', 'xzf', tgz], cwd=dist_path)

        def find(name, path):
            for root, dirs, files in os.walk(path):
                if name in files:
                    return os.path.join(root, name)
        demo_so = find("a.so", dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

from subprocess import check_call
from distutils.sysconfig import get_python_lib
import os
import errno
import shutil
import sys
import sysconfig
import unittest

cwd = os.path.dirname(__file__)
python_version = "python{}.{}".format(sys.version_info.major,
                                      sys.version_info.minor)
if sys.version_info.major == 3:
    so_version = ".{}m-{}".format(sys.implementation.cache_tag,
                                  sysconfig.get_config_var('MULTIARCH'))
else:
    so_version = ""

def merge(x, y):
    z = x.copy()
    z.update(y)
    return z

def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise


def my_check_call(args, **kwargs):
    if 'prefix' in kwargs:
        prefix = kwargs['prefix']
        pythonpath = get_python_lib(prefix=prefix)
        del kwargs['prefix']
        args += ('--prefix=%s' % prefix, )
        env = kwargs.get('env', os.environ)
        env = merge(env, {'PYTHONPATH': pythonpath})
        lcwd = kwargs.get('cwd', cwd)
        mkdir_p(os.path.join(lcwd, pythonpath))
        kwargs['env'] = env
    check_call(args, **kwargs)

class TestDistutils(unittest.TestCase):

    def test_setup_build(self):
        my_check_call(['python', 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        my_check_call(['python', 'setup.py', 'install'],
                   prefix='demo_install',
                   cwd=os.path.join(cwd, 'test_distutils'))
        my_check_call(['python', '-c', 'import demo'],
                   cwd=os.path.join(cwd, 'test_distutils', 'demo_install',
                                    'lib', python_version, 'site-packages'))
        my_check_call(['python', 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'demo_install'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'build'))

    def test_setup_sdist_install(self):
        my_check_call(['python', 'setup.py', 'sdist', "--dist-dir=sdist"],
                   cwd=os.path.join(cwd, 'test_distutils'))
        my_check_call(['tar', 'xzf', 'demo-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils', 'sdist'))
        my_check_call(['python', 'setup.py', 'install'],
                   prefix='demo_install',
                   cwd=os.path.join(cwd, 'test_distutils', 'sdist', 'demo-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'sdist'))

    def test_setup_bdist_install(self):
        my_check_call(['python', 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils'))
        dist_path = os.path.join(cwd, 'test_distutils', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        my_check_call(['tar', 'xzf', tgz], cwd=dist_path)

        def find(name, path):
            for root, dirs, files in os.walk(path):
                if name in files:
                    return os.path.join(root, name)
        demo_so = find("demo{}.so".format(so_version), dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

    def test_setup_build2(self):
        my_check_call(['python', 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        my_check_call(['python', 'setup.py', 'install'],
                   prefix='demo_install2',
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        my_check_call(['python', '-c', 'import demo2.a'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'demo_install2',
                                    'lib', python_version, 'site-packages'))
        my_check_call(['python', 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'demo_install2'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'build'))


    def test_setup_sdist_install2(self):
        my_check_call(['python', 'setup.py', 'sdist', "--dist-dir=sdist2"],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        my_check_call(['tar', 'xzf', 'demo2-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'sdist2'))
        my_check_call(['python', 'setup.py', 'install'],
                   prefix='demo_install2',
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'sdist2', 'demo2-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'sdist2'))

    def test_setup_bdist_install2(self):
        my_check_call(['python', 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        dist_path = os.path.join(cwd, 'test_distutils_packaged', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        my_check_call(['tar', 'xzf', tgz], cwd=dist_path)

        def find(name, path):
            for root, dirs, files in os.walk(path):
                if name in files:
                    return os.path.join(root, name)
        demo_so = find("a{}.so".format(so_version), dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

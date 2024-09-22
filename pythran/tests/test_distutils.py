from subprocess import check_call
import os
import re
import shutil
import sys
import sysconfig
import unittest

cwd = os.path.dirname(__file__)

def _get_implementation():
    if sys.implementation.name == 'pypy':
        return 'pypy'
    return 'python'

python_version = "{}{}.{}".format(_get_implementation(), sys.version_info.major,
                                      sys.version_info.minor)

python = sys.executable

def find_so(name, path):
    for root, dirs, files in os.walk(path):
        for filename in files:
            if re.match(name, filename):
                return os.path.join(root, filename)

class TestDistutils(unittest.TestCase):

    def test_setup_build(self):
        check_call([python, 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils'))

        extra_args = ['--no-build-isolation',]
        check_call([python, '-m', 'pip', 'install', '.',
                    '--prefix=demo_install'] + extra_args,
                   cwd=os.path.join(cwd, 'test_distutils'))

        base = os.path.join(cwd, 'test_distutils', 'demo_install',)
        libdir = os.path.join(base, 'lib')
        if not os.path.isdir(libdir):
            libdir = os.path.join(base, 'lib64')

        local_env = os.environ.copy()
        local_env['PYTHONPATH'] = os.path.join(libdir, python_version, 'site-packages')
        check_call([python, '-c', 'import demo'], env=local_env)
        check_call([python, 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'demo_install'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'build'))

    def test_setup_sdist_install(self):
        check_call([python, 'setup.py', 'sdist', "--dist-dir=sdist"],
                   cwd=os.path.join(cwd, 'test_distutils'))
        check_call(['tar', 'xzf', 'demo-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils', 'sdist'))
        check_call([python, 'setup.py', 'install', '--prefix=demo_install'],
                   cwd=os.path.join(cwd, 'test_distutils', 'sdist', 'demo-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils', 'sdist'))

    def test_setup_bdist_install(self):
        check_call([python, 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils'))
        dist_path = os.path.join(cwd, 'test_distutils', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        check_call(['tar', 'xzf', tgz], cwd=dist_path)

        demo_so = find_so(r"demo.*\.so", dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

    def test_setup_wheel_install(self):
        check_call([python, 'setup.py', 'bdist_wheel', "--dist-dir=bdist_wheel"],
                   cwd=os.path.join(cwd, 'test_distutils_setuptools'))
        dist_path = os.path.join(cwd, 'test_distutils_setuptools', 'bdist_wheel')
        wheel_dir = 'wheeeeeeel'
        whl = [f for f in os.listdir(dist_path) if f.endswith(".whl")][0]
        check_call(['unzip', whl, '-d', wheel_dir], cwd=dist_path)

        demo_so = find_so(r"demo.*\.so", os.path.join(dist_path, wheel_dir))
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)


    def test_setup_build2(self):
        check_call([python, 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))

        extra_args = ['--no-build-isolation',]
        check_call([python, '-m', 'pip', 'install', '.',
                    '--prefix=demo_install2'] + extra_args,
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))

        base = os.path.join(cwd, 'test_distutils_packaged', 'demo_install2',)
        libdir = os.path.join(base, 'lib')
        if not os.path.isdir(libdir):
            libdir = os.path.join(base, 'lib64')
        local_env = os.environ.copy()
        local_env['PYTHONPATH'] = os.path.join(libdir, python_version, 'site-packages')
        check_call([python, '-c', 'import demo2.a'], env=local_env)
        check_call([python, 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'demo_install2'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'build'))

    def test_setup_sdist_install2(self):
        check_call([python, 'setup.py', 'sdist', "--dist-dir=sdist2"],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        check_call(['tar', 'xzf', 'demo2-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'sdist2'))
        check_call([python, 'setup.py', 'install', '--prefix=demo_install2'],
                   cwd=os.path.join(cwd, 'test_distutils_packaged', 'sdist2', 'demo2-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_packaged', 'sdist2'))

    def test_setup_bdist_install2(self):
        check_call([python, 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils_packaged'))
        dist_path = os.path.join(cwd, 'test_distutils_packaged', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        check_call(['tar', 'xzf', tgz], cwd=dist_path)

        demo_so = find_so(r"a.*\.so", dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

    @unittest.skipIf(sys.version_info >= (3, 12), "setup install is deprecated")
    def test_setup_build3(self):
        check_call([python, 'setup.py', 'build'],
                   cwd=os.path.join(cwd, 'test_distutils_numpy'))

        base = os.path.join(cwd, 'test_distutils_numpy', 'demo_install3',)
        libdir = os.path.join(base, 'lib')
        lib64dir = os.path.join(base, 'lib64')

        local_env = os.environ.copy()
        local_env['PYTHONPATH'] = os.pathsep.join((
            os.path.join(lib64dir, python_version,
                         'site-packages'),
            os.path.join(libdir, python_version,
                         'site-packages'),
            local_env.get('PYTHONPATH', ''),
            ))

        check_call([python, 'setup.py', 'install', '--prefix=demo_install3'],
                   cwd=os.path.join(cwd, 'test_distutils_numpy'),
                   env=local_env)

        check_call([python, '-c', 'import demo3.a'],
                   cwd=cwd, env=local_env)
        check_call([python, 'setup.py', 'clean'],
                   cwd=os.path.join(cwd, 'test_distutils_numpy'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_numpy', 'demo_install3'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_numpy', 'build'))

    def test_setup_sdist_install3(self):
        check_call([python, 'setup.py', 'sdist', "--dist-dir=sdist3"],
                   cwd=os.path.join(cwd, 'test_distutils_numpy'))
        check_call(['tar', 'xzf', 'demo3-1.0.tar.gz'],
                   cwd=os.path.join(cwd, 'test_distutils_numpy', 'sdist3'))
        check_call([python, 'setup.py', 'install', '--prefix=demo_install3'],
                   cwd=os.path.join(cwd, 'test_distutils_numpy', 'sdist3', 'demo3-1.0'))
        shutil.rmtree(os.path.join(cwd, 'test_distutils_numpy', 'sdist3'))

    def test_setup_bdist_install3(self):
        check_call([python, 'setup.py', 'bdist', "--dist-dir=bdist"],
                   cwd=os.path.join(cwd, 'test_distutils_numpy'))
        dist_path = os.path.join(cwd, 'test_distutils_numpy', 'bdist')
        tgz = [f for f in os.listdir(dist_path) if f.endswith(".tar.gz")][0]
        check_call(['tar', 'xzf', tgz], cwd=dist_path)

        demo_so = find_so(r"a.*\.so", dist_path)
        self.assertIsNotNone(demo_so)
        shutil.rmtree(dist_path)

try:
    check_call(['ninja', '--version'])
    has_ninja = True
except:
    has_ninja = False

try:
    check_call(['meson', '--version'])
    has_meson = True
except:
    has_meson = False

class TestMeson(unittest.TestCase):

    @unittest.skipIf(not has_meson, "meson not found")
    @unittest.skipIf(not has_ninja, "ninja not found")
    def test_meson_build(self):
        srcdir = os.path.join(cwd, 'test_distutils')
        builddir = os.path.join(srcdir, '_meson_build')
        shutil.rmtree(builddir, ignore_errors=True)
        check_call(['meson', 'setup', builddir, '.'],
                   cwd=srcdir)
        check_call(['ninja', '-v'],
                   cwd=builddir)
        check_call([python, '-c', 'import b'],
                   cwd=builddir)


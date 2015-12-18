from __future__ import print_function

# Preliminary checks that cannot be done by setuptools
# like... the setuptools dependency itself!
try:
    import setuptools
except ImportError:
    print()
    print("*****************************************************")
    print("* Setuptools must be installed before running setup *")
    print("*****************************************************")
    print()
    raise

# See https://gist.github.com/kejbaly2/71517b08536776399198
# Turns out installing numpy as a dep with setuptools is tricky
try:
    import numpy
except ImportError:
    print()
    print("******************************************************************")
    print("* Numpy must be installed before running setup, sorry about this *")
    print("******************************************************************")
    print()
    raise

from setuptools.command.build_py import build_py
from setuptools import setup
from distutils import ccompiler
from setuptools.command.test import test as TestCommand
from subprocess import check_call

import logging
import glob
import os
import re
import shutil
from tempfile import NamedTemporaryFile
import sys

# It appears old versions of setuptools are not supported, see
#   https://github.com/serge-sans-paille/pythran/issues/489

from distutils.version import LooseVersion
MinimalSetuptoolsVersion = LooseVersion("12.0.5")
if LooseVersion(setuptools.__version__) < MinimalSetuptoolsVersion:
    msg = "Setuptools version is {}, but must be at least {}".format(
        setuptools.__version__,
        MinimalSetuptoolsVersion)
    print()
    print("*" * (len(msg) + 4))
    print("*", msg, "*")
    print("*" * (len(msg) + 4))
    print()
    raise ImportError("setuptools")


logger = logging.getLogger("pythran")
logger.addHandler(logging.StreamHandler())

versionfile = os.path.join('pythran', 'version.py')
exec(open(versionfile).read())


class PyTest(TestCommand):
    user_options = [('pytest-args=', 'a', "Arguments to pass to py.test")]

    def initialize_options(self):
        TestCommand.initialize_options(self)
        self.pytest_args = []

    def finalize_options(self):
        TestCommand.finalize_options(self)
        self.test_args = ['--pep8']
        self.test_suite = True

    def run_tests(self):
        # import here, cause outside the eggs aren't loaded
        import pytest
        sys.path.append(os.getcwd())
        errno = pytest.main(self.pytest_args)
        sys.exit(errno)


class BuildWithThirdParty(build_py):

    """
    Set up Pythran dependencies.

    * install nt2
    * install boost.simd
    * install boost dependencies
    """

    def copy_nt2(self):
        """ Install NT2 and boost deps from the third_party directory """

        print('Copying nt2 and its dependencies')
        for d in ('nt2', 'boost'):
            src = os.path.join('third_party', d)

            # copy to the build tree
            target = os.path.join(self.build_lib, 'pythran', d)
            shutil.rmtree(target, True)
            shutil.copytree(src, target)

            # copy them to the source tree too, needed for sdist
            target = os.path.join('pythran', d)
            shutil.rmtree(target, True)
            shutil.copytree(src, target)

    def detect_gmp(self):
        # It's far from perfect, but we try to compile a code that uses
        # Python long. If it fails, _whatever the reason_ we just disable gmp
        print('Trying to compile GMP dependencies.')

        cc = ccompiler.new_compiler(verbose=False)
        trash = list()
        # try to compile a code that requires gmp support
        with NamedTemporaryFile(suffix='.cpp', delete=False) as temp:
            temp.write('''
                #include <gmpxx.h>
                int main() {
                    mpz_class a(1);
                    return a == 0;
                };
            '''.encode('ascii'))
            srcs = [temp.name]
            trash.append(temp.name)
        exe = "a.out"
        try:
            objs = cc.compile(srcs)
            map(trash.append, objs)
            cc.link(ccompiler.CCompiler.EXECUTABLE,
                    objs, exe,
                    libraries=['gmp', 'gmpxx'])
            trash.append(exe)
        except Exception:
            # failure: remove the gmp dependency
            print('Failed to compile GMP source, disabling long support.')
            for pythrandir in (os.path.join(self.build_lib, "pythran"),
                               os.path.join(os.path.dirname(__file__),
                                            "pythran")):
                for cfg in glob.glob(os.path.join(pythrandir,
                                                  "pythran-*.cfg")):
                    with open(cfg, "r+") as cfg:
                        content = cfg.read()
                        content = content.replace('USE_GMP', '')
                        content = content.replace('gmp gmpxx', '')
                        cfg.seek(0)
                        cfg.write(content)
        map(os.remove, trash)

    def run(self, *args, **kwargs):
        # regular build done by parent class
        build_py.run(self, *args, **kwargs)
        if not self.dry_run:  # compatibility with the parent options
            self.detect_gmp()
            self.copy_nt2()


# Cannot use glob here, as the files may not be generated yet
nt2_headers = (['nt2/' + '*/' * i + '*.hpp' for i in range(1, 20)] +
               ['boost/' + '*/' * i + '*.hpp' for i in range(1, 20)])
pythonic_headers = ['*/' * i + '*.hpp' for i in range(9)] + ['patch/*']

# rename pythran into pythran3 for python3 version
if sys.version_info[0] == 3:
    pythran_cmd = 'pythran3'
else:
    pythran_cmd = 'pythran'

setup(name='pythran',
      version=__version__,
      description=__descr__,
      author='Serge Guelton',
      author_email='serge.guelton@telecom-bretagne.eu',
      url=__url__,
      packages=['pythran', 'pythran.analyses', 'pythran.transformations',
                'pythran.optimizations', 'omp', 'pythran/pythonic',
                'pythran.types'],
      package_data={'pythran': ['pythran*.cfg'] + nt2_headers,
                    'pythran/pythonic': pythonic_headers},
      classifiers=[
          'Development Status :: 4 - Beta',
          'Environment :: Console',
          'Intended Audience :: Developers',
          'License :: OSI Approved :: BSD License',
          'Natural Language :: English',
          'Operating System :: POSIX :: Linux',
          'Programming Language :: Python :: 2.7',
          'Programming Language :: Python :: 3',
          'Programming Language :: Python :: Implementation :: CPython',
          'Programming Language :: C++',
          'Topic :: Software Development :: Code Generators'
      ],
      license="BSD 3-Clause",
      install_requires=[
          'ply>=3.4',
          'networkx>=1.5',
          'colorlog',
          'decorator',
      ],
      entry_points={'console_scripts': ['pythran = pythran.run:run',
                                        'pythran-config = pythran.config:run'],
                    },
      tests_require=['pytest', 'pytest-pep8'],
      test_suite="pythran/test",
      cmdclass={'build_py': BuildWithThirdParty, 'test': PyTest})

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
from distutils.errors import CompileError, LinkError
from setuptools.command.test import test as TestCommand

import logging
import glob
import os
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

        cc = ccompiler.new_compiler("posix", verbose=False)
        # try to compile a code that requires gmp support
        with NamedTemporaryFile(suffix='.c', delete=False) as temp:
            temp.write('''
                #include <stdio.h>
                #include <gmp.h>

                int main(void) {
                 mpz_t x,y,result;

                 mpz_init_set_str(x, "7612058254738945", 10);
                 mpz_init_set_str(y, "9263591128439081", 10);
                 mpz_init(result);

                 mpz_mul(result, x, y);
                 gmp_printf("%Zd * %Zd = %Zd", x, y, result);

                 /* free used memory */
                 mpz_clear(x);
                 mpz_clear(y);
                 mpz_clear(result);

                 return 0;
                }
            '''.encode('ascii'))
            srcs = [temp.name]
        exe = "a.out"
        objs = []  # Make sure this variable exist in case of fail.
        try:
            objs = cc.compile(srcs)
            cc.link(ccompiler.CCompiler.EXECUTABLE,
                    objs, exe,
                    libraries=['gmp'])
        except (LinkError, CompileError):
            # failure: remove the gmp dependency
            print('Failed to compile GMP source, disabling long support.')
            for cfg in glob.glob(os.path.join(self.build_lib, "pythran",
                                              "pythran-*.cfg")):
                with open(cfg, "r+") as cfg:
                    content = cfg.read()
                    content = content.replace('USE_GMP', '')
                    content = content.replace('gmp gmpxx', '')
                    cfg.seek(0)
                    cfg.write(content)
                    cfg.truncate(len(content))
        finally:
            tmp_files = objs + srcs + [exe]
            for filename in tmp_files:
                # file may not exist as it may raise before its creation.
                if os.path.exists(filename):
                    os.remove(filename)

    def run(self, *args, **kwargs):
        # regular build done by parent class
        build_py.run(self, *args, **kwargs)
        if not self.dry_run:  # compatibility with the parent options
            self.copy_nt2()
            self.detect_gmp()


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
      install_requires=open('requirements.txt').read().splitlines(),
      entry_points={'console_scripts': ['pythran = pythran.run:run',
                                        'pythran-config = pythran.config:run'],
                    },
      tests_require=['pytest', 'pytest-pep8'],
      test_suite="pythran/test",
      cmdclass={'build_py': BuildWithThirdParty, 'test': PyTest})

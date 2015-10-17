from __future__ import print_function
from setuptools.command.build_py import build_py
from setuptools import setup
from setuptools.command.test import test as TestCommand
from subprocess import check_call, check_output
from urllib2 import urlopen
from zipfile import ZipFile
from StringIO import StringIO

import logging
import os
import re
import shutil
import sys

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

logger = logging.getLogger("pythran")
logger.addHandler(logging.StreamHandler())

execfile(os.path.join('pythran', 'version.py'))


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


class BuildWithPly(build_py):

    """
    Set up Pythran dependencies.

    * install nt2
    * install boost.simd
    """

    def patch_nt2(self, nt2_path, version):
        """
        NT2 version gets override by pythran's git version if any
        So force it here...
        """
        cmakelists = os.path.join(nt2_path, 'CMakeLists.txt')
        with open(cmakelists, 'r') as cm:
            print("patching nt2 version in" + cmakelists)
            data = cm.read()
            data = re.sub(r'(nt2_parse_version\()',
                          r'set(NT2_VERSION_STRING "{}")\n\1'.format(version),
                          data)
        with open(cmakelists, 'w') as cm:
            cm.write(data)

        with open(os.path.join(nt2_path, 'tagname'), 'w') as tn:
            tn.write(version)

    def build_nt2(self):
        """ Install NT2 from the github-generated archive. """
        nt2_dir = 'nt2'
        nt2_version = '1.2.3-pythran'  # fake!
        cwd = os.getcwd()
        build_temp = os.path.join(os.path.dirname(__file__), "build")
        nt2_src_dir = os.path.join(cwd, build_temp, nt2_dir + '_src')
        if not os.path.isdir(nt2_src_dir):
            print('nt2 archive needed, downloading it')
            url = 'https://github.com/pbrunet/nt2/archive/gemv_release.zip'
            location = urlopen(url)
            http_code_prefix = location.getcode() / 100
            assert http_code_prefix not in [4, 5], "Failed to download nt2."
            zipfile = ZipFile(StringIO(location.read()))
            zipfile.extractall(build_temp)
            extracted = os.path.dirname(zipfile.namelist()[0])
            shutil.move(os.path.join(build_temp, extracted), nt2_src_dir)
            self.patch_nt2(nt2_src_dir, nt2_version)
            assert os.path.isdir(nt2_src_dir), "download & unzip ok"

        nt2_build_dir = os.path.join(build_temp, nt2_dir)
        if not os.path.isdir(nt2_build_dir):
            os.makedirs(nt2_build_dir)

        if not os.path.exists(os.path.join(nt2_build_dir, 'modules')):
            print('nt2 not configured, configuring it')
            # remove any remaining artifacts
            shutil.rmtree(nt2_build_dir, True)
            os.makedirs(nt2_build_dir)

            os.chdir(nt2_build_dir)
            build_cmd = ['cmake',
                         nt2_src_dir,
                         '-DNT2_VERSION_STRING={}'.format(nt2_version),
                         '-DCMAKE_INSTALL_PREFIX=.']
            try:
                check_call(build_cmd)
            except Exception:
                print("configure failed upon: " + " " .join(build_cmd))
                raise
            os.chdir(cwd)

        print('Compile and install nt2')
        check_output(['cmake', '--build', nt2_build_dir,
                      '--target', 'install'])
        for d in ('nt2', 'boost'):
            src = os.path.join(nt2_build_dir, 'include', d)

            # copy to the build tree
            target = os.path.join(self.build_lib, 'pythran', d)
            shutil.rmtree(target, True)
            shutil.copytree(src, target)

            # copy them to the source tree too, needed for sdist
            target = os.path.join('pythran', d)
            shutil.rmtree(target, True)
            shutil.copytree(src, target)

    def run(self, *args, **kwargs):
        # regular build done by parent class
        build_py.run(self, *args, **kwargs)
        if not self.dry_run:  # compatibility with the parent options
            self.build_nt2()


# Cannot use glob here, as the files may not be generated yet
nt2_headers = (['nt2/' + '*/' * i + '*.hpp' for i in range(1, 20)] +
               ['boost/' + '*/' * i + '*.hpp' for i in range(1, 20)])
pythonic_headers = ['*/' * i + '*.hpp' for i in range(9)] + ['patch/*']

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
      cmdclass={'build_py': BuildWithPly, 'test': PyTest})

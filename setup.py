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

from setuptools.command.build_py import build_py
from setuptools.command.develop import develop

from setuptools import setup

import logging
import os
import shutil
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

if sys.version_info.major < 3:
    print()
    print("****************************************************")
    print("*        Python 2 has reached end-of-support       *")
    print("****************************************************")
    print("*                                                  *")
    print("* Last Pythran version supporting Python2 is 0.9.5 *")
    print("*                                                  *")
    print("****************************************************")
    print()


logger = logging.getLogger("pythran")
logger.addHandler(logging.StreamHandler())

versionfile = os.path.join('pythran', 'version.py')
exec(open(versionfile).read())


class BuildWithThirdParty(build_py):

    """
    Set up Pythran dependencies.

    * install boost dependencies
    * install xsimd dependencies
    """

    third_parties = 'boost', 'xsimd'

    user_options = build_py.user_options + [
        ('no-{}'.format(pkg), None, 'Do not distribute {} headers'.format(pkg))
        for pkg in third_parties
    ]

    def initialize_options(self):
        build_py.initialize_options(self)
        for pkg in BuildWithThirdParty.third_parties:
            setattr(self, 'no_' + pkg, None)

    def copy_pkg(self, pkg, src_only=False):
        "Install boost deps from the third_party directory"

        if getattr(self, 'no_' + pkg) is None:
            print('Copying', pkg, 'dependencies')
            to_copy = pkg,
        else:
            return

        src = os.path.join('third_party', *to_copy)

        # copy to the build tree
        if not src_only:
            target = os.path.join(self.build_lib, 'pythran', *to_copy)
            shutil.rmtree(target, True)
            shutil.copytree(src, target)

        # copy them to the source tree too, needed for sdist
        target = os.path.join('pythran', *to_copy)
        shutil.rmtree(target, True)
        shutil.copytree(src, target)

    def run(self, *args, **kwargs):
        # regular build done by parent class
        build_py.run(self, *args, **kwargs)
        if not self.dry_run:  # compatibility with the parent options
            for pkg in BuildWithThirdParty.third_parties:
                self.copy_pkg(pkg)


class DevelopWithThirdParty(develop, BuildWithThirdParty):

    def initialize_options(self):
        develop.initialize_options(self)
        BuildWithThirdParty.initialize_options(self)

    def run(self, *args, **kwargs):
        if not self.dry_run:  # compatibility with the parent options
            for pkg in BuildWithThirdParty.third_parties:
                self.copy_pkg(pkg, src_only=True)
        develop.run(self, *args, **kwargs)


# Cannot use glob here, as the files may not be generated yet
boost_headers = ['boost/' + '*/' * i + '*.hpp' for i in range(1, 20)]
xsimd_headers = ['xsimd/' + '*/' * i + '*.hpp' for i in range(1, 20)]
pythonic_headers = ['*/' * i + '*.hpp' for i in range(9)] + ['patch/*']


# read longdescr from README
def longdescr(readme_path):
    with open(readme_path) as readme:
        lines = list(readme)
        start_index = lines.index('What is it?\n')
        stop_index = lines.index('Installation\n')
        long_description = "".join(lines[start_index + 2: stop_index])
        return long_description


setup(name='pythran',
      version=__version__,
      description=__descr__,
      long_description=longdescr("README.rst"),
      author='Serge Guelton',
      author_email='serge.guelton@telecom-bretagne.eu',
      url=__url__,
      packages=['pythran', 'pythran.analyses', 'pythran.transformations',
                'pythran.optimizations', 'omp', 'pythran/pythonic',
                'pythran.types'],
      package_data={'pythran': (['pythran*.cfg']
                                + boost_headers
                                + xsimd_headers),
                    'pythran/pythonic': pythonic_headers},
      classifiers=[
          'Development Status :: 4 - Beta',
          'Environment :: Console',
          'Intended Audience :: Developers',
          'License :: OSI Approved :: BSD License',
          'Natural Language :: English',
          'Operating System :: POSIX :: Linux',
          'Operating System :: MacOS',
          'Programming Language :: Python :: 2.7',
          'Programming Language :: Python :: 3',
          'Programming Language :: Python :: Implementation :: CPython',
          'Programming Language :: C++',
          'Topic :: Software Development :: Compilers',
          'Topic :: Software Development :: Code Generators'
      ],
      license="BSD 3-Clause",
      install_requires=open('requirements.txt').read().splitlines(),
      entry_points={'console_scripts':
                    ['pythran = pythran.run:run',
                     'pythran-config = pythran.config:run']},
      extras_require={
          'doc': open('docs/requirements.txt').read().splitlines(),
      },
      test_suite="pythran.tests.test_cases",
      cmdclass={'build_py': BuildWithThirdParty,
                'develop': DevelopWithThirdParty})

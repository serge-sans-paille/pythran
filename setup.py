from __future__ import print_function
from distutils.command.build import build
from distutils.core import setup, Command
from subprocess import check_call, check_output
import logging
import numpy
import os
import shutil
import sys
import time

logger = logging.getLogger("pythran")
logger.addHandler(logging.StreamHandler())

from pythran import __version__


def _exclude_current_dir_from_import():
    """ Prevents Python loading from current directory, so that
    `import pythran` lookup the PYTHONPATH.

    Returns current_dir

    """
    current_dir = os.path.dirname(os.path.abspath(__file__))
    sys.path = filter(lambda p: p != current_dir, sys.path)
    return current_dir


class BuildWithPly(build):
    '''Use ply to generate parsetab before building module.'''

    def build_ply(self):
        from pythran.spec import SpecParser
        SpecParser()  # this forces the generation of the parsetab file
        self.mkpath(os.path.join(self.build_lib, 'pythran'))
        for p in ('parsetab.py',):
            target = os.path.join(self.build_lib, 'pythran', p)
            if os.path.exists(p):
                os.rename(p, target)
            assert os.path.exists(target)

    def build_nt2(self):
        nt2_dir = 'nt2'
        if not os.path.isdir(nt2_dir):
            print('nt2 git repository not setup, cloning it')
            cmd = 'git clone https://github.com/MetaScale/nt2.git -b release'
            check_call(cmd.split())
        else:
            cmd = 'git fetch && git checkout origin/release'
            check_call(cmd, shell=True, cwd=nt2_dir)
            print('nt2 git repository updated')

        nt2_build_dir = os.path.join(self.build_temp, nt2_dir)
        if not os.path.isdir(nt2_build_dir):
            os.makedirs(nt2_build_dir)

        if not os.path.exists(os.path.join(nt2_build_dir, 'Makefile')):
            print('nt2 not already configured, configuring it')

            cwd = os.getcwd()
            abs_nt2_dir = os.path.join(cwd, nt2_dir)
            os.chdir(nt2_build_dir)
            build_cmd = ['cmake',
                         abs_nt2_dir,
                         '-DCMAKE_INSTALL_PREFIX=.',
                         '-DNT2_FIND_REPOSITORIES='
                         'git://github.com/MetaScale/nt2-modules.git']
            check_call(build_cmd)
            os.chdir(cwd)

        print('Compile and install nt2')
        check_output(['make', '-C', nt2_build_dir, 'install', '-j'])
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
        if not self.dry_run:  # compatibility with the parent options
            self.build_ply()
            self.build_nt2()
        # regular build done by parent class
        build.run(self, *args, **kwargs)


class TestCommand(Command):

    """Scan the test directory for any tests, and run them."""

    description = 'run the test suite for the package'
    user_options = [('failfast', None, 'Stop upon first fail'),
                    ('cov', None, 'Perform coverage analysis'),
                    ('num-threads=', None,
                     'Number of threads to execute tests')]

    def initialize_options(self):
        """ Initialize default value to command line arguments. """
        self.failfast = False
        self.cov = False
        import multiprocessing
        self.num_threads = multiprocessing.cpu_count()

    def finalize_options(self):
        """ Check arguments validity. """
        assert self.num_threads > 0, "Not enough threads for tests."

    def run(self):
        """
        Run tests using the PYTHONPATH path to load pythran.

        It also check third party library installation before running tests.
        """
        # Do not include current directory, validate using installed pythran
        current_dir = _exclude_current_dir_from_import()
        where = os.path.join(current_dir, 'pythran')

        from pythran import test_compile
        test_compile()

        import pytest
        args = [where, '--pep8']

        # try a parallel run
        try:
            import xdist
            args = ["-n", str(self.num_threads)] + args
        except ImportError:
            print('W: Skipping parallel run, pytest_xdist not found')

        if self.failfast:
            args.insert(0, '-x')

        if self.cov:
            try:
                # Avoid loading unused module
                __import__('imp').find_module('pytest_cov')
                args = ["--cov-report", "html",
                        "--cov-report", "annotate",
                        "--cov", "pythran"] + args
            except ImportError:
                print('W: Skipping coverage analysis, pytest_cov'
                       'not found')
        if pytest.main(args) == 0:
            print('\\_o<')


class BenchmarkCommand(Command):

    """Scan the test directory for any runnable test, and benchmark them."""

    default_nb_iter = 30
    modes = ("cpython", "pythran", "pythran+omp")
    description = 'run the benchmark suite for the package'
    user_options = [
        ('nb-iter=', None,
         'number of times the benchmark is run'
         '(default={0})'.format(default_nb_iter)),
        ('mode=', None,
         'mode to use ' + str(modes))
    ]

    runas_marker = '#bench '

    def __init__(self, *args, **kwargs):
        Command.__init__(self, *args, **kwargs)

    def initialize_options(self):
        self.nb_iter = BenchmarkCommand.default_nb_iter
        self.parallel = False
        self.mode = "pythran"

    def finalize_options(self):
        self.nb_iter = int(self.nb_iter)
        if self.mode not in BenchmarkCommand.modes:
            raise RuntimeError("Unknown mode : '{}'".format(self.mode))

    def run(self):
        import glob
        import timeit
        from pythran import test_compile, compile_pythranfile
        import random

        # Do not include current directory, validate using installed pythran
        current_dir = _exclude_current_dir_from_import()
        os.chdir("pythran/tests")
        where = os.path.join(current_dir, 'pythran', 'tests', 'cases')

        test_compile()

        candidates = glob.glob(os.path.join(where, '*.py'))
        sys.path.append(where)
        random.shuffle(candidates)
        for candidate in candidates:
            with file(candidate) as content:
                runas = [line for line in content.readlines()
                         if line.startswith(BenchmarkCommand.runas_marker)]
                if runas:
                    modname, _ = os.path.splitext(os.path.basename(candidate))
                    runas_commands = runas[0].replace(
                        BenchmarkCommand.runas_marker, '').split(";")
                    runas_context = ";".join(["import {0}".format(
                        modname)] + runas_commands[:-1])
                    runas_command = modname + '.' + runas_commands[-1]

                    # cleaning
                    sopath = os.path.splitext(candidate)[0] + ".so"
                    if os.path.exists(sopath):
                        os.remove(sopath)

                    ti = timeit.Timer(runas_command, runas_context)

                    print(modname + ' running ...')

                    # pythran part
                    if self.mode.startswith('pythran'):
                        cxxflags = ["-O2", "-DNDEBUG", "-DUSE_BOOST_SIMD",
                                    "-march=native"]
                        if self.mode == "pythran+omp":
                            cxxflags.append("-fopenmp")
                        begin = time.time()
                        compile_pythranfile(candidate,
                                            cxxflags=cxxflags)
                        print('Compilation in : ', (time.time() - begin))

                    sys.stdout.flush()
                    timing = numpy.array(ti.repeat(self.nb_iter, number=1))
                    print('median :', numpy.median(timing))
                    print('min :', numpy.min(timing))
                    print('max :', numpy.max(timing))
                    print('std :', numpy.std(timing))
                    del sys.modules[modname]
                else:
                    print('* Skip ', candidate, ', no ',end='')
                    print(BenchmarkCommand.runas_marker, ' directive')


# Cannot use glob here, as the files may not be generated yet
nt2_headers = (['nt2/' + '*/' * i + '*.hpp' for i in range(1, 20)] +
               ['boost/' + '*/' * i + '*.hpp' for i in range(1, 20)])

setup(name='pythran',
      version=__version__,
      description='a claimless python to c++ converter',
      author='Serge Guelton',
      author_email='serge.guelton@telecom-bretagne.eu',
      url='https://github.com/serge-sans-paille/pythran',
      packages=['pythran', 'pythran.analyses', 'pythran.transformations',
                'pythran.optimizations', 'omp', 'pythran/pythonic'],
      package_data={'pythran': ['pythran*.cfg'] + nt2_headers,
                    'pythran/pythonic': ['*/' * i + '*.hpp' for i in range(9)]
                                        + ['patch/*']},
      scripts=['scripts/pythran', 'scripts/pythran-config'],
      classifiers=['Development Status :: 4 - Beta',
                   'Environment :: Console',
                   'Intended Audience :: Developers',
                   'License :: OSI Approved :: BSD License',
                   'Natural Language :: English',
                   'Operating System :: POSIX :: Linux',
                   'Programming Language :: Python :: 2.7',
                   'Programming Language :: Python :: Implementation :: CPython',
                   'Programming Language :: C++',
                   'Topic :: Software Development :: Code Generators'],
      license="BSD 3-Clause",
      requires=['ply (>=3.4)', 'networkx (>=1.5)', 'numpy', 'colorlog'],
      cmdclass={'build': BuildWithPly,
                'test': TestCommand,
                'bench': BenchmarkCommand}
      )

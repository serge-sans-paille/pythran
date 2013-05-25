from distutils.core import setup, Command
from distutils.command.build import build
from unittest import TextTestRunner, TestLoader
import os
import sys
import shutil
from subprocess import check_call


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
            print 'nt2 git reprository not setup, cloning it'
            cmd = 'git clone https://github.com/MetaScale/nt2.git -b release'
            check_call(cmd.split())

        nt2_build_dir = os.path.join(self.build_temp, nt2_dir)
        if not os.path.isdir(nt2_build_dir):
            os.makedirs(nt2_build_dir)

        if not os.path.exists(os.path.join(nt2_build_dir, 'Makefile')):
            print 'nt2 not already configured, configuring it'

            cwd = os.getcwd()
            abs_nt2_dir = os.path.join(cwd, nt2_dir)
            os.chdir(nt2_build_dir)
            build_cmd = ['cmake',
                    abs_nt2_dir,
                    '-DCMAKE_INSTALL_PREFIX=.',
                    '-DNT2_FIND_REPOSITORIES='
                    'git://github.com/MetaScale/nt2-modules.git',
                    '-DNT2_MODULES_EXTRA='
                    'extern.boost_math']
            check_call(build_cmd)
            os.chdir(cwd)

        check_call(['make', '-C', nt2_build_dir, 'install'])
        for d in ('nt2', 'boost'):
            src = os.path.join(nt2_build_dir, 'include', d)
            target = os.path.join(self.build_lib, 'pythran', d)
            shutil.rmtree(target,True)
            shutil.copytree(src, target)

    def run(self, *args, **kwargs):
        if not self.dry_run:  # compatibility with the parent options
            self.build_ply()
            self.build_nt2()
        # regular build done by patent class
        build.run(self, *args, **kwargs)


class TestCommand(Command):
    '''Scan the test directory for any tests, and run them.'''

    description = 'run the test suite for the package'
    user_options = [('failfast', None, 'Stop upon first fail'),
                    ('cov', None, 'Perform coverage analysis')]

    def initialize_options(self):
        self.failfast = False
        self.cov = False

    def finalize_options(self):
        pass

    def run(self):
        where = os.path.join('pythran', 'tests')
        try:
            import py
            import xdist
            import multiprocessing
            cpu_count = multiprocessing.cpu_count()
            args = ["-n", str(cpu_count), where]
            if self.failfast:
                args.insert(0, '-x')
            if self.cov:
                try:
                    import pytest_cov
                    args = ["--cov-report", "html",
                            "--cov-report", "annotate",
                            "--cov", "pythran"] + args
                except ImportError:
                    print ("W: Skipping coverage analysis, pytest_cov"
                            "not found")
            if py.test.cmdline.main(args) == 0:
                print "\\_o<"
        except ImportError:
            print ("W: Using only one thread, "
                    "try to install pytest-xdist package")
            loader = TestLoader()
            t = TextTestRunner(failfast=self.failfast)
            t.run(loader.discover(where))
            if t.wasSuccessful():
                print "\\_o<"


class BenchmarkCommand(Command):
    '''Scan the test directory for any runnable test, and benchmark them.'''

    default_nb_iter = 11
    description = 'run the benchmark suite for the package'
    user_options = [
            ('nb-iter=', None,
                'number of times the benchmark is run'
                '(default={0})'.format(default_nb_iter)),
            ('mode=', None,
                'mode to use (cpython, pythran, pythran' '+omp)')
            ]

    runas_marker = '#runas '

    def __init__(self, *args, **kwargs):
        Command.__init__(self, *args, **kwargs)

    def initialize_options(self):
        self.nb_iter = BenchmarkCommand.default_nb_iter
        self.parallel = False
        self.mode = "pythran"

    def finalize_options(self):
        self.nb_iter = int(self.nb_iter)

    def run(self):
        import glob
        import timeit
        from pythran import cxx_generator, spec_parser
        from pythran import compile as pythran_compile
        where = "pythran/tests/cases/"
        candidates = glob.glob(where + '*.py')
        sys.path.append(where)
        median = lambda x: sorted(x)[len(x) / 2]
        for candidate in candidates:
            with file(candidate) as content:
                runas = [line for line in content.readlines()
                        if line.startswith(BenchmarkCommand.runas_marker)]
                if runas:
                    module_name, _ = os.path.splitext(
                            os.path.basename(candidate))
                    runas_commands = runas[0].replace(
                            BenchmarkCommand.runas_marker, '').split(";")
                    runas_context = ";".join(["import {0}".format(
                                    module_name)] + runas_commands[:-1])
                    runas_command = module_name + '.' + runas_commands[-1]

                    # cleaning
                    sopath = module_name + ".so"
                    if os.path.exists(sopath):
                        os.remove(sopath)

                    ti = timeit.Timer(runas_command, runas_context)

                    # pythran part
                    if self.mode.startswith('pythran'):
                        specs = spec_parser(candidate)
                        code = file(candidate).read()
                        mod = cxx_generator(module_name, code, specs)
                        cxxflags = ["-Ofast", "-DNDEBUG"]
                        if self.mode == "pythran+omp":
                            cxxflags.append("-fopenmp")
                        pythran_compile(os.environ.get("CXX", "c++"),
                                mod, cxxflags=cxxflags)

                    timing = median(ti.repeat(self.nb_iter, number=1))
                    print module_name, timing


setup(name='pythran',
        version='0.2.0',
        description='a claimless python to c++ converter',
        author='Serge Guelton',
        author_email='serge.guelton@telecom-bretagne.eu',
        url='https://github.com/serge-sans-paille/pythran',
        packages=['pythran', 'omp', 'pythran/pythonic++'],
        package_data={'pythran': ['pythran.h', 'pythran_gmp.h', 'pythran.cfg'],
            'pythran/pythonic++': ['pythonic++.h', 'core/*.h',
            'modules/*.h']},
        scripts=['scripts/pythran'],
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
            'Topic :: Software Development :: Code Generators',
            ],
        license="BSD 3-Clause",
        requires=['ply (>=3.4)', 'networkx (>=1.5)', 'numpy'],
        cmdclass={
            'build': BuildWithPly,
            'test': TestCommand,
            'bench': BenchmarkCommand
            }
     )

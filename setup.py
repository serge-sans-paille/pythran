from distutils.core import setup, Command
from distutils.command.build import build
from unittest import TextTestRunner, TestLoader
import os
import sys


class build_with_ply(build):
    '''Use ply to generate parsetab before building module.'''

    def run(self, *args, **kwargs):
        if not self.dry_run:
            from pythran.spec import SpecParser
            SpecParser()  # this forces the generation of the parsetab file
            self.mkpath(os.path.join(self.build_lib, 'pythran'))
            for p in ['parsetab.py']:
                target = os.path.join(self.build_lib, 'pythran', p)
                if os.path.exists(p):
                    os.rename(p, target)
                else:
                    assert os.path.exists(target)
        build.run(self, *args, **kwargs)


class TestCommand(Command):
    '''Scan the test directory for any tests, and run them.'''

    description = 'run the test suite for the package'
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        where = os.path.join('pythran', 'tests')
        try:
            import py
            import xdist
            import multiprocessing
            cpu_count = multiprocessing.cpu_count()
            py.test.cmdline.main(["-n", str(cpu_count), where])
        except ImportError:
            print ("W: Using only one thread,"
                    "try to install pytest-xdist package")
            loader = TestLoader()
            t = TextTestRunner()
            t.run(loader.discover(where))


class BenchmarkCommand(Command):
    '''Scan the test directory for any runnable test, and benchmark them.'''

    default_nb_iter = 11
    description = 'run the benchmark suite for the package'
    user_options = [
            ('nb-iter=',
                None,
                'number of times the benchmark is run (default={0})'.format(
                    default_nb_iter)),
            ('mode=',
                None,
                'mode to use (cpython, pythran, pythran + omp)')
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
        candidates = glob.glob("pythran/tests/cases/*.py")
        sys.path.append("pythran/tests/cases")
        median = lambda x: sorted(x)[len(x) / 2]
        for candidate in candidates:
            with file(candidate) as content:
                runas = [line for line in content.readlines()
                        if line.startswith(BenchmarkCommand.runas_marker)]
                if len(runas) == 1:
                    module_name, _ = os.path.splitext(
                            os.path.basename(candidate))
                    runas_commands = runas[0].replace(
                            BenchmarkCommand.runas_marker, '').split(";")
                    runas_context = ";".join(["import {0}".format(
                                    module_name)] + runas_commands[:-1])
                    runas_command = "{0}.{1}".format(module_name,
                                    runas_commands[-1])

                    # cleaning
                    sopath = module_name + ".so"
                    if os.path.exists(sopath):
                        os.remove(sopath)

                    ti = timeit.Timer(runas_command, runas_context)

                    # pythran part
                    if self.mode == 'pythran'or self.mode == 'pythran+omp':
                        specs = spec_parser(candidate)
                        mod = cxx_generator(module_name, file(candidate)
                            .read(), specs)
                        pythran_compile(os.environ.get("CXX", "c++"),
                                mod,
                                cxxflags=(["-Ofast", "-DNDEBUG"]
                                    + (["-fopenmp"]
                                        if self.mode == "pythran+omp"
                                        else [])))

                    timing = median(ti.repeat(self.nb_iter, number=1))
                    print module_name, timing


setup(name='pythran',
        version='0.2.0',
        description='a claimless python to c++ converter',
        author='Serge Guelton',
        author_email='serge.guelton@telecom-bretagne.eu',
        url='https://github.com/serge-sans-paille/pythran',
        packages=['pythran', 'omp', 'pythran/pythonic++'],
        package_data={'pythran': ['pythran.h', 'pythran_gmp.h'],
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
        requires=['ply (>=3.4)', 'networkx (>=1.5)'],
        cmdclass={'build': build_with_ply, 'test': TestCommand,
            'bench': BenchmarkCommand}
     )

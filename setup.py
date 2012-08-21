from distutils.core import setup, Command
from distutils.command.build import build

from unittest import TextTestRunner, TestLoader
import os, sys

class build_with_ply(build):
    '''Use ply to generate parsetab before building module.'''

    def run(self, *args, **kwargs):
        if not self.dry_run:
            from  pythran.spec import SpecParser
            SpecParser() # this forces the generation of the parsetab file
            self.mkpath(os.path.join(self.build_lib,'pythran'))
            for p in ['parsetab.py']:
                target = os.path.join(self.build_lib,'pythran',p)
                if os.path.exists(p):
                    os.rename(p,target)
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
        loader = TestLoader()
        t = TextTestRunner()
        t.run(loader.discover(os.path.join('pythran','tests')))

class BenchmarkCommand(Command):
    '''Scan the test directory for any runnable test, and benchmark them.'''

    description = 'run the benchmark suite for the package'
    user_options=[]

    runas_marker = '#runas '
    nb_iter=11

    def initialize_options(self):
        pass
    def finalize_options(self):
        pass
    def run(self):
        import glob, timeit
        from pythran import cxx_generator, spec_parser
        from pythran import compile as pythran_compile
        candidates=glob.glob("pythran/tests/cases/*.py")
        sys.path.append("pythran/tests/cases")
        median = lambda x: sorted(x)[len(x)/2]
        for candidate in candidates:
            with file(candidate) as content:
                runas = [ line for line in content.readlines() if line.startswith(BenchmarkCommand.runas_marker) ]
                if len(runas) == 1 :
                    module_name,_= os.path.splitext(os.path.basename(candidate))
                    runas_commands= runas[0].replace(BenchmarkCommand.runas_marker,'').split(";")
                    runas_context = ";".join( ["import {0}".format(module_name)] + runas_commands[:-1]  )
                    runas_command = "{0}.{1}".format(module_name, runas_commands[-1])

                    # cleaning
                    sopath=module_name+".so"
                    if os.path.exists(sopath): os.remove(sopath)

                    # python part
                    ti=timeit.Timer(runas_command, runas_context)
                    print module_name, median(ti.repeat(BenchmarkCommand.nb_iter,number=1)),

                    # force module reloading
                    del sys.modules[module_name]

                    # pythran part
                    specs = spec_parser(candidate)
                    mod = cxx_generator(module_name, file(candidate).read(), specs)
                    pythran_compile(os.environ.get("CXX","c++"), mod, cxxflags=["-O3", "-DNDEBUG"])
                    ti=timeit.Timer(runas_command, runas_context)
                    print median(ti.repeat(BenchmarkCommand.nb_iter,number=1))


setup(  name='pythran',
        version='0.1.0',
        description='a claimless python to c++ converter',
        author='Serge Guelton',
        author_email='serge.guelton@telecom-bretagne.eu',
        url='https://github.com/serge-sans-paille/pythran',
        packages=['pythran', 'pythran/pythonic++'],
        package_data = { 'pythran': ['pythran.h'], 'pythran/pythonic++': ['pythonic++.h', 'core/*.h', 'modules/*.h'] },
        scripts= ['scripts/pythran'],
        classifiers= [
            'Development Status :: 3 - Alpha',
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
        cmdclass= { 'build' : build_with_ply, 'test' : TestCommand, 'bench' : BenchmarkCommand }
     )

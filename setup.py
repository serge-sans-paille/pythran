from distutils.core import setup, Command
from distutils.command.build import build

from unittest import TextTestRunner, TestLoader
import os

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
    '''Scan the test directory for any tests, and run them'''

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

setup(  name='pythran',
        version='0.1.0',
        description='a claimless python to c++ converter',
        author='Serge Guelton',
        author_email='serge.guelton@telecom-bretagne.eu',
        url="http://serge.liyun.free.fr/serge",
        packages=['pythran', 'pythran/pythonic++'],
        package_data = { 'pythran': ['pythran.h'], 'pythran/pythonic++': ['pythonic++.h', 'core/*.h', 'modules/*.h'] },
        scripts= ['scripts/pythran'],
        requires=['ply (>=3.4)', 'networkx (>=1.5)'],
        cmdclass= { 'build' : build_with_ply, 'test' : TestCommand }
     )

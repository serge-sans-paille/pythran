from distutils.core import setup, Command
from unittest import TextTestRunner, TestLoader
import os

class TestCommand(Command):
    description = "run the test suite for the package"
    user_options = []

    def initialize_options(self):
        pass
    def finalize_options(self):
        pass
    def run(self):
        loader = TestLoader()
        t = TextTestRunner()
        t.run(loader.discover(os.path.join("pythran","tests")))


setup(  name='pythran',
        version='0.1.0',
        description='Light Python to C++ converter',
        author='Serge Guelton',
        author_email='serge.guelto@telecom-bretagne.eu',
        url="http://serge.liyun.free.fr/serge",
        packages=['pythran'],
        package_data= { 'pythran' : ['pythran.h'] },
        requires=["codepy (>=2012.1.2)", "ply (>=3.4)"],
        cmdclass= { 'test' : TestCommand }
     )

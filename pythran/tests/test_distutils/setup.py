from distutils.core import setup, Extension
from pythran.dist import PythranExtension, PythranBuildExt

module1 = PythranExtension('demo', sources = ['a.py'])

setup(name = 'demo',
      version = '1.0',
      description = 'This is a demo package',
      cmdclass={"build_ext": PythranBuildExt},
      ext_modules = [module1])

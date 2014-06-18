from distutils.core import setup, Extension
from pythran.dist import PythranExtension

module1 = PythranExtension('demo', sources = ['a.py'])

setup(name = 'demo',
      version = '1.0',
      description = 'This is a demo package',
      ext_modules = [module1])

from distutils.core import setup, Extension

module1 = Extension('demo', sources = ['a.py'])

setup(name = 'demo',
      version = '1.0',
      description = 'This is a demo package',
      pythran_modules = [module1])

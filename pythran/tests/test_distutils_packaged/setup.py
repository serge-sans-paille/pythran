from distutils.core import setup, Extension

setup(name = 'demo2',
      version = '1.0',
      description = 'This is another demo package',
      packages = ['demo2'],
      pythran_modules = [Extension('demo2.a', sources = ['a.py'])])

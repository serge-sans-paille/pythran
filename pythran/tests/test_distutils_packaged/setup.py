from distutils.core import setup, Extension
from pythran import PythranExtension

setup(name = 'demo2',
      version = '1.0',
      description = 'This is another demo package',
      packages = ['demo2'],
      ext_modules = [PythranExtension('demo2.a', sources = ['a.py'])])

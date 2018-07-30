from distutils.core import setup, Extension
from pythran.dist import PythranExtension, PythranBuildExt

setup(name = 'demo2',
      version = '1.0',
      description = 'This is another demo package',
      packages = ['demo2'],
      cmdclass={"build_ext": PythranBuildExt},
      ext_modules = [PythranExtension('demo2.a', sources = ['a.py'])])

from numpy.distutils.core import setup
from numpy.distutils.command.build_ext import build_ext as npy_build_ext
from pythran.dist import PythranExtension, PythranBuildExt

module1 = PythranExtension('demo3.a', sources = ['demo3/a.py'])

setup(name = 'demo3',
      version = '1.0',
      description = 'This is a demo package',
      cmdclass={"build_ext": PythranBuildExt[npy_build_ext]},
      ext_modules = [module1])

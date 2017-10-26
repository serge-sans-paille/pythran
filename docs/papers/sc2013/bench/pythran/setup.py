from distutils.core import setup
from distutils.core import Command
from distutils.extension import Extension
from os import path
import pythran

class build_ext(Command):

    description = 'build pythran extension',
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        self.extensions = self.distribution.ext_modules

    def run(self):
        import os
        for extension in self.extensions:
            source = extension.sources[0]
            out = extension.name + '.so'
            if not path.isfile(out) or path.getmtime(source) > path.getmtime(out):
                print 'building pythran extension', extension.name
                content = file(source).read()

                module = pythran.cxx_generator(
                        extension.name,
                        content,
                        pythran.spec_parser(content),
                        []
                        )

                pythran.compile(
                        os.environ.get('CXX','c++'),
                        module,
                        out,
                        cxxflags = ['-O2', '-g'] + extension.extra_compile_args + extension.extra_link_args
                        )


setup(
        cmdclass = {'build_ext': build_ext},
        ext_modules = [
            Extension("convolution", ["convolution.py"]),
            Extension("convolution_omp", ["convolution.py"], extra_compile_args=['-fopenmp']),
            Extension("fbcorr",   ["fbcorr.py"]),
            Extension("fbcorr_omp",   ["fbcorr.py"], extra_compile_args=['-fopenmp']),
            Extension("mandel", ["mandel.py"]),
            Extension("mandel_omp", ["mandel.py"], extra_compile_args=['-fopenmp']),
            Extension("matmul", ["matmul.py"]),
            Extension("matmul_omp", ["matmul.py"], extra_compile_args=['-fopenmp']),
            Extension("wave_", ["wave_.py"]),
            Extension("wave__omp", ["wave_.py"], extra_compile_args=['-fopenmp']),
            Extension("pairwise", ["pairwise.py"]),
            Extension("pairwise_omp", ["pairwise.py"], extra_compile_args=['-fopenmp']),
            Extension("hyantes", ["hyantes.py"]),
            Extension("hyantes_omp", ["hyantes.py"], extra_compile_args=['-fopenmp']),
            Extension("pi_buffon_omp", ["pi_buffon.py"], extra_compile_args=['-fopenmp']),
            ]
     )

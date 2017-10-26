from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

setup(
        cmdclass = {'build_ext': build_ext},
        ext_modules = [
            Extension("cconvolution", ["convolution.pyx"]),
            Extension("cconvolution_omp",   ["convolution_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            Extension("cfbcorr", ["fbcorr_cython.pyx"]),
            Extension("cfbcorr_omp",   ["fbcorr_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            Extension("cmandel", ["mandel_cython.pyx"]),
            Extension("cmandel_omp",   ["mandel_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            Extension("cmatmul", ["matmul_cython.pyx"]),
            Extension("cmatmul_omp",   ["matmul_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            Extension("cpairwise", ["pairwise.pyx"]),
            Extension("cpairwise_omp", ["pairwise_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            Extension("cwave_", ["wave_.pyx"]),
            Extension("cwave__omp", ["wave_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            Extension("chyantes", ["hyantes.pyx"]),
            Extension("chyantes_omp", ["hyantes_para.pyx"], extra_compile_args=['-fopenmp'], extra_link_args=['-fopenmp']),
            ]
     )
